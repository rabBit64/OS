/* thread t1, t2 경합 상태*/
#include <iostream>
#include <thread>
using namespace std; static int shared = 50;
void printSquare1() { //thread1 수행 함수
	for(int j=0; j<5; j++) {
		for(int i=0; i<5; i++) cout<<shared++<<' ';
		//Sleep(100); cout<<endl;
	}
	//여기까지가 임계영역	
}
void printSquare2() {
	for(int j=0; j<5; j++){
		for(int i=0; i<5; i++) cout<<shared--<<' ';
		//Sleep(100); cout<<endl;
	}
}
int main() {
	thread t1(printSquare1); thread t2(printSquare2);
	t1.join(); //main()이 선 종료 방지, thread t1이 끝날 때까지 대기
	t2.join(); return 0;
}
