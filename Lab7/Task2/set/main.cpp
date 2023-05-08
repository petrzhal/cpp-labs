#include <iostream>
#include "set/set.h"

int main() {
	set<int> a;
	for (int i = 10; i > 0; i--)
	{
		a.insert(i);
	}
	auto b = a;
	for (const auto& var : b) {
		std::cout << var << " ";
	}
	/*for (int i = 1; i <= 10; i++)
	{
		std::cout << a[i] << " ";
	}*/
	/*for (const auto& now : a) {
		std::cout << now.first << " ";
	}*/
	/*auto it = a.end();
	--it;
	for (; it != a.begin(); --it) {
		std::cout << *it << " ";
	}
	std::cout << "\n" << (*a.find(5));*/
}