TARGET := udp-parse

SRC := ./src
INC := ./inc

SOURCES := $(shell find $(SRC) -name '*.c')
SRC_DIR := $(shell find $(SRC) -type d)
INC_DIR := $(shell find $(INC) -type d)

CC = gcc
CCFLAGS := -Wall -Wextra -g

CPPFLAGS := $(addprefix -I,$(INC_DIR))

all: $(TARGET)
	@echo
	@echo 'all is done successfully, binary is:'
	@echo
	@size $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CPPFLAGS) $(CCFLAGS) -o $@ $^

.PHONY: clean
clean:
	@rm ./$(TARGET)
