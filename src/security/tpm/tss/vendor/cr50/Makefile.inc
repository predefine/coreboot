## SPDX-License-Identifier: GPL-2.0-only

ramstage-y += cr50.c
romstage-y += cr50.c
postcar-y += cr50.c

verstage-$(CONFIG_VBOOT) += cr50.c
