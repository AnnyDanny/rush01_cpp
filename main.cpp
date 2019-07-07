#include <iostream>
#include "HostnameModule.hpp"
#include "OSInfoModule.hpp"
#include "DateTimeModule.hpp"
#include "CPUModule.hpp"
#include "RAMModule.hpp"
#include "NetworkModule.hpp"
#include "NcursesOut.hpp"
#include "IMonitorDisplay.hpp"
#include "Common.hpp"
#include "QTOut.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <ncurses.h>

int main() {
	HostnameModule hostnameModule;
	OSInfoModule osInfoModule;
	DateTimeModule dateTimeModule;
	CPUModule cpuModule;
	RAMModule ramModule;
	NetworkModule networkModule;
//
//	std::cout << hostnameModule.getInfo() << std::endl;
//	std::cout << osInfoModule.getInfo() << std::endl;
//	std::cout << dateTimeModule.getInfo() << std::endl;
//	std::cout << cpuModule.getInfo() << std::endl;
//	std::cout << ramModule.getInfo() << std::endl;
//	std::cout << networkModule.getInfo() << std::endl;

	IMonitorDisplay *visualMode = new NcursesOut();
	bool isNcurses = true;

	while (true) {
		visualMode->printOut();
		Command command = visualMode->getInput();
		if (command == SPACE) {
			// delete(visualMode);
			if (isNcurses) {
				// visualMode = new QTOut();
				std::cout << "Call graphical" << std::endl;
				isNcurses = false;
			}
			else {
				visualMode = new NcursesOut();
				isNcurses = true;
			}
		}
		else if (command == EXIT) {
			delete(visualMode);
			break;
		} 
	}

	return 0;
}