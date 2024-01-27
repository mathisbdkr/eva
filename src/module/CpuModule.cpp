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

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

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
    }
    try {
        throw FileOpenException();
    } catch (const FileOpenException& message) {
        std::cerr << "Caught exception: " << message.what() << std::endl;
        return message.what();
    }
}

int CpuModule::parseNbrCore()
{
    std::ifstream fileStream("/proc/cpuinfo");
    std::string buffer;
    std::string coreStr;
    int core;

    if (fileStream.is_open()) {
        while (std::getline(fileStream, buffer)) {
            if (buffer.find("processor") != std::string::npos) {
                coreStr = buffer.substr(buffer.find(':') + 1, buffer.length() - (buffer.find(':') + 1));
            }
        }
        core = atoi(coreStr.c_str());
        core += 1;
        fileStream.close();
        return core;
    }
    return std::stoi("File could not be opened.");
}

std::deque<std::string> CpuModule::openNbCore(int core)
{
    std::ifstream fileStream("/proc/stat");
    std::string buffer;
    std::string formated;
    std::string cpu;
    int x = 0;
    std::deque<std::string> dq;

    if (fileStream.is_open()) {
        while (std::getline(fileStream, buffer)) {
            cpu = "cpu";
            cpu += std::to_string(x);
            if (buffer.find(cpu) != std::string::npos) {
                buffer = buffer.substr(buffer.find(' ') + 1, buffer.length() - buffer.find(' '));
                dq.push_back(buffer);
                x += 1;
                if (x > core - 1)
                    return dq;
            }
        }
        fileStream.close();
        return dq;
    }
    return dq;
}

void CpuModule::PopCompute(std::deque<std::string> dq)
{
    std::deque<long long> dqlong;
    while (!dq.empty()) {
        std::string buffer = dq.at(0);
        dq.pop_front();
        float res = TotalCPUpercent(buffer);
        std::cout << res << std::endl;
        dqlong.push_back(res);
    }
}
