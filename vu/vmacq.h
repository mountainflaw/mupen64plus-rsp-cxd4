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
 * Note about VMACQ.
 *
 * Current implementation of VMACQ is experimental.
 * It is the surviving op-code of the MPEG-DCT-designated RSP circuitries.
 * As such, for it to not be omitted, it is heavily modified from the actual.
 *
 * It was changed into this newer, archaic algorithm on the hardware.
 * Could not find any games using VMACQ, so I gave up waiting for an error
 * complaining to me that I should implement it.  The below algorithm is in
 * conformance to the suggested, explained mode of operation.
 */

static void VMACQ(void)
{
    register int i;
    const int vd = inst.R.sa;

    message("VMACQ", 2); /* untested, any N64 ROMs use this?? */
    for (i = 0; i < N; i++)
        if (VACC[i].DW & (32 << 16)) /* Bit 21 of acc. must be nonzero. */
            continue; /* VACC[i].DW += 0x000000000000; */
        else
            VACC[i].DW += (VACC[i].s[HI] & 0x8000) ? +32 << 16 : -32 << 16;
    for (i = 0; i < N; i++) /* Sign-extend 48-bit to 64-bit supersets. */
        VACC[i].HW[03] = (signed short)(VACC[i].s[HI]) >> 15;
    SIGNED_CLAMP(VMUL_PTR, SM_MUL_Q);
    return;
}
