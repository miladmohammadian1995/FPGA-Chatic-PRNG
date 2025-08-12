#ifndef PRNG_H
#define PRNG_H

#include <ap_int.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h> // کتابخانه لازم برای کار با استریم استاندارد AXI

// تعریف ساختار بسته خروجی برای استریم
typedef ap_axiu<8, 0, 0, 0> stream_packet;

// معرفی تابع اصلی با نوع استریم استاندارد
void prng_generator(
    double                  seed,
    int                     n_bits,
    int                     num_bits,
    hls::stream<stream_packet> &out_stream
);

#endif // PRNG_H
