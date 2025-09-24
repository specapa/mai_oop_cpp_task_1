#include <iostream>
#include <string>
#include "TimeConverter.hpp"

int main() {
    std::string s;
    std::getline(std::cin, s);
	std::cout << convert(parse(s)) << std::endl;
	return 0;
}

