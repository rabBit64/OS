/*서버
  socket() -> bind() -> listen() -> accept() -> read()/write() -> close()

  1. socket() 정의: client-server 간 통신용 file descriptor 만듦
  2. bind(): 자신의 소켓 이름, type 정의(uni)
             자신의 IP, port 정의
  3. listen(): client 연결 요청 대기
  4. accept(): server의 복사 소켓 client 소켓 연결
               -> client 소켓 구조를 setting
			   -> connfd 를 리턴 (data 연결라인 descriptor)
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100
/*소문자를 대문자로 변환하는 서버 프로그램*/
int main(){
	int listenfd, connfd, clientlen;
	char inmsg[MAXLINE], outmsg[MAXLINE];
	struct sockaddr_un serverAddr, clientAddr;

	signal(SIGCHLD, SIG_IGN);
	clientlen = sizeof(clientAddr);

	listenfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL); //1. 소켓 정의
	serverAddr.sun_family = AF_UNIX;
	strcpy(serverAddr.sun_path, "convert");
	unlink("convert");
	bind(listenfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); //2. bind(생성한 소켓을 특정 포트에 등록)

	listen(listenfd, 5); //3. listen(클라이언트의 접속을 기다림)

	while(1) { /* 소켓 연결 요청 수락*/
		connfd = accept(listenfd, (struct sockaddr *) &clientAddr, &clientlen); //4. accept
		if(fork() == 0) {
			/*소켓으로부터 한 줄을 읽어 대문자로 변환하여 보냄*/
			readLine(connfd, inmsg);
			toUpper(inmsg, outmsg);
			write(connfd, outmsg, strlen(outmsg)+1);
			close(connfd);
			exit(0);
		} else close(connfd);
	}
}

toUpper(char* in, char* out) {
	int i;
	for(i = 0; i<strlen(in); i++) 
		if(islower(in[i])) out[i] = toupper(in[i]);
		else out[i] = in[i];
	out[i] = '\0';
}
/*한 줄 읽기*/
readLine(int fd, char* str) {
	int n;
	do{
		n = read(fd, str, 1);
	}while (n>0 && *str++ != '\0');
	return (n>0);
	
}
