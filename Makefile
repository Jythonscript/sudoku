TARGET := sudoku
BUILD := build
SOURCES := .
OUTPUT := $(TARGET)

CFILES := $(foreach dir, $(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
OFILES := $(CFILES:%.c=$(BUILD)/%.o)

IDIR=./
CC=gcc

CFLAGS = -I $(IDIR) -O3
CFLAGS += `pkg-config --cflags gtk+-3.0`

LFLAGS=

USE_GTK = 1
USE_READLINE = 1

ifeq ($(USE_GTK), 1)
	LFLAGS += `pkg-config --libs gtk+-3.0`
	CFLAGS += "-D USE_GTK"
endif

ifeq ($(USE_READLINE), 1)
	LFLAGS += -lreadline
	CFLAGS += "-D USE_READLINE"
endif

all: $(BUILD) $(OUTPUT)
debug: CFLAGS += -g
debug: $(BUILD) $(OUTPUT)

.PHONY: all clean

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
