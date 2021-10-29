# ------------------------------------------------------------------------
# Author     : Weilun Fong | wlf@zhishan-iot.tk
# Date       : 2021-09-27
# Description: config Makefile
# E-mail     : mcu@zhishan-iot.tk
# Make-tool  : CMake
# Page       : https://hw.zhishan-iot.tk/page/hml/detail/fwlib_8051.html
# Project    : HML_FwLib_8051
# Version    : v0.0.1
# ------------------------------------------------------------------------

# Print note information
message(STATUS "Collect MCU config information")

# Options for print format
#  [CMAKE_VERBOSE_MAKEFILE] This is a builtin variable which provides by CMake.
# CMake will print more details, when its value is "TRUE".
set(CMAKE_VERBOSE_MAKEFILE FALSE)

# Options for MCU configurations
#  [CLKFRE] Specify frequency of MCU clock, the unit is Hz.
set(CLKFRE 11059200)
#  [CODE] Specify total size of ROM(external+ on-chip) during compilation
#    manually (unit: KB, default: 8KB)
#  [IRAM] Specify total size of internal RAM during compilation manually
#    (unit: B, default: 256)
#  [XRAM] Specify total size of external RAM during compilation manually
#    (unit: KB, default: 0)
set(CODE 8)
set(IRAM 256)
set(XRAM 0)

# Options for build target
#  [EXECUTABLE_C] Specify user source file or Makefile will fill it with "test.c".
#    It's noticed that once use this option to compile specified .c file,
#    user should add this option when do all targets related to build operation,
#    such as clean and rebuild.
set(EXECUTABLE_C usr/test.c)
