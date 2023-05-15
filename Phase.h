#include "TF1.h"

Double_t PhaseR(Double_t *x, Double_t *par) {
  // par[0] = R, par[1] = L, par[2] = C
  Double_t xx = x[0] * 2 * M_PI;
  return atan((par[1] * xx) / (par[0] * (par[1] * par[2] * xx * xx - 1)));
}

Double_t PhaseLC(Double_t *x, Double_t *par) {
  // par[0] = R, par[1] = L, par[2] = C
  Double_t xx = x[0] * 2 * M_PI;
  return -atan((par[0] * (par[1] * par[2] * xx * xx - 1)) / (par[1] * xx));
}

Double_t Real_PhaseR(Double_t *x, Double_t *par) {
  Float_t xx = x[0] * 2 * M_PI;
  Float_t r = par[0];
  Float_t l = par[1];
  Float_t c = par[2];
  Float_t rl = par[3];
  Float_t rv = par[4];
  return -TMath::ATan(
      ((l * xx * (1 - l * c * xx * xx) - rl * rl * c * xx)) /
      (rl + (r + rv) * (pow(1 - l * c * xx * xx, 2) + pow(rl * c * xx, 2))));
}
