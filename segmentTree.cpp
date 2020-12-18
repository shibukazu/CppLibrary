#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
/*
segmentTreeの各要素型をT
各要素間の二項演算のシグネチャをFnとする
呼び出し例:
  segmentTree<ll, function<ll(ll, ll)>>
注意: 0オリジンとしている
*/
template <typename T, typename Fn>
class segmentTree
{
private:
  vector<T> tree;
  ll leavesSize;
  T fill;
  Fn binaryOperation;
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
      cand1 = innerQuery(startIdx, (startIdx + endIdx) / 2, leftIdx, rightIdx, innerIdx * 2 + 1);
      cand2 = innerQuery((startIdx + endIdx) / 2, endIdx, leftIdx, rightIdx, innerIdx * 2 + 2);
      return binaryOperation(cand1, cand2);
    }
  }

public:
  //余分な値を埋めるための要素 fill
  //クエリの際に絶対に選ばれない値とする
  segmentTree(vector<T> &seq, T fill, Fn binaryOperation)
  {
    this->fill = fill;
    this->binaryOperation = binaryOperation;
    ll originalSize = seq.size();
    this->leavesSize = 1;
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
        tree[j] = binaryOperation(tree[j * 2 + 1], tree[j * 2 + 2]);
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
      tree[innerIdx] = binaryOperation(tree[innerIdx * 2 + 1], tree[innerIdx * 2 + 2]);
    }
  }
  //updateのオーバーロード
  //更新時に既存の値との二項演算を行いたい場合こちらを使う
  //二項演算型を指定する
  //二項演算の第二引数が新しい値
  template <typename UpFn>
  void update(ll idx, T value, UpFn updateOperation)
  {
    ll innerIdx = leavesSize - 1 + idx;
    tree[innerIdx] = updateOperation(tree[innerIdx], value);
    while (innerIdx > 0)
    {
      innerIdx = (innerIdx - 1) / 2;
      tree[innerIdx] = binaryOperation(tree[innerIdx * 2 + 1], tree[innerIdx * 2 + 2]);
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
  vector<ll> seq(n);
  for (int i = 0; i < n; ++i)
  {
    ll a;
    cin >> seq[i];
  }
  auto binaryOperation = [](ll num1, ll num2) { return num1 ^ num2; };
  auto updateOperation = [](ll num1, ll num2) { return num1 ^ num2; };
  segmentTree<ll, function<ll(ll, ll)>>
      seg = segmentTree<ll, function<ll(ll, ll)>>(seq, 0, binaryOperation);
  for (int i = 0; i < q; i++)
  {
    int c, x, y;
    cin >> c >> x >> y;
    if (c == 1)
    {
      seg.update<function<ll(ll, ll)>>(x - 1, y, updateOperation);
    }
    else if (c == 2)
    {
      ll result = seg.query(x - 1, y);
      cout << result << endl;
    }
  }
}