// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xprng_generator.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XPrng_generator_CfgInitialize(XPrng_generator *InstancePtr, XPrng_generator_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XPrng_generator_Start(XPrng_generator *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPrng_generator_ReadReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_AP_CTRL) & 0x80;
    XPrng_generator_WriteReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XPrng_generator_IsDone(XPrng_generator *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPrng_generator_ReadReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XPrng_generator_IsIdle(XPrng_generator *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPrng_generator_ReadReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XPrng_generator_IsReady(XPrng_generator *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPrng_generator_ReadReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XPrng_generator_EnableAutoRestart(XPrng_generator *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPrng_generator_WriteReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XPrng_generator_DisableAutoRestart(XPrng_generator *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPrng_generator_WriteReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_AP_CTRL, 0);
}

void XPrng_generator_Set_seed(XPrng_generator *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPrng_generator_WriteReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_SEED_DATA, (u32)(Data));
    XPrng_generator_WriteReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_SEED_DATA + 4, (u32)(Data >> 32));
}

u64 XPrng_generator_Get_seed(XPrng_generator *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPrng_generator_ReadReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_SEED_DATA);
    Data += (u64)XPrng_generator_ReadReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_SEED_DATA + 4) << 32;
    return Data;
}

void XPrng_generator_Set_n_bits(XPrng_generator *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPrng_generator_WriteReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_N_BITS_DATA, Data);
}

u32 XPrng_generator_Get_n_bits(XPrng_generator *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPrng_generator_ReadReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_N_BITS_DATA);
    return Data;
}

void XPrng_generator_Set_num_bits(XPrng_generator *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPrng_generator_WriteReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_NUM_BITS_DATA, Data);
}

u32 XPrng_generator_Get_num_bits(XPrng_generator *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPrng_generator_ReadReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_NUM_BITS_DATA);
    return Data;
}

void XPrng_generator_InterruptGlobalEnable(XPrng_generator *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPrng_generator_WriteReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_GIE, 1);
}

void XPrng_generator_InterruptGlobalDisable(XPrng_generator *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPrng_generator_WriteReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_GIE, 0);
}

void XPrng_generator_InterruptEnable(XPrng_generator *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XPrng_generator_ReadReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_IER);
    XPrng_generator_WriteReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_IER, Register | Mask);
}

void XPrng_generator_InterruptDisable(XPrng_generator *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XPrng_generator_ReadReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_IER);
    XPrng_generator_WriteReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_IER, Register & (~Mask));
}

void XPrng_generator_InterruptClear(XPrng_generator *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPrng_generator_WriteReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_ISR, Mask);
}

u32 XPrng_generator_InterruptGetEnabled(XPrng_generator *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XPrng_generator_ReadReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_IER);
}

u32 XPrng_generator_InterruptGetStatus(XPrng_generator *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XPrng_generator_ReadReg(InstancePtr->Control_BaseAddress, XPRNG_GENERATOR_CONTROL_ADDR_ISR);
}

