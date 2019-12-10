#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int pid;
void alarmHandler();
/*명령줄 인수로 받은 명령어 실행에 제한 시간을 둔다*/
int main(int argc, char *argv[]){
	int child, status, limit;
	signal(SIGALRM, alarmHandler);
	sscanf(argv[1], "%d", &limit);
	alarm(limit);

	pid = fork();
	if(pid == 0) {
		execvp(argv[2], &argv[2]); //명령어 실행
		fprintf(stderr, "%s: 실행불가\n", argv[1]);
	} else {
		child = wait(&status);
		printf("[%d] 자식 프로세스 %d 종료 \n", getpid(), pid);
	}
}

/*SIGNAL 처리 함수*/
void alarmHandler() {
	printf("[알람] 자식 프로세스 %d 시간 초과\n", pid);
	kill(pid, SIGINT); // 명령어 실행 중인 자식 프로세스 종료
}
/*
[anna~/Develop/hongik/OS]$ ./a.out 3 sleep 5                  
[알람] 자식 프로세스 1101 시간 초과
[1100] 자식 프로세스 1101 종료 
*/

/*참고
프로세스 동기화
주로 부모 프로세스가 wait()함수를 이용하여 자식 프로세스의 작업이 끝날때까지 기다렸다가 작업을 시작
*/
