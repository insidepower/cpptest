############# Target type (Debug/Release) ##################
############################################################

###### Predefined macros ################
CPPCompileDebug=-g
CPPCompileRelease=-O
LinkDebug=-g
LinkRelease=-O

RM=/bin/rm -rf
MD=/bin/mkdir -p
INCLUDE_QUALIFIER=-I
#CC=gcc -DUSE_IOSTREAM
CC=gcc
LIB_CMD=ar
LINK_CMD=$(CC)
LIB_FLAGS=rvu
#LINK_FLAGS=-lpthread -lstdc++ $(LinkDebug) 
LINK_FLAGS=-lpthread $(LinkDebug) 

#CPP_EXT=.cpp
C_EXT=.c
H_EXT=.h
OBJ_EXT=.o
EXE_EXT=
LIB_EXT=.a

ConfigurationCPPCompileSwitches=   -I. $(INST_FLAGS) $(INCLUDE_PATH) $(INST_INCLUDES) $(CPPCompileDebug) -c

########################################
####### Context macros ##################
TARGET_NAME=MAC

TARGET_MAIN=main

MAKEFILE_NAME=Makefile

ADDITIONAL_OBJS=

OBJS= 
########################################
####### function macros ##################

ifeq ($(OBJ_DIR),)
CREATE_OBJ_DIR=
CLEAN_OBJ_DIR=
else
CREATE_OBJ_DIR= $(MD) $(OBJ_DIR)
CLEAN_OBJ_DIR=  $(RM) $(OBJ_DIR)
endif

.SUFFIXES: $(C_EXT)
########################################

all : $(TARGET_NAME)$(EXE_EXT) $(MAKEFILE_NAME)
#$(OBJS) :  $(INST_LIBS) $(OXF_LIBS)

#Dsplink.o : Dsplink$(C_EXT) Dsplink$(H_EXT) SignalTrap.h DebugDsp.h DSP_Ctrl.h TxPduMgmt.h DSP_MsgqReply.h RxPduMgt.h 
# @echo Compiling Dsplink$(C_EXT)
# $(CREATE_OBJ_DIR)
# @$(CC) $(ConfigurationCPPCompileSwitches)  -o Dsplink$(OBJ_EXT) Dsplink$(C_EXT)

$(TARGET_MAIN)$(OBJ_EXT) : $(TARGET_MAIN)$(C_EXT) $(OBJS)
	@$(CC) $(ConfigurationCPPCompileSwitches) -o  $(TARGET_MAIN)$(OBJ_EXT) $(TARGET_MAIN)$(C_EXT)

$(TARGET_NAME)$(EXE_EXT): $(OBJS) $(ADDITIONAL_OBJS) $(TARGET_MAIN)$(OBJ_EXT) $(MAKEFILE_NAME)
	@echo Linking $(TARGET_NAME)$(EXE_EXT)
	@$(LINK_CMD)  $(TARGET_MAIN)$(OBJ_EXT) $(OBJS) $(ADDITIONAL_OBJS) \
		$(LIBS) \
		$(INST_LIBS) \
		$(LINK_FLAGS) -o $(TARGET_NAME)$(EXE_EXT)

$(TARGET_NAME)$(LIB_EXT) : $(OBJS) $(ADDITIONAL_OBJS) $(MAKEFILE_NAME)
	@echo Building library $@
	@$(LIB_CMD) $(LIB_FLAGS) $(TARGET_NAME)$(LIB_EXT) $(OBJS) $(ADDITIONAL_OBJS)

clean:
	@echo Cleanup
	$(RM) $(TARGET_MAIN)$(OBJ_EXT) $(ADDITIONAL_OBJS)
	$(RM) $(TARGET_NAME)$(LIB_EXT)
	$(RM) $(TARGET_NAME)$(EXE_EXT)
	$(CLEAN_OBJ_DIR)
#####################################################################
##################### Context dependencies and commands #############

