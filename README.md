# HML_FwLib_8051
[![Jenkins](https://img.shields.io/jenkins/build?jobUrl=http%3A%2F%2Fjenkins.zhishan-iot.tk%3A12463%2Fjob%2FHML_FwLib_8051)](http://jenkins.zhishan-iot.tk:12463/job/HML_FwLib_8051)
[![GitHub repo size](https://img.shields.io/github/repo-size/MCU-ZHISHAN-IoT/HML_FwLib_8051)](https://github.com/MCU-ZHISHAN-IoT/HML_FwLib_8051)
[![GitHub](https://img.shields.io/github/license/MCU-ZHISHAN-IoT/HML_FwLib_8051)](https://github.com/MCU-ZHISHAN-IoT/HML_FwLib_8051/blob/master/LICENSE)
[![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/MCU-ZHISHAN-IoT/HML_FwLib_8051?color=26a69a)](https://github.com/MCU-ZHISHAN-IoT/HML_FwLib_8051/tags)

## What is HML_FwLib_8051
HML_FwLib_8051 is the first member component of HML firmware library, **providing a group of interface functions for users to 
operate on-chip resource of MCS-51 MCUs**, including GPIO, external interrupt, timer and UART modules. The 8051 MCUs have been 
one of the most widely used MCUs since it was produced by [Intel](https://www.intel.com/) in 1981. As amateurs with some 
experience of 8051 development, we intend to develop a lite and easy-use tool that can help future developers to complete 
projects based on 8051 MCUs more easily and quickly.

The source codes are written in C language and for [SDCC compiler](http://sdcc.sourceforge.net/), i.e., it can only be compiled
by SDCC. This choice is motivated by the fact that SDCC is free and highly efficient, while there are very few examples of 
application about SDCC on the Internet. We hope that, as one of the early attempts to develop MCU projects using SDCC, this work
will make SDCC become more popular among MCU developers.

Please visit [detail page](https://hw.zhishan-iot.tk/page/hml/detail/fwlib_stc8051.html) for more information to get started it!

## Feature
+ :dart:Based on [SDCC compiler](http://sdcc.sourceforge.net/).
+ Cover all on-chip resource of 8051 MCUs.
+ Open all source code on [Github](https://github.com) and licensed under the [WTPL2](http://wtfpl2.com/).
+ Readable code and provide examples to help you get started it.

## Config
There are several parameters need to be configured before using HML_FwLib_8051 by user manually. It's noticed that the name of 
following macros is different with previous version.
### \_\_CONF\_COMPILE\_xxx (for conditional compilation)
In order to ensure projects based on HML_FwLib_8051 can be downloaded into the limited on-chip memory space of 8051 MCUs, 
developers can modify compile macros which are with format of `__CONF_COMPILE_xxx` in *hml/conf.h* to specify which piece of 
code will take part in compilation, then it will reduce size of final .hex file. For instance, if user only use GPIO module, 
then user just need to enable `__CONF_COMPILE_GPIO` macro in *hml/conf.h*. Some macros for conditional compilation depend on
others. For example, before you enable macro `__CONF_COMPILE_UART`, macro `__CONF_COMPILE_TIM` should be enable at the same 
time. Otherwise, build works will be failed.
### \_\_CONF\_FRE\_CLKIN
A macro marks frequency of clock source and it's defined in *hml/conf.h*. The default value is `11059200UL`. This value can be 
configured via make command line interface variable or config Makefile(refer to *mk/config.mk* or *cmake/config.cmake*)
### \_\_CONF\_HAVE\_T2MOD
When the macro is defined and mark value `1`, it means current MCU has register T2MOD. Besides, if you enable this macro, please
make sure macro `__CONF_HAVE_TIM2` is enabled firstly.
### \_\_CONF\_HAVE\_TIM2
When the macro is defined and mark value `1`, it means current MCU has timer-2.

## Building
We provide two kinds of build system support:
* cmake
* gmake
### cmake
Run this command for initialization. Add option `-GNinja` if you expect to build project via Ninja.
```
$ cmake -S . -B build
```
Run this command for building project. Add option `--clean-first` if you want to execute clean operation before building.
```
$ cmake --build build -j$(nproc)
```
You can execute command `cmake --build build -t usage` for usage. If you want to adjust build details, please modify `cmake/config.cmake`.
### gmake
Execute this command for building HML_FwLib_8051 with GNU Make.
```
$ make -j$(nproc)
```
You can execute command `make help` for usage. If you want to adjust build details, please modify `mk/config.mk`.

## Contribution
Welcome suggestions and contribution from you! You can fork it and make a pull request or contact us via *[mcu@zhishan-iot.tk](mailto:mcu@zhishan-iot.tk)*.

## Team
This is a one-man project....

|member        | role              |e-mail                        |
|--------------|-------------------|------------------------------|
| Weilun Fong  | **Developer**     |[wlf@zhishan-iot.tk](mailto:wlf@zhishan-iot.tk) |
