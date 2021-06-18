CC = clang
SRC_DIR = src
INC_DIR = include
OBJ_DIR = objs
CFLAGS = -I$(INC_DIR)
LDFLAGS = 

TEST_TARGET = stack-test
TARGET = abacus


SRC = $(wildcard $(SRC_DIR)/*.c)
$(info $(SRC))
DEPS = $(wildcard $(INC_DIR)/*.h)
_INIT_OBJ = $(SRC:$(SRC_DIR)/%.c=%.o)
_OBJ = $(filter-out $(TEST_TARGET).o, $(_INIT_OBJ))
_TEST_OBJ = $(filter-out $(TARGET).o, $(_INIT_OBJ))
$(info    _OBJ is $(_OBJ))
$(info    _TEST_OBJ is $(_TEST_OBJ))
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))
TEST_OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_TEST_OBJ))

all: dirs $(TARGET)

tests: dirs $(TEST_TARGET)

dirs:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET)
