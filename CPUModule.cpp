#include "CPUModule.hpp"
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sstream>

CPUModule::CPUModule() {
    char model[1024];
    std::stringstream clock;
    size_t size = sizeof(model);
    if (sysctlbyname("machdep.cpu.brand_string", &model, &size, NULL, 0) < 0)
    {
        throw std::runtime_error("Fail to get CPU model");
    }

    size = sizeof(_hw);

    if (sysctlbyname("hw.cpufrequency", &_hw, &size, NULL, 0) < 0)
    {
        throw std::runtime_error("Fail to get clock speed");
    }

    size = sizeof(_core);
    if (sysctlbyname("machdep.cpu.core_count", &_core, &size, NULL, 0) < 0)
    {
        throw std::runtime_error("Fail to get count cores");
    }

    clock << model;
    _modelReal = clock.str();
}

CPUModule::~CPUModule() {
	
}

CPUModule::CPUModule(const CPUModule &copy)
{
	getInfo();
    *this = copy;
}
CPUModule& CPUModule::operator=(const CPUModule&rhs)
{
	getInfo();
    _hw = rhs._hw;
    _core = rhs._core;
    return (*this);
}

MType CPUModule::getInfo() {
	std::cout << std::endl;
    std::cout << "*************** CPU MODULES ****************" << std::endl;

    if (FILE * stream = popen("top -l 1 -n 0 -s 0 | grep CPU | awk '{print$7}'", "r"))
    {
        fscanf(stream, "%f", &_idleCPU);
	}
	else {
		throw std::runtime_error("Fail to get CPU activity");
	}

	std::stringstream ss;

    ss << "CPU model: " << _modelReal << std::endl
		<< "Clock speed: " << _hw << std::endl
        << "Count cores: " << _core << std::endl;
	return ss.str();
   
}
std::string CPUModule::getModel() const {
    return _modelReal;
}
uint64_t CPUModule::hatHW() const {
	return _hw;
}
int CPUModule::getCore() {
	if (FILE * stream = popen("top -l 1 -n 0 -s 0 | grep CPU | awk '{print$7}'", "r"))
	{
		fscanf(stream, "%f", &_idleCPU);
	}
	else {
		throw std::runtime_error("Fail to get CPU activity");
	}
    return (static_cast<int>(_idleCPU));
}
std::string CPUModule::getActivity() const {
	std::string ret = _activity;
	return ret;
}
float CPUModule::getIdleCpu() const {
	return _idleCPU;
}
// sysctl -a
// sysctl hw.cpufrequency
