/* SPDX-License-Identifier: GPL-2.0-only */

#include <soc/iomap.h>

#define MAILBOX_DATA 0x7080
#define MAILBOX_INTF 0x7084
#define PMIO_LENGTH 0x80
#define PMIO_LIMIT 0x480

scope (\_SB) {
	Device (IPC1)
	{
		Name (_HID, "INT34D2")
		Name (_CID, "INT34D2")
		Name (_DDN, "Intel(R) IPC1 Controller")
		Name (RBUF, ResourceTemplate ()
		{
			Memory32Fixed (ReadWrite, 0x0, 0x2000, IBAR)
			Memory32Fixed (ReadWrite, 0x0, 0x4, MDAT)
			Memory32Fixed (ReadWrite, 0x0, 0x4, MINF)
			IO (Decode16, ACPI_BASE_ADDRESS, PMIO_LIMIT,
			      0x04, PMIO_LENGTH)
			Memory32Fixed (ReadWrite, 0x0, 0x2000, SBAR)
			Interrupt (ResourceConsumer, Level, ActiveLow, Exclusive, , , )
			{
			      PMC_INT
			}
		})

		Method (_CRS, 0x0, NotSerialized)
		{
			CreateDwordField (^RBUF, ^IBAR._BAS, IBAS)
			IBAS = PCH_PWRM_BASE_ADDRESS

			CreateDwordField (^RBUF, ^MDAT._BAS, MDBA)
			MDBA = MCH_BASE_ADDRESS + MAILBOX_DATA
			CreateDwordField (^RBUF, ^MINF._BAS, MIBA)
			MIBA = MCH_BASE_ADDRESS + MAILBOX_INTF

			CreateDwordField (^RBUF, ^SBAR._BAS, SBAS)
			SBAS = SRAM_BASE_0

			Return (^RBUF)
		}
		Method (_STA, 0x0, NotSerialized)
		{
			Return(0xb)
		}
	}
}
