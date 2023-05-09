#include "TF1.h"

Double_t FitR(Double_t *x, Double_t *par) {
  Float_t xx = 2 * M_PI * x[0];
  Float_t v = par[0];
  Float_t r = par[1];
  Float_t l = par[2];
  Float_t c = par[3];
  return v * v * (r * r * (l * c * xx * xx - 1) * (l * c * xx * xx - 1)) /
         (r * r * (l * c * xx * xx - 1) * (l * c * xx * xx - 1) +
          l * l * xx * xx);
}