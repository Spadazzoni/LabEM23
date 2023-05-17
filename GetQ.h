#include "TF1.h"

double GetQErr(Double_t r, Double_t l, Double_t c, Double_t dr, Double_t dl,
               Double_t dc) {
  return sqrt((c / l) * dr * dr + 0.25 * r * r * dc * dc * (1 / (l * c)) +
              0.25 * dl * dl * r * r * c / (l * l * l));
}

Double_t GetF0Err(Double_t l, Double_t c, Double_t dl, Double_t dc) {
  return (1 / (2 * M_PI * sqrt(l * c))) *
         sqrt((dl * dl) / (l * l) + (dc * dc) / (c * c));
}