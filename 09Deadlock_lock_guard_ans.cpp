/* lock_gaurd의 활용
 정상적인 수행
 */
#include <thread>
#include <iostream>
#include <mutex>
using namespace std;
int shared_data = 0;
mutex shared_lock;

void thread_function(int id){
    shared_lock.lock(); shared_data = id;
    cout<<"Thread "<<id<<" set shared value to "<<shared_data<<endl;
    cout<<"Thread "<<id<<" has shared value as "<<shared_data<<endl;
    shared_lock.unlock(); //먼저 잠금을 푼 경우
}
int main() {
    const size_t thread_size = 5; thread threads[thread_size];
    for(size_t i = 0; i<thread_size; i++) threads[i] = thread(thread_function, i);
    for(size_t i = 0; i<thread_size; i++) threads[i].join();
    //Wait until threads are complete before main() continues
    cout<<"Done "<<endl; return 0;
}
/*
 순서적으로 잠금을 해제함
 
 Thread 0 set shared value to 0
 Thread 0 has shared value as 0
 Thread 1 set shared value to 1
 Thread 1 has shared value as 1
 Thread 2 set shared value to 2
 Thread 2 has shared value as 2
 Thread 4 set shared value to 4
 Thread 4 has shared value as 4
 Thread 3 set shared value to 3
 Thread 3 has shared value as 3
 Done
 */

