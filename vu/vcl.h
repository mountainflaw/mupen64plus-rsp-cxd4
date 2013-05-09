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

static void VCL(int vd, int vs, int vt, int e)
{
    int ge, le;
    register int i;

    for (i = 0; i < 8; i++)
    {
        const unsigned short VS = (unsigned short)VR[vs][i];
        const unsigned short VT = (unsigned short)VR[vt][ei[e][i]];
        const int eq = (((VCO >> (i + 8)) & 1) == 0); /* !(NOTEQUAL) */

        if ((VCO >> i) & 1)
        {
            ge = (VCC >> (i + 8)) & 1;
            if (eq)
            {
                const int sum = VS + VT;
                int ce = (VCE >> i) & 1;
                int lz = ((sum & 0x0000FFFF) == 0x00000000);
                int uz = ((sum & 0xFFFF0000) == 0x00000000); /* !carryout */

                le = (ce & (lz | uz)) | ((!ce) & (lz & uz));
            }
            else
                le = (VCC >> i) & 1;
            VACC[i].s[LO] = le ? -VT : VS;
        }
        else
        {
            le = (VCC >> i) & 1;
            ge = eq ? (VS - VT >= 0) : (VCC >> (i + 8)) & 1;
            VACC[i].s[LO] = ge ? VT : VS;
        }
        VCC &= ~(0x0101 << i);
        VCC |= (ge << (i + 8)) | (le << (i + 0));
    }
    for (i = 0; i < 8; i++)
        VR[vd][i] = VACC[i].s[LO];
    VCO = 0x0000;
    VCE = 0x00;
    return;
}
