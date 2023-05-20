#include <fstream>

#include "Amp.h"
#include "GetQ.h"
#include "Phase.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"

void DataAnalysis2() {
  // creating a file
  TFile *file = new TFile("MyDrawings.root", "recreate");
  // creating functions and graphs
  const Double_t w0 = 1 / (2 * M_PI * sqrt(10.16e-3 * 10.15e-9));
  /*const Double_t dw0 =
      (1 / (2*2 * M_PI * sqrt(10.16e-3 * 10.15e-9))) *
      sqrt((10.16e-3 * 0.01 * 10.16e-3 * 0.01) / (10.16e-3 * 10.16e-3) +
           (10.15e-9 * 0.01 * 10.15e-9 * 0.01) / (10.15e-9 * 10.15e-9));*/
  const Double_t dw0 = w0 / 100;
  TString gR = "gR";
  TString gM = "gM";
  TString gF = "gF";
  TString fR = "fR";
  TString fM = "fM";
  TString fF = "fF";
  TString H = "H_{R}";
  TString name[5] = {"150", "330", "560", "1200", "2200"};
  const Double_t R[5] = {150.95, 328.98, 560.1, 1179, 2194.8};
  const Double_t dR[5] = {1.15095e-3, 1.32898e-3, 1.5601e-3, 0.011979,
                          0.012948};
  TGraphErrors *gtotR[5];
  TGraphErrors *gtotM[5];
  TGraph *gtotF[5];
  TF1 *ftotR[5];
  TF1 *ftotM[5];
  TF1 *ftotF[5];
  const TString titleR[5] = {
      "Risposta in ampiezza su R_{1}", "Risposta in ampiezza su R_{2}",
      "Risposta in ampiezza su R_{3}", "Risposta in ampiezza su R_{4}",
      "Risposta in ampiezza su R_{5}"};
  const TString titleM[5] = {
      "Risposta in ampiezza su M_{1}", "Risposta in ampiezza su M_{2}",
      "Risposta in ampiezza su M_{3}", "Risposta in ampiezza su M_{4}",
      "Risposta in ampiezza su M_{5}"};
  const TString titleF[5] = {
      "Risposta in fase su R_{1}", "Risposta in fase su R_{2}",
      "Risposta in fase su R_{3}", "Risposta in fase su R_{4}",
      "Risposta in fase su R_{5}"};
  const TString titleX = "Frequenza (Hz)";
  const TString titleY = "Ampiezza (V)";
  const TString titleYF = "Fase (rad)";
  for (int i = 0; i < 5; ++i) {
    gtotR[i] = new TGraphErrors("ER" + name[i] + ".txt", "%lg%lg%lg");
    gtotR[i]->SetMarkerStyle(25);
    ftotR[i] =
        new TF1(fR + i, Real_AmplitudeR,
                TMath::MinElement(gtotR[i]->GetN(), gtotR[i]->GetX()),
                TMath::MaxElement(gtotR[i]->GetN(), gtotR[i]->GetX()), 6);
    ftotR[i]->SetParameters(2.5, R[i], 10.16e-3, 10.15e-9, 37.41, 50);
    ftotR[i]->SetLineColor(kOrange + 10);
    gtotR[i]->SetTitle(titleR[i]);
    gtotR[i]->SetName(gR + i);
    gtotR[i]->GetHistogram()->GetXaxis()->SetTitle(titleX);
    gtotR[i]->GetHistogram()->GetYaxis()->SetTitle(titleY);
  }
  for (int i = 0; i < 5; ++i) {
    gtotM[i] = new TGraphErrors("EM" + name[i] + ".txt", "%lg%lg%lg");
    gtotM[i]->SetMarkerStyle(25);
    ftotM[i] =
        new TF1(fM + i, Real_Amplitude_LC,
                TMath::MinElement(gtotM[i]->GetN(), gtotM[i]->GetX()),
                TMath::MaxElement(gtotM[i]->GetN(), gtotM[i]->GetX()), 6);
    ftotM[i]->SetParameters(2.5, R[i], 10.16e-3, 10.15e-9, 37.41, 50);
    ftotM[i]->SetLineColor(kOrange + 10);
    gtotM[i]->SetTitle(titleM[i]);
    gtotM[i]->SetName(gM + i);
    gtotM[i]->GetHistogram()->GetXaxis()->SetTitle(titleX);
    gtotM[i]->GetHistogram()->GetYaxis()->SetTitle(titleY);
  }
  // phase
  int j[5] = {0, 0, 0, 0, 0};
  std::ifstream in[5];
  for (int i = 0; i < 5; ++i) {
    in[i].open("F" + name[i] + ".txt");
    gtotF[i] = new TGraph();
    Double_t x, y;
    while (1) {
      in[i] >> x >> y;
      if (!in[i].good()) {
        break;
      }
      gtotF[i]->SetPoint(j[i], x, (y - (0.000195723 * x)) * (M_PI / 180));
      ++j[i];
    }
    in[i].close();
    gtotF[i]->SetName(gF + i);
    gtotF[i]->SetTitle(titleF[i]);
    gtotF[i]->SetMarkerStyle(25);
    ftotF[i] =
        new TF1(fF + i, Real_PhaseR,
                TMath::MinElement(gtotF[i]->GetN(), gtotF[i]->GetX()),
                TMath::MaxElement(gtotF[i]->GetN(), gtotF[i]->GetX()), 5);
    ftotF[i]->SetParameters(R[i], 10.16e-3, 10.15e-9, 37.41, 50);
    ftotF[i]->SetLineColor(kOrange + 10);
    gtotF[i]->GetHistogram()->GetXaxis()->SetTitle(titleX);
    gtotF[i]->GetHistogram()->GetYaxis()->SetTitle(titleYF);
  }
  // fitting
  for (int i = 0; i < 5; ++i) {
    gtotR[i]->Fit(ftotR[i], "qs0");
    gtotR[i]->GetHistogram()->GetYaxis()->SetRangeUser(
        0, ftotR[i]->GetMaximum() + 0.2);
    gtotR[i]->GetHistogram()->GetXaxis()->SetRangeUser(
        TMath::MinElement(gtotR[i]->GetN(), gtotR[i]->GetX()),
        TMath::MaxElement(gtotR[i]->GetN(), gtotR[i]->GetX()));
    gtotR[i]->Write();
    ftotR[i]->Write();
  }
  for (int i = 0; i < 5; ++i) {
    gtotM[i]->Fit(ftotM[i], "qs0");
    gtotM[i]->GetHistogram()->GetYaxis()->SetRangeUser(
        0, ftotM[i]->GetMaximum() + 0.2);
    gtotM[i]->GetHistogram()->GetXaxis()->SetRangeUser(
        TMath::MinElement(gtotM[i]->GetN(), gtotM[i]->GetX()),
        TMath::MaxElement(gtotM[i]->GetN(), gtotM[i]->GetX()));
    gtotM[i]->Write();
    ftotM[i]->Write();
  }
  for (int i = 0; i < 5; ++i) {
    gtotF[i]->Fit(ftotF[i], "qs0");
    gtotF[i]->GetHistogram()->GetXaxis()->SetRangeUser(
        TMath::MinElement(gtotF[i]->GetN(), gtotF[i]->GetX()),
        TMath::MaxElement(gtotF[i]->GetN(), gtotF[i]->GetX()));
    gtotF[i]->Write();
    ftotF[i]->Write();
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
  Double_t QR[5];
  for (int i = 0; i < 5; ++i) {
    w1R[i] = H_R[i]->GetX(1 / sqrt(2), -10e10, w0);
    w2R[i] = H_R[i]->GetX(1 / sqrt(2), w0, 10e10);
    QR[i] = w0 / (w2R[i] - w1R[i]);
  }
  Double_t w1M[5];
  Double_t w2M[5];
  Double_t QM[5];
  for (int i = 0; i < 5; ++i) {
    w1M[i] = ftotM[i]->GetX(2.5 / sqrt(2), -10e10, w0);
    w2M[i] = ftotM[i]->GetX(2.5 / sqrt(2), w0, 10e10);
    QM[i] = w0 / (w2M[i] - w1M[i]);
  }
  // measuring f0
  Double_t f0_minR[5];   // calculated as the min x of the fit func (R)
  Double_t f0_fitR[5];   // calculated from the fit parameters (R)
  Double_t df0_fitR[5];  // error on f0 from fit parameters (R)
  Double_t f0_minM[5];   // calculated as the min x of the fit func (M)
  Double_t f0_fitM[5];   // calculated from the fit parameters (M)
  Double_t df0_fitM[5];  // error on f0 from fit parameters (M)
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
  double WeightedAverage;
  double DeltaWeightedAverage;
  double num = 0.;
  double den = 0.;
  for (int i = 0; i < 5; ++i) {
    num +=
        f0_fitR[i] / (pow(df0_fitR[i], 2)) + f0_fitM[i] / (pow(df0_fitM[i], 2));
    den += 1 / pow(df0_fitR[i], 2) + 1 / pow(df0_fitM[i], 2);
  }
  WeightedAverage = num / den;
  DeltaWeightedAverage = 1 / sqrt(den);
  // saving data
  std::ofstream txt("./Data2.txt", std::ofstream::out);
  if (txt.is_open()) {
    txt << "============================" << '\n';
    txt << "||  RISULTATI SPERIMENTALI ||" << '\n';
    txt << "============================" << '\n';
    txt << '\n';
    txt << '\n';
    txt << "==> Confronto tra Q misurato e Q stimato (R)" << '\n';
    for (int i = 0; i < 5; ++i) {
      txt << "Misurato"
          << " (" << name[i] << "R):  " << QR[i]
          << "  ||  Stimato (Approx.):  " << R[i] * sqrt(10.15e-9 / 10.16e-3)
          << "  +/-  "
          << GetQErr(R[i], 10.16e-3, 10.15e-9, dR[i], (10.16e-3) * (0.01),
                     (10.15e-9) * (0.01))
          << "  ||  Stimato (Esatto):  "
          << w0 / GetBandWidth(R[i], 10.16e-3, 10.15e-9) << '\n';
    }
    txt << '\n';
    txt << '\n';
    txt << "==> Confronto tra Q misurato e Q stimato (M)" << '\n';
    for (int i = 0; i < 5; ++i) {
      txt << "Misurato"
          << " (" << name[i] << "M):  " << QM[i]
          << "  ||  Stimato:  " << R[i] * sqrt(10.15e-9 / 10.16e-3) << "  +/-  "
          << GetQErr(R[i], 10.16e-3, 10.15e-9, dR[i], (10.16e-3) * (0.01),
                     (10.15e-9) * (0.01))
          << "  ||  Stimato (Esatto):  "
          << w0 / GetBandWidth(R[i], 10.16e-3, 10.15e-9) << '\n';
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
    txt << "Media Pesata:  " << WeightedAverage << "  +/-  "
        << DeltaWeightedAverage <<  "  Hz"<<'\n';
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
    txt << '\n';
    txt << '\n';
    txt << "==> Risultati Fit (Phi)" << '\n';
    for (int i = 0; i < 5; ++i) {
      txt << "- F" << name[i] << ":  " << '\n';
      txt << "Resistenza R:  " << ftotF[i]->GetParameter(0) << "  +/-  "
          << ftotF[i]->GetParError(0) << "  ohm" << '\n';
      txt << "Induttanza L:  " << ftotF[i]->GetParameter(1) << "  +/-  "
          << ftotF[i]->GetParError(1) << "  H" << '\n';
      txt << "Capacità C:  " << ftotF[i]->GetParameter(2) << "  +/-  "
          << ftotF[i]->GetParError(2) << "  F" << '\n';
      txt << "Resistenza Induttore Rl:  " << ftotF[i]->GetParameter(3)
          << "  +/-  " << ftotF[i]->GetParError(3) << "  ohm" << '\n';
      txt << "Resistenza Generatore Rv:  " << ftotF[i]->GetParameter(4)
          << "  +/-  " << ftotF[i]->GetParError(4) << "  ohm" << '\n';
      txt << "Chi quadro e NDF:  " << ftotF[i]->GetChisquare() << "  ,  "
          << ftotF[i]->GetNDF() << '\n';
      txt << "Chi quadro ridotto:  "
          << ftotF[i]->GetChisquare() / ftotF[i]->GetNDF() << '\n';
      txt << '\n';
    }
    txt.close();
  } else {
    std::cout << "Cannot Open File..." << '\n';
  }
  file->Close();
}
