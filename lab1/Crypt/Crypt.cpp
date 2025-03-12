#include <iostream>
#include <bitset>
#include <fstream>
#include <string>

const int MINRANGE = 0;
const int MAXRANGE = 255;

enum class Mode
{
    CRYPT,
    DECRYPT,
};

struct Args
{
    Mode mode;
    std::string inputFile;
    std::string outputFile;
    int key{};
};


Mode SelectMode(const std::string& mode)
{
    if (mode == "crypt")
    {
        return Mode::CRYPT;
    }
    else if (mode == "decrypt")
    {
        return Mode::DECRYPT;
    }
    else
    {
        throw std::invalid_argument("Invalid mode\n");
    }
}

Args ParseArguments(int argc, char* argv[])
{
    Args args;
    if (argc == 5)
    {
        args.mode = SelectMode(std::string(argv[1]));
        args.inputFile = argv[2];
        args.outputFile = argv[3];
        try
        {
            args.key = std::stoi(argv[4]);
        }
        catch (const std::exception& ex)
        {
            throw std::invalid_argument("Invalid key fromat\n");
        }
    }
    else
    {
        throw std::invalid_argument("Invalid count of arguments\n");
    }

    if (args.key < MINRANGE || args.key > MAXRANGE)
    {
        throw std::invalid_argument("Invalid key format\n");
    }
    return args;
}

unsigned char SwapBits(unsigned char num)
{
    unsigned char result = 0;
    result |= (num & 0b00000111) << 2;
    result |= (num & 0b00011000) << 3;
    result |= (num & 0b01100000) >> 5;
    result |= (num & 0b10000000) >> 2;
    return result;

}

unsigned char ReverseleBits(unsigned char num)
{
    unsigned char result = 0;
    result |= (num & 0b00000011) << 5;
    result |= (num & 0b00011100) >> 2;
    result |= (num & 0b00100000) << 2;
    result |= (num & 0b11000000) >> 3;
    return result;

}
void Crypt(std::string& inputFiel, std::string& outputFile, int key)
{
    std::ifstream input(inputFiel, std::ios::binary | std::ios::in);
    if (!input)
    {
        throw std::runtime_error("Failed to read data from input file\n");
    }
    std::ofstream output(outputFile, std::ios::binary | std::ios:: trunc);
    if (!output)
    {
        throw std::runtime_error("Failed to wtire data to output file\n");
    }
    
    char ch;
    while (input.read(&ch, sizeof(ch)))
    {
        ch = static_cast<char>(ch ^ key);
        output.put(static_cast<char>(SwapBits(ch)));
        if (!output.flush())
        {
            throw std::runtime_error("Failed to write data to output file\n");
        }
    }
    if (!input.eof() || input.bad())
    {
        throw std::runtime_error("Failed to read data from input file\n");
    }
}

void ReverseCrypt(std::string& inputFile, std::string& outputFile, int key)
{
    std::ifstream input(inputFile, std::ios::binary | std::ios::in);
    if (!input)
    {
        throw std::runtime_error("Failed to read data from input file\n");
    }
    std::ofstream output(outputFile, std::ios::binary | std::ios::trunc);
    if (!output)
    {
        throw std::runtime_error("Failed to write data to output file\n");
    }
    char ch;
    while (input.read(&ch, sizeof(ch)))
    {
        ch = (static_cast<char>(ReverseleBits(ch)));
        output.put(static_cast<char>(ch) ^ key);
        if (!output.flush())
        {
            throw std::runtime_error("Failed to write data to output file\n");
        }
    }
    if (!input.eof() || input.bad())
    {
        throw std::runtime_error("Failed to read data from input file\n");
    }
}


int main(int argc, char* argv[])
{
    try
    {
        Args args;
        args = ParseArguments(argc, argv);
        switch (args.mode)
        {
        case Mode::CRYPT:
            Crypt(args.inputFile, args.outputFile, args.key);
            break;
        case Mode::DECRYPT:
            ReverseCrypt(args.inputFile, args.outputFile, args.key);
            break;
        default:
            break;
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}


