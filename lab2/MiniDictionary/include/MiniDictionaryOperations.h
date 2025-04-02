#pragma once
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <istream>
#include <iostream>
#include <unordered_map>

const std::string EXIT_COMMAND = "...";
const char  SEPARATOR = ' ';

using Dictionary = std::multimap<std::string, std::string>;


std::string ToLower(std::string& str);
void SaveDictionary(const std::string& filename, const Dictionary& dict, const Dictionary& originalDictionary);
std::multimap<std::string, std::string> LoadDictionary(const std::string& filename);
void UseDictionary(std::multimap<std::string, std::string>& dictionary, const std::string& filename);


