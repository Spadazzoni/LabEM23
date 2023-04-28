#include "TCanvas.h"
#include "TGraph.h"
#include "TH1.h"
#include "TString.h"

void Graph() {
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 1000, 600);
  TString s[5] = {"R150", "R330", "R560", "R1200", "R2200"};
  TGraph *g[5];
  for (int i = 0; i < 5; ++i) {
    g[i] = new TGraph(s[i] + ".txt", "%lg%lg");
    g[i]->SetMarkerStyle(25);
    if (i == 0) {
      TH1 *h = g[i]->GetHistogram();
      h->GetYaxis()->SetRangeUser(0, 2.5);
      g[i]->Draw("AP");
    } else {
      g[i]->Draw("same,AP");
    }
  }
}