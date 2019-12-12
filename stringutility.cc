#include "stringutility.h"

bool StringUtility::EndsWith(const std::string& source, const std::string& ending) {
    if (source.size() < ending.size())
        return false;
    for (auto itEnding = ending.rbegin(), itSource = source.rbegin(); itEnding != ending.rend(); ++itEnding, ++itSource)
        if (*itEnding != *itSource)
            return false;
    return true;
}

auto StringUtility::Split(const std::string& source, char separator) -> std::shared_ptr<std::vector<std::string>> {
    auto elements = std::make_shared<std::vector<std::string>>();
    std::string element;
    for (auto ch : source) {
        if (ch != separator)
            element.push_back(ch);
        else if (!element.empty()) {
            elements->push_back(element);
            element.clear();
        }
    }
    if (!element.empty())
        elements->push_back(element);
    return elements;
}
