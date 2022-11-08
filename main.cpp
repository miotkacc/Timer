#include <chrono>
#include <iostream>

#include "SimpleTimerFactory.hpp"
#include "SimpleTimer.hpp"


int main(){
    std::chrono::duration<double> intervalSeconds;
    {
        int interval;
        std::cout<<"please give me interval in seconds"<<std::endl;
        std::cin>>interval;
        intervalSeconds = std::chrono::duration<double>(interval);
    }
    const SimpleTimerFactory simpleTimerFactory{};
    auto t1 = simpleTimerFactory.CreateOneShotTimer([]{std::cout<<"I am single shot!"<<std::endl;}, 3*intervalSeconds);
    auto t2 = simpleTimerFactory.CreateRecurringTimer([]{std::cout<<"Running..."<<std::endl;}, 1.5*intervalSeconds);
    auto t3 = simpleTimerFactory.CreateRecurringTimer([]{std::cout<<"Walking..."<<std::endl;}, intervalSeconds);
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
            std::cout<<t1.get();
            std::cout<<t2.get()<<std::endl;
            std::cout<<t3.get()<<std::endl;
        }
    }
    return 0;
}