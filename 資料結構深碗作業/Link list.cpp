#include<iostream>
using namespace std;
template <class T>
class ChainNode
{
public:
	T>();
	~T>();
	ChainNode() {};
	ChainNode(const T& data) {
		this->data = data;
	}
	ChainNode(const T& data, chainNode<T>* link) {
		this->data = data;
		this->link = link;
	}

private:
	T data;
	ChainNode<T>* link;
};

template<class T>
class Chain
{
public:
	Chain() { first = 0; }
	~Chain() {
		while (first != NULL) {
			ChainNode<T>* next = first->link;
			delete first;
			first = next;
		}
	}
	bool IsEmpty();
	int IndexOf(const T & theElement)const {
		ChainNode<T>* currentNode = first;
		int index = 0;
		while (currentNode != NULL && currentNode->data != theElement) {
			currentNode = currentNode->link;
			index++;
		}
		if (currentNode == NULL) {
			return -1;
		}
		else {
			return index;
		}
	}
	void Delete(int theIndex) {
		if (first == 0) throw"Cannot delete from empty chain";
		ChainNode<T>* deleteNode;
		if (theIndex == 0) {
			deleteNode = first;
			first = first->link;
		}
		else {
			ChainNode<T>* p = first;
			for (int i = 0; i < theIndex; i++) {
				if (p == 0) throw"Delete element does not exist";
				p = p->next;
			}
			deleteNode = p->link;
			p->link = p->link->link;
		}
		delete deleteNode;
	}
	void Insert(int theIndex, const T& theElement) {
		if (theIndx < 0) throw "Bad insert index";
		else if (theIndex == 0) first = new ChainNode<T>(theElement, first);
		else {
			ChainNode<T>* p = first;
			for (int i = 0; i < theIndex - 1; i++) {
				if (p == 0)throw"Bad insert index";
				p = p->link;
			}
			p->link = new ChainNode<T>(theElement, p->link);
		}
	}
	void display() {
		ChainNode<T>* p = first;
		while (p != NULL) {
			cout << p->data << "->";
			p = p->link;
		}
		cout << "NULL" << endl;
	}
private:
	ChainNode<T>* first;
};

int main() {
	Chain<int> a;
	while (true){
		cout <<" == = Linked list Menu === "<< endl;
		cout << "1.Insert" << endl;
		cout << "2.Delete" << endl;
		cout << "3.InedxOf" << endl;
		cout << "4.Display" << endl;
		cout << "5.Exit" << endl;
	}
}