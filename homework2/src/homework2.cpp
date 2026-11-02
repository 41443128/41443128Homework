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
