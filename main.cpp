#include <iostream>
#include "Matrix.cpp"
#include <string>

int main() {

	Matrix<int> A(1, 2, 3);
	Matrix<int> B(1, 2, 2);

	B = 2 + B;
	
	std::cout << A;

	return 0;
}