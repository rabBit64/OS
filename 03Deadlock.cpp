/*교착상태 발생 프로그램의 예시
 교착상태: 2개 이상의 프로세스가 다른 프로세스의 작업이 끝나기만 기다리며
 작업을 더 이상 진행하지 못하는 상태*/
#include <iostream>
#include <thread>
using namespace std;
bool doNot = 1; //func1과 func2가 동시에 쓰레드 진입을 위해 필요한 수
thread* fn1; //Thread의 포인터 변수 (defined in main function)
thread* fn2;
void func1(bool x) {
    while(doNot) { ; } //doNot = 0 될 때까지 대기
    fn2 -> join(); //t1 스레드에서 t2의 자원 join() 함수를 요청 deadlock 발생
}
void func2(bool x) {
    while(doNot) { ; }
    fn1 -> join();
}
int main() {
    thread t1(func1, 1); thread t2(func2, 1);
    fn1 = &t1; fn2 = &t2; //t1, t2의 pointer 대입
    cout << "DeadLock Starting!" << endl;
    doNot = 0; //동시에 t1, t2 스레드 시작
    t1.join(); t2.join();
    cout<<"Hello!"; //This code will never be done...
}

/*
 DeadLock Starting!
 libc++abi.dylib: terminating with uncaught exception of type std::__1::system_error: thread::join failed: Invalid argument
 */
