TARGET := sudoku
BUILD := build
SOURCES := .
OUTPUT := $(TARGET)

CFILES := $(foreach dir, $(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
OFILES := $(CFILES:%.c=$(BUILD)/%.o)

IDIR=./
CC=gcc
CFLAGS=-I $(IDIR) -O3
LFLAGS=-lreadline

.PHONY: all clean

all: $(BUILD) $(OUTPUT)

# @ means less verbose
# $@ means current target
$(BUILD):
	@[ -d $@ ] || mkdir -p $@

clean:
	rm -rf $(BUILD) $(TARGET)

$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT): $(OFILES)
	$(CC) $(LFLAGS) -o $@ $^
