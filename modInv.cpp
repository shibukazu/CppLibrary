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
//mod nにおけるkの逆元のうち正の範囲で最小のものを返す
//つまりkx = 1 (mod n)を満たすxを求める
//なお逆元が存在しな場合は0を返す
ll modInv(ll k, ll n)
{

  //kとnのgcdが1であることが逆元が存在することの必要十分条件より確認する
  if (gcd(k, n) == 1)
  {
    Result innerResult = extendedEuclid(k, n, 1);
    ll result = innerResult.x < 0 ? innerResult.x + n : innerResult.x;
    return result;
  }
  else
  {
    return 0;
  }
}
int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  int k, n;
  cin >> k >> n;
  ll result = modInv(k, n);
  cout << result << endl;
}