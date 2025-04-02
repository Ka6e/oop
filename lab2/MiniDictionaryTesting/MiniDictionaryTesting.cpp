#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../MiniDictionary/include/MiniDictionaryOperations.h"

void createTempDictionaryFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
}

TEST_CASE("ToLower converts string to lowercase", "[ToLower]") 
{
    SECTION("Basic uppercase string") 
    {
        std::string input = "HELLO";
        std::string expected = "hello";
        CHECK(ToLower(input) == expected);
        CHECK(input == expected); 
    }

    SECTION("Mixed case string") 
    {
        std::string input = "HeLLo WoRLD";
        std::string expected = "hello world";
        CHECK(ToLower(input) == expected);
    }

    SECTION("Empty string") 
    {
        std::string input = "";
        CHECK(ToLower(input) == "");
    }
}


TEST_CASE("LoadDictionary loads dictionary from file", "[LoadDictionary]") 
{
    SECTION("Empty file") 
    {
        createTempDictionaryFile("empty.txt", "");
        Dictionary dict = LoadDictionary("empty.txt");
        CHECK(dict.empty());
        std::remove("empty.txt");
    }

    SECTION("Valid dictionary file") 
    {
        std::string content = "cat кошка\ncat кот\ndog собака\n";
        createTempDictionaryFile("dict.txt", content);
        Dictionary dict = LoadDictionary("dict.txt");
        CHECK(dict.size() == 3);
        auto range = dict.equal_range("cat");
        CHECK(std::distance(range.first, range.second) == 2);
        CHECK(range.first->second == "кошка");
        CHECK((++range.first)->second == "кот");
        CHECK(dict.find("dog")->second == "собака");
        std::remove("dict.txt");
    }

    SECTION("Non-existent file") 
    {
        Dictionary dict = LoadDictionary("nonexistent.txt");
        CHECK(dict.empty());
    }
}

TEST_CASE("SaveDictionary saves only new entries", "[SaveDictionary]") 
{
    SECTION("Empty original dictionary") 
    {
        Dictionary dict{ {"cat", "кошка"}, {"dog", "собака"} };
        Dictionary originalDict;
        SaveDictionary("output.txt", dict, originalDict);
        std::ifstream file("output.txt");
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        CHECK(content == "cat кошка\ndog собака\n");
        std::remove("output.txt");
    }

    SECTION("Non-empty original dictionary") 
    {
        Dictionary originalDict{ {"cat", "кошка"} };
        Dictionary dict{ {"cat", "кошка"}, {"cat", "кот"}, {"dog", "собака"} };
        SaveDictionary("output.txt", dict, originalDict);
        std::ifstream file("output.txt");
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        CHECK_FALSE(content == "cat кот\ndog собака\n"); 
        std::remove("output.txt");
    }
}

TEST_CASE("UseDictionary handles user interaction", "[UseDictionary]") 
{
    SECTION("Translate existing word and exit") 
    {
        Dictionary dict{ {"cat", "кошка"}, {"cat", "кот"} };
        std::stringstream input("cat\n...\n");
        std::stringstream output;
        std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
        std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        UseDictionary(dict, "test.txt");

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        std::string expected = "> кошка, кот, \n> До свидания.\n";
        CHECK(output.str() == expected);
    }

    SECTION("Add new translation and save") 
    {
        Dictionary dict{ {"cat", "кошка"} };
        std::stringstream input("dog\nсобака\n...\nY\n");
        std::stringstream output;
        std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
        std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        UseDictionary(dict, "test.txt");

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        std::string expected = \
            "> Неизвестное слово \"dog\". Введите перевод или пустую строку для отказа.\n" \
            "> Слово \"dog\" сохранено в словаре как \"собака\".\n" \
            "> В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n" \
            "> Изменения сохранены. До свидания.\n";
        CHECK(output.str() == expected);

        std::ifstream file("test.txt");
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        CHECK(content == "dog собака\n");
        std::remove("test.txt");
    }

    SECTION("Ignore new translation") 
    {
        Dictionary dict{ {"cat", "кошка"} };
        std::stringstream input("dog\n\n...\n");
        std::stringstream output;
        std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
        std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        UseDictionary(dict, "test.txt");

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        std::string expected = \
            "> Неизвестное слово \"dog\". Введите перевод или пустую строку для отказа.\n" \
            "> Слово \"dog\" проигнорировано.\n" \
            "> До свидания.\n";
        CHECK(output.str() == expected);
    }
}