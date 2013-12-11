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

INLINE static void clr_bi(short* VD, short* VS, short* VT)
{ /* clear CARRY and borrow in to accumulators */
    signed int dif[N];
    short hi[N], lo[N];
    register int i;

    for (i = 0; i < N; i++)
        VACC_L[i] = VS[i] - VT[i] - co[i];
    for (i = 0; i < N; i++)
        dif[i] = VS[i] - VT[i] - co[i];
    for (i = 0; i < N; i++)
        ne[i] = 0;
    for (i = 0; i < N; i++)
        co[i] = 0;

/*
 * SIGNED_CLAMP(VD, SM_ADD_A);
 */
    for (i = 0; i < N; i++)
        lo[i] = (dif[i] + 0x8000) >> 31;
    for (i = 0; i < N; i++)
        hi[i] = (0x7FFF - dif[i]) >> 31;
    for (i = 0; i < N; i++)
        VD[i]  = VACC_L[i];
    for (i = 0; i < N; i++)
        VD[i] &= ~lo[i];
    for (i = 0; i < N; i++)
        VD[i] |=  hi[i];
    for (i = 0; i < N; i++)
        VD[i] ^= 0x8000 & (hi[i] | lo[i]);
    return;
}

static void VSUB(void)
{
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;

    clr_bi(VR[vd], VR[vs], ST);
    return;
}

static void VSUB_v(void)
{
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    clr_bi(VR[vd], VR[vs], VR[vt]);
    return;
}
static void VSUB0q(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x2);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB1q(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x3);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB0h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x4);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB1h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x5);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB2h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x6);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB3h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x7);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB0w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x8);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB1w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x9);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB2w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xA);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB3w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xB);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB4w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xC);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB5w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xD);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB6w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xE);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
static void VSUB7w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xF);
    clr_bi(VR[vd], VR[vs], SV);
    return;
}
