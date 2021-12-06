#include "vm/frame.h"
#include "vm/page.h"
#include "vm/swap.h"

#include "threads/synch.h"
#include "devices/block.h"
#include "threads/vaddr.h"
#include "lib/kernel/bitmap.h"

struct lock swap_lock;
struct bitmap *swap_bitmap;

void swap_init(size_t used_size, void *kaddr){
    lock_init (&swap_lock);
    swap_bitmap = bitmap_create(used_size);
	bitmap_set_all(swap_bitmap, 0);
}
void swap_in(size_t used_index, void* kaddr){
	int i;
	lock_acquire(&swap_lock);
    struct block *swap_block = block_get_role (BLOCK_SWAP);
	for(i = 0; i < 8; i++){
		block_read(swap_block, i + 8 * used_index, kaddr + i * BLOCK_SECTOR_SIZE);
	}

    bitmap_set(swap_bitmap, used_index, 1);
	lock_release(&swap_lock);
}
size_t swap_out(void* kaddr){
	int i;
	lock_acquire(&swap_lock);
    struct block *swap_block = block_get_role (BLOCK_SWAP);
    size_t swap_index = bitmap_scan_and_flip (swap_bitmap, 0, 1, 0);
    if(swap_index == BITMAP_ERROR)
        return swap_index;
	for(i = 0; i < 8; i++){
		block_write(swap_block, i + 8 * swap_index, kaddr + i * BLOCK_SECTOR_SIZE);
	}
    bitmap_set(swap_bitmap, swap_index, 1);
	lock_release(&swap_lock);
}