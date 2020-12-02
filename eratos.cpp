#include <bits/stdc++.h>
using namespace std;
//2~nまでの素数を列挙する
void eratos(int n)
{
  vector<bool> isPrime = vector<bool>(n + 1, true);
  isPrime[0] = false;
  isPrime[1] = false;
  for (int i = 2; i <= n; i++)
  {
    if (isPrime[i])
    {
      int j = i + i;
      while (j <= n)
      {
        isPrime[j] = false;
        j += i;
      }
    }
  }
  for (int i = 0; i <= n; i++)
  {
    if (isPrime[i])
      cout << i << " ";
  }
  cout << endl;
}
int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  eratos(n);
}