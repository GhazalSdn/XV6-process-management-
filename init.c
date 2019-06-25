// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *argv[] = { "sh", 0 };

int
main(void)
{
  int pid, wpid;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr
 #ifdef RR
    printf(1, "Scheduler policy: round robin\n");
  #else
  #ifdef FRR
    printf(1, "Scheduler policy: fifo round robin\n");
  #else
  #ifdef GRT
    printf(1, "Scheduler policy: Guarnteed(Fair-Share) scheduling\n");
  #else
  #ifdef 3Q
    printf(1, "Scheduler policy: Multi level queue scheduling\n");
  
  #endif
  #endif
  #endif
  #endif




  for(;;){
    printf(1, "init: starting sh\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
