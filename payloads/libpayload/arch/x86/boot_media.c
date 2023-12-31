/* SPDX-License-Identifier: BSD-3-Clause */

#include <libpayload.h>
#include <boot_device.h>

__attribute__((weak)) ssize_t boot_device_read(void *buf, size_t offset, size_t size)
{
	/* Memory-mapping usually only works for the top 16MB. */
	if (!lib_sysinfo.boot_media_size || lib_sysinfo.boot_media_size - offset > 16 * MiB)
		return CB_ERR_ARG;
	const void *const ptr = phys_to_virt(0 - lib_sysinfo.boot_media_size + offset);
	memcpy(buf, ptr, size);
	return size;
}
