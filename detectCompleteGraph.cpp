/*------------------------------
全頂点中の全部分集合のなかで
クリークであるものをbitDPに記録する
adjはbit管理する
bitDPのサイズは頂点数nの時2^n(1~2^n-1より)
頂点番号は1~n
--------------------------------*/
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
void judgeCG(vector<bool> &bitDP, vector<int> &adj, int n)
{
  //単独ではクリーク
  bitDP[0] = true;
  for (int i = 1; i <= (1 << (n - 1)); i <<= 1)
  {
    bitDP[i] = true;
  }
  //iは各集合のbit
  for (int i = 1; i < (int)pow(2, n); i++)
  {
    //代表となるノード番号
    //どれを代表に選んでも完全グラフかどうかは変わらない
    int base;
    for (int j = 1; j <= n; j++)
    {
      if (i & (1 << (j - 1)))
      {
        base = j;
        break;
      }
    }
    //繋がっているかどうかを見たい対象のノード集合を表すbit
    int target = i & ~(1 << (base - 1));
    //targetたちが完全グラフになっていることがiが完全グラフである必要条件
    //targetはiより必ず小さいから計算できる
    if (bitDP[target])
    {
      //adj[base]がtargetを包括するのであればtarget全てに頂点が存在し、その集合は完全グラフである
      if ((adj[base] & target) == target)
      {
        bitDP[i] = true;
      }
      else
      {
        bitDP[i] = false;
      }
    }
    else
    {
      bitDP[i] = false;
    }
  }
}
int main()
{
  int n;
  cin >> n;
  vector<bool> bitDP((int)pow(2, n), false);
  vector<int> adj(n + 1, 0);
  int e;
  cin >> e;
  for (int i = 0; i < e; i++)
  {
    int a, b;
    cin >> a >> b;
    adj[a] |= (1 << (b - 1));
    adj[b] |= (1 << (a - 1));
  }
  judgeCG(bitDP, adj, n);
  for (int i = 0; i < (int)pow(2, n); i++)
  {
    if (bitDP[i])
    {
      cout << bitset<5>(i) << " true" << endl;
    }
    else
    {
      cout << bitset<5>(i) << " false" << endl;
    }
  }
}
