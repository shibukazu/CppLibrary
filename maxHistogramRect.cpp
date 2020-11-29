#include <bits/stdc++.h>
using namespace std;
//ヒストグラム内の最大長方形の面積を返す
struct Rect
{
  int rightIdx;
  int leftIdx;
  int height;
};
int maxHistogramRect(vector<int> &histogram)
{
  int maxArea = 0;
  int histogramSize = histogram.size();
  stack<Rect> weightStack;
  for (int i = 0; i < histogramSize; i++)
  {
    Rect newRect;
    newRect.height = histogram[i];
    //空なのは最初だけ、それ以降は空でないことが保証できる
    if (weightStack.empty())
    {
      newRect.leftIdx = i;
      weightStack.push(newRect);
      maxArea = 1 * newRect.height;
    }
    //取り出されたものは戻されることはなく、一方通行だからO(n)
    else
    {
      int lastLeftIdx = i;
      while (!weightStack.empty() && weightStack.top().height > histogram[i])
      {
        weightStack.top().rightIdx = i - 1;
        int area = (weightStack.top().rightIdx - weightStack.top().leftIdx + 1) * weightStack.top().height;
        if (maxArea < area)
          maxArea = area;
        lastLeftIdx = weightStack.top().leftIdx;
        weightStack.pop();
      }
      Rect newRect;
      newRect.height = histogram[i];
      newRect.leftIdx = lastLeftIdx;
      weightStack.push(newRect);
    }
  }
  //weightStackに残ったものについての面積を計算する
  while (!weightStack.empty())
  {
    weightStack.top().rightIdx = histogramSize - 1;
    int area = (weightStack.top().rightIdx - weightStack.top().leftIdx + 1) * weightStack.top().height;
    if (maxArea < area)
      maxArea = area;
    weightStack.pop();
  }
  return maxArea;
}
int main()
{
  int n;
  cin >> n;
  vector<int> histogram;
  for (int i = 0; i < n; i++)
  {
    int h;
    cin >> h;
    histogram.push_back(h);
  }
  cout << maxHistogramRect(histogram) << endl;
}