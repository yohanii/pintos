#ifndef VM_PAGE_H
#define VM_PAGE_H

struct page{
	void *kaddr;
	struct vm_entry *vme;
	struct thread *pg_thread;
	struct list_elem lru;
};

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
}

#endif