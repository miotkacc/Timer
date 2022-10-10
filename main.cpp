#include "timer.hpp"
#include <chrono>
#include <iostream>
#include <stdio.h>

int main(){
    int interval;
    std::cout<<"please give me interval in ms"<<std::endl;
    std::cin>>interval;
    Timer t;
    t.addFunction(FunctionInfo{std::chrono::milliseconds{3*interval}, [](){std::cout<<"I am single shot!"<<std::endl;}, false});
    t.addFunction(FunctionInfo{std::chrono::milliseconds{int(1.5*interval)}, [](){std::cout<<"Running..."<<std::endl;}, true});
    t.addFunction(FunctionInfo{std::chrono::milliseconds{interval}, [](){std::cout<<"Walking..."<<std::endl;}, true});
    t.start();
    std::cout<<"E displays elapsed time for all running timers"<<std::endl;
    std::cout<<"Q stops application"<<std::endl;
    char key = ' ';
    while(key != 'Q')
    {
        std::cin>>key;
        if(key == 'E'){
            std::cout<<t.getElapsedTime().count()<<" elapsed time"<<std::endl;
        }
    }
    return 0;
}