#include <bits/stdc++.h>
using namespace std;
/*
二次元平面上である範囲内に存在する値を列挙するプログラム
*/
//P 座標の型(比較可能な数値型)
//I 各座標のインデックスの型(人の位置なら人の名前など)
template <typename P, typename I>
class kDTree
{
private:
  struct Point
  {
    I index;
    P x;
    P y;
  };
  struct Node
  {
    Node *parent;
    Node *leftChild;
    Node *rightChild;
    Point point;
  };
  Node *rootNode;
  vector<Point> points;
  //l~rにおけるmidNodeポインタを返す
  Node *makekDTree(int l, int r, int depth, Node *parent)
  {
    if (r == l + 1)
    {
      //この場合はl~rに1つしかないため
      //そのノードを返す
      //そのノードは子を持たない
      int midIdx = l;
      Point midPoint = points[midIdx];
      Node *midNode = new Node;
      midNode->parent = parent;
      midNode->point = midPoint;
      midNode->leftChild = NULL;
      midNode->rightChild = NULL;
      return midNode;
    }
    else if (r == l)
    {
      //この場合は何も存在しないのでNULLポインタを返す
      return NULL;
    }
    //ソートは毎回行い、O(nlogn)
    //基本的には頂点分行うからO(n^2logn)
    if (depth % 2 == 0)
    {
      //偶数深度のときは対象範囲をxでソート
      sort(points.begin() + l, points.begin() + r, [](Point first, Point second) -> bool { return first.x < second.x; });
    }
    else
    {
      //奇数深度のときは対象範囲をyでソート
      sort(points.begin() + l, points.begin() + r, [](Point first, Point second) -> bool { return first.y < second.y; });
    }
    int midIdx = (l + r) / 2;
    Point midPoint = points[midIdx];
    Node *midNode = new Node;
    midNode->parent = parent;
    midNode->point = midPoint;
    midNode->leftChild = makekDTree(l, midIdx, depth + 1, midNode);
    midNode->rightChild = makekDTree(midIdx + 1, r, depth + 1, midNode);
    return midNode;
  }
  //引数targetは探索開始位置（rootNode）
  void innerFind(P sx, P tx, P sy, P ty, int depth, Node *target, vector<I> &ans)
  {
    //探索は木の高さ分行うからO(logn)
    Point targetPoint = target->point;
    if (sx <= targetPoint.x && targetPoint.x <= tx && sy <= targetPoint.y && targetPoint.y <= ty)
      ans.push_back(targetPoint.index);
    //偶数の深さの時はxの二分探索木として探索
    if (depth % 2 == 0)
    {
      if (sx <= targetPoint.x && target->leftChild != NULL)
      {
        innerFind(sx, tx, sy, ty, depth + 1, target->leftChild, ans);
      }
      if (targetPoint.x <= tx && target->rightChild != NULL)
      {
        innerFind(sx, tx, sy, ty, depth + 1, target->rightChild, ans);
      }
    }
    //奇数の深さの時はyの二分探索木として探索
    else
    {
      if (sy <= targetPoint.y && target->leftChild != NULL)
      {
        innerFind(sx, tx, sy, ty, depth + 1, target->leftChild, ans);
      }
      if (targetPoint.y <= ty && target->rightChild != NULL)
      {
        innerFind(sx, tx, sy, ty, depth + 1, target->rightChild, ans);
      }
    }
  }

public:
  kDTree() {}
  //kd木にいれたい座標を追加する
  void add(P x, P y, I index)
  {
    points.push_back(Point{index, x, y});
  }
  //追加した座標をもとにkd木を構成
  void build()
  {
    rootNode = new Node;
    //一旦kd木をrootの左部分木として実装
    rootNode->leftChild = makekDTree(0, points.size(), 0, rootNode);
    //rootを部分木の根に書き換える→rootからkd木にアクセス可能
    rootNode = rootNode->leftChild;
  }
  //sx~tx, sy~ty内に存在する座標のインデックスを改行ありで出力する(最終行出力後も改行あり)
  void find(P sx, P tx, P sy, P ty)
  {
    vector<I> ans;
    innerFind(sx, tx, sy, ty, 0, rootNode, ans);
    sort(ans.begin(), ans.end());
    for (auto it = ans.begin(); it != ans.end(); it++)
    {
      cout << *it << endl;
    }
    cout << endl;
  }
};
int main()
{
  int n;
  cin >> n;
  kDTree<int, int> *kd = new kDTree<int, int>;
  for (int i = 0; i < n; i++)
  {
    int x, y;
    cin >> x >> y;
    kd->add(x, y, i);
  }
  kd->build();
  int q;
  cin >> q;
  for (int i = 0; i < q; i++)
  {
    int sx, tx, sy, ty;
    cin >> sx >> tx >> sy >> ty;
    kd->find(sx, tx, sy, ty);
  }
  free(kd);
}