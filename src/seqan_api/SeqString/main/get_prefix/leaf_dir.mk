include standard_defs.mk
include objects.mk

$(phony all): $(filesubst %.cpp, %.exe, $(shell find . -type d -name backup -prune -o -type f -name '*.cpp'))

#$(phony all): $(filesubst %.cpp, %.exe, $(shell find . -maxdepth 1 -type f -name '*.cpp'))

ifdef FILTERING_PATTERN

FILTERED_OBJECTS:=$(filter-out $(FILTERING_PATTERN), $(OBJECTS))

%.exe: %.o $(FILTERED_OBJECTS)
	$(CXX) -o $(output) $(inputs) $(LDLIBS) $(LDFLAGS)

else

%.exe: %.o $(OBJECTS)
	$(CXX) -o $(output) $(inputs) $(LDLIBS) $(LDFLAGS) 

endif

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(input) -o $(output)

