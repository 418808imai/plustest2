// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1_AR72614 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xmuladd.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XMuladd_CfgInitialize(XMuladd *InstancePtr, XMuladd_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Axilites_BaseAddress = ConfigPtr->Axilites_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XMuladd_Start(XMuladd *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMuladd_ReadReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_AP_CTRL) & 0x80;
    XMuladd_WriteReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_AP_CTRL, Data | 0x01);
}

u32 XMuladd_IsDone(XMuladd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMuladd_ReadReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XMuladd_IsIdle(XMuladd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMuladd_ReadReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XMuladd_IsReady(XMuladd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMuladd_ReadReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XMuladd_EnableAutoRestart(XMuladd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMuladd_WriteReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_AP_CTRL, 0x80);
}

void XMuladd_DisableAutoRestart(XMuladd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMuladd_WriteReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_AP_CTRL, 0);
}

u32 XMuladd_Get_return(XMuladd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMuladd_ReadReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_AP_RETURN);
    return Data;
}
u32 XMuladd_Get_a_BaseAddress(XMuladd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XMULADD_AXILITES_ADDR_A_BASE);
}

u32 XMuladd_Get_a_HighAddress(XMuladd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XMULADD_AXILITES_ADDR_A_HIGH);
}

u32 XMuladd_Get_a_TotalBytes(XMuladd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMULADD_AXILITES_ADDR_A_HIGH - XMULADD_AXILITES_ADDR_A_BASE + 1);
}

u32 XMuladd_Get_a_BitWidth(XMuladd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMULADD_AXILITES_WIDTH_A;
}

u32 XMuladd_Get_a_Depth(XMuladd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMULADD_AXILITES_DEPTH_A;
}

u32 XMuladd_Write_a_Words(XMuladd *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMULADD_AXILITES_ADDR_A_HIGH - XMULADD_AXILITES_ADDR_A_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Axilites_BaseAddress + XMULADD_AXILITES_ADDR_A_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMuladd_Read_a_Words(XMuladd *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMULADD_AXILITES_ADDR_A_HIGH - XMULADD_AXILITES_ADDR_A_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Axilites_BaseAddress + XMULADD_AXILITES_ADDR_A_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMuladd_Write_a_Bytes(XMuladd *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMULADD_AXILITES_ADDR_A_HIGH - XMULADD_AXILITES_ADDR_A_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Axilites_BaseAddress + XMULADD_AXILITES_ADDR_A_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMuladd_Read_a_Bytes(XMuladd *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMULADD_AXILITES_ADDR_A_HIGH - XMULADD_AXILITES_ADDR_A_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Axilites_BaseAddress + XMULADD_AXILITES_ADDR_A_BASE + offset + i);
    }
    return length;
}

u32 XMuladd_Get_b_BaseAddress(XMuladd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XMULADD_AXILITES_ADDR_B_BASE);
}

u32 XMuladd_Get_b_HighAddress(XMuladd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XMULADD_AXILITES_ADDR_B_HIGH);
}

u32 XMuladd_Get_b_TotalBytes(XMuladd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMULADD_AXILITES_ADDR_B_HIGH - XMULADD_AXILITES_ADDR_B_BASE + 1);
}

u32 XMuladd_Get_b_BitWidth(XMuladd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMULADD_AXILITES_WIDTH_B;
}

u32 XMuladd_Get_b_Depth(XMuladd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMULADD_AXILITES_DEPTH_B;
}

u32 XMuladd_Write_b_Words(XMuladd *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMULADD_AXILITES_ADDR_B_HIGH - XMULADD_AXILITES_ADDR_B_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Axilites_BaseAddress + XMULADD_AXILITES_ADDR_B_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMuladd_Read_b_Words(XMuladd *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMULADD_AXILITES_ADDR_B_HIGH - XMULADD_AXILITES_ADDR_B_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Axilites_BaseAddress + XMULADD_AXILITES_ADDR_B_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMuladd_Write_b_Bytes(XMuladd *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMULADD_AXILITES_ADDR_B_HIGH - XMULADD_AXILITES_ADDR_B_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Axilites_BaseAddress + XMULADD_AXILITES_ADDR_B_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMuladd_Read_b_Bytes(XMuladd *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMULADD_AXILITES_ADDR_B_HIGH - XMULADD_AXILITES_ADDR_B_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Axilites_BaseAddress + XMULADD_AXILITES_ADDR_B_BASE + offset + i);
    }
    return length;
}

void XMuladd_InterruptGlobalEnable(XMuladd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMuladd_WriteReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_GIE, 1);
}

void XMuladd_InterruptGlobalDisable(XMuladd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMuladd_WriteReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_GIE, 0);
}

void XMuladd_InterruptEnable(XMuladd *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMuladd_ReadReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_IER);
    XMuladd_WriteReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_IER, Register | Mask);
}

void XMuladd_InterruptDisable(XMuladd *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMuladd_ReadReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_IER);
    XMuladd_WriteReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_IER, Register & (~Mask));
}

void XMuladd_InterruptClear(XMuladd *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMuladd_WriteReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_ISR, Mask);
}

u32 XMuladd_InterruptGetEnabled(XMuladd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMuladd_ReadReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_IER);
}

u32 XMuladd_InterruptGetStatus(XMuladd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMuladd_ReadReg(InstancePtr->Axilites_BaseAddress, XMULADD_AXILITES_ADDR_ISR);
}

