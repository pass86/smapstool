#pragma once

#include "smapsinfo.h"
#include <map>
#include <string>
#include <memory>

class SmapsTool {
  public:
    bool LoadFile(const std::string& fileName);
    void PrintCodeMemory();

  private:
    auto GetCodeVMAInfos() -> std::shared_ptr<std::vector<std::shared_ptr<VirtualMemoryAreaInfo>>>;
    bool IsCodePathName(const std::string& pathName);
    void SortVMAInfos(std::shared_ptr<std::vector<std::shared_ptr<VirtualMemoryAreaInfo>>> vmaInfos);
    void PrintVMAInfos(std::shared_ptr<std::vector<std::shared_ptr<VirtualMemoryAreaInfo>>> vmaInfos);

    std::map<std::string, std::shared_ptr<VirtualMemoryAreaInfo>> m_VMAInfos;
};
