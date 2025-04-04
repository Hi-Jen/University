#include <iostream>
using namespace std;

class arrInt3 {
public:
    arrInt3(int d1, int d2, int d3);
    int GetAt(int p1, int p2, int p3);
    void SetAt(int p1, int p2, int p3, int v);
private:
    int * arr_;
    int d1_, d2_, d3_;
};

arrInt3::arrInt3(int d1, int d2, int d3) {
    d1_ = d1;
    d2_ = d2;
    d3_ = d3;
    arr_ = new int[d1 * d2 * d3];
    for (int i = 0; i < d1 * d2 * d3; i++) {
        arr_[i] = 0;  
    }
}

int arrInt3::GetAt(int p1, int p2, int p3) {
    if (p1 < 0 || p1 >= d1_ || p2 < 0 || p2 >= d2_ || p3 < 0 || p3 >= d3_) {
        return -1;
    }
    return arr_[(p1 * d2_ * d3_) + (p2 * d3_) + p3];
}

void arrInt3::SetAt(int p1, int p2, int p3, int v) {
    if (p1 >= 0 && p1 < d1_ && p2 >= 0 && p2 < d2_ && p3 >= 0 && p3 < d3_) {
        arr_[(p1 * d2_ * d3_) + (p2 * d3_) + p3] = v;
    }
}

int main() {
    int d1, d2, d3;
    int x, y, z, v;

    cin >> d1 >> d2 >> d3;
    arrInt3 cube(d1, d2, d3);

    for (int i = 0; i < 3; i++) {
        cin >> x >> y >> z >> v;
        cube.SetAt(x, y, z, v);
    }

    cin >> x >> y >> z;
    cout << cube.GetAt(x, y, z) << endl;

    return 0;
}
