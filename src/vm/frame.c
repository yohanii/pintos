#include <vm/frame.h>

struct list frame_table;
struct list lru_list;
struct list_elem *lru_clock;

void
lru_list_init (void)
{
  list_init (&lru_list);
  list_init (&frame_table);
  lru_clock = NULL;
}
   
static struct frame * get_frame (void) {
/*palloc_get_page()에 PAL_USER을 넣어서 사용*/
   /*user pool로부터 페이지를 못 받았을 경우, 메모리 공간을 얻기 위해 할당되어 있는
frame 제거*/
/*list_push_back을 이용하여 frame_table에 element 넣어주기*/
}
static struct frame *evict_frame (void) {
/* for문을 이용해 frame_table을 돌면서 해당하는 frame 제거 */
}
bool claim_page (void *va ){
/*user page가 이미 mapping 되었거나 메모리 할당 실패시 false return*/
}

void free_page(void *kaddr)
{

}

void __free_page(struct page *page)
{

}


void add_page_to_lru_list(struct page *page){
  list_push_back (&lru_list, &page->lru);
}

void del_page_from_lru_list(struct page *page){

  if (lru_clock == &page->lru)
      lru_clock = list_remove (lru_clock);
  else
      list_remove (&page->lru);
}
struct list_elem* get_next_lru_clock(void){

   if(lru_clock == NULL){
      if(!list_empty(&lru_list)){
         lru_clock = list_begin (&lru_list);
         return lru_clock;
      }
      else return NULL;
   }
   if(lru_clock == list_end(&lru_list)){
      if(!list_empty(&lru_list)){
         lru_clock = list_begin(&lru_list);
         return lru_clock;
      }
      else return NULL;
   }

  lru_clock = list_next (lru_clock);
  if (lru_clock == list_end (&lru_list)){
		if(lru_clock == list_begin(&lru_list)){
			return NULL;
		}
		else
			lru_clock = list_begin(&lru_list);
  }
  return lru_clock;
}