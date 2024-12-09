MAKEFLAGS += -s
profile = release

compile:  # Compile develop profile
	cmake --build build/$(profile) -j 4

configure:  # Configure MBED OS develop profile
	~/.virtualenvs/mbed-os/bin/mbed-tools configure --mbed-os-path lib/mbed-os -m NUCLEO_F429ZI -b $(profile) -t GCC_ARM -o build/$(profile) # Configure MBED OS
	cmake -S . -B build/$(profile) -DPython3_ROOT_DIR=~/.virtualenvs/mbed-os/bin # Generate project's buildsystem

flash:  # Flash binary to MCU
	cp build/$(profile)/beer-carbonation-system.bin /media/nano/NOD_F429ZI
