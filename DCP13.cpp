using namespace std;

#include<algorithm>
#include<array>
#include<iostream>
#include<list>
#include<utility>

struct Frequencies {

private:
	array<int, 26> lower{}, upper{};
	int num_distinct_chars{0};

public:
	void add_character(char a) {
		if(a <= 'z' && a >= 'a') {
			if(!lower[a-'a'])
				num_distinct_chars++;
			lower[a-'a']++;
		}
	}

	void delete_character(char a) {
			if(a <= 'z' && a >= 'a') {
				lower[a-'a']--;
				if(!lower[a-'a'])
					num_distinct_chars--;
			}
		}

	int get_num_distinct_chars() { return num_distinct_chars;}
};

pair<int, int> f(const string& str, int K) {
	int left{0}, right{0};
	int N = str.size();
	int max_len = 0;
	Frequencies frequencies{};
	pair<int,int> substring{0,0};
	while(right < N) {

		while(frequencies.get_num_distinct_chars() == K+1)
			frequencies.delete_character(str[left++]);

//		cout<<"["<<left<<","<<right<<"): "<<str.substr(left, right-left)<<": "<<frequencies.get_num_distinct_chars()<<endl;

		while(frequencies.get_num_distinct_chars() <= K && right < N)
			frequencies.add_character(str[right++]);

//		cout<<"["<<left<<","<<right<<"): "<<str.substr(left, right-left)<<": "<<frequencies.get_num_distinct_chars()<<endl;

		if(frequencies.get_num_distinct_chars() <= K)
			++right;

		if(right-left-1 > max_len) {
			max_len = right - left-1;
			substring.first = left;
			substring.second = right-1;
		}
	}
	return substring;
}

int main() {
	list<pair<string, int>> inputs{{"abcba", 0}, {"", 5}, {"abccbddee", 3}, {"abccbdee", 4}, {"abccbdee", 30}};
	for_each(inputs.begin(), inputs.end(),
			[] (pair<string, int> input) -> void {
		auto result = f(input.first, input.second);
		cout<<"Longest substring of '"<<input.first<<"' with atmost "<<input.second<<
				" distinct characters is ["<<result.first<<","<<result.second<<")='"<<
				input.first.substr(result.first, result.second-result.first)<<"'"<<endl;
	cout<<"-----------------------------------------------------------"<<endl;});
	return 0;
}
