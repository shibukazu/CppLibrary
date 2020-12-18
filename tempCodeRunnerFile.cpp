#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
template <typename T>
class segmentTree
{
private:
  vector<T> tree;
  ll leavesSize;
  T fill;
  //開区間で考える
  //left, rightがクエリの開区間
  T innerQuery(ll startIdx, ll endIdx, ll leftIdx, ll rightIdx, ll innerIdx)
  {
    //いま考えている区間がクエリ区間に入らない場合
    if (endIdx <= leftIdx || rightIdx <= startIdx)
      return fill;
    //今考えている区間がクエリ区間に完全に入る場合
    else if (leftIdx <= startIdx && endIdx <= rightIdx)
    {
      return tree[innerIdx];
    }
    //部分的に入っている場合
    else
    {
      T cand1, cand2;
      cand1 = innerQuery(startIdx, endIdx / 2, leftIdx, rightIdx, innerIdx * 2 + 1);
      cand2 = innerQuery(endIdx / 2, endIdx, leftIdx, rightIdx, innerIdx * 2 + 2);
      return min(cand1, cand2);
    }
  }

public:
  //余分な値を埋めるための要素 fill
  //クエリの際に絶対に選ばれない値とする
  segmentTree(vector<T> &seq, T fill)
  {
    this->fill = fill;
    ll originalSize = seq.size();
    leavesSize = 1;
    while (leavesSize < originalSize)
    {
      leavesSize *= 2;
    }
    tree = vector<T>(leavesSize * 2 - 1, fill);
    //入力値を葉に代入
    for (ll i = 0; i < originalSize; i++)
    {
      tree[leavesSize - 1 + i] = seq[i];
    }
    //セグメントツリーを構成
    for (ll i = 0; i < leavesSize; i++)
    {
      ll j = leavesSize - 1 + i;
      while (j > 0)
      {
        j = (j - 1) / 2;
        tree[j] = min(tree[j * 2 + 1], tree[j * 2 + 2]);
      }
    }
  }
  void update(ll idx, T value)
  {
    ll innerIdx = leavesSize - 1 + idx;
    tree[innerIdx] = value;
    while (innerIdx > 0)
    {
      innerIdx = (innerIdx - 1) / 2;
      tree[innerIdx] = min(tree[innerIdx * 2 + 1], tree[innerIdx * 2 + 2]);
    }
  }
  //開区間で考える
  T query(ll leftIdx, ll rightIdx)
  {
    return innerQuery(0, leavesSize, leftIdx, rightIdx, 0);
  }
};
int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  vector<ll> seq(n, (ll)pow(2, 31) - 1);
  segmentTree<ll>
      seg = segmentTree<ll>(seq, (ll)pow(2, 31) - 1);
  for (int i = 0; i < q; i++)
  {
    int c, x, y;
    cin >> c >> x >> y;
    if (c == 0)
    {
      seg.update(x, y);
    }
    else if (c == 1)
    {
      ll result = seg.query(x, y + 1);
      cout << result << endl;
    }
  }
}