# ================================
#  Compiler Setup
# ================================

ifeq ($(OS),Windows_NT)
    ECHO_FLAGS := -e
else
    ECHO_FLAGS :=
endif

ifdef DEVKITARM
    export PATH := $(DEVKITARM)/bin:$(PATH)
endif

PREFIX := arm-none-eabi-

export CC      := $(PREFIX)gcc
export CXX     := $(PREFIX)g++
export AS      := $(PREFIX)as
export AR      := $(PREFIX)ar
export OBJCOPY := $(PREFIX)objcopy
export OBJDUMP := $(PREFIX)objdump
export LD      := $(PREFIX)ld

# Uncomment below for fast compilation
# command line echo output breaks though
# export MAKEFLAGS="-j 4"

# ================================================================================
#  TARGET is the name of the output
#  BUILD is the directory where object files & intermediate files will be placed
#  SOURCE_DIR is the source code directory
#  INCLUDE_DIR is the include directory
# ================================================================================

TARGET      := newcode
BUILD       := build
SOURCES     := source source/nsmb source/actors
INCLUDE_DIR := include

# ================================
#  Code Generation Flags
# ================================

ARCH := -march=armv5te -mtune=arm946e-s

CFLAGS := -g $(ARCH) $(INCLUDE) \
		-Wall -O2 \
		-fomit-frame-pointer -ffast-math \
		-DSDK_GCC -DSDK_CW -DSDK_ARM9 \
		-nodefaultlibs -I. -fno-builtin -c

CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions

ASFLAGS := -g $(ARCH)
LDFLAGS := -g -T $(CURDIR)/../symbols.x -T $(CURDIR)/../linker.x -Map newcode.map

ifdef CODEADDR
    LDFLAGS += -Ttext $(CODEADDR)
endif

#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT  := $(CURDIR)/$(TARGET)
export DEPSDIR := $(CURDIR)/$(BUILD)
export VPATH   := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))

C_FILES   := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CXX_FILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
ASM_FILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))

export OBJECTS := $(CXX_FILES:.cpp=.o) $(C_FILES:.c=.o) $(ASM_FILES:.s=.o)
export INCLUDE := $(foreach dir,$(INCLUDE_DIR),-iquote $(CURDIR)/$(dir)) -I$(CURDIR)/$(BUILD)

.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@echo $(ECHO_FLAGS) "\033[37;1m[\033[0m\033[34;1mInfo\033[0m\033[37;1m]\033[0m Building..."
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
	@echo $(ECHO_FLAGS) "\033[37;1m[\033[0m\033[34;1mInfo\033[0m\033[37;1m]\033[0m Build finished!"

#---------------------------------------------------------------------------------
clean:
	@echo $(ECHO_FLAGS) "\033[0;33m[\033[33;1mInfo\033[0;33m] \033[0;37mCleaning...\033[0m"
	@echo $(ECHO_FLAGS) "\033[0;33m[\033[0;31mDeleting\033[0;33m] \033[0;37m$(BUILD)\033[0m"
	@rm -fr $(BUILD)
	@echo $(ECHO_FLAGS) "\033[0;33m[\033[0;31mDeleting\033[0;33m] \033[0;37m$(TARGET).elf\033[0m"
	@rm -fr $(TARGET).elf
	@echo $(ECHO_FLAGS) "\033[0;33m[\033[0;31mDeleting\033[0;33m] \033[0;37m$(TARGET).bin\033[0m"
	@rm -fr $(TARGET).bin
	@echo $(ECHO_FLAGS) "\033[0;33m[\033[0;31mDeleting\033[0;33m] \033[0;37m$(TARGET).sym\033[0m"
	@rm -fr $(TARGET).sym

#---------------------------------------------------------------------------------
else

# ================================
#  Targets
# ================================

all: $(OUTPUT).bin $(OUTPUT).sym $(OBJECTS)

$(OUTPUT).bin : $(OUTPUT).elf
	@echo $(ECHO_FLAGS) "\033[37;1m[\033[0m\033[32;1mBuild\033[0m\033[37;1m]\033[0m Making binary \033[33;1m\"$(notdir $<)\"\033[0m -> \033[33;1m\"$(notdir $@)\"\033[0m"
	@$(OBJCOPY) -O binary $< $@

$(OUTPUT).sym : $(OUTPUT).elf
	@echo $(ECHO_FLAGS) "\033[37;1m[\033[0m\033[32;1mBuild\033[0m\033[37;1m]\033[0m Dumping symbols \033[33;1m\"$(notdir $<)\"\033[0m -> \033[33;1m\"$(notdir $@)\"\033[0m"
	@$(OBJDUMP) -t $< > $@

#---------------------------------------------------------------------------------
%.elf: $(OBJECTS)
	@echo $(ECHO_FLAGS) "\033[37;1m[\033[0m\033[32;1mBuild\033[0m\033[37;1m]\033[0m Linking -> \033[33;1m\"$(notdir $@)\"\033[0m"
	@$(LD)  $(LDFLAGS) $(OBJECTS) -o $@

#---------------------------------------------------------------------------------
%.o: %.cpp
	@echo $(ECHO_FLAGS) "\033[37;1m[\033[0m\033[32;1mBuild\033[0m\033[37;1m]\033[0m Building C++ file \033[33;1m\"$(notdir $<)\"\033[0m"
	@$(CXX) -MMD -MP -MF $(DEPSDIR)/$*.d $(CXXFLAGS) -c $< -o $@ $(ERROR_FILTER)

#---------------------------------------------------------------------------------
%.o: %.c
	@echo $(ECHO_FLAGS) "\033[37;1m[\033[0m\033[32;1mBuild\033[0m\033[37;1m]\033[0m Building C file \033[33;1m\"$(notdir $<)\"\033[0m"
	@$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d $(CFLAGS) -c $< -o $@ $(ERROR_FILTER)

#---------------------------------------------------------------------------------
%.o: %.s
	@echo $(ECHO_FLAGS) "\033[37;1m[\033[0m\033[32;1mBuild\033[0m\033[37;1m]\033[0m Building ASM file \033[33;1m\"$(notdir $<)\"\033[0m"
	@$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d -x assembler-with-cpp $(ASFLAGS) -c $< -o $@ $(ERROR_FILTER)

-include $(DEPSDIR)/*.d

endif
