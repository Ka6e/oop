#include "../../MiniDictionary/include/MiniDictionaryOperations.h"


std::string ToLower(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), 
        [](unsigned char c){ 
            return std::tolower(c); 
        });
    return str;
}

std::multimap<std::string, std::string> LoadDictionary(const std::string& filename)
{
	Dictionary dictionary;
	std::ifstream file(filename);
	if (!file)
	{
		return dictionary;
	}

	std::string line;
	while (std::getline(file, line))
	{
		size_t pos = line.find(SEPARATOR);
		if (pos != std::string::npos)
		{
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 1);
			dictionary.insert({ key, value });
		}
	}
	return dictionary;
}

void SaveDictionary(const std::string& filename, const Dictionary& dict, const Dictionary& originalDictionary)
{
	std::ofstream output(filename, std::ios::trunc);
	for (const auto& [key, value]: dict)
	{
		if (originalDictionary.find(key) == originalDictionary.end())
		{
			output << key << SEPARATOR << value << std::endl;
		}
	}

}

void ProcessUnknownWord(std::multimap<std::string, std::string>& dictionary, const std::string& inputWord, bool& modified)
{
    std::cout << "Неизвестное слово \"" << inputWord << "\". Введите перевод или пустую строку для отказа.\n> ";
    std::string translation;
    std::getline(std::cin, translation);

    if (!translation.empty())
    {
        dictionary.insert({ inputWord, translation });
        modified = true;
        std::cout << "Слово \"" << inputWord << "\" сохранено в словаре как \"" << translation << "\".\n";
    }
    else
    {
        std::cout << "Слово \"" << inputWord << "\" проигнорировано.\n";
    }
}

void DisplayTranslations(const std::multimap<std::string, std::string>& dictionary, const std::string& inputWord)
{
    auto range = dictionary.equal_range(inputWord);
    for (auto it = range.first; it != range.second; ++it)
    {
        std::cout << it->second << ", ";
    }
    std::cout << "\n";
}

bool ConfirmSave()
{
    std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n> ";
    std::string response;
    std::getline(std::cin, response);
    return (response == "Y" || response == "y");
}

void UseDictionary(std::multimap<std::string, std::string>& dictionary, const std::string& filename)
{
    std::multimap<std::string, std::string> originalDictionary = dictionary; 
    std::string inputWord;
    bool modified = false;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, inputWord);
        ToLower(inputWord);

        if (inputWord == EXIT_COMMAND)
        {
            break;
        }

        auto range = dictionary.equal_range(inputWord);
        if (range.first == range.second)
        {
            ProcessUnknownWord(dictionary, inputWord, modified);
        }
        else
        {
            DisplayTranslations(dictionary, inputWord);
        }
    }

    if (modified && ConfirmSave())
    {
        SaveDictionary(filename, dictionary, originalDictionary);
        std::cout << "Изменения сохранены. До свидания.\n";
    }
    else
    {
        std::cout << "До свидания.\n";
    }
}