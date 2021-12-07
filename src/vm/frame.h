#ifndef VM_FRAME_H
#define VM_FRAME_H
#include <vm/page.h>
#include <stdbool.h>

struct list lru_list;

struct frame {
    void *kva;
    struct page *page;
    //struct list_elem frame_elem;
};

static struct frame * get_frame (void);
static struct frame *evict_frame (void);
bool claim_page (void *va );//UNUSED);
void free_page(void *kaddr);
void __free_page(struct page *page);
void add_page_to_lru_list(struct page *page);
void del_page_from_lru_list(struct page *page);
struct list_elem* get_next_lru_clock(void);

#endif