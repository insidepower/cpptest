###################################################
################ Context Macros ###################
TARGET_NAME=linklist
TARGET_MAIN=main
MAKEFILE_NAME=Makefile
ADDITIONAL_OBJS=
###################################################
################ Define Object ####################
MEMDEBUG=memDebug
LINKLIST=ll
#OBJS= \
#	$(MEMDEBUG)$(OBJ_EXT) \
#	$(LINKLIST)$(OBJ_EXT) \
#	$(TARGET_MAIN)$(OBJ_EXT)
OBJS = memDebug.o ll.o main.o
###################################################
################ Compile Object ###################
#$(MEMDEBUG)$(OBJ_EXT):$(MEMDEBUG)$(H_EXT)
#memDebug.o: memDebug.h
#	cc -D_GNU_SOURCE -g -Wall -c memDebug.c

#$(LINKLIST)$(OBJ_EXT):$(LINKLIST)$(H_EXT)
#$(TARGET_MAIN)$(OBJ_EXT):$(TARGET_MAIN)$(H_EXT)

all: $(OBJS)
	$(CC) -Wall -g -o main $(OBJS) -lpthread 

$(OBJS):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS)

###################################################
################ Linking Object ###################
###################################################
################ Predefined Macros ################
CPPCompileDebug=-g
CPPCompileRelease=-O
LinkDebug=-g
LinkRelease=-O

MD=/bin/mkdir -p
INCLUDE_QUALIFIER=-I
LIB_CMD=ar
LINK_CMD=$(CC)
LIB_FLAGS=rvu
LINK_FLAGS=-lpthread $(LinkDebug) 

C_EXT=.c
H_EXT=.h
OBJ_EXT=.o
EXE_EXT=
LIB_EXT=.a
###################################################
########### Var Used by Implicit Rules ############
AR=ar
CC=gcc
CXX=g++
#NOTE:CPP=C preprocessor;-E:stop af preprocessing
CPP=$(CC) -E
LINT=lint
RM=/bin/rm -rf
###### flag ######
ARFLAGS=rv
#CFLAGS=-Wall -pedantic -g -D_GNU_SOURCE
CFLAGS=-Wall -g -D_GNU_SOURCE
CXXFLAGS=
CPPFLAGS=
LINTFLAGS=
#$(CC) -c $(CFLAGS) $(CPPFLAGS)
###################################################
################### References ####################
# $@	Full name of the current target
# $?	names of all the prequisites which are newer than the target
# $<	name of the first prequisite
# $^  The names of all the dependencies, with spaces between them. (no duplicates)
# $*  The stem with which an implicit rule matches.
# e.g. 1 $@ is 'dir/a.foo.b'
# target pattern is 'a.%.b' then $* is 'dir/foo'. (use $(*D)=dir, $(*F)=foo)
# e.g. 2 (explicit rule)
# $@ = foo.c
# $*   = foo (with suffix .c removed)
# $+  same as $^, but duplicates are not removed 
