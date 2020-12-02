/*-------------------------------------------------------- 
名前: グリッドサーチ
目的: 二次元座標を幅優先探索し、スタートからtargetへの最短コストを計算する
アルゴリズム: 
オーダー: O(HW)
説明: 高さH, 幅Wの二次元座標について
各座標では4通りの移動（4つの辺）しか持たないから
O(4*HW) = O(HW)
--------------------------------------------------------*/
#include <bits/stdc++.h>
using namespace std;
template <typename T>
int gridSearch(int sx, int sy, T target, vector<vector<T>> &grid)
{
  struct Point
  {
    int x;
    int y;
    int cost;
  };
  int cost = 0;
  vector<vector<bool>> detected(grid.size(), vector<bool>(grid[0].size(), false));
  vector<int> dx{0, 1, 0, -1};
  vector<int> dy{1, 0, -1, 0};
  queue<Point> bfsQueue;
  bfsQueue.push(Point{sx, sy, 0});
  detected[sy][sx] = 0;
  //gridは連結より可能
  while (!bfsQueue.empty())
  {
    Point p = bfsQueue.front();
    bfsQueue.pop();
    for (int i = 0; i < 4; i++)
    {
      int nx = p.x + dx[i], ny = p.y + dy[i];
      if (nx < 0 || nx >= grid[0].size() || ny < 0 || ny >= grid.size() || detected[ny][nx])
        continue;
      else
      {
        if (grid[ny][nx] == target)
        {
          return p.cost + 1;
        }
        bfsQueue.push(Point{nx, ny, p.cost + 1});
        detected[ny][nx] = true;
      }
    }
  }
  return -1;
}
int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  int h, w;
  cin >> h >> w;
  vector<vector<int>> grid(h, vector<int>(w, 0));
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      cin >> grid[i][j];
    }
  }
  cout << gridSearch(0, 0, 5, grid) << endl;
}