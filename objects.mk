EXPORT_DIRS:=$(shell find $(SRC_DIR) -type d -name backup -prune -o -name .export -printf '%h\n')
OBJECTS:=$(abspath $(wildcard $(EXPORT_DIRS)/*.o))
