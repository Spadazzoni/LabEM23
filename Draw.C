#include "Amp.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TRandom.h"

void Draw() {
  gRandom->SetSeed();
  TCanvas *c = new TCanvas("c", "myCanvas", 200, 200, 1000, 600);
  TGraph *g = new TGraph();
  g->SetMarkerStyle(25);
  TF1 *f = new TF1("f", AmplitudeR, 10e3, 70e3, 4);
  f->SetParameters(2.5, 150, 1e-3, 15e-9);
  for (int i = 0; i < 150; ++i) {
    Double_t x = gRandom->Uniform(10e3, 70e3);
    Double_t err = gRandom->Gaus(0, 1e-1);
    Double_t y = f->Eval(x) + err;
    g->SetPoint(i, x, y);
  }
  g->Fit("f", "s0");
  g->Draw("AP");
  f->Draw("same");
}