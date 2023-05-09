#include "Amp.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH1.h"
#include "TString.h"

void GraphLC() {
  TCanvas *c = new TCanvas("c", "MyCanvas", 200, 200, 1000, 600);
  TString s[5] = {"M150", "M330", "M560", "M1200", "M2200"};
  Double_t R[5] = {150, 330, 560, 1200, 2200};
  EColor col[5] = {kGreen, kBlue, kPink, kRed, kYellow};
  TGraph *g[5];
  TF1 *f[5];
  for (int i = 0; i < 5; ++i) {
    g[i] = new TGraph(s[i] + ".txt", "%lg%lg");
    f[i] = new TF1("f" + s[i], AmplitudeLC, 4000, 20000, 4);
    f[i]->SetParameters(2.5, R[i], 1.005e-3, 159.6e-9);
    f[i]->SetLineColor(col[i]);
    if (i == 0) {
      TH1 *h = g[i]->GetHistogram();
      h->GetYaxis()->SetRangeUser(0, 2);
      h->GetXaxis()->SetRangeUser(4000, 20000);
      h->SetTitle("Passa banda su #nu_{0}");
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