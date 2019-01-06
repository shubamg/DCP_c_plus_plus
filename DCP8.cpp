#include <iostream>
#include <set>
#include <utility>

using namespace std;
/*
This problem was asked by Google.
A unival tree (which stands for "universal value") is a tree where all nodes under it have the same value.
Given the root to a binary tree, count the number of unival subtrees.
For example, the following tree has 5 unival subtrees:
   0(A)
  / \
 1   0 (B,C)
    / \
   1   0 (D,E)
  / \
 1   1 (F,G)
*/


struct Node {
	string name;
	Node * left;
	Node * right;
	int value;

	Node (int val, const string& name): name{name}, left{nullptr}, right{nullptr}, value{val} {}
	Node (Node &) = delete;
	Node (Node &&) = delete;
	Node& operator= (Node &) = delete;
	Node& operator = (Node &&) = delete;
	~Node() {
		cout<<"Begin destructor call on "<<name<<endl;
		if(left) {
			string name = left->name;
			cout<<"Deleting "<<name<<endl;
			delete  left;
			cout<<"Deleted "<<name<<endl;
		}
		if(right) {
			string name = right->name;
			cout<<"Deleting "<<name<<endl;
			delete right;
			cout<<"Deleted "<<name<<endl;
		}
		cout<<"End destructor call on "<<name<<endl;
	}
	static bool is_unival(Node * node) {
		if (!node)
			return true;
		if (!(is_unival(node->left) && is_unival(node->right)))
			return false;
		set<int> temp{node->value};
		if(node->left)
			temp.insert(node->left->value);
		if(node->right)
			temp.insert(node->right->value);
		return (temp.size() == 1);
	}

	static int get_num_unival_nodes(Node * subtree_root) {
		if (!subtree_root)
			return 0;
		return  get_num_unival_nodes(subtree_root->left) +
				get_num_unival_nodes(subtree_root->right) +
				is_unival(subtree_root);
	}

	Node* insert_left_child(int val, const string& name){
		if(left)
			delete left;
		left = new Node{val, name};
		return left;
	}

	Node* insert_right_child(int val, const string& name){
			if(right)
				delete right;
			right = new Node{val, name};
			return right;
		}
};

class Tree {
private:
	Node * root;
public:
	Tree(int val, const string& name): root{new Node{val, name}} {}
	~Tree() { delete  root;}
	Node * get_root() { return root;}
	int get_num_unival_nodes() { return root->get_num_unival_nodes(root); }
};

int main() {
	Tree tree{0, "a"};
	string F = "f";
	auto a = tree.get_root();
	auto b = a->insert_left_child(1, "b");
	auto c = a->insert_right_child(0, "c");
	auto d = c->insert_left_child(1, "d");
	auto e = c->insert_right_child(0, "e");
	auto f = d->insert_left_child(1, F);
	auto g = d->insert_right_child(1, "g");
//	auto c1 = a->insert_right_child(0, "c1");
	cout<<tree.get_num_unival_nodes()<<endl;
	return 0;
}
