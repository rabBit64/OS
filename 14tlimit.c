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
		execvp(argv[2], &argv[2]);
