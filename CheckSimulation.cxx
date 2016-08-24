//==============================================================================
// CheckSimulation.cxx
// This program produces histograms using data 
// from a LArSoft-simulated ROOT file
//
// Gleb Sinev, 2016, gleb.v.sinev@gmail.com
//==============================================================================

#include "CheckSimulation.h"

int main(int argc, char *argv[])
{

  std::cout << "Starting check-simulation.\n";

  int numberOfArguments = 1;
  if (argc != (numberOfArguments + 1))
  {
    std::cout << "Usage: check-simulation inputFile.root.\n";
    return 1;
  }

  return 0;

}
