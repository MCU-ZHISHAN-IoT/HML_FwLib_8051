#!/usr/bin/make

# ------------------------------------------------------------------------
# Author     : Weilun Fong | wlf@zhishan-iot.tk
# Date       : 2021-09-30
# Description: config Makefile
# E-mail     : mcu@zhishan-iot.tk
# Make-tool  : GNU Make (http://www.gnu.org/software/make/manual/make.html)
# Page       : https://hw.zhishan-iot.tk/page/hml/detail/fwlib_8051.html
# Project    : HML_FwLib_8051
# Version    : v0.4.0
# ------------------------------------------------------------------------

# @Note: Specify value of config variable via command line has higher priority

# Options for print format
#  [VERBOSE] Print control option, when its value is "1", Makefile will print
#   more details, or it will only print brief
VERBOSE   ?= 0

# Options for MCU configurations
#  [CLKFRE] Specify frequency of MCU clock, the unit is Hz.
CLKFRE    ?= 11059200
#  [CODE] Specify total size of ROM(external+ on-chip) during compilation
#    manually (unit: KB, default: 8KB)
#  [IRAM] Specify total size of internal RAM during compilation manually
#    (unit: B, default: 256)
#  [XRAM] Specify total size of external RAM during compilation manually
#    (unit: KB, default: 0)
CODE      ?= 8
IRAM      ?= 256
XRAM      ?= 0

# Options for build target
#  [MYFILE] Specify user source file or Makefile will fill it with "test.c".
#    It's noticed that once use this option to compile specified .c file,
#    user should add this option when do all targets related to build operation,
#    such as clean and rebuild.
MYFILE    ?= usr/test.c
EXE_C     ?= $(MYFILE)

# Options for number of parallel build jobs
# [JOBS] Specify number of parallel build jobs, this variable only works
#    during run <rebuild> target
JOBS      ?= $(shell nproc)