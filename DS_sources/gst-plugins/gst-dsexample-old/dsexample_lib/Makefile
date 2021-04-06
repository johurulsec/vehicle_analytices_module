################################################################################
# Copyright (c) 2017-2019, NVIDIA CORPORATION.  All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#################################################################################

# all:
# 	gcc -ggdb -c -o dsexample_lib.o -fPIC dsexample_lib.cpp pkg-config opencv --cflags --libs
# 	ar rcs libdsexample.a dsexample_lib.o


# all:
# 	g++ -ggdb -c -o dsexample_lib.o -fPIC dsexample_lib.cpp $(shell pkg-config --cflags $(PKGS))
# 	ar rcs libdsexample.a dsexample_lib.o


# CC = gcc
# CFLAGS = -g -Wall -ggdb -c
# SRCS = dsexample_lib.cpp
# PROG = dsexample_lib.o

# OPENCV = `pkg-config opencv --cflags --libs`
# LIBS = $(OPENCV)

# all:
# 	$(CC) $(CFLAGS) -o $(PROG) -fPIC $(SRCS) $(LIBS)

# 	ar rcs libdsexample.a dsexample_lib.o



PKGS:= gstreamer-1.0 gstreamer-base-1.0 opencv

DS_SDK_ROOT:=/opt/nvidia/deepstream/deepstream
CFLAGS+=-I $(DS_SDK_ROOT)/sources/includes
CFLAGS+=$(shell pkg-config --cflags $(PKGS))
LIBS = `pkg-config --libs opencv`


all:
	gcc -ggdb $(CFLAGS) $(LIBS) -c -o dsexample_lib.o -fPIC dsexample_lib.cpp
	ar rcs libdsexample.a dsexample_lib.o
