#include "Init.h"
#include "Scheduler.h"
#include "Thread.h"

#include <stdio.h>
#include <unistd.h>
void* AppTask();
void Testcase(void);//여기 둬야되나
typedef thread_t thread_id;//추가함
int main(void)
{
    thread_id tid1,tid2,tid3,tid4;//thread_t아닌가?
     int arg;
     ReadyQHead=NULL;
     ReadyQTail=NULL;
    //  Init();
    pthread_create(&tid1, NULL, AppTask, &arg);
    sleep(5);
    //sleep(1);
    
    //Ready_dequeue();

    // Ready_print_queue();
    
    // thread_create(&tid2, NULL, AppTask, &arg);
    // sleep(1);
    // Ready_print_queue();

    // thread_create(&tid3, NULL, AppTask, &arg);
    // sleep(1);
    // Ready_print_queue();

    // thread_create(&tid4, NULL, AppTask, &arg);
    // sleep(1);
    // Ready_print_queue();
    // thread_suspend(tid2);
    
    // for(int i=0;i<10;i++)
    // {
    //     Ready_enqueue(i);
    //     Ready_print_queue();
    // }
    // for(int i=0;i<10;i++)
    // {
    //     Ready_dequeue();
    //     Ready_print_queue();
    
    // }
    // Ready_print_queue();
    
    RunScheduler();
     //여기부터 추가
     //printf("test\n");
}
void* AppTask(void *arg)
{
    Testcase();
    return NULL;
}