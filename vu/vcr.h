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

void do_cr(short* VD, short* VS, short* VT)
{
    int ge[N], le[N];
    short temp[N];
    short VC[N];
    signed short sn[N];
    register int i;

    memcpy(VC, VT, N*sizeof(short));
    for (i = 0; i < N; i++)
        sn[i] = VS[i] ^ VC[i];
    for (i = 0; i < N; i++)
        sn[i] = sn[i] >> 15;
#if (0)
    for (i = 0; i < N; i++)
        le[i] = sn[i] ? (VC[i] <= ~VS[i]) : (VC[i] <= ~0x0000);
    for (i = 0; i < N; i++)
        ge[i] = sn[i] ? (~0x0000 >= VC[i]) : (VS[i] >= VC[i]);
#else
    for (i = 0; i < N; i++)
        temp[i] = VS[i] & sn[i];
    for (i = 0; i < N; i++)
        le[i] = (VC[i] <= ~temp[i]);
    for (i = 0; i < N; i++)
        temp[i] = VS[i] | sn[i];
    for (i = 0; i < N; i++)
        ge[i] = (temp[i] >=  VC[i]);
#endif
    for (i = 0; i < N; i++)
        VC[i] ^= sn[i]; /* if (sn == ~0) {VT = ~VT;} else {VT =  VT;} */
    for (i = 0; i < N; i++)
        ACC_L(i) = le[i] ? VC[i] : VS[i];
    memcpy(VD, VACC_L, N*sizeof(short));

    for (i = 0; i < N; i++)
        clip[i] = ge[i];
    for (i = 0; i < N; i++)
        comp[i] = le[i];
    for (i = 0; i < N; i++)
        ne[i] = 0;
    for (i = 0; i < N; i++)
        co[i] = 0;
    for (i = 0; i < N; i++)
        vce[i] = 0;
    return;
}

static void VCR_v(void)
{
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    do_cr(VR[vd], VR[vs], VR[vt]);
    return;
}
static void VCR0q(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x2);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR1q(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x3);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR0h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x4);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR1h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x5);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR2h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x6);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR3h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x7);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR0w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x8);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR1w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x9);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR2w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xA);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR3w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xB);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR4w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xC);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR5w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xD);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR6w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xE);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
static void VCR7w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xF);
    do_cr(VR[vd], VR[vs], SV);
    return;
}
