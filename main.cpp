#include <chrono>
#include <iostream>

#include "SimpleTimerFactory.hpp"
#include "SimpleTimer.hpp"


int main(){
    int interval_ms;
    {
        int interval;
        std::cout<<"please give me interval in seconds"<<std::endl;
        std::cin>>interval;
        interval_ms = interval*1000;
    }
    SimpleTimerFactory simpleTimerFactory{};
    auto t1 = simpleTimerFactory.CreateOneShotTimer([]{std::cout<<"I am single shot!"<<std::endl;}, std::chrono::milliseconds{3*interval_ms});
    auto t2 = simpleTimerFactory.CreateRecurringTimer([](){std::cout<<"Running..."<<std::endl;}, std::chrono::milliseconds{int(1.5*interval_ms)});
    auto t3 = simpleTimerFactory.CreateRecurringTimer([](){std::cout<<"Walking..."<<std::endl;}, std::chrono::milliseconds{interval_ms});
    t1->start();
    t2->start();
    t3->start();
    std::cout<<"E displays elapsed time for all running timers"<<std::endl;
    std::cout<<"Q stops application"<<std::endl;
    char key = ' ';
    while(key != 'Q')
    {
        std::cin>>key;
        if(key == 'E'){
            std::cout<<t1->getElapsedTime().count()<<" ms t1 elapsed time"<<std::endl;
            std::cout<<t2->getElapsedTime().count()<<" ms t2 elapsed time"<<std::endl;
            std::cout<<t3->getElapsedTime().count()<<" ms t3 elapsed time"<<std::endl;
        }
    }
    return 0;
}