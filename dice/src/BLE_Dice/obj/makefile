################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include StdPeriphDriver/subdir.mk
-include Startup/subdir.mk
-include RVMSIS/subdir.mk
-include Profile/subdir.mk
-include HAL/subdir.mk
-include APP/ble_uart_service/subdir.mk
-include APP/app_drv_fifo/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
BLE_Dice.hex \

SECONDARY_LIST += \
BLE_Dice.lst \

SECONDARY_SIZE += \
BLE_Dice.siz \


# 所有目标
all: BLE_Dice.elf secondary-outputs

# 工具调用
BLE_Dice.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -T "C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -L"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\BLE\LIB" -L"C:\Users\libc0\Desktop\dice\CH573EVT\EVT\EXAM\SRC\StdPeriphDriver" -Xlinker --print-memory-usage -Wl,-Map,"BLE_Dice.map" --specs=nano.specs --specs=nosys.specs -o "BLE_Dice.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
BLE_Dice.hex: BLE_Dice.elf
	@	riscv-none-embed-objcopy -O ihex "BLE_Dice.elf"  "BLE_Dice.hex"
	@	@
BLE_Dice.lst: BLE_Dice.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "BLE_Dice.elf" > "BLE_Dice.lst"
	@	@
BLE_Dice.siz: BLE_Dice.elf
	@	riscv-none-embed-size --format=berkeley "BLE_Dice.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) BLE_Dice.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
