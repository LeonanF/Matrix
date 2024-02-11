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

	// Sobrecarga de operador de atribui��o
	Matrix<T>& operator=(const Matrix<T>& rhs);

	// Opera��es matem�ticas entre matrizes
	template<typename U>
	Matrix<decltype(T() + U())> operator+(const Matrix<U>& rhs);
	template<typename U>
	Matrix<T> operator-(const Matrix<T>& rhs);
	template<typename U>
	Matrix<T> operator*(const Matrix<T>& rhs);
	template<typename U>
	Matrix<T>& operator+=(const Matrix<T>& rhs);
	template<typename U>
	Matrix<T>& operator-=(const Matrix<T>& rhs);
	template<typename U>
	Matrix<T>& operator*=(const Matrix<T>& rhs);
	template<typename U>
	Matrix<T> transpose();

	// Opera��es matem�ticas de matrizes com escalares
	template<typename U>
	Matrix<T> operator+(const T& rhs);
	template<typename U>
	Matrix<T> operator-(const T& rhs);
	template<typename U>
	Matrix<T> operator*(const T& rhs);
	template<typename U>
	Matrix<T> operator/(const T& rhs);
	template<typename U>
	Matrix<T>& operator+=(const T& rhs);
	template<typename U>
	Matrix<T>& operator-=(const T& rhs);
	template<typename U>
	Matrix<T>& operator*=(const T& rhs);
	template<typename U>
	Matrix<T>& operator/=(const T& rhs);


	// Opera��es matriz/vetor
	template<typename U>
	std::vector<T> operator*(const std::vector<T>& rhs);
	std::vector<T> diagVec();

	// Acessar os elementos individualmente
	T& operator()(const unsigned& row, const unsigned& col);
	const T& operator()(const unsigned& row, const unsigned& col) const;

	unsigned get_rows() const;
	unsigned get_cols() const;
	
};

// Operador de sa�da <<
template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& rhs);
