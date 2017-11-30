#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void *child(void *arg) {
	printf("child\n");
	return NULL;
}
int 	thread_create(thread_t *thread, thread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
	pthread_t t;
	WrapperArg w;
	w.funcPtr = child;
	w.funcArg = arg;
	if(pthread_create(&t,NULL,WrapperFunc,&w)!=0){
		return 1;
	}
	printf("create complete\n");
	sleep(2);
	ReadyQinsert(t);
	return -1;
}


int 	thread_join(thread_t thread, void **retval)
{

	pthread_join(thread, (void*)&retval);
	return 1;
}

int 	thread_suspend(thread_t tid)
{
	printf("asd");
	printf("tid : %u",(unsigned int)tid);
	Thread *temp,*prev,*next,*Wtemp;
	temp = getThread(tid);
	printf("temp tid : %u",(unsigned int)temp->tid);
	Wtemp = temp;
	Wtemp->status=THREAD_STATUS_BLOCKED;
	WaitQinsert(Wtemp->tid);

	if(temp == NULL)
		printf("why?");
	else{
	if(temp == ReadyQHead&&temp==ReadyQTail)
		temp=NULL;
	else if(temp==ReadyQHead){
		next=temp->pNext;
		free(temp);
		next->pPrev=NULL;
	}
	else if (temp == ReadyQTail){
		prev=temp->pPrev;
		free(temp);
		prev->pNext=NULL;
		
	}
	else{
		temp->pPrev->pNext = temp->pNext;
		temp->pNext->pPrev = temp->pPrev;
		// prev=temp->pPrev;
		// next->pPrev=prev;
		// prev->pNext=next;	
		 free(temp);
	}
}
}


int	thread_resume(thread_t tid)
{
	Thread *temp, *prev,*next,*Wtemp;
	temp = getThread(tid);
	Wtemp = temp;
	Wtemp->status=THREAD_STATUS_READY;
	ReadyQinsert(Wtemp->tid);

	if(temp==WaitQHead){
		next=temp->pNext;
		next->pPrev=NULL;
		free(temp);
	}
	else if (temp == WaitQTail){
		prev=temp->pPrev;
		prev->pNext=NULL;
		free(temp);
	}
	else{
		next=temp->pNext;
		prev=temp->pPrev;
		next->pPrev=prev;
		prev->pNext=next;	
		free(temp);
	}
}


Thread* getThread(thread_t ntid){
	thread_t tid;
	Thread* temp=ReadyQHead;
	while(temp!=NULL){
		tid=temp->tid;
		if (ntid==tid)
			return temp;
		temp=temp->pNext;
	}
	// return (void*);

}

thread_t	thread_self()
{
	return pthread_self();
}	
void *WrapperFunc(void* arg){
	printf("ReadyQ insert tid : %u\n",(unsigned int)thread_self());
	void * ret;
	sigset_t set;
	int retSig;

	sigemptyset(&set);
	sigaddset(&set,SIGUSR1);
	sigwait(&set,&retSig);

	WrapperArg* pArg = (WrapperArg*)arg;
	void* funcPtr = pArg->funcPtr;
	void* funcArg = pArg->funcArg;

	ret = (pArg->funcPtr)(pArg->funcArg);
}
void thread_wait_handler(int signo){
	Thread* pTh;
	pTh = getThread(pthread_self());
	pthread_mutex_lock(&(pTh->readyMutex));
	while(pTh->bRunnable == 0)
		pthread_cond_wait(&(pTh->readyCond), &(pTh->readyMutex));
	pthread_mutex_unlock(&(pTh->readyMutex));
}
Thread* new_thread(){
	Thread *newth = (Thread*)malloc(sizeof(Thread));
	newth->pPrev = NULL;
	newth->pNext = NULL;
	newth->status = THREAD_STATUS_READY;
//	newth->readyCond;
	newth->bRunnable = 0;
//	newth->readyMutex;
	//durltj ek chrlghk

	return newth;
}

void ReadyQinsert(thread_t ntid){
	Thread *temp = ReadyQHead;
	Thread *newth = new_thread();
	newth->tid = ntid;
	if(ReadyQHead==NULL){
		ReadyQHead = newth;
		return;
	}
	else
		while(temp->pNext != NULL)
			temp = temp->pNext;
		temp->pNext=newth;
		newth->pPrev=temp;
		ReadyQTail = newth;
}
void ReadyQdelete(){
	Thread *temp = ReadyQHead;
	if(temp == NULL)	return;
	temp=temp->pNext;
	free(ReadyQHead);
	if(temp == NULL){ 
		ReadyQHead = temp;
		return;
	}
	temp->pPrev=NULL;
	ReadyQHead = temp;
}
void WaitQinsert(thread_t ntid){
	Thread *temp = WaitQHead;
	Thread *newth = new_thread();
	newth->tid = ntid;
	printf("%ld",newth->tid);
	if(WaitQHead==NULL){
		WaitQHead = newth;
		return;
	}
	else
		while(temp->pNext != NULL)
			temp = temp->pNext;
		temp->pNext=newth;
		newth->pPrev=temp;
		WaitQTail = newth;
}
void WaitQdelete(){
	Thread *temp = WaitQHead;
	if(temp == NULL)	return;
	temp=temp->pNext;
	free(WaitQHead);
	if(temp == NULL){ 
		WaitQHead = temp;
		return;
	}
	temp->pPrev=NULL;
	WaitQHead = temp;
}

void printQ(){
	Thread *temp = ReadyQHead;
	printf("Head(%p) \t Tail(%p)\n", ReadyQHead,ReadyQTail);
	int i = 0;
	while(temp != NULL){
		printf("node %2d*%p) > ",i,temp);
		printf("Prev : %p,  \t Next : %p\n", temp->pPrev, temp->pNext);
		temp = temp->pNext;
		i++;
	}
	printf("\n");
}
