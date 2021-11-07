#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#define HIGH_ADDR 0xc0000000
#define LOW_ADDR 0x8048000
static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{
  int syscall_num;
  int arg[5];
  void *esp = f->esp;


  if(esp >= LOW_ADDR && esp < HIGH_ADDR){
    syscall_num = *(int *)esp;
	}
	else{
		exit(-1);
	}


  switch (syscall_num) {
    case SYS_HALT:
      break;
    case SYS_EXIT:
		  get_argument(esp,arg,1);
		  exit(arg[0]);
      break;
    case SYS_EXEC:
      break;
    case SYS_WAIT:
      break;
    case SYS_CREATE:
      break;
    case SYS_REMOVE:
      break;
    case SYS_OPEN:
      break;
    case SYS_FILESIZE:
      break;
    case SYS_READ:
      break;
    case SYS_WRITE:
      write((int)*(uint32_t*)(f->esp+20), (void*)*(uint32_t*)(f->esp+24), (unsigned)*((uint32_t*)(f->esp+28)));
      break;
    case SYS_SEEK:
      break;
    case SYS_TELL:
      break;
    case SYS_CLOSE:
      break;

  }   


  //thread_exit ();
}

/* get_argument function */
void
get_argument(void *esp, int *arg, int count)
{
	void *sp = esp + 4;
	if(count <= 0){
    return;
  }
	for(int i=0; i<count; i++){
	  if(sp >= LOW_ADDR && sp <= HIGH_ADDR){
			arg[i] = *(int *)sp;
			sp = sp + 4;
	  }
	  else{
		  exit(-1);
	  }
	}

}

void exit(int status){

  printf("%s: exit(%d)\n", thread_name(), status);
  thread_exit();
}

int write(int fd, const void *buffer, unsigned size){
  if(fd==1){
    putbuf(buffer, size);
    return size;
  }
  return -1;
} 

void halt(void){
  shutdown_power_off();
}

pid_t exec(const char *cmd_lime){

}
int wait(pid_t pid){

}
bool create(const char *file, unsigned initial_size){

}
bool remove(const char *file){

}
int open(const char *file){

}
int filesize(int fd){

}
int read(int fd, void *buffer, unsigned size){

}

void seek(int fd, unsigned position){

}
unsigned tell(int fd){

}
void close(int fd){
  
}