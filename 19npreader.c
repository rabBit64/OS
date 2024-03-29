/*
1. 이름이 있는 pipe 생성
	mkfifo("myPipe", 0660);
2. 생성된 pipe에 open 명령어 이용. 디스크립터 생성
	fd = open("myPipe", O_RDONLY);
3. 프로세스간 디스크립터를 통해 상호 read/write 수행
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MAXLINE 100

/*이름 있는 파이프를 통해 읽은 내용을 프린트한다*/
int main(){
	int fd;
	char str[MAXLINE];

	unlink("myPipe");
	mkfifo("myPipe", 0660);
	fd = open("myPipe", O_RDONLY);

	while(readLine(fd, str)) //파이프에서 한 줄 읽기
		printf("%s \n",str);

	close(fd);
	return 0;
}

int readLine(int fd, char *str) {
	int n;
	do {
		n = read(fd, str, 1);
	}while (n > 0 && *str++ != NULL);
	return (n > 0);
}
