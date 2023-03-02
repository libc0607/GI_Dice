################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_adc.c \
C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_clk.c \
C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_flash.c \
C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_gpio.c \
C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_pwr.c \
C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_spi0.c \
C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_sys.c \
C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_timer0.c \
C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_uart0.c 

OBJS += \
./StdPeriphDriver/CH57x_adc.o \
./StdPeriphDriver/CH57x_clk.o \
./StdPeriphDriver/CH57x_flash.o \
./StdPeriphDriver/CH57x_gpio.o \
./StdPeriphDriver/CH57x_pwr.o \
./StdPeriphDriver/CH57x_spi0.o \
./StdPeriphDriver/CH57x_sys.o \
./StdPeriphDriver/CH57x_timer0.o \
./StdPeriphDriver/CH57x_uart0.o 

C_DEPS += \
./StdPeriphDriver/CH57x_adc.d \
./StdPeriphDriver/CH57x_clk.d \
./StdPeriphDriver/CH57x_flash.d \
./StdPeriphDriver/CH57x_gpio.d \
./StdPeriphDriver/CH57x_pwr.d \
./StdPeriphDriver/CH57x_spi0.d \
./StdPeriphDriver/CH57x_sys.d \
./StdPeriphDriver/CH57x_timer0.d \
./StdPeriphDriver/CH57x_uart0.d 


# Each subdirectory must supply rules for building sources it contributes
StdPeriphDriver/CH57x_adc.o: C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=0 -DCH573 -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\Profile\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\app_drv_fifo" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
StdPeriphDriver/CH57x_clk.o: C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_clk.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=0 -DCH573 -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\Profile\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\app_drv_fifo" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
StdPeriphDriver/CH57x_flash.o: C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=0 -DCH573 -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\Profile\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\app_drv_fifo" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
StdPeriphDriver/CH57x_gpio.o: C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=0 -DCH573 -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\Profile\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\app_drv_fifo" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
StdPeriphDriver/CH57x_pwr.o: C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_pwr.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=0 -DCH573 -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\Profile\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\app_drv_fifo" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
StdPeriphDriver/CH57x_spi0.o: C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_spi0.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=0 -DCH573 -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\Profile\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\app_drv_fifo" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
StdPeriphDriver/CH57x_sys.o: C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_sys.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=0 -DCH573 -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\Profile\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\app_drv_fifo" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
StdPeriphDriver/CH57x_timer0.o: C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_timer0.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=0 -DCH573 -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\Profile\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\app_drv_fifo" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
StdPeriphDriver/CH57x_uart0.o: C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/StdPeriphDriver/CH57x_uart0.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=0 -DCH573 -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\Profile\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\app_drv_fifo" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

