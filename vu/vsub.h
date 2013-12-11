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
    register int i;

    for (i = 0; i < N; i++)
        VACC_L[i] = VS[i] - VT[i] - co[i];
    SIGNED_CLAMP_SUB(VD, VS, VT);
    for (i = 0; i < N; i++)
        ne[i] = 0;
    for (i = 0; i < N; i++)
        co[i] = 0;
    return;
}

static void VSUB(int vd, int vs, int vt, int e)
{
    short ST[N];

    SHUFFLE_VECTOR(ST, VR[vt], e);
    clr_bi(VR[vd], VR[vs], ST);
    return;
}
