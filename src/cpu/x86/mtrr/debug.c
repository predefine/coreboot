/* SPDX-License-Identifier: GPL-2.0-only */

#include <console/console.h>
#include <cpu/cpu.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/mtrr.h>
#include <stdint.h>

static const char *display_mtrr_type(uint32_t type)
{
	switch (type) {
	default: return "reserved";
	case 0: return "UC";
	case 1: return "WC";
	case 4: return "WT";
	case 5: return "WP";
	case 6: return "WB";
	case 7: return "UC-";
	}
}

static void display_mtrr_fixed_types(msr_t msr_data,
	uint32_t starting_address, uint32_t memory_size)
{
	uint32_t base_address;
	uint32_t index;
	uint32_t next_address;
	uint32_t next_type;
	uint32_t type;

	type = msr_data.raw & MTRR_DEF_TYPE_MASK;
	base_address = starting_address;
	next_address = base_address;
	for (index = 0; index < 64; index += 8) {
		next_address = starting_address + (memory_size *
			((index >> 3) + 1));
		next_type = (msr_data.raw >> index) & MTRR_DEF_TYPE_MASK;
		if (next_type != type) {
			printk(BIOS_DEBUG, "    0x%08x - 0x%08x: %s\n",
				base_address, next_address - 1,
				display_mtrr_type(type));
			base_address = next_address;
			type = next_type;
		}
	}
	if (base_address != next_address)
		printk(BIOS_DEBUG, "    0x%08x - 0x%08x: %s\n",
			base_address, next_address - 1,
			display_mtrr_type(type));
}

static void display_4k_mtrr(uint32_t msr_reg, uint32_t starting_address,
	const char *name)
{
	const msr_t msr = rdmsr(msr_reg);
	printk(BIOS_DEBUG, "0x%016llx: %s\n", msr.raw, name);
	display_mtrr_fixed_types(msr, starting_address, 0x1000);
}

static void display_16k_mtrr(uint32_t msr_reg, uint32_t starting_address,
	const char *name)
{
	const msr_t msr = rdmsr(msr_reg);
	printk(BIOS_DEBUG, "0x%016llx: %s\n", msr.raw, name);
	display_mtrr_fixed_types(msr, starting_address, 0x4000);
}

static void display_64k_mtrr(void)
{
	const msr_t msr = rdmsr(MTRR_FIX_64K_00000);
	printk(BIOS_DEBUG, "0x%016llx: IA32_MTRR_FIX64K_00000\n", msr.raw);
	display_mtrr_fixed_types(msr, 0, 0x10000);
}

static void display_mtrrcap(void)
{
	const msr_t msr = rdmsr(MTRR_CAP_MSR);
	printk(BIOS_DEBUG,
		"0x%08x%08x: IA32_MTRRCAP: %s%s%s%s%u variable MTRRs\n",
		msr.hi, msr.lo,
		(msr.lo & MTRR_CAP_PRMRR) ? "PRMRR, " : "",
		(msr.lo & MTRR_CAP_SMRR) ? "SMRR, " : "",
		(msr.lo & MTRR_CAP_WC) ? "WC, " : "",
		(msr.lo & MTRR_CAP_FIX) ? "FIX, " : "",
		msr.lo & MTRR_CAP_VCNT);
}

static void display_mtrr_def_type(void)
{
	const msr_t msr = rdmsr(MTRR_DEF_TYPE_MSR);
	printk(BIOS_DEBUG, "0x%016llx: IA32_MTRR_DEF_TYPE:%s%s %s\n",
		msr.raw,
		(msr.raw & MTRR_DEF_TYPE_EN) ? " E," : "",
		(msr.raw & MTRR_DEF_TYPE_FIX_EN) ? " FE," : "",
		display_mtrr_type((uint32_t)(msr.raw &
			MTRR_DEF_TYPE_MASK)));
}

static void display_variable_mtrr(int index, uint64_t address_mask)
{
	uint64_t base_address;
	uint64_t length;
	uint64_t mask;
	const msr_t msr_base = rdmsr(MTRR_PHYS_BASE(index));
	const msr_t msr_mask = rdmsr(MTRR_PHYS_MASK(index));

	if (msr_mask.raw & MTRR_PHYS_MASK_VALID) {
		base_address = (msr_base.raw & 0xfffffffffffff000ULL)
			& address_mask;
		printk(BIOS_DEBUG,
			"0x%016llx: PHYBASE%d: Address = 0x%016llx, %s\n",
			msr_base.raw, index, base_address,
			display_mtrr_type(msr_base.raw & MTRR_DEF_TYPE_MASK));
		mask = (msr_mask.raw & 0xfffffffffffff000ULL) & address_mask;
		length = (~mask & address_mask) + 1;
		printk(BIOS_DEBUG,
			"0x%016llx: PHYMASK%d: Length  = 0x%016llx, Valid\n",
			msr_mask.raw, index, length);
	} else {
		printk(BIOS_DEBUG, "0x%016llx: PHYBASE%d\n", msr_base.raw, index);
		printk(BIOS_DEBUG, "0x%016llx: PHYMASK%d: Disabled\n",
			msr_mask.raw, index);
	}
}

static void _display_mtrrs(void)
{
	uint32_t address_bits;
	uint64_t address_mask;
	int i;
	int variable_mtrrs;

	/* Display the fixed MTRRs */
	display_mtrrcap();
	display_mtrr_def_type();
	display_64k_mtrr();
	display_16k_mtrr(MTRR_FIX_16K_80000, 0x80000, "IA32_MTRR_FIX16K_80000");
	display_16k_mtrr(MTRR_FIX_16K_A0000, 0xa0000, "IA32_MTRR_FIX16K_A0000");
	display_4k_mtrr(MTRR_FIX_4K_C0000, 0xc0000, "IA32_MTRR_FIX4K_C0000");
	display_4k_mtrr(MTRR_FIX_4K_C8000, 0xc8000, "IA32_MTRR_FIX4K_C8000");
	display_4k_mtrr(MTRR_FIX_4K_D0000, 0xd0000, "IA32_MTRR_FIX4K_D0000");
	display_4k_mtrr(MTRR_FIX_4K_D8000, 0xd8000, "IA32_MTRR_FIX4K_D8000");
	display_4k_mtrr(MTRR_FIX_4K_E0000, 0xe0000, "IA32_MTRR_FIX4K_E0000");
	display_4k_mtrr(MTRR_FIX_4K_E8000, 0xe8000, "IA32_MTRR_FIX4K_E8000");
	display_4k_mtrr(MTRR_FIX_4K_F0000, 0xf0000, "IA32_MTRR_FIX4K_F0000");
	display_4k_mtrr(MTRR_FIX_4K_F8000, 0xf8000, "IA32_MTRR_FIX4K_F8000");
	address_bits = cpu_phys_address_size();
	address_mask = (1ULL << address_bits) - 1;

	/* Display the variable MTRRs */
	variable_mtrrs = get_var_mtrr_count();
	for (i = 0; i < variable_mtrrs; i++)
		display_variable_mtrr(i, address_mask);
}

asmlinkage void display_mtrrs(void)
{
	if (CONFIG(DISPLAY_MTRRS))
		_display_mtrrs();
}
