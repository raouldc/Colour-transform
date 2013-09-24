#include "matrixops.h"

#include <stdexcept>
#include <cmath>

Matrixf multiply(Matrixf const& left, Matrixf const& right) {

	// error check
	if (left.ncols() != right.nrows()) {
		throw std::runtime_error("Unable to multiply: matrix dimensions not agree.");
	}

	/** implement matrix/vector multiplication ********************/
	Matrixf ret(left.nrows(), right.ncols());
	int sum=0;
	for(unsigned int i=0;i<left.nrows();i++)
	{
		for(unsigned int j=0;j<right.ncols();j++)
		{
			for(unsigned int k=0;k<right.nrows();k++)
			{
				sum+=left(i,k)*right(k,j);
			}
			ret(i,j)=sum;
			sum=0;
		}
	}
	return ret;
}

Matrixf multiply(Matrixf const& mat, float scalar) {

	/** implement matrix/vector multiplication ********************/
	Matrixf result(mat.nrows(), mat.ncols());

	for(unsigned int i=0;i<mat.nrows();i++)
	{
		for(unsigned int j=0;j<mat.ncols();j++)
		{
			result(i,j)=mat(i,j)*scalar;
		}
	}
	return result;
}

Matrixf multiply(float scalar, Matrixf const& mat) {
	return multiply(mat, scalar);
}

float dot(Matrixf const& vec1, Matrixf const& vec2) {

	// error check
	if (!vec1.isVector() || !vec2.isVector()) {
		throw std::runtime_error("Unable to do dot product: not column vectors.");
	}
	if (vec1.nrows() != vec2.nrows()) {
		throw std::runtime_error("Unable to do dot product: vector lengths not equal.");
	}

	float ret = 0;

	/** implement dot product *************************************/
	for(unsigned int i=0;i<vec1.nrows();i++)
	{
		ret+=vec1(i,0)*vec2(i,0);
	}
	return ret;
}

Matrixf cross(Matrixf const& vec1, Matrixf const& vec2) {

	// error check
	if (!vec1.isVector() || !vec2.isVector()) {
		throw std::runtime_error("Unable to do dot product: not column vectors.");
	}
	if (vec1.nrows() != 3 || vec2.nrows() != 3) {
		throw std::runtime_error("Unable to do cross product: vector lengths not 3.");
	}

	/** implement cross product ***********************************/




	Matrixf ret(1, 1);

	return ret;
}

// Sample implementation of matrix addition
Matrixf add(Matrixf const& mat1, Matrixf const& mat2) {

	// error check
	if (mat1.ncols() != mat2.ncols() ||
		mat1.nrows() != mat2.nrows())
	{
		throw std::runtime_error("Unable to add 2 matrix together: dimensions not identical.");
	}

	Matrixf result(mat1.nrows(), mat1.ncols());
	for (unsigned int r = 0; r < mat1.nrows(); ++r) {
		for (unsigned int c = 0; c < mat1.ncols(); ++c) {
			result(r, c) = mat1(r, c) + mat2(r, c);
		}
	}

	return result;
}

Matrixf transpose(Matrixf const& mat) {
	Matrixf result(mat.ncols(), mat.nrows());

	for (unsigned int r = 0; r < mat.nrows(); ++r) {
		for (unsigned int c = 0; c < mat.ncols(); ++c) {
			result(c, r) = mat(r, c);
		}
	}

	return result;
}

// Computes the length (L2 norm) of a vector
float length(Matrixf const& v) {
	// error check
	if (!v.isVector()) {
		throw std::runtime_error("Not a vector.");
	}

	float result = 0.0f;

	for (unsigned int r = 0; r < v.nrows(); ++r) {
		result += v(r, 0) * v(r, 0);
	}

	return std::sqrtf(result);
}
