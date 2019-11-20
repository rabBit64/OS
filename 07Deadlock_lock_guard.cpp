/* lock_gaurd의 활용
 잠금을 풀지 않아서 발생한 교착상태 */
#include <thread>
#include <iostream>
#include <mutex>
using namespace std;
int shared_data = 0; mutex shared_lock;
void thread_function(int id){
    shared_lock.lock(); shared_data = id;
    cout<<"Thread "<<id<<" set shared value to "<<shared_data<<endl;
    cout<<"Thread "<<id<<" has shared value as "<<shared_data<<endl;
    if(id != 1) shared_lock.unlock();
}
int main(void){
    const size_t thread_size = 5; thread threads[thread_size];
    for(size_t i = 0; i < thread_size; i++) threads[i] = thread(thread_function, i);
    for(size_t i = 0; i < thread_size; i++) threads[i].join();
    //Wait until threads are complete before main() continues
    cout<<"Done"<<endl; return 0;
}
/*
Thread 0 set shared value to 0
Thread 0 has shared value as 0
Thread 1 set shared value to 1
Thread 1 has shared value as 1

문제점
if(id != 1) shared_lock.unlock();
id = 0 인 스레드 잠금 해제, id = 1인 스레드는 잠금 해제 안함 -> 교착상태 발생
*/
*/
