//
// Created by yjs on 2022/3/14.
//

#include <muduo/base/noncopyable.h>
#include <muduo/base/Mutex.h>
#include <cstdint>
#include <iostream>
using namespace std;
using namespace muduo;



class Counter:public noncopyable{
public:
    Counter():value_(0){}
    int64_t value() const{

        MutexLockGuard lock(mutex_);
        return value_;

    };
    int64_t getAndIncrease() {
        MutexLockGuard lock(mutex_);
        int64_t ret=value_++;
        return ret;
    };


private:
    int64_t value_;
    mutable  MutexLock mutex_;


};



int main(){

    Counter*  counter= new Counter()  ;
    counter->getAndIncrease();
    cout << counter->value()<<endl;



    return 0;
}