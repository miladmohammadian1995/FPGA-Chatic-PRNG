// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xprng_generator.h"

extern XPrng_generator_Config XPrng_generator_ConfigTable[];

XPrng_generator_Config *XPrng_generator_LookupConfig(u16 DeviceId) {
	XPrng_generator_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XPRNG_GENERATOR_NUM_INSTANCES; Index++) {
		if (XPrng_generator_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XPrng_generator_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XPrng_generator_Initialize(XPrng_generator *InstancePtr, u16 DeviceId) {
	XPrng_generator_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XPrng_generator_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XPrng_generator_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

