#include "vm/page.h"

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
