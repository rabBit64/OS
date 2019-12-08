/* 제한 시간 명령어 실행 예제
명령줄 인수로 받은 명령어를 제한 시간 내에 실행
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int pid;
void alarmHandler();
/*명령줄 인수로 받은 명령어 실행에 제한 시간을 둔다. */
int main(int argc, char *argv[]) {
	int child, status, limit;
	signal(SIGALRM, alarmHandler); //자식 프로세스가 명령어를 실행하는 동안 정해진 시간이 초과되면 SIGALRM 시그널이 발생
	sscanf(argv[1], "%d", &limit);
	alarm(limit);
	pid = fork();

	if(pid == 0) {
		execvp(argv[2], &argv[2]);
		fprintf(stderr, "%s:실행 불가\n", argv[1]);
	} else {
		child = wait(&status);
		printf("[%d] 자식 프로세스 %d 종료 \n", getpid(), pid);
	}
}
void alarmHandler() { //SIGALRM 시그널에 대한 처리함수 alarmHandler()에서 자식 프로세스를 강제 종료
	printf("[알람] 자식 프로세스 %d 시간 초과\n", pid);
	kill(pid, SIGINT); //자식 프로세스에 SIGINT 시그널을 보내어 강제 종료
}
/*
[anna~/Develop/hongik/OS]$ ./a.out 3 sleep 5
[알람] 자식 프로세스 1231 시간 초과
[1230] 자식 프로세스 1231 종료
*/
