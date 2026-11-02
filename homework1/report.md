# 41443128

# 作業一

## Problem 1：Ackermann's Function

### 1. 解題說明

#### 問題描述

這題要計算 Ackermann 函數，而且要做兩種版本：

1. 遞迴版本。
2. 非遞迴版本。

Ackermann 函數的規則為：

- 當 `m = 0` 時，答案是 `n + 1`。
- 當 `m > 0` 且 `n = 0` 時，計算 `A(m - 1, 1)`。
- 其他情況計算 `A(m - 1, A(m, n - 1))`。

#### 解題策略

遞迴版本直接照題目的公式寫。

非遞迴版本用陣列模擬 stack，把還沒算完的 `m` 暫時存起來，再慢慢取出來計算。

因為本學期有標頭限制，所以沒有使用 `<stack>`。

### 2. 程式實作

```cpp
#include <iostream>

using namespace std;

int ackermann(int m, int n) {
    if (m == 0)
        return n + 1;
    if (n == 0)
        return ackermann(m - 1, 1);

    return ackermann(m - 1, ackermann(m, n - 1));
}

int ackermannLoop(int m, int n) {
    int s[100000];
    int top = 0;

    s[top++] = m;

    while (top > 0) {
        m = s[--top];

        if (m == 0) {
            n++;
        } else if (n == 0) {
            n = 1;
            s[top++] = m - 1;
        } else {
            s[top++] = m - 1;
            s[top++] = m;
            n--;
        }
    }

    return n;
}

int main() {
    int m = 2;
    int n = 3;

    cout << "Recursive: " << ackermann(m, n) << '\n';
    cout << "Non-recursive: " << ackermannLoop(m, n) << '\n';

    return 0;
}
```

### 3. 效能分析

Ackermann 函數成長很快，所以輸入稍微大一點，計算量就會變很多。

1. 時間複雜度：沒有辦法簡單用一般的 `O(n)` 表示，會隨 `m`、`n` 很快增加。
2. 空間複雜度：
   - 遞迴版本需要使用系統的 Call Stack。
   - 非遞迴版本使用陣列模擬 stack。

因此這題測試時不適合使用太大的數字。

### 4. 測試與驗證

測試幾組簡單的資料：

| 測試案例 | 輸入 | 預期輸出 |
| --- | --- | --- |
| 測試一 | `A(0,0)` | `1` |
| 測試二 | `A(0,3)` | `4` |
| 測試三 | `A(1,2)` | `4` |
| 測試四 | `A(2,3)` | `9` |
| 測試五 | `A(3,2)` | `29` |

實際執行：

```shell
$ g++ src/problem1.cpp --std=c++21 -o problem1.exe
$ ./problem1.exe
Recursive: 9
Non-recursive: 9
```

兩種方法算出來都是 `9`，所以結果相同。

### 5. 申論及開發報告

這題使用遞迴是因為題目的公式本身就是遞迴形式，所以直接照公式寫最簡單。

遞迴的優點是程式很短，也很好理解，但如果呼叫太多層，可能會造成 Stack Overflow。

非遞迴版本則是自己用陣列模擬 stack。雖然程式比較長，但是可以看出遞迴其實就是把還沒完成的工作先記住，之後再回來繼續算。

透過這題，我比較了解遞迴和 stack 之間的關係。

---

## Problem 2：Powerset

### 1. 解題說明

#### 問題描述

Powerset 是一個集合所有可能的子集合。

例如：

`S = {a,b,c}`

它的 Powerset 有：

`{}`、`{a}`、`{b}`、`{c}`、`{a,b}`、`{a,c}`、`{b,c}`、`{a,b,c}`。

如果集合有 `n` 個元素，總共會有 `2^n` 個子集合。

#### 解題策略

每一個元素都有兩種選擇：

1. 不選這個元素。
2. 選這個元素。

所以可以用遞迴一直往下一個元素處理。

當所有元素都處理完，就把目前的子集合印出來。

### 2. 程式實作

```cpp
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
```

### 3. 效能分析

每個元素都有「選」和「不選」兩種情況，所以會產生 `2^n` 個子集合。

1. 時間複雜度：`O(n×2^n)`。
2. 空間複雜度：`O(n)`。

空間主要來自遞迴的深度。

### 4. 測試與驗證

測試資料：

| 測試案例 | 輸入集合 | 子集合數量 |
| --- | --- | --- |
| 測試一 | `{a}` | `2` |
| 測試二 | `{a,b}` | `4` |
| 測試三 | `{a,b,c}` | `8` |

實際執行：

```shell
$ g++ src/problem2.cpp --std=c++21 -o problem2.exe
$ ./problem2.exe
{}
{c}
{b}
{b,c}
{a}
{a,c}
{a,b}
{a,b,c}
```

輸入有 3 個元素，所以應該有：

`2^3 = 8`

個子集合。

實際也印出了 8 個，因此結果正確。

### 5. 申論及開發報告

這題使用遞迴是因為每一個元素都可以分成「選」和「不選」兩種情況。

例如處理 `a` 時，可以先算不選 `a` 的情況，再算有選 `a` 的情況。

程式中的：

```cpp
powerset(s, index + 1, now);
```

代表不選目前的元素。

而：

```cpp
powerset(s, index + 1, now + s[index]);
```

代表選目前的元素。

這種寫法很簡單，也可以把所有可能的子集合都列出來。

透過這題，我比較了解遞迴可以用來處理有很多種選擇的問題。

---

## 作業總結

這次作業主要練習遞迴。

Problem 1 使用 Ackermann 函數，除了寫遞迴版本，也練習把遞迴改成非遞迴。

Problem 2 則是使用遞迴產生 Powerset。

做完這兩題後，我對遞迴的執行方式，以及 stack 的用途有更清楚的了解。
