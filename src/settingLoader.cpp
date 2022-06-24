#include "settingLoader.h"

settingLoader::settingLoader(string path) {
    std::ifstream iniFile(path);

    while (!iniFile.eof()) {
        string temp;
        iniFile >> temp;
        auto settingPair = parseSettingString(temp);
        setting.insert(settingPair);
        cout << settingPair.first << " " << settingPair.second << endl;
    }
}

std::pair<string, string> settingLoader::parseSettingString(std::string setting) {
    std::pair<string,string> result = {};
    int index = setting.find("=");

    if(index != -1){
        result.first = setting.substr(0, index);
        result.second = setting.substr(index + 1);
    }else{
        return {};
    }

    return result;
}

std::string settingLoader::getSetting(string settingLabel){
    return setting[settingLabel];
}