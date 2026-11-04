# 41443149
### 題目 多項式
## 解題說明

1.問題描述:
 - 要做出多項式可以相加，相乘，還有求點的距離，並依照作業圖片做出polynomial和term的類別
 - 一開始給的記憶體空間是固定大小如果超過沒辦法算答案
2.解題策略
 - newTerm函式，以解決記憶體空間是固定的問題，判斷多項式次方的大小原本記憶體空間比次方最大項小的話就把記憶體乘以二，然後把舊陣列的數值一道新陣列
 - add函式，判斷次方一樣相加，不一樣的再判斷
 - mult函式，計算次方相乘係數相加，乘完同次方的去add函式相加
 - eval函式，帶入x值計算出答案
 - 最後再用函式多載出入輸出
 
## 程式實作

```cpp
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
```

## 效能分析
| 函式 | 時間複雜度 | 空間複雜度 | 說明 |
|----------|--------------|----------|----------|
| 建構子、解構子              |   O(1) 					   | O(1)                 | 僅配置大小為 2 的固定陣列並初始化變數。 執行 delete[] termArray 釋放動態記憶體。      |
| 拷貝建構子、拷貝指派運算子   |  O(n)  					   | O(n)                | 需動態配置長度為 capacity 的陣列，並複製 n個項目。釋放舊記憶體後重新配置，並複製 n 個項目。        |
| newTerm                    |   均攤 O(1) / 最差 O(m)      | O(1) (擴容時暫時 O(m))   | 陣列未滿時直接插入為 O(1)；滿時倍增擴容需複製 m 個元素，均攤（Amortized）為 O(1)。        |
| Add                        |   O(m + n) 					| O(m + n)              |採雙指針依序掃描兩多項式，最多走訪 m + n 次；回傳的新多項式最多含 m + n項。       |
| Mult                       |   O(m^2*n)     				| O(m + n)             | 5        | 
| Eval                        |   O(m)      				| O(1)                   | 單層迴圈走訪 m 個項目，各項進行一次常數時間的乘方與相乘。        | 
| 輸入運算子 operator>>       |   均攤 O(k)  				| O(k)              | 讀入 k個項目並呼叫 k 次 newTerm，均攤時間為 O(k)，新配置儲存 k項的空間。       | 
| 輸出運算子 operator<<       |   O(m)            			| O(1)                   | 單層迴圈走訪m個項目並依格式印出，無動態配置額外空間。       | 

## 測試與驗證
| 測試案例 | 輸入多項式p1 | 輸入多項式p2 | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|----------|
| 測試一   |   2 3 2 5 0  | 1 1 1 0   | 1        | 1        |
| 測試二   |   (1,3)      | 5        | 5        | 1        |
| 測試三   |   (2,2)      | 7        | 7        | 1        |

## 申論及開發報告

