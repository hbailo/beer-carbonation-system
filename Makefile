MAKEFLAGS += -s


compile:
	cmake --build build/NUCLEO_F429ZI/develop/GCC_ARM -j 4

new:
	~/.virtualenvs/mbed-os/bin/mbed-tools new .	 # Create new MBED OS project

configure: # MBED OS develop profile
	~/.virtualenvs/mbed-os/bin/mbed-tools configure -m NUCLEO_F429ZI -b develop -t GCC_ARM -o build/NUCLEO_F429ZI/develop/GCC_ARM # Configure MBED OS
	cmake -S . -B build/NUCLEO_F429ZI/develop/GCC_ARM # Generate project's buildsystem

flash:
	cp cmake_build/NUCLEO_F429ZI/develop/GCC_ARM/Example-1.bin /media/nano/NOD_F429ZI
