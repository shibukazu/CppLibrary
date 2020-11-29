#include <bits/stdc++.h>
using namespace std;
class UnionFind
{
private:
  struct Node
  {
    int number;
    Node *parent;
    //自分をrootとしたときの木の高さ
    int rank;
  };
  vector<Node *> nodes;

public:
  UnionFind(int nodeSize)
  {
    nodes = vector<Node *>(nodeSize);
    for (int i = 0; i < nodeSize; ++i)
    {
      Node *node = new Node{i};
      node->parent = node;
      nodes[i] = node;
    }
  }

  //値がxのNodeが属する集合の代表Nodeを見つける
  Node *findSet(int x)
  {
    Node *node = nodes[x];
    while (node->parent != node)
    {
      node = node->parent;
    }
    return node;
  }
  void unite(int x, int y)
  {
    if (same(x, y))
      return;
    Node *represent1 = findSet(x);
    Node *represent2 = findSet(y);
    //高さが同じときはどちらに結合してもいい
    //結合先の木のrootの高さが1増える
    if (represent1->rank == represent2->rank)
    {
      represent2->parent = represent1;
      represent1->rank = represent1->rank + 1;
    }
    //高さが異なる時は全体の高さが高くならないように、高さが高い方に結合する
    //そのとき高さは変わらない
    else
    {
      if (represent1->rank > represent2->rank)
      {
        represent2->parent = represent1;
      }
      else
      {
        represent1->parent = represent2;
      }
    }
  }
  bool same(int x, int y)
  {
    Node *represent1 = findSet(x);
    Node *represent2 = findSet(y);
    return represent1 == represent2 ? true : false;
  }
};