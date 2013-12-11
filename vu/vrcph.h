/*
 * mupen64plus-rsp-cxd4 - RSP Interpreter
 * Copyright (C) 2012-2013  RJ 'Iconoclast' Swedlow
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "vu.h"
#include "divrom.h"

static void VRCPHv0(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][00] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x0 & 0x0) + (i & 0x7)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPHv1(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][01] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x1 & 0x0) + (i & 0x7)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH0q(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][02] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x2 & 0x1) + (i & 0xE)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH1q(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][03] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x3 & 0x1) + (i & 0xE)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH0h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][04] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x4 & 0x3) + (i & 0xC)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH1h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][05] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x5 & 0x3) + (i & 0xC)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH2h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][06] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x6 & 0x3) + (i & 0xC)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH3h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][07] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x7 & 0x3) + (i & 0xC)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH0w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][00] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x8 & 0x7) + (i & 0x0)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH1w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][01] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x9 & 0x7) + (i & 0x0)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH2w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][02] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0xA & 0x7) + (i & 0x0)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH3w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][03] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0xB & 0x7) + (i & 0x0)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH4w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][04] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0xC & 0x7) + (i & 0x0)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH5w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][05] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0xD & 0x7) + (i & 0x0)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH6w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][06] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0xE & 0x7) + (i & 0x0)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
static void VRCPH7w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    DivIn = VR[vt][07] << 16;
    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0xF & 0x7) + (i & 0x0)];
    VR[vd][de] = DivOut >> 16;
    DPH = 1;
    return;
}
