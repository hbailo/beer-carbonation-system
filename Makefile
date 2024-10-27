MAKEFLAGS += -s


compile:  # Compile develop profile
	cmake --build build/NUCLEO_F429ZI/develop/GCC_ARM -j 4

new:  # Create new MBED OS project
	~/.virtualenvs/mbed-os/bin/mbed-tools new -c .	 
	ln -s ~/lib/mbed-os lib/mbed-os	# Path to local MBED OS library

configure:  # Configure MBED OS develop profile
	~/.virtualenvs/mbed-os/bin/mbed-tools configure -m NUCLEO_F429ZI -b develop -t GCC_ARM -o build/NUCLEO_F429ZI/develop/GCC_ARM # Configure MBED OS
	cmake -S . -B build/NUCLEO_F429ZI/develop/GCC_ARM # Generate project's buildsystem

flash:  # Flash binary to MCU
	cp build/NUCLEO_F429ZI/develop/GCC_ARM/Beer-Carbonation-System.bin /media/nano/NOD_F429ZI # 
