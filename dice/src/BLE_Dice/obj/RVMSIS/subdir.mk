################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/RVMSIS/core_riscv.c 

OBJS += \
./RVMSIS/core_riscv.o 

C_DEPS += \
./RVMSIS/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
RVMSIS/core_riscv.o: C:/Users/libc0/Desktop/dice/CH573EVT/EVT/EXAM/SRC/RVMSIS/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=0 -DCH573 -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Startup" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\Profile\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\StdPeriphDriver\inc" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\HAL\include" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Ld" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\LIB" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\RVMSIS" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\app_drv_fifo" -I"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\BLE_Dice\APP\ble_uart_service" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

