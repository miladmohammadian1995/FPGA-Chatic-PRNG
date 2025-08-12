#include "prng.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>

int main() {
    // Default parameters for testing
    double seed = 0.75;
    int n_bits = 5;
    int num_bits = 1000; // Generate 2 million bits for NIST test
    const char* out_filename = "output_bits_for_nist.txt";
    int error_count = 0;

    std::cout << "--- PRNG HLS Testbench ---\n";
    std::cout << "Parameters:\n"
              << "  seed = " << seed << "\n"
              << "  n_bits = " << n_bits << "\n"
              << "  num_bits = " << num_bits << "\n";

    hls::stream<stream_packet> out_stream;

    // Call the main function
    prng_generator(seed, n_bits, num_bits, out_stream);

    std::ofstream fout(out_filename);
    if (!fout) {
        std::cerr << "ERROR: Cannot open output file " << out_filename << "\n";
        return 1;
    }

    int bits_written = 0;
    bool tlast_received = false;
    // Instead of characters, just write 0 and 1 to the file
    while (bits_written < num_bits && !tlast_received) {
        if (out_stream.empty()) {
            std::cout << "Stream is empty, but not all bits received. Early exit.\n";
            break;
        }

        stream_packet pkt = out_stream.read();
        ap_uint<8> byte_val = pkt.data;

        for (int i = 7; i >= 0; --i) {
            if (bits_written >= num_bits) break;
            bool bit = (byte_val >> i) & 1;
            fout << (bit ? '1' : '0'); // Removing '\n' for compatibility with NIST tool
            bits_written++;
        }

        if (pkt.last) {
            std::cout << "TLAST signal received. Ending stream read.\n";
            tlast_received = true;
        }
    }
    fout.close();

    if (!tlast_received && num_bits > 0) {
        std::cerr << "ERROR: TLAST signal was never received.\n";
        error_count++;
    }

    if (bits_written != num_bits) {
        std::cerr << "ERROR: Wrote " << bits_written << " bits, but expected " << num_bits << ".\n";
        error_count++;
    }

    if (error_count == 0) {
        std::cout << "SUCCESS: Simulation finished successfully. "
                  << bits_written << " bits written to " << out_filename << ".\n";
    } else {
        std::cout << "FAILURE: Simulation finished with " << error_count << " errors.\n";
    }

    return error_count;
}
