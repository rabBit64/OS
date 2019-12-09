#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100
int main() {/*소문자-대문자 변환: 클라이언트 프로그램*/
	int clientfd, result;
	char inmsg[MAXLINE], outmsg[MAXLINE];
	struct sockaddr_un serverAddr;
	clientfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
	serverAddr.sun_family = AF_UNIX;
	strcpy(serverAddr.sun_path, "convert");
	do{ /*연력 ㄹ요청*/
		result = connect(clientfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
		if(result == -1) sleep(1);
	}while (result == -1);
	printf("변환할 문자열 입력:\n");
	fgets(inmsg, MAXLINE, stdin);
	while(clientfd, inmsg, strlen(inmsg)+1); //변환할 문자열 보내기
	readLine(clientfd, outmsg);
	printf("s --> \n%s", inmsg, outmsg);
	close(clientfd);
	exit(0);
}
readLine(int fd, char* str) {
	int n;
	do{
		n = read(fd, str, 1);
	}while (n>0 && *str++ != '\0');
	return (n>0);
}
