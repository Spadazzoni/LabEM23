#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH1.h"
#include "TStyle.h"

Double_t AmplitudeRV2(Double_t *x, Double_t *par) {
  // par[0] = V0, par[1] = R, par[2] = L, par[3] = C, par[4] = r_l, par[5] = r_i
  Float_t xx = x[0] * 2 * M_PI;
  return par[0] *
         sqrt(pow(par[1] * par[4] * par[3] * xx * xx *
                          ((par[1] + par[5]) * par[4] * par[3] + par[2]) +
                      par[1] * (par[2] * par[3] * pow(xx, 2) - 1) *
                          (par[2] * par[3] * pow(xx, 2) - 1 - par[4]),
                  2) +
              pow(par[1] * xx * (par[2] * par[3] * pow(xx, 2) - 1) *
                          ((par[1] + par[5]) * par[4] * par[3] + par[2]) -
                      par[1] * par[4] * par[3] * xx *
                          (par[2] * par[3] * pow(xx, 2) - 1 - par[4]),
                  2)) /
         (pow(xx, 2) * pow((par[1] + par[5]) * par[4] * par[3] + par[2], 2) +
          pow(par[2] * par[3] * pow(xx, 2) - 1 - par[4], 2));
}

void FitR(Double_t V0, Double_t R, Double_t L, Double_t C, Double_t r_l,
          Double_t r_i) {
  gStyle->SetOptFit(1111);
  TCanvas *c = new TCanvas("c", "myCanvas", 200, 200, 1000, 600);
  TGraph *g = new TGraph("NotchData.txt", "%lg%lg");
  TF1 *f = new TF1("f", AmplitudeRV2, 2400.04, 23000.1, 4);
  g->SetMarkerStyle(25);
  f->SetParameters(V0, R, L, C, r_l, r_i);
  g->Fit(f, "S0");
  g->Draw("AP");
  f->Draw("same");
}

void Draw(Double_t V0, Double_t R, Double_t L, Double_t C, Double_t r_l,
          Double_t r_i) {
  TCanvas *c = new TCanvas("c", "myCanvas", 200, 200, 1000, 600);
  TF1 *f = new TF1("f", AmplitudeRV2, 2400.04, 23000.1, 4);
  f->SetParameters(V0, R, L, C, r_l, r_i);
  f->Draw();
}