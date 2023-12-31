/* SPDX-License-Identifier: GPL-2.0-only */

/* S1 support: bit 0, S2 Support: bit 1, etc. S0 & S5 assumed */
#if CONFIG(HAVE_ACPI_RESUME)
Name (SSFG, 0x0D)
#else
Name (SSFG, 0x09)
#endif

If (CONFIG(ACPI_S1_NOT_SUPPORTED)) {
	SSFG &= 0xfe
}

If (CONFIG(DISABLE_ACPI_HIBERNATE)) {
	SSFG &= 0xf7
}

External (\OSFG, IntObj)
If (CondRefOf(\OSFG)) {
	SSFG = \OSFG
}

/* Supported sleep states: */
Name(\_S0, Package () {0x00, 0x00, 0x00, 0x00} )	/* (S0) - working state */

If (SSFG & 0x01) {
	Name(\_S1, Package () {0x01, 0x00, 0x00, 0x00} )	/* (S1) - sleeping w/CPU context */
}
If (SSFG & 0x04) {
	Name(\_S3, Package () {0x05, 0x00, 0x00, 0x00} )	/* (S3) - Suspend to RAM */
}
If (SSFG & 0x08) {
	Name(\_S4, Package () {0x06, 0x04, 0x00, 0x00} )	/* (S4) - Suspend to Disk */
}

Name(\_S5, Package () {0x07, 0x00, 0x00, 0x00} )	/* (S5) - Soft Off */
