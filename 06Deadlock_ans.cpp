/*정상적인 프로그램 예*/
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int shared_data = 0; mutex *locks = NULL;
int thread_size;//id = 0, 잠금 4,3,2,1,0 -> id=1, 해제 0,1,2,3,4순: 순서에 의한 해제 (?? 거꾸로 아닌가)
void thread_function(int id){
    for(int i=0; i < thread_size; i++) locks[i].lock();
    shared_data = id;
    cout<<"Thread "<<id<<" set data to "<<id<<endl;
    for(int i = thread_size-1; i>=0; i--) locks[i].unlock();
}
int main(int argc, char** argv){ //argv[1] = 5로 외부 입력
    thread_size = atoi(argv[1]);
    thread* threads = new thread[thread_size]; //동적 할당 메모리 스레드 배열 선언
    locks = new mutex[thread_size]; //동적 할당 뮤텍스 배열 선언
    for(int i=0; i<thread_size; i++) threads[i] = thread(thread_function, i);
    for(int i=0; i<thread_size; i++) threads[i].join();
    //Wait until Threads are complete before main() continues
    delete[] locks; delete[] threads; return 0;
}
/*
Thread 2 set data to 2
Thread 0 set data to 0
Thread 1 set data to 1
Thread 3 set data to 3
Thread 4 set data to 4
*/
