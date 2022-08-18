# 직선과 직선의 교차
/*
두 직선의 교차 여부와 교차점 구하는 문제는 방정식으로 구하는 코드 작성시 수평선이나 수직선 같은 예외에 대응하기 어려워진다.
직선의 교차를 작성하는 간단한 방법은 직선을 한 점과 방향 벡터, 즉 (한 점) + p * (방향벡터)의 형태로 작성하는 것이다.
두 점 a,b를 지나는 a + p * (b - a) 와 두 점 c, d를 지나는 c + q * (d - c)의 교점 구하기.
p = {(c - a) x (d - c)} /  {(b-a) x (d-c)}
*/
코드 15.3 두 직선의 교차점을 계산하는 lineIntersection() 함수의 구현
// 벡터 (a -> b)를 포함하는 선과 벡터 (c -> d)를 포함하는 선의 교점을 x에 반환한다.
// 두 선이 평행이면 (겹치는 경우를 포함) 거짓을, 아니면 참을 반환한다. (평행에 대한 예외처리)
bool lineInterSection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
    double det = (b - a).cross(d-c);
    // 두 선이 평행인 경우
    if (fabs(det) < EPSILON) return false;
    x = a + ((c-a).cross(d-c) / det)*(b - a);
    return true;
}

# 선분과 선분의 교차
코드 15.4 선분과 선분의 교차점을 계산하는 segmentInterSection()의 구현
// 선분 (a, b)와 선분 (c, d)가 평행한 두 선분일 때, 이들이 한 점에서 겹치는지 확인한다.(평행 예외처리)
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
    // 각각 a가 왼쪽 아래에 위치하도록 설정
    if(b < a) swap(a,b);
    if(c < d) swap(c,d);
    // 한 직선 위에 없거나 두 선분이 겹치지 않는 경우를 우선 걸러낸다.
    if(ccw(a,b,c) != 0 || b < c || a > d) return false;
    // 두 선분은 확실히 겹친다. 교차점을 하나 찾자.
    if(a < c) p = c; else p = a;
    return true;
}

// p가 (a, b)를 감싸면서 각 변이 x, y축에 평행한 최소 사각형 내부에 잇는지 확인한다.
// a, b, p는 일직선 상에 있다고 가정한다.
bool inBoundRectangle(vector2 p, vector2 a, vector2 b){
    // 힝싱 점 a가 왼쪽 아래에 있도록
    if(b < a) swap(a,b);
    // 이렇게 굳이 나눈 이유는 vector2에서 <=이 정의되지 않았기 때문이다.
    return p == a || p == b || (a < p && p < b);
}
// (a, b)선분과 (c, d) 선분의 교점을 p에 반환한다.
// 교점이 여러 개일 경우 아무 점이나 반환한다.
// 두 선분이 교차하지 않을 경우 false를 반환한다.
bool segmentInterSection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p){
    // 두 직선이 평행한 경우 예외 처리
    if(!lineInterSection(a,b,c,d,p);){
        return parallelSegments(a,b,c,d,p);
    }
    // p가 두 선분에 포함되어 있는 경우에만 참을 반환한다.
    return inBoundRectangle(p,a,b) && inBoundRectangle(p,c,d);
}

# 선분과 선분의 교차 : 교차점이 필요 없을 때
코드 15.5 두 선분의 교차 여부를 좀 더 간단하게 확인하는 segmentIntersects() 함수의 구현
// 두 선분이 서로 접촉하는지 여부를 반환한다.
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d){
    double ab = ccw(a, b, c) * ccw(a, b, d);
    double cd = ccw(c, d, a) * ccw(c, d, b);
    // 두 선분이 한 직선 위에 있거나 끝 점이 겹치는 경우
    if (ab == 0 && cd == 0){
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        return !(b < c || a > d);
    }
    return ab <= 0 && cd <= 0;
}

# 점과 선 사이의 거리
코드 15.6 점과 선 사이의 거리를 계산하는 함수 pointToLine()의 구현
// 벡터의 사영을 이용해 수선의 발을 먼저 구하고, 이를 이용해 거리를 구한다.
// 점 p에서 (a,b)직선에 내린 수선의 발 구하기
vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b){
    return a + (p - a).project(b-a);
}
// 점 p와 (a,b)직선 사이의 거리를 구하기
double pointToLine(vector2 p, vector2 a, vector2 b){
    return (p - perpendicularFoot(p,a,b)).norm();
} 