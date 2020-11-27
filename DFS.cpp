#include <bits/stdc++.h>
using namespace std;
//注意: 0オリジンとしている
//発見順にノードのインデックスを格納したint型リストを返す
list<int> innerDFS(vector<list<int>> &adjList, vector<bool> &detected, int startIdx)
{
  static list<int> detectedIdx;
  detectedIdx.push_back(startIdx);
  detected[startIdx] = true;
  for (auto it = adjList[startIdx].begin(); it != adjList[startIdx].end(); it++)
  {
    if (!detected[*it])
    {
      innerDFS(adjList, detected, *it);
    }
  }
  return detectedIdx;
}
list<int> DFS(vector<list<int>> &adjList)
{
  int nodeSize = adjList.size();
  vector<bool> detected = vector<bool>(nodeSize, false);
  list<int> detectedIdx;
  for (int i = 0; i < nodeSize; i++)
  {
    //非連結有向グラフより
    //様々なノードを始点として探索しなくてはならない
    if (!detected[i])
    {
      list<int> returnedList = innerDFS(adjList, detected, i);
      for (auto it = returnedList.begin(); it != returnedList.end(); it++)
      {
        detectedIdx.push_back(*it);
      }
    }
  }
  return detectedIdx;
}
//v->uに辺が存在する場合
//adjList[u]に辺を加える
int main()
{
  int nodeSize;
  cin >> nodeSize;
  vector<list<int>> adjList = vector<list<int>>(nodeSize);
  for (int i = 0; i < nodeSize; i++)
  {
    int notUse;
    int dim;
    cin >> notUse >> dim;
    for (int j = 0; j < dim; j++)
    {
      int nodeNum;
      cin >> nodeNum;
      adjList[i].push_back(nodeNum);
    }
  }
  list<int> result = DFS(adjList);
  for (auto it = result.begin(); it != result.end(); it++)
  {
    cout << *it;
  }
}