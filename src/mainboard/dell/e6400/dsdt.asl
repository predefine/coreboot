/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpi.h>
DefinitionBlock(
	"dsdt.aml",
	"DSDT",
	ACPI_DSDT_REV_2,
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x20090419	// OEM revision
)
{
	#include <acpi/dsdt_top.asl>

	#include <southbridge/intel/i82801ix/acpi/globalnvs.asl>
	#include <southbridge/intel/common/acpi/platform.asl>

	#include <cpu/intel/speedstep/acpi/cpu.asl>

	Scope (\_SB) {
		Device (PCI0) {
			#include <northbridge/intel/gm45/acpi/gm45.asl>
			#include <southbridge/intel/i82801ix/acpi/ich9.asl>

			#include <drivers/intel/gma/acpi/default_brightness_levels.asl>
		}
	}

	#include <southbridge/intel/common/acpi/sleepstates.asl>

}
