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

static void VMOVv0(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x0 & 0x0) + (i & 0x7)];
    VR[vd][de] = ACC_L(00);
    return;
}
static void VMOVv1(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x1 & 0x0) + (i & 0x7)];
    VR[vd][de] = ACC_L(01);
    return;
}
static void VMOV0q(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x2 & 0x1) + (i & 0xE)];
    VR[vd][de] = ACC_L(02);
    return;
}
static void VMOV1q(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x3 & 0x1) + (i & 0xE)];
    VR[vd][de] = ACC_L(03);
    return;
}
static void VMOV0h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x4 & 0x3) + (i & 0xC)];
    VR[vd][de] = ACC_L(04);
    return;
}
static void VMOV1h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x5 & 0x3) + (i & 0xC)];
    VR[vd][de] = ACC_L(05);
    return;
}
static void VMOV2h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x6 & 0x3) + (i & 0xC)];
    VR[vd][de] = ACC_L(06);
    return;
}
static void VMOV3h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x7 & 0x3) + (i & 0xC)];
    VR[vd][de] = ACC_L(07);
    return;
}
static void VMOV0w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x8 & 0x7) + (i & 0x0)];
    VR[vd][de] = ACC_L(00);
    return;
}
static void VMOV1w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0x9 & 0x7) + (i & 0x0)];
    VR[vd][de] = ACC_L(01);
    return;
}
static void VMOV2w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0xA & 0x7) + (i & 0x0)];
    VR[vd][de] = ACC_L(02);
    return;
}
static void VMOV3w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0xB & 0x7) + (i & 0x0)];
    VR[vd][de] = ACC_L(03);
    return;
}
static void VMOV4w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0xC & 0x7) + (i & 0x0)];
    VR[vd][de] = ACC_L(04);
    return;
}
static void VMOV5w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0xD & 0x7) + (i & 0x0)];
    VR[vd][de] = ACC_L(05);
    return;
}
static void VMOV6w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0xE & 0x7) + (i & 0x0)];
    VR[vd][de] = ACC_L(06);
    return;
}
static void VMOV7w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int de = inst.R.rd & 07;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        ACC_L(i) = VR[vt][(0xF & 0x7) + (i & 0x0)];
    VR[vd][de] = ACC_L(07);
    return;
}
