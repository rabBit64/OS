/*lock_gaurd의 활용
 deadlock 발생 */
#include <thread>
#include <iostream>
#include <mutex>
using namespace std;
int accounts[2]; mutex locks[2];
void thread_function(int id){ // We transfer money from our account to the other account
    int amount = (id + 2) * 10;
    lock_guard<mutex> this_lock(locks[id]); //Sleep(100);
    lock_guard<mutex> that_lock(locks[!id]);
    accounts[id] -= amount; accounts[!id] += amount;
    cout<<"Thread "<<id<<"transferred $"<<amount<<"from account"<<id<"to account"<<!id<<endl;
    
}
int main(void) {
    const size_t thread_size = 2; thread threads[thread_size];
    for(size_t i = 0; i<2; i++) accounts[i] = 100;
    for(size_t i = 0; i<2; i++) cout<<"Account"<<i<<"has $"<<accounts[i]<<endl;
    for(size_t i = 0; i<thread_size; i++) threads[i] = thread(thread_function, i);
    for(size_t i = 0; i<thread_size; i++) threads[i].join();
    //Wait until threads are complete before main() continues
    for(size_t i = 0; i<2; i++) cout<<"Account"<<i<<"has $"<<accounts[i]<<endl;
}
/*
Account 0 has $100
Account 1 has $100
Thread 0 transfered $20 from account0 to account1
Thread 1 transfered $30 from account1 to account0
Account 0 has $110
Account 1 has $90
*/
