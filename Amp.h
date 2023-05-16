#include "TF1.h"

Double_t AmplitudeR(Double_t *x, Double_t *par) {
  // par[0] = V0, par[1] = R, par[2] = L, par[3] = C
  Float_t xx = x[0];
  return par[0] *
         abs(par[1] *
             (par[2] * par[3] * (xx * (2 * M_PI)) * (xx * (2 * M_PI)) - 1)) /
         sqrt(
             par[1] * par[1] *
                 (par[2] * par[3] * (xx * (2 * M_PI)) * (xx * (2 * M_PI)) - 1) *
                 (par[2] * par[3] * (xx * (2 * M_PI)) * (xx * (2 * M_PI)) - 1) +
             par[2] * par[2] * (xx * (2 * M_PI)) * (xx * (2 * M_PI)));
}

Double_t AmplitudeLC(Double_t *x, Double_t *par) {
  // par[0] = V0, par[1] = R, par[2] = L, par[3] = C
  Float_t xx = x[0];
  return par[0] * par[2] * (xx * (2 * M_PI)) /
         sqrt(
             par[1] * par[1] *
                 (par[2] * par[3] * (xx * (2 * M_PI)) * (xx * (2 * M_PI)) - 1) *
                 (par[2] * par[3] * (xx * (2 * M_PI)) * (xx * (2 * M_PI)) - 1) +
             par[2] * par[2] * (xx * (2 * M_PI)) * (xx * (2 * M_PI)));
}

Double_t Real_AmplitudeR(Double_t *x, Double_t *par) {
  Float_t xx = x[0] * 2 * M_PI;
  Float_t v = par[0];
  Float_t r = par[1];
  Float_t l = par[2];
  Float_t c = par[3];
  Float_t rl = par[4];
  Float_t rv = par[5];
  return (r * v) /
         (sqrt(pow(r + rv +
                       rl / ((1 - xx * xx * l * c) * (1 - xx * xx * l * c) +
                             (rl * c * xx) * (rl * c * xx)),
                   2) +
               pow((l * xx * (1 - l * c * xx * xx) - rl * rl * c * xx) /
                       ((1 - xx * xx * l * c) * (1 - xx * xx * l * c) +
                        (rl * c * xx) * (rl * c * xx)),
                   2)));
}

Double_t Real_H_R(Double_t *x, Double_t *par) {
  Float_t xx = x[0] * 2 * M_PI;
  Float_t r = par[0];
  Float_t l = par[1];
  Float_t c = par[2];
  Float_t rl = par[3];
  Float_t rv = par[4];
  return (r) /
         (sqrt(pow(r + rv +
                       rl / ((1 - xx * xx * l * c) * (1 - xx * xx * l * c) +
                             (rl * c * xx) * (rl * c * xx)),
                   2) +
               pow((l * xx * (1 - l * c * xx * xx) - rl * rl * c * xx) /
                       ((1 - xx * xx * l * c) * (1 - xx * xx * l * c) +
                        (rl * c * xx) * (rl * c * xx)),
                   2)));
}

Double_t Real_AmplitudeLC(Double_t *x, Double_t *par) {
  Float_t xx = x[0] * 2 * M_PI;
  Float_t v = par[0];
  Float_t r = par[1];
  Float_t l = par[2];
  Float_t c = par[3];
  Float_t rl = par[4];
  Float_t rv = par[5];
  Float_t Den =
      pow((rl + (r + rv) * ((1 - xx * xx * l * c) * (1 - xx * xx * l * c) +
                            (rl * c * xx) * (rl * c * xx))),
          2) +
      pow(xx * l * (1 - xx * xx * l * c) - rl * rl * c * xx, 2);
  Float_t Num =
      sqrt(pow(rl * rl +
                   rl * (r + rv) *
                       ((1 - xx * xx * l * c) * (1 - xx * xx * l * c) +
                        (rl * c * xx) * (rl * c * xx)) +
                   pow(xx * l * (1 - xx * xx * l * c) - rl * rl * c * xx, 2),
               2) +
           pow(pow(xx * l * (1 - xx * xx * l * c) - rl * rl * c * xx, 2) *
                   pow(rl + (r + rv) *
                                ((1 - xx * xx * l * c) * (1 - xx * xx * l * c) +
                                 (rl * c * xx) * (rl * c * xx)),
                       2),
               2));
  return v * Num / Den;
}