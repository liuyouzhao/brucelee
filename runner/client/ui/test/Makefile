# C build flags
#CFLAGS = -mtune=arm966e-s -march=armv5te -mfloat-abi=soft -fno-builtin
#CFLAGS = -mfloat-abi=soft -fno-builtin

CC = gcc
AR = ar

CFLAGS += -c
CFLAGS += -Os -ggdb
# AR flags
LDFLAGS = -r
#########################################################################################

SRCS = graph_test.c \
	  ../graph/graph.c 


## Global functions
all:
	$(foreach S, $(SRCS), $(eval OBJS += $(S:%c=%o)) $(shell $(CC) $(CFLAGS) $(S) -o $(S:%c=%o)) $(warning  building:$(S) $(CFLAGS)))
	$(shell $(AR) $(LDFLAGS) libtest.a -o $(OBJS))
	$(shell $(CC) -L./ -ltest -o test)
	$(warning  ar: $(OBJS) )
#########################################################################################


## just for cleaning
.PHONY:clean
clean:
	$(foreach S, $(SRCS), $(eval OBJS += $(S:%c=%o)))
	$(warning rm $(OBJS))
	$(shell rm -r $(OBJS))
