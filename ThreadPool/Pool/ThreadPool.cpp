#include "ThreadPool.h"

ThreadPool::ThreadPool():_done(false),_joiners(_threads)
{
    unsigned const thread_count=thread::hardware_concurrency();
    try{
        for(unsigned i=0;i<thread_count;++i){
            _threads.push_back(
                thread(&ThreadPool::Worker_Thread,this));
        }
    }
    catch(...){
        _done=true;
        throw;
    }

}

ThreadPool::~ThreadPool()
{
    _done=true;
}

void ThreadPool::Worker_Thread()
{
   while(!_done){
        function<void()>task;
        if(_work_queue.try_pop(task)){
            task();
        }else{
            this_thread::yield();
        }
   }
}

ThreadPool &ThreadPool::GetThreadPool()
{
   // TODO: 在此处插入 return 语句
   return threadPool;
}
ThreadPool ThreadPool::threadPool;
