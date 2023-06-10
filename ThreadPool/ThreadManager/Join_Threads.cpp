#include "Join_Threads.h"

Join_Threads::Join_Threads(vector<thread> &threads):_threads(threads){}
Join_Threads::~Join_Threads()
{
    for(unsigned long i=0;i<_threads.size();i++){
        if(_threads[i].joinable()){
            _threads[i].join();
        }
    }
}



