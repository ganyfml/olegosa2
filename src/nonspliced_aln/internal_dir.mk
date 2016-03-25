include standard_defs.mk

$(phony all): $(filesubst %.cpp, %.o, $(wildcard *.cpp))

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(input) -o $(output)

$(phony clean):
	$(RM) `find . -name '*.o' -o -name '*.exe'`
