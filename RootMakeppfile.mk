include standard_defs.mk
include objects.mk

$(phony all): $(OBJECTS)
$(phony main): $(wildcard src/**/main*.exe))
$(phony lib): lib/lib$(PACKAGE).a
$(phony clean):
	$(RM) `find src lib -name '*.o' -o -name '*.exe' -o -name '*.a'`
