/*
점과 직선, 선분의 표현은 일관되게 "벡터"로 표현한다.

*/
#include <vector>
#include <math.h>
using namespace std;

# 점과 직선, 선분의 표현
// 세 개의 점 p, a, b가 주어졌을 때, a가 b보다 얼마나 p에 더 가까운지 반환하는 함수 작성시 벡터가 용이함
double howMuchCloser(vector2 p, vector2 a, vector2 b){
    return (b - p).norm() - (a - p).norm();
}
// cf. 만약 각 점을 {x,y}로 표현하는 경우 코드가 복잡해짐
double howMuchCloser(double px, double py, double ax, double ay, double bx, double by){
    return sqrt((bx - px) * (bx - px) + (by - py) * (by - py)) - sqrt((ax - px)*(ax - px) + (ay - py)*(ay - py));
}

# 벡터의 내적과 외적
코드 15.2 두 벡터의 방향성을 판단하는 ccw() 함수의 구현 [counter clock wise]
// 원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환한다. (오른손 법칙)
double ccw(vector2 a, vector2 b){
    return a.cross(b);
}
// 점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환한다.
// 세 점이 주어진 경우
double ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p, b-p);
}