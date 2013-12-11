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

void do_ge(int vs)
{
    int ge[8];
    int vce[8]; /* !(NOTEQUAL) */
    int vnc[8]; /* !(CARRY) */
    register int i;

    VCO = ~VCO; /* CARRY <-- !CARRY; NOTEQUAL <-- !NOTEQUAL */
    for (i = 0; i < N; i++)
        vnc[i] = (VCO >> (i+0x0)) & 1;
    for (i = 0; i < N; i++)
        vce[i] = (VCO >> (i+0x8)) & 1;
    VCO = 0x0000;
    for (i = 0; i < N; i++)
        ge[i] = vce[i] | vnc[i]; /* ge = (VS > VT) || (VS == VT && vnc|vce) */
    for (i = 0; i < N; i++)
        ge[i] = ge[i] & (VR[vs][i] == VC[i]); /* equal to */
    for (i = 0; i < N; i++)
        ge[i] = ge[i] | (VR[vs][i] >  VC[i]); /* greater than */
    VCC = 0x0000;
    for (i = 0; i < N; i++)
        VCC |= ge[i] << (i + 0x0);
    for (i = 0; i < N; i++)
        VCC |=     0 << (i + 0x8);
    for (i = 0; i < N; i++)
        ACC_L(i) = ge[i] ? VR[vs][i] : VC[i];
    return;
}

static void VGE_v(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][i];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE0q(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0x2 & 01) + (i & 0xE)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE1q(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0x3 & 01) + (i & 0xE)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE0h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0x4 & 03) + (i & 0xC)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE1h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0x5 & 03) + (i & 0xC)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE2h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0x6 & 03) + (i & 0xC)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE3h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0x7 & 03) + (i & 0xC)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE0w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0x8 & 07) + (i & 0x0)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE1w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0x9 & 07) + (i & 0x0)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE2w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0xA & 07) + (i & 0x0)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE3w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0xB & 07) + (i & 0x0)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE4w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0xC & 07) + (i & 0x0)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE5w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0xD & 07) + (i & 0x0)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE6w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0xE & 07) + (i & 0x0)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
static void VGE7w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VC[i] = VR[vt][(0xF & 07) + (i & 0x0)];
    do_ge(vs);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    return;
}
