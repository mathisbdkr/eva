/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** DisplaySfml
*/

#include "DisplaySfml.hpp"

DisplaySfml::DisplaySfml() : window(sf::VideoMode(1920, 1080), "SFML Window")
{
    _pos_ram = get_position(300,100);
    _pos_cpu = get_position(300,500);
    _pos_sys = get_position(1000,100);
    _module._RamModule = new RamModule;
    _module._SysInfoModule = new SysInfoModule;
    _module._CpuModule = new CpuModule;
    launch_sfml();
}


DisplaySfml::~DisplaySfml()
{
    delete(_module._CpuModule);
    delete(_module._RamModule);
    delete(_module._SysInfoModule);
}

sf::Vector2f DisplaySfml::get_position(float x, float y)
{
    sf::Vector2f vector;

    vector.x = x;
    vector.y = y;
    return (vector);
}

void DisplaySfml::set_sprite()
{
    backgroundTexture.loadFromFile("assets/image/background.png");
    background.setTexture(backgroundTexture, false);

    CPU_texture.loadFromFile("assets/image/cpu.png");
    CPU_sprite.setTexture(CPU_texture, false);
    CPU_sprite.setScale(get_position(0.2, 0.2));
    CPU_sprite.setPosition(get_position(20, 120));

    RAM_texture.loadFromFile("assets/image/ram.png");
    RAM_sprite.setTexture(RAM_texture, false);
    RAM_sprite.setScale(get_position(0.2, 0.2));
    RAM_sprite.setPosition(get_position(20, 20));

    SYS_texture.loadFromFile("assets/image/sys.png");
    SYS_sprite.setTexture(SYS_texture, false);
    SYS_sprite.setScale(get_position(0.25, 0.25));
    SYS_sprite.setPosition(get_position(15, 240));
}

void DisplaySfml::display_sys_info()
{
    std::string titre = "System Information";
    std::string user = "User     : ";
    std::string Hostname = "Hostname : ";
    std::string time = "Time    : ";
    std::string cpu_str = "Cpu ";
    std::string os = "OS : ";
    std::string kernel = "Kernel : ";
    kernel.append(_module._SysInfoModule->GetKernem());
    os.append( _module._SysInfoModule->OsInfo());
    cpu_str.append( _module._SysInfoModule->getCpu());
    time.append(_module._SysInfoModule->TimeDate());
    Hostname.append(_module._SysInfoModule->getHostname());
    user.append(_module._SysInfoModule->GetUser());
    long int all_second = _module._SysInfoModule->GetUpTime();
    int hours = all_second / 3600;
    int minuts = all_second / 60;
    int second = all_second;
    for (int i = 0; i < hours; i++) {
        minuts -= 60;
        second -= 3600;
    }
    for (int i = 0; i < minuts; i++) {
        second -= 60;
    }
    std::string hours_str = std::to_string(hours);
    std::string minuts_str = std::to_string(minuts);
    std::string second_str = std::to_string(second);
    std::string uptime = "Uptime : ";
    uptime.append(hours_str);
    uptime.append(":");
    uptime.append(minuts_str);
    uptime.append(":");
    uptime.append(second_str);
    window.draw(made_txt(titre.c_str(), get_position(_pos_sys.x + 10, _pos_sys.y - 20), get_position(30, 5), font));
    window.draw(made_txt(time.c_str(), get_position(_pos_sys.x + 10, _pos_sys.y + 30), get_position(30, 5), font));
    window.draw(made_txt(user.c_str(), get_position(_pos_sys.x + 10, _pos_sys.y + 70), get_position(30, 5), font));
    window.draw(made_txt(Hostname.c_str(), get_position(_pos_sys.x + 10, _pos_sys.y + 110), get_position(30, 5), font));
    window.draw(made_txt(cpu_str.c_str(), get_position(_pos_sys.x + 10, _pos_sys.y + 150), get_position(30, 5), font));
    window.draw(made_txt(os.c_str(), get_position(_pos_sys.x + 10, _pos_sys.y + 190), get_position(30, 5), font));
    window.draw(made_txt(kernel.c_str(), get_position(_pos_sys.x + 10, _pos_sys.y + 230), get_position(30, 5), font));
    window.draw(made_txt(uptime.c_str(), get_position(_pos_sys.x + 10, _pos_sys.y + 270), get_position(30, 5), font));
}

void DisplaySfml::display_ram_info()
{
    _module._RamModule->get_ram_usage();
    std::string titre = "Current ram";
    std::string ram_percent = "Ram used : ";
    std::string tmp = std::to_string(_module._RamModule->_ram_usage);
    ram_percent.append(tmp);
    ram_percent.append("%");

    std::string ram_usage = "Ram usage : ";
    std::string ram_used = std::to_string(_module._RamModule->_total_ram - _module._RamModule->_free_ram);
    std::string ram_used_total = ram_used.substr(0, ram_used.find('.'));
    ram_used_total.append(" / ");
    std::string total_ram = std::to_string(_module._RamModule->_total_ram);
    ram_used_total.append(total_ram.substr(0, total_ram.find('.')));
    ram_used_total.append(" KB");

    std::string tt = std::to_string(_module._RamModule->_free_ram);
    std::string ram_free = tt.substr(0, tt.find('.'));

    ram_free.append(" KB  free.");
    window.draw(made_txt(titre.c_str(), get_position(_pos_ram.x + 10, _pos_ram.y - 20), get_position(30, 5), font));
    window.draw(made_txt(ram_percent.c_str(), get_position(_pos_ram.x + 10, _pos_ram.y + 30), get_position(30, 5), font));
    window.draw(made_txt(ram_usage.c_str(), get_position(_pos_ram.x + 10, _pos_ram.y + 70), get_position(30, 5), font));
    window.draw(made_txt(ram_used_total.c_str(), get_position(_pos_ram.x + 10, _pos_ram.y + 110), get_position(30, 5), font));
    window.draw(made_txt(ram_free.c_str(), get_position(_pos_ram.x + 10, _pos_ram.y + 150), get_position(30, 5), font));
}

void DisplaySfml::display_cpu_info()
{
    std::string titre = "Current CPU";
    std::string cpu_name = "CPU ";
    cpu_name.append( _module._SysInfoModule->getCpu());
    std::string cpu_percent = "CPU usage : ";
    std::string tmp;
    float limite = 0.001;
    float cpu_percent_float = _module._CpuModule->TotalCPUpercent(_module._CpuModule->getTotalCpu());
    if (cpu_percent_float > limite) {
        cpu_usage_value = cpu_percent_float;
        tmp = std::to_string(cpu_usage_value);
    } else {
        tmp = std::to_string(cpu_usage_value);
    }
    cpu_percent.append(tmp.substr(0, tmp.find('.') - 3));
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    window.draw(made_txt(titre.c_str(), get_position(_pos_cpu.x + 10, _pos_cpu.y - 20), get_position(30, 5), font));
    window.draw(made_txt(cpu_name.c_str(), get_position(_pos_cpu.x + 10, _pos_cpu.y + 30), get_position(30, 5), font));
    window.draw(made_txt(cpu_percent.c_str(), get_position(_pos_cpu.x + 10, _pos_cpu.y + 70), get_position(30, 5), font));
}

void DisplaySfml::display_info()
{
    if (_sys == true) {
        display_sys_info();
    }
    if (_ram == true) {
        display_ram_info();
    }
    if (_cpu == true) {
        display_cpu_info();
    }
}

void DisplaySfml::launch_sfml(void)
{
    sf::Event event;
    font.loadFromFile("./assets/fonts/RobotoRegular.ttf");
    while (window.isOpen()) {
        set_sprite();
        window.clear(sf::Color::Black);
        window.draw(background);

        window.draw(CPU_sprite);
        window.draw(RAM_sprite);
        window.draw(SYS_sprite);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }  else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (CPU_sprite.getGlobalBounds().contains(mousePosition)) {
                       _cpu = !_cpu;
                    }

                    if (RAM_sprite.getGlobalBounds().contains(mousePosition)) {
                        _ram = !_ram;
                    }

                    if (SYS_sprite.getGlobalBounds().contains(mousePosition)) {
                        _sys = !_sys;
                    }
                }
            }
        }
        if (_cpu == true) {
            made_rond_rect(get_position(600, 300), _pos_cpu, RGB(100,100,100), window);
        }
        if (_sys == true) {
            made_rond_rect(get_position(600, 300), _pos_sys, RGB(100,100,100), window);
        }
        if (_ram == true) {
            made_rond_rect(get_position(600, 300), _pos_ram, RGB(100,100,100), window);
        }
        display_info();
        window.display();
    }
}
