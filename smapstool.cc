#include "smapstool.h"
#include "stringutility.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

bool SmapsTool::LoadFile(const std::string& fileName) {
    std::ifstream fileStream(fileName);
    if (!fileStream.is_open()) {
        std::cout << "Open failed " << fileName << std::endl;
        return false;
    }
    m_VMAInfos.clear();
    std::shared_ptr<VirtualMemoryAreaInfo> info;
    for (std::string line; std::getline(fileStream, line); ) {
        auto lineElements = StringUtility::Split(line, ' ');
        if (lineElements->size() >= 6) {
            auto address = StringUtility::Split(lineElements->at(0), '-');
            if (address->size() != 2)
                continue;
            // Format: address perms offset dev inode pathname
            auto pathName = lineElements->at(5);
            auto it = m_VMAInfos.find(pathName);
            if (it != m_VMAInfos.end()) {
                info = it->second;
                continue;
            }
            info = std::make_shared<VirtualMemoryAreaInfo>();
            info->pathName = pathName;
            m_VMAInfos.insert(std::make_pair(pathName, info));
        } else if (lineElements->size() == 3) {
            // Format: type size kB
            auto type = lineElements->at(0);
            if (type == "Pss:")
                info->pss += std::stoi(lineElements->at(1));
        }
    }
    return true;
}

void SmapsTool::PrintCodeMemory() {
    auto codeInfos = GetCodeVMAInfos();
    SortVMAInfos(codeInfos);
    PrintVMAInfos(codeInfos);
}

auto SmapsTool::GetCodeVMAInfos() -> std::shared_ptr<std::vector<std::shared_ptr<VirtualMemoryAreaInfo>>> {
    auto vmaInfos = std::make_shared<std::vector<std::shared_ptr<VirtualMemoryAreaInfo>>>();
    for (auto kv : m_VMAInfos)
        if (kv.second->pss > 0 && IsCodePathName(kv.second->pathName))
            vmaInfos->push_back(kv.second);
    return vmaInfos;
}

bool SmapsTool::IsCodePathName(const std::string& pathName) {
    return StringUtility::EndsWith(pathName, ".so") ||
        StringUtility::EndsWith(pathName, ".jar") ||
        StringUtility::EndsWith(pathName, ".apk") ||
        StringUtility::EndsWith(pathName, ".ttf") ||
        StringUtility::EndsWith(pathName, ".dex") ||
        StringUtility::EndsWith(pathName, ".oat") ||
        StringUtility::EndsWith(pathName, ".ZygoteJIT") ||
        StringUtility::EndsWith(pathName, ".AppJIT");
}

void SmapsTool::SortVMAInfos(std::shared_ptr<std::vector<std::shared_ptr<VirtualMemoryAreaInfo>>> vmaInfos) {
    std::sort(vmaInfos->begin(), vmaInfos->end(), [](std::shared_ptr<VirtualMemoryAreaInfo> a, std::shared_ptr<VirtualMemoryAreaInfo> b) {
        return a->pss > b->pss;
    });
}

void SmapsTool::PrintVMAInfos(std::shared_ptr<std::vector<std::shared_ptr<VirtualMemoryAreaInfo>>> vmaInfos) {
    std::cout << "PathName,Pss" << std::endl;
    for (auto info : *vmaInfos)
        std::cout << info->pathName << "," << info->pss << std::endl;
}
