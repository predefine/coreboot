# SPDX-License-Identifier: GPL-2.0-or-later

bootblock-y += bootblock.c

romstage-y += chromeos.c
romstage-y += sku_id.c
romstage-y += romstage.c

ramstage-y += chromeos.c
ramstage-y += ec.c
ramstage-y += sku_id.c

verstage-y += chromeos.c
verstage-y += verstage.c

BASEBOARD_DIR:=$(call strip_quotes,$(CONFIG_BASEBOARD_DIR))

subdirs-y += variants/baseboard/$(BASEBOARD_DIR)
subdirs-y += variants/baseboard
subdirs-y += variants/$(VARIANT_DIR)/spd
subdirs-y += spd

CPPFLAGS_common += -I$(src)/mainboard/$(MAINBOARDDIR)/variants/baseboard/include
CPPFLAGS_common += -I$(src)/mainboard/$(MAINBOARDDIR)/variants/baseboard/include/baseboard/acpi

subdirs-y += variants/$(VARIANT_DIR)
CPPFLAGS_common += -I$(src)/mainboard/$(MAINBOARDDIR)/variants/$(VARIANT_DIR)/include
