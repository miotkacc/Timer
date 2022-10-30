#include <chrono>
#include <iostream>

#include "SimpleTimerFactory.hpp"
#include "SimpleTimer.hpp"


int main(){
    std::chrono::duration<double, std::ratio<1,1>> intervalS;
    {
        int interval;
        std::cout<<"please give me interval in seconds"<<std::endl;
        std::cin>>interval;
        intervalS = std::chrono::duration<double, std::ratio<1,1>>(interval);
    }
    SimpleTimerFactory simpleTimerFactory{};
    auto t1 = simpleTimerFactory.CreateOneShotTimer([]{std::cout<<"I am single shot!"<<std::endl;}, 3*intervalS);
    auto t2 = simpleTimerFactory.CreateRecurringTimer([](){std::cout<<"Running..."<<std::endl;}, 1.5*intervalS);
    auto t3 = simpleTimerFactory.CreateRecurringTimer([](){std::cout<<"Walking..."<<std::endl;}, intervalS);
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