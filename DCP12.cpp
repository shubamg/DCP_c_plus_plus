#include <algorithm>
#include <iostream>
# include <tuple>
#include <vector>

using namespace std;

using tuple_of_3 = tuple<vector<int>, vector<int>, vector<int>>;

template <size_t N>
struct Matrix;

template <size_t N>
Matrix<N> get_identity();

template <size_t N>
struct Matrix {
	size_t length;
	vector<vector<int>> rows;

	Matrix(): length{N}, rows{vector<vector<int>>(length, vector<int>(length, 0))} {}

	Matrix(const vector<vector<int>>& _rows): length{N}, rows{_rows} {}

	Matrix(const vector<int>& seq): Matrix{} {
		rows[0] = seq;
		for(int i=1; i<length; i++)
			rows[i][i-1]=1;
	}

	Matrix<N> operator*(const Matrix<N>& rhs) const {
		Matrix<N> result{vector<vector<int>>{N, vector<int>(N, 0)}};
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				for(int k=0;k<N; k++)
					result.rows[i][j]+= rows[i][k]*rhs.rows[k][j];
		return result;
	}

	vector<int> operator*(const vector<int> v) const {
		vector<int> result(N,0);
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				result[i] += (this->rows[i][j] * v[j]);
		return result;
	}

	Matrix<N> operator^(int exponent) const {
		if (!exponent)
			return get_identity<N>();
		if(exponent == 1)
			return *this;
		Matrix<N> temp = (*this)^(exponent>>1);
		temp = temp * temp;
		if(exponent & 1)
			temp = temp * (*this);
		return temp;
	}
};

template <size_t N>
Matrix<N> get_identity() {
	int len = N;
	Matrix<N> result{};
	for(int i=0;i<N;i++)
		result.rows[i][i]=1;
	return result;
}

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

ostream &operator<<(ostream &os, const vector<int> &result) {
	for(int i=0;i<result.size(); i++)
			cout<<result[i]<<" ";
	cout<<endl;
    return os;
}

template <size_t N>
void process_input(tuple_of_3 input) {
	// tuple.first is the first row of matrix. It has size N
	// tuple.second is the initial seq a_{N-1}, a_{N-2}, ..., a_1, a_0
	// tuple.third are the indexes for which result is desired
	cout<<"--------------------------------------------"<<endl;
	cout<<"Recurrence relation coefficients are: "<<get<0>(input);
	cout<<"Initial conditions are: "<<get<1>(input);
	cout<<"The sequence elements are:"<<endl;
	for_each(get<2>(input).cbegin(), get<2>(input).cend(),
			[&base_seq=get<0>(input), &initial_seq=get<1>(input)] (int index) -> void
			{cout<<index<<": "<<(((Matrix<N>{base_seq} ^ index)* initial_seq)[N-1])<<endl;});
}

int main() {
	tuple_of_3 input1{{1, 1}, {1,1}, {0,1,2,3,4,10,20}};
	tuple_of_3 input2{{1,0,1,0,1}, {3,2,1,1,1}, {0,1,2,3,4,5,6,7,8,9,10}};
	process_input<2>(input1);
	process_input<5>(input2);
	return 0;
}
