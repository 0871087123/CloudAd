#Serial模块功能为串口通信
#DNS模块功能为DNS解析，并进行数据包打包解包
#main为主程序
#logic为逻辑部分
#test为UT单元测试，用于对其中各个部分的测试。

#用于PC机测试时选择g++
#用于实际使用时选择arm-linu-g++
#CC = g++
#CXX = arm-linux-gnueabihf-g++
CXXFLAGS = -g

RasDaemon : dns.o Serial.o main.o function.o
	$(CXX) $(CXXFLAGS) -o $@ $^

dns.o : dns.cpp

Serial.o : Serial.cpp

function.o : function.cpp

main.o : main.cpp

clean :
	rm -rf *.o

