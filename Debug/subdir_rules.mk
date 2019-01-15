################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Compiler'
	"/Applications/ti/ccsv7/tools/compiler/msp430-gcc-6.2.1.16_osx/bin/msp430-elf-gcc" -c -mmcu=msp430fr5969 -I"/Applications/ti/ccsv7/ccs_base/msp430/include_gcc" -I"/Users/amjad/Documents/projects/T2TDir/T2TNetwork/T2Tnet/frame/inc" -I"/Users/amjad/Documents/projects/T2TDir/T2TNetwork/T2Tnet" -I"/Users/amjad/Documents/projects/T2TDir/T2TNetwork/T2Tnet/phy/inc" -I"/Users/amjad/Documents/projects/T2TDir/T2TNetwork/T2Tnet/sys/inc" -I"/Users/amjad/Documents/projects/T2TDir/T2TNetwork/T2Tnet/mac/inc" -I"/Users/amjad/Documents/projects/T2TDir/T2TNetwork/T2Tnet" -I"/Applications/ti/ccsv7/tools/compiler/msp430-gcc-6.2.1.16_osx/msp430-elf/include" -Os -g -gdwarf-3 -gstrict-dwarf -Wall -mlarge -mhwmult=f5series -mcode-region=none -mdata-region=none -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o"$@" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


