#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <ctime>
#include <chrono>
#include <string>
using namespace std;
class Semaphore {
private:
    mutex sem_mutex;
    condition_variable sem_cv;
    int sem_count;
public:
    Semaphore(int count = 0) : sem_count(count) { }
    void Signal() {
        unique_lock<mutex> lock(sem_mutex);
        ++sem_count;
        sem_cv.notify_one();
    }
    void wait() {
        unique_lock<mutex> lock(sem_mutex);
        sem_cv.wait(lock, [=] { return sem_count > 0; });
        --sem_count;
    }
};

mutex g_io_mutex;
Semaphore g_semaphore(1);

string formatTimeNow() {
    const time_t totalSeconds = time(NULL);
    unsigned currentSecond = (unsigned)totalSeconds % 60;
    unsigned totalMinutes = (unsigned)totalSeconds / 60;
    unsigned currentMinute = totalMinutes % 60;
    unsigned totalHours = totalMinutes / 60 + 9;
    unsigned currentHour = totalHours % 24;
    string now = to_string(currentHour) + " : "  + to_string(currentMinute) + " : " + to_string(currentSecond);
    return now;
}
void Worker() {
    g_semaphore.wait();
    thread::id thread_id = this_thread::get_id();
    string now = formatTimeNow();
    {
        lock_guard<mutex> lock(g_io_mutex);
        cout<<"Thread "<<thread_id<<": wait succeeded"<<" (" <<now<<")"<<endl;
    }
    //sleep 1 second to simualate data processing
    this_thread::sleep_for(chrono::seconds(1));
    g_semaphore.Signal();
}
int main() {
    const int SIZE = 3;
    thread threads[SIZE];
    for(int i=0; i<SIZE; ++i) threads[i] = thread(Worker);
    for(thread& t : threads) t.join();
    return 0;
}

/*
 Semaphore g_semaphore(1); 일 경우
 Thread 0x70000bed4000: wait succeeded (17 : 47 : 38)
 Thread 0x70000bfda000: wait succeeded (17 : 47 : 39)
 Thread 0x70000bf57000: wait succeeded (17 : 47 : 40)
 
 
 Semaphore g_semaphore(3); 일 경우
 Thread 0x70000c403000: wait succeeded (17 : 47 : 26)
 Thread 0x70000c509000: wait succeeded (17 : 47 : 26)
 Thread 0x70000c486000: wait succeeded (17 : 47 : 26)
 */
