/*
This problem was asked by Facebook.
Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, count the number of ways it can be decoded.
For example, the message '111' would give 3, since it could be decoded as 'aaa', 'ka', and 'ak'.
You can assume that the messages are decodable. For example, '001' is not allowed.
*/
using namespace std;
#include <algorithm>
# include <iostream>
#include <list>
int f(const string& input) {
	if (input.empty())
		return 1;
	int f_next_to_next = 1, f_next = 1, f_current = 1;
	for(auto rev_itr = input.rbegin()+1; rev_itr != input.rend(); rev_itr++) {
		if (*rev_itr == '0')
			f_current = 0;
		else if((*rev_itr - '0') <= 9 && (*rev_itr - '0') > 2 )
			f_current = f_next;
		else if((*rev_itr - '0') == 2)
			f_current = f_next + f_next_to_next * ((*rev_itr - '0') <= 6);
		else if ((*rev_itr - '0') == 1)
			f_current = f_next + f_next_to_next;
		else
			throw "Non numeric character found in encoding";
		f_next_to_next = f_next;
		f_next = f_current;
	}
	return f_current;
}

int main() {
	list<string> inputs{"111", "123456", "", "1", "12123456", "602", "1020", "def"};
	for_each(inputs.begin(), inputs.end(),
			[] (const string& input) -> void {cout<<input<<": "<<f(input)<<endl;});
	return 0;
}
