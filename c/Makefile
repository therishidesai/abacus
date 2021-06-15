CC = clang
SRC_DIR = src
INC_DIR = include
OBJ_DIR = objs
CFLAGS = -I$(INC_DIR)
LDFLAGS = 
SRC = $(wildcard $(SRC_DIR)/*.c)
$(info $(SRC))
DEPS = $(wildcard $(INC_DIR)/*.h)
_OBJ = $(SRC:$(SRC_DIR)/%.c=%.o)
$(info    _OBJ is $(_OBJ))
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

TARGET = abacus-c

all: dirs $(TARGET)

dirs:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
