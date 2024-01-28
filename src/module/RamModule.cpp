/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** RamModule
*/

#include "RamModule.hpp"
#include <cstdlib>
RamModule::RamModule() {
    _ram_usage = 0;
}

void RamModule::get_ram_usage() {
    struct sysinfo i;
    sysinfo(&i);
    float total_minus_free = i.totalram - i.freeram;
    float total = i.totalram;
    _ram_usage = (total_minus_free / total) * 100;
    _total_ram = total;
    _free_ram = i.freeram;
}
