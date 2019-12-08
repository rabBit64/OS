/*setjmp(), longjmp() 함수를 이용하여 a가 8번 수행한 후 종료시키는 프로그램*/
#include <stdio.h>
#include <setjmp.h>

jmp_buf jump_buffer;

void a(int count) {
	printf("a(%d) called\n", count);
	longjmp(jump_buffer, count+1);
}
int main(void) {
	int count = 0;
	if(setjmp(jump_buffer) != 9)
		a(++count);
}
/*
a(1) called
a(2) called
a(3) called
a(4) called
a(5) called
a(6) called
a(7) called
a(8) called
*/
