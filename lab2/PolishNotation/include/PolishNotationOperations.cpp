#include "include\PolishNotationOperations.h"
#include <vector>


int Calculate(char ch,std::vector<int>& vec)
{
    if (vec.empty()) throw std::runtime_error("No arguments provided.");

    int result = (ch == '+' || ch == '-') ? 0 : 1;  
    bool first = true;  

    for (int num : vec) {
        if (first) {
            result = num;
            first = false;
        }
        else {
            switch (ch) {
            case '+': 
                result += num; 
                break;
            case '-': 
                result -= num; 
                break;
            case '*': 
                result *= num; 
                break;
            case '/':
                if (num == 0) throw std::runtime_error("Division by zero");
                result /= num;
                break;
            default: throw std::runtime_error("Unknown operation.");
            }
        }
    }   
    return result;
}

int Evaluate()
{
    /*char ch;
    std::cin >> ch; 

    if (isdigit(ch) || (ch == '-' && std::cin.peek() != ' ' && std::cin.peek() != ')')) {
        std::cin.unget();
        int num;
        std::cin >> num;
        return num;
    }

    if (ch == '(') 
    {  
        char op;
        std::cin >> op;  

        std::vector<int> args;
        while (true) 
        {
            std::cin >> ch;
            if (ch == ')') break; 

            std::cin.unget();  
            args.push_back(Evaluate());  
        }

        return Calculate(op, args);
    }

    return 0;  */
}

