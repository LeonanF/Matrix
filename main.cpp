#include <iostream>
#include "Matrix.cpp"
#include <string>

int main() {

	Matrix<int> A = { {1,2},{3,4} };
	Matrix<int> B = { {1,2},{3,4} };
	auto C = A + B;

	std::cout << C;

	return 0;
}