LIB_DIR=./lib
LIB_NAME=calc
INCLUDE_DIR=./include
SRC_DIR=./src
TARGET=app
MAIN=main.c
DEPENDENCE=$(MAIN) $(LIB_DIR)/lib$(LIB_NAME).a $(INCLUDE_DIR)
DEP_C=$(wildcard ./src/*.c)
DEP_O=$(patsubst %.c, %.o, $(DEP_C)) 

$(TARGET): $(DEPENDENCE)
	$(CC) $(MAIN) -o $@ -I $(INCLUDE_DIR) -L $(LIB_DIR) -l$(LIB_NAME)	

$(LIB_DIR)/lib$(LIB_NAME).a: $(DEP_O) 
	ar rcs $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)
	$(CC) -c $< -o $@ -I $(INCLUDE_DIR)

.PHONY: clean
clean:
	rm -f $(DEP_O)
