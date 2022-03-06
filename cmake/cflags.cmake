# ------------------------------------------------------------------------
# Author     : Weilun Fong | wlf@zhishan-iot.tk
# Date       : 2022-03-06
# Description: compile parametes define
# E-mail     : mcu@zhishan-iot.tk
# Make-tool  : CMake
# Page       : https://hw.zhishan-iot.tk/page/hml/detail/fwlib_8051.html
# Project    : HML_FwLib_8051
# Version    : v0.0.2
# ------------------------------------------------------------------------

# [CLKFRE] frequency of MCU clock
if(CLKFRE MATCHES "^[0-9]+$")
    set(CLOCK_FREQUENCY ${CLKFRE})
else()
    message(FATAL_ERROR "invalid CLKFRE value")
endif()

# [CODE] internal ROM
if(DEFINED CODE)
    set(CODE_SIZE 0)
    math(EXPR CODE_SIZE "${CODE} * 1024")
else()
    message(FATAL_ERROR "unspeficy CODE size")
endif()

# [IRAM] internal RAM
if(DEFINED IRAM)
    set(IRAM_SIZE ${IRAM})
else()
    message(FATAL_ERROR "unspeficy IRAM size")
endif()

# [XRAM] external RAM
if(DEFINED XRAM)
    set(XRAM_SIZE 0)
    math(EXPR XRAM_SIZE "${XRAM} * 1024")
else()
    set(XRAM_SIZE 0)
endif()

# Compile parameters define
add_compile_options(
   --std-sdcc99
   --fsigned-char
   --opt-code-size
   "SHELL: --code-loc 0x0000 --code-size ${CODE_SIZE}"
   "SHELL: --iram-size ${IRAM_SIZE}"
   "SHELL: --xram-size ${XRAM_SIZE}"
)
add_definitions(
    -D__CONF_FRE_CLKIN=${CLOCK_FREQUENCY}UL
)

# Print config information
message("memory (code=${CODE_SIZE}B, iram=${IRAM_SIZE}B, xram=${XRAM_SIZE}B) clock:${CLOCK_FREQUENCY}Hz")
