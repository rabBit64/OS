#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int pid;
void alarmHandler();
/*명령줄 인수로 받은 명령어 실행에 제한 시간을 둔다. */
int main(int argc, char *argv[]) {
	int child, status, limit;
	signal(SIGALRM, alarmHandler);
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
void alarmHandler() {
	printf("[알람] 자식 프로세스 %d 시간 초과\n", pid);
	kill(pid, SIGINT);
}
/*
[anna~/Develop/hongik/OS]$ ./a.out 3 sleep 5
[알람] 자식 프로세스 1231 시간 초과
[1230] 자식 프로세스 1231 종료
*/
