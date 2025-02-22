#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <stdlib.h>
#include <unistd.h>


using namespace std;

queue<int> _queue;
mutex queue_mtx;
condition_variable condition;


void producer(){
    // push to the queue
    int number = 5;
    sleep(4);

    cout << "Producer Inserting..." << endl;
    unique_lock<mutex> lock(queue_mtx);
    _queue.push(number);
    queue_mtx.unlock();

    condition.notify_one();
};

void consumer(){
    // pop from the queue

    // while queue is empty
    unique_lock<mutex> lock(queue_mtx);
    while(_queue.empty()){
        cout << "Consumer waiting on empty Queue..." << endl;
        condition.wait(lock);
    }

    auto result = _queue.front();
    _queue.pop();

    cout << "Consumer consumed " << result << endl;
};




int main(){


    thread producer1 = thread(producer);
    thread consumer1 = thread(consumer);


    producer1.join();
    consumer1.join();


    return 0;
};