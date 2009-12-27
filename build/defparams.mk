# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming, duzy@duzy.info
#	

V = debug
OUT_DIR = out/$(V)

UNAME := $(shell uname)

BOOST_DIR := $(HOME)/open/boost_libraries
BOOST_LIB_DIR := $(BOOST_DIR)/stage-$V/lib

