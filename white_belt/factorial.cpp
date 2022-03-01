#include <iostream>

unsigned int factorial(unsigned int n) {
	if (n) 
		return n * factorial(n - 1);
	else
		return 1;
}

int main() {
	
	std::cout << factorial(4);

}

