#include <iostream>

bool palindrom(const std::string& s) {

	return (s == std::string(s.rbegin(), s.rend()));
}

int main() {
	
	std::cout << palindrom("madam") << '\n';
	std::cout << palindrom("ser") << '\n';
}
