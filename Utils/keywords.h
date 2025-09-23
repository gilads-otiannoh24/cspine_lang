#pragma once
#include <string>
#include <unordered_map>

enum class KeywordType
{
    PRINT,
    LET,
    FN,
    NONE // means it's just a variable/identifier
};

inline KeywordType lookupKeyword(const std::string &word)
{
    static const std::unordered_map<std::string, KeywordType> keywords = {
        {"print", KeywordType::PRINT},
        {"let", KeywordType::LET},
        {"fn", KeywordType::FN}};

    auto it = keywords.find(word);
    return it != keywords.end() ? it->second : KeywordType::NONE;
}
