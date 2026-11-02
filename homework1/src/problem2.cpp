#include <iostream>
#include <string>

using namespace std;

void powerset(string s, int index, string now) {
    if (index == s.size()) {
        cout << "{";
        for (int i = 0; i < now.size(); i++) {
            if (i != 0)
                cout << ",";

            cout << now[i];
        }
        cout << "}" << '\n';
        return;
    }
    powerset(s, index + 1, now);
    powerset(s, index + 1, now + s[index]);
}

int main() {
    string s = "abc";
    powerset(s, 0, "");

    return 0;
}
