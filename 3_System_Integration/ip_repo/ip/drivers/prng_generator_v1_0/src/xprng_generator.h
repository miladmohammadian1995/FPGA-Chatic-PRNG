// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XPRNG_GENERATOR_H
#define XPRNG_GENERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xprng_generator_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XPrng_generator_Config;
#endif

typedef struct {
    u32 Control_BaseAddress;
    u32 IsReady;
} XPrng_generator;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XPrng_generator_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XPrng_generator_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XPrng_generator_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XPrng_generator_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XPrng_generator_Initialize(XPrng_generator *InstancePtr, u16 DeviceId);
XPrng_generator_Config* XPrng_generator_LookupConfig(u16 DeviceId);
int XPrng_generator_CfgInitialize(XPrng_generator *InstancePtr, XPrng_generator_Config *ConfigPtr);
#else
int XPrng_generator_Initialize(XPrng_generator *InstancePtr, const char* InstanceName);
int XPrng_generator_Release(XPrng_generator *InstancePtr);
#endif

void XPrng_generator_Start(XPrng_generator *InstancePtr);
u32 XPrng_generator_IsDone(XPrng_generator *InstancePtr);
u32 XPrng_generator_IsIdle(XPrng_generator *InstancePtr);
u32 XPrng_generator_IsReady(XPrng_generator *InstancePtr);
void XPrng_generator_EnableAutoRestart(XPrng_generator *InstancePtr);
void XPrng_generator_DisableAutoRestart(XPrng_generator *InstancePtr);

void XPrng_generator_Set_seed(XPrng_generator *InstancePtr, u64 Data);
u64 XPrng_generator_Get_seed(XPrng_generator *InstancePtr);
void XPrng_generator_Set_n_bits(XPrng_generator *InstancePtr, u32 Data);
u32 XPrng_generator_Get_n_bits(XPrng_generator *InstancePtr);
void XPrng_generator_Set_num_bits(XPrng_generator *InstancePtr, u32 Data);
u32 XPrng_generator_Get_num_bits(XPrng_generator *InstancePtr);

void XPrng_generator_InterruptGlobalEnable(XPrng_generator *InstancePtr);
void XPrng_generator_InterruptGlobalDisable(XPrng_generator *InstancePtr);
void XPrng_generator_InterruptEnable(XPrng_generator *InstancePtr, u32 Mask);
void XPrng_generator_InterruptDisable(XPrng_generator *InstancePtr, u32 Mask);
void XPrng_generator_InterruptClear(XPrng_generator *InstancePtr, u32 Mask);
u32 XPrng_generator_InterruptGetEnabled(XPrng_generator *InstancePtr);
u32 XPrng_generator_InterruptGetStatus(XPrng_generator *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
