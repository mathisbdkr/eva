/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** SysInfoModule
*/

#include "SysInfoModule.hpp"

SysInfoModule::SysInfoModule()
{
}

SysInfoModule::~SysInfoModule()
{
}

std::string SysInfoModule::GetUser() {
    char* User = getlogin();

    if (User == nullptr) {
        return "";
    }
    return User;
}

std::string SysInfoModule::GetKernem()
{
    std::ifstream fileStream("/proc/version");

    if (fileStream.is_open()) {
        std::string kernel;
        std::getline(fileStream, kernel);
        fileStream.close();
        return kernel.substr(0, kernel.find("("));
    } else {
        return "File could not be opened.\n";
    }
}

std::string SysInfoModule::OsInfo()
{
    std::ifstream fileStream("/etc/os-release");
    std::string buffer;

    if (fileStream.is_open()) {
        while (std::getline(fileStream, buffer)) {
            if (buffer.find("PRETTY_NAME") != std::string::npos) {
                fileStream.close();
                return buffer.substr(13, buffer.rfind("\"") - buffer.find("\"") - 1);
            }
        }
        fileStream.close();
        return "OS not found\n.";
    }
    return "File could not be opened.\n";
}

std::string SysInfoModule::getCpu()
{
    std::ifstream fileStream("/proc/cpuinfo");
    std::string buffer;

    if (fileStream.is_open()) {
        while (std::getline(fileStream, buffer)) {
            if (buffer.find("model name") != std::string::npos) {
                fileStream.close();
                return buffer.substr(buffer.find(':'), buffer.length() - buffer.find(':'));
            }
        }
        fileStream.close();
        return "OS not found\n.";
    }
    return "File could not be opened.\n";
}

long int SysInfoModule::GetUpTime()
{
    struct sysinfo i;
    sysinfo(&i);
    return i.uptime;
}
