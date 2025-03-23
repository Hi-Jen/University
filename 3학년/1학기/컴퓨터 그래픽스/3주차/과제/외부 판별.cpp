#include <iostream>

using namespace std;

// 외적을 이용한 방향 판별 함수
double crossProduct(double x1, double y1, double x2, double y2) {
    return x1 * y2 - y1 * x2;
}

// 점 (a, b)가 삼각형 (x1, y1), (x2, y2), (x3, y3) 내부에 있는지 확인
bool isInsideTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double a, double b) {
    // 벡터 정의
    double cross1 = crossProduct(x2 - x1, y2 - y1, a - x1, b - y1);
    double cross2 = crossProduct(x3 - x2, y3 - y2, a - x2, b - y2);
    double cross3 = crossProduct(x1 - x3, y1 - y3, a - x3, b - y3);

    // 모든 외적의 부호가 같으면 삼각형 내부에 있음
    return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0) || (cross1 <= 0 && cross2 <= 0 && cross3 <= 0);
}

int main() {
    double x1, y1, x2, y2, x3, y3, x, y;
    cout << "삼각형 세 점의 좌표를 입력하세요. (x1, y1), (x2, y2), (x3, y3): ";
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    cout << "원하는 x, y 좌표를 입력하세요. (x, y): ";
    cin >> x >> y;

    if (isInsideTriangle(x1, y1, x2, y2, x3, y3, x, y)) {
        cout << "점이 삼각형 내부에 있습니다.\n";
    }
    else {
        cout << "점이 삼각형 외부에 있습니다.\n";
    }

    return 0;
}
