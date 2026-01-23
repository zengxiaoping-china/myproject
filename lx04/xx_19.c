/*
有4个圆塔,圆心分别为(2,2).(-2,2).(- 2,-2).(2,-2),圆半径为1,这4个塔的高度为
10m,塔以外无建筑物。今输人任一点的坐标,求该点的建筑高度(塔外的高度为零)。
*/
#include <stdio.h>
#include <math.h>

int main() {
    double x, y;
    double h = 0;

    printf("请输入一点的坐标(x,y): ");
    scanf("%lf %lf", &x, &y);

    // 判断点是否在圆塔内
    if (sqrt((x - 2)*(x - 2) + (y - 2)*(y - 2)) <= 1) {
        h = 10;
    } else if (sqrt((x + 2)*(x + 2) + (y - 2)*(y - 2)) <= 1) {
        h = 10;
    } else if (sqrt((x + 2)*(x + 2) + (y + 2)*(y + 2)) <= 1) {
        h = 10;
    } else if (sqrt((x - 2)*(x - 2) + (y + 2)*(y + 2)) <= 1) {
        h = 10;
    }

    printf("该点的建筑高度为: %.0f\n", h);

    return 0;
}