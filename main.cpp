#include "timer.hpp"
#include <chrono>
#include <iostream>

void hello2()
{
    std::cout<<"funkcja2"<<std::endl;
}

void hello()
{
    std::cout<<"funkcja"<<std::endl;
}

int main(){
    Timer t;
    t.addFunction(FunctionInfo{std::chrono::milliseconds{2000}, hello2, true});
    t.addFunction(FunctionInfo{std::chrono::milliseconds{1000}, hello, true});
    t.start();
    std::cout<<t.get_elapsed_time().count()<<" elapsed time"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds{4});
    t.stop();
    std::cout<<t.get_elapsed_time().count()<<" elapsed time"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds{4});
    return 0;
}