#include <iostream>
using namespace std;

class Elevator {
private:
    int currentFloor; // ���� ���� �����ϴ� ����
public:
    // ������: ���������͸� �ش� ���� ��ġ��Ŵ
    Elevator(int floor) : currentFloor(floor) {}

    // ��ư�� ���� �� ȣ��Ǵ� �Լ�
    void Button(int targetFloor) {
        while (currentFloor != targetFloor) {
            cout << "������: " << currentFloor << endl;
            if (currentFloor < targetFloor) {
                currentFloor++;
            }
            else {
                currentFloor--;
            }
        }
     
    }
    // ���� ���� �� ȣ��Ǵ� �Լ�
    void CloseDoor() {
        cout << "������: " << currentFloor << endl;
    }
};

int main() {
    Elevator a(1), b(8); // ���������� 2�� ����, a�� 1����, b�� 8���� ����

    a.Button(6); // 6�� ��ư ������ ���� ��ư ������ ���������� 6������ �̵�
    a.CloseDoor(); // ���� �̵��� ���� ���� �� ���
    cout << endl;

    b.Button(3); // 3�� ��ư ������ ���� ��ư ������ ���������� 3������ �̵�
    b.CloseDoor(); // ���� �̵��� ���� ���� �� ���

    return 0;
}