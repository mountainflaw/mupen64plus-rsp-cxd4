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

static void VSAW(int vd, int vs, int vt, int element)
{
    register int i;

#ifdef VU_EMULATE_SCALAR_ACCUMULATOR_READ
    short result[8]; /* Prebuffer VR[vs] to prevent source overwrite. */

    for (i = 0; i < 8; i++)
        result[i] = VR[vs][i];
#else
    vs = 0;
#endif
    vt = 0;
/* Even though `vt` is ignored in VSAR, according to official sources as well
 * as reversing, lots of games seem to specify it as nonzero, possibly to
 * avoid register stalling or other VU hazards.  Not really certain why yet.
 */
    element ^= 0x8;
/* Or, for exception overrides, should this be `element &= 0x7;` ?
 * Currently this code is safer because &= is less likely to catch oddities.
 * Either way, documentation shows that the switch range is 0:2, not 8:A.
 */
    switch (element)
    {
        case 00:
            for (i = 0; i < 8; i++)
                VR[vd][i] = VACC[i].s[HI];
            break;
        case 01:
            for (i = 0; i < 8; i++)
                VR[vd][i] = VACC[i].s[MD];
            break;
        case 02:
            for (i = 0; i < 8; i++)
                VR[vd][i] = VACC[i].s[LO];
            break;
        default:
            message("VSAR\nInvalid mask.", 2);
            for (i = 0; i < 8; i++)
                VR[vd][i] = 0x0000; /* override behavior (zilmar) */
    }
#ifdef VU_EMULATE_SCALAR_ACCUMULATOR_READ
    element ^= 03;
    --element;
    for (i = 0; i < 8; i++)
        VACC[i].s[element] = result[i]; /* ... = VR[vs][i]; */
#endif
    return;
}
