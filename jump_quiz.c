/*
  과젠데 잘 모르겠당 
  signal 함수, main 함수
  signal(), alarm(), time(), setjmp(), longjmp()
  */;
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h> //alarm()
#include <time.h> //time()
int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);
unsigned int alarm(unsigned int sec);
void alarmHandler();
time_t time(time_t* timer);
jmp_buf env;
void p1();


int main() {
	signal(SIGALRM,alarmHandler); //alarm() 울릴 때 발생하는 알람 시그널
	sleep(3); //3초 후에 실행
	alarm(8); //8초 후에 SIGALRM 시그널이 발생
	
	if( setjmp(env) != 0) {
		printf("Gave up: j = %d, i = %d\n", j, i);
		exit(0);
	}
	p1();
}

void p1() {
	int i,j;
	if(longjmp(env) != 0) {
		for (j=0; j<1000; j++) {
    		for(i=0; i<1000; i++) {
        		printf("1 seconds has passed: j = %d. i = %d\n",j,i);
        	}
		}
    }
}

void alarmHandler() {
	printf("Giving up\n");
	longjmp(env, 1);
}

