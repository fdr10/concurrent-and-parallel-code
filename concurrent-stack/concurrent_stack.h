#include <iostream>
#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack: std::exception{
	const char * what() const throw();
};
template <typename T> 
class threadsafe_stack{
	private:
		std::stack<T> data;
		mutable std::mutex mux;
	public:
		threadsafe_stack(int size);
		threadsafe_stack(const threadsafe_stack& other);
		threadsafe_stack& operator=(const threadsafe_stack&) = delete;
		void push(T new_value);
		std::shared_ptr<T> pop();
		void pop(T &value);
		bool empty();
};

template<typename T>
threadsafe_stack<T>::threadsafe_stack(int size){
	std::cout<< size<<std::endl;
}

template<typename T>
threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack& other){
	std::lock_guard<std::mutex> lock{this->mux};
	this->data=other.data;
	std::cout<<"Created current stack"<<std::endl;
}


template<typename T>
void threadsafe_stack<T>::push(T new_value){
	std::lock_guard<std::mutex> lock{this->mux};
	this->data.push(std::move(new_value));
}


template<typename T>
std::shared_ptr<T> threadsafe_stack<T>::pop(){
	std::lock_guard<std::mutex> lock{this->mux};
	if(data.empty()) throw empty_stack{};
	std::shared_ptr<T> const res{std::make_shared<T>(data.top())};
	data.pop();
	return res;
}


template<typename T>
void threadsafe_stack<T>::pop(T& value){
	std::lock_guard<std::mutex> lock{this->mux};
	if(data.empty()) throw empty_stack{};
	value=data.top();
	data.pop();
}


template<typename T>
bool threadsafe_stack<T>::empty(){
	std::lock_guard<std::mutex> lock{this->mux};
	return data.empty();
}
