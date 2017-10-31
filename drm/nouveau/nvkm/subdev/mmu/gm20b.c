/*
 * Copyright 2017 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#include "vmm.h"

#include <subdev/fb.h>

#include <nvif/class.h>

static const struct nvkm_mmu_func
gm20b_mmu = {
	.limit = (1ULL << 40),
	.dma_bits = 40,
	.lpg_shift = 17,
	.vmm = {{ -1,  0, NVIF_CLASS_VMM_GM200}, gm20b_vmm_new },
	.kind = gm200_mmu_kind,
};

static const struct nvkm_mmu_func
gm20b_mmu_fixed = {
	.limit = (1ULL << 40),
	.dma_bits = 40,
	.lpg_shift = 17,
	.vmm = {{ -1, -1, NVIF_CLASS_VMM_GM200}, gm20b_vmm_new_fixed },
	.kind = gm200_mmu_kind,
};

int
gm20b_mmu_new(struct nvkm_device *device, int index, struct nvkm_mmu **pmmu)
{
	if (device->fb->page)
		return nvkm_mmu_new_(&gm20b_mmu_fixed, device, index, pmmu);
	return nvkm_mmu_new_(&gm20b_mmu, device, index, pmmu);
}
