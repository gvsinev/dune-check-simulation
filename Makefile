#
# Makefile for the program that checks a LArSoft-simulated ROOT file
# By Gleb Sinev, gleb.v.sinev@gmail.com
#

OBJS     := CheckSimulation.o
CXX      := g++
CXXFLAGS := -g -std=c++14 -Wall -Werror -pedantic
LDFLAGS  := -g -Wall
RM       := rm


LARSOFT_INCS := 
INCLUDES     := $(LARSOFT_INCS) -I${ROOT_INC}

LARSOFT_LIBS := 
LIBS         := $(LARSOFT_LIBS) $(shell root-config --libs)

check-simulation: $(OBJS)
	$(CXX) $(LDFLAGS) -o check-simulation $(OBJS) $(LIBS)

CheckSimulation.o: CheckSimulation.cxx CheckSimulation.h
	$(CXX) -c $(CXXFLAGS) CheckSimulation.cxx $(INCLUDES)

clean:
	$(RM) $(OBJS) check-simulation
