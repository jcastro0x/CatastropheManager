APP			:= CatastropheManager
CCGLAFS		:= -Wall -pedantic -std=c++17 -O3
LIBS_DIR	:= /usr/local/lib
LIBS		:= -lboost_date_time -lboost_program_options -lpthread
CC			:= g++
SOURCE_DIR	:= src
BUILD_DIR_N	:= build
ALLCPPS		:= $(shell find $(SOURCE_DIR) -type f -iname *.cpp)

APP : build_dir
	$(CC) $(ALLCPPS) $(CCGLAFS) $(LIBS) -L$(LIBS_DIR) -Iinclude -o $(BUILD_DIR_N)/$(APP)

build_dir:
	mkdir -p $(BUILD_DIR_N)