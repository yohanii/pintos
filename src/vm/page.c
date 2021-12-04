#include "vm/page.h"
#include "vm/frame.h"


static unsigned vm_hash_func (const struct hash_elem *e, void *aux UNUSED);
static bool vm_less_func (const struct hash_elem *a, const struct hash_elem *b, void *aux UNUSED);

void vm_init(struct hash *vm){

    ASSERT (vm != NULL);
    hash_init (vm, vm_hash_func, vm_less_func, NULL);
}

static unsigned
vm_hash_func (const struct hash_elem *e, void *aux UNUSED)
{
  ASSERT (e != NULL);
  return hash_int (hash_entry (e, struct vm_entry, elem)->vaddr);
}

static bool
vm_less_func (const struct hash_elem *a, const struct hash_elem *b, void *aux UNUSED)
{
  ASSERT (a != NULL);
  ASSERT (b != NULL);
  struct vm_entry *p_a = hash_entry (a, struct vm_entry, elem);
  struct vm_entry *p_b = hash_entry (b, struct vm_entry, elem);
  return p_a->vaddr < p_b->vaddr;
}

bool insert_vme(struct hash *vm, struct vm_entry*vme)
{
  ASSERT (vm != NULL);
  ASSERT (vme != NULL);
  if(!hash_insert (vm, &vme->elem)){
    return true;
  }else{
    return false;
  }
}

bool delete_vme(struct hash *vm, struct vm_entry*vme)
{
  ASSERT (vm != NULL);
  ASSERT (vme != NULL);
  if(hash_delete (vm, &vme->elem)){
    return true;
  }else{
    return false;
  }
}

struct vm_entry *find_vme(void*vaddr){
  /* pg_round_down()으로vaddr의페이지번호를얻음*/
  /* hash_find() 함수를사용해서hash_elem구조체얻음*/
  /* 만약존재하지않는다면NULL리턴*/
  /* hash_entry()로해당hash_elem의vm_entry구조체리턴*/
  struct hash *vm;
  struct vm_entry vme;
  struct hash_elem *elem;

  vm = &thread_current()->vm;
  vme.vaddr = pg_round_down(vaddr);
  if(!(elem = hash_find (vm, &vme.elem)))
  {
    return NULL;
  }

  return hash_entry(elem, struct vm_entry, elem);
}


void vm_destroy(struct hash *vm)
{
  /* hash_destroy()으로해시테이블의버킷리스트와vm_entry들을제거*/
  ASSERT (vm != NULL);
  hash_destroy (vm, vm_destroy_func);
}


void vm_destroy_func(struct hash_elem *e, void*aux UNUSED)
{
  /* Get hash element (hash_entry() 사용) */
  /* load가되어있는page의vm_entry인경우
  page의할당해제및page mapping 해제(palloc_free_page()와pagedir_clear_page() 사용) */
  /* vm_entry객체할당해제*/
  struct vm_entry *vme = hash_entry(e, struct vm_entry, elem);
  struct page *page = get_page_by_kaddr (pagedir_get_page (thread_current()->pagedir, vme->vaddr));
  if(page){
    pagedir_clear_page (page->pg_thread->pagedir, page->vme->vaddr);
    palloc_free_page(page->kaddr);
    free (vme);
  }
  
}

struct page *
get_page_by_kaddr(void *kaddr)
{
  struct list_elem *elem;
  for (elem = list_begin (&lru_list); elem != list_end (&lru_list); elem = list_next (elem)) {
    struct page *pg = list_entry (elem, struct page, lru);
    if (pg->kaddr == kaddr)
      return pg;
  }
  return NULL;
}


bool load_file(void *kaddr, struct vm_entry *vme)
{
	bool success = false;   
  int return_value = file_read_at(vme->file, kaddr, vme->read_bytes, vme->offset);
	if((int)vme->read_bytes == return_value)
	{
		success = true;
		memset(kaddr + vme->read_bytes, 0, vme->zero_bytes);
	} 
	return success;
}
