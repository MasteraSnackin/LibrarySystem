#Makefile
#Author: M00870488
#Created: 1/7/2024
#Updated: 22/1/2024

# Directory of the current Makefile
PROJECT_DIR = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# Object files for the build
OBJECTS = LibSys.o

# Setting flags based on the build mode
ifeq ($(MODE),debug)
	COMPILE_FLAGS += -g
else ifeq ($(MODE),release)
	COMPILE_FLAGS += -O2
else ifeq ($(MODE),profiling)
	COMPILE_FLAGS += -g -pg -fprofile-arcs -ftest-coverage
	LINK_FLAGS += -pg -fprofile-arcs -ftest-coverage
	CLEANUP_FILES += LibSys.gcda LibSys.gcno $(PROJECT_DIR)gmon.out
	POST_BUILD = rm -rf LibSys.gcda
else
    $(error Unsupported build mode $(MODE))
endif

# Default target
default:	LibSystem

# Linking the final executable
LibSystem:	$(OBJECTS)
	$(CXX) $(LINK_FLAGS) -o $@ $^
	$(POST_BUILD)

# Compiling C++ source files
%.o:	$(PROJECT_DIR)%.cpp
	$(CXX) -c $(COMPILE_FLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

# Compiling C source files
%.o:	$(PROJECT_DIR)%.c
	$(CC) -c $(COMPILE_FLAGS) $(CPPFLAGS) -o $@ $<

# Clean target for removing generated files
clean:
	rm -fr LibSystem $(OBJECTS) $(CLEANUP_FILES)
