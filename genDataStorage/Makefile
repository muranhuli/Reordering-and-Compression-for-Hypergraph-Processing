PCC = g++
PCFLAGS = -std=c++14 -fopenmp

ALL = reorderingVertices reorderingHyperedges reorderingVerticesHyperedges compressUnordering

all: $(ALL)
% : %.cpp
	$(PCC) $(PCFLAGS) -o $@ $<

clean :
	rm -f *.o $(ALL)

cleansrc :
	rm -f *.o $(ALL) 
	rm $(COMMON)