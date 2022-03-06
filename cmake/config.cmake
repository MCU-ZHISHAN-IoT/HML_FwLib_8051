# ------------------------------------------------------------------------
# Author     : Weilun Fong | wlf@zhishan-iot.tk
# Date       : 2022-03-03
# Description: config Makefile
# E-mail     : mcu@zhishan-iot.tk
# Make-tool  : CMake
# Page       : https://hw.zhishan-iot.tk/page/hml/detail/fwlib_8051.html
# Project    : HML_FwLib_8051
# Version    : v0.0.2
# ------------------------------------------------------------------------

# Print note information
message(STATUS "Collect MCU config information")

# [VERBOSE] Building print control, the value will be passed to CMake builtin
#   variable CMAKE_VERBOSE_MAKEFILE. CMake will print more when the value is
#   set as 'TRUE'
set(VERBOSE FALSE CACHE BOOL "Verbose mode")

# Options for MCU configurations
#  [CLKFRE] Specify frequency of MCU clock, the unit is Hz.
set(CLKFRE 11059200 CACHE STRING "Frequency of MCU clock")
#  [CODE] Specify total size of ROM(external+ on-chip) during compilation
#    manually (unit: KB, default: 8KB)
#  [IRAM] Specify total size of internal RAM during compilation manually
#    (unit: B, default: 256)
#  [XRAM] Specify total size of external RAM during compilation manually
#    (unit: KB, default: 0)
set(CODE 8 CACHE STRING "Size of CODE area (unit: KB)")
set(IRAM 256 CACHE STRING "Size of IRAM area (unit: B)")
set(XRAM 0 CACHE STRING "Size of XRAM area (unit: KB)")

# Options for build target
#  [EXECUTABLE_C] Specify user source file or Makefile will fill it with "test.c".
#    It's noticed that once use this option to compile specified .c file,
#    user should add this option when do all targets related to build operation,
#    such as clean and rebuild.
set(EXECUTABLE_C usr/test.c CACHE PATH "Path of executable source fils")
