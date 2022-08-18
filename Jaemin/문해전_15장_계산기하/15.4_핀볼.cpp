#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
const double PI = 2.0 * acos(0.0);



struct vector2{
    double x, y;

    // 생성자를 explicit으로 지정하면 vector2를 넣을 곳에 잘못해서 실수가 들어가는 일을 방지해준다.
    explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_){}

    // 두 벡터의 비교
    bool operator == (const vector2& rhs) const{
        return x == rhs.x && y == rhs.y;
    }
    
    bool operator < (const vector2& rhs) const{
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }

    // 벡터의 덧셈과 뺄셈
    vector2 operator + (const vector2& rhs) const{
        return vector2(x + rhs.x, y + rhs.y);
    }
    vector2 operator - (const vector2& rhs) const{
        return vector2(x - rhs.x, y - rhs.y);
    }
    // 실수로 곱셈
    vector2 operator * (double rhs) const{
        return vector2(x * rhs, y * rhs);
    }
    // 벡터의 길이를 반환한다.
    double norm() const{
        return hypot(x,y);
    }
    // 방향이 같은 단위 벡터를 반환한다. 영벡터에 대해 호출한 경우 반환 값은 정의되지 않는다.
    vector2 normalize() const{
        return vector2(x / norm(), y / norm());
    }
    // x축의 양의 방향으로부터 이 벡터까지의 반시계 방향으로 잰 각도
    double polar() const{
        return fmod(atan2(y,x) + 2 * PI, 2*PI);
    }
    // 내적과 외적
    double dot(const vector2& rhs) const{
        return x * rhs.x + y * rhs.y;
    }
    double cross(const vector2& rhs) const{
        return x * rhs.y - y * rhs.x;
    }
    // 이 벡터를 rhs 벡터에 사영한 결과
    vector2 project(const vector2& rhs) const{
        vector2 r = rhs.normalize();
        return r * r.dot(*this);
    }
};

struct Circle{
    vector2 xy; int r; 
};

int C, x, y, dx, dy,N;
vector<Circle> circles;
const double EPSILON = 1e-9;
const double INFTY = 1e200;

// 2차 방정식 ax^2 + bx + c = 0의 모든 실근을 크기 순서대로 반환한다.
vector<double> solve2(double a, double b, double c){
    double d = b*b - 4*a*c;
    // 해가 없는 경우 (d < 0이 아니라 d가 double이므로 수치적 안정성 때문에 EPSILON과의 비교를 한다.)
    if(d < -EPSILON) return vector<double>();
    // 중근
    if (d < EPSILON) return vector<double>(1,-b / (2*a));

    vector<double> ret;
    ret.push_back((-b - sqrt(d)) / (2*a));
    ret.push_back((-b + sqrt(d)) / (2*a));
    return ret;
}

// here에 있는 공이 1초마다 dir만큼 굴러갈 때, center을 중심으로 하고
// 반지름 radius인 장애물과 몇 초 후에 충돌하는지 반환한다.
// 충돌하지 않을 경우 아주 큰 값 "INFTY"를 반환한다.
double hitCircle(vector2 here, vector2 dir, vector2 center, int radius){
    double a = dir.dot(dir);
    double b = 2 * (here - center).dot(dir);
    double c = center.dot(center) + here.dot(here) - 2 * (center.dot(here)) - radius * radius;
    vector<double> sols = solve2(a,b,c);
    if(sols.empty() ||sols[0] < EPSILON) return INFTY;
    return sols[0];
}

// here에 있던 공이 dir 방향으로 굴러와 center을 중심으로하는 장애물에서
// contact위치에서 충돌했을 때 공의 새로운 방향을 반환.
vector2 reflect(vector2 here, vector2 dir, vector2 center, vector2 contact){
    return (dir - dir.project(contact - center) * 2).normalize();
}




int main(){
    cin >> C;
    for(int epoch = 0 ; epoch < C; epoch++){
        circles.clear();
        cin >> x >> y >> dx >> dy >> N;
        for(int i = 0; i < N; i++){
            int xi, yi, ri;
            cin >> xi >> yi >> ri;
            // 박는 공 반지름 1을 빼서 장애물에 더해주는 팁
            circles.push_back({vector2(xi,yi), ri + 1});
        }

        vector2 here = vector2(x,y);
        vector2 dir = vector2(dx,dy).normalize();

        double minTime = INFTY;
        int minIdx = -1;
        int cnt = 0;
        while(cnt < 100){
            minIdx = -1;
            minTime = INFTY;
            for(int i = 0; i < N; i ++){
                double t = hitCircle(here,dir,circles[i].xy,circles[i].r);
                if(minTime > t){
                    minIdx = i;
                    minTime = t;
                }
            }
            if(minIdx == -1){
                break;
            }
            if(cnt++) cout << " ";
            cout << minIdx;
            vector2 contact = here + dir*minTime;
            dir = reflect(here,dir,circles[minIdx].xy,contact);
            here = contact;
        }
        cout << '\n';
    }
        
    
    return 0;
}