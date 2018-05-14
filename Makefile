.PHONY: run_gpio_test
run_gpio_test: clean gpio_test
	./test_build/gpio_test

gpio_test: mock_gpio.o
	cd test_build && g++ -o gpio_test -m32 -mlittle-endian -I/usr/local/boost_1_67_0/prefix/include -I../inc/gpio -I../test/inc -I/Users/dewaynetaylor/Documents/work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include -I/Users/dewaynetaylor/Documents/work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Device/ST/STM32F7xx/Source -DSTM32F746xx -std=c++1y mock_gpio.o ../test/unit_test/gpio_test.cpp

mock_gpio.o: ./inc/gpio/gpio_interface.hpp ./test/inc/mock_gpio.hpp ./test/src/mock_gpio.cpp
	cd test_build && g++ -c -o mock_gpio.o -mlittle-endian -std=c++1y -m32 -I../test/inc -I../inc/gpio -I/Users/dewaynetaylor/Documents/work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include -I/Users/dewaynetaylor/Documents/work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Device/ST/STM32F7xx/Source -I/Users/dewaynetaylor/Documents/work/ST_workspace/STM32Cube_FW_F7_V1.7.0/Drivers/CMSIS/Include -DSTM32F746xx ../test/src/mock_gpio.cpp && cd ../

gpio.o: ./inc/gpio/gpio_interface.hpp ./inc/gpio/gpio.hpp ./src/gpio.cpp
	cd build && g++ -c -o gpio.o -m32 -mlittle-endian -std=c++1y -I../inc/gpio ../src/gpio.cpp && cd ../

.PHONY : clean
clean :
	rm -f ./build/* ./test_build/*
