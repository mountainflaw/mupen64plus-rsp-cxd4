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

#include "Rsp_#1.1.h"
#include "rsp.h"

#include "su.h"
#include "vu/vu.h"
#include "matrix.h"

void run_task(void)
{
    register int PC;
    register int i;

    if (CFG_WAIT_FOR_CPU_HOST != 0)
        for (i = 0; i < 32; i++)
            MFC0_count[i] = 0;
    PC = *RSP.SP_PC_REG & 0x00000FFC;
    while ((*RSP.SP_STATUS_REG & 0x00000001) == 0x00000000)
    {
        inst.W = *(unsigned int *)(RSP.IMEM + PC);
#ifdef EMULATE_STATIC_PC
        if (stage != 0) /* stage == 1 */
        {
            PC = *RSP.SP_PC_REG & 0x00000FFC;
            --stage;
        }
        else
        {
            PC = (PC + 0x004) & 0xFFC;
            *RSP.SP_PC_REG = 0x04001000 + PC;
        }
#endif
#ifdef SP_EXECUTE_LOG
        step_SP_commands(inst.W);
#endif
        if (inst.W >> 25 == 0x25) /* is a VU instruction */
        {
            COP2_C2[inst.W & 077]();
        }
        else
        {
         /* SR[0] = 0x00000000; // already handled on per-instruction basis */
            EX_SCALAR[inst.W >> 26][inst.W>>sub_op_table[inst.W >> 26] & 077]();
        }
#ifndef EMULATE_STATIC_PC
        if (stage == 2) /* branch phase of scheduler */
        {
            stage = 0*stage;
            PC = temp_PC & 0x00000FFC;
            *RSP.SP_PC_REG = temp_PC;
        }
        else
        {
            stage = 2*stage; /* next IW in branch delay slot? */
            PC = (PC + 0x004) & 0xFFC;
            *RSP.SP_PC_REG = 0x04001000 + PC;
        }
        continue;
#endif
    }
    if (*RSP.SP_STATUS_REG & 0x00000002) /* normal exit, from executing BREAK */
        return;
    else if (*RSP.MI_INTR_REG & 0x00000001) /* interrupt set by MTC0 to break */
        RSP.CheckInterrupts();
    else if (CFG_WAIT_FOR_CPU_HOST != 0) /* plugin system hack to re-sync */
        {}
    else if (*RSP.SP_SEMAPHORE_REG != 0x00000000) /* semaphore lock fixes */
        {}
    else /* ??? unknown, possibly external intervention from CPU memory map */
    {
        message("SP_SET_HALT", 3);
        return;
    }
    *RSP.SP_STATUS_REG &= ~0x00000001; /* CPU restarts with the correct SIGs. */
    return;
}
