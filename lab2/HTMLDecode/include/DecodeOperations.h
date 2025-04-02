#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

using UnorderedMap = std::unordered_map<std::string, char>;

const UnorderedMap htmlEntities = {
    {"&quot;", '"'},
    {"&apos;", '\''},
    {"&lt;", '<'},
    {"&gt;", '>'},
    {"&amp;", '&'}
};

std::string HtmlDecode(std::string const& html);
