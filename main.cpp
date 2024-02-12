#include <iostream>
#include "Matrix.cpp"
#include <string>

int main() {

	Matrix<int> A = { {1,2}, {3,4} };

	std::cout << A * 2;
	std::cout << 2 * A;

	return 0;
}