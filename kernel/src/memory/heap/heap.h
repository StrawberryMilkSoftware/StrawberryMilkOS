#pragma once
#include <stdint.h>
#include <stddef.h>

struct HeapSegHdr {
    size_t length;
    HeapSegHdr* next;
    HeapSegHdr* last;
    bool free;
    void CombineForward();
    void CombineBackward();
    HeapSegHdr* Split(size_t splitLength);
};

void InitHeap(void* heapAddr, size_t pageCount);

void* malloc(size_t size);
void free(void* addr);

void ExpandHeap(size_t length);

inline void* operator new(size_t size) {return malloc(size);}
inline void* operator new[](size_t size) {return malloc(size);}

inline void operator delete(void* p) {free(p);}