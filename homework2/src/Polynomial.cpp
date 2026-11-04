#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

class Polynomial;

class Term {
	friend Polynomial;
	friend istream& operator>>(istream& is, Polynomial& p);
	friend ostream& operator<<(ostream& os, const Polynomial& p);
private:
	float coef;//係數
	int exp;//指數
};

class Polynomial {
	friend istream& operator>>(istream& is, Polynomial& p);
	friend ostream& operator<<(ostream& os, const Polynomial& p);

private:
	Term* termArray;
	int capacity;//容量
	int terms;//非零項係數
public:
	Polynomial() :capacity(2), terms(0) {
		termArray = new Term[capacity];
	}
	~Polynomial(){
		delete[] termArray;
	}

	Polynomial(const Polynomial& other) : capacity(other.capacity), terms(other.terms) {
		termArray = new Term[capacity];
		copy(other.termArray, other.termArray + terms, termArray);
	}

	Polynomial& operator=(const Polynomial& other) {
		if (this != &other) {
			delete[] termArray;
			capacity = other.capacity;
			terms = other.terms;
			termArray = new Term[capacity];
			copy(other.termArray, other.termArray + terms, termArray);
		}
		return *this;
	}

	void newTerm(const float theCoef, const int theExp);
	Polynomial Add(const Polynomial& b);
	Polynomial Mult(const Polynomial& b);
	float Eval(float f);
};

void Polynomial::newTerm(const float theCoef, const int theExp) {
	if (theCoef == 0)return;
	if (terms == capacity) {
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, termArray + terms, temp);
		delete[]termArray;
		termArray = temp;
	}
	termArray[terms].coef = theCoef;
	termArray[terms++].exp = theExp;
}

Polynomial Polynomial::Add(const Polynomial& b) {
	Polynomial c;
	int aPos = 0, bPos = 0;
	while ((aPos < terms) && (bPos < b.terms)) {
		if (termArray[aPos].exp == b.termArray[bPos].exp) {
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) c.newTerm(t, termArray[aPos].exp);
			aPos++;
			bPos++;
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) {
			c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	for (; aPos < terms; aPos++) c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++) c.newTerm(b.termArray[bPos].coef, termArray[bPos].exp);
	return c;
}

Polynomial Polynomial::Mult(const Polynomial& b) {
	Polynomial c;
	for (int i = 0; i < terms; i++) {
		Polynomial temp;
		for (int j=0; j < b.terms; j++) {
			float coef = termArray[i].coef * b.termArray[j].coef;
			int exp = termArray[i].exp + b.termArray[j].exp;
			temp.newTerm(coef, exp);
		}
		c = c.Add(temp);
	}
	return c;
}
float Polynomial ::Eval(float f) {
	float result = 0.0;
	for (int i = 0; i < terms; i++){
		result += termArray[i].coef * pow(f, termArray[i].exp);
	}
	return result;
}
istream& operator>>(istream& is, Polynomial& p) {
	int n;
	if (!(is >> n)) return is;
	p.terms = 0;
	for (int i = 0; i < n; i++) {
		float coef;
		int exp;
		is >> coef >> exp;
		p.newTerm(coef, exp);
	}
	return is;
}
ostream& operator<<(ostream& os, const Polynomial& p) {
	if (p.terms == 0) {
		os << "0";
		return os;
	}
	for (int i = 0; i < p.terms; i++) {
		float c = p.termArray[i].coef;
		int e = p.termArray[i].exp;
		if (i > 0) {
			if (c > 0) os << " + ";
			else {
				os << " - ";
				c = -c;
			}
		}
		else if (c < 0) {
			os << "-";
			c = -c;
		}
		if (e == 0) {
			os << c;
		}
		else {
			if (c != 1.0f) os << c;
			os << "x";
			if (e != 1) os << "^" << e;
		}
	}
	return os;
}
int main() {
	Polynomial p1, p2;

	cout << "輸入多項式 1 (格式：項數 係數1 次方1 係數2 次方2...):" << endl;
	cout << "例: 輸入 '2 3 2 5 0' 代表 3x^2 + 5" << endl;
	cin >> p1;

	cout << "輸入多項式 2:" << endl;
	cin >> p2;

	cout << "\np1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;

	Polynomial sum = p1.Add(p2);
	cout << "p1 + p2 = " << sum << endl;

	Polynomial prod = p1.Mult(p2);
	cout << "p1 * p2 = " << prod << endl;

	float x = 2.0f;
	cout << "p1 當 x = " << x << " 時的值為: " << p1.Eval(x) << endl;

	return 0;
}
