#include <fstream>

#include "FitR.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1.h"

void FitR() {
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 1000, 600);
  TGraph *g = new TGraph(); 
  g->SetMarkerStyle(25);
  TF1 *f = new TF1("f", FitR, 4000, 20000, 4);
  f->SetParameters(2.5, 1200, 1.005e-3, 159.6e-9);
  std::ifstream in;
  in.open("R1200.txt");
  Double_t x;
  Double_t y;
  int i = 0;
  while (1) {
    in >> x >> y;
    if (!in.good()) {
      break;
    }
    g->SetPoint(i, x, y * y);
    ++i;
  }
  in.close();
  TH1 *h = g->GetHistogram();
  h->GetYaxis()->SetRangeUser(0, f->GetMaximum() + 1);
  g->Fit(f, "S0");
  g->Draw("AP");
  f->Draw("same");
}