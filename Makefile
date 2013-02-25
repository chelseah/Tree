OBJECT_tree = testtree.o tree.o item.o 
OBJECT_transit = mergetransit.o tree.o transit.o
OBJECT_opt = parser.o
all: sorttransit

test: testopt

testopt: $(OBJECT_opt)
	$(CXX) -pg -o $@ $^

sorttransit: $(OBJECT_transit)
	$(CXX) -pg -o $@ $^

sorttree: $(OBJECT_tree)
	$(CXX) -pg -o $@ $^

clean:
	$(RM) *.o
	$(RM) .depend
	$(RM) testopt
depend:
	    $(CXX) -MM $(CXXFLAGS) *.cpp > .depend


