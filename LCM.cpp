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
//計算順序によりオーバーフローを回避
int LCM(int m, int n)
{
  return m / GCD(m, n) * n;
}
int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
}