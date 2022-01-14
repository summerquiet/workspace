# 这是一个ADFW编写各模块的TestProject的demo

## root

### CMakeLists.txt

cmake的工程文件

### stdafx.h && stdafx.cpp

从win32时期遗留下来的共用头文件
通常定义一些所有文件都需要使用的头文件和全局定义

### TestProject.h && TestProject.cpp

本模块的实体

### TestProjectIF.cpp

对外公开的interface的cpp

## doxygen_template

这个目录下面存放了编写doxygen用的模板

## include

### TestProjectPublicDef.h

用于放置对外公开的定义内容  
并定义了namespace的begin和end

### TestProjectIF.h

对外公开的interface

## test

用于单体测试以及结合测试的测试代码

## utility

本模块使用的工具集  
通常工具集中都是static函数

## working

主要放置本模块的主逻辑
