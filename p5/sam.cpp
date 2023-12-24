#include <algorithm>
#include <iostream>
#include <string>
#include "Dlist.h"
#include "Instr.h"
const int memory=16;


class Stack {
private:
    Dlist<int> stack;
public:
    int pop() {
        int *p = stack.removeBack();
        int copy = *p;
        delete p;
        return copy;
    }

    void push(int num) {
        stack.insertBack(new int(num));
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack& given) {
        os << given.stack;
        return os;
    }
    };

    class List {
    private:
        Dlist<Instr> list;
    public:
        void push_instr_back(Instr num) {
            list.insertBack(new Instr(num));
        }

        bool isEmpty() {
            return list.isEmpty();
        }

        Instr pop() {
            Instr *p = list.removeFront();
            Instr copy = *p;
            delete p;
            return copy;
        }

        friend std::ostream& operator<< (std::ostream& os, const List& dl) {
            os<<dl.list;
            return os;
        }
    };
    void ADD(Stack& stack) {
        stack.push(stack.pop()+stack.pop());
}
    void NOR(Stack& stack) {
        stack.push(~(stack.pop()|stack.pop()));
}

    void LOAD(Stack& stack, int* array) {
    stack.push(array[stack.pop()]);
}
    void STORE(Stack& stack, int* array) {
        int index = stack.pop();
        array[index] = stack.pop();

}
    void work(Stack &stack, List &list, int *array, bool ifs) {
        while (!list.isEmpty()) {
            Instr current = list.pop();
            switch (current.name) {
                case InstrName::ADD: {
                    ADD(stack);
                    break;
                }
                case InstrName::NOR: {
                    NOR(stack);
                    break;
                }
                case InstrName::IFZ: {
                    if(stack.pop()==0){
                        for(int i=0;i<current.parameter;i++)
                            list.pop();
                    }
                    break;
                }
                case InstrName::HALT: {
                    while (!list.isEmpty()) {
                        list.pop();}
                    if(ifs){
                        std::cout<<stack<<"\n";
                        for(int i=0;i<memory;i++){
                            std::cout<<array[i]<<" ";
                        }
                        std::cout<<std::endl;
                    }
                    break;
                }
                case InstrName::LOAD: {
                    LOAD(stack,array);
                    break;
                }
                case InstrName::STORE: {
                    STORE(stack,array);
                    break;
                }
                case InstrName::POP: {
                    stack.pop();
                    break;
                }
                case InstrName::PUSHI: {
                    stack.push(current.parameter);
                    break;
                }
                case InstrName::NOOP: {
                    break;
                }
                default:
                    break;
            }
            if (!ifs) {
                cout << current << "\n" << stack << "\n" << list<<"\n";
                for(int i=0;i<memory;i++){
                cout<<array[i]<<" ";}
                cout<<endl;
            }
            }
        }


    int main(int argc, char *argv[]) {
        Stack stack;
        List list;
        int *array = new int[memory];
        int m, n;
        cin >> m >> n;
        while (m != 0) {
            int temp;
            cin >> temp;
            stack.push(temp);
            m--;
        }
        while (n != 0) {
            Instr temp;
            cin >> temp;
            list.push_instr_back(temp);
            n--;
        }
        for (int i = 0; i < memory; i++) {
            int temp;
            cin >> temp;
            array[i] = temp;
        }
        bool ifs = false;
        if (argc > 1) {
            string str = argv[1];
            if (str == "-s") {
                ifs = true;
            }
        }
        work(stack,list,array,ifs);
        delete[] array;
        return 0;
    }
