# ROOT must be set first
TARGET = libnetutils.a
#ROOT = $(BRU_BASE_PATH)/$(NAME)

# Headers path
CFLAGS += -I$(BRU_BASE_PATH)/libs/libnetutils/include

# all .c files under
#$(NAME)SRCS = $(shell find $(ROOT) -type f -name "*\.c")

# u can set manually here
SRCS = ./source/json/cJSON.c \
	./source/codecs/md5.c \
	./source/codecs/urldecode.c \
	./source/codecs/base64.c

