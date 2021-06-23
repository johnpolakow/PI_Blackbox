## Calibration Execution Makefile

#defines targets all and clean
.PHONY = all clean

#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#
#	$^ The names of all the prerequisites, with spaces between them.
#	$< The name of the first prerequisite.
#	$@ The file name of the target of the rule

# define the compiler to use
CC = gcc

# compile-time flags
#CFLAGS =-Wall -g -fsanitize=address -static-libasan -fsanitize=leak -fno-omit-frame-pointer
CFLAGS =-g -fsanitize=address -static-libasan -fsanitize=leak -fno-omit-frame-pointer
	# -g provides for debugging with gdb
	# -Wall provides extra errors and warnings from compilation
	# -fsanitize=leak catches memory leaks, out of bound array access, and use after free errors

CAL_DIR =./CAL_DATA/


# define any include directories for header files other than /usr/include
# -I means include directory
INCLUDES = -I $(CAL_DIR) -I ./

# libraries to link into executable:
# link in libbcm2835.so and libm.so: (PI GPIO library and math library)
#LIBS = -l bcm2835 -l m
LIBS =-l bcm2835 -l m -l pthread

# define the source .cpp files
PI_SRC = $(wildcard ./src/Execution_Engine.c) 

PARAMETERS_DEF_FILE = ./Cal_Parameters.cpp
SRCS = $(PI_SRC) 	

# define the name of the executable file 
MAIN = DAQ

OBJ_DIR := obj
BIN_DIR := bin
SRC_DIR := src

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of the rule (a .c file)
#  $@: the name of the target of the rule (a .o file) 
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

PI_OBJ = $(PI_SRC:.c=.o)
OBJS = $(PI_OBJ)

OBJECT_NAMES = $(notdir $(OBJS))
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJECT_NAMES) )

ccred=$(shell echo -e "\033[0;31m")
ccend=$(shell echo -e "\033[0m")

red:=$(shell tput setaf 1)
bold:=$(shell tput bold)
yellow:=$(shell tput setaf 3)
reset:=$(shell tput sgr0)

#OBJ := $(patsubst %,$(OBJ_DIR)%,$(OBJ1))
all: target

# the $(OBJ_DIR) and $(BIN_DIR) creates those directories if they dont already exist
target: object_files
	@cp $(MAIN) $(BIN_DIR)/$(MAIN)

object_files: $(OBJ_DIR) $(BIN_DIR) main 
	@echo "$(yellow) Linking.... $(reset)"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJ) $(LIBS)
	@echo '-------------------------------------------------------------------'
	@echo 'done.'
	@echo 'created executable  "$(bold)$(red)$(MAIN)$(reset)"'
	@echo 'to run, enter command:  $(bold)sudo $(red) ./$(MAIN)$(reset) '

# for all the below rules, the object files are created in the current working directory.
# so the mv command after the compile line moves the object files to the $(OBJ_DIR)
main:
	@echo "$(yellow) PI DAQ Module $(reset)"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $(PI_SRC) $(LIBS)
	@mv *.o $(OBJ_DIR)
	@echo ""

$(OBJ_DIR):
	@mkdir -p $@

$(BIN_DIR):
	@mkdir -p $@
clean:
	$(RM) *.o *~ $(MAIN)
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(BIN_DIR)/*










