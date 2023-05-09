#include "Amp.h"
#include "TCanvas.h"
#include "TGraph.h"

void Fit() {
  TCanvas *c = new TCanvas("c", "myCanvas", 200, 200, 1000, 600);
  TGraph *g = new TGraph("R2200.txt", "%lg%lg");
  g->SetMarkerStyle(25);
  TF1 *f = new TF1("f", Real_AmplitudeR, 4e3, 20e3, 5);
  f->SetParameters(2.5, 2200, 1.005e-3, 159.6e-9, 14, 50);
  g->Fit("f", "s0");
  g->Draw("ap");
  f->Draw("same");
}