#include "include\PolishNotationOperations.h"

std::stack<int> numbers;
std::stack<char> operations;

std::unordered_map<char, char>  operationsMap =
{
    {'+','+'},
    {'-','-'},
    {'*','*'},
    {'/','/'},
};

int Calculate(char ch, std::vector<int>& vec)
{
    int sum{};
	switch (ch)
	{
	case '+':
        for (auto& el : vec)
        {
            sum += el;
        }
		return sum;
	case '-':
        sum = vec[0];
        for (size_t i = 1; i < vec.size(); i++)
        {
            sum -= vec[i];
        }
        return sum;
		break;
	case '*':
        sum = vec[0];
        for (size_t i = 1 ; i < vec.size(); i++)
        {
            sum *= vec[i];
        }
        return sum;
		break;
	case '/':
        sum = vec[0];
        for (size_t i = 1; i < vec.size(); i++)
        {
            if (vec[i] == 0)
            {
    			throw std::runtime_error("Division by zero\n");
            }
            sum /= vec[i];
        }
        return sum;
		break;
	default:
		throw std::invalid_argument("Unknown operation\n");
		break;
	}
}

int CalculateTheResult(std::stack<char>& operations, std::stack<int>& numbers)
{
    std::vector<int> vec;
    while (!numbers.empty()) {
        vec.push_back(numbers.top());
        numbers.pop();
    }
    if (vec.empty()) {
        throw std::runtime_error("No numbers to calculate\n");
    }
    if (operations.empty()) {
        return vec[0]; // Если只有一个 аргумент
    }
    int result = Calculate(operations.top(), vec);
    operations.pop();
    return result;
    //std::vector<int> vec;
    //if (numbers.size() == 1)
    //{
    //    return numbers.top();
    //}
    //while (!numbers.empty())
    //{
    //    vec.push_back(numbers.top());
    //    numbers.pop();
    //}
    //int result = Calculate(operations.top(), vec);
    //return result;
}
int readNumber(std::istream& in, char firstChar) {
    std::string numberStr;
    numberStr += firstChar; // Первый символ уже прочитан
    char ch;

    while (in.get(ch)) { // Используем get для чтения без пропуска пробелов
        if (std::isdigit(ch)) {
            numberStr += ch;
        }
        else {
            in.unget(); // Возвращаем нечисловой символ
            break;
        }
    }

    try {
        return std::stoi(numberStr);
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Invalid number format\n");
    }
}
// Основная функция для вычисления выражения из потока
int EvaluateExpression(std::istringstream& in)
{
    std::stack<std::vector<int>> argsStack; // Стек векторов аргументов для каждой операции
    char ch;

    while (in >> ch) {
        if (ch == '(') {
            argsStack.push(std::vector<int>()); // Новая рамка для аргументов
            operations.push(' '); // Временный placeholder, будет заменён операцией
        }
        else if (ch == '+' || ch == '*' || ch == '-' || ch == '/') {
            if (argsStack.empty()) {
                throw std::runtime_error("Invalid expression: operation without opening parenthesis\n");
            }
            operations.top() = ch; // Устанавливаем операцию для текущей рамки
        }
        else if (ch == ')') {
            if (argsStack.empty()) {
                throw std::runtime_error("Invalid expression: extra closing parenthesis\n");
            }
            if (operations.empty() || operations.top() == ' ') {
                throw std::runtime_error("Invalid expression: no operation specified\n");
            }

            std::vector<int> vec = argsStack.top();
            argsStack.pop();
            char op = operations.top();
            operations.pop();

            int result = Calculate(op, vec);
            numbers.push(result);

            if (!argsStack.empty()) {
                argsStack.top().push_back(result); // Добавляем результат в предыдущую рамку
            }
            else {
                // Конечный результат
                return CalculateTheResult(operations, numbers);
            }
        }
        else if (std::isdigit(ch) || ch == '-') {
            in.unget(); // Возвращаем первый символ числа
            int number = readNumber(in, ch);
            if (argsStack.empty()) {
                throw std::runtime_error("Invalid expression: number outside of parentheses\n");
            }
            argsStack.top().push_back(number); // Добавляем число в текущую рамку
        }
        else {
            throw std::runtime_error("Invalid character in expression\n");
        }
    }

    throw std::runtime_error("Invalid expression: missing closing parenthesis\n");
 /*   int result{};
    char ch;
    bool begin = false;
    std::vector<int> vec;
    while (in >> ch)
    {
        if (ch == '(')
        {
            begin = true;
        }
        else if (ch == ')')
        {
            begin = false;
            result = Calculate(operations.top(), vec);
            operations.pop();
            numbers.push(result);
            vec.clear();
        }
        if (begin)
        {
            if (ch == '-' && in.peek() == std::isdigit(ch))
            {
                result = -(ch - '0');
                in >> ch;
                in >> ch;
            }
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
            {
                operations.push(ch);
            }
            if (std::isdigit(ch))
            {
                if (result != 0)
                {
                    vec.push_back(result);
                }
                vec.push_back(ch - '0');
            }
        }
    }
    return result = CalculateTheResult(operations, numbers);*/
}
void RunPolishNotation()
{	
	
	std::string str;
	while (std::getline(std::cin, str))
	{
		try
		{
			std::istringstream iss(str);
			int result = EvaluateExpression(iss);
			std::cout << result << std::endl;
		}
		catch (const std::exception& ex)
		{
			std::cerr << "ERROR: " << ex.what() << std::endl;
 		}
	}

}
