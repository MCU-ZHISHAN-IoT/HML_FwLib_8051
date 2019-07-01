# HML_FwLib_8051
[![BuildStatus](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://hw.zhishan-iot.tk/page/hml/detail/fwlib_stc89.html)
[![License](https://img.shields.io/badge/license-WTFPL2-blue.svg)](http://wtfpl2.com/)
[![MCU](https://img.shields.io/badge/mcu-8051-orange.svg)](http://www.stcmcu.com/)
## What is HML_FwLib_8051
HML_FwLib_8051 is the first member component of HML firmware library, **providing a group of interface functions for users to operate on-chip resource of MCS-51 MCUs**, including GPIO, external interrupt, timer and UART modules. The 8051 MCUs have been one of the most widely used MCUs since it was produced by [Intel](https://www.intel.com/) in 1981. As amateurs with some experience of 8051 development, we intend to develop a lite and easy-use tool that can help future developers to complete projects based on 8051 MCUs more easily and quickly.

The source codes are written in C language and for [SDCC compiler](http://sdcc.sourceforge.net/), i.e., it can only be compiled by SDCC. This choice is motivated by the fact that SDCC is free and highly efficient, while there are very few examples of application about SDCC on the Internet. We hope that, as one of the early attempts to develop MCU projects using SDCC, this work will make SDCC become more popular among MCU developers.

Please visit [detail page](https://hw.zhishan-iot.tk/page/hml/detail/fwlib_stc8051.html) for more information to get started it!

## Feature
+ :dart:Based on [SDCC compiler](http://sdcc.sourceforge.net/).
+ Cover all on-chip resource of 8051 MCUs.
+ Open all source code on [Github](https://github.com) and licensed under the [WTPL2](http://wtfpl2.com/).
+ Readable code and provide examples to help you get started it.

## Prerequisite
+ [GNU Make](http://www.gnu.org/software/make/manual/make.html)(recommend)
+ [SDCC compiler](http://sdcc.sourceforge.net/)
+ *\[for Windows\]* Unix shell tools([msys](http://www.mingw.org/wiki/MSYS), [Cygwin](http://www.cygwin.com/), [GNUwin32](http://gnuwin32.sourceforge.net/)) needed by makefile for SDCC

## Usage
### file structure
```bash
HML_FwLib_8051
├─doc      #store related documents about HML_FwLib_8051
├─example  #provide some example files with *.c format to help users learn about HML_FwLib_8051
├─inc      #include all header files(*.h) of HML_FwLib_8051
├─obj      #store all output files, including *.hex,*.ihx,*.lk,*.rel and others during compilation
├─src      #store all source files(*.c) of HML_FwLib_8051
└─usr      #store makefile and a source file which includes main function
```
### configuration
There are several parameters need to be configured by user manually.
#### \_FRE\_OSC\_
The macro mark frequency of clock source, including extern crystal oscillator, and it's defined in *macro.h*. The default value is `11059200L`.
#### conditional compilation
In order to ensure the projects based on HML_FwLib_8051 can be downloaded into the limited on-chip store space of 8051 MCUs, the developers can modify the macro definition named `___COMPILE_XXX___` in *macro.h* to specify which piece of code should be compiled, thus to reduce the size of the HEX file. If user only use GPIO module, then user just need to enable `___COMPILE_GPIO___` macro definition in macro.h. Some macros for conditional compilation rely on others. For example, before you define the macro definition `___COMPILE_UART___`, the macro `___COMPILE_TIM___` should be defined, otherwise the compilation would be failed.
### code & compile
There is a source file named *test.c* under *usr* directory, we have put a main function here. User can add and modify own code here, then enter <kbd>make</kbd> in terminal, the Makefile will work and complete compilation. From version V0R3, you can enter <kbd>make help</kbd> to get all usages, and former version makefile only support <kbd>make</kbd>, <kbd>make clean</kbd>, <kbd>make mostlyclean</kbd>(change into <kbd>make distclean</kbd> now)

Certainly, you can just add *inc* and *src* directory into your project, and write your own makefile to build a custom project. 

## Contributing
Welcome suggestions and contribution from you! You can fork it or contact us via *[mcu@zhishan-iot.tk](mailto:mcu@zhishan-iot.tk)*.

## License
HML_FwLib_8051 is licensed under the [WTFPL2](http://wtfpl2.com/).

##  Team
This is a one-man project....

|member        | role              |e-mail                        |
|--------------|-------------------|------------------------------|
| Weilun Fong  | **Developer**     |[wlf@zhishan-iot.tk](mailto:wlf@zhishan-iot.tk) |
