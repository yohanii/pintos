#include <vm/frame.h>

struct list frame_table;
struct list lru_list;


   
static struct frame * get_frame (void) {



}
static struct frame *evict_frame (void) {



}
bool claim_page (void *va ){//UNUSED) {




}

void free_page(void *kaddr)
{

}

void __free_page(struct page *page)
{
}