# 编译器设置
CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lzmq

# 目标文件
CLIENT_TARGET = client
SERVER_TARGET = server

# 默认构建客户端和服务器
all: $(CLIENT_TARGET) $(SERVER_TARGET)

# 客户端构建规则
$(CLIENT_TARGET): client.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# 服务器构建规则
$(SERVER_TARGET): server.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# 清理规则
clean:
	rm -f $(CLIENT_TARGET) $(SERVER_TARGET)


.PHONY: all clean run_client run_server
