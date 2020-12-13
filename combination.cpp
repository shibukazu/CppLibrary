#include <bits/stdc++.h>
using namespace std;
uint64_t combinations2(uint64_t n, uint64_t k)
{
  uint64_t r = 1;
  for (uint64_t d = 1; d <= k; ++d)
  {
    /* 毎回dで割っても割り切れる？？
    →割り切れる(わる数を1から増加させる場合)
    (n / 1 * n - 1) / 2　はnC2になっているから
    */
    r *= n--;
    r /= d;
  }
  return r;
}