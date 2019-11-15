#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
using namespace std;

class semaphore {
private:
    mutex m_mtx;
    condition_variable m_cv; //조건 변수 (서로 다른 스레드 블로킹 할 수 있음. 통신 가능하게 함)
    unsigned long cnt; //약간 이게 lock의 개념 같은데(0이면 대기해야하고 1되면 들어갈 수 있게..?)
public:
    semaphore(int count = 1) : cnt(count) {} //생성자 cnt 지정 안해줄 경우 default 값 1
    void notify() {
        unique_lock<mutex> lck(m_mtx);
        ++cnt;
        m_cv.notify_one(); //해당 조건 변수 기다리고 있는 스레드 중 한 개를 깨움
    }
    void wait() {
        unique_lock<mutex> lck(m_mtx);
        while(cnt == 0) //cnt가 0이면 계속 대기함
            m_cv.wait(lck);
        --cnt; //cnt가 감소했다는건 thread 가 작업에 들어갔다는것 (??)
    }
    unsigned long getCount() { return cnt; }
};

static semaphore sm;
static int num = 0; //공유자원

void func1(int _id) {
    sm.wait(); // thread가 안에 들어가며 notify를 호출하고 wait된 스레드 하나 작업 (??)
    cout<<_id<<"번째 thread 작업 시작"<<endl;
    for(int i=0; i<10000000; ++i, ++num);
    cout<<_id<<"번째 작업 끝"<<endl;
    sm.notify();
}
int main() {
    /*쓰레드(thread) : 프로세스에서 실행되는 단위*/
    thread thread01 = thread(func1, 1); //func(1) 실행하는 thread01 객체
    thread thread02 = thread(func1, 2); //func(2) 실행하는 thread02 객체
    cout<<num<<endl;
    thread01.join();//join() 을 실행시키면 thread01이 종료되기 전까지 기다림
    
    thread02.join();//
    cout<<num<<endl;
}

/*
 서로 다른 스레드들이 동일한 자원을 사용할 때 생기는 문제: 경쟁 상태
 
 condition_varibale 클래스가 제공하는 메서드
 1. notify_one(); 해당 조건 변수를 기다리고 있는 스레드 중 한 개의 스레드를 깨운다
 2. notify_all(); 해당 조건 변수를 기다리고 있는 모든 스래드를 깨운다


/*
결과:
 1번째 thread 작업 시작
 1번째 작업 끝
 2번째 thread 작업 시작
 2번째 작업 끝
 20000000
*/
