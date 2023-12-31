/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef PARROT_EC_H
#define PARROT_EC_H

#define EC_SCI_GPI      7   /* GPIO7 is EC_SCI# */
#define EC_SMI_GPI      8   /* GPIO8 is EC_SMI# */
#define EC_LID_GPI     15   /* GPIO15 is EC_LID_OUT# */

/* EC SMI sources TODO - make defines
 * No event  80h
*/
#define EC_NO_EVENT 0x80
/*
 * DTS temperature update  A0h
 * Decrease brightness event  A1h
 * Increase brightness event  A2h
 * Lid open  A5h
 * Lid closed  A6h
 */
#define EC_LID_CLOSE 0xA6
 /* Bluetooth wake up event  A9h
 * Display change (LCD , CRT)  ACh
 * Cpu fast event  ADh
 * Cpu slow event  ADh
 * Battery life in critical low state (LLB) B2h
 */
#define EC_BATTERY_CRITICAL 0xB2
/*
 * Battery life in low power state (LB) B3h
 * Battery Plug-In  B5h
 * Docked in request  BAh
 * Undock request  BBh
 * Power button pressed  C2h
 * AC power plug-in  C7h
 * AC power plug-out  C8h
 * Modem Ring In  CAh
 * PME signal active  CEh
 * Acer Hotkey Function - Make event D5h
 * Acer Hotkey Function - Break event D6h
 */

#ifndef __ACPI__
void parrot_ec_init(void);
u8 parrot_rev(void);
#endif

#endif // PARROT_EC_H
