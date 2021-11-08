#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "filesys/fsutil.h"
#include "devices/shutdown.h"
#include "process.h"



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
  int syscall;
  int arg[5];
  void *esp = f->esp;

  if(esp>LOW_ADDR && esp < HIGH_ADDR){
    syscall = *(uint32_t *)esp;
  }else{
    exit(-1);
  }

  switch (syscall) {
    case SYS_HALT:
      halt();
      break;
    case SYS_EXIT:
      get_argument(esp, arg, 1, 0);
      exit((int)arg[0]);
      break;
    case SYS_EXEC:
      get_argument(esp, arg, 1, 0);
      f->eax = exec((const char *)arg[0]);
      break;
    case SYS_WAIT:
      get_argument(esp, arg, 1, 0);
      f->eax = wait((pid_t)arg[0]);
      break;
    case SYS_CREATE:
    	get_argument(esp, arg, 2, 0);
      if (arg[0] == NULL){
        exit(-1);
      }
		  f->eax = create((const char *)arg[0],(unsigned)arg[1]);
      break;
    case SYS_REMOVE:
    	get_argument(esp, arg, 1, 0);
      if(arg[0] == NULL){
        exit(-1);
      }
		  f->eax = remove((const char *)arg[0]);
      break;
    case SYS_OPEN:
    	get_argument(esp, arg, 1, 0);
      if(arg[0] == NULL){
        exit(-1);
      }
		  f->eax = open((const char *)arg[0]);
      break;
    case SYS_FILESIZE:
		  get_argument(esp, arg, 1, 0);
		  f->eax = filesize((int)arg[0]);
      break;
    case SYS_READ:
      get_argument(esp, arg, 3, 16);
      f->eax = read((int)(arg[0]), (void*)(arg[1]), (unsigned)(arg[2]));
      break;
    case SYS_WRITE:
      get_argument(esp, arg, 3, 16);
      f->eax = write((int)(arg[0]), (void*)(arg[1]), (unsigned)(arg[2]));
      break;
    case SYS_SEEK:
		  get_argument(esp, arg, 2, 0);
		  seek(arg[0],(unsigned)arg[1]);
      break;
    case SYS_TELL:
		  get_argument(esp, arg, 1, 0);
		  f->eax = tell((int)arg[0]);
      break;
    case SYS_CLOSE:
		  get_argument(esp, arg, 1, 0);
		  close((int)arg[0]);
      break;

  }   


  //thread_exit ();
}

void get_argument(void *esp, int *arg, int count, int add)
{
  void *sp = esp + 4 + add;
  if(count <= 0){
    return;
  }
  for(int i=0; i<count; i++){
    if(sp>LOW_ADDR && sp < HIGH_ADDR){
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
  thread_current() -> thread_status = status;
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

pid_t exec(const char *cmd_line){
  return process_execute(cmd_line);
}
int wait(pid_t pid){
  return process_wait(pid);
}
bool create(const char *file, unsigned initial_size){
  return filesys_create(file, initial_size);
}
bool remove(const char *file){
  return filesys_remove(file);
}
int open(const char *file){
	struct file *open = filesys_open(file);
  return (open == NULL)? -1 : process_add_file(open);
}
int filesize(int fd){
  struct file *file = process_get_file(fd);
  return (file == NULL)? -1 : file_length(file);
}
int read(int fd, void *buffer, unsigned size){
  int i;
  if(fd ==0){
    for(i=0;i<size;i++){
      if(((char*)buffer)[i] == '\0'){
        break;
      }
    }
  }
  return i;
}

void seek(int fd, unsigned position){
  file_seek(process_get_file(fd), position);
}
unsigned tell(int fd){
  file_tell(process_get_file(fd));
}
void close(int fd){
  process_close_file(fd);
}
