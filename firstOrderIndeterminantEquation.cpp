//係数a,b　定数cの一時不定方程式の特殊解を求めるアルゴリズム
//右辺の定数項cが左辺の係数a, bのgcdとなっていることを確認した上で使用する
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
struct Result
{
  ll x;
  ll y;
};
//値が大きい方をaとする
Result extendedEuclid(ll a, ll b, ll c)
{
  if (gcd(a, b) != c)
  {
    throw runtime_error("この一次不定方程式は解を持ちません.");
  }
  if (b == 0)
  {
    return Result{1, 0};
  }
  else
  {
    ll r = a % b;
    Result result = extendedEuclid(b, r, c);
    return Result{result.y, result.x - (a / b) * result.y};
  }
}
int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  int a, b, c;
  cin >> a >> b >> c;
  Result result = extendedEuclid(a, b, c);
  cout << result.x << " " << result.y << endl;
}