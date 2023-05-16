#include "TF1.h"

double GetQErr(Double_t r, Double_t l, Double_t c, Double_t dr, Double_t dl,
              Double_t dc) {
  return sqrt((c / l) * dr * dr + 0.25 * r * r * dc * dc * (1 / (l * c)) +
              0.25 * dl * dl * r * r * c / (l * l * l));
}