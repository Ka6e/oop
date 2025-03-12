#include <iostream>
#include <map>
#include <bitset>
#include <string>


struct Args
{
    std::string source;
    std::string destination;
    std::string value;
};

Args ParseArguments(int argc, char* argv[])
{
    Args args;
    if (argc == 4)
    {
        args.source = argv[1];
        args.destination = argv[2];
        args.value = argv[3];
    }
    else
    {
        throw std::invalid_argument("Invalid arguments count\nUsage: radix.exe <source notation> <destination notation> <value>\n");
    }

    return args;
}


void checkTheRange(int radix)
{
    if (radix < 2 || radix > 36)
    {
        throw std::invalid_argument("Invalid input format. Your range of the calculus system goes beyond [2,36]\n");
    }
}

int StringToInt(const std::string& str, int radix)
{
    checkTheRange(radix);
    bool isNegative = (str[0] == '-');
    size_t startIndex;
    if (isNegative)
    {
        startIndex = 1;
    }
    else
    {
        startIndex = 0;
    }
    int result = 0;

    for (size_t i = startIndex; i < str.length(); i++)
    {
        char ch = std::toupper(str[i]);
        int digit;
        if (ch >= '0' && ch <= '9')
        {
            digit = ch - '0';
        }
        else if (ch >= 'A' && ch <= 'J')
        {
            digit = ch - 'A' + 10;
        }
        else if (ch >= 'K' && ch <= 'T')
        {
            digit = ch - 'K' + 20;
        }
        else if (ch >= 'U' && ch <= 'Z')
        {
            digit = ch - 'U' + 30;
        }
        else
        {
            throw std::invalid_argument("Invalid argument\n");
        }
        if (result > (INT32_MAX - digit) / radix) 
        {
            throw std::runtime_error("Overflow\n");
        }
        result = result * radix + digit;
    }
    return isNegative ? -result : result;
}

std::string IntToString(int n, int radix)
{
    checkTheRange(radix);
    std::string str;
    if (n == 0)
    {
        str += '0';
        return str;
    }
    bool isNegative = (n < 0);
    int num = isNegative ? -n : n;
    while (num > 0)
    {
        int remains = num % radix;
        if (remains >= 0 && remains <= 9)
        {
            str += (remains + '0');
        }
        else
        {
            str += (remains - 10) + 'A';
        }

        num /= radix;
    }
    std::reverse(str.begin(), str.end());
    return isNegative ? ('-' + str) : str;
}

int main(int argc, char* argv[])
{
    try
    {
        Args args = ParseArguments(argc, argv);
        bool error = false;
        int num = StringToInt(args.value, std::stoi(args.source));
        std::string result = IntToString(num, std::stoi(args.destination));
        std::cout << result;        
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    return 0;
}

