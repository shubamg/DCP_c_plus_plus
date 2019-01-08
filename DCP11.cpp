/*
This problem was asked by Twitter.
Implement an autocomplete system. That is, given a query string s and a set of all possible query strings, return all strings in the set that have s as a prefix.
For example, given the query string de and the set of strings [dog, deer, deal], return [deer, deal].
Hint: Try preprocessing the dictionary into a more efficient data structure to speed up queries.
*/
# include <algorithm>
#include <iostream>
# include <list>
# include <unordered_map>
# include <utility>

using namespace std;

using list_t = list<pair<string, unsigned int>>;

struct Node {
	char letter;
	unsigned int num_words_ending;
	unordered_map<char, Node*> children;

	Node(char c): letter{c}, num_words_ending{0}, children{} {}

	list_t get_all_matches (const string& prefix) const {
		// prefix includes my letter
		list_t result{};
		if(num_words_ending)
			result.push_back(make_pair(prefix, num_words_ending));

		for_each(children.begin(), children.end(),
				[&result, &prefix] (pair<char, Node*> node) -> void
				{result.splice(result.end(), node.second->get_all_matches(prefix + node.second->letter));});

		return result;
	}

	list_t find_matches(const string& prefix, unsigned int remaining_index) const {
		if (remaining_index == prefix.size())
			return get_all_matches(prefix);

		auto node = children.find(prefix[remaining_index]);

		if(node == children.end())
			return list_t{};

		return node->second->find_matches(prefix, remaining_index + 1);
	}

	void increment_count() { num_words_ending++;}

	Node* get_child(char c) {
		auto prev_itr = children.find(c);
		if (prev_itr == children.end()) {
			children.insert(make_pair(c, new Node{c}));
		}
		return children[c];
	}
};

struct Trie{
	Node  root;

	Trie(): root{Node{0}} {}
	Trie(Trie&) = delete;
	Trie& operator= (Trie&) = delete;

	list_t find_matches(const string& prefix) const { return root.find_matches(prefix, 0); }

//	~Trie() { delete root;}

	void insert(const string& word) {
		Node* node = &root;
		cout<<"Inserting "<<word<<endl;
		for(char c: word)
			node = node->get_child(c); //cout<<"Node address is "<<node<<" with letter "<<node->letter<<" and count = "<<node->num_words_ending<<endl; }
		node->increment_count();
//		cout<<"Node address is "<<node<<" with letter "<<node->letter<<" and count = "<<node->num_words_ending<<endl;
//		cout<<"------------------------------------------------------------"<<endl;
	}
};

ostream &operator<<(ostream &os, const list_t &result) {
	for_each(result.cbegin(), result.cend(),
			[&os] (pair<string, int> word) -> void
			{os<<word.first<<": "<<word.second<<endl;});
    return os;
}

struct printer {
	Trie& trie;
	void operator()(const string& word) const {
		cout<<"----------------------------------------"<<endl;
		cout<<"Prefix: "<<word<<endl;
		cout<<trie.find_matches(word);
	}
};

int main() {
	Trie trie;
	list<string> inputs{"abc", "abcd", "", "d", "d", "", "abe"};
	for_each(inputs.begin(), inputs.end(),
			[&trie] (string word) -> void {trie.insert(word);});
	list<string> prefixes{"a", "", "ab", "d"};
	for_each(prefixes.begin(), prefixes.end(),printer{trie});
	return 0;
}
