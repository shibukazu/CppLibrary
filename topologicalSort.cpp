/*
トポロジカルソート
目的:
  閉路を持たない有向グラフの有向辺の向きが必ず左から右になるように頂点を並び替えるソート
方法:
  各頂点について入次数が0のものを連結リスト に挿入する
  その後、その頂点から出る辺が入る頂点の入次数を1減らす
オーダー: 
  時間計算量: 各ノードごとにO(1)の処理および隣接ノードの入次数を減らす
            →O(|V|+|E|)
*/
#include <bits/stdc++.h>
using namespace std;
const float INF = numeric_limits<float>::infinity();
//DAGと仮定する
//並べ替えた頂点のインデックスを含むリストを返す
list<int> topologicalSort(vector<list<float>> &adjList, vector<int> &inDim)
{
  int nodeSize = adjList.size();
  vector<bool> detected = vector<bool>(nodeSize, false);
  queue<int> nextIdx;
  list<int> sortedIdx;
  //DAGより入次数が0となるノードが必ず存在する
  while (sortedIdx.size() != nodeSize)
  {
    int fromIdx;
    for (int i = 0; i < nodeSize; i++)
    {
      if (inDim[i] == 0 && !detected[i])
      {
        fromIdx = i;
        break;
      }
    }
    for (auto it = adjList[fromIdx].begin(); it != adjList[fromIdx].end(); it++)
    {
      inDim[*it]--;
    }
    sortedIdx.push_back(fromIdx);
    detected[fromIdx] = true;
  }

  return sortedIdx;
}
int main()
{
  int nodeSize, edgeSize;
  cin >> nodeSize >> edgeSize;
  vector<list<float>> adjList = vector<list<float>>(nodeSize);
  vector<int> inDim = vector<int>(nodeSize, 0);
  for (int i = 0; i < edgeSize; i++)
  {
    int s, t;
    cin >> s >> t;
    adjList[s].push_back(t);
    inDim[t]++;
  }
  list<int> sortedIdx;
  sortedIdx = topologicalSort(adjList, inDim);
  for (auto it = sortedIdx.begin(); it != sortedIdx.end(); it++)
  {
    cout << *it << endl;
  }
}