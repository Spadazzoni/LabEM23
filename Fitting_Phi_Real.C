#include <iostream>

#include "Phase.h"
#include "TCanvas.h"
#include "TGraph.h"

void Fit() {
  TString s;
  Float_t r;
  std::cin >> s >> r;
  TCanvas *c = new TCanvas("c", "myCanvas", 200, 200, 1000, 600);
  TGraph *g = new TGraph("F" + s + ".txt", "%lg%lg");
  g->SetMarkerStyle(25);
  TF1 *f = new TF1("f", Real_PhaseR, 4e3, 20e3, 5);
  f->SetParameters(2.5, r, 10.16e-3, 10.15e-9, 37.41, 50);
  g->Fit("f", "s0");
  g->Draw("ap");
  f->Draw("same");
}

