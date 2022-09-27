#include <iostream>
#include "concurrent_stack.h"
int main(){
	threadsafe_stack<int> s{10};
	return 0;
}
