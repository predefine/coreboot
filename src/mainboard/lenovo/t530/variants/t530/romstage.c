/* SPDX-License-Identifier: GPL-2.0-only */

#include <southbridge/intel/bd82x6x/pch.h>

const struct southbridge_usb_port mainboard_usb_ports[] = {
	{ 1, 1,  0 }, /* P0: USB double port upper, USB3, OC 0 */
	{ 1, 1,  1 }, /* P1: USB double port lower, USB3, (EHCI debug) OC 1 */
	{ 1, 2,  3 }, /* P2: Dock, USB3, OC 3 */
	{ 1, 1, -1 }, /* P3: WWAN slot, no OC */
	{ 1, 1,  2 }, /* P4: yellow USB, OC 2 */
	{ 1, 0, -1 }, /* P5: ExpressCard slot, no OC */
	{ 0, 0, -1 }, /* P6: empty */
	{ 1, 2, -1 }, /* P7: docking, no OC */
	{ 1, 0, -1 }, /* P8: smart card reader, no OC */
	{ 1, 1,  5 }, /* P9: USB port single (EHCI debug), OC 5 */
	{ 1, 0, -1 }, /* P10: fingerprint reader, no OC */
	{ 1, 0, -1 }, /* P11: bluetooth, no OC. */
	{ 1, 3, -1 }, /* P12: wlan, no OC - disabled in vendor bios*/
	{ 1, 1, -1 }, /* P13: camera, no OC */
};
