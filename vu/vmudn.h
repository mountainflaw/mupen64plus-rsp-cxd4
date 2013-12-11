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

INLINE void do_mudn(short* VD, short* VS, short* VT)
{
    INT64 acc[N];
    register int i;

    for (i = 0; i < N; i++)
        acc[i] = (unsigned short)(VS[i]) * (signed short)(VT[i]);
    do_store(acc);
    for (i = 0; i < N; i++)
        VD[i] = ACC_L(i); /* no possibilities to clamp */
    return;
}

static void VMUDN_v(void)
{
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    do_mudn(VR[vd], VR[vs], VR[vt]);
    return;
}
static void VMUDN0q(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0x2 & 0x1) + (i & 0xE)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN1q(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0x3 & 0x1) + (i & 0xE)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN0h(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0x4 & 0x3) + (i & 0xC)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN1h(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0x5 & 0x3) + (i & 0xC)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN2h(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0x6 & 0x3) + (i & 0xC)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN3h(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0x7 & 0x3) + (i & 0xC)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN0w(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0x8 & 0x7) + (i & 0x0)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN1w(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0x9 & 0x7) + (i & 0x0)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN2w(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0xA & 0x7) + (i & 0x0)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN3w(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0xB & 0x7) + (i & 0x0)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN4w(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0xC & 0x7) + (i & 0x0)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN5w(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0xD & 0x7) + (i & 0x0)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN6w(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0xE & 0x7) + (i & 0x0)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
static void VMUDN7w(void)
{
    short SV[N];
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        SV[i] = VR[vt][(0xF & 0x7) + (i & 0x0)];
    do_mudn(VR[vd], VR[vs], SV);
    return;
}
