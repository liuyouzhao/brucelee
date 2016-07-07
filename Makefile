## YunOS-BRU team
## Usage:
## All: make CSP BRU BIN
## (1) make CSP: if u want to build CSP which contains chip code only, use 'make CSP' independently
## (2) make BRU: on the case of the CSP is already built and needd not to be update, 'make BRU'
## (3) make BIN: put all .a into .bin

## global path definitions
BRU_BASE_PATH=	 	$(shell pwd)
BRU_BASE_CONFIG_FILE= 	$(shell ls  $(BRU_BASE_PATH)/.config)
BRU_COMPILE_PREFIX=
CC=			$(BRU_COMPILE_PREFIX)gcc
AR=			$(BRU_COMPILE_PREFIX)ar
BRU_OUT_PATH_SEGMENT=	out/target/product
BRU_OUT_LIB_FOLDER=	lib
BRU_OUT_PATH=
BRU_OUT_PATH_LIB=
BRU_OUT_LIBS=
BRU_OUT_BIN=		bru
########################################################################################

# C build flags
#CFLAGS = -mtune=arm966e-s -march=armv5te -mfloat-abi=soft -fno-builtin
#CFLAGS = -mfloat-abi=soft -fno-builtin
CFLAGS += -c
CFLAGS += -Os
# AR flags
LDFLAGS = -r
#########################################################################################




## check if defconfig is here, then include
ifeq ($(BRU_BASE_CONFIG_FILE),)
    $(error "BRU_BASE_CONFIG_FILE not set yet!")
    exit 1;
endif
-include $(BRU_BASE_PATH)/.config
########################################################################################


## set global vars according to defconfig
ifeq ($(CONFIG_CHIP_VERSION), )
    $(error "CONFIG_CHIP_VERSION not set yet!")
    exit 1;
else
    BRU_OUT_PATH = $(BRU_BASE_PATH)/$(BRU_OUT_PATH_SEGMENT)/$(CONFIG_CHIP_VERSION)
    BRU_OUT_PATH_LIB = $(BRU_BASE_PATH)/$(BRU_OUT_PATH_SEGMENT)/$(CONFIG_CHIP_VERSION)/$(BRU_OUT_LIB_FOLDER)
endif
ifeq ($(CONFIG_CHIP_COMPILE_PREFIX), )
else
    BRU_COMPILE_PREFIX = $(CONFIG_CHIP_COMPILE_PREFIX)
endif
#########################################################################################






## Global functions
define BUILD_MODEL
	$(foreach DIR, $(BRU_SUBDIRS),
		$(eval OBJS=)
		$(warning Entering: $(DIR))
		$(eval include $(DIR)/Makefile) 
		$(foreach S, $(SRCS),
			$(eval OBJS += $(DIR)/$(S:%c=%o))
			$(shell $(CC) $(CFLAGS) $(DIR)/$(S) -o $(DIR)/$(S:%c=%o)) 
			$(warning  building:$(DIR)/$(S) $(CFLAGS)))
		$(shell $(AR) $(LDFLAGS) $(DIR)/$(TARGET) -o $(OBJS))
		$(warning  ar: $(OBJS) ) )
endef
	#$(foreach T, $(TARGETS), 
	#	$(foreach S, $($(T:lib%.a=%)SRCS), 
	#		$(shell $(CC) $(CFLAGS) $(BRU_BASE_PATH)/$(T:lib%.a=%)/$(S) -o $(BRU_BASE_PATH)/$(T:lib%.a=%)/$(S:%c=%o)) 
	#		$(warning building: $(T:lib%.a=%)/$(S)) ) )
	#$(foreach T, $(TARGETS), 
	#	$(shell $(AR) $(LDFLAGS) $(BRU_OUT_PATH_LIB)/$(T) -o $($(T:lib%.a=%)SRCS:%c=$(BRU_BASE_PATH)/$(T:lib%.a=%)/%o) )
	#	$(warning  $($(T:lib%.a=%)OBJS) $(T)) )
#$(shell $(AR) $(LDFLAGS) $(BRU_BASE_PATH)/$(T:lib%.a=%)/$(T) -o $($(T:lib%.a=%)SRCS:%c=$(BRU_BASE_PATH)/$(T:lib%.a=%)/%o) )
#########################################################################################




## Begin to include sub dirs of our yoc models
## let's build!
ifeq ($(CONFIG_BRU_LIBNETUTILS), y)
    BRU_SUBDIRS +=  $(BRU_BASE_PATH)/libs/libnetutils
endif

ifeq ($(CONFIG_BRU_CORE), y)
    BRU_SUBDIRS +=  $(BRU_BASE_PATH)/core
endif
######################################################################


## Copy all .a to out folder
#$(warning build all libs finished, lets copy them to out folder: $(BRU_OUT_LIBS))
BRU:
	$(warning ***************build yoc models*********************)
	$(BUILD_MODEL)
	$(shell mkdir -p $(BRU_OUT_PATH_LIB))
	$(foreach DIR, $(BRU_SUBDIRS), $(shell find $(DIR) -type f -name "*\.a"|xargs -I{} cp {} $(BRU_OUT_PATH_LIB)))
##########################################################################################

## Link all .a to bin
BRU_LIBS = $(shell ls $(BRU_OUT_PATH_LIB))
BRU_LIBS_L = $(foreach L, $(BRU_LIBS), -l$(L:lib%.a=%))

BIN:
	$(warning "libs:"$(BRU_LIBS_L))
	$(shell $(CC) -o $(BRU_OUT_PATH)/$(BRU_OUT_BIN) -L$(BRU_OUT_PATH_LIB) $(BRU_LIBS_L))
#########################################################################################

all: BRU BIN

## just for cleaning
.PHONY:clean
clean:
	$(foreach S, $(BRU_SUBDIRS), $(warning cleaning: $(S)) $(shell find $(S) -type f -name "*\.o"|xargs rm) $(eval include $(S)/Makefile ) $(shell rm $(S)/$(TARGET)))
	$(shell rm -r $(BRU_OUT_PATH))
