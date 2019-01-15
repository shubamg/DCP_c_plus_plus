using namespace std;

#include<iostream>
#include<chrono>
#include <random>

bool use_new(int n, default_random_engine& dre) {
	return bernoulli_distribution{1.0L/n}(dre);
}

int get_final_index(int n) {
	default_random_engine dre{chrono::system_clock::now().time_since_epoch().count()};
	int answer = 1;
	for(int i=2;i<=n; i++)
		answer = (use_new(i, dre)?i:answer);
	return answer-1;
}

int main() {

	int number_of_tries = 1000000;
	int permutation_size = 50;
	vector<int> frequency(permutation_size, 0);
	for(int i=1;i<number_of_tries; ++i)
		frequency[get_final_index(permutation_size)]++;

	for(int i=0; i<permutation_size; i++)
		cout<<i<<": "<< (frequency[i] * 100.0/number_of_tries)<<endl;

	return 0;
}
