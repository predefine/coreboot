/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <baseboard/variants.h>
#include <soc/platform_descriptors.h>

void mb_pre_fspm(FSP_M_CONFIG *mcfg)
{
	size_t num_base_gpios;
	const struct soc_amd_gpio *base_gpios;

	baseboard_romstage_gpio_table(&base_gpios, &num_base_gpios);
	gpio_configure_pads(base_gpios, num_base_gpios);
}
