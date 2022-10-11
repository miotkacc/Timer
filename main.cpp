#include <chrono>
#include <iostream>

#include "timer.hpp"

int main(){
    int interval_ms;
    {
        int interval;
        std::cout<<"please give me interval in seconds"<<std::endl;
        std::cin>>interval;
        interval_ms = interval*1000;
    }
    SimpleTimer t1({std::chrono::milliseconds{3*interval_ms}, []{std::cout<<"I am single shot!"<<std::endl;}, false});
    SimpleTimer t2({std::chrono::milliseconds{int(1.5*interval_ms)}, [](){std::cout<<"Running..."<<std::endl;}, true});
    SimpleTimer t3({std::chrono::milliseconds{interval_ms}, [](){std::cout<<"Walking..."<<std::endl;}, true});
    t1.start();
    t2.start();
    t3.start();
    std::cout<<"E displays elapsed time for all running timers"<<std::endl;
    std::cout<<"Q stops application"<<std::endl;
    char key = ' ';
    while(key != 'Q')
    {
        std::cin>>key;
        if(key == 'E'){
            std::cout<<t1.getElapsedTime().count()<<" t1 elapsed time"<<std::endl;
            std::cout<<t2.getElapsedTime().count()<<" t2 elapsed time"<<std::endl;
            std::cout<<t3.getElapsedTime().count()<<" t3 elapsed time"<<std::endl;
        }
    }
    return 0;
}