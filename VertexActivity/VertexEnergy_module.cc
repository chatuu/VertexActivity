////////////////////////////////////////////////////////////////////////
// Class:       VertexEnergy
// Plugin Type: producer (art v2_13_00)
// File:        VertexEnergy_module.cc
//
// Generated at Wed Sep 16 23:24:57 2020 by Chatura Kuruppu using cetskelgen
// from cetlib version v3_06_01.
////////////////////////////////////////////////////////////////////////

#include "CAFMaker/CAFMakerParams.h"
#include "CAFMaker/FillEnergies.h"
#include "CAFMaker/FillPIDs.h"
#include "CAFMaker/FillParentInfo.h"
#include "CAFMaker/FillReco.h"
#include "CAFMaker/FillTruth.h"
#include "CAFMaker/Utils.h"
// C/C++ includes
#include <fenv.h>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#ifdef DARWINBUILD
#include <libgen.h>
#endif
// ROOT includes
#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
// Framework includes
#include <art/Framework/Services/Optional/TFileService.h>
#include <art/Framework/Services/Optional/TFileDirectory.h>
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/FileBlock.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/SubRun.h"
#include "art/Framework/Services/Optional/TFileDirectory.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "canvas/Persistency/Common/FindMany.h"
#include "canvas/Persistency/Common/FindManyP.h"
#include "canvas/Persistency/Common/FindOne.h"
#include "canvas/Persistency/Common/FindOneP.h"
#include "canvas/Persistency/Common/Ptr.h"
#include "canvas/Persistency/Common/PtrVector.h"
#include "cetlib_except/exception.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
//#include <IFDH_service.h>
// NOvASoft includes
// Geo/Cal/Util
#include "Calibrator/Calibrator.h"
#include "ChannelInfo/BadChanList.h"
#include "Geometry/Geometry.h"
#include "Geometry/LiveGeometry.h"
#include "GeometryObjects/CellGeo.h"
#include "GeometryObjects/Geo.h"
#include "GeometryObjects/PlaneGeo.h"
#include "Metadata/MetadataManager.h"
#include "NovaDAQConventions/DAQConventions.h"
#include "RawData/RawTrigger.h"
#include "RunHistory/service/RunHistoryService.h"
#include "Utilities/func/MathUtil.h"
// DataQuality
#include "DataQuality/DAQHeader/DAQEventSummary.h"
// Sim/BackTracker
#include "MCCheater/BackTracker.h"
#include "MCReweight/FluxWeights.h"
#include "Simulation/GENIEReweightTable.h"
#include "nusimdata/SimulationBase/GTruth.h"
#include "nusimdata/SimulationBase/MCFlux.h"
#include "nusimdata/SimulationBase/MCNeutrino.h"
#include "nusimdata/SimulationBase/MCParticle.h"
#include "nusimdata/SimulationBase/MCTruth.h"
// RecoBase
#include "RecoBase/CellHit.h"
#include "RecoBase/Cluster.h"
#include "RecoBase/Energy.h"
#include "RecoBase/FilterList.h"
#include "RecoBase/FitSum.h"
#include "RecoBase/Prong.h"
#include "RecoBase/RecoHit.h"
#include "RecoBase/Shower.h"
#include "RecoBase/Track.h"
#include "RecoBase/Vertex.h"
#include "RecoBase/WeightedProng.h"
// Other Reco
#include "CVN/func/CVNFeatures.h"
#include "CVN/func/PixelMap.h"
#include "CVN/func/ProngTrainingData.h"
#include "CVN/func/Result.h"
#include "CVN/func/RegResult.h"
#include "CVN/func/TrainingData.h"
#include "CosRej/CosRejObj.h"
#include "CosRej/NueCosRej.h"
#include "CosRej/TrkCntObj.h"
#include "LEM/PIDDetails.h"
#include "LSTME/prediction/LSTMEnergy.h"
#include "MEFinder/MEClusters.h"
#include "MuonRemove/art/MRCCParent.h"
#include "NCID/NCCosRej.h"
#include "NumuEnergy/NumuE.h"
#include "Preselection/PreselObj.h"
#include "Preselection/Veto.h"
#include "ReMId/ReMId.h"
#include "RecVarPID/RVP.h"
#include "RecoJMShower/EID.h"
#include "RecoJMShower/JMShower.h"
#include "ShowerLID/DedxDistribution.h"
#include "ShowerLID/EventLID.h"
#include "ShowerLID/ShowerLID.h"
#include "ShowerLID/ShowerPID.h"
#include "ShowerLID/SliceLID.h"
#include "SliceLID/prediction/Prediction.h"
#include "XSecReco/art/NCPi0BkgRej.h"
#include "XnuePID/Xnue.h"
#include "TensorFlowProducts/CVNCosmicFiltList.h"
#include "TrackInfo/TrackInfoObj.h"
// SummData
#include "SummaryData/CosmicExposure.h"
#include "SummaryData/EventQuality.h"
#include "SummaryData/POTSum.h"
#include "SummaryData/SpillData.h"
// OscLib - for woscdumb
//#include "OscLib/func/OscCalculatorDumb.h"
// StandardRecord
#include "StandardRecord/SRSpillTruthBranch.h"
#include "StandardRecord/StandardRecord.h"
// CAFMaker support
#include "CAFMaker/Blinding.h"
#include "Utilities/AssociationUtil.h"

// Custom made headers
#include "structs.h"

class VertexEnergy;

class VertexEnergy : public art::EDProducer
{
public:
  explicit VertexEnergy(fhicl::ParameterSet const &p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  VertexEnergy(VertexEnergy const &) = delete;
  VertexEnergy(VertexEnergy &&) = delete;
  VertexEnergy &operator=(VertexEnergy const &) = delete;
  VertexEnergy &operator=(VertexEnergy &&) = delete;

  // Required functions.
  void produce(art::Event &e) override;

  // Selected optional functions.
  void beginJob() override;
  void beginRun(art::Run &r) override;
  void beginSubRun(art::SubRun &sr) override;
  void endJob() override;
  void endRun(art::Run &r) override;
  void endSubRun(art::SubRun &sr) override;
  void respondToCloseInputFile(art::FileBlock const &fb) override;
  void respondToCloseOutputFiles(art::FileBlock const &fb) override;
  void respondToOpenInputFile(art::FileBlock const &fb) override;
  void respondToOpenOutputFiles(art::FileBlock const &fb) override;

private:
  // Declare member data here.
};

VertexEnergy::VertexEnergy(fhicl::ParameterSet const &p)
// :
// Initialize member data here.
{
  // Call appropriate produces<>() functions here.
}

void VertexEnergy::produce(art::Event &e)
{
  // Implementation of required member function here.
}

void VertexEnergy::beginJob()
{
  // Implementation of optional member function here.
}

void VertexEnergy::beginRun(art::Run &r)
{
  // Implementation of optional member function here.
}

void VertexEnergy::beginSubRun(art::SubRun &sr)
{
  // Implementation of optional member function here.
}

void VertexEnergy::endJob()
{
  // Implementation of optional member function here.
}

void VertexEnergy::endRun(art::Run &r)
{
  // Implementation of optional member function here.
}

void VertexEnergy::endSubRun(art::SubRun &sr)
{
  // Implementation of optional member function here.
}

void VertexEnergy::respondToCloseInputFile(art::FileBlock const &fb)
{
  // Implementation of optional member function here.
}

void VertexEnergy::respondToCloseOutputFiles(art::FileBlock const &fb)
{
  // Implementation of optional member function here.
}

void VertexEnergy::respondToOpenInputFile(art::FileBlock const &fb)
{
  // Implementation of optional member function here.
}

void VertexEnergy::respondToOpenOutputFiles(art::FileBlock const &fb)
{
  // Implementation of optional member function here.
}

DEFINE_ART_MODULE(VertexEnergy)
