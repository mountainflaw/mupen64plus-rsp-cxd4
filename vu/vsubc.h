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
#define SETBI(i)    (result[i] < 0)
#else
#define SETBI(i)    (!!(result[i] & 0x80000000))
#endif
#define SETNE(i)    (result[i] != 0)

#define BMASK(i)    ((i & 0x8) ? (ne[i-8] << i) : (bo[i-0] << i))
void set_bo(void) /* set CARRY and borrow out from difference */
{
    register int i;

    for (i = 0; i < N; i++)
        ne[i] = SETNE(i);
    for (i = 0; i < N; i++)
        co[i] = SETBI(i);
    return;
}
static void VSUBC_v(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] = (unsigned short)(VR[vs][i]) - (unsigned short)(VR[vt][i]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC0q(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0x2 & 01) + (i & 0xE)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC1q(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0x3 & 01) + (i & 0xE)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC0h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0x4 & 03) + (i & 0xC)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC1h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0x5 & 03) + (i & 0xC)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC2h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0x6 & 03) + (i & 0xC)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC3h(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0x7 & 03) + (i & 0xC)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC0w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0x8 & 07) + (i & 0x0)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC1w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0x9 & 07) + (i & 0x0)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC2w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0xA & 07) + (i & 0x0)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC3w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0xB & 07) + (i & 0x0)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC4w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0xC & 07) + (i & 0x0)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC5w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0xD & 07) + (i & 0x0)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC6w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0xE & 07) + (i & 0x0)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
static void VSUBC7w(void)
{
    register int i;
    const int vd = inst.R.sa;
    const int vs = inst.R.rd;
    const int vt = inst.R.rt;

    for (i = 0; i < N; i++)
        result[i] =
            (unsigned short)(VR[vs][i])
          - (unsigned short)(VR[vt][(0xF & 07) + (i & 0x0)]);
    for (i = 0; i < N; i++)
        ACC_L(i) = (short)(result[i]);
    for (i = 0; i < N; i++)
        VR[vd][i] = ACC_L(i);
    set_bo();
    return;
}
