//
// Created by light on 12/4/24.
//

#include "../constants.h"
#include "../color.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <unistd.h>

std::ostringstream getConfigFolderPath()
{
    std::ostringstream sourceDirectory {};

    assert(getenv("USER") && "user environment is null");

    sourceDirectory << "/home/" << getenv("USER")
                    << "/.config/" << constants::toolName << '/';

    return sourceDirectory;
}

std::string getPmCfgFilePath(std::string_view pmName)
{
    return (getConfigFolderPath() << pmName << ".cfg").str();
}

std::string getDistroId()
{
    std::ifstream osRelease {"/etc/os-release"};

    std::string line {};

    while (std::getline(osRelease,line))
    {
        //search for id
        if (line.substr(0,3) == "ID=")
        {
            return line.substr(3);
        }
    }

    //handle the case with no support for os-release

    std::cout << color::red("your distrobution doesn't support /etc/os-release \n");
    std::cout << "Enter distro id (without spaces): ";
    std::string id {};
    std::cin >> id;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    return id;
}

void insureDir(std::string_view path)
{
    if (!std::filesystem::exists(path))
    {
        std::ostringstream cmd {};
        cmd << "mkdir -p " << path;
        system(cmd.str().c_str());
    }
}

std::string_view getLongestDirectoryPath(std::string_view filePath)
{
    while (filePath.back() != '/' || filePath.empty())
    {
        filePath.remove_suffix(1);
    }

    //we use function parameter for address so its fine returning a pointer
    return filePath;
}

bool fileExists(std::string_view path){ return std::fstream{ path.data() }.good(); };

void insureFile(std::string_view path)
{
    //makes sure the directory that holds path exists
    insureDir( getLongestDirectoryPath(path) );

    if (!fileExists(path))
    {
        std::ostringstream cmd {};
        cmd << "touch " << path;
        system(cmd.str().c_str());
    }



}

void insureSourceDir()
{
    insureDir(getConfigFolderPath().str());
}