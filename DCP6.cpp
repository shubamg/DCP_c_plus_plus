using namespace std;
#include <iostream>

#define INF -1
class Node {
public:
	Node(int val, Node * prev, Node * next): val{val}, xor_addr{(uintptr_t)prev ^ (uintptr_t)next} {}
	void set_xor_addr(uintptr_t val) { xor_addr = val;}
	uintptr_t get_xor_addr() { return xor_addr;}
	int val;
private:
	uintptr_t xor_addr;
};

class List {
public:
	List(): tail(new Node{INF, 0, 0}), head{tail}, size{0} {//cout<<"size = "<<size<<" head  = "<<head<<endl;
}
	void append(int val) {
		Node * prev = (Node *)tail->get_xor_addr();
		Node* tempNode = new Node{val, prev, tail};
		tempNode->set_xor_addr((uintptr_t)prev ^ (uintptr_t)tail);
		cout<<"Appending "<<val<<" to list "<<endl;
		if(size)
			prev->set_xor_addr((prev->get_xor_addr() ^ (uintptr_t)tail) ^ (uintptr_t)tempNode);
		else
			head = tempNode;
		tail->set_xor_addr((uintptr_t) tempNode);
		++size;
		if(size)
			get(size-1);
	}

	int get(unsigned int index) {
		if (index >= size || index < 0)
			throw "index out of bounds";
		uintptr_t prev = 0;
		uintptr_t curr = (uintptr_t)head;
		uintptr_t temp;
		for(int itr = 0; itr < index; ++itr) {
			temp = curr;
			curr = ((Node*)curr)->get_xor_addr() ^ prev;
			prev = temp;
		}
		return ((Node*)curr)->val;
	}

	List(const List &) = delete;
	List(const List &&) = delete;
	List& operator= (const List &) = delete;
	List& operator= (const List &&) = delete;

	~List() {
		uintptr_t prev = 0;
		uintptr_t curr = (uintptr_t)head;
		uintptr_t temp;
		for(int itr = 0; itr <= size; ++itr) {
			delete [] (Node *)curr;
			temp = curr;
			curr = ((Node*)curr)->get_xor_addr() ^ prev;
			prev = temp;
		}
	}
	unsigned int size{0};

private:
		Node * tail, * head;
};

int main() {
	List list{};
	list.append(120);
	list.append(130);
	cout<<"0: "<<list.get(0)<<endl;
	list.append(150);
	cout<<"2: "<<list.get(2)<<endl;
	list.append(45);
	cout<<"4: "<<list.get(3)<<endl;
	cout<<"5: "<<list.get(5)<<endl;
}
