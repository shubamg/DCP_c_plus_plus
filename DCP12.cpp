#include <iostream>
#include <vector>
#include<initializer_list>

using namespace std;

template <size_t N>
struct Matrix {
	int length;
	vector< vector<int>> rows;

	Matrix(vector<vector<int>>&& _rows): length{N}, rows{_rows} {}

	Matrix<N> operator*(const Matrix<N>& rhs) const {
		Matrix<N> result{vector<vector<int>>{N, vector<int>(N, 0)}};
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
	Matrix<2> m{{{3,4},{5,6}}}, m2{{{1,2},{5,6}}};
	cout<<m<<m2<<(m*m2);
}
