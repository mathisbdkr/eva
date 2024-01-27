/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** SysInfoModule
*/

#ifndef SYSINFOMODULE_HPP_
#define SYSINFOMODULE_HPP_

#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>
#include <sys/sysinfo.h>

class SysInfoModule {
    public:
        SysInfoModule();
        ~SysInfoModule();
        std::string getCpu();
        std::string OsInfo();
        std::string GetKernem();
        std::string GetUser();
        long int GetUpTime();
    protected:
    private:
};

#endif /* !SYSINFOMODULE_HPP_ */
