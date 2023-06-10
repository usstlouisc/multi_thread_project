#include <memory>
using namespace std;

struct impl_base
{
    virtual void call() = 0; // 接口
    virtual ~impl_base(){};
};

//模版类
template <typename F>
struct impl_type : impl_base
{

    F _f;
    impl_type(F &&f) : _f(move(f)) {} // 构造函数
    void call()
    {
        _f();
    }
};

class Function_Wrapper
{
public:
    unique_ptr<impl_base> _spImpl;

public:
    template <typename F>
    Function_Wrapper(F&& f) : _spImpl(
                                  new impl_type<F>(move(f))) {}

    Function_Wrapper() = default;               // 默认构造函数
    void operator()();                          // 重载

    Function_Wrapper(Function_Wrapper &&other); // 移动构造函数   左值触发
    Function_Wrapper& operator=(Function_Wrapper&& other);

    Function_Wrapper(const Function_Wrapper &) = delete;
    Function_Wrapper(Function_Wrapper &) = delete;
    Function_Wrapper& operator=(const Function_Wrapper& ) = delete;
};
