#include <thread>
#include<vector>
#include <memory>
using namespace std;

class Join_Threads
{
public:  
    Join_Threads();
    ~Join_Threads();
    explicit Join_Threads(vector<thread>& threads);

private:  
    vector<thread>& _threads;    

};