/* mutex에 의한 상호배제 */
#include <thread>
#include <iostream>
#include <unistd.h>
#include <mutex>
using namespace std;
int shared_data = 0; mutex shared_lock;
void thread_function(int id) { //thread[0], [1], [2], [3], [4]가 서로 경합상태
    shared_lock.lock(); //임계영역을 잠금
    shared_data = id;
    cout<<"Thread "<<id<<" set shared value to "<<shared_data<<endl;
    sleep(id*100);
    cout<<"Thread "<<id<<" has shared value as "<<shared_data<<endl;
    shared_lock.unlock();
} //end of race on shared_data
int main(void){
    const size_t thread_size = 5; thread threads[thread_size]; //선언
    for(size_t i=0; i<thread_size; i++) threads[i] = thread(thread_function, i);
    for(size_t i =0; i<thread_size; i++) threads[i].join();
    cout<<"Done"<<endl; return 0;
}

