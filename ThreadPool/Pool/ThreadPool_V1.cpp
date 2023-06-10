#include "ThreadPool_V1.h"

void ThreadPool_V1::Work_Thread()
{
    while(!_done){
        Function_Wrapper task;
        if(work_queue.try_pop(task)){
            task();   //重载了对象的行为
        }else{
            this_thread::yield();
        }
    }
}

void ThreadPool_V1::Stop()
{
    _done=true;
}

ThreadPool_V1 &ThreadPool_V1::GetThreadPool()
{
    // TODO: 在此处插入 return 语句
    return threadPool;
}
ThreadPool_V1 ThreadPool_V1::threadPool;
ThreadPool_V1::ThreadPool_V1():_done(false),_joiners(_threads)
{
    unsigned const thread_count=thread::hardware_concurrency();
    try{
        for(unsigned i=0;i<thread_count;++i){
            _threads.push_back(
                thread(&ThreadPool_V1::Work_Thread,this));
        }
    }
    catch(...){
        _done=true;
        throw;
    }

}

ThreadPool_V1::~ThreadPool_V1()
{
    _done=true;
}