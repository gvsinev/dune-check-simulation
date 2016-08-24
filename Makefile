#
# Makefile for the program that checks a LArSoft-simulated ROOT file
# By Gleb Sinev, gleb.v.sinev@gmail.com
#

OBJS     := CheckSimulation.o
CXX      := g++
CXXFLAGS := -g -std=c++14 -Wall -Werror -pedantic
LDFLAGS  := -g -Wall
RM       := rm


FRAMEWORK_INCS := -I${CANVAS_INC}   \
                  -I${CETLIB_INC}   \
                  -I${FHICLCPP_INC} \
                  -I${GALLERY_INC}  \
                  -I${NUSIMDATA_INC}
INCLUDES       := $(FRAMEWORK_INCS) -I${ROOT_INC}

FRAMEWORK_LIBS := -L${CANVAS_LIB}    -lcanvas_Utilities \
                  -L${CETLIB_LIB}    -lcetlib           \
                  -L${GALLERY_LIB}   -lgallery          \
                  -L${NUSIMDATA_LIB} -lnusimdata_SimulationBase
LIBS           := $(FRAMEWORK_LIBS) $(shell root-config --libs)

check-simulation: $(OBJS)
	$(CXX) $(LDFLAGS) -o check-simulation $(OBJS) $(LIBS)

CheckSimulation.o: CheckSimulation.cxx CheckSimulation.h
	$(CXX) -c $(CXXFLAGS) CheckSimulation.cxx $(INCLUDES)

clean:
	$(RM) $(OBJS) check-simulation
