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

static void VSUB(int vd, int vs, int vt, int e)
{
    signed int result[8];
    register int i;

    for (i = 0; i < 8; i++) /* Try to vectorize the subtracts to be parallel. */
        result[i] = VR[vs][i] - VR_T(i);
    for (i = 0; i < 8; i++)
    {
        result[i] -= VCO & 0x0001;
        VCO >>= 1;
    }
    VCO = 0x0000; /* Clear the remaining, upper NOTEQUAL bits. */
    for (i = 0; i < 8; i++)
        VACC[i].s[LO] = (short)result[i];
    for (i = 0; i < 8; i++)
#ifdef FORCE_STATIC_CLAMP
    {
        const signed int under = (signed)(result[i] + 32768) >> 31;
        const signed int over  = (signed)(32767 - result[i]) >> 31;

        sclamp[1][1] = result[i] & 0x0000FFFF;
        VR_D(i) = sclamp[under + 1][over + 1];
    }
#else
        if (result[i] > +32767)
            VR_D(i) = +32767;
        else if (result[i] < -32768)
            VR_D(i) = -32768;
        else
            VR_D(i) = (short)result[i];
#endif
    return;
}
