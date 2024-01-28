/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** SysInfoModule
*/

#ifndef SYSINFOMODULE_HPP_
#define SYSINFOMODULE_HPP_
#include "ErrorException.hpp"

#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>
#include <limits.h>
#include <sys/sysinfo.h>
#include <chrono>
#include <ctime>

class SysInfoModule {
    public:
        SysInfoModule();
        ~SysInfoModule();
        std::string getCpu();
        std::string OsInfo();
        std::string GetKernem();
        std::string GetUser();
        long int GetUpTime();
        std::string getHostname();
        char* TimeDate();

    protected:
    private:
};

#endif /* !SYSINFOMODULE_HPP_ */
