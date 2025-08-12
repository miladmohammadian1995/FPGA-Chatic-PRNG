// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of seed
//        bit 31~0 - seed[31:0] (Read/Write)
// 0x14 : Data signal of seed
//        bit 31~0 - seed[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of n_bits
//        bit 31~0 - n_bits[31:0] (Read/Write)
// 0x20 : reserved
// 0x24 : Data signal of num_bits
//        bit 31~0 - num_bits[31:0] (Read/Write)
// 0x28 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XPRNG_GENERATOR_CONTROL_ADDR_AP_CTRL       0x00
#define XPRNG_GENERATOR_CONTROL_ADDR_GIE           0x04
#define XPRNG_GENERATOR_CONTROL_ADDR_IER           0x08
#define XPRNG_GENERATOR_CONTROL_ADDR_ISR           0x0c
#define XPRNG_GENERATOR_CONTROL_ADDR_SEED_DATA     0x10
#define XPRNG_GENERATOR_CONTROL_BITS_SEED_DATA     64
#define XPRNG_GENERATOR_CONTROL_ADDR_N_BITS_DATA   0x1c
#define XPRNG_GENERATOR_CONTROL_BITS_N_BITS_DATA   32
#define XPRNG_GENERATOR_CONTROL_ADDR_NUM_BITS_DATA 0x24
#define XPRNG_GENERATOR_CONTROL_BITS_NUM_BITS_DATA 32

