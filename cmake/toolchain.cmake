# ------------------------------------------------------------------------
# Author     : Weilun Fong | wlf@zhishan-iot.tk
# Date       : 2021-09-28
# Description: toolchain config
# E-mail     : mcu@zhishan-iot.tk
# Make-tool  : CMake
# Page       : https://hw.zhishan-iot.tk/page/hml/detail/fwlib_8051.html
# Project    : HML_FwLib_8051
# ------------------------------------------------------------------------

# Target description
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR 8051)

# ------------------------------------------------------------------------
#  @note: If you install SDCC at a non-standard location, you can define a
#   variable whoes name is SYSROOT to specify search path
# ------------------------------------------------------------------------
# SET(CMAKE_FIND_ROOT_PATH $ENV{SYSROOT})

# Toolchain command define
if(NOT DEFINED ENV{CROSS_COMPILE})
    set(ENV{CROSS_COMPILE} sd)
endif()

set(CMAKE_C_COMPILER $ENV{CROSS_COMPILE}cc)
set(PACKIHX packihx)
