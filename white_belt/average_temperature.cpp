#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>

std::vector<int> more_average_temp(const std::vector<int>& v) {

	std::vector<int> ret;
	
	int aver_temp = std::accumulate(v.begin(), v.end(), 0);
	aver_temp /= v.size();
	std::cout << "aver: " << aver_temp << '\n';
	
	std::copy_if(v.begin(), v.end(), std::back_inserter(ret), [&](int x) {return x > aver_temp;});
	
	return ret;
	
}

int main() {

	std::vector<int> temp_days {7, 6, 3, 0, 9};
	
	auto v = more_average_temp(temp_days);
	
	for(auto& n : v) {
		std::cout << n << ' ';
	}	
	
}
