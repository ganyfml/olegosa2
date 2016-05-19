include standard_defs.mk

$(phony all): $(filesubst %.cpp, %.o, $(shell find . -type d -name backup -prune -o -type f -name '*.cpp'))

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(input) -o $(output)

$(phony clean):
	$(RM) `find . -name '*.o' -o -name '*.exe'`
