# 1. TOOLCHAIN & OUTPUT
PROJECT_NAME     := ss_twr_init
TARGETS          := nrf52832_xxaa
OUTPUT_DIRECTORY := _build

CC      := arm-none-eabi-gcc
AS      := arm-none-eabi-gcc -x assembler-with-cpp
OBJCOPY := arm-none-eabi-objcopy
SIZE    := arm-none-eabi-size

# 2. SOURCE FILES & INCLUDES
# Try to get the path from the environment first
SDK_ROOT := $(NRF_SDK_PATH)

# Go up 6 levels to reach 05_CODE, then into the SDK
ifeq ($(SDK_ROOT),)
  SDK_ROOT := ../../../../../nRF5_SDK_14.2.0
endif

# Final safety check: if both failed, stop the build
ifeq ($(SDK_ROOT),)
  $(error NRF_SDK_PATH is not set and no fallback was found.)
endif

PROJ_DIR := ..

SRC_FILES += \
  $(PROJ_DIR)/main.c \
  $(PROJ_DIR)/ss_init_main.c \
  $(SDK_ROOT)/components/boards/boards.c \
  ../../../deca_driver/deca_device.c \
  ../../../deca_driver/deca_params_init.c \
  ../../../deca_driver/port/port_platform.c \
  $(SDK_ROOT)/components/toolchain/gcc/gcc_startup_nrf52.S \
  $(SDK_ROOT)/components/toolchain/system_nrf52.c \
  $(SDK_ROOT)/components/libraries/uart/app_uart_fifo.c \
  $(SDK_ROOT)/components/libraries/fifo/app_fifo.c \
  $(SDK_ROOT)/components/libraries/uart/retarget.c \
  $(SDK_ROOT)/components/drivers_nrf/uart/nrf_drv_uart.c \
  $(SDK_ROOT)/components/drivers_nrf/common/nrf_drv_common.c \
  $(SDK_ROOT)/components/drivers_nrf/spi_master/nrf_drv_spi.c \
  $(SDK_ROOT)/components/drivers_nrf/gpiote/nrf_drv_gpiote.c \

INC_FOLDERS += \
  $(PROJ_DIR) \
  $(PROJ_DIR)/config \
  ../../../boards \
  ../../../deca_driver \
  ../../../deca_driver/port \
  $(SDK_ROOT)/components/toolchain/cmsis/include \
  $(SDK_ROOT)/components/toolchain \
  $(SDK_ROOT)/components/device \
  $(SDK_ROOT)/components/boards \
  $(SDK_ROOT)/components/drivers_nrf/hal \
  $(SDK_ROOT)/components/drivers_nrf/delay \
  $(SDK_ROOT)/components/libraries/util \
  $(SDK_ROOT)/modules/nrfx/mdk \
  $(SDK_ROOT)/components/drivers_nrf/nrf_soc_nosd \
  $(SDK_ROOT)/components/libraries/experimental_section_vars \
  $(SDK_ROOT)/components/libraries/strerror \
  $(SDK_ROOT)/components/libraries/uart \
  $(SDK_ROOT)/components/libraries/fifo \
  $(SDK_ROOT)/components/drivers_nrf/uart \
  $(SDK_ROOT)/components/drivers_nrf/common \
  $(SDK_ROOT)/components/libraries/experimental_log \
  $(SDK_ROOT)/components/libraries/experimental_log/src \
  $(SDK_ROOT)/components/drivers_nrf/spi_master \
  $(SDK_ROOT)/components/libraries/timer \
  $(SDK_ROOT)/components/drivers_nrf/clock \

# 3. FLAGS
CFLAGS += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -O3 -g3 -Wall 
CFLAGS += -DNRF52832_XXAA -DBOARD_CUSTOM -DCONFIG_GPIO_AS_PINRESET
CFLAGS += -DCONFIG_GPIO_AS_PINRESET   # Reset button
# Force the compiler to include our custom overrides first
CFLAGS += -include app_config.h

LDFLAGS += -L$(SDK_ROOT)/components/toolchain/gcc
LDFLAGS += -T$(SDK_ROOT)/components/toolchain/gcc/nrf52_xxaa.ld
LDFLAGS += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16

# 4. BUILD RULES
INC_PATHS = $(addprefix -I, $(INC_FOLDERS))

.PHONY: default clean flash erase reset

default: $(OUTPUT_DIRECTORY)/$(PROJECT_NAME).hex

$(OUTPUT_DIRECTORY)/$(PROJECT_NAME).out: $(SRC_FILES)
	@mkdir -p $(@D)
	@echo "Building target: $@"
	$(CC) $(CFLAGS) $(INC_PATHS) $(LDFLAGS) $^ -o $@

$(OUTPUT_DIRECTORY)/$(PROJECT_NAME).hex: $(OUTPUT_DIRECTORY)/$(PROJECT_NAME).out
	@echo "Generating hex file..."
	$(OBJCOPY) -O ihex $< $@
	$(SIZE) $<

clean:
	rm -rf $(OUTPUT_DIRECTORY)

# 5. AUTOMATION TARGETS
SERIAL_NUM ?= 760206151

flash: $(OUTPUT_DIRECTORY)/$(PROJECT_NAME).hex
	@echo "Flashing: $<"
	nrfutil device program --firmware $< --serial-number $(SERIAL_NUM) --options reset=RESET_PIN
	@echo "Triggering hardware reset..."
	nrfutil device reset --serial-number $(SERIAL_NUM)

erase:
	@echo "Erasing device..."
	nrfutil device erase --all --serial-number $(SERIAL_NUM)

reset:
	@echo "Resetting device..."
	nrfutil device reset --serial-number $(SERIAL_NUM)