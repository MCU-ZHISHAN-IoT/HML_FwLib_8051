#!/usr/bin/make

# ------------------------------------------------------------------------
# Author     : Weilun Fong | wlf@zhishan-iot.tk
# Date       : 2021-09-30
# Description: project Makefile
# E-mail     : mcu@zhishan-iot.tk
# Make-tool  : GNU Make (http://www.gnu.org/software/make/manual/make.html)
# Page       : https://hw.zhishan-iot.tk/page/hml/detail/fwlib_8051.html
# Project    : HML_FwLib_8051
# Version    : v0.4.0
# ------------------------------------------------------------------------

# ----------------------------------------
#  Variable define
# ----------------------------------------
# Package Bash shell command
export SHELL       := /bin/bash
export AWK         := awk
export BASENAME    := basename
export CD          := cd
export DATE        := date
export ECHO        := echo
export EECHO       := $(ECHO) -e
export GREP        := grep
export LS          := ls
export NPROC       := nproc
export RM          := rm -f
export TR          := tr
export TRUE        := true
export XARGS       := xargs

# Define number of parallel build jobs
JOS                ?= $(shell $(NPROC))

# Definition of toolchain
CROSS_COMPILE      := sd
AR                 := $(CROSS_COMPILE)ar
CC                 := $(CROSS_COMPILE)cc
MAKE               := make --no-print-directory
PACKIHX            := packihx

# Mark special phony targets
PHONY_LIST_IN      := clean distclean mostlyclean help rebuild version

# Definition of project basic path
ROOTDIR            := $(CURDIR)
INCDIR             := $(ROOTDIR)/inc
MKDIR              := $(ROOTDIR)/mk
OBJDIR             := $(ROOTDIR)/obj
SRCDIR             := $(ROOTDIR)/src

# Configure all custom parameters
SPACE              := $(empty) $(empty)
HIGHLIGHT          := \033[36m
ifeq ($(findstring $(MAKECMDGOALS), $(PHONY_LIST_IN)),)
    ifneq ($(CONF),)
        include $(CONF)
    else
        include $(MKDIR)/config.mk
    endif
    include $(MKDIR)/mcu.mk
endif

#  Definition of of print format
ifneq ("$(VERBOSE)", "0")
    Q :=
    VECHO := @$(TRUE)
else
    Q := @
    VECHO := @$(ECHO)
endif

# Important files
LIB      := libhml_8051.lib
SRCS     := $(wildcard $(SRCDIR)/*.c)
RELS     := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.rel, $(SRCS))
EXE_REL  := $(patsubst %.c, $(OBJDIR)/%.rel, $(notdir $(EXE_C)))

# Target file
TARGET        := output

# Version define
MK_VERSION    := v0.4.0

# ----------------------------------------
#  Build rules
# ----------------------------------------
all: $(OBJDIR)/$(TARGET).hex
	@$(ECHO) ===================================================
	@$(ECHO) Make $(MAKECMDGOALS) done!
	@$(ECHO) ---------------------------------------------------
	@$(ECHO) completed at `$(DATE) "+%Y-%m-%d %H:%M:%S"`
	@$(ECHO) ===================================================

# Startup
startup:
	@$(EECHO) "$(HIGHLIGHT) - Start to build!\033[0m"

# Compile HML source file(*.c)
$(SRCS): startup
$(RELS): $(OBJDIR)/%.rel: $(SRCDIR)/%.c
	$(VECHO) "CC  $<"
	$(Q)$(CC) $< $(CFLAGS) -o $@

# Generate static library
$(OBJDIR)/$(LIB): $(RELS)
	@$(EECHO) "$(HIGHLIGHT) - Make static library `$(BASENAME) $@` \033[0m"
	$(VECHO) "AR  $@"
	$(Q)$(AR) $(AFLAGS) $@ $^

# Compile executable file
$(EXE_REL): $(EXE_C) $(OBJDIR)/$(LIB)
	@$(EECHO) "$(HIGHLIGHT) - Make executable `$(BASENAME) $@` \033[0m"
	$(VECHO) "CC  $<"
	$(Q)$(CC) $< $(CFLAGS) -L$(OBJDIR) -lhml_stc89 -o $(OBJDIR)/`$(BASENAME) $@`

# Generate .hex file
$(OBJDIR)/$(TARGET).ihx: $(EXE_REL)
	@$(EECHO) "$(HIGHLIGHT) - Generate .ihx file \033[0m"
	$(VECHO) "CC  $@"
	$(Q)$(CC) $^ $(OBJDIR)/$(LIB) -o $@
$(OBJDIR)/$(TARGET).hex: $(OBJDIR)/$(TARGET).ihx
	@$(EECHO) "\033[36m - Generate .hex file \033[0m"
	$(VECHO) "PACKIHX $@"
	$(Q)$(PACKIHX) $< > $@ 2>/dev/null

# ----------------------------------------
#  Phony targets
# ----------------------------------------
# [+] clean
.PHONY: clean
clean:
	$(CD) $(OBJDIR) && $(LS) | $(GREP) -vE -e \.lib$$  -e \.lst$$ -e \.rel$$ | $(XARGS) $(RM)
# [+] distclean
.PHONY: distclean
distclean:
	@$(ECHO) "This is a deprecated phony target, please use <mostlyclean> instead of it" >&2
# [+] mostlyclean
.PHONY: mostlyclean
mostlyclean:
	$(RM) $(OBJDIR)/*
# [+] help
.PHONY: help
help:
	@$(ECHO) "Build:"
	@$(ECHO) "    all         - Build target. (include HML library file and user code)"
	@$(ECHO) "    library     - Only build HML library file."
	@$(ECHO) "    rebuild     - Rebuild target(include HML library file and user code). In this case, option -j can't work"
	@$(ECHO) "                 and please pass JOBS variable via command line instead of it, such as \"make rebuild JOBS=8\"."
	@$(ECHO) ""
	@$(ECHO) "Clean:"
	@$(ECHO) "    clean       - Delete temporary files, except for library related files."
	@$(ECHO) "    distclean   - Deprecated phony target."
	@$(ECHO) "    mostlyclean - Delete all temporary files and generated library file."
	@$(ECHO) ""
	@$(ECHO) "Info:"
	@$(ECHO) "    help        - Show help information."
	@$(ECHO) "    version     - Show version information."
	@$(ECHO)
	@$(ECHO) "Some influential variables:"
	@$(ECHO) "    CLKFRE      - Specify clock frequency manually. (unit: Hz)"
	@$(ECHO) "    CODE        - Specify total size of ROM(external & on-chip). (unit: KB, default: 8)"
	@$(ECHO) "    IRAM        - Specify total size of internal RAM. (unit: B, default: 256)"
	@$(ECHO) "    XRAM        - Specify total size of external RAM. (unit: KB)"
	@$(ECHO) ""
	@$(ECHO) "    CONF        - Specify config Makefile. (default: makefile/config.mk)"
	@$(ECHO) "    JOBS        - Specify number of make job, only for make rebuild. (default: `$(NPROC)`)"
	@$(ECHO) "    MYFILE      - Specify user source file or Makefile will fill it with \"usr/test.c\". It's noticed that once "
	@$(ECHO) "                  use this option to compile specified .c file, user should add this option during doing "
	@$(ECHO) "                  other works, such as clean and rebuild."
	@$(ECHO) "    VERBOSE     - When the value is not equal 0, Makefile will print more details during building."
	@$(ECHO) ""
	@$(ECHO) "Examples:"
	@$(ECHO) "    (1) make -j"
	@$(ECHO) "    (2) make -j CLKFRE=11059200 IRAM=256 XRAM=4"
	@$(ECHO) "    (2) make -j library CLKFRE=11059200 IRAM=256 XRAM=4"
# [+] library
.PHONY: library
library: $(OBJDIR)/$(LIB)
	@$(ECHO) ===================================================
	@$(ECHO) Make $(MAKECMDGOALS) done!
	@$(ECHO) ---------------------------------------------------
	@$(ECHO) completed at `$(DATE) "+%Y-%m-%d %H:%M:%S"`
	@$(ECHO) ===================================================
# [+] rebuild
.PHONY: rebuild
rebuild:
	@$(EECHO) "$(HIGHLIGHT) - Clean previous files \033[0m"
	@$(MAKE) mostlyclean
	@$(MAKE) -f Makefile -j$(JOBS) $(MAKEFLAGS)
# [+] version
.PHONY: version
version:
	@$(ECHO) "HmlFwlibMakefile [$(MK_VERSION)]"
	@$(ECHO) "General purpose Makefile for HML firmware library."
	@$(ECHO) "Copyright(c) 2018-2021 ZHISHAN-IoT, all rights reserved."
	@$(ECHO) ""
	@$(ECHO) "Adapted for HML_FwLib_8051 by Weilun Fong <wlf@zhishan-iot.tk>"
	@$(ECHO) "Report bugs and patches to <wlf@zhishan-iot.tk>"
