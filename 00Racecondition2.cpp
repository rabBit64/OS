/* thread[i] 경합 상태 */
#include <thread>
#include <iostream>
#include <unistd.h>
using namespace std;
int shared_data = 0;
void thread_function(int id) { //thread[0], [1], [2], [3], [4]가 서로 경합상태
    //임계영역 시작
    shared_data = id; //shared_data를 5개의 스레드가 경합함
    cout<<"Thread "<<id<<" set shared vlaue to "<<shared_data<<endl;
    sleep(id*100);//1000이 1초
    cout<<"Thread "<<id<<" has shared value as "<<shared_data<<endl;
} //end of race on shared_data
int main(void){
    const size_t thread_size = 5; thread threads[thread_size]; //선언
    for(size_t i=0; i<thread_size; i++) threads[i] = thread(thread_function, i);
    for(size_t i =0; i<thread_size; i++) threads[i].join();
    cout<<"Done"<<endl; return 0;
}
