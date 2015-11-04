/*
 * single.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: sebis
 */

#include <iostream>

using namespace std;

class List {
	struct Node {
		int payload;
		Node* next;
		Node(int p, Node* n=nullptr): payload(p), next(n) {}
	};
	Node* first = nullptr;
public:
	List() = default;
	void put(int x) {
		Node* apa = new Node(x, first);
		first = apa;
	}
	int get() {

		int ret = first->payload;
		Node* apa = first;
		first = first->next;
		delete apa;
		return ret;
	}
	bool empty() const {
		return first == nullptr? true : false;
	}
};

int main() {
	List lst;
	for (int k=1; k<=10; ++k) {
		lst.put(k*2);
	}
	while (!lst.empty()) {
		cout << lst.get() << endl;
	}
}


