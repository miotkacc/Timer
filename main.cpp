#include "timer.hpp"
#include <chrono>
#include <iostream>

void hello()
{
    std::cout<<"funkcja"<<std::endl;
}

int main(){
    Timer t;
    t.start();
    t.startTimeInterval(std::chrono::milliseconds{400}, hello);
    while(1){};
    return 0;
}