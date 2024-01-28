/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** IModule
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include <string>
#include <iostream>
#include <cstring>
#include "./module/RamModule.hpp"
#include "./module/SysInfoModule.hpp"
#include "./module/CpuModule.hpp"

namespace Krell {
    class IModule {
        public:
            IModule() {};
            ~IModule() {};
            RamModule *_RamModule;
            SysInfoModule *_SysInfoModule;
            CpuModule *_CpuModule;

        protected:
        private:
    };
}

#endif /* !IMODULE_HPP_ */
