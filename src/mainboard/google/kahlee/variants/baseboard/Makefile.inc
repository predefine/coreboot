# SPDX-License-Identifier: GPL-2.0-only

bootblock-y += gpio.c
bootblock-y += OemCustomize.c

romstage-y += OemCustomize.c
romstage-y += gpio.c
romstage-y += memory.c

ramstage-y += gpio.c
ramstage-y += mainboard.c

# Add OEM ID table
ifeq ($(CONFIG_USE_OEM_BIN),y)
cbfs-files-y += oem.bin
oem.bin-file := $(call strip_quotes,$(CONFIG_OEM_BIN_FILE))
oem.bin-type := raw
endif #($(CONFIG_USE_OEM_BIN),y)
