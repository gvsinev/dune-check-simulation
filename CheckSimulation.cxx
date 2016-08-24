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
    std::cerr << "Usage: check-simulation inputFile.root.\n";
    return 1;
  }
  std::vector< std::string > fileNames{ std::string(argv[1]) };

  std::string outputFileName("output.root");
  TFile outputFile(outputFileName.c_str(), "RECREATE");
  if (outputFile.IsZombie())
  {
    std::cerr << "Unable to open " << outputFileName << ", exiting...\n";
    return 1;
  }

  TTree tree("GeneratorTree", "Generator-level information");
  if (tree.IsZombie())
  {
    std::cerr << "Unable to create " << tree.GetName() << ", exiting...\n";
    return 1;
  }
  int   eventID;
  int   NParticles;
  std::vector< float > PDGVector;
  std::vector< float > energyVector;
  tree.Branch("EventID",      &eventID,    "EventID/I"   );
  tree.Branch("NParticles",   &NParticles, "NParticles/I");
  tree.Branch("PDGVector",    &PDGVector   );
  tree.Branch("EnergyVector", &energyVector);

  art::InputTag generatorTag { "generator" };

  for (gallery::Event event(fileNames); !event.atEnd(); event.next())
  {
    eventID = event.eventEntry();

    auto const& MCTruths = 
      *event.getValidHandle< std::vector < simb::MCTruth > >(generatorTag);
    if (!MCTruths.empty()) {
      NParticles = MCTruths[0].NParticles();
      PDGVector   .reserve(NParticles);
      energyVector.reserve(NParticles);
      for (int index = 0; index < NParticles; ++index)
      {
        auto const& particle = MCTruths[0].GetParticle(index);
        PDGVector   .emplace_back(particle.PdgCode());
        energyVector.emplace_back(particle.E()      );
      }
    }

    tree.Fill();
    PDGVector   .clear();
    energyVector.clear();
  }

  outputFile.Write();
  outputFile.Close();

  return 0;

}
