EXPORT_DIRS:=$(shell find $(SRC_DIR) -name .export -printf '%h\n')
OBJECTS:=$(abspath $(wildcard $(EXPORT_DIRS)/*.o))
