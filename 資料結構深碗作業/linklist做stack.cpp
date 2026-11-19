#include<iostream>
using namespace std;

template<class T>
class Chain;

template <class T>
class ChainNode {
	friend class Chain<T>;
private:
	T data;
	ChainNode<T>* link;
public:
	ChainNode(){}
	ChainNode(const T& data) {
		this->data = data;
	}
	ChainNode(const T& data, ChainNode<T>* link) {
		this->data = data;
		this->link = link;
	}
};

template<class T>
class Chain {
public:
	Chain() { first = nullptr; }
	~Chain() {};
	Chain(int stackCapacity = 10);
	bool IsEmpty()const { return first == 0; }
	T& Top()const;
	void Push(const T& item);
	void pop();
private:
	ChainNode<T>* first;
};

template<class T>
Chain<T>::~Chain() {
	while (first!=nullptr){
		ChainNode<T>* nextNode = first->link;
		delete first;
		first = nextNode;
	}
}

template<class T>
inline T& Chain<T>::Top() const {
	if (IsEmpty())throw "Stack is empty";
	return stack[top];
}

template<class T>
void Chain<T>::Push(const T& item) {
	
}

template<class T>
void Chain<T>::pop() {
	if (IsEmpty())throw "Stack is empty. Cannot delete.";
	Chain[top--].~T();
}

int main() {
	Chain o;
	cout << "-- - Stack目錄---" << endl;
	cout << "1.Push" << endl;
	cout << "2.Pop" << endl;
	cout << "3.Top" << endl;
	cout << "4.IsEmpty" << endl;
	cout << "5.Display" << endl;
	cout << "6.Exit" << endl;
	
	int n;
	while (1) {
		cout << "Choice : ";
		cin >> n;
		switch (n)
		{
		case 1: {

			break;
		}
		case 2: {

			break;
		}
		case 3: {

			break;
		}
		case 4: {

			break;
		}
		case 5: {

			break;
		}
		case 6: {

			break;
		}
		default:
			break;
		}
	}
}
