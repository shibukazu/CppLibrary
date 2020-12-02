/*-------------------------------------------------------- 
名前: 約数列挙アルゴリズム
目的: 与えられた数Nの約数を効率的に列挙する
アルゴリズム: 
i = 1~floor(sqrt(N))について
iが約数であればN/iが約数であることは明らかなので
セットで列挙する
オーダー: O(sqrt(N))
説明: 
--------------------------------------------------------*/

#include <bits/stdc++.h>
using namespace std;
vector<int> divisor(int n)
{
  vector<int> result;
  for (int i = 1; i <= floor(sqrt(n)); i++)
  {
    if (n % i == 0)
    {
      result.push_back(i);
      result.push_back(n / i);
    }
  }
  sort(result.begin(), result.end());
  return result;
}
int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  vector<int> result = divisor(n);
  for (const auto &i : result)
    cout << i << endl;
}