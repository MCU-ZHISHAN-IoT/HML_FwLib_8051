#!/usr/bin/make

# ------------------------------------------------------------------------
# Author     : Weilun Fong | wlf@zhishan-iot.tk
# Date       : 2022-02-24
# Description: MCU parameters config Makefile
# E-mail     : mcu@zhishan-iot.tk
# Make-tool  : GNU Make (http://www.gnu.org/software/make/manual/make.html)
# Page       : https://hw.zhishan-iot.tk/page/hml/detail/fwlib_8051.html
# Project    : HML_FwLib_8051
# Version    : v0.4.1
# ------------------------------------------------------------------------

# Print note information
$(info $(SPACE)- Collect MCU config information)

# Configuration parameter translation
# [CLKFRE] frequency of MCU clock
ifneq ($(CLKFRE),)
    ifeq ($(shell $(ECHO) $(CLKFRE) | $(GREP) '^[[:digit:]]*$$'),)
        $(error invalid CLKFRE value)
    else
        CLOCK_FREQUENCY := $(CLKFRE)
    endif
else
    CLOCK_FREQUENCY := 11059200
endif

# [CODE] internal ROM
ifneq ($(CODE),)
    export CODE_SIZE := $(shell $(ECHO) $(CODE) | $(AWK) '{printf("%d",$$1*1024)}')
else
    export CODE_SIZE := 8192
endif
# [IRAM] internal RAM
ifneq ($(IRAM),)
    export IRAM_SIZE := $(IRAM)
else
    export IRAM_SIZE := 256
endif
# [XRAM] external RAM
ifneq ($(XRAM),)
    export XRAM_SIZE := $(shell $(ECHO) $(XRAM) | $(AWK) '{printf("%d",$$1*1024)}')
else
    export XRAM_SIZE := 0
endif

# Generate and export CFLAGS
#   Details:
#    --fsigned-char     Make "char" signed by default
#    -mmcs51            Generate code for the Intel MCS51 family of processors.
#                       This is the default processor target.
#    --std-sdcc99       Use ISO C99 standard with SDCC extensions
#    --opt-code-size    Optimize for code size rather than speed
#    --code-loc         Code Segment Location
#    --code-size        Code Segment size
#    --iram-size        Internal Ram size
#    --xram-size        External Ram size
export CFLAGS := -c -I$(INCDIR) \
-mmcs51 \
-D__CONF_FRE_CLKIN=$(CLOCK_FREQUENCY)UL \
--std-sdcc99 --fsigned-char \
--opt-code-size \
--code-loc 0x0000 --code-size $(CODE_SIZE) \
--iram-size $(IRAM_SIZE) \
--xram-size $(XRAM_SIZE)

# Generate and export AFLAGS
#     -c      do not warn if the library had to be created
#     -s      act as ranlib
#     -r      replace existing or insert new file(s) into the archive
AFLAGS        := -rcs

# Print final MCU information according to all configurations
$(info memory: code=$(CODE_SIZE)B iram=$(IRAM_SIZE)B xram=$(XRAM_SIZE)B, \
clock: $(shell $(ECHO) $(CLOCK_FREQUENCY) | $(AWK) '{printf("%.6f",$$1/1000000)}') MHz)
