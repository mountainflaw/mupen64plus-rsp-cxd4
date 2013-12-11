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

INLINE static void do_ch(short* VD, short* VS, short* VT)
{
    short eq[N], ge[N], le[N];
    short sn[N];
    short VC[N];
    short diff[N];
    register int i;

    for (i = 0; i < N; i++)
        VC[i] = VT[i];
    for (i = 0; i < N; i++)
        sn[i] = (VS[i] ^ VC[i]) < 0;
    for (i = 0; i < N; i++)
        VC[i] ^= -sn[i]; /* if (sn == ~0) {VT = ~VT;} else {VT =  VT;} */
    for (i = 0; i < N; i++)
        vce[i]  = (VS[i] == VC[i]); /* (VR[vs][i] + ~VC[i] == ~1); */
    for (i = 0; i < N; i++)
        vce[i] &= sn[i];
    for (i = 0; i < N; i++)
        VC[i] += sn[i]; /* converts ~(VT) into -(VT) if (sign) */
    for (i = 0; i < N; i++)
        eq[i]  = (VS[i] == VC[i]);
    for (i = 0; i < N; i++)
        eq[i] |= vce[i];

#if (0)
    for (i = 0; i < N; i++)
        le[i] = sn[i] ? (VS[i] <= VC[i]) : (VC[i] < 0);
    for (i = 0; i < N; i++)
        ge[i] = sn[i] ? (VC[i] > 0x0000) : (VS[i] >= VC[i]);
#elif (0)
    for (i = 0; i < N; i++)
        le[i] = sn[i] ? (VT[i] <= -VS[i]) : (VT[i] <= ~0x0000);
    for (i = 0; i < N; i++)
        ge[i] = sn[i] ? (~0x0000 >= VT[i]) : (VS[i] >= VT[i]);
#else
    for (i = 0; i < N; i++)
        diff[i] = -VS[i] | -(sn[i] ^ 1);
    for (i = 0; i < N; i++)
        le[i] = VT[i] <= diff[i];
    for (i = 0; i < N; i++)
        diff[i] = +VS[i] | -(sn[i] ^ 0);
    for (i = 0; i < N; i++)
        ge[i] = diff[i] >= VT[i];
#endif

    merge(comp, sn, le, ge);
    merge(VACC_L, comp, VC, VS);
    for (i = 0; i < N; i++)
        VD[i] = VACC_L[i];

    for (i = 0; i < N; i++)
        clip[i] = ge[i];
    for (i = 0; i < N; i++)
        comp[i] = le[i];
    for (i = 0; i < N; i++)
        ne[i] = eq[i] ^ 1;
    for (i = 0; i < N; i++)
        co[i] = sn[i];
    return;
}

static void VCH(void)
{
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;

    do_ch(VR[vd], VR[vs], ST);
    return;
}

static void VCH_v(void)
{
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    do_ch(VR[vd], VR[vs], VR[vt]);
    return;
}
static void VCH0q(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x2);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH1q(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x3);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH0h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x4);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH1h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x5);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH2h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x6);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH3h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x7);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH0w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x8);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH1w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x9);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH2w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xA);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH3w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xB);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH4w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xC);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH5w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xD);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH6w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xE);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
static void VCH7w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xF);
    do_ch(VR[vd], VR[vs], SV);
    return;
}
