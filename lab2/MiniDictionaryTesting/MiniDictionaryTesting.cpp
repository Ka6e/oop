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
        std::string content = "cat �����\ncat ���\ndog ������\n";
        createTempDictionaryFile("dict.txt", content);
        Dictionary dict = LoadDictionary("dict.txt");
        CHECK(dict.size() == 3);
        auto range = dict.equal_range("cat");
        CHECK(std::distance(range.first, range.second) == 2);
        CHECK(range.first->second == "�����");
        CHECK((++range.first)->second == "���");
        CHECK(dict.find("dog")->second == "������");
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
        Dictionary dict{ {"cat", "�����"}, {"dog", "������"} };
        Dictionary originalDict;
        SaveDictionary("output.txt", dict, originalDict);
        std::ifstream file("output.txt");
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        CHECK(content == "cat �����\ndog ������\n");
        std::remove("output.txt");
    }

    SECTION("Non-empty original dictionary") 
    {
        Dictionary originalDict{ {"cat", "�����"} };
        Dictionary dict{ {"cat", "�����"}, {"cat", "���"}, {"dog", "������"} };
        SaveDictionary("output.txt", dict, originalDict);
        std::ifstream file("output.txt");
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        CHECK_FALSE(content == "cat ���\ndog ������\n"); 
        std::remove("output.txt");
    }
}

TEST_CASE("UseDictionary handles user interaction", "[UseDictionary]") 
{
    SECTION("Translate existing word and exit") 
    {
        Dictionary dict{ {"cat", "�����"}, {"cat", "���"} };
        std::stringstream input("cat\n...\n");
        std::stringstream output;
        std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
        std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        UseDictionary(dict, "test.txt");

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        std::string expected = "> �����, ���, \n> �� ��������.\n";
        CHECK(output.str() == expected);
    }

    SECTION("Add new translation and save") 
    {
        Dictionary dict{ {"cat", "�����"} };
        std::stringstream input("dog\n������\n...\nY\n");
        std::stringstream output;
        std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
        std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        UseDictionary(dict, "test.txt");

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        std::string expected = \
            "> ����������� ����� \"dog\". ������� ������� ��� ������ ������ ��� ������.\n" \
            "> ����� \"dog\" ��������� � ������� ��� \"������\".\n" \
            "> � ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������.\n" \
            "> ��������� ���������. �� ��������.\n";
        CHECK(output.str() == expected);

        std::ifstream file("test.txt");
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        CHECK(content == "dog ������\n");
        std::remove("test.txt");
    }

    SECTION("Ignore new translation") 
    {
        Dictionary dict{ {"cat", "�����"} };
        std::stringstream input("dog\n\n...\n");
        std::stringstream output;
        std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
        std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        UseDictionary(dict, "test.txt");

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        std::string expected = \
            "> ����������� ����� \"dog\". ������� ������� ��� ������ ������ ��� ������.\n" \
            "> ����� \"dog\" ���������������.\n" \
            "> �� ��������.\n";
        CHECK(output.str() == expected);
    }
}