/*
 * Copyright (c) 2021 Graphene
 */

#include <kernel.h>
#include <taihen.h>
#include <string.h>

static tai_hook_ref_t hook_ref[1];
static SceUID hook_id[1];

#define DBGGXM_PRX_PATH "vs0:sys/external/libgxm_dbg_es4.suprx"

static int preload_module_patched(SceUID pid, const char *moduleFileName, int preloadFlags)
{
	int ret;
	if (strcmp(moduleFileName, "os0:us/libgxm_es4.suprx") == 0) {
		ret = TAI_CONTINUE(int, hook_ref[0], pid, DBGGXM_PRX_PATH, preloadFlags);
	}
	else
		ret = TAI_CONTINUE(int, hook_ref[0], pid, moduleFileName, preloadFlags);

	return ret;
}

int module_start(SceSize argc, const void *args)
{
	tai_module_info_t info;
	info.size = sizeof(tai_module_info_t);
	taiGetModuleInfoForKernel(KERNEL_PID, "SceKernelModulemgr", &info);

	SceUID fd = sceIoOpen(DBGGXM_PRX_PATH, SCE_O_RDONLY, 0);
	if (fd > 0) {
		sceIoClose(fd);

		hook_id[0] = taiHookFunctionOffsetForKernel(
			KERNEL_PID,
			&hook_ref[0],
			info.modid,
			0,
			0x266C,
			1,
			preload_module_patched);
	}

	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{
	return SCE_KERNEL_STOP_SUCCESS;
}
