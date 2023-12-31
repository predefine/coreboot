## SPDX-License-Identifier: GPL-2.0-only
ifeq ($(CONFIG_SOC_AMD_COMMON_BLOCK_BANKED_GPIOS),y)

all-y += gpio.c
smm-y += gpio.c

romstage-$(CONFIG_TPM_GOOGLE) += tpm_tis.c
ramstage-$(CONFIG_TPM_GOOGLE) += tpm_tis.c
verstage-$(CONFIG_TPM_GOOGLE) += tpm_tis.c

endif # CONFIG_SOC_AMD_COMMON_BLOCK_BANKED_GPIOS
