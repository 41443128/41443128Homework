# 41443128

作業二

## 解題說明

## 解題說明

本題要求實作Polynomial類別，用來儲存及計算多項式，並完成多項式的輸入、輸出、相加、相乘以及帶入 x 求值。

### 解題策略

1. 使用 Term 類別儲存多項式每一項的係數 coef 和指數 exp。
2. 使用動態陣列 termArray 儲存多項式中的所有項目，當容量不足時將陣列大小增加為原本的兩倍。
3. 使用 Add() 完成兩個多項式的相加。
4. 使用 Mult() 將兩個多項式中的每一項互相相乘。
5. 使用 Eval() 將 x 的值帶入多項式中計算結果。
6. 使用 << 和 >> 運算子完成多項式的輸入與輸出。
7. 主程式利用選單讓使用者選擇相加、相乘、帶入 x 或結束程式。

```markdown
## 程式實作

以下為主要程式碼：

```cpp
#include<iostream>
using namespace std;

class Polynomial;

class Term {
	friend class Polynomial;
	friend ostream& operator<<(ostream& out, const Polynomial& p);
private:
	float coef;
	int exp;
};

class Polynomial {

private:
	Term* termArray;
	int capacity;
	int terms;
public:
	Polynomial() :capacity(2), terms(0) {
		termArray = new Term[capacity];
	}
	void newTerm(const float theCoef, const int theExp);
	Polynomial Add(const Polynomial& b);
	Polynomial Mult(const Polynomial& b);
	float Eval(float x);
	friend ostream& operator<<(ostream& out, const Polynomial& p);
	friend istream& operator>>(istream& in, Polynomial& p);
};

void Polynomial::newTerm(const float theCoef, const int theExp) {
	if (theCoef == 0) return;
	if (terms == capacity) {
		capacity *= 2;
		Term* temp = new Term[capacity];
		for (int i = 0; i < terms; i++) {
			temp[i] = termArray[i];
		}
		delete[]termArray;
		termArray = temp;
	}
	termArray[terms].coef = theCoef;
	termArray[terms].exp = theExp;
	terms++;
}

Polynomial Polynomial::Add(const Polynomial& b) {
	Polynomial c;
	int aPos = 0, bPos = 0;
	while ((aPos < terms) && (bPos < b.terms))
		if (termArray[aPos].exp == b.termArray[bPos].exp) {
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) c.newTerm(t, termArray[aPos].exp);
			aPos++;bPos++;
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) {
			c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}

	for (; aPos < terms; aPos++)
		c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++)
		c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}

Polynomial Polynomial::Mult(const Polynomial& b) {
	Polynomial c;
	for (int i = 0; i < terms; i++) {
		for (int j = 0; j < b.terms; j++) {
			float newCoef =
				termArray[i].coef * b.termArray[j].coef;
			int newExp =
				termArray[i].exp + b.termArray[j].exp;
			int same = -1;
			for (int k = 0; k < c.terms; k++) {
				if (c.termArray[k].exp == newExp) {
					same = k;
					break;
				}
			}
			if (same != -1) {
				c.termArray[same].coef += newCoef;
			}
			else {
				c.newTerm(newCoef, newExp);
			}
		}
	}
	return c;
}

float Polynomial::Eval(float x) {
	float answer = 0;
	for (int i = 0; i < terms; i++) {
		float power = 1;
		for (int j = 0; j < termArray[i].exp; j++) {
			power *= x;
		}
		answer += termArray[i].coef * power;
	}
	return answer;
}

istream& operator>>(istream& in, Polynomial& p) {
	int n;
	cout << "輸入項數: ";
	in >> n;
	for (int i = 0; i < n; i++) {
		float coef;
		int exp;
		cout << "輸入係數和指數: ";
		in >> coef >> exp;
		p.newTerm(coef, exp);
	}
	return in;
}

ostream& operator<<(ostream& out, const Polynomial& p) {
	for (int i = 0; i < p.terms; i++) {
		if (i > 0 && p.termArray[i].coef > 0)
			out << " + ";
		if (p.termArray[i].coef < 0)
			out << " - ";
		float c = p.termArray[i].coef;
		if (c < 0)
			c = -c;
		out << c;
		if (p.termArray[i].exp > 0) {
			out << "x";
			if (p.termArray[i].exp > 1)
				out << "^" << p.termArray[i].exp;
		}
	}
	return out;
}

int main() {
	Polynomial a;
	Polynomial b;
	cout << "多項式 A:" << '\n';
	cin >> a;
	cout << "多項式 B:" << '\n';
	cin >> b;
	cout << '\n';
	cout << "A = " << a << '\n';
	cout << "B = " << b << '\n';
	int choice;
	while (true){
	    cout << "\n==========選單==========" << '\n';
	    cout << "1. 相加" << '\n';
	    cout << "2. 相乘" << '\n';
	    cout << "3. 帶入 x" << '\n';
	    cout << "4. 結束" << '\n';
	    cin >> choice;
	    if (choice == 1) {
	    	Polynomial c = a.Add(b);
	    	cout << "A + B = " << c << '\n';
    	}
    	else if (choice == 2) {
    		Polynomial c = a.Mult(b);
    		cout << "A * B = " << c << '\n';
    	}
    	else if (choice == 3) {
    		float x;
    		cout << "輸入 x: ";
    		cin >> x;
    		cout << "A(" << x << ") = "
    			<< a.Eval(x) << '\n';
    		cout << "B(" << x << ") = "
    			<< b.Eval(x) << '\n';
    	}
    	else if (choice == 4) {
			break;
		}
	}
	    
	
	return 0;
}
```

## 效能分析

1. 多項式加法：時間複雜度為 $O(m+n)$。
2. 多項式乘法：兩個多項式的每一項都要互相相乘，因此基本時間複雜度為 $O(mn)$。
3. 帶入 x：程式會逐項計算 $x$ 的次方。
4. 空間複雜度：
   - 多項式使用動態陣列儲存資料，因此空間使用量會隨項數增加。
   - 如果陣列容量不足，會建立更大的陣列並複製原本資料。


## 測試與驗證

### 測試案例

假設輸入的兩個多項式為：

$$
A = 5x^2 + 3x + 2
$$

$$
B = 2x + 1
$$

測試結果如下：

| 測試案例 | 功能 | 輸入 | 預期輸出 | 實際輸出 |
|----------|------|------|----------|----------|
| 測試一 | 多項式相加 | 選擇 `1` | `5x^2 + 5x + 3` | `5x^2 + 5x + 3` |
| 測試二 | 多項式相乘 | 選擇 `2` | `10x^3 + 11x^2 + 7x + 2` | `10x^3 + 11x^2 + 7x + 2` |
| 測試三 | 帶入 x | 選擇 `3`，`x = 2` | `A(2) = 28`、`B(2) = 5` | `A(2) = 28`、`B(2) = 5` |
| 測試四 | 結束程式 | 選擇 `4` | 程式結束 | 程式結束 |

### 效能量測

本程式使用的多項式項數不多，因此相加、相乘與帶入 x 都可以很快得到結果。
其中：
相加只需要依序比較兩個多項式中的項目。
帶入 x 需要計算每一項的次方。
相乘需要將兩個多項式的每一項互相相乘，還要搜尋是否有相同指數，因此運算量最大。
例如：
A 有 3 項，B 有 2 項。
相乘時至少需要做：
$$
3\times2=6
$$
次項目相乘。
因此當多項式項數增加時，相乘所需要的時間會比相加增加得更快。

### 心得討論

這次作業讓我練習到如何使用類別和動態陣列來表示多項式。
一開始比較容易出錯的地方是在陣列容量不足時，如果直接刪除舊陣列，原本的資料也會消失，所以需要先將原本資料複製到新的陣列。
在多項式加法中，可以利用兩個位置同時比較兩個多項式的指數。
乘法則比加法複雜，因為每一項都需要和另一個多項式的每一項相乘，如果產生相同指數還需要合併。
這次也使用了 operator<< 和 operator>>，讓 Polynomial 物件可以直接使用 cout 和 cin。
最後加入選單後，可以一直選擇相加、相乘或帶入 x，直到選擇 4 才結束程式。
透過這次作業，我對 Polynomial 類別、動態陣列以及運算子多載的使用方式更熟悉。


