################ Config

NAME_STATIC = libvnn.a
NAME_DYNAMIC = libvnn.so

COMPILER = g++
O_FLAGS = 
FLAGS = 
ARCHIVER = ar
ARCHIVER_FLAGS = rc

# Theses are specials variables for UE4 projects
COMPILER_UE4 = /home/vyn/Software/UnrealEngine/Engine/Extras/ThirdPartyNotUE/SDKs/HostLinux/Linux_x64/v13_clang-7.0.1-centos7/x86_64-unknown-linux-gnu/bin/clang++ # Change for your need
O_FLAGS_UE4 = -stdlib=libc++ # UE4 needs libc++ instead of libstdc++
FLAGS_UE4 = -stdlib=libc++ -lpthread # libc++ needs libpthread, i don't remember why, i may be wrong

ARCHIVER_UE4 = /home/vyn/Software/UnrealEngine/Engine/Extras/ThirdPartyNotUE/SDKs/HostLinux/Linux_x64/v13_clang-7.0.1-centos7/x86_64-unknown-linux-gnu/bin/llvm-ar # Change for your need
ARCHIVER_UE4_FLAGS = rc

COMPILER = $(COMPILER_UE4) # Uncomment to use UE4 compiler (clang)
O_FLAGS = $(O_FLAGS_UE4) # Uncomment to use UE4 flags for .o compilation (clang flags)
FLAGS = $(FLAGS_UE4) # Uncomment to use UE4 flags (clang flags)

ARCHIVER = $(ARCHIVER_UE4) # Uncomment to use UE4 archiver (llvm-ar)
ARCHIVER_FLAGS = $(ARCHIVER_UE4_FLAGS)
#----------------------------------------------

INCLUDES =	-I includes

SOURCES = 	Neuron.cpp \
			Connection.cpp \
			Layer.cpp \
			Network.cpp \
			Network_Fit.cpp \
			Network_Propagate.cpp \
			Population.cpp \
			functions/activationFunctions.cpp \
			functions/costFunctions.cpp \
			functions/crossOverFunctions.cpp \
			utils/utils.cpp \
			debug/debug.cpp 

################ Setup paths

SRCS = $(addprefix sources/, $(SOURCES)) # All sources are ine 'sources' folder
OBJS = $(SRCS:sources/%.cpp=obj/%.o) # All objects are ine 'obj' folder, mirrored from 'sources'
OBJDIRS := $(dir $(OBJS)) # Get all directories to create them in the 'obj' folder. (remove files from the string)

################ Rules

all: createdir $(NAME)
	
createdir:
	if [ ! -d "obj" ]; then mkdir obj; fi
	-mkdir $(OBJDIRS)

obj/%.o: sources/%.cpp includes/*
	$(COMPILER) $(O_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME_STATIC)
	rm -f $(NAME_DYNAMIC)

static: createdir $(NAME_STATIC)

$(NAME_STATIC): $(OBJS)
	$(ARCHIVER) $(ARCHIVER_FLAGS) $(NAME_STATIC) $(OBJS)

dynamic: setup_dymanic createdir $(NAME_DYNAMIC)

setup_dymanic:
	$(eval O_FLAGS = $(O_FLAGS) -fPIC)

$(NAME_DYNAMIC): $(OBJS)
	$(COMPILER) $(FLAGS) -shared $(OBJS) -o $(NAME_DYNAMIC)

test: static
	$(COMPILER) tests/*.cpp libvnn.a -o test_program
	./test_program