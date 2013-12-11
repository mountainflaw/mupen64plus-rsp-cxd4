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

INLINE static void do_madn(short* VD, short* VS, short* VT)
{
    long product[N];
    unsigned long addend[N];
    register int i;

    for (i = 0; i < N; i++)
        product[i] = (unsigned short)(VS[i]) * (signed short)(VT[i]);
    for (i = 0; i < N; i++)
        addend[i] = (product[i] & 0x00000000FFFF) >>  0;
    for (i = 0; i < N; i++)
        addend[i] = (unsigned short)ACC_L(i) + addend[i];
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)addend[i];
    for (i = 0; i < N; i++)
        addend[i] = (unsigned short)(addend[i] >> 16) + (product[i] >> 16);
    for (i = 0; i < N; i++)
        addend[i] = (unsigned short)ACC_M(i) + addend[i];
    for (i = 0; i < N; i++)
        ACC_M(i) = (short)addend[i];
    for (i = 0; i < N; i++)
        result[i] = (ACC_H(i) << 16) + addend[i];
    for (i = 0; i < N; i++)
        ACC_H(i) = (short)(result[i] >> 16);
    SIGNED_CLAMP(VD, SM_MUL_Z);
    return;
}

static void VMADN(void)
{
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;

    do_madn(VR[vd], VR[vs], ST);
    return;
}

static void VMADN_v(void)
{
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    do_madn(VR[vd], VR[vs], VR[vt]);
    return;
}
static void VMADN0q(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x2);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN1q(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x3);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN0h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x4);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN1h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x5);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN2h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x6);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN3h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x7);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN0w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x8);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN1w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x9);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN2w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xA);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN3w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xB);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN4w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xC);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN5w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xD);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN6w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xE);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
static void VMADN7w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xF);
    do_madn(VR[vd], VR[vs], SV);
    return;
}
