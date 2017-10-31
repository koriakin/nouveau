#ifndef __NVKM_MMU_PRIV_H__
#define __NVKM_MMU_PRIV_H__
#define nvkm_mmu(p) container_of((p), struct nvkm_mmu, subdev)
#include <subdev/mmu.h>

void nvkm_mmu_ctor(const struct nvkm_mmu_func *, struct nvkm_device *,
		   int index, struct nvkm_mmu *);
int nvkm_mmu_new_(const struct nvkm_mmu_func *, struct nvkm_device *,
		  int index, struct nvkm_mmu **);

struct nvkm_mmu_func {
	void *(*dtor)(struct nvkm_mmu *);
	int (*oneinit)(struct nvkm_mmu *);
	void (*init)(struct nvkm_mmu *);

	u64 limit;
	u8  dma_bits;
	u32 pgt_bits;
	u8  spg_shift;
	u8  lpg_shift;

	int  (*create)(struct nvkm_mmu *, u64 offset, u64 length, u64 mm_offset,
		       struct lock_class_key *, struct nvkm_vm **);

	void (*map_pgt)(struct nvkm_gpuobj *pgd, u32 pde,
			struct nvkm_memory *pgt[2]);
	void (*map)(struct nvkm_vma *, struct nvkm_memory *,
		    struct nvkm_mem *, u32 pte, u32 cnt,
		    u64 phys, u64 delta);
	void (*map_sg)(struct nvkm_vma *, struct nvkm_memory *,
		       struct nvkm_mem *, u32 pte, u32 cnt, dma_addr_t *);
	void (*unmap)(struct nvkm_vma *, struct nvkm_memory *pgt,
		      u32 pte, u32 cnt);
	void (*flush)(struct nvkm_vm *);

	struct {
		struct nvkm_sclass user;
		int (*ctor)(struct nvkm_mmu *, u64 addr, u64 size,
			    void *argv, u32 argc, struct lock_class_key *,
			    const char *name, struct nvkm_vmm **);
		bool global;
	} vmm;
};

int nvkm_vm_create(struct nvkm_mmu *, u64, u64, u64, u32,
		   struct lock_class_key *, struct nvkm_vm **);

extern const struct nvkm_mmu_func nv04_mmu;

int nv50_vm_create(struct nvkm_mmu *, u64, u64, u64, struct lock_class_key *,
		   struct nvkm_vm **);
void nv50_vm_map_pgt(struct nvkm_gpuobj *, u32, struct nvkm_memory **);
void nv50_vm_map(struct nvkm_vma *, struct nvkm_memory *, struct nvkm_mem *,
		 u32, u32, u64, u64);
void nv50_vm_map_sg(struct nvkm_vma *, struct nvkm_memory *, struct nvkm_mem *,
		    u32, u32, dma_addr_t *);
void nv50_vm_unmap(struct nvkm_vma *, struct nvkm_memory *, u32, u32);
void nv50_vm_flush(struct nvkm_vm *);

int gf100_vm_create(struct nvkm_mmu *, u64, u64, u64, struct lock_class_key *,
		    struct nvkm_vm **);
void gf100_vm_map_pgt(struct nvkm_gpuobj *, u32, struct nvkm_memory **);
void gf100_vm_map(struct nvkm_vma *, struct nvkm_memory *, struct nvkm_mem *,
		  u32, u32, u64, u64);
void gf100_vm_map_sg(struct nvkm_vma *, struct nvkm_memory *, struct nvkm_mem *,
		     u32, u32, dma_addr_t *);
void gf100_vm_unmap(struct nvkm_vma *, struct nvkm_memory *, u32, u32);
void gf100_vm_flush(struct nvkm_vm *);

struct nvkm_mmu_pt {
	union {
		struct nvkm_mmu_ptc *ptc;
		struct nvkm_mmu_ptp *ptp;
	};
	struct nvkm_memory *memory;
	bool sub;
	u16 base;
	u64 addr;
	struct list_head head;
};

void nvkm_mmu_ptc_dump(struct nvkm_mmu *);
struct nvkm_mmu_pt *
nvkm_mmu_ptc_get(struct nvkm_mmu *, u32 size, u32 align, bool zero);
void nvkm_mmu_ptc_put(struct nvkm_mmu *, bool force, struct nvkm_mmu_pt **);
#endif
