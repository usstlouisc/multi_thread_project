#include <iostream>
#include <thread>
#include <atomic>
#include "./../ThreadQueue/ThreadSafeQueue.h"
#include "./../ThreadManager/Join_Threads.h"
// ./代表根目录
// ../ 
using namespace std;
class ThreadPool
{
public:   
    ~ThreadPool();    
    void Worker_Thread();    
    template<typename Callable>
    void Submit(Callable f){
        _work_queue.push(f);
    }
    static ThreadPool& GetThreadPool();
private:
    ThreadPool() ; // noexcept关键字告诉编译器，该函数不会抛出异常
    atomic_bool _done;   
    ThreadSafeQueue<function<void()>> _work_queue;    
    vector<thread>_threads;   //线程池中的线程
    Join_Threads _joiners;  
    static ThreadPool threadPool;
    
};