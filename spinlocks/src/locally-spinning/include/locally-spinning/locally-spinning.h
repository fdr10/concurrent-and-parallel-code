#include <atomic>
#include <thread>
#include <cstdint>
#include <vector>

class SpinLock{
	private:
		std::atomic<bool> locked{false};

	public:

		void lock(){
      while(1){
        if(!locked.exchange(true)) return;
    			while(locked.load())
    				;
      }
		}

	
		void unlock(){locked.store(false);}

};


// Increment val once each time the lock is acquired
inline void increment(SpinLock &s, std::int64_t &val) {
  for (int i = 0; i < 100000; i++) {
    s.lock();
    val++;
    s.unlock();
  }
}





