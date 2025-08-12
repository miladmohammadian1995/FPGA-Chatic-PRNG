#include "prng.h"

typedef unsigned int uint32_t;

// Using the original 48-bit precision
typedef ap_fixed<48, 5> prng_fixed_t;

// Helper function for the core calculation (unchanged)
prng_fixed_t calculate_x_new(prng_fixed_t r, prng_fixed_t x_log_in) {
    #pragma HLS INLINE
    prng_fixed_t x_new = r * x_log_in * (prng_fixed_t(1.0) - x_log_in);

    if (x_new < 0) {
        x_new = -x_new;
    }
    if (x_new > 10.0) {
        x_new = prng_fixed_t(1.0) + (x_new - (int)x_new);
    }
    return (x_new != 0.0) ? x_new : prng_fixed_t(0.5);
}


void prng_generator(
    double                  seed,
    int                     n_bits,
    int                     num_bits,
    hls::stream<stream_packet> &out_stream
) {
#pragma HLS INTERFACE s_axilite port=seed     bundle=control
#pragma HLS INTERFACE s_axilite port=n_bits   bundle=control
#pragma HLS INTERFACE s_axilite port=num_bits bundle=control
#pragma HLS INTERFACE s_axilite port=return   bundle=control
#pragma HLS INTERFACE axis      port=out_stream

    #pragma HLS ALLOCATION instances=mul limit=4 operation

    // ✅ New Solution: Calculate total bytes to send at the beginning.
    // This ensures the core logic is not manipulated.
    int total_bytes_to_send = (num_bits > 0) ? ((num_bits - 1) / 8 + 1) : 0;
    int bytes_sent = 0;

    // --- Return to the original, untouched logic ---
    const prng_fixed_t r  = 3.97;
    prng_fixed_t x_log    = seed;
    prng_fixed_t x_F      = 0.0;
    prng_fixed_t y_F      = 0.0;

    int          total_bits = 0;
    ap_uint<8>   curr_byte  = 0;
    int          bit_pos    = 7;

    // This loop and all logic within it is identical to your original code
    while (total_bits < num_bits) {
        #pragma HLS PIPELINE

        prng_fixed_t x_log_iter0, x_log_iter1, x_log_iter2, x_log_iter3, x_log_iter4;
        prng_fixed_t X_F_cur1_local, X_F_cur2_local;

        x_log_iter0 = calculate_x_new(r, x_log);
        X_F_cur1_local = x_log_iter0;

        x_log_iter1 = calculate_x_new(r, x_log_iter0);
        prng_fixed_t tmp1 = (x_log_iter1 + prng_fixed_t(1.0)) * r + (X_F_cur1_local + prng_fixed_t(1.0)) * r;
        prng_fixed_t v1   = prng_fixed_t(1.0) + (tmp1 - (int)tmp1);
        x_F = (v1 != 0.0) ? v1 : prng_fixed_t(0.5);

        x_log_iter2 = calculate_x_new(r, x_log_iter1);
        X_F_cur2_local = x_log_iter2;

        x_log_iter3 = calculate_x_new(r, x_log_iter2);
        prng_fixed_t tmp2 = (x_log_iter3 + prng_fixed_t(1.0)) * r + (X_F_cur2_local + prng_fixed_t(1.0)) * r;
        prng_fixed_t v2   = prng_fixed_t(1.0) + (tmp2 - (int)tmp2);
        y_F = (v2 != 0.0) ? v2 : prng_fixed_t(0.5);

        x_log_iter4 = calculate_x_new(r, x_log_iter3);
        x_log = x_log_iter4;

        uint32_t I1 = x_log.range(31, 0);
        uint32_t I2 = y_F.range(31, 0);
        uint32_t I3 = x_F.range(31, 0);

        uint32_t combined = I1 ^ I2 ^ I3;
        uint32_t mask     = (1u << n_bits) - 1u;
        uint32_t val      = combined & mask;

        for (int b = n_bits - 1; b >= 0; --b) {
            if (total_bits >= num_bits) break;

            ap_uint<1> bit = (val >> b) & 1u;
            curr_byte[bit_pos] = bit;
            --bit_pos;
            ++total_bits;

            if (bit_pos < 0) {
                stream_packet pkt;
                pkt.data = curr_byte;
                pkt.keep = 0xff;
                bytes_sent++;
                // ✅ Safe Change: TLAST is set based only on the byte counter
                pkt.last = (bytes_sent == total_bytes_to_send);
                out_stream.write(pkt);

                curr_byte = 0;
                bit_pos   = 7;
            }
        }
    }

    if (bit_pos != 7) {
        stream_packet pkt;
        pkt.data = curr_byte;
        pkt.keep = 0xff;
        bytes_sent++;
        // ✅ Safe Change: This packet is definitely the last one
        pkt.last = (bytes_sent == total_bytes_to_send);
        out_stream.write(pkt);
    }
}
