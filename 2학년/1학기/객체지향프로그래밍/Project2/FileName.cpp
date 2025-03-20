#include <iostream>
using namespace std;

class Elevator {
private:
    int currentFloor; // 현재 층을 저장하는 변수
public:
    // 생성자: 엘리베이터를 해당 층에 위치시킴
    Elevator(int floor) : currentFloor(floor) {}

    // 버튼을 누를 때 호출되는 함수
    void Button(int targetFloor) {
        while (currentFloor != targetFloor) {
            cout << "현재층: " << currentFloor << endl;
            if (currentFloor < targetFloor) {
                currentFloor++;
            }
            else {
                currentFloor--;
            }
        }
     
    }
    // 문을 닫을 때 호출되는 함수
    void CloseDoor() {
        cout << "현재층: " << currentFloor << endl;
    }
};

int main() {
    Elevator a(1), b(8); // 엘리베이터 2개 생성, a는 1층에, b는 8층에 존재

    a.Button(6); // 6층 버튼 누르고 닫힘 버튼 누르면 현재층에서 6층으로 이동
    a.CloseDoor(); // 한층 이동시 마다 현재 층 출력
    cout << endl;

    b.Button(3); // 3층 버튼 누르고 닫힘 버튼 누르면 현재층에서 3층으로 이동
    b.CloseDoor(); // 한층 이동시 마다 현재 층 출력

    return 0;
}