.PHONY: run_gpio_test
run_unit_test: clean gpio_test
	./test_build/gpio_test

unit_test: mock_gpio.o
	g++ -m32 -mlittle-endian -DSTM32F746xx -std=c++1y -I"/usr/local/boost_1_67_0/prefix/include" -I"./inc" -I"./inc/gpio" -I"./test/inc" -I"/Users/dewaynetaylor/Documents/work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Include" -I"/Users/dewaynetaylor/Documents/work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -o "./test_build/gpio_test" "./test_build/test_gpio.o" "./test_build/mock_gpio.o" "./test/unit_test/gpio_test.cpp"

mock_gpio.o: test_gpio.o ./inc/gpio/gpio_interface.hpp ./test/inc/mock_gpio.hpp ./test/src/mock_gpio.cpp
	g++ -mlittle-endian -std=c++1y -m32 -DSTM32F746xx -I"./test/inc" -I"./inc/gpio" -I"./inc" -I"/Users/dewaynetaylor/Documents/work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/Users/dewaynetaylor/Documents/work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Include" -c -o "./test_build/mock_gpio.o" "./test/src/mock_gpio.cpp"

test_gpio.o: ./inc/gpio/gpio_interface.hpp ./inc/gpio/gpio.hpp ./src/gpio.cpp
	g++ -mlittle-endian -std=c++1y -m32 -DSTM32F746xx -DSTM32F746G_DISCO -DSTM32F746NGHx -DSTM32F7 -DSTM32 -I"./inc" -I"./inc/gpio" -I"/Users/dewaynetaylor/Documents/Work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Include" -I"/Users/dewaynetaylor/Documents/Work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -c -o "test_build/test_gpio.o" "./src/gpio.cpp"

lib.a: gpio.o
	arm-none-eabi-ar -cr --target=elf32-littlearm ./lib/libDrivers.a ./build/gpio.o

gpio.o: ./inc/gpio/gpio_interface.hpp ./inc/gpio/gpio.hpp ./src/gpio.cpp
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32F746xx -DSTM32F746G_DISCO -DSTM32F746NGHx -DSTM32F7 -DSTM32 -I"./inc" -I"./inc/gpio" -I"/Users/dewaynetaylor/Documents/Work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Include" -I"/Users/dewaynetaylor/Documents/Work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -c -o "./build/gpio.o" "./src/gpio.cpp"

.PHONY : clean
clean :
	rm -f ./build/* ./test_build/*
