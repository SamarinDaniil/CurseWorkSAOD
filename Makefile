APP_NAME = saod
LIB_NAME = libsaod
TEST_NAME = saod-test

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I src -MP -MMD
CPPFLAGST = -I thirdparty -MP -MMD
LDFLAGS =
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test

APP_PATH = $(BIN_DIR)/$(APP_NAME)
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a

SRC_EXT = cpp
TEST_EXT = cpp

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

TEST_SOURCES = $(shell find $(TEST_DIR) -name '*.$(SRC_EXT)')
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.$(TEST_EXT)=$(OBJ_DIR)/$(TEST_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
		g++ $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(LIB_PATH): $(LIB_OBJECTS)
		ar rcs $@ $^

$(OBJ_DIR)/%.o: %.cpp
		g++ -c $(CFLAGS) $(CPPFLAGS) $(CPPFLAGST) $< -o $@

.PHONY: clean
clean:
		$(RM) $(APP_PATH) $(TEST_PATH) $(LIB_PATH)
		find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
		find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;

.PHONY: test
test: $(TEST_PATH)

-include $(DEPS)

obj/test/main.o: test/main.cpp
		g++ -c $(CFLAGS) $(CPPFLAGS) $(CPPFLAGST) test/main.cpp -o obj/test/main.o $(LDLIBS)

obj/test/test.o: test/test.cpp
		g++ -c $(CFLAGS) $(CPPFLAGS) $(CPPFLAGST) test/test.cpp -o obj/test/test.o $(LDLIBS)

$(TEST_PATH): $(TEST_OBJECTS) $(LIB_PATH)
		g++ $(CPPFLAGST) $^ -o $@ $(LDFLAGS) $(LDLIBS)
