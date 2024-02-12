#pragma once
#include <vector>
#include <iostream>
#include <string>

template<typename T>
using MatrixInit = const std::initializer_list<std::initializer_list<T>>&;


template<typename T>
class Matrix
{

private:
	std::vector<std::vector<T> > mat;
	unsigned rows;
	unsigned cols;

public:

	Matrix(unsigned _rows, unsigned _cols, const T& _initial);
	Matrix(const Matrix<T>& rhs);
	Matrix(MatrixInit<T> valores);
	virtual ~Matrix();

	// Sobrecarga de operador de atribuição
	Matrix<T>& operator=(const Matrix<T>& rhs);

	// Operações matemáticas entre matrizes
	template<typename U>
	Matrix<decltype(T() + U())> operator+(const Matrix<U>& rhs);

	template<typename U>
	Matrix<decltype(T() + U())> operator-(const Matrix<U>& rhs);

	template<typename U>
	Matrix<decltype(T() + U())> operator*(const Matrix<U>& rhs);

	template<typename U>
	Matrix<decltype(T() + U())> operator+=(const Matrix<U>& rhs);

	template<typename U>
	Matrix<decltype(T() + U())> operator-=(const Matrix<U>& rhs);

	template<typename U>
	Matrix<decltype(T() + U())> operator*=(const Matrix<U>& rhs);

	Matrix<T> transpose();

	// Operações matemáticas de matrizes com escalares à direita
	template<typename U>
	Matrix<decltype(T() + U())> operator+(const U& rhs);

	template<typename U>
	Matrix<decltype(T() + U())> operator-(const U& rhs);

	template<typename U>
	Matrix<decltype(T() + U())> operator*(const U& rhs);

	template<typename U>
	Matrix<decltype(T() + U())> operator/(const U& rhs);

	template<typename U>
	Matrix<decltype(T() + U())> operator+=(const U& rhs);

	template<typename U>
	Matrix<decltype(T() + U())> operator-=(const U& rhs);

	template<typename U>
	Matrix<decltype(T() + U())> operator*=(const U& rhs);

	template<typename U>
	Matrix<decltype(T() + U())> operator/=(const U& rhs);

	// Operações matriz/vetor
	std::vector<T> diagVec();

	// Acessar os elementos individualmente
	T& operator()(const unsigned& row, const unsigned& col);
	const T& operator()(const unsigned& row, const unsigned& col) const;

	unsigned get_rows() const;
	unsigned get_cols() const;
};

// Operador de saída <<
template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& rhs);


// Sobrecarga do operador para permitir adicionar um escalar à esquerda da matriz
template<typename T, typename U>
Matrix<decltype(T() + U())> operator+(const U& lhs, const Matrix<T>& rhs);

// Sobrecarga do operador para permitir adicionar um escalar à esquerda da matriz
template<typename T, typename U>
Matrix<decltype(T() + U())> operator*(const U& lhs, const Matrix<T>& rhs);