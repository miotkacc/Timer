#include <chrono>
#include <iostream>

#include "SimpleTimerFactory.hpp"
#include "SimpleTimer.hpp"
#include "CVSingleRunnerStrategy.hpp"
#include "FunctionInfo.hpp"


int main(){
    /*
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
    */

    std::chrono::duration<double> intervalSeconds{1};
    auto fun = [](){std::cout<<"sieman"<<std::endl;};
    Timer::FunctionInfo functionInfo{fun ,std::chrono::milliseconds{4000}};
    std::unique_ptr<IRunnerStrategy> cvs = std::make_unique<CVSingleRunnerStrategy>(functionInfo);
    SimpleTimer t{std::move(cvs)};
    t.start();
    std::this_thread::sleep_for(std::chrono::milliseconds{33});
    t.stop();
    std::cout<<"E displays elapsed time for all running timers"<<std::endl;
    std::cout<<"Q stops application"<<std::endl;
    char key = ' ';
    while(key != 'Q')
    {
        std::cin>>key;
        if(key == 'E'){
            std::cout<<&t;
        }
    }
    
    return 0;
}