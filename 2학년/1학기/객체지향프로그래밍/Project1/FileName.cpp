#include <iostream>

class Gate {
protected:
    int x, y; 
    int output; 
public:
    void input(int x_val, int y_val) {
        x = x_val;
        y = y_val;
    }

    int result() const {
        return output;
    }
};

class AndGate : public Gate {
public:
    void op() {
        output = x && y;
    }
};

class OrGate : public Gate {
public:
    void op() {
        output = x || y;
    }
};

int main() {
    AndGate a_and, b_and;
    OrGate c_or;

    a_and.input(1, 0);// AND 게이트 
    a_and.op();
    std::cout << "AND input: 1 0 -> " << a_and.result() << std::endl; 

    a_and.input(1, 1);
    a_and.op();
    std::cout << "AND input: 1 1 -> " << a_and.result() << std::endl; 

    c_or.input(1, 0);// OR 게이트 
    c_or.op();
    std::cout << "OR input: 1 0 -> " << c_or.result() << std::endl; 

    b_and.input(1, 0);
    b_and.op();
    std::cout << "AND input: 1 0 -> " << b_and.result() << std::endl; 

    b_and.input(1, 1);
    b_and.op();
    std::cout << "AND input: 1 1 -> " << b_and.result() << std::endl;

    c_or.input(a_and.result(), b_and.result());
    c_or.op();
    std::cout << "OR input: 0 1 -> " << c_or.result() << std::endl; 

    return 0;
}