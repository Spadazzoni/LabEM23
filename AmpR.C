#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH1.h"
#include "TStyle.h"

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
             par[2] * par[2] * (xx * (2 * M_PI)) * (xx * (2 * M_PI)))
      ;
}

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