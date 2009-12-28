# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming <duzy@duzy.info>
#

SM_MODULE_DIR := $(call sm-module-dir)
SM_MODULE_TYPE := static
SM_MODULE_NAME := libsmart.a
SM_MODULE_SOURCES := $(wildcard src/*.cpp)
SM_MODULE_HEADERS := 
SM_MODULE_INCLUDES := a b c -Iinclude


