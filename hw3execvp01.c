#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 1024
int main() {
	int chpid, exitcode;
	char com[SIZE];	char *pri[10];
	while(1) {
		bzero(com, SIZE);
		bzero(pri, sizeof(pri));
		printf("shell>");
		fgets(com, sizeof(com), stdin);
		com[strlen(com)-1]='\0';//개행 제거
		if(! strcmp(com, "exit")){ //명령어 입력시 "exit"이면 종료시킨다
			exit(0);
		}
				
		char *ptr = strtok(com, " "); //shell 명령어

		int index = 0;
		while(ptr != NULL) {
			pri[index] = ptr;
			ptr = strtok(NULL, " ");
//			printf("%s\n", pri[index]);
			index++;	
		}
		chpid = fork();
		if(chpid == 0) { //자식프로세스
			execvp(pri[0],pri); //명령어를 실행
			
			printf("command not found\n"); 
			exit(1);
		}
	}
		wait(&exitcode);
}
