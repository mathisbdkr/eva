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
#include "ErrorException.hpp"

class CpuModule{
    public:
        CpuModule();
        ~CpuModule();
        std::string getCpu();
        float TotalCPUpercent(std::string buf);
        std::string getTotalCpu();
        void reformate_cpu();
        void parseCpuStats();
        std::string parseNbrCore();
        std::string openNbCore();
        std::deque<float> PopCompute();

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
        int _nbCore;
        long long _user;
        long long _nice;
        long long _system;
        long long _idle;
        long long _iowait;
        long long _irq;
        long long _softirq;
        long long _hundred;
        std::deque<std::string> _dq;
};

#endif /* !CPUMODULE_HPP_ */