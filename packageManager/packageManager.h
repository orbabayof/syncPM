//
// Created by light on 12/4/24.
//

#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H



#include <array>
#include <fstream>
#include <string>

class packageManager
{
public:

    enum Command
    {
        install,
        update,

        max_commands
    };

    using PackageName_t = std::string_view;

    packageManager();
    void installPackage(PackageName_t packageName);


private:

    // must be first, the other two depend on it
    std::string m_id {};

    std::fstream m_packages {};
    std::fstream m_commands {};

    constexpr static std::array<Command,max_commands> allCmd {install, update};

    static std::fstream fileSetup(const char* fileName);

    void resetFilesPtrs();

    static std::string_view getCommandName(Command command);
    std::string getCommandFromStorage(Command command);
    void setSingleCommandWithUserIn(Command command);
    void setCommandsWithUserIn();
    void insureCommands();

    bool wasPackageRegistered(std::string_view packageName);
    void insurePackageRegistered(PackageName_t packageName);
};

#endif //PACKAGEMANAGER_H
