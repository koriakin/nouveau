#ifndef __NV50_GR_H__
#define __NV50_GR_H__
struct nvkm_device;

int  nv50_grctx_init(struct nouveau_device *, u32 *size);
void nv50_grctx_fill(struct nouveau_device *, struct nouveau_gpuobj *);
#endif