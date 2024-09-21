MAKEFLAGS += -s

build:
	cmake --build cmake_build/NUCLEO_F429ZI/develop/GCC_ARM -j 4
new:
	~/.virtualenvs/mbed-os/bin/mbed-tools new .  # Create new MBED OS project

configure:
	~/.virtualenvs/mbed-os/bin/mbed-tools configure -m NUCLEO_F429ZI -t GCC_ARM  # Configure MBED OS
	cmake -S . -B cmake_build/NUCLEO_F429ZI/develop/GCC_ARM  # Generate project's buildsystem

flash:
	cp cmake_build/NUCLEO_F429ZI/develop/GCC_ARM/$${PWD##*/}.bin /media/nano/NOD_F429ZI
