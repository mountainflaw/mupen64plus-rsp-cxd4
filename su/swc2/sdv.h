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

/******************************************************************************\
* Project:  SP VU Emulation Table:  Store Doubleword from Vector Unit          *
* Authors:  Iconoclast                                                         *
* Release:  2013.05.06                                                         *
* License:  none (public domain)                                               *
\******************************************************************************/

void SDV(int vt, int element, signed int offset, int base)
{
    register unsigned int addr;

    addr  = SR[base] + (offset <<= 3);
    addr &= 0x00000FFF;
    element += 0x1;
    element &= ~01; /* advance adaptation to odd-indexed halfword entries */
    switch (addr & 07)
    {
        case 00:
            *(short *)(RSP.DMEM + addr + HES(0x000)) = VR_H(vt, element);
            element += 0x2;
            element &= 0xF;
            *(short *)(RSP.DMEM + addr + HES(0x002)) = VR_H(vt, element);
            element += 0x2;
            element &= 0xF;
            *(short *)(RSP.DMEM + addr + HES(0x004)) = VR_H(vt, element);
            element += 0x2;
            element &= 0xF;
            *(short *)(RSP.DMEM + addr + HES(0x006)) = VR_H(vt, element);
            return;
        case 01:
            message("SDV\nOdd addr.", 3);
            return;
        case 02:
            *(short *)(RSP.DMEM + addr - (0x000 ^ 02)) = VR_H(vt, element);
            element += 0x2;
            element &= 0xF;
            *(short *)(RSP.DMEM + addr + (0x006 ^ 02)) = VR_H(vt, element);
            element += 0x2;
            element &= 0xF;
            *(short *)(RSP.DMEM + addr + (0x000 ^ 02)) = VR_H(vt, element);
            element += 0x2;
            element &= 0xF;
            addr += 0x006 + 02; /* halfword endian swap adjust */
            addr &= 0x00000FFF;
            *(short *)(RSP.DMEM + addr) = VR_H(vt, element);
            return;
        case 03:
            message("SDV\nOdd addr.", 3);
            return;
        case 04:
            *(short *)(RSP.DMEM + addr + HES(0x000)) = VR_H(vt, element);
            element += 0x2;
            element &= 0xF;
            *(short *)(RSP.DMEM + addr + HES(0x002)) = VR_H(vt, element);
            element += 0x2;
            element &= 0xF;
            addr += 0x004;
            addr &= 0x00000FFF;
            *(short *)(RSP.DMEM + addr + HES(0x000)) = VR_H(vt, element);
            element += 0x2;
            element &= 0xF;
            *(short *)(RSP.DMEM + addr + HES(0x002)) = VR_H(vt, element);
            return;
        case 05:
            message("SDV\nOdd addr.", 3);
            return;
        case 06:
            *(short *)(RSP.DMEM + addr - (0x000 ^ 02)) = VR_H(vt, element);
            element += 0x2;
            element &= 0xF;
            addr += 0x002;
            addr &= 0x00000FFF;
            *(short *)(RSP.DMEM + addr + (0x000 ^ 02)) = VR_H(vt, element);
            element += 0x2;
            element &= 0xF;
            *(short *)(RSP.DMEM + addr + (0x002 ^ 02)) = VR_H(vt, element);
            element += 0x2;
            element &= 0xF;
            *(short *)(RSP.DMEM + addr + (0x004 ^ 02)) = VR_H(vt, element);
            return;
        case 07:
            message("SDV\nOdd addr.", 3);
            return;
    }
}
