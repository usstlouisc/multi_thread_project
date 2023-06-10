#include "Function_Wrapper.h"


void Function_Wrapper::operator()(){
    _spImpl->call();
}

Function_Wrapper::Function_Wrapper(Function_Wrapper&& other)
    :_spImpl(move(other._spImpl)){}

Function_Wrapper& Function_Wrapper::operator=(Function_Wrapper&& other)
{
    // TODO: 在此处插入 return 语句
    _spImpl=move(other._spImpl);   //move(_spImpl)   移动智能指针，移交归属权
    return* this;
}
