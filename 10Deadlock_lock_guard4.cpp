/*lock_gaurd의활용
  deadlock 발생과 해결*/
#include <mutex>
#include <iostream>
#include <thread>
using namespace std;
mutex _m1, _m2;
static int shared_data = 50;
//Deadlock will occur because func12 and func21 aquires the two locks in reverse order
void func1(int num){
    lock_guard<mutex> lg1(_m1);
    cout<<"func1 shared dat= "<<shared_data++<<endl;
    lock_guard<mutex> lg2(_m2);
}
void func2(int num){
    lock_guard<mutex> lg2(_m2); //이 순서가 맞음
    cout<<"func2 shared dat= "<<shared_data++<<endl;
    lock_guard<mutex> lg1(_m1);
}
int main(int argc, char* argv[]){
    thread t1(func1, 1); thread t2(func2, 2);
    t1.join(); t2.join();
    cout<<"All done!";//this won't be executed becuase of deadlock
}
/*
 func1 shared dat=50
 func2 shared dat=51
 */
