.PHONY: all clean

CC = g++
CFLAGS= -fdiagnostics-color=always -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef			\
		-Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs 		\
		-Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual	\
		-Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers \
		-Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual 			\
		-Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel 		\
		-Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

CD = $(shell cd)

BUILD_DIR = build
NESTED_DIRS = test

TARGET = main.exe

FILES = $(shell dir /s /a /b *.cpp)

MAKE_DIRS = $(NESTED_DIRS:%=$(BUILD_DIR)\\%)
OBJ = $(FILES:$(CD)\\%=$(BUILD_DIR)\\%)
DEPENDS = $(OBJ:%.cpp=%.d)
OBJECTS = $(OBJ:%.cpp=%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CC) $^ -o $@

$(BUILD_DIR):
	@if not exist $@ md $@

$(MAKE_DIRS): | $(BUILD_DIR)
	@if not exist $@ md $@

-include $(DEPENDS)

$(BUILD_DIR)\\%.o: %.cpp docs | $(MAKE_DIRS)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

docs:
	@doxygen.exe docs/Doxyfile

clean:
	@del *.o /a /s
	@del *.d /a /s
	@del $(TARGET)

