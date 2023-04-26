
vpath %.cpp applications
vpath %.h includes


# compilers
PCC = g++
PCFLAGS = -std=c++14 -I includes -fopenmp

COMMON = adjListTest.h oneDimArrayTest.h


ALL = BFSAdjList DFSAdjList KcoreAdjList MISAdjList NQAdjList PRAdjList SCCAdjList SSSPAdjList BFSOneDimArray DFSOneDimArray KcoreOneDimArray MISOneDimArray NQOneDimArray PROneDimArray SCCOneDimArray SSSPOneDimArray

all: $(ALL)
% : %.cpp $(COMMON)
	$(PCC) $(PCFLAGS) -o $@ $<

.PHONY : clean

clean :
	rm -f *.o $(ALL)

cleansrc :
	rm -f *.o $(ALL)·
	rm $(COMMON)