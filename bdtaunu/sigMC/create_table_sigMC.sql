CREATE TABLE event (
  eid                         bigserial PRIMARY KEY,
  run                         int,
  mode_label                  int,
  runNumber                   int,
  platform                    int,
  partition                   int,
  upperID                     int,
  lowerID                     int,
  majorID                     int,
  configKey                   int,
  ddate                       int,
  eePx                        real,
  eePy                        real,
  eePz                        real,
  eeE                         real,
  beamSX                      real,
  beamSY                      real,
  beamSZ                      real,
  beamSCovXX                  real,
  beamSCovYY                  real,
  beamSCovZZ                  real,
  beamSCovXZ                  real,
  EventWeight                 real,
  NNeutrals                   int,
  Npi0                        int,
  EventLabel                  int,
  nTracks                     int,
  nGoodTrkLoose               int,
  R2All                       real,
  R2                          real,
  mcLen                       int,
  mcLund                      int[],
  mothIdx                     int[],
  dauLen                      int[],
  dauIdx                      int[],
  mcmass                      real[],
  mcp3CM                      real[],
  mccosthCM                   real[],
  mcphiCM                     real[],
  mcenergyCM                  real[],
  mcp3                        real[],
  mccosth                     real[],
  mcphi                       real[],
  mcenergy                    real[],
  mcVtxx                      real[],
  mcVtxy                      real[],
  mcVtxz                      real[],
  nY                          int,
  YBPairCosThetaPmissCM       real[],
  YBPairCosThetaT             real[],
  YBPairCostauh_neg           real[],
  YBPairCostauh_pos           real[],
  YBPairCostauh_zero          real[],
  YBPairDiffBY                real[],
  YBPairEextra50              real[],
  YBPairM2min                 real[],
  YBPairM3min                 real[],
  YBPairMmiss2                real[],
  YBPairMmissPrime2           real[],
  YBPairq2_neg                real[],
  YBPairq2_pos                real[],
  YBPairq2_zero               real[],
  YChi2                       real[],
  YMass                       real[],
  YMassErr                    real[],
  YSigBCosBY                  real[],
  YSigBCosThetaDSoftCM        real[],
  YSigBCosThetaDtauCM         real[],
  YSigBDMass                  real[],
  YSigBDstarDeltaM            real[],
  YSigBVtxProbB               real[],
  YSigBVtxProbh               real[],
  YSigBhMass                  real[],
  YSigBhP3MagCM               real[],
  YSigBsoftP3MagCM            real[],
  YTagBCosBY                  real[],
  YTagBCosThetaDSoftCM        real[],
  YTagBCosThetaDlCM           real[],
  YTagBDMass                  real[],
  YTagBDstarDeltaM            real[],
  YTagBVtxProbB               real[],
  YTagBlP3MagCM               real[],
  YTagBsoftP3MagCM            real[],
  YVtxx                       real[],
  YVtxy                       real[],
  YVtxz                       real[],
  Ycosth                      real[],
  YcosthCM                    real[],
  Yenergy                     real[],
  YenergyCM                   real[],
  Yp3                         real[],
  Yp3CM                       real[],
  Yphi                        real[],
  YphiCM                      real[],
  YLund                       int[],
  YMCIdx                      int[],
  YVtxStatus                  int[],
  YnDaus                      int[],
  YnDof                       int[],
  Yd1Lund                     int[],
  Yd1Idx                      int[],
  Yd2Lund                     int[],
  Yd2Idx                      int[],
  nB                          int,
  BChi2                       real[],
  BMass                       real[],
  BMassErr                    real[],
  BVtxx                       real[],
  BVtxy                       real[],
  BVtxz                       real[],
  Bcosth                      real[],
  BcosthCM                    real[],
  Benergy                     real[],
  BenergyCM                   real[],
  Bp3                         real[],
  Bp3CM                       real[],
  Bphi                        real[],
  BphiCM                      real[],
  BLund                       int[],
  BMCIdx                      int[],
  BVtxStatus                  int[],
  BnDaus                      int[],
  BnDof                       int[],
  Bd1Lund                     int[],
  Bd1Idx                      int[],
  Bd2Lund                     int[],
  Bd2Idx                      int[],
  Bd3Lund                     int[],
  Bd3Idx                      int[],
  Bd4Lund                     int[],
  Bd4Idx                      int[],
  nD                          int,
  DChi2                       real[],
  DDoca                       real[],
  DDocaErr                    real[],
  DDocaXY_xy                  real[],
  DDocaXY_xyErr               real[],
  DDocaXY_z                   real[],
  DDocaXY_zErr                real[],
  DDoca_z                     real[],
  DDoca_zErr                  real[],
  DMass                       real[],
  DMassErr                    real[],
  DPocaXY_cxx                 real[],
  DPocaXY_cxy                 real[],
  DPocaXY_cyy                 real[],
  DPocaXY_cyz                 real[],
  DPocaXY_czx                 real[],
  DPocaXY_czz                 real[],
  DPocaXY_x                   real[],
  DPocaXY_xErr                real[],
  DPocaXY_y                   real[],
  DPocaXY_yErr                real[],
  DPocaXY_z                   real[],
  DPocaXY_zErr                real[],
  DPoca_cxx                   real[],
  DPoca_cxy                   real[],
  DPoca_cyy                   real[],
  DPoca_cyz                   real[],
  DPoca_czx                   real[],
  DPoca_czz                   real[],
  DPoca_x                     real[],
  DPoca_xErr                  real[],
  DPoca_y                     real[],
  DPoca_yErr                  real[],
  DPoca_z                     real[],
  DPoca_zErr                  real[],
  DVtxx                       real[],
  DVtxy                       real[],
  DVtxz                       real[],
  Dcosth                      real[],
  DcosthCM                    real[],
  Denergy                     real[],
  DenergyCM                   real[],
  Dp3                         real[],
  Dp3CM                       real[],
  Dphi                        real[],
  DphiCM                      real[],
  DLund                       int[],
  DMCIdx                      int[],
  DVtxStatus                  int[],
  DnDaus                      int[],
  DnDof                       int[],
  Dd1Lund                     int[],
  Dd1Idx                      int[],
  Dd2Lund                     int[],
  Dd2Idx                      int[],
  Dd3Lund                     int[],
  Dd3Idx                      int[],
  Dd4Lund                     int[],
  Dd4Idx                      int[],
  Dd5Lund                     int[],
  Dd5Idx                      int[],
  nC                          int,
  CChi2                       real[],
  CDoca                       real[],
  CDocaErr                    real[],
  CDocaXY_xy                  real[],
  CDocaXY_xyErr               real[],
  CDocaXY_z                   real[],
  CDocaXY_zErr                real[],
  CDoca_z                     real[],
  CDoca_zErr                  real[],
  CMass                       real[],
  CMassErr                    real[],
  CPocaXY_cxx                 real[],
  CPocaXY_cxy                 real[],
  CPocaXY_cyy                 real[],
  CPocaXY_cyz                 real[],
  CPocaXY_czx                 real[],
  CPocaXY_czz                 real[],
  CPocaXY_x                   real[],
  CPocaXY_xErr                real[],
  CPocaXY_y                   real[],
  CPocaXY_yErr                real[],
  CPocaXY_z                   real[],
  CPocaXY_zErr                real[],
  CPoca_cxx                   real[],
  CPoca_cxy                   real[],
  CPoca_cyy                   real[],
  CPoca_cyz                   real[],
  CPoca_czx                   real[],
  CPoca_czz                   real[],
  CPoca_x                     real[],
  CPoca_xErr                  real[],
  CPoca_y                     real[],
  CPoca_yErr                  real[],
  CPoca_z                     real[],
  CPoca_zErr                  real[],
  CVtxx                       real[],
  CVtxy                       real[],
  CVtxz                       real[],
  Ccosth                      real[],
  CcosthCM                    real[],
  Cenergy                     real[],
  CenergyCM                   real[],
  Cp3                         real[],
  Cp3CM                       real[],
  Cphi                        real[],
  CphiCM                      real[],
  CLund                       int[],
  CMCIdx                      int[],
  CVtxStatus                  int[],
  CnDaus                      int[],
  CnDof                       int[],
  Cd1Lund                     int[],
  Cd1Idx                      int[],
  Cd2Lund                     int[],
  Cd2Idx                      int[],
  nh                          int,
  hChi2                       real[],
  hDoca                       real[],
  hDocaErr                    real[],
  hDocaXY_xy                  real[],
  hDocaXY_xyErr               real[],
  hDocaXY_z                   real[],
  hDocaXY_zErr                real[],
  hDoca_z                     real[],
  hDoca_zErr                  real[],
  hKKMSuperLoose_w            real[],
  hKKMSuperLoose_werr         real[],
  hKKMTight_w                 real[],
  hKKMTight_werr              real[],
  hMass                       real[],
  hMassErr                    real[],
  hPocaXY_cxx                 real[],
  hPocaXY_cxy                 real[],
  hPocaXY_cyy                 real[],
  hPocaXY_cyz                 real[],
  hPocaXY_czx                 real[],
  hPocaXY_czz                 real[],
  hPocaXY_x                   real[],
  hPocaXY_xErr                real[],
  hPocaXY_y                   real[],
  hPocaXY_yErr                real[],
  hPocaXY_z                   real[],
  hPocaXY_zErr                real[],
  hPoca_cxx                   real[],
  hPoca_cxy                   real[],
  hPoca_cyy                   real[],
  hPoca_cyz                   real[],
  hPoca_czx                   real[],
  hPoca_czz                   real[],
  hPoca_x                     real[],
  hPoca_xErr                  real[],
  hPoca_y                     real[],
  hPoca_yErr                  real[],
  hPoca_z                     real[],
  hPoca_zErr                  real[],
  hVtxx                       real[],
  hVtxy                       real[],
  hVtxz                       real[],
  hcosth                      real[],
  hcosthCM                    real[],
  henergy                     real[],
  henergyCM                   real[],
  hp3                         real[],
  hp3CM                       real[],
  hphi                        real[],
  hphiCM                      real[],
  hpiKMVeryLoose_w            real[],
  hpiKMVeryLoose_werr         real[],
  hKKMSuperLoose_stat         int[],
  hKKMTight_stat              int[],
  hLund                       int[],
  hMCIdx                      int[],
  hVtxStatus                  int[],
  hnDaus                      int[],
  hnDof                       int[],
  hpiKMVeryLoose_stat         int[],
  hd1Lund                     int[],
  hd1Idx                      int[],
  hd2Lund                     int[],
  hd2Idx                      int[],
  hTrkIdx                     int[],
  nl                          int,
  lChi2                       real[],
  lDoca                       real[],
  lDocaErr                    real[],
  lDocaXY_xy                  real[],
  lDocaXY_xyErr               real[],
  lDocaXY_z                   real[],
  lDocaXY_zErr                real[],
  lDoca_z                     real[],
  lDoca_zErr                  real[],
  lLooseKMElectronMicro_w     real[],
  lLooseKMElectronMicro_werr  real[],
  lMass                       real[],
  lMassErr                    real[],
  lPocaXY_cxx                 real[],
  lPocaXY_cxy                 real[],
  lPocaXY_cyy                 real[],
  lPocaXY_cyz                 real[],
  lPocaXY_czx                 real[],
  lPocaXY_czz                 real[],
  lPocaXY_x                   real[],
  lPocaXY_xErr                real[],
  lPocaXY_y                   real[],
  lPocaXY_yErr                real[],
  lPocaXY_z                   real[],
  lPocaXY_zErr                real[],
  lPoca_cxx                   real[],
  lPoca_cxy                   real[],
  lPoca_cyy                   real[],
  lPoca_cyz                   real[],
  lPoca_czx                   real[],
  lPoca_czz                   real[],
  lPoca_x                     real[],
  lPoca_xErr                  real[],
  lPoca_y                     real[],
  lPoca_yErr                  real[],
  lPoca_z                     real[],
  lPoca_zErr                  real[],
  lTightKMElectronMicro_w     real[],
  lTightKMElectronMicro_werr  real[],
  lVtxx                       real[],
  lVtxy                       real[],
  lVtxz                       real[],
  lcosth                      real[],
  lcosthCM                    real[],
  lenergy                     real[],
  lenergyCM                   real[],
  lmuBDTLooseFakeRate_w       real[],
  lmuBDTLooseFakeRate_werr    real[],
  lmuBDTTightFakeRate_w       real[],
  lmuBDTTightFakeRate_werr    real[],
  lp3                         real[],
  lp3CM                       real[],
  lphi                        real[],
  lphiCM                      real[],
  lLooseKMElectronMicro_stat  int[],
  lLund                       int[],
  lMCIdx                      int[],
  lTightKMElectronMicro_stat  int[],
  lVtxStatus                  int[],
  lmuBDTLooseFakeRate_stat    int[],
  lmuBDTTightFakeRate_stat    int[],
  lnDaus                      int[],
  lnDof                       int[],
  ld1Lund                     int[],
  ld1Idx                      int[],
  ld2Lund                     int[],
  ld2Idx                      int[],
  ld3Lund                     int[],
  ld3Idx                      int[],
  lTrkIdx                     int[],
  ngamma                      int,
  gammaMass                   real[],
  gammaMassErr                real[],
  gammacosth                  real[],
  gammacosthCM                real[],
  gammaenergy                 real[],
  gammaenergyCM               real[],
  gammap3                     real[],
  gammap3CM                   real[],
  gammaphi                    real[],
  gammaphiCM                  real[],
  gammaLund                   int[],
  gammaMCIdx                  int[],
  gammanDaus                  int[],
  nTRK                        int,
  TRKLund                     int[],
  TRKnHitXY                   int[],
  TRKnHitZ                    int[],
  TRKnSvtXY                   int[],
  TRKnSvtZ                    int[],
  TRKnDchXY                   int[],
  TRKnDchZ                    int[],
  TRKdchFirst                 int[],
  TRKdchLast                  int[],
  TRKEff                      real[],
  TRKEfferr                   real[],
  TRKchEff                    real[],
  TRKchEfferr                 real[],
  KSelectorsMap               int[],
  eSelectorsMap               int[],
  muSelectorsMap              int[],
  piSelectorsMap              int[],
  pSelectorsMap               int[],
  TRKDrcTh                    real[],
  TRKDrcThErr                 real[],
  TRKDrcDeltaMom              real[],
  TRKDrcNph                   int[],
  TRKDrcNbgph                 int[],
  TRKdedxdch                  real[],
  TRKdedxdchsamp              int[],
  TRKDchDeltaMom              real[],
  gammaLat                    real[],
  gammaA42                    real[],
  gammaECal                   real[],
  gammaErawCal                real[],
  gammaCentx                  real[],
  gammaCenty                  real[],
  gammaCentz                  real[],
  gammanCrys                  int[]
);
