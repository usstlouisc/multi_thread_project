#include <iostream>
#include <thread>
#include <queue>
#include <condition_variable>
using namespace std;

template <typename T>
class ThreadSafeQueue
{
private:
    int _a;
    queue<T> _q;
    condition_variable _cv;
    mutex _mut;

public:
    ThreadSafeQueue() {}
    ~ThreadSafeQueue() {}

    void push(T data)
    {
        lock_guard<mutex> lock(_mut);
        _q.push(move(data));
        _cv.notify_one();
    }

    //取数据会阻塞
    void wait_and_pop(T& data)
    {
        unique_lock<mutex> lock(_mut);
        _cv.wait(lock, [this]
                 { return !_q.empty(); });
        //T data = _q.front();
        data=move(_q.front());
        _q.pop();
        //lock.unlock();        
    }

    shared_ptr<T> wait_and_pop(){
         unique_lock<mutex> lock(_mut);
        _cv.wait(lock, [this]
                 { return !_q.empty(); });
        shared_ptr<T>sp(make_shared(
            move(_q.front())
            ));      
         _q.pop();
       // lock.unlock();
        return sp;
    }

    bool try_pop(T& data){
         unique_lock<mutex> lock(_mut);
         if(!_q.empty()){
            data=move(_q.front());
            _q.pop();
            //lock.unlock();
            return true;
         }else{
            return false;
         }
    }

    //取数据不会阻塞，有就有，没有就没有，立即返回
    shared_ptr<T> try_pop()
    {
        unique_lock<mutex> lock(_mut);
        if(!_q.empty()){
            shared_ptr<T>sp(make_shared(
                move(_q.front())
                ));
            _q.pop();           
         }
         else{
            shared_ptr<T>p1(nullptr);
            return p1;
           // return shared_ptr<T>sp1(nullptr);
         }        
    }

    bool empty()
    {
        lock_guard<mutex> lock(_mut);
        return _q.empty();
    }
};
