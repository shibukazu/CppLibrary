#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
struct Result
{
  ll x;
  ll y;
};
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
//kx = s (mod n)を満たすxのうち正の範囲で最小のものを求める
ll solveModEquation(ll k, ll s, ll n)
{
  ll g1 = gcd(gcd(k, s), n);
  //k, s, nをg1で割った合同方程式が必要条件として求まる
  ll k1 = k / g1, s1 = s / g1, n1 = n / g1;
  //このときgcd(k1, n1)とs1は互いに素であるので解の存在条件はgcd(k1, n1) = 1のみ
  if (gcd(k1, n1) != 1)
  {
    return 0;
  }
  //gcdが1のときの解法はまず逆元を求めること
  else
  {
    ll inv = modInv(k1, n1);
    //FIXME なぜ%n1 ??
    return (inv * s1) % n1;
  }
}
int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 0; i < t; i++)
  {
    int n, s, k;
    cin >> n >> s >> k;
    ll result = solveModEquation(k, n - s, n);
    result = result == 0 ? -1 : result;
    cout << result << endl;
  }
}