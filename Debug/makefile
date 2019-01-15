################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccsv7/tools/compiler/msp430-gcc-6.2.1.16_osx

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./app.o" \
"./frame/frame.o" \
"./frame/frameValidation.o" \
"./mac/mac.o" \
"./phy/radio.o" \
"./phy/rx.o" \
"./phy/timers.o" \
"./phy/tx.o" \
"./sys/buffers.o" \
"./sys/debug.o" \
"./sys/node.o" \
"./sys/peripherals.o" \
-T"../msp430fr5969.ld" \
$(GEN_CMDS__FLAG) \
-Wl,--start-group \
-lgcc \
-lc \
-Wl,--end-group \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include frame/subdir_vars.mk
-include mac/subdir_vars.mk
-include phy/subdir_vars.mk
-include sys/subdir_vars.mk
-include subdir_rules.mk
-include frame/subdir_rules.mk
-include mac/subdir_rules.mk
-include phy/subdir_rules.mk
-include sys/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
T2Tnetwork.out \

EXE_OUTPUTS__QUOTED += \
"T2Tnetwork.out" \

BIN_OUTPUTS += \
T2Tnetwork.hex \

BIN_OUTPUTS__QUOTED += \
"T2Tnetwork.hex" \


# All Target
all: $(OBJS) $(LD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "T2Tnetwork.out"

# Tool invocations
T2Tnetwork.out: $(OBJS) $(LD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Linker'
	"/Applications/ti/ccsv7/tools/compiler/msp430-gcc-6.2.1.16_osx/bin/msp430-elf-gcc" -Os -g -gdwarf-3 -gstrict-dwarf -Wall -mhwmult=f5series -mcode-region=none -mdata-region=none -mlarge -Wl,-Map,"T2Tnetwork.map" -L"/Applications/ti/ccsv7/ccs_base/msp430/include_gcc" -o"T2Tnetwork.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

T2Tnetwork.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: GNU Objcopy Utility'
	"/Applications/ti/ccsv7/tools/compiler/msp430-gcc-6.2.1.16_osx/bin/msp430-elf-objcopy"  $(EXE_OUTPUTS__QUOTED) "T2Tnetwork.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "app.o" "frame/frame.o" "frame/frameValidation.o" "mac/mac.o" "phy/radio.o" "phy/rx.o" "phy/timers.o" "phy/tx.o" "sys/buffers.o" "sys/debug.o" "sys/node.o" "sys/peripherals.o" 
	-$(RM) "app.d" "frame/frame.d" "frame/frameValidation.d" "mac/mac.d" "phy/radio.d" "phy/rx.d" "phy/timers.d" "phy/tx.d" "sys/buffers.d" "sys/debug.d" "sys/node.d" "sys/peripherals.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

