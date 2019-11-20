#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int shared_data = 0; mutex locks = NULL;
int thread_size; // id=0, 잠금 4,3,2,1,0 -> id=1, 잠금 0,1,2,3,4 순 thread[0] 해제 불가
void thread_function(int id) {
	if(id % 2) for(int i=0; i<thread_size; i++) locks[i].lock();
	else for(int i=thread_size-1; i>=0; i--) locks[i].lock();
	shared_data = id;
	cout<<"Thread"<<id<<"set data to"<<id<<endl;
	if(id % 2) for(int i=thread_size-1; i>=0; i--) locks[i].unlock();
	else for(int i=0; i<thread_size; i++) locks[i].unlock()
