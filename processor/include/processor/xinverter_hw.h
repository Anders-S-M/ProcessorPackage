// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// AXI_CPU
// 0x000 : Control signals
//         bit 0  - ap_start (Read/Write/COH)
//         bit 1  - ap_done (Read/COR)
//         bit 2  - ap_idle (Read)
//         bit 3  - ap_ready (Read)
//         bit 7  - auto_restart (Read/Write)
//         others - reserved
// 0x004 : Global Interrupt Enable Register
//         bit 0  - Global Interrupt Enable (Read/Write)
//         others - reserved
// 0x008 : IP Interrupt Enable Register (Read/Write)
//         bit 0  - enable ap_done interrupt (Read/Write)
//         bit 1  - enable ap_ready interrupt (Read/Write)
//         others - reserved
// 0x00c : IP Interrupt Status Register (Read/TOW)
//         bit 0  - ap_done (COR/TOW)
//         bit 1  - ap_ready (COR/TOW)
//         others - reserved
// 0x400 ~
// 0x7ff : Memory 'in_r' (1024 * 8b)
//         Word n : bit [ 7: 0] - in_r[4n]
//                  bit [15: 8] - in_r[4n+1]
//                  bit [23:16] - in_r[4n+2]
//                  bit [31:24] - in_r[4n+3]
// 0x800 ~
// 0xbff : Memory 'out_r' (1024 * 8b)
//         Word n : bit [ 7: 0] - out_r[4n]
//                  bit [15: 8] - out_r[4n+1]
//                  bit [23:16] - out_r[4n+2]
//                  bit [31:24] - out_r[4n+3]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XINVERTER_AXI_CPU_ADDR_AP_CTRL    0x000
#define XINVERTER_AXI_CPU_ADDR_GIE        0x004
#define XINVERTER_AXI_CPU_ADDR_IER        0x008
#define XINVERTER_AXI_CPU_ADDR_ISR        0x00c
#define XINVERTER_AXI_CPU_ADDR_IN_R_BASE  0x400
#define XINVERTER_AXI_CPU_ADDR_IN_R_HIGH  0x7ff
#define XINVERTER_AXI_CPU_WIDTH_IN_R      8
#define XINVERTER_AXI_CPU_DEPTH_IN_R      1024
#define XINVERTER_AXI_CPU_ADDR_OUT_R_BASE 0x800
#define XINVERTER_AXI_CPU_ADDR_OUT_R_HIGH 0xbff
#define XINVERTER_AXI_CPU_WIDTH_OUT_R     8
#define XINVERTER_AXI_CPU_DEPTH_OUT_R     1024

