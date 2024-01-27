/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** CpuModule
*/

#ifndef CPUMODULE_HPP_
#define CPUMODULE_HPP_
#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <cmath>
#include <deque>

class CpuModule{
    public:
        CpuModule();
        ~CpuModule();
        std::string getCpu();
        float TotalCPUpercent(std::string buf);
        std::string getTotalCpu();
        void reformate_cpu();
        void parseCpuStats();
        int parseNbrCore();
        std::deque<std::string> openNbCore(int core);
        void PopCompute(std::deque<std::string> dq);

    protected:
    private:
        std::string _cpu_usage;
        std::string _buffer;
        std::string _userStr;
        std::string _niceStr;
        std::string _systemStr;
        std::string _idleStr;
        std::string _iowaitStr;
        std::string _irqStr;
        std::string _softirqStr;
        long long _user;
        long long _nice;
        long long _system;
        long long _idle;
        long long _iowait;
        long long _irq;
        long long _softirq;
        long long _hundred;
};

#endif /* !CPUMODULE_HPP_ */