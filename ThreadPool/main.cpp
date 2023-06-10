

//#include "./Pool/ThreadPool.h"
//#pragma once
#include "./Pool/ThreadPool_V1.h"
#include <atomic>

int JJ(int a,int b)
{
    cout << "is so difficult" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return a+b;
}

int main()
{
    // ThreadPool_V1 pool;   
    // auto f=bind(JJ,2,6);
    // future<int>fut=pool.submit(f);
    // cout<<fut.get()<<endl;    
    // pool.Stop();

    ThreadPool_V1& pool=ThreadPool_V1::GetThreadPool();
    auto f=bind(JJ,2,6);
    future<int>fut=pool.submit(f);
    cout<<fut.get()<<endl;    
    pool.Stop();
    
}
