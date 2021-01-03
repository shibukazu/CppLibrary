/*
bitで集合を表現したとき
部分集合の中の部分集合を列挙する
1減らしてbaseとの論理積を取ることで部分集合を得る
iが部分集合
*/
#include <bits/stdc++.h>
using namespace std;
#define subset(i, base) for (int i = base; i > 0; i &= (i - 1))
