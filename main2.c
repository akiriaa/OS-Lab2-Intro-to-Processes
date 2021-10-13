#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#define   MAX_COUNT  2

void ChildProcess(void);                /* child process prototype  */
void ParentProcess(void);               /* parent process prototype */

void main(void)
{
  pid_t  pid[MAX_COUNT];
  int i;
  
  for(i=0; i<MAX_COUNT; i++){
    pid[i] = fork();
    switch(pid[i]){
      case 0:
        ChildProcess();
        wait();
        break;
      case 1:
        break;
      default:
        ParentProcess();
        break;    
    };
  };
//parent process will wait for both to terminate
}
  
  
void ChildProcess(void)
{
  int i;
  /*reference
   * https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
   */
  
  time_t t;
  srand((unsigned) time(&t));
  for (i = 1; i <= (rand()%31); i++){ //loop for some random number of iterations, but no more than 30,
    printf("Child Pid: %d is going to sleep!\n", getpid());
    sleep(rand()%11); //random amount of time, but no more than 10 secs 
    printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
  }
  exit(0); //child process should calll exit(0) to terminate
}

void ParentProcess(void)
{
  int i;
  int status;
  wait(&status);
  printf("Child Pid: %d has completed\n", status);
}