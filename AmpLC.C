#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH1.h"
#include "TStyle.h"
#include "Amp.h"

void NotchGraphLC(Double_t V0, Double_t R, Double_t L, Double_t C) {
  gStyle->SetOptFit(1111);
  TCanvas *c = new TCanvas("c", "myCanvas", 200, 200, 1000, 600);
  TGraph *g = new TGraph("MagliaData.txt", "%lg%lg");
  TF1 *f = new TF1("f", AmplitudeLC, 2400.03, 22700.2, 4);
  g->SetMarkerStyle(25);
  f->SetParameters(V0, R, L, C);
  g->Fit(f, "S0");
  g->Draw("AP");
  f->Draw("same");
}
