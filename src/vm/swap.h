#ifndef VM_SWAP_H
#define VM_SWAP_H



void swap_init(size_t used_size, void *kaddr);
void swap_in(size_t used_index, void* kaddr);
size_t swap_out(void* kaddr);
#endif