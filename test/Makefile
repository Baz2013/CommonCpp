GTEST_INC_DIR=/home/bazar/user/gucb/gtest_dir/include
GTEST_LIB_DIR=/home/bazar/user/gucb/gtest_dir/lib
S_LIB_PATH = /home/bazar/user/gucb/GIT/CommonCpp/lib

INC_PATH = /home/bazar/user/gucb/GIT/CommonCpp/common/inc
OBJ_PATH = /home/bazar/user/gucb/GIT/CommonCpp/test/obj

G_LIB = -L$(GTEST_LIB_DIR) -L$(S_LIB_PATH)
 
gtest_demo: ${OBJ_PATH}/TimeUtil_test.o $(GTEST_LIB_DIR)/libgtest.a
	g++ -o gtest_demo -Wall -pthread -lpthread -lrt -fPIC -g ${OBJ_PATH}/TimeUtil_test.o -L$(GTEST_LIB_DIR) $(G_LIB) -lgtest -lcommon

${OBJ_PATH}/TimeUtil_test.o: TimeUtil_test.cpp
	g++ -c -D_GNU_SOURCE -fPIC -g TimeUtil_test.cpp -o ${OBJ_PATH}/TimeUtil_test.o -I$(GTEST_INC_DIR) -I$(INC_PATH)

#${OBJ_PATH}/StringUtil_test.o: StringUtil_test.cpp
#	g++ -c -D_GNU_SOURCE -fPIC -g StringUtil_test.cpp -o ${OBJ_PATH}/StringUtil_test.o -I$(GTEST_INC_DIR) -I$(INC_PATH)

clean:
	rm -rf ${OBJ_PATH}/*.o ./gtest_demo 
