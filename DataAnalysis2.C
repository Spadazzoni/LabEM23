#include "Amp.h"
#include "GetQ.h"
#include "TF1.h"
#include "TGraph.h"

void DataAnalysis2() {
  // creating functions and graphs
  const Double_t w0 = 1 / (2 * M_PI * sqrt(10.16e-3 * 10.15e-9));
  TString f = "f";
  TString H = "H_{R}";
  TString name[5] = {"150", "330", "560", "1200", "2200"};
  Double_t R[5] = {150.95, 328.98, 560.1, 1.979e3, 2194.8};
  Double_t dR[5] = {1.15095e-3, 1.32898e-3, 1.5601e-3, 0.011979, 0.012948};
  TGraph *gtot[5];
  TF1 *ftot[5];
  for (int i = 0; i < 5; ++i) {
    gtot[i] = new TGraph("R" + name[i] + ".txt", "%lg%lg");
    gtot[i]->SetMarkerStyle(25);
    ftot[i] = new TF1(f + i, Real_AmplitudeR, 2.7e3, 30e3, 6);
    ftot[i]->SetParameters(2.5, R[i], 10.16e-3, 10.15e-9, 37.41, 50);
    ftot[i]->SetLineColor(kOrange + 10);
  }
  // fitting
  for (int i = 0; i < 5; ++i) {
    gtot[i]->Fit(ftot[i], "qs0");
  }
  // measuring Q
  TF1 *H_R[5];
  for (int i = 0; i < 5; ++i) {
    H_R[i] = new TF1(H + i, Real_H_R, -10e10, 10e10, 5);
    H_R[i]->SetParameters(ftot[i]->GetParameter(1), ftot[i]->GetParameter(2),
                          ftot[i]->GetParameter(3), ftot[i]->GetParameter(4),
                          ftot[i]->GetParameter(5));
  }
  Double_t w1[5];
  Double_t w2[5];
  Double_t Q[5];
  for (int i = 0; i < 5; ++i) {
    w1[i] = H_R[i]->GetX(1 / sqrt(2), -10e10, w0);
    w2[i] = H_R[i]->GetX(1 / sqrt(2), w0, 10e10);
    Q[i] = w0 / (w2[i] - w1[i]);
    std::cout << Q[i] << "  vs  " << R[i] * sqrt(10.15e-9 / 10.16e-3)
              << "  +/-  "
              << GetQErr(R[i], 10.16e-3, 10.15e-9, dR[i], (10.16e-3) * (0.01),
                         (10.15e-9) * (0.01))
              << '\n'; //dividendo il Q analitico per 2.5 si ottengono risultati compatibili
  }
}