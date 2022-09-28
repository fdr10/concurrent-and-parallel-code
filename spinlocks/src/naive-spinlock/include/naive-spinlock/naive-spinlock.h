#include <atomic>
#include <thread>
#include <cstdint>
#include <vector>

class SpinLock{
	private:
		std::atomic<bool> locked{false};

	public:

		void lock(){

			while(locked.exchange(true))
				;
		}

	
		void unlock(){locked.store(false);}

};


// Increment val once each time the lock is acquired
inline void inc(SpinLock &s, std::int64_t &val) {
  for (int i = 0; i < 100000; i++) {
    s.lock();
    val++;
    s.unlock();
  }
}





