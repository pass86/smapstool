#pragma once

#include <string>
#include <vector>
#include <memory>

class StringUtility {
  public:
    static bool EndsWith(const std::string& source, const std::string& ending);
    static auto Split(const std::string& source, char separator) -> std::shared_ptr<std::vector<std::string>>;
};
