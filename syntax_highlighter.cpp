#include "syntax_highlighter.h"
#include <iostream>
#include <regex>
#include <vector>

std::string applySyntaxHighlighting(const std::string& line, const std::string& language) {
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m"; // For comments
    const std::string RESET = "\033[0m";

    std::vector<std::pair<std::string, std::string>> keywords;

    if (language == "cpp") {
        keywords = {
            {"int", RED}, {"float", RED}, {"double", RED}, {"char", RED},
            {"return", RED}, {"if", RED}, {"else", RED}, {"while", RED}, {"for", RED},
            {"class", RED}, {"include", RED}, {"using", RED}, {"namespace", RED},
            {"void", RED}, {"public", RED}, {"private", RED}, {"protected", RED}
        };
    } else if (language == "python") {
        keywords = {
            {"def", RED}, {"import", RED}, {"class", RED}, {"if", RED},
            {"elif", RED}, {"else", RED}, {"return", RED}, {"for", RED}, {"while", RED},
            {"try", RED}, {"except", RED}, {"with", RED}, {"as", RED}
        };
    } else if (language == "javascript") {
        keywords = {
            {"function", RED}, {"let", RED}, {"var", RED}, {"const", RED},{"let", RED},{"alert", RED},
            {"if", RED}, {"else", RED}, {"for", RED}, {"while", RED},
            {"return", RED}, {"class", RED}, {"import", RED}, {"export", RED}
        };
    }

    std::string highlightedLine = line;

    // Highlight comments (basic)
    if (language == "cpp" || language == "javascript") {
        std::regex commentRegex("//.*");
        highlightedLine = std::regex_replace(highlightedLine, commentRegex,
                                             GREEN + std::string("$&") + RESET);
    } else if (language == "python") {
        std::regex commentRegex("#.*");
        highlightedLine = std::regex_replace(highlightedLine, commentRegex,
                                             GREEN + std::string("$&") + RESET);
    }

    // Highlight keywords
    for (const auto& keyword : keywords) {
        std::regex keywordRegex("\\b" + keyword.first + "\\b");
        highlightedLine = std::regex_replace(highlightedLine, keywordRegex,
                                             keyword.second + keyword.first + RESET);
    }

    return highlightedLine;
}
