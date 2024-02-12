#include "Matrix.h"

// Construtor padrão
template<typename T>
Matrix<T>::Matrix(unsigned _rows, unsigned _cols, const T& _initial)
	:rows(_rows),cols(_cols), mat(_rows,std::vector<T>(_cols, _initial))
{
}

// Construtor de cópia
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs)
	:rows(rhs.rows), cols(rhs.cols), mat(rhs.mat)
{
}

// Construtor com lista inicializadora
template<typename T>
Matrix<T>::Matrix(MatrixInit<T> valores)
{
	this->rows = valores.size();

	if (this->rows == 0) {
		this->cols = 0;
	}
	else {
		this->cols = valores.begin()->size();
	}

	for (const auto& linha : valores) {
		if (linha.size() != this->cols) {
			throw std::invalid_argument("Número incorreto de colunas");
		}
		std::vector<T> linhaData;
		for (auto valor : linha) {
			linhaData.push_back(valor);
		}
		this->mat.push_back(linhaData);
	}

}

// Destrutor virtual
template<typename T>
Matrix<T>::~Matrix()
{
}

// Sobrecarga de operador de atribuição
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
	if (&rhs == this)
		return *this;

	unsigned new_rows = rhs.get_rows();
	unsigned new_cols = rhs.get_cols();

	this->mat.resize(new_rows);
	for (unsigned i = 0; i < this->mat.size(); i++) {
		this->mat[i].resize(new_cols);
	}

	for (unsigned i = 0; i < new_rows; i++) {
		for (unsigned j = 0; j < new_cols; j++) {
			this->mat[i][j] = rhs(i, j);
		}
	}
	this->rows = new_rows;
	this->cols = new_cols;

	return *this;
}

// Adição de duas matrizes
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator+(const Matrix<U>& rhs)
{

	if (rhs.get_cols() != this->cols || rhs.get_rows() != this->rows)
		throw std::invalid_argument("As matrizes não podem ser somadas porque são de ordens diferentes.");

	Matrix<decltype(T() + U())> resultante(this->rows, this->cols, decltype(T()+U())());

	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			resultante(i, j) = this->mat[i][j] + rhs(i, j);
		}
	}

	return resultante;
}


// Subtração de duas matrizes
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator-(const Matrix<U>& rhs)
{

	if (rhs.get_cols() != this->cols || rhs.get_rows() != this->rows)
		throw std::invalid_argument("As matrizes não podem ser subtraídas porque são de ordens diferentes.");

	Matrix<decltype(T() + U())> resultante(this->rows, this->cols, decltype(T() + U())());

	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			resultante(i, j) = this->mat[i][j] - rhs(i, j);
		}
	}

	return resultante;
}

// Multiplicação de duas matrizes
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator*(const Matrix<U>& rhs)

{

	if (this->cols != rhs.get_rows())
		throw std::invalid_argument("As matrizes não podem ser multiplicadas porque o número de colunas da primeira é diferente do número de linhas da segunda.");

	unsigned rows = this->rows;
	unsigned cols = rhs.get_cols();

	Matrix<decltype(T() + U())> resultante(rows, cols, decltype(T() + U())());

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			for (unsigned k = 0; k < this->cols; k++) {
				resultante(i, j) += this->mat[i][k] * rhs(k, j);
			}
		}
	}

	return resultante;
}

// Sobrescrição dessa matriz com adição de outra
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator+=(const Matrix<U>& rhs)
{

	if (rhs.get_cols() != this->cols || rhs.get_rows() != this->rows)
		throw std::invalid_argument("As matrizes não podem ser somadas porque são de ordens diferentes.");


	Matrix resultante = (*this) + rhs;
	(*this) = resultante;
	return *this;
}

// Sobrescrição dessa matriz com subtração de outra
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator-=(const Matrix<U>& rhs)
{

	if (rhs.get_cols() != this->cols || rhs.get_rows() != this->rows)
		throw std::invalid_argument("As matrizes não podem ser subtraídas porque são de ordens diferentes.");


	Matrix resultante = (*this) - rhs;
	(*this) = resultante;
	return *this;
}

// Sobrescrição dessa matriz com multiplicação de outra
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator*=(const Matrix<U>& rhs)
{
	if (this->cols != rhs.get_rows())
		throw std::invalid_argument("As matrizes não podem ser multiplicadas porque o número de colunas da primeira é diferente do número de linhas da segunda.");


	Matrix resultante = (*this) * rhs;
	(*this) = resultante;
	return *this;
}

// Cálculo da matriz transposta
template<typename T>
Matrix<T> Matrix<T>::transpose()
{
	unsigned new_rows = this->cols;
	unsigned new_cols = this->rows;

	Matrix resultante(new_rows, new_cols, T());

	for (unsigned i = 0; i < this->get_rows(); i++) {
		for (unsigned j = 0; j < this->get_cols(); j++) {
			resultante(j, i) = this->mat[i][j];
		}
	}

	return resultante;

}

// Adição de matriz com escalar
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator+(const U& rhs)
{
	Matrix<decltype(T()+U())> resultante(this->rows, this->cols, decltype(T() + U())());

	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			resultante(i, j) = this->mat[i][j] + rhs;
		}
	}

	return resultante;
}


// Subtração de matriz com escalar
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator-(const U& rhs)
{
	Matrix<decltype(T() + U())> resultante(this->rows, this->cols, decltype(T() + U())());

	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			resultante(i, j) = this->mat[i][j] - rhs;
		}
	}

	return resultante;
}

// Multiplicação de matriz com escalar
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator*(const U& rhs)
{
	Matrix<decltype(T() + U())> resultante(this->rows, this->cols, decltype(T() + U())());

	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			resultante(i, j) = this->mat[i][j] * rhs;
		}
	}

	return resultante;
}

// Divisão de matriz com escalar
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator/(const U& rhs)
{
	Matrix<decltype(T() + U())> resultante(this->rows, this->cols, decltype(T() + U())());

	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			resultante(i, j) = this->mat[i][j] / rhs;
		}
	}

	return resultante;
}

// Sobrescrição com adição de escalar
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator+=(const U& rhs)
{
	Matrix resultante = (*this) + rhs;

	*this = resultante;

	return resultante;

}

// Sobrescrição com subtração de escalar
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator-=(const U& rhs)
{

	Matrix resultante = (*this) - rhs;

	*this = resultante;

	return resultante;
}

// Sobrescrição com mutliplicação de escalar
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator*=(const U& rhs) 
{

	Matrix resultante = (*this) * rhs;

	*this = resultante;

	return resultante;
}

// Sobrescrição com divisão de escalar
template<typename T>
template<typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator/=(const U& rhs)
{

	Matrix resultante = (*this) / rhs;

	*this = resultante;

	return resultante;
}

// Obter a diagonal do vetor como matriz
template<typename T>
std::vector<T> Matrix<T>::diagVec()
{
	std::vector<T> resultante(this->rows, T());

	for (unsigned i = 0; i < this->rows; i++) {
		resultante[i] = this->mat[i][i];
	}

	return resultante;
}

// Acessar um elemento da matriz
template<typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col)
{
	return this->mat[row][col];
}

// Acessar um elemento de uma matriz constante
template<typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const
{
	return this->mat[row][col];
}

// Getter do número de linhas
template<typename T>
unsigned Matrix<T>::get_rows() const
{
	return this->rows;
}

// Getter do número de colunas
template<typename T>
unsigned Matrix<T>::get_cols() const
{
	return this->cols;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& rhs)
{
	for (unsigned i = 0; i < rhs.get_rows(); i++) {
		for (unsigned j = 0; j < rhs.get_cols(); j++) {
			os << rhs(i, j) << "\t";
		}
		os << std::endl;
	}
	return os;
}

template<typename T, typename U>
Matrix<decltype(T() + U())> operator+(const U& lhs, const Matrix<T>& rhs)
{
	Matrix<decltype(T() + U())> resultante(this->rows, this->cols, decltype(T() + U())());

	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			resultante(i, j) = this->mat[i][j] + rhs;
		}
	}

	return resultante;
}

template<typename T, typename U>
Matrix<decltype(T() + U())> operator*(const U& lhs, const Matrix<T>& rhs)
{
	Matrix<decltype(T() + U())> resultante(this->rows, this->cols, decltype(T() + U())());

	for (unsigned i = 0; i < rhs.get_rows(); i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			resultante(i, j) = this->mat[i][j] * rhs;
		}
	}

	return resultante;
}
