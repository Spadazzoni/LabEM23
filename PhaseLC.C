#include "Phase.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1.h"
#include "TRandom.h"

void Rndm_PhaseLC(Double_t R, Double_t L, Double_t C) {
  gRandom->SetSeed();
  TF1 *f = new TF1("f", PhaseLC, 4000, 20000, 4);
  f->SetParameters(R, L, C);
  TCanvas *c = new TCanvas("c", "myCanvas", 200, 200, 1000, 600);
  TGraph *g = new TGraph(300);
  g->SetMarkerStyle(25);
  for (int i = 0; i < 300; ++i) {
    Double_t x = gRandom->Uniform(4000, 20000);
    g->SetPoint(i, x, f->Eval(x));
  }
  TH1 *h = g->GetHistogram();
  h->GetYaxis()->SetRangeUser(-2, 2);
  g->Fit(f, "S0");
  g->Draw("AP");
  f->Draw("same");
}