#include <iostream>
#include <array>

using namespace std;

template <size_t N>
ostream &operator<<(ostream &os, const array<int, N>& result) {
	for(int i=0;i<N; i++)
		os<<result[i]<<" ";
	os<<endl<<"--------------------------------------------"<<endl;
    return os;
}

template <size_t N>
struct Matrix {
	int length;
	array< array<int, N>, N> rows;

	Matrix(array<array<int, N>, N>&& _rows): length{N}, rows{_rows} {}

	Matrix<N> operator*(const Matrix<N>& rhs) const {
		Matrix<N> result{array<array<int, N>, N>{}};
//		cout<<(*this);
//		cout<<rhs;
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				for(int k=0;k<N; k++) {
//					cout<<"result["<<i<<"]["<<j<<"] was "<<result.rows[i][j]<<" before."<<endl;
//					cout<<"lhs["<<i<<"]["<<k<<"]*rhs["<<k<<"]["<<j<<"]="<<rows[i][k]
//					  <<"*"<<rhs.rows[k][j]<<"="<<rows[i][k]*rhs.rows[k][j]<<endl;
					result.rows[i][j]+= rows[i][k]*rhs.rows[k][j];
//					cout<<"result["<<i<<"]["<<j<<"] is "<<result.rows[i][j]<<" now."<<endl;
//					cout<<"--------------------------------------------"<<endl;
				}
		return result;
	}

	array<int, N> operator*(const array<int, N>& rhs) const {
		array<int, N> result{};
	//		cout<<(*this);
	//		cout<<rhs;
			for(int i=0; i<N; i++)
				for(int j=0; j<N; j++)
					result[i]+= rows[i][j]*rhs[j];
			return result;
		}
};

template <size_t N>
ostream &operator<<(ostream &os, const Matrix<N> &result) {
	for(int i=0;i<N; i++) {
		for(int j=0;j<N;j++)
			cout<<result.rows[i][j]<<" ";
		cout<<endl;
	}
	cout<<"--------------------------------------------"<<endl;
    return os;
}



int main() {
	Matrix<2> m{{3,4,5,6}}, m2{{1,2,5,6}};
	Matrix<2> prod = m * m2;
//	cout<<m<<m2<<prod;
	array<int, 2> vec{{1,3}};
	cout<<prod<<vec;
	cout<<(prod*vec);
}
