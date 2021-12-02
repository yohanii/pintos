#ifndef VM_PAGE_H
#define VM_PAGE_H
#define VM_BIN 0
#define VM_FILE 1
#define VM_ANON 2

#include "threads/vaddr.h"
#include "threads/thread.h"
#include "threads/malloc.h"
#include "vm/frame.h"
#include "userprog/pagedir.h"
#include "filesys/file.h"
#include "threads/interrupt.h"
#include <string.h>
#include <hash.h>
#include <list.h>
#include <stdio.h>


struct vm_entry{
   uint8_t type;
   void *vaddr;
   bool writable;
   
   bool is_loaded;
   struct file* file;
   
   size_t offset;
   size_t read_bytes;
   size_t zero_bytes;
   
   
   struct hash_elem elem;
};

struct page{
	void *kaddr;
	struct vm_entry *vme;
	struct thread *pg_thread;
	struct list_elem lru;
};

void vm_init(struct hash *vm);
bool insert_vme(struct hash *vm, struct vm_entry*vme);
bool delete_vme(struct hash *vm, struct vm_entry*vme);
struct vm_entry *find_vme(void*vaddr);
void vm_destroy(struct hash *vm);
void vm_destroy_func(struct hash_elem *e, void*aux UNUSED);
struct page *get_page_by_kaddr(void *kaddr);
 
#endif