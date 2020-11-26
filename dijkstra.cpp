#include <bits/stdc++.h>
using namespace std;
/*
始点から全て辿れる場合のダイクストラによる最短経路コスト計算プログラム
*/
const float INF = numeric_limits<float>::infinity();
//各ノードの始点からの最短経路コストを計算する
void dijkstra(vector<list<pair<int, float>>> &adjList, vector<float> &minimumDistances, int startIdx)
{
  int nodeSize = adjList.size();
  //まだ最短経路木に入っていないノードの現段階の最短コストを格納するpriority_queue
  //各要素はfirst->ノード番号, second->現段階の最短コスト
  auto compare = [](pair<int, float> l, pair<int, float> r) {
    //小さい順に取り出す
    return l.second < r.second;
  };
  //ここでいうMSTはMinimumShortestTree
  priority_queue<pair<int, float>, vector<pair<int, float>>, decltype(compare)> notInMST(compare);
  notInMST.push(make_pair(startIdx, 0.0));
  //始点から全て辿れることからnotInMSTが空になったときが終了タイミング
  while (!notInMST.empty())
  {
    //最小コストのものを取り出す(notInMSTにはまだ最短経路木に入っていないものしか入っていない)
    //コストINFの場合は必ず取り出されないため、発見済みのノードのみ取り出されることになる
    pair<int, float> minCostNode = notInMST.top();
    notInMST.pop();
    int minCostNodeIdx = minCostNode.first;
    float minCost = minCostNode.second;
    minimumDistances[minCostNodeIdx] = minCost;
    //この時点でminimumDistances[minCostNodeIdx]は始点からの最小コストになっている
    for (auto it = adjList[minCostNodeIdx].begin(); it != adjList[minCostNodeIdx].end(); it++)
    {
      //確定した(MSTに入った)ノードに隣接するノードに対して
      //コストが小さくなるならば更新する
      //この際、別の確定済みノードと隣接していたとしても確実に更新されない（性質より）
      //また、queueも更新する
      int nodeIdx = (*it).first;
      int weight = (*it).second;
      if (weight + minimumDistances[minCostNodeIdx] < minimumDistances[nodeIdx])
      {
        minimumDistances[nodeIdx] = weight + minimumDistances[minCostNodeIdx];
        notInMST.push(make_pair(nodeIdx, minimumDistances[nodeIdx]));
      }
    }
  }
}

int main()
{
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);
  int n;
  cin >> n;
  vector<float> minimumDistances = vector<float>(n, INF);
  vector<list<pair<int, float>>> adjList = vector<list<pair<int, float>>>(n);
  for (int i = 0; i < n; i++)
  {
    int nodeIdx, dim;
    cin >> nodeIdx >> dim;
    for (int j = 0; j < dim; j++)
    {
      int nextNodeIdx, weight;
      cin >> nextNodeIdx >> weight;
      adjList[nodeIdx].push_back(make_pair(nextNodeIdx, weight));
    }
  }
  dijkstra(adjList, minimumDistances, 0);
  for (int i = 0; i < n; i++)
  {
    cout << i << ' ' << minimumDistances[i] << endl;
  }
}