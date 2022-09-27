#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <cstdint>
#include <chrono>
#include <condition_variable>


static constexpr int MAX_FUEL_PERCENTAGE = 100;
std::mutex mux;
std::condition_variable full_cond;
std::condition_variable empty_cond;

void hello(){
  std::cout<<"Hello from thread"<<std::endl;
}


void producer(int* fuel, int delta){
  while(1){
    std::unique_lock<std::mutex> lk(mux);
    while( *fuel >= MAX_FUEL_PERCENTAGE ){
        std::cout<<"Tank is full. Waiting"<<std::endl;
        full_cond.wait(lk); 
    }
    (*fuel) += delta;
    std::cout<<"Producer fueled to: "<< *fuel<< " with delta: "<<delta<<std::endl;
    lk.unlock();
    empty_cond.notify_one();
  }
  
}


void consumer(int* fuel, int delta){
  while(1){
      std::unique_lock<std::mutex> lk(mux);
      while(*fuel < 0){
        std::cout<<"Tank is empty. Waiting"<<std::endl;
        empty_cond.wait(lk);
        
      }
      (*fuel) -= delta;
      std::cout<<"Consumer has fuel: "<< *fuel<< " with delta: "<<delta<<std::endl;
      lk.unlock();
      if(*fuel <= MAX_FUEL_PERCENTAGE){
          full_cond.notify_one();
      }
  }
}

int main(){
 
  int fuel = 0;
  int delta = 10;
  //std::thread hello_thread(hello);
  //hello_thread.join();
  std::thread producer_thread(producer, &fuel, delta);
  std::thread consumer_thread(consumer, &fuel, delta);
  
  producer_thread.join();
  consumer_thread.join();
  //consumer_thread.join();
  return 0;
}
