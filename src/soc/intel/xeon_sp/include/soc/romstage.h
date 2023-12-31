/* SPDX-License-Identifier: GPL-2.0-or-later */

#ifndef _SOC_ROMSTAGE_H_
#define _SOC_ROMSTAGE_H_

#include <fsp/api.h>

/* These functions are weak and can be overridden by a mainboard functions. */
void mainboard_memory_init_params(FSPM_UPD * mupd);
void mainboard_rtc_failed(void);
void save_dimm_info(void);
void mainboard_ewl_check(void);
void mainboard_fsp_error_handle(void);

#endif /* _SOC_ROMSTAGE_H_ */
