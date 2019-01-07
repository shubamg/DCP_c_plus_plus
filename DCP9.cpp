/*
This problem was asked by Airbnb.
Given a list of integers, write a function that returns the largest sum of non-adjacent numbers. Numbers can be 0 or negative.
For example, [2, 4, 6, 2, 5] should return 13, since we pick 2, 6, and 5. [5, 1, 1, 5] should return 10, since we pick 5 and 5.
Follow-up: Can you do this in O(N) time and constant space?
*/
#include <algorithm>
# include <vector>
# include <list>
# include <iostream>

using namespace std;

int f(const list<int>& v) {
	int n=v.size(), prev_sum{0}, prev_to_prev_sum{0};
	int curr_sum=0;
	for(const int& element: v) {
		curr_sum = max(prev_sum, prev_to_prev_sum + element);
		prev_to_prev_sum = prev_sum;
		prev_sum = curr_sum;
	}
	return curr_sum;
}

ostream &operator<<(ostream &os, const list<int> &m) {
	auto citr = m.cbegin();
	if(citr != m.cend())
		os << (*citr);
	++citr;
	for_each(citr, m.cend(), [&os] (int element) -> void {os<<", "<<element;});
	os << " --> ";
    return os;
}

int main() {
	list<list<int>> input{{1,2,3,4,5}, {2,4,6,2,5}, {}, {-1,-2,-34, -45}, {5, 6}, {10}};
	for_each(input.begin(), input.end(),
			[] (const auto& seq) -> void {cout<<seq<<": "<<f(seq)<<endl;});
	return 0;
}
