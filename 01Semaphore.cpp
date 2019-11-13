/* 경합상태(race condition): 두개 이상의 프로세스(스레드)가 공유자원에 동시에 접근하는 상태 

세마포어(Semaphore) : 공유된 자원의 데이터를 여러 프로세스가 접근하는 것을 막는 것
뮤텍스(Mutex) : 공유된 자원의 데이터를 여러 쓰레드가 접근하는 것을 막는 것

   Mutex 클래스 : 잠금 메커니즘을 가지며 잠금과 잠금 해제 기능을 가짐
   Mutex 함수: 
   	lock(): 임계영역을 잠그는 기능 함수
	unlock(): 임계영역을 해제하는 기능함수
	bool try_lock(): 다른 스레드에 의해 잠겨있으면 false 반환 후 

 세마포어: 임계구역에 진입하기 전에 스위치를 사용 중으로 놓고 임구역으로 들어감
 
 */

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
using namespace std;
class semaphore {
private:
	mutex m_mtx;
	condition_variable m_cv;
	unsigned long cnt;
public:
	semaphore(int count = 1) : cnt(count) {}
	void notify() {
		unique_lock<mutex> lck(m_mtx);
		++cnt;
		m_cv.notify_one();
	}
	void wait() {
		unique_lock<mutex> lck(m_mtx);
		while(cnt == 0) //cnt가 0이면 계속 대기함
			m_cv.wait(lck);
		--cnt; //cnt가 감소했다는건 thread 가 작업에 들어갔다는것 
	}
	unsigned long getCount() { return cnt; }
};
static semaphore sm; static int num = 0;
void func1(int _id) {
	sm.wait(); // thread가 안에 들어가며 notify를 호출하고 wait된 스레드 하나 작업
	cout<<_id<<"번째 thread 작업 시작"<<endl;
	for(int i=0; i<10000000; ++i, ++num);
	cout<<_id<<"번째 작업 끝"<<endl;
	sm.notify();
}
int main() {
	thread thread01 = thread(func1, 1);
	thread thread02 = thread(func1, 2);
	thread01.join();
	thread02.join();
	cout<<num<<endl;
}

/*
2번째 thread 작업 시작
2번째 작업 끝
1번째 thread 작업 시작
1번째 작업 끝
20000000
*/
