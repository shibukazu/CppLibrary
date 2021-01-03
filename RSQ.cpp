/*------------------------------
数列 A = {a1,a2,...,an} に対し、次の２つの操作を行うプログラム
add(s,t,x): as,as+1,...,at にxを加算する。
getSum(s,t): as,as+1,...,atの合計値を出力する。

各クエリの結果が累積する場合に応用可能
--------------------------------*/
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
template <typename T, typename Fn>
class lazySegmentTree
{
private:
  vector<T> tree;
  vector<T> lazy;
  ll leavesSize;
  T fill;
  Fn binaryOperation;
  //lazyに値があるならば子にlazyを伝達させていき、自分の値を更新する
  void eval(ll innerIdx)
  {
    ll leftChildIdx = innerIdx * 2 + 1;
    ll rightChildIdx = innerIdx * 2 + 2;
    if (lazy[innerIdx] != 0 && leftChildIdx < tree.size() && rightChildIdx < tree.size())
    {
      //lazyへの代入は完全被覆のときのみだから半分にしていい
      //例: 区間[0-4)のlazyに代入されるのはupdate範囲がs<=0 ~ 4<=tのときのみ
      //累積するから代入ではない
      lazy[leftChildIdx] += lazy[innerIdx] / 2;
      lazy[rightChildIdx] += lazy[innerIdx] / 2;
    }
    tree[innerIdx] += lazy[innerIdx];
    lazy[innerIdx] = 0;
  }
  //開区間で考える
  //left, rightがクエリの開区間
  T innerQuery(ll startIdx, ll endIdx, ll leftIdx, ll rightIdx, ll innerIdx)
  {
    eval(innerIdx);
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
  //開区間で考える
  void innerUpdate(ll startIdx, ll endIdx, ll leftIdx, ll rightIdx, ll innerIdx, T value)
  {
    eval(innerIdx);
    //いま考えている区間がクエリ区間に入らない場合
    if (endIdx <= leftIdx || rightIdx <= startIdx)
      return;
    //今考えている区間がクエリ区間に完全に入る場合
    else if (leftIdx <= startIdx && endIdx <= rightIdx)
    {
      lazy[innerIdx] = (endIdx - startIdx) * value;
      eval(innerIdx);
    }
    //部分的に入っている場合
    else
    {
      innerUpdate(startIdx, (startIdx + endIdx) / 2, leftIdx, rightIdx, innerIdx * 2 + 1, value);
      innerUpdate((startIdx + endIdx) / 2, endIdx, leftIdx, rightIdx, innerIdx * 2 + 2, value);
      ll leftChildIdx = innerIdx * 2 + 1;
      ll rightChildIdx = innerIdx * 2 + 2;
      tree[innerIdx] = tree[leftChildIdx] + tree[rightChildIdx];
    }
  }

public:
  //余分な値を埋めるための要素 fill
  //クエリの際に絶対に選ばれない値とする
  lazySegmentTree(vector<T> &seq, T fill, Fn binaryOperation)
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
    lazy = vector<T>(leavesSize * 2 - 1, fill);
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
  void update(ll leftIdx, ll rightIdx, T value)
  {
    innerUpdate(0, leavesSize, leftIdx, rightIdx, 0, value);
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
  vector<ll> seq(n, 0);
  auto binaryOperation = [](ll num1, ll num2) { return num1 + num2; };
  auto seg = lazySegmentTree<ll, function<ll(ll, ll)>>(seq, 0, binaryOperation);
  for (int i = 0; i < q; i++)
  {
    int c;
    cin >> c;
    if (c == 0)
    {
      int s, t, x;
      cin >> s >> t >> x;
      seg.update(s - 1, t, x);
    }
    else if (c == 1)
    {
      int s, t;
      cin >> s >> t;
      ll result = seg.query(s - 1, t);
      cout << result << endl;
    }
  }
}