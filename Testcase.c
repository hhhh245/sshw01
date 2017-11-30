#include "Init.h"
#include "Scheduler.h"
#include "Thread.h"
#include<stdio.h>
#include<unistd.h>
//이거 c파일로 해야됨
typedef thread_t thread_id;//추가함
void* foo1(void* arg)
{
    //….
    while(1);
    return((void *)0);

}

void* foo2(void* arg)
{
 //….
   while(1);
return((void *)0);

}
void* foo3(void* arg)
{
 //….
   while(1);
return((void *)0);

}
//…

void Testcase(void)
{
     thread_id tid1, tid2, tid3;
     int  arg1, arg2, arg3;
    // Ready_print_queue();
    // Wait_print_queue();

     thread_create(&tid1, NULL, foo1, &arg1);
     printf("%u",(unsigned int)tid1);
  
     thread_create(&tid2, NULL, foo2, &arg2);
     thread_create(&tid3, NULL, foo3, &arg3);
     //…
    //  printf("\n");
    //  Ready_print_queue();
    //  Wait_print_queue();

//  printf("\n");
//      Ready_print_queue();
//      Wait_print_queue();
      //thread_suspend(tid1);

      //prinQ();
    //  thread_suspend(tid2);
  
    //  //…
    //  thread_resume(tid1);
     printf("\n");
    // Ready_print_queue();
    // Wait_print_queue();
     
     while(1);
}