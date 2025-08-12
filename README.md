# Project Description & Reconstruction Guide

This project follows a **three-stage design flow**, starting with algorithm development in HLS, moving to RTL-level verification, and finally integrating into a complete Zynq-based system.

## 📂 Project Structure
```text
Project_Root/
│
├── 1_HLS_Source/                       # PRNG core design in C++ (Vivado HLS)
│   ├── src/                             # C++ source files
│   │   ├── prng_generator.cpp
│   │   └── prng.h
│   │
│   ├── images/                          # HLS synthesis & cosimulation outputs
│   │   ├── 1_sythesis_report_HLS.jpg
│   │   └── 2_cosimulation.jpg
│   │
│   └── tb/                              # C++ testbench for HLS simulation
│       └── prng_test.cpp
│
├── 2_RTL_Verification/                  # RTL simulation in Vivado
│   ├── images/                          # Simulation waveforms
│   │   ├── 0_simulation.jpg
│   │   └── 1_simulation.jpg
│   │
│   ├── src/                             # Verilog RTL generated from HLS + scripts
│   │   ├── prng_generator.v
│   │   ├── prng_generator_ap_dcmp_0_no_dsp_64_ip.tcl
│   │   ├── prng_generator_control_s_axi.v
│   │   └── prng_generator_dcbkb.v
│   │
│   └── tb/                              # Verilog testbench for behavioral simulation
│       └── test_bench.v
│
├── 3_System_Integration/                # Zynq-based system integration
│   ├── block_design/                    # Vivado block design & wrapper
│   │   ├── design_L1.bd
│   │   └── design_L1_wrapper.vhd
│   │
│   ├── images/                          # Block diagram & implementation summary
│   │   ├── block_diagram.pdf
│   │   └── Project Summary.jpg
│   │
│   └── ip_repo/                         # Packaged custom IP from Vivado HLS
│       └── ip/                          # Contains HDL sources, scripts, and metadata
│
├── reports/                             # Timing, utilization, and HLS reports
│   ├── design_L1_wrapper_timing_summary_routed.rpt
│   ├── design_L1_wrapper_utilization_placed.rpt
│   └── prng_generator_csynth.rpt
│
└── Readme.txt                           # Basic text info about the project
```

---

## 1️⃣ `1_HLS_Source/` — PRNG Core Design in C++ with Vivado HLS
Contains C++ source code for the chaos-based PRNG algorithm, HLS synthesis & cosimulation report images, and a C++ testbench for software-level verification.

**Reconstruction:**
1. Open Vivado HLS and create a new project.
2. Add files from `src/` and `tb/`.
3. Run **C Simulation**, **C Synthesis**, and **Cosimulation**.
4. Once verified, **Export RTL** for the next stage.

---

## 2️⃣ `2_RTL_Verification/` — RTL Simulation in Vivado
Contains Verilog RTL generated from HLS, AXI control logic, waveform images from Vivado behavioral simulation, and a Verilog testbench to verify signal behavior (`TVALID`, `TLAST`, etc.).

**Reconstruction:**
1. Open Vivado and create a new RTL project.
2. Add `src/` files as Design Sources and `tb/test_bench.v` as a Simulation Source.
3. Run **Behavioral Simulation** and compare results with images in `images/`.

---

## 3️⃣ `3_System_Integration/` — Zynq-Based System Integration
Includes the Vivado block design (`.bd`), system diagram images, post-implementation summary, and the IP repository containing the packaged PRNG IP from Vivado HLS for reuse.

**Reconstruction:**
1. Open Vivado and create a new Zynq project.
2. Add the `ip_repo/` path in **Settings → IP → Repository** to make the custom IP available.
3. Import `design_L1.bd` from `block_design/`.
4. Regenerate the block design and run **Synthesis** and **Implementation**.

---

## 4️⃣ `reports/` — Final Reports
Contains post-route timing analysis, FPGA resource utilization, and the HLS synthesis report for the PRNG core.  
These can be used to validate design performance against your own results.

---

**Note:**  
The project has been **fully designed, synthesized, and simulated**, but **on-board testing was not performed** due to the absence of physical FPGA hardware.
