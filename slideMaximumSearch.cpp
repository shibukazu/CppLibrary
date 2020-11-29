//数列のある区間（５個など）の中で最大のものを全て出力するプログラム

//ポイント
//区間をスライドしていくと考え、スライドしていく過程で
//自分よりも大きい値が入ってきたらそれ以降最大値になる可能性はない
//そのため行列から取り出す
//つまり降順になっている
//取り出されるパターン
//①最大値で区間の外になった場合
//②自分より大きい値が入ってきた場合
//オーダー
// dequeに入れる回数、出す回数は最大N回だからO(N)
// なぜなら一度出したらもう入れることはないから

#include <bits/stdc++.h>
using namespace std;
struct Number
{
  int number;
  int index;
};
//区間幅をKとする
void slideMaximumSearch(int K, vector<int> &seq)
{
  deque<Number> weightSeq;
  weightSeq.push_back({seq[0], 0});
  //区間の先頭のインデックス
  int startIdx = 0;
  for (int i = 1; i < K; i++)
  {
    while (!weightSeq.empty() && weightSeq.back().number < seq[i])
    {
      weightSeq.pop_back();
    }
    weightSeq.push_back({seq[i], i});
  }
  cout << weightSeq.front().number << endl;
  if (startIdx == weightSeq.front().index)
    weightSeq.pop_front();
  for (int i = K; i < seq.size(); ++i)
  {
    startIdx++;
    while (!weightSeq.empty() && weightSeq.back().number < seq[i])
    {
      weightSeq.pop_back();
    }
    weightSeq.push_back({seq[i], i});
    cout << weightSeq.front().number << endl;
    if (startIdx == weightSeq.front().index)
      weightSeq.pop_front();
  }
}
int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  int n, k;
  cin >> n >> k;
  vector<int> seq;
  for (int i = 0; i < n; i++)
  {
    int num;
    cin >> num;
    seq.push_back(num);
  }
  slideMaximumSearch(k, seq);
}