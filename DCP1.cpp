/*
This problem was recently asked by Google.
Given a list of numbers and a number k, return whether any two numbers from the list add up to k.
For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.
Bonus: Can you do this in one pass?
*/

#include<algorithm>
#include<list>
#include<iostream>
#include <tuple>
#include <utility>
#include <unordered_set>

using namespace std;

tuple<bool,long,long> predicate(const list<long>& input,const long K) {
	unordered_set<long> numbers{};
	for(auto& current_num: input) {
		auto itr = numbers.find(K-current_num);
		if (itr!= numbers.end())
			return make_tuple(true, K-current_num, current_num);
		numbers.insert(current_num);
	}
	return make_tuple(false, 0L, 0L);
}

void print_list(const list<long>& input) {
	auto const_itr = input.begin();
	if(const_itr != input.end()) {
		cout<<(*const_itr);
		++const_itr;
	}
	for_each(const_itr, input.end(), [] (long number) -> void {cout<<", "<<number;});
}

void print(const list<long>& input, const long K) {
	print_list(input);
	cout<<": "<<K<<" -> ";
	auto answer = predicate(input, K);
	if(get<0>(answer))
		cout<<K<<"="<<get<1>(answer)<<"+"<<get<2>(answer)<<endl;
	else
		cout<<"Not possible"<<endl;
}

int main() {
	list<pair<list<long>, long>> inputs{
		{{1L,2L,300L},4L},
		{{100L, 56L, 67L}, 156L},
		{{123456L, 345L, 640L, 640L}, 640*2L},
		{{}, 400L}};
	for(auto& input : inputs)
		print(input.first, input.second);
	return 0;
}


