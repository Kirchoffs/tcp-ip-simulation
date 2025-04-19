CC = clang
CFLAGS = -Wall -Wextra -I./src -I./src/utils
SRC_DIR = src
UTILS_DIR = src/utils
TEST_DIR = tests
BUILD_DIR = build

GRAPH_SRC = $(SRC_DIR)/graph.c
GLUE_LIST_SRC = $(UTILS_DIR)/glue_doubly_linked_list.c
SIMPLIFIED_LIST_SRC = $(UTILS_DIR)/simplified_glue_doubly_linked_list.c

GRAPH_TEST = $(TEST_DIR)/graph_test.c
GLUE_LIST_TEST = $(TEST_DIR)/glue_doubly_linked_list_test.c

GRAPH_TEST_BIN = $(BUILD_DIR)/graph_test
GLUE_LIST_TEST_BIN = $(BUILD_DIR)/glue_list_test

all: $(GRAPH_TEST_BIN) $(GLUE_LIST_TEST_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(GRAPH_TEST_BIN): $(GRAPH_TEST) $(GRAPH_SRC) $(SIMPLIFIED_LIST_SRC)
	$(MAKE) $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(GLUE_LIST_TEST_BIN): $(GLUE_LIST_TEST) $(GLUE_LIST_SRC)
	$(MAKE) $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

test: $(GRAPH_TEST_BIN) $(GLUE_LIST_TEST_BIN)
	@echo "Running tests..."
	@$(BUILD_DIR)/graph_test
	@$(BUILD_DIR)/glue_list_test

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
