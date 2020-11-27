#include <bits/stdc++.h>
using namespace std;
//無向グラフにおける関節点探索アルゴリズム
//仮定: 連結であるグラフにのみ適用可能
//     非連結な場合、連結部分のいずれかをstartIdxにする
struct Node
{
  int index;
  float cost;
  float minCost;
  Node *parent;
  list<Node *> children;
};
const float INF = numeric_limits<float>::infinity();
void DFS(vector<list<int>> &adjList, vector<Node *> nodes, int startIdx, vector<bool> &detected)
{
  static float innerCost = 0.0;
  Node *self = nodes[startIdx];
  self->cost = innerCost;
  detected[startIdx] = true;
  for (auto it = adjList[startIdx].begin(); it != adjList[startIdx].end(); it++)
  {
    if (!detected[*it])
    {
      self->children.push_back(nodes[*it]);
      nodes[*it]->parent = self;
      innerCost += 1;
      DFS(adjList, nodes, *it, detected);
    }
  }
  //子全てについて探索が終わったことになるのでminCostを計算できる
  //backEdgeが存在する場合,backEdgeがつながっている先のノードのコストを格納する
  list<float> backEdgeCosts;
  //前進辺の先のノードはは必ず今のノードのコストより大きいことが保証されるので
  //前進辺を含め、parentでないノードが辺の先になっている辺全てをbackEdgeとする
  //無向グラフよりadjList[startIdx]飲み調べれば良い
  for (auto it = adjList[startIdx].begin(); it != adjList[startIdx].end(); it++)
  {
    if (nodes[*it] != self->parent)

      backEdgeCosts.push_back(nodes[*it]->cost);
  }
  float minBackEdgeCost = INF;
  if (backEdgeCosts.size() > 0)
  {
    auto it = min_element(backEdgeCosts.begin(), backEdgeCosts.end());
    minBackEdgeCost = *it;
  }
  float minChildrenCost = INF;
  if (self->children.size() > 0)
  {
    auto it = min_element(self->children.begin(), self->children.end(), [](Node *n1, Node *n2) {
      return n1->minCost <= n2->minCost;
    });
    minChildrenCost = (*it)->minCost;
  }

  self->minCost = min({minBackEdgeCost, minChildrenCost, self->cost});
}
void articulationPoints(vector<list<int>> &adjList, set<int> &result)
{
  int nodeSize = adjList.size();
  vector<Node *> nodes;
  for (int i = 0; i < nodeSize; i++)
  {
    nodes.push_back(new Node{i, INF, INF, NULL});
  }
  vector<bool> detected = vector<bool>(nodeSize, false);
  //ノード0を探索のルートとする
  DFS(adjList, nodes, 0, detected);
  //ルートノードである0についてルートのときの関節点条件を検討する
  Node *rootNode = nodes[0];
  if (rootNode->children.size() >= 2)
    result.insert(0);
  //ルートノード以外の全ノードについて関節点条件を検討する
  for (int i = 1; i < nodeSize; i++)
  {
    Node *targetNode = nodes[i];
    if (targetNode->parent == rootNode)
      continue;
    else
    {
      if (targetNode->parent->cost <= targetNode->minCost)
      {
        result.insert(targetNode->parent->index);
      }
    }
  }
}
int main()
{
  int nodeSize, edgeSize;
  cin >> nodeSize >> edgeSize;
  vector<list<int>> adjList = vector<list<int>>(nodeSize);
  for (int i = 0; i < edgeSize; i++)
  {
    int s, t;
    cin >> s >> t;
    adjList[s].push_back(t);
    adjList[t].push_back(s);
  }
  set<int> result;
  articulationPoints(adjList, result);
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout << *it << endl;
  }
}