#include "CVSingleRunnerStrategy.hpp"

#include <condition_variable>
#include <chrono>
#include <iostream>


void CVSingleRunnerStrategy::run(const std::function<std::chrono::milliseconds()>){
    std::cout<<"czekanie " << std::endl;
    std::unique_lock<std::mutex> myUniqueLock{myMutex};
    if(cv.wait_for(myUniqueLock, functionInfo.interval) == std::cv_status::timeout){
        functionInfo.funName();
    }else{
        std::cout<<"somebody pressed stop"<<std::endl;
    }
}

void CVSingleRunnerStrategy::stop(){
    std::cout<<"I am trying to stop";
    //myMutex.unlock();

    cv.notify_all();
}

CVSingleRunnerStrategy::~CVSingleRunnerStrategy(){

}

CVSingleRunnerStrategy::CVSingleRunnerStrategy(const Timer::FunctionInfo& functionInfo): functionInfo(functionInfo){
}
