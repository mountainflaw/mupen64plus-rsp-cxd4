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

#if (0)
#define SETBI(i)    (res[i] < 0)
#else
#define SETBI(i)    (!!(res[i] & 0x80000000))
#endif
#define SETNE(i)    (res[i] != 0)

#define BMASK(i)    ((i & 0x8) ? (ne[i-8] << i) : (bo[i-0] << i))
void set_bo(short* VD, short* VS, short* VT)
{ /* set CARRY and borrow out from difference */
    unsigned int res[N];
    register int i;

    for (i = 0; i < N; i++)
        res[i] = (unsigned short)(VS[i]) - (unsigned short)(VT[i]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(res[i]);
    for (i = 0; i < N; i++)
        VD[i] = ACC_L(i);
    for (i = 0; i < N; i++)
        ne[i] = SETNE(i);
    for (i = 0; i < N; i++)
        co[i] = SETBI(i);
    return;
}
static void VSUBC_v(void)
{
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    set_bo(VR[vd], VR[vs], VR[vt]);
    return;
}
static void VSUBC0q(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x2);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC1q(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x3);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC0h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x4);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC1h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x5);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC2h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x6);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC3h(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x7);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC0w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x8);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC1w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0x9);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC2w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xA);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC3w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xB);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC4w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xC);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC5w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xD);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC6w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xE);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
static void VSUBC7w(void)
{
    short SV[N];
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    SHUFFLE_VECTOR(SV, VR[vt], 0xF);
    set_bo(VR[vd], VR[vs], SV);
    return;
}
