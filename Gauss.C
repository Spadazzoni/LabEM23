#include <fstream>

#include "TCanvas.h"
#include "TH2F.h"

void Gauss() {
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 800, 600);
  TH2F *h =
      new TH2F("h", "Scatter Plot A vs #nu", 50, 499.93, 499.9535, 200, 2.1678, 2.1685);
  Float_t x, y;
  std::ifstream in;
  in.open("IncertezzaCasualeAvsF.txt");
  while (1) {
    in >> x >> y;
    if (!in.good()) {
      break;
    }
    h->Fill(x, y);
  }
  /*h->SetMarkerStyle(8);
  h->Draw();*/
}