#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH1.h"

void Err() {
  TCanvas *c = new TCanvas("c", "myCanvas", 200, 200, 1000, 600);
  TGraph *g = new TGraph("ErrF.txt", "%lg%lg");
  g->SetMarkerStyle(25);
  TH1 *h = g->GetHistogram();
  h->GetYaxis()->SetRangeUser(160, 175);
  TF1 *f = new TF1("f", "[0]*x+[1]", 2700.12, 30000.1);
  g->Fit(f, "s0");
  g->Draw("ap");
  f->Draw("same");
}