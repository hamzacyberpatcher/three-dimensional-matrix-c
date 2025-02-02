#include <iostream>
#include <iomanip>
#include <vector>

template <class T>
class Matrix3d
{
	T *** m_matrix = nullptr;
	size_t m_i = 0;
	size_t m_j = 0;
	size_t m_k = 0;

	void allocatememory()
	{
		m_matrix = new T**[m_i];
		for(size_t i = 0; i < m_i; i++)
		{
			m_matrix[i] = new T*[m_j];
			for(int j = 0; j < m_j; j++)
				m_matrix[i][j] = new T[m_k];
		}
	}

public:
	Matrix3d() {}
	Matrix3d(const size_t i, const size_t j, const size_t k) : m_i(i), m_j(j), m_k(k)
	{
		allocatememory();
	}
	Matrix3d(const std::vector<std::vector<std::vector<T>>>& mat)
	{
		m_i = mat.size();
		m_j = mat[0].size();
		m_k = mat[0][0].size();

		allocatememory();

		for(size_t i = 0; i < m_i; i++)
			for(size_t j = 0; j < m_j; j++)
				for(size_t k = 0; k < m_k; k++)
					m_matrix[i][j][k] = mat[i][j][k];
	}
	Matrix3d(const Matrix3d<T>& mat)
	{
		m_i = mat.m_i;
		m_j = mat.m_j;
		m_k = mat.m_k;

		allocatememory();

		for(size_t i = 0; i < m_i; i++)
			for(size_t j = 0; j < m_j; j++)
				for(size_t k = 0; k < m_k; k++)
					m_matrix[i][j][k] = mat[i][j][k];
	}
	Matrix3d(T *** mat, size_t i, size_t j, size_t k) : m_i(i), m_j(j), m_k(k)
	{
		allocatememory();

		for(size_t i = 0; i < m_i; i++)
			for(size_t j = 0; j < m_j; j++)
				for(size_t k = 0; k < m_k; k++)
					m_matrix[i][j][k] = mat[i][j][k];
	}
	~Matrix3d()
	{
		for(size_t i = 0; i < m_i; i++)
		{
			for(size_t j = 0; j < m_j; j++)
			{
				delete [] m_matrix[i][j];
				m_matrix[i][j] = nullptr;
			}
			delete [] m_matrix[i];
			m_matrix[i] = nullptr;
		}
		m_matrix = nullptr;
		m_i = m_j = m_k = 0;
	}
	Matrix3d<T> operator=(const std::vector<std::vector<std::vector<T>>>& mat)
	{
		if (m_matrix != nullptr)
		{
			for(size_t i = 0; i < m_i; i++) for(size_t j = 0; j < m_j; j++) delete [] m_matrix[i][j];
			for(size_t i = 0; i < m_i; i++) delete [] m_matrix[i];
			delete [] m_matrix;
		}
		m_i = mat.size();
		m_j = mat[0].size();
		m_k = mat[0][0].size();

		allocatememory();

		for(size_t i = 0; i < m_i; i++)
			for(size_t j = 0; j < m_j; j++)
				for(size_t k = 0; k < m_k; k++)
					m_matrix[i][j][k] = mat[i][j][k];
	}
	Matrix3d<T> operator=(const Matrix3d<T>& mat)
	{
		if (this == &mat)
		{
			return *this;
		}
		if (m_matrix != nullptr)
		{
			for(size_t i = 0; i < m_i; i++) for(size_t j = 0; j < m_j; j++) delete [] m_matrix[i][j];
			for(size_t i = 0; i < m_i; i++) delete [] m_matrix[i];
			delete [] m_matrix;
			m_matrix = nullptr;
		}
		m_i = mat.m_i;
		m_j = mat.m_j;
		m_k = mat.m_k;

		allocatememory();

		for(size_t i = 0; i < m_i; i++)
			for(size_t j = 0; j < m_j; j++)
				for(size_t k = 0; k < m_k; k++)
					m_matrix[i][j][k] = mat[i][j][k];

		return *this;
	}

	T** operator[](size_t i)
	{
		return m_matrix[i];
	}

	const T* const * operator[](size_t i) const
	{
		return m_matrix[i];
	}

	Matrix3d<T> operator+(const Matrix3d<T>& mat)
	{
		if (m_i != mat.m_i || m_j != mat.m_j || m_k != mat.m_k)
			return Matrix3d<T>();

		Matrix3d<T> result(m_i, m_j, m_k);

		for(size_t i = 0; i < m_i; i++)
			for(size_t j = 0; j < m_j; j++)
				for(size_t k = 0; k < m_k; k++)
					result[i][j][k] = m_matrix[i][j][k] + mat[i][j][k];

		return result;
	}

	Matrix3d<T> operator-(const Matrix3d<T>& mat)
	{
		if (m_i != mat.m_i || m_j != mat.m_j || m_k != mat.m_k)
			return Matrix3d<T>();

		Matrix3d<T> result(m_i, m_j, m_k);

		for(size_t i = 0; i < m_i; i++)
			for(size_t j = 0; j < m_j; j++)
				for(size_t k = 0; k < m_k; k++)
					result[i][j][k] = m_matrix[i][j][k] - mat[i][j][k];

		return result;
	}

	void display() const
	{
		for(size_t i = 0; i < m_i; i++)
		{
			for(size_t k = 0; k < m_k; k++)
			{
				for(size_t j = 0; j < m_j; j++)
				{
					std::cout << std::setw(3 + k + 1) << m_matrix[i][j][k] << "\t";
				}
				std::cout << std::endl;
			}
		}
	}

	size_t getI() const
	{
		return m_i;
	}

	size_t getJ() const
	{
		return m_j;
	}

	size_t getK() const
	{
		return m_k;
	}

};



template <class T, class S>
Matrix3d<T> operator*(const Matrix3d<T>& mat, const S scalar)
{
	Matrix3d<T> result(mat.getI(), mat.getJ(), mat.getK());

	for(size_t i = 0; i < mat.getI(); i++)
		for(size_t j = 0; j < mat.getJ(); j++)
			for(size_t k = 0; k < mat.getK(); k++)
				result[i][j][k] = static_cast<T>(mat[i][j][k] * scalar);

	return result;
}

template <class T, class S>
Matrix3d<T> operator*(const S scalar, const Matrix3d<T>& mat)
{
	Matrix3d<T> result(mat.getI(), mat.getJ(), mat.getK());

	for(size_t i = 0; i < mat.getI(); i++)
		for(size_t j = 0; j < mat.getJ(); j++)
			for(size_t k = 0; k < mat.getK(); k++)
				result[i][j][k] = static_cast<T>(mat[i][j][k] * scalar);

	return result;
}

template <class T, class S>
Matrix3d<T> operator/(const Matrix3d<T>& mat, const S scalar)
{
	Matrix3d<T> result(mat.getI(), mat.getJ(), mat.getK());

	for(size_t i = 0; i < result.getI(); i++)
		for(size_t j = 0; j < mat.getJ(); j++)
			for(size_t k = 0; k < mat.getK(); k++)
				result[i][j][k] = static_cast<T>(mat[i][j][k] / scalar);

	return result;
}

int main()
{
	std::vector<std::vector<std::vector<int>>> mat = {
												 {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}},
												 {{17,18,19,20},{21,22,23,24},{25,26,27,28},{29,30,31,32}},
												 {{33,34,35,36},{37,38,39,40},{41,42,43,44},{45,46,47,48}},
												 {{49,50,51,52},{53,54,55,56},{57,58,59,60},{61,62,63,64}}
												};


	Matrix3d<int> mat3d = mat;
	Matrix3d<int> mat2 = mat3d + mat3d;

	mat2 = mat2 * 2;

	Matrix3d<int> mat3 = mat2 - mat3d;

	mat3 = mat3 / 3;

	mat3.display();


	return 0;
}
