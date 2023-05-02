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