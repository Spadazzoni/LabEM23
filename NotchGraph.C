#include "Amp.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH1.h"
#include "TString.h"

void Graph() {
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 1000, 600);
  TString s[5] = {"R150", "R330", "R560", "R1200", "R2200"};
  Double_t R[5] = {150, 330, 560, 1200, 2200};
  EColor col[5] = {kGreen, kBlue, kPink, kRed, kYellow};
  TGraph *g[5];
  TF1 *f[5];
  for (int i = 0; i < 5; ++i) {
    g[i] = new TGraph(s[i] + ".txt", "%lg%lg");
    f[i] = new TF1("f" + s[i], AmplitudeR, 0, 24000, 4);
    f[i]->SetParameters(2.5, R[i], 1.005e-3, 159.6e-9);
    f[i]->SetLineColor(col[i]);
    if (i == 0) {
      TH1 *h = g[i]->GetHistogram();
      h->GetYaxis()->SetRangeUser(0, 2.5);
      h->SetTitle("Nascondi Banda su #nu_{0}");
      g[i]->Fit(f[i], "QS0");
      g[i]->Draw();
      f[i]->Draw("same");
    } else {
      g[i]->Fit(f[i], "QS0");
      g[i]->Draw("same");
      f[i]->Draw("same");
    }
  }
}