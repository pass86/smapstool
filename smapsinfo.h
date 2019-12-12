#pragma once

#include <string>
#include <cstdint>

struct VirtualMemoryAreaInfo {
    uint32_t pss = 0;
    std::string pathName;
};
