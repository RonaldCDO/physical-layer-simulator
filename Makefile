#Project Name	
PROJ_NAME=physicalLayerSimulator

#.cpp Files
CPP_SOURCE=$(wildcard ./source/*.cpp)

#.hpp Files
HPP_SOURCE=$(wildcard ./source/*.hpp)

#Object Files
OBJ=$(subst .cpp,.o,$(subst source,objects,$(CPP_SOURCE)))

#Compilator
CC=g++

#Compilator Flags
CC_FLAGS=-g			\
		 -std=c++14 \
		 -pedantic	\
		 -Wall		\
		 -Wextra	\
		 -Wshadow	\


#Remove Command
RM=rm -rf

#
#Linking and Compiling
#
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@echo 'Linking target using G++ Compiler'
	$(CC) $^ -o $@
	@echo ' '

./objects/%.o: ./source/%.cpp ./source/%.hpp
	@echo 'Building target using G++ Compiler'
	$(CC) -c $< $(CC_FLAGS) -o $@ 
	@echo ' ' 

./objects/simulador.o: ./source/simulador.cpp $(HPP_SOURCE)
	@echo 'Building target using GCC Compiler '
	$(CC) -c $< $(CC_FLAGS) -o $@ 
	@echo ' '

objFolder:
	@ mkdir -p objects

clean: 
	@ $(RM) ./objects/*.o $(PROJ_NAME) *~ 
	@ rmdir objects

.PHONY: all clean
