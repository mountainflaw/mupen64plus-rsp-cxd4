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

static void VMACF(int vd, int vs, int vt, int e)
{
    register int i;

    for (i = 0; i < N; i++)
        VACC[i].DW += VR[vs][i]*VR_T(i) << 1;
    SIGNED_CLAMP(VMUL_PTR, SM_MUL_X);
    return;
}

static void VMACF_v(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][i];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF0q(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0x2 & 01) + (i & 0xE)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF1q(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0x3 & 01) + (i & 0xE)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF0h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0x4 & 03) + (i & 0xC)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF1h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0x5 & 03) + (i & 0xC)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF2h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0x6 & 03) + (i & 0xC)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF3h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0x7 & 03) + (i & 0xC)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF0w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0x8 & 07) + (i & 0x0)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF1w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0x9 & 07) + (i & 0x0)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF2w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0xA & 07) + (i & 0x0)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF3w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0xB & 07) + (i & 0x0)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF4w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0xC & 07) + (i & 0x0)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF5w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0xD & 07) + (i & 0x0)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF6w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0xE & 07) + (i & 0x0)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
static void VMACF7w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        VACC[i].DW += 2*VR[vs][i]*VR[vt][(0xF & 07) + (i & 0x0)];
    SIGNED_CLAMP(VR[vd], SM_MUL_X);
    return;
}
