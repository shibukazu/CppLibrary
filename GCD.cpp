/*-------------------------------------------------------- 
名前: ユークリッドの互除法
目的: 最大公約数の導出
アルゴリズム: 
二つの数a, bのうち大きい方aを小さい方bで割ったあまりrを出し
次にbを余りrで割る。
これを余りが0になるまで続ける。
余りが0になったときのbが最大公約数
オーダー: O(loga) aは二つの数のうち、大きい方
説明: 
a = q * b + rにおいて
公約数(a, b) = 公約数(b, r)であることを利用し
公約数(a', 0)まで変換していく
0はどんな数でも割れる（どんな数をも約数に持つ）ので
そのときの割られる数であるa'が最大公約数となる
--------------------------------------------------------*/
#include <bits/stdc++.h>
using namespace std;
int GCD(int num1, int num2)
{
  int divided, divider, remain;
  if (num1 < num2)
  {
    divided = num2;
    divider = num1;
  }
  else
  {
    divided = num1;
    divider = num2;
  }
  while (divider != 0)
  {
    remain = divided % divider;
    divided = divider;
    divider = remain;
  }
  return divided;
}
int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  int n1, n2;
  cin >> n1 >> n2;
  int gcd = GCD(n1, n2);
  cout << gcd << endl;
}