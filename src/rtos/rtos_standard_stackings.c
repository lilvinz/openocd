/***************************************************************************
 *   Copyright (C) 2011 by Broadcom Corporation                            *
 *   Evan Hunter - ehunter@broadcom.com                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "rtos.h"

static const struct stack_register_offset rtos_standard_Cortex_M3_stack_offsets[] = {
	{ 0x20, 32 },		/* r0   */
	{ 0x24, 32 },		/* r1   */
	{ 0x28, 32 },		/* r2   */
	{ 0x2c, 32 },		/* r3   */
	{ 0x00, 32 },		/* r4   */
	{ 0x04, 32 },		/* r5   */
	{ 0x08, 32 },		/* r6   */
	{ 0x0c, 32 },		/* r7   */
	{ 0x10, 32 },		/* r8   */
	{ 0x14, 32 },		/* r9   */
	{ 0x18, 32 },		/* r10  */
	{ 0x1c, 32 },		/* r11  */
	{ 0x30, 32 },		/* r12  */
	{ -2,   32 },		/* sp   */
	{ 0x34, 32 },		/* lr   */
	{ 0x38, 32 },		/* pc   */
	{ -1,   96 },		/* FPA1 */
	{ -1,   96 },		/* FPA2 */
	{ -1,   96 },		/* FPA3 */
	{ -1,   96 },		/* FPA4 */
	{ -1,   96 },		/* FPA5 */
	{ -1,   96 },		/* FPA6 */
	{ -1,   96 },		/* FPA7 */
	{ -1,   96 },		/* FPA8 */
	{ -1,   32 },		/* FPS  */
	{ 0x3c, 32 },		/* xPSR */
};

static const struct stack_register_offset rtos_standard_Cortex_M4F_stack_offsets[] = {
	{ 0x24, 32 },		/* r0   */
	{ 0x28, 32 },		/* r1   */
	{ 0x2c, 32 },		/* r2   */
	{ 0x30, 32 },		/* r3   */
	{ 0x00, 32 },		/* r4   */
	{ 0x04, 32 },		/* r5   */
	{ 0x08, 32 },		/* r6   */
	{ 0x0c, 32 },		/* r7   */
	{ 0x10, 32 },		/* r8   */
	{ 0x14, 32 },		/* r9   */
	{ 0x18, 32 },		/* r10  */
	{ 0x1c, 32 },		/* r11  */
	{ 0x34, 32 },		/* r12  */
	{ -2,   32 },		/* sp   */
	{ 0x38, 32 },		/* lr   */
	{ 0x3c, 32 },		/* pc   */
	{ -1,   96 },		/* FPA1 */
	{ -1,   96 },		/* FPA2 */
	{ -1,   96 },		/* FPA3 */
	{ -1,   96 },		/* FPA4 */
	{ -1,   96 },		/* FPA5 */
	{ -1,   96 },		/* FPA6 */
	{ -1,   96 },		/* FPA7 */
	{ -1,   96 },		/* FPA8 */
	{ -1,   32 },		/* FPS  */
	{ 0x40, 32 },		/* xSPR */
};

static const struct stack_register_offset rtos_standard_Cortex_M4F_FPU_stack_offsets[] = {
	{ 0x64, 32 },		/* r0   */
	{ 0x68, 32 },		/* r1   */
	{ 0x6c, 32 },		/* r2   */
	{ 0x70, 32 },		/* r3   */
	{ 0x00, 32 },		/* r4   */
	{ 0x04, 32 },		/* r5   */
	{ 0x08, 32 },		/* r6   */
	{ 0x0c, 32 },		/* r7   */
	{ 0x10, 32 },		/* r8   */
	{ 0x14, 32 },		/* r9   */
	{ 0x18, 32 },		/* r10  */
	{ 0x1c, 32 },		/* r11  */
	{ 0x74, 32 },		/* r12  */
	{ -2,   32 },		/* sp   */
	{ 0x78, 32 },		/* lr   */
	{ 0x7c, 32 },		/* pc   */
	{ -1,   96 },		/* FPA1 */
	{ -1,   96 },		/* FPA2 */
	{ -1,   96 },		/* FPA3 */
	{ -1,   96 },		/* FPA4 */
	{ -1,   96 },		/* FPA5 */
	{ -1,   96 },		/* FPA6 */
	{ -1,   96 },		/* FPA7 */
	{ -1,   96 },		/* FPA8 */
	{ -1,   32 },		/* FPS  */
	{ 0x80, 32 },		/* xSPR */
};

static const struct stack_register_offset rtos_standard_Cortex_R4_stack_offsets[] = {
	{ 0x08, 32 },		/* r0  (a1)   */
	{ 0x0c, 32 },		/* r1  (a2)  */
	{ 0x10, 32 },		/* r2  (a3)  */
	{ 0x14, 32 },		/* r3  (a4)  */
	{ 0x18, 32 },		/* r4  (v1)  */
	{ 0x1c, 32 },		/* r5  (v2)  */
	{ 0x20, 32 },		/* r6  (v3)  */
	{ 0x24, 32 },		/* r7  (v4)  */
	{ 0x28, 32 },		/* r8  (a1)  */
	{ 0x2c, 32 },		/* r9  (sb)  */
	{ 0x30, 32 },		/* r10 (sl) */
	{ 0x34, 32 },		/* r11 (fp) */
	{ 0x38, 32 },		/* r12 (ip) */
	{ -2,   32 },		/* sp   */
	{ 0x3c, 32 },		/* lr   */
	{ 0x40, 32 },		/* pc   */
	{ -1,   96 },		/* FPA1 */
	{ -1,   96 },		/* FPA2 */
	{ -1,   96 },		/* FPA3 */
	{ -1,   96 },		/* FPA4 */
	{ -1,   96 },		/* FPA5 */
	{ -1,   96 },		/* FPA6 */
	{ -1,   96 },		/* FPA7 */
	{ -1,   96 },		/* FPA8 */
	{ -1,   32 },		/* FPS  */
	{ 0x04, 32 },		/* CSPR */
};

const struct rtos_register_stacking rtos_standard_Cortex_M3_stacking = {
	0x40,					/* stack_registers_size */
	-1,					/* stack_growth_direction */
	26,					/* num_output_registers */
	0,					/* stack_alignment */
	rtos_standard_Cortex_M3_stack_offsets	/* register_offsets */
};

const struct rtos_register_stacking rtos_standard_Cortex_M3_stacking_pad = {
	0x44,					/* stack_registers_size */
	-1,					/* stack_growth_direction */
	26,					/* num_output_registers */
	0,					/* stack_alignment */
	rtos_standard_Cortex_M3_stack_offsets	/* register_offsets */
};

const struct rtos_register_stacking rtos_standard_Cortex_M4F_stacking = {
	0x44,					/* stack_registers_size, ignore the additional 16 fpu registers */
	-1,					/* stack_growth_direction */
	26,					/* num_output_registers */
	0,					/* stack_alignment */
	rtos_standard_Cortex_M4F_stack_offsets	/* register_offsets */
};

const struct rtos_register_stacking rtos_standard_Cortex_M4F_stacking_pad = {
	0x48,					/* stack_registers_size, ignore the additional 16 fpu registers */
	-1,					/* stack_growth_direction */
	26,					/* num_output_registers */
	0,					/* stack_alignment */
	rtos_standard_Cortex_M4F_stack_offsets	/* register_offsets */
};

const struct rtos_register_stacking rtos_standard_Cortex_M4F_FPU_stacking = {
	0xcc,					/* stack_registers_size, ignore the additional 16 fpu registers */
	-1,					/* stack_growth_direction */
	26,					/* num_output_registers */
	0,					/* stack_alignment */
	rtos_standard_Cortex_M4F_FPU_stack_offsets	/* register_offsets */
};

const struct rtos_register_stacking rtos_standard_Cortex_M4F_FPU_stacking_pad = {
	0xd0,					/* stack_registers_size, ignore the additional 16 fpu registers */
	-1,					/* stack_growth_direction */
	26,					/* num_output_registers */
	0,					/* stack_alignment */
	rtos_standard_Cortex_M4F_FPU_stack_offsets	/* register_offsets */
};

const struct rtos_register_stacking rtos_standard_Cortex_R4_stacking = {
	0x48,					/* stack_registers_size */
	-1,					/* stack_growth_direction */
	26,					/* num_output_registers */
	0,					/* stack_alignment */
	rtos_standard_Cortex_R4_stack_offsets	/* register_offsets */
};
