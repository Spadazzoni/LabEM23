#include <fstream>

#include "Amp.h"
#include "GetQ.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"

void DataAnalysis2() {
  // creating functions and graphs
  const Double_t w0 = 1 / (2 * M_PI * sqrt(10.16e-3 * 10.15e-9));
  const Double_t dw0 =
      (1 / (2 * M_PI * sqrt(10.16e-3 * 10.15e-9))) *
      sqrt((10.16e-3 * 0.01 * 10.16e-3 * 0.01) / (10.16e-3 * 10.16e-3) +
           (10.15e-9 * 0.01 * 10.15e-9 * 0.01) / (10.15e-9 * 10.15e-9));
  TString f = "f";
  TString H = "H_{R}";
  TString name[5] = {"150", "330", "560", "1200", "2200"};
  Double_t R[5] = {150.95, 328.98, 560.1, 1.979e3, 2194.8};
  Double_t dR[5] = {1.15095e-3, 1.32898e-3, 1.5601e-3, 0.011979, 0.012948};
  TGraphErrors *gtotR[5];
  TGraphErrors *gtotM[5];
  TF1 *ftotR[5];
  TF1 *ftotM[5];
  for (int i = 0; i < 5; ++i) {
    gtotR[i] = new TGraphErrors("ER" + name[i] + ".txt", "%lg%lg%lg%lg");
    gtotR[i]->SetMarkerStyle(25);
    ftotR[i] = new TF1(f + i, Real_AmplitudeR, 2.7e3, 30e3, 6);
    ftotR[i]->SetParameters(2.5, R[i], 10.16e-3, 10.15e-9, 37.41, 50);
    ftotR[i]->SetLineColor(kOrange + 10);
  }
  for (int i = 0; i < 5; ++i) {
    gtotM[i] = new TGraphErrors("EM" + name[i] + ".txt", "%lg%lg%lg%lg");
    gtotM[i]->SetMarkerStyle(25);
    ftotM[i] = new TF1(f + i, Real_Amplitude_LC, 2.7e3, 30e3, 6);
    ftotM[i]->SetParameters(2.5, R[i], 10.16e-3, 10.15e-9, 37.41, 50);
    ftotM[i]->SetLineColor(kOrange + 10);
  }
  // fitting
  for (int i = 0; i < 5; ++i) {
    gtotR[i]->Fit(ftotR[i], "qs0");
  }
  for (int i = 0; i < 5; ++i) {
    gtotM[i]->Fit(ftotM[i], "qs0");
  }
  // measuring Q
  TF1 *H_R[5];
  for (int i = 0; i < 5; ++i) {
    H_R[i] = new TF1(H + i, Real_H_R, -10e10, 10e10, 5);
    H_R[i]->SetParameters(ftotR[i]->GetParameter(1), ftotR[i]->GetParameter(2),
                          ftotR[i]->GetParameter(3), ftotR[i]->GetParameter(4),
                          ftotR[i]->GetParameter(5));
  }
  Double_t w1R[5];
  Double_t w2R[5];
  Double_t QR  [5];
  for (int i = 0; i < 5; ++i) {
    w1R[i] = H_R[i]->GetX(1 / sqrt(2), -10e10, w0);
    w2R[i] = H_R[i]->GetX(1 / sqrt(2), w0, 10e10);
    QR  [i] = w0 / (w2R[i] - w1R[i]);
  }
  // measuring f0
  Double_t f0_minR[5];   // calculated as the min x of the fit func (R)
  Double_t f0_fitR[5];   // calculated from the fit parameters (R)
  Double_t df0_fitR[0];  // error on f0 from fit parameters (R)
  Double_t f0_minM[5];   // calculated as the min x of the fit func (M)
  Double_t f0_fitM[5];   // calculated from the fit parameters (M)
  Double_t df0_fitM[0];  // error on f0 from fit parameters (M)
  for (int i = 0; i < 5; ++i) {
    f0_minR[i] = ftotR[i]->GetMinimumX();
    f0_fitR[i] =
        1 / (2 * M_PI *
             sqrt(ftotR[i]->GetParameter(2) * ftotR[i]->GetParameter(3)));
    df0_fitR[i] = GetF0Err(ftotR[i]->GetParameter(2), ftotR[i]->GetParameter(3),
                           ftotR[i]->GetParError(2), ftotR[i]->GetParError(3));
  }
  for (int i = 0; i < 5; ++i) {
    f0_minM[i] = ftotM[i]->GetMaximumX();
    f0_fitM[i] =
        1 / (2 * M_PI *
             sqrt(ftotM[i]->GetParameter(2) * ftotM[i]->GetParameter(3)));
    df0_fitM[i] = GetF0Err(ftotM[i]->GetParameter(2), ftotM[i]->GetParameter(3),
                           ftotM[i]->GetParError(2), ftotM[i]->GetParError(3));
  }
  // saving data
  std::ofstream txt("./Data2.txt", std::ofstream::out);
  if (txt.is_open()) {
    txt << "============================" << '\n';
    txt << "||  RISULTATI SPERIMENTALI ||" << '\n';
    txt << "============================" << '\n';
    txt << '\n';
    txt << '\n';
    txt << "==> Confronto tra Q misurato e Q stimato" << '\n';
    for (int i = 0; i < 5; ++i) {
      txt << "Misurato"
          << " (" << name[i] << "R):  " << QR  [i]
          << "  ||  Stimato:  " << R[i] * sqrt(10.15e-9 / 10.16e-3) << "  +/-  "
          << GetQErr(R[i], 10.16e-3, 10.15e-9, dR[i], (10.16e-3) * (0.01),
                     (10.15e-9) * (0.01))
          << '\n';
    }
    txt << '\n';
    txt << '\n';
    txt << "==> Misura e Confronto tra frequenze di risonanza misurate (R)"
        << '\n';
    txt << "====> Valore Atteso:  " << w0 << "  +/-  " << dw0 << "  Hz" << '\n';
    for (int i = 0; i < 5; ++i) {
      txt << "- R" << name[i] << ":  " << '\n';
      txt << "Valore Stimato come Minimo del Fit:  " << f0_minR[i] << "  +/- "
          << "???"
          << "  Hz" << '\n';
      txt << "Valore Stimato dai Parametri del Fit:  " << f0_fitR[i] << "  +/- "
          << df0_fitR[i] << "  Hz" << '\n';
      txt << '\n';
    }
    txt << '\n';
    txt << '\n';
    txt << "==> Misura e Confronto tra frequenze di risonanza misurate (M)"
        << '\n';
    txt << "====> Valore Atteso:  " << w0 << "  +/-  " << dw0 << "  Hz" << '\n';
    for (int i = 0; i < 5; ++i) {
      txt << "- M" << name[i] << ":  " << '\n';
      txt << "Valore Stimato come Massimo del Fit:  " << f0_minM[i] << "  +/- "
          << "???"
          << "  Hz" << '\n';
      txt << "Valore Stimato dai Parametri del Fit:  " << f0_fitM[i] << "  +/- "
          << df0_fitM[i] << "  Hz" << '\n';
      txt << '\n';
    }
    txt << '\n';
    txt << '\n';
    txt << "==> Risultati Fit (R)" << '\n';
    for (int i = 0; i < 5; ++i) {
      txt << "- R" << name[i] << ":  " << '\n';
      txt << "Ampiezza V0:  " << ftotR[i]->GetParameter(0) << "  +/-  "
          << ftotR[i]->GetParError(0) << "  V" << '\n';
      txt << "Resistenza R:  " << ftotR[i]->GetParameter(1) << "  +/-  "
          << ftotR[i]->GetParError(1) << "  ohm" << '\n';
      txt << "Induttanza L:  " << ftotR[i]->GetParameter(2) << "  +/-  "
          << ftotR[i]->GetParError(2) << "  H" << '\n';
      txt << "Capacità C:  " << ftotR[i]->GetParameter(3) << "  +/-  "
          << ftotR[i]->GetParError(3) << "  F" << '\n';
      txt << "Resistenza Induttore Rl:  " << ftotR[i]->GetParameter(4)
          << "  +/-  " << ftotR[i]->GetParError(4) << "  ohm" << '\n';
      txt << "Resistenza Generatore Rv:  " << ftotR[i]->GetParameter(5)
          << "  +/-  " << ftotR[i]->GetParError(5) << "  ohm" << '\n';
      txt << "Chi quadro e NDF:  " << ftotR[i]->GetChisquare() << "  ,  "
          << ftotR[i]->GetNDF() << '\n';
      txt << "Chi quadro ridotto:  "
          << ftotR[i]->GetChisquare() / ftotR[i]->GetNDF() << '\n';
      txt << '\n';
    }
    txt << '\n';
    txt << '\n';
    txt << "==> Risultati Fit (M)" << '\n';
    for (int i = 0; i < 5; ++i) {
      txt << "- M" << name[i] << ":  " << '\n';
      txt << "Ampiezza V0:  " << ftotM[i]->GetParameter(0) << "  +/-  "
          << ftotM[i]->GetParError(0) << "  V" << '\n';
      txt << "Resistenza R:  " << ftotM[i]->GetParameter(1) << "  +/-  "
          << ftotM[i]->GetParError(1) << "  ohm" << '\n';
      txt << "Induttanza L:  " << ftotM[i]->GetParameter(2) << "  +/-  "
          << ftotM[i]->GetParError(2) << "  H" << '\n';
      txt << "Capacità C:  " << ftotM[i]->GetParameter(3) << "  +/-  "
          << ftotM[i]->GetParError(3) << "  F" << '\n';
      txt << "Resistenza Induttore Rl:  " << ftotM[i]->GetParameter(4)
          << "  +/-  " << ftotM[i]->GetParError(4) << "  ohm" << '\n';
      txt << "Resistenza Generatore Rv:  " << ftotM[i]->GetParameter(5)
          << "  +/-  " << ftotM[i]->GetParError(5) << "  ohm" << '\n';
      txt << "Chi quadro e NDF:  " << ftotM[i]->GetChisquare() << "  ,  "
          << ftotM[i]->GetNDF() << '\n';
      txt << "Chi quadro ridotto:  "
          << ftotM[i]->GetChisquare() / ftotM[i]->GetNDF() << '\n';
      txt << '\n';
    }
    txt.close();
  } else {
    std::cout << "Cannot Open File..." << '\n';
  }
}
