cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(veludda_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(veludda_pico
	bmpdata.c
	graphlib.c
	ili9341_spi.c
	musicdata.c
	rotatevideo_lcd.c
	veludda_chars.c
	veludda_lcd.c
	ff.C
	pico-sdmm.c
)

# Pull in basic dependencies
target_link_libraries(veludda_pico pico_stdlib hardware_spi hardware_pwm)

# create map/bin/hex file etc.
pico_add_extra_outputs(veludda_pico)
