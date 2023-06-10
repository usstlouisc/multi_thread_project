#include <iostream>
#include <thread>
#include <atomic>
#include <future>
#include "./../ThreadQueue/ThreadSafeQueue.h"
#include "./../ThreadManager/Join_Threads.h"
#include "./../FunWrapper/Function_Wrapper.h"
using namespace std;

class ThreadPool_V1
{
private:
    atomic_bool _done;    
    ThreadSafeQueue<Function_Wrapper>work_queue;
    vector<thread>_threads;   //线程池中的线程
    Join_Threads _joiners;  
    static ThreadPool_V1 threadPool;
    ThreadPool_V1();
public:  
   
    ~ThreadPool_V1();
    void Work_Thread();
    void Stop();
    static ThreadPool_V1& GetThreadPool();
    
    template<typename FunctionType>
    future<typename result_of<FunctionType()>::type> submit(FunctionType f)
    {
        typedef typename result_of<FunctionType()>::type result_type;    //推断函数运行的结果类型
        packaged_task<result_type()>task(move(f));
        future<result_type>res(task.get_future());
        work_queue.push(move(task));
        return res;
    }

};
