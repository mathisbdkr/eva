/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** CpuModule
*/

 #include "CpuModule.hpp"

 CpuModule::CpuModule()
 {
 }

 CpuModule::~CpuModule()
 {
 }

void CpuModule::reformate_cpu()
{

    _userStr = _buffer.substr(0, _buffer.find(' '));
    _buffer = _buffer.substr(_buffer.find(' ') + 1, _buffer.length() - _buffer.find(' '));

    _niceStr = _buffer.substr(0, _buffer.find(' '));
    _buffer = _buffer.substr(_buffer.find(' ') + 1, _buffer.length() - _buffer.find(' '));

    _systemStr = _buffer.substr(0, _buffer.find(' '));
    _buffer = _buffer.substr(_buffer.find(' ') + 1, _buffer.length() - _buffer.find(' '));

    _idleStr = _buffer.substr(0, _buffer.find(' '));
    _buffer = _buffer.substr(_buffer.find(' ') + 1, _buffer.length() - _buffer.find(' '));

    _iowaitStr = _buffer.substr(0, _buffer.find(' '));
    _buffer = _buffer.substr(_buffer.find(' ') + 1, _buffer.length() - _buffer.find(' '));

    _irqStr = _buffer.substr(0, _buffer.find(' '));
    _buffer = _buffer.substr(_buffer.find(' ') + 1, _buffer.length() - _buffer.find(' '));

    _softirqStr = _buffer.substr(0, _buffer.find(' '));
    _buffer = _buffer.substr(_buffer.find(' ') + 1, _buffer.length() - _buffer.find(' '));

}

void CpuModule::parseCpuStats()
{
    _user = std::stoll(_userStr, 0);
    _nice = std::stoll(_niceStr, 0);
    _system = std::stoll(_systemStr, 0);
    _idle = std::stoll(_idleStr, 0);
    _iowait = std::stoll(_iowaitStr, 0);
    _irq = std::stoll(_irqStr, 0);
    _softirq = std::stoll(_softirqStr, 0);
    _hundred = 100;
}

float CpuModule::TotalCPUpercent(std::string buf)
{
    _buffer = buf;
    reformate_cpu();
    parseCpuStats();

    long long totalOne = _user + _nice + _system + _idle + _iowait + _irq + _softirq;
    long long workOne = _user + _nice + _system;

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    _buffer = getTotalCpu();

    reformate_cpu();

    parseCpuStats();

    double totalTwo = _user + _nice + _system + _idle + _iowait + _irq + _softirq;
    double workTwo = _user + _nice + _system;

    double totalPeriod = totalTwo - totalOne;
    double totalWork = workTwo - workOne;

    float res = (totalWork / totalPeriod) * 100;
    return res;
}

std::string CpuModule::getTotalCpu()
{
    std::ifstream fileStream("/proc/stat");

    if (fileStream.is_open()) {
        while (std::getline(fileStream, _buffer)) {
            if (_buffer.find("cpu") != std::string::npos) {
                fileStream.close();
                return _buffer.substr(_buffer.find(' ') + 2, _buffer.length() - _buffer.find(' '));
            }
        }
        fileStream.close();
        try {
            throw OSNotFoundException();
        } catch (const OSNotFoundException& message) {
            std::cerr << "Caught exception: " << message.what() << std::endl;
            return message.what();
        }
    } else {
        try {
            throw FileOpenException();
        } catch (const FileOpenException& message) {
            std::cerr << "Caught exception: " << message.what() << std::endl;
            return message.what();
        }
    }
}

std::string CpuModule::parseNbrCore()
{
    std::ifstream fileStream("/proc/cpuinfo");
    std::string buffer;
    std::string coreStr;

    if (fileStream.is_open()) {
        while (std::getline(fileStream, buffer)) {
            if (buffer.find("processor") != std::string::npos) {
                coreStr = buffer.substr(buffer.find(':') + 1, buffer.length() - (buffer.find(':') + 1));
            }
        }
        _nbCore = atoi(coreStr.c_str());
        _nbCore += 1;
        fileStream.close();
    } else {
        try {
           throw FileOpenException();
        } catch (const FileOpenException& message) {
           std::cerr << "Caught exception: " << message.what() << std::endl;
           return message.what();
        }
    }
    return "";
}

std::string CpuModule::openNbCore()
{
    parseNbrCore();
    std::ifstream fileStream("/proc/stat");
    std::string buffer;
    std::string formated;
    std::string cpu;
    int x = 0;

    if (fileStream.is_open()) {
        while (std::getline(fileStream, buffer)) {
            cpu = "cpu";
            cpu += std::to_string(x);
            if (buffer.find(cpu) != std::string::npos) {
                buffer = buffer.substr(buffer.find(' ') + 1, buffer.length() - buffer.find(' '));
                _dq.push_back(buffer);
                x += 1;
                if (x > _nbCore - 1)
                    return "No Error";
            }
        }
        try {
            throw FileOpenException();
        } catch (const FileOpenException& message) {
            std::cerr << "Caught exception: " << message.what() << std::endl;
            return message.what();
        }
    } else {
        try {
            throw FileOpenException();
        } catch (const FileOpenException& message) {
            std::cerr << "Caught exception: " << message.what() << std::endl;
            return message.what();
        }
    }
}

std::deque<long long> CpuModule::PopCompute()
{
    openNbCore();
    std::deque<long long> dqlong;
    while (!_dq.empty()) {
        std::string buffer = _dq.at(0);
        _dq.pop_front();
        float res = TotalCPUpercent(buffer);
        dqlong.push_back(res);
    }
    return dqlong;
}
