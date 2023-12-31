/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/pci_ops.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <drivers/lenovo/hybrid_graphics/hybrid_graphics.h>
#include <northbridge/intel/sandybridge/sandybridge.h>

static void hybrid_graphics_init(void)
{
	bool peg, igd;
	u32 reg32;

	early_hybrid_graphics(&igd, &peg);

	if (peg && igd)
		return;

	/* Hide disabled devices */
	reg32 = pci_read_config32(PCI_DEV(0, 0, 0), DEVEN);
	reg32 &= ~(DEVEN_PEG10 | DEVEN_IGD);

	if (peg)
		reg32 |= DEVEN_PEG10;

	if (igd)
		reg32 |= DEVEN_IGD;
	else
		/* Disable IGD VGA decode, no GTT or GFX stolen */
		pci_write_config16(PCI_DEV(0, 0, 0), GGC, 2);

	pci_write_config32(PCI_DEV(0, 0, 0), DEVEN, reg32);
}

// OC3 set in BIOS to port 2-7, OC7 set in BIOS to port 10-13
const struct southbridge_usb_port mainboard_usb_ports[] = {
	{ 1, 1,  0 }, /* P0: system port 4, OC0 */
	{ 1, 1,  1 }, /* P1: system port 2 (EHCI debug), OC 1 */
	{ 1, 1, -1 }, /* P2: HALF MINICARD (WLAN) no oc */
	{ 1, 0, -1 }, /* P3: WWAN, no OC */
	{ 1, 0, -1 }, /* P4: smartcard, no OC */
	{ 1, 1, -1 }, /* P5: ExpressCard, no OC */
	{ 0, 0, -1 }, /* P6: empty */
	{ 0, 0, -1 }, /* P7: empty */
	{ 1, 1,  4 }, /* P8: system port 3, OC4*/
	{ 1, 1,  5 }, /* P9: system port 1 (EHCI debug), OC 5 */
	{ 1, 0, -1 }, /* P10: fingerprint reader, no OC */
	{ 1, 0, -1 }, /* P11: bluetooth, no OC. */
	{ 1, 1, -1 }, /* P12: docking, no OC */
	{ 1, 1, -1 }, /* P13: camera (LCD), no OC */
};

void mainboard_early_init(int s3resume)
{
	hybrid_graphics_init();
}
