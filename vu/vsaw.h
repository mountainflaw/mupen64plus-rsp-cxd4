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

static void VSAW(int vd, int vs, int vt, int e)
{
    register int i;
#ifdef VU_EMULATE_SCALAR_ACCUMULATOR_READ
    for (i = 0; i < N; i++)
        result[i] = VR[vs][i];
#endif
    vs = vt = 0;
/* Even though `vt` is ignored in VSAR, according to official sources as well
 * as reversing, lots of games seem to specify it as nonzero, possibly to
 * avoid register stalling or other VU hazards.  Not really certain why yet.
 */
    e ^= 0x8;
/* Or, for exception overrides, should this be `e &= 0x7;` ?
 * Currently this code is safer because &= is less likely to catch oddities.
 * Either way, documentation shows that the switch range is 0:2, not 8:A.
 */
    e = 2 - e;
    if (e < 0)
    {
        message("VSAR\nInvalid mask.", 2);
        for (i = vs; i < 8; i++)
            VR_D(i) = 0x0000; /* override behavior (zilmar) */
    }
    else
        for (i = vs; i < 8; i++)
            VR_D(i) = VACC[i].s[e];
#ifdef VU_EMULATE_SCALAR_ACCUMULATOR_READ
    e ^= 03;
    --e;
    for (i = 0; i < N; i++)
        VACC[i].s[e] = result[i]; /* ... = VR[vs][i]; */
#endif
    return;
}

static void VSAWH(void)
{
    register int i;
    const int vd = inst.R.sa;

    for (i = 0; i < N; i++)
        VR[vd][i] = VACC[i].s[HI];
    return;
}
static void VSAWM(void)
{
    register int i;
    const int vd = inst.R.sa;

    for (i = 0; i < N; i++)
        VR[vd][i] = VACC[i].s[MD];
    return;
}
static void VSAWL(void)
{
    register int i;
    const int vd = inst.R.sa;

    for (i = 0; i < N; i++)
        VR[vd][i] = VACC[i].s[LO];
    return;
}
