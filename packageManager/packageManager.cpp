//
// Created by light on 12/4/24.
//

#include "packageManager.h"

#include "../constants.h"
#include "../util/util.h"

#include <iostream>
#include <cassert>

#include "../color.h"

std::fstream packageManager::fileSetup(const char* fileName)
{

    const std::string commandPath { (getConfigFolderPath() << getDistroId() << '/' << fileName).str() };
    insureFile(commandPath);
    return std::fstream{ commandPath, std::ios::app | std::ios::in };
}

void packageManager::resetFilesPtrs()
{
    m_commands.seekg(0, std::ios::beg);
    m_commands.seekp(0, std::ios::beg);
    m_packages.seekg(0, std::ios::beg);
    m_packages.seekp(0, std::ios::beg);
}


std::string_view packageManager::getCommandName(Command command)
{
    switch (command)
    {
        case install:
            return "install";
        case update:
            return "update";
        case uninstall:
            return "uninstall";
        default:
            assert(command == max_commands && "getCommandName(Command): forgot to add another command parameter");
            return "undefined";
    }
}

std::string packageManager::getCommandFromStorage(Command command)
{
    std::string line {};
    std::string wantedRow { (std::ostringstream {} << getCommandName(command).data()  << '=').str() };
    std::string wantedCommand {};


    while (std::getline(m_commands,line))
    {
        if (line.find(wantedRow) != std::string::npos)
        {
            wantedCommand = line.substr( wantedRow.length());
        }
    }

    m_commands.clear();

    resetFilesPtrs();

    return wantedCommand;
}

//caller is responsable for reseting file ptrs
void packageManager::setSingleCommandWithUserIn(Command command)
{
    std::cout << "Enter " << getCommandName(command) << " comamnd: ";
    std::string commandDesc {};
    std::getline(std::cin, commandDesc);
    m_commands << getCommandName(command) << '=' << commandDesc << '\n';

    //doen't reset file pointer so the next call will be on the next line
}


void packageManager::setCommandsWithUserIn()
{
    for (auto e : allCmd)
    {
        setSingleCommandWithUserIn(e);
    }

    resetFilesPtrs();
}



void packageManager::insureCommands()
{
    bool cmdSet { true };
    for (auto e : allCmd)
    {
        if (getCommandFromStorage(e).empty())
            cmdSet = false;
    }

    if (!cmdSet)
        setCommandsWithUserIn();
}

packageManager::packageManager()
    : m_id { getDistroId() }
    , m_packages { fileSetup( constants::packageFileName ) }
    , m_commands { fileSetup( constants::commandFileName ) }
{
    insureCommands();

}

bool packageManager::wasPackageRegistered(std::string_view packageName)
{
    bool wasRegistered { false };
    for (std::string line {}; std::getline(m_packages, line);)
        if (line == packageName)
            wasRegistered = true;

    m_packages.clear();
    resetFilesPtrs();

    return wasRegistered;
}

void packageManager::insurePackageRegistered(std::string_view packageName)
{
    if (!wasPackageRegistered(packageName))
    {
        m_packages.seekp(0,std::ios::end);
        m_packages << packageName << '\n';

        resetFilesPtrs();
    }
}

int packageManager::runSystemCommand(Command command, PackageName_t packageName)
{
    std::string instCommand { getCommandFromStorage(command) };

    std::ostringstream fullCommand {};

    fullCommand << instCommand << ' ' << packageName;

    return system(fullCommand.str().c_str());
}

void packageManager::installPackage(PackageName_t packageName)
{

    int success { runSystemCommand(install, packageName ) };

    if (success == 0)
    {
        insurePackageRegistered(packageName);
    }
}

void packageManager::updatePackage(PackageName_t packageName)
{
    int success { runSystemCommand(update, packageName ) };

    if (success == 0)
    {
        insurePackageRegistered(packageName);
    }
}

void packageManager::uninstallPackage(PackageName_t packageName)
{
    int success { runSystemCommand(uninstall, packageName ) };

    if (success == 0)
    {
        removePackageFromStorage(packageName);
    }
}

void packageManager::removePackageFromStorage(PackageName_t packageName)
{
   // std::ostringstream command {};
    //sed -i '/packageName/d' PATH
    //command << "sed -i /" << packageName << "/d " << getConfigFolderPath().str() << getDistroId() << '/' <<
    //         constants::packageFileName;
    //system(command.str().c_str());
}





