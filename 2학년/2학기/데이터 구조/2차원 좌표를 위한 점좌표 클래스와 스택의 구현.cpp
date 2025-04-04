#include <iostream>
using namespace std;

class point;
class node {
public:
    node(point * p, node * n = 0) {
        next = n;
        ppt = p;
    }
// private: 코딩상의 편의를 위하여 모두 public으로 한다.
    node * next;
    point * ppt;
};

class point {
public:
    int x, y;
    point (int a, int b) {
        x = a;
        y = b;
    }
};

class node;

class stack {
public:
    node * top;
    stack() {
          top = nullptr;
    }

    void Push(point *p) {
        top = new node(p, top);
    }

    void Push(int a, int b) {
        Push(new point(a,b));
    }

    point *Pop() {
        if (top == nullptr) return nullptr;
        node * temp = top;
        point *ppt = top -> ppt;
        top = top -> next;
        delete temp;
        return ppt;
    }
};

int main() {
  int a, b, c, d;
  stack * s = new stack();

  cin >> a >> b >> c >> d;
  s->Push(new point(a,b));
  s->Push(c,d);
  point * ppt = s->Pop();
  cout << ppt->x << " " << ppt->y << " ";
  delete ppt;
  ppt = s->Pop();
  cout << ppt->x << " " << ppt->y << endl;
  delete ppt;
  return 0;
};
