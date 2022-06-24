#pragma once
#include "fstream"
#include "utilities.h"
#include "unordered_map"

class settingLoader {
   private:
    string path;
    std::unordered_map<string, string> setting;

   public:
    settingLoader(string path);
    std::pair<string, string> parseSettingString(std::string setting);
    string getSetting(string setting);
};
