////////////////////////////////////////////////////////////////////////
// Class:       VertexEnergy
// Plugin Type: producer (art v2_13_00)
// File:        VertexEnergy_module.cc
//
// Generated at Wed Sep 16 23:24:57 2020 by Chatura Kuruppu using cetskelgen
// from cetlib version v3_06_01.
////////////////////////////////////////////////////////////////////////
#include "headers.h"
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
  void reconfigure(const fhicl::ParameterSet &pset);

private:
  // Declare member data here.
  template <class T>
  void GetByLabelStrict(const art::Event &evt, const std::string &label,
                        art::Handle<T> &handle) const;

  template <class T, class U>
  art::FindManyP<T> FindManyPStrict(const U &from, const art::Event &evt,
                                    const art::InputTag &label) const;
  std::string fSlicerLabel;
  std::string fElasticArmsLabel;
  std::string fCellHitLabel;

  fhicl::ParameterSet fVol1, fVol2, fVol3, fVol4;
  std::vector<fhicl::ParameterSet> fVols;
  //std::array test;

  std::vector<volume> vols;
};

VertexEnergy::VertexEnergy(fhicl::ParameterSet const &p)
// :
// Initialize member data here.
{
  fSlicerLabel = p.get<std::string>("SlicerLabel");
  fElasticArmsLabel = p.get<std::string>("ElasticArmsLabel");
  fCellHitLabel = p.get<std::string>("CellHitLabel");

  fVols.push_back(p.get<fhicl::ParameterSet>("volume1"));
  fVols.push_back(p.get<fhicl::ParameterSet>("volume2"));
  fVols.push_back(p.get<fhicl::ParameterSet>("volume3"));
  fVols.push_back(p.get<fhicl::ParameterSet>("volume4"));
}

void VertexEnergy::produce(art::Event &e)
{
  // Implementation of required member function here.
  art::ServiceHandle<cheat::BackTracker> bt;
  art::Handle<std::vector<rb::Cluster>> slices;
  GetByLabelStrict(e, fSlicerLabel, slices);
  auto fmElastic = FindManyPStrict<rb::Vertex>(slices, e, fElasticArmsLabel);
  art::Handle<std::vector<rb::CellHit>> htHandle;
  e.getByLabel(fCellHitLabel, htHandle);
  art::PtrVector<rb::CellHit> allHits;
}

void VertexEnergy::beginJob()
{
  // Implementation of optional member function here.
  printf("\nVertex Activity Module Started..!\n");
  //std::cout << "testing: " << fVol1.get<int>("xMin") << "\n";
  printf("\nVolumes defined:");
  unsigned int vol = 1;
  for (auto it = fVols.begin(); it != fVols.end(); ++it)
  {
    printf("\nVolume %d: Xmin: %d Xmax: %d Ymin: %d Ymax: %d Zmin: %d Zmax: %d",
           vol,
           it->get<int>("xMin"),
           it->get<int>("xMax"),
           it->get<int>("yMin"),
           it->get<int>("yMax"),
           it->get<int>("zMin"),
           it->get<int>("zMax"));
    vol++;
  }
  printf("\n\n\n\n");
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
  printf("\nVertex Activity Module has finished job..!\n");
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
//......................................................................
template <class T>
void VertexEnergy::GetByLabelStrict(const art::Event &evt,
                                    const std::string &label,
                                    art::Handle<T> &handle) const
{
  evt.getByLabel(label, handle);
  if (!label.empty() && handle.failedToGet())
  {
    std::cout << "CAFMaker: No product of type '"
              << abi::__cxa_demangle(typeid(*handle).name(), 0, 0, 0) << "' found under label '" << label << "'. "
              << "Set 'StrictMode: false' to continue anyway." << std::endl;
    abort();
  }
}
//......................................................................
template <class T, class U>
art::FindManyP<T> VertexEnergy::FindManyPStrict(const U &from,
                                                const art::Event &evt,
                                                const art::InputTag &tag) const
{
  art::FindManyP<T> ret(from, evt, tag);
  if (!tag.label().empty() && !ret.isValid())
  {
    std::cout << "CAFMaker: No Assn from '" << abi::__cxa_demangle(typeid(from).name(), 0, 0, 0) << "' to '"
              << abi::__cxa_demangle(typeid(T).name(), 0, 0, 0)
              << "' found under label '" << tag << "'. "
              << "Set 'StrictMode: false' to continue anyway." << std::endl;
    abort();
  }
  return ret;
}
//......................................................................

DEFINE_ART_MODULE(VertexEnergy)
