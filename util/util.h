//
// Created by light on 12/4/24.
//

#ifndef UTIL_H
#define UTIL_H

#include <sstream>
#include <string_view>


std::ostringstream getConfigFolderPath();

std::string getPmCfgFilePath(std::string_view pmName);

std::string getDistroId();

void insureDir(std::string_view path);

std::string_view getLongestDirectoryPath(std::string_view filePath);

void insureFile(std::string_view path);

void insureSourceDir();

#endif //UTIL_H
