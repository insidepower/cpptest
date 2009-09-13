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
OBJS= \
	$(MEMDEBUG)$(OBJ_EXT) \
	$(LINKLIST)$(OBJ_EXT)
###################################################
################ Compile Object ###################
$(MEMDEBUG)$(OBJ_EXT): $(MEMDEBUG)$(H_EXT)
	$(CC) -D_GNU_SOURCE -c -g -o $@ $(MEMDEBUG)$(C_EXT)

all: $(TARGET_NAME)$(EXE_EXT) $(MAKEFILE_NAME)

$(TARGET_NAME)$(EXE_EXT):$(OBJS) $(TARGET_MAIN)$(OBJ_EXT)

###################################################
################ Linking Object ###################
###################################################
################ Predefined Macros ################
CPPCompileDebug=-g
CPPCompileRelease=-O
LinkDebug=-g
LinkRelease=-O

RM=/bin/rm -rf
MD=/bin/mkdir -p
INCLUDE_QUALIFIER=-I
CC=gcc
CFLAGS=-Wall -g -D_GNU_SOURCE
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
