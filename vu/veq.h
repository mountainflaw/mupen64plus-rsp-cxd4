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

INLINE static void do_eq(short* VD, short* VS, short* VT)
{
    register int i;

    for (i = 0; i < N; i++)
        clip[i] = 0;
    for (i = 0; i < N; i++)
        comp[i] = (VS[i] == VT[i]);
    for (i = 0; i < N; i++)
        comp[i] = comp[i] & (ne[i] ^ 1);
#if (0)
    merge(VACC_L, comp, VS, VT); /* correct but redundant */
#else
    vector_copy(VACC_L, VT);
#endif
    vector_copy(VD, VACC_L);

    for (i = 0; i < N; i++)
        ne[i] = 0;
    for (i = 0; i < N; i++)
        co[i] = 0;
    return;
}

static void VEQ(int vd, int vs, int vt, int e)
{
    short ST[N];

    SHUFFLE_VECTOR(ST, VR[vt], e);
    do_eq(VR[vd], VR[vs], ST);
    return;
}
