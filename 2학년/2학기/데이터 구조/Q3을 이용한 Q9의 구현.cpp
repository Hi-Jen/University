'시험 문제'
- q30 이었나 아무튼 무언가로 q90을 구현 하는 문제였던 것 같은데 확실하진 않음.
- 첫장 반 페이지에 Q 문제 였음.

  #include <iostream>
using namespace std;
#define ERROR -1;

class queue3 {
public:
    queue3() {
        rear=0;
    }
    bool IsEmpty() { return (rear==0); };
    bool IsFull() { return (rear==3); };
    bool InsertQ(int el) {
        if (rear==3) return false;
        arr[rear++] = el;
        return true;
    }
    int DeleteQ() {
        if (rear==0) return -1;
        int el=arr[0];
        rear--;
        for (int i=0; i< rear; i++) arr[i] = arr[i+1];
        return el;
    }
private:
    int arr[3];
    int rear;
};

class queue9 {
public:
    queue9();
    bool IsEmpty();
    bool IsFull();
    bool InsertQ(int el);
    int DeleteQ();
private:
    queue3 q1;
    queue3 *q2;
    queue3 *q3;
};

queue9::queue9() {
    q2 = new queue3();
    q3 = new queue3();
};

bool queue9::IsEmpty() {
  return (q1.IsEmpty() && q2 -> IsEmpty() && q3 -> IsEmpty());
}

bool queue9::IsFull() {
  return (q1.IsFull() && q2 -> IsFull() && q3 -> IsFull());
}

bool queue9::InsertQ(int el) {
  if(!q1.IsFull()) return q1.InsertQ(el);
  else if(!q2.IsFull()) return q2.InsertQ(el);
  else if(!q3.IsFull()) return q3.InsertQ(el);
  else return false;
}

int queue9::DeleteQ( ) {
  if(!q1.IsEmpty()) return q1.DeleteQ();
  else if(!q2.IsEmpty()) return q2.DeleteQ( );
  else if(!q3.IsEmpty()) return q3.DeleteQ( );
  else return ERROR;
}


int main() {
    int n, i, a;
    queue9 * q = new queue9();

    cin >> n;
    for (i=0; i<n; i++) {
        cin >> a;
        if (a==0) cout << q->DeleteQ() << " ";
        else q->InsertQ(a);
    }
    return 0;
};
