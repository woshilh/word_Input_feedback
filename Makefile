DIR := ./inc/ ./inc/thread/ ./inc/inet/
SRC := ./src/ ./src/thread/ ./src/inet/
SRCS := $(wildcard ./src/*.cc) $(wildcard ./src/thread/*.cc) $(wildcard ./src/inet/*.cc)

LIBS := -pthread

CXX := g++

CXXFLAGS := -Wall -g -std=c++11 $(addprefix -I, $(DIR)) $(LIBS)

EXE := ./main.exe

$(EXE) : $(SRCS)
	$(CXX) -o $(EXE) $(SRCS) $(CXXFLAGS)

clean:
	rm -rf ./main.exe
