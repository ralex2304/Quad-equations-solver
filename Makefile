.PHONY: all clean

CC = g++
CFLAGS= -fdiagnostics-color=always -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef			\
		-Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs 			\
		-Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual	\
		-Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers 	\
		-Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual 			\
		-Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel 		\
		-Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

BUILD_DIR = build/
TARGET = main.exe

FILES = main.cpp quad_solver.cpp input.cpp args_parser.cpp test/test.cpp

OBJ = $(FILES:%=$(BUILD_DIR)%)
DEPENDS = $(OBJ:%.cpp=%.d)
OBJECTS = $(OBJ:%.cpp=%.o)

all: $(TARGET)

main.exe: $(OBJECTS)
	$(CC) $^ -o $@

-include $(DEPENDS)

$(BUILD_DIR)%.o: %.cpp
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	del *.o /a /s
	del $(TARGET)

echo:
	@echo $(DEPENDS)
