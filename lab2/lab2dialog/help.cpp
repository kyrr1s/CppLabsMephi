#include "dialog.h"

void io::getType(int& value) {
	std::cin >> value;
	if (std::cin.fail()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::invalid_argument("Wrong type.");
	}
	if (std::cin.eof()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::runtime_error("End of file! Breaking...");
	}
	return;
}

void io::getType(double& value) {
	std::cin >> value;
	if (std::cin.fail()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::invalid_argument("Wrong type.");
	}
	if (std::cin.eof()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::runtime_error("End of file! Breaking...");
	}
	return;
}

void io::setRadiuses(double& r1, double& r2) {
	std::cout << "Input the first polar radius:" << std::endl;
	io::getType(r1);
	std::cout << "Input the second poler radius:" << std::endl;
	io::getType(r2);
	return;
}
