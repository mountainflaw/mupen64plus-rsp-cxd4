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

void clr_ci(void) /* clear CARRY and carry in to accumulators */
{
    int ci[8];
    register int i;

    for (i = 0; i < N; i++)
        ci[i] = !!(VCO & 0x01<<i); /* (VCO >> i) & 1 */
    VCO = 0x0000;
    for (i = 0; i < N; i++)
        result[i] += ci[i];
    return;
}
static void VADD_v(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][i];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD0q(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0x2 & 01) + (i & 0xE)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD1q(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0x3 & 01) + (i & 0xE)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD0h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0x4 & 03) + (i & 0xC)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD1h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0x5 & 03) + (i & 0xC)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD2h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0x6 & 03) + (i & 0xC)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD3h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0x7 & 03) + (i & 0xC)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD0w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0x8 & 07) + (i & 0x0)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD1w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0x9 & 07) + (i & 0x0)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD2w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0xA & 07) + (i & 0x0)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD3w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0xB & 07) + (i & 0x0)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD4w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0xC & 07) + (i & 0x0)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD5w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0xD & 07) + (i & 0x0)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD6w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0xE & 07) + (i & 0x0)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
static void VADD7w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = VR[vs][i] + VR[vt][(0xF & 07) + (i & 0x0)];
    clr_ci();
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    SIGNED_CLAMP(VR[vd], SM_ADD_A);
    return;
}
