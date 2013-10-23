# VPS_Server负责收集AD数据，当Rasp连接时给Arduino下指令。
# 目    标：VCloudd
# 测试目标：debug
# 文    件：main.cpp function.cpp stream.cpp

VCloudd : main.cpp function.cpp stream.cpp log.cpp
	g++ -o $@ $^ --static

debug : main.cpp function.cpp stream.cpp log.cpp
	g++ -g -D__DEBUG__ -Wall -o VCloudd $^

clean :
	rm -rf VCloudd
