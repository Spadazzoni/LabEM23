#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH1.h"
#include "TStyle.h"
#include "Amp.h"

void NotchGraphR(Double_t V0, Double_t R, Double_t L, Double_t C) {
  // gStyle->SetOptFit(1111);
  TCanvas *c = new TCanvas("c", "myCanvas", 200, 200, 1000,
                           600);  // cambiando R non cambia il fit (?)
  TGraph *g = new TGraph("NotchData.txt", "%lg%lg");
  TF1 *f = new TF1("f", AmplitudeR, 2400.04, 23000.1, 4);
  g->SetMarkerStyle(25);
  f->SetParameters(V0, R, L, C);
  TH1 *h = g->GetHistogram();
  h->GetYaxis()->SetRangeUser(0, 5);
  g->Fit(f, "S0");
  g->Draw("AP");
  f->Draw("same");
}