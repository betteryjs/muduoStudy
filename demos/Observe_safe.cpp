//
// Created by yjs on 2022/3/15.
//
#include <iostream>
#include <vector>
#include <memory>
#include <muduo/base/Mutex.h>
using namespace std;
using namespace muduo;

class Observer {
public:
    ~Observer();
    void update();
};


Observer::~Observer() {


}
//观察目标
class Observable {
public:
    void register_(const weak_ptr<Observer> & x) ;
    void notifyObservers() {
       MutexLockGuard lock(mutex_);
       Iterator iterator=observers_.begin();
       if(iterator!=observers_.end()){
           shared_ptr<Observer> obj(iterator->lock());
           if(obj){

               obj->update();
               ++iterator;
           }else{
               iterator=observers_.erase(iterator);
           }
       }
    }
private:
    mutable MutexLock mutex_;
    std::vector<weak_ptr<Observer>> observers_;
    using Iterator = std::vector<weak_ptr<Observer>>::iterator;
};



