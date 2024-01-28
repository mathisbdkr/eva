/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** RamModule
*/

#ifndef RAMMODULE_HPP_
#define RAMMODULE_HPP_

#include <sys/sysinfo.h>

class RamModule {
    public:
        RamModule();
        ~RamModule() {};

        void get_ram_usage();

        float _ram_usage;
        float _total_ram;
        float _free_ram;

    private:
};

#endif /* !RAMMODULE_HPP_ */
