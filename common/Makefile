#makefile 文件
MAIN_PATH = ..
OBJ_PATH = ${MAIN_PATH}/common/obj
LIB_PATH = ${MAIN_PATH}/lib
BIN_PATH = ${MAIN_PATH}/bin
SRC_PATH = $(MAIN_PATH)/common/src
INC_PATH = $(MAIN_PATH)/common/inc

##编译环境
CC        = g++
CFLAGS    = -g #-brtl -q64 -O -lc -bnoquiet #-Ddebug
CCINC     = -I$(INC_PATH) #-I$(ALTIBASE_INC)
##CCLIB     = $(ORALIBS) $(ALTIBASE_LIB)
LINK.CC   = $(CC) $(CFLAGS) $(CCINC) #$(CCLIB)
COMP.CC   = $(CC) $(CFLAGS) $(CCINC)


clean:
	-@rm -f ${OBJ_PATH}/*.o ${LIB_PATH}/libcommon.a 

TARGET = ${LIB_PATH}/libcommon.a 
all: $(TARGET)

${LIB_PATH}/libcommon.a: ${OBJ_PATH}/StringUtil.o
	ar r ${LIB_PATH}/libcommon.a ${OBJ_PATH}/StringUtil.o

${OBJ_PATH}/StringUtil.o:${SRC_PATH}/StringUtil.cpp
	$(COMP.CC) -o ${OBJ_PATH}/StringUtil.o -c ${SRC_PATH}/StringUtil.cpp -I ${INC_PATH}

