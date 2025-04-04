#include <iostream>
using namespace std;

class arrInt4 {
public:
    arrInt4();
    int GetAt(int p0, int p1, int p2, int p3);
    void SetAt(int p0, int p1, int p2, int p3, int v);
private:
    int arr[100]; 
    int size; // 저장공간
    int max; // 저장할 값의 최대 개수
};

struct Element {
    int indices[4]; // 4차원 인덱스
    int value; // 저장할 값
};

arrInt4::arrInt4() {
    size = 0;
    max = 20;
}

int arrInt4::GetAt(int p0, int p1, int p2, int p3) {
    if (p0 < 1 || p0 > 10 || p1 < 1 || p1 > 10 || p2 < 1 || p2 > 10 || p3 < 1 || p3 > 10) {
        return -1; // 범위를 벗어난 경우 -1 반환
    }
    // 저장된 요소를 검색하여 값 반환
    for (int i = 0; i < size; i++) {
        Element* e = reinterpret_cast<Element*>(&arr[i * sizeof(Element) / sizeof(int)]); // arr를 Element 배열처럼 사용
        if (e->indices[0] == p0 && e->indices[1] == p1 &&
            e->indices[2] == p2 && e->indices[3] == p3) {
            return e->value; // 일치하는 인덱스의 값 반환
        }
    }
    return 0; // 해당 위치에 값이 없으면 0 반환
}

void arrInt4::SetAt(int p0, int p1, int p2, int p3, int v) {
    if (p0 < 1 || p0 > 10 || p1 < 1 || p1 > 10 || p2 < 1 || p2 > 10 || p3 < 1 || p3 > 10 || v <= 0) {
        return; // 인덱스가 범위를 벗어나거나 값이 0 이하인 경우 저장하지 않음
    }

    // 이미 저장된 요소가 있는지 확인
    for (int i = 0; i < size; i++) {
        Element* e = reinterpret_cast<Element*>(&arr[i * sizeof(Element) / sizeof(int)]);
        if (e->indices[0] == p0 && e->indices[1] == p1 &&
            e->indices[2] == p2 && e->indices[3] == p3) {
            e->value = v;
            return;
        }
    }

    if (size < max) {
        Element* e = reinterpret_cast<Element*>(&arr[size * sizeof(Element) / sizeof(int)]);
        e->indices[0] = p0;
        e->indices[1] = p1;
        e->indices[2] = p2;
        e->indices[3] = p3;
        e->value = v;
        size++;
    }
}

int main() {
    arrInt4 arr;
    int w, x, y, z, v;

    for (int i = 0; i < 3; i++) {
        cin >> w >> x >> y >> z >> v;
        arr.SetAt(w, x, y, z, v);
    }

    cin >> w >> x >> y >> z;
    cout << arr.GetAt(w, x, y, z);
    return 0;
}
