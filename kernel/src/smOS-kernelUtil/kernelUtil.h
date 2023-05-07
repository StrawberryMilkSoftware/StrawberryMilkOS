#pragma once

#include <stddef.h>
#include "../rendering/BasicRenderer.h"
#include "../numbers/cstr.h"
#include "../memory/efiMemory.h"
#include "../memory/memory.h"
#include "../bitmap/bitmap.h"
#include "../paging/pageFrameAllocator.h"
#include "../paging/pageMapIndexer.h"
#include "../paging/paging.h"
#include "../paging/PageTableManager.h"
#include "../userinput/mouse/mouse.h"
#include "../acpi/acpi.h"
#include "../acpi/pci/pci.h"

struct BootInfo{
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
	ACPI::RSDP2* rsdp;
};

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo {
    PageTableManager* pageTableManager;
};

KernelInfo InitKernel(BootInfo* bootInfo);