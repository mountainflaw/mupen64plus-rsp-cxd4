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

/*
 * -1:  VT *= -1, because VS < 0 // VT ^= -2 if even, or ^= -1, += 1
 *  0:  VT *=  0, because VS = 0 // VT ^= VT
 * +1:  VT *= +1, because VS > 0 // VT ^=  0
 *      VT ^= -1, "negate" -32768 as ~+32767 (corner case hack for N64 SP)
 */
INLINE static void do_abs(short* VD, short* VS, short* VT)
{
    short neg[N], pos[N];
    short nez[N], cch[N]; /* corner case hack -- abs(-32768) == +32767 */
    short res[N];
    register int i;

    vector_copy(res, VT);
#ifndef ARCH_MIN_SSE2
#define MASK_XOR
#endif
    for (i = 0; i < N; i++)
        neg[i]  = (VS[i] <  0x0000);
    for (i = 0; i < N; i++)
        pos[i]  = (VS[i] >  0x0000);
    for (i = 0; i < N; i++)
        nez[i]  = 0;
#ifdef MASK_XOR
    for (i = 0; i < N; i++)
        neg[i]  = -neg[i];
    for (i = 0; i < N; i++)
        nez[i] += neg[i];
#else
    for (i = 0; i < N; i++)
        nez[i] -= neg[i];
#endif
    for (i = 0; i < N; i++)
        nez[i] += pos[i];
#ifdef MASK_XOR
    for (i = 0; i < N; i++)
        res[i] ^= nez[i];
    for (i = 0; i < N; i++)
        cch[i]  = (res[i] != -32768);
    for (i = 0; i < N; i++)
        res[i] += cch[i]; /* -(x) === (x ^ -1) + 1 */
#else
    for (i = 0; i < N; i++)
        res[i] *= nez[i];
    for (i = 0; i < N; i++)
        cch[i]  = (res[i] == -32768);
    for (i = 0; i < N; i++)
        res[i] -= cch[i];
#endif
    vector_copy(VACC_L, res);
    vector_copy(VD, VACC_L);
    return;
}

static void VABS(int vd, int vs, int vt, int e)
{
    short ST[N];

    SHUFFLE_VECTOR(ST, VR[vt], e);
    do_abs(VR[vd], VR[vs], ST);
    return;
}
