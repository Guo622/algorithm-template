#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<set>
#include<unordered_map>
#include<stack>
#include<string>
#include<vector>

using namespace std;
using ll = long long;
//https://blog.csdn.net/weixin_39648539/article/details/111393172?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_antiscanv2&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_antiscanv2&utm_relevant_index=2
struct Point2d
{
    double x;
    double y;
    Point2d(double xx, double yy) : x(xx), y(yy) {}
};

double ComputePolygonArea(const vector<Point2d>& points)
{
    int point_num = points.size();
    if (point_num < 3)return 0.0;
    double s = 0;
    for (int i = 0; i < point_num; ++i)
        s += points[i].x * points[(i + 1) % point_num].y - points[i].y * points[(i + 1) % point_num].x;
    return fabs(s / 2.0);
}

int main() {
    vector<Point2d>points;
    int n;
    scanf("%d", &n);
    for (int i = 1;i <= n;i++) {
        int x, y;
        double p;
        scanf("%d %d %lf", &x, &y, &p);
        points.push_back({ x,y });
    }
    printf("%lf", ComputePolygonArea(points));
    return 0;
}
