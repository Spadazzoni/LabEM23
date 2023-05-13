#include <fstream>

#include "TCanvas.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TStyle.h"

void DataAnalysis() {
  gStyle->SetOptStat("2210");
  // creating histos, canvases and functions
  const int N = 3;
  TH2F *htot[N];
  TF1 *ftotX[N - 1];
  TF1 *ftotY[N];
  TH1D *htotX[N - 1];
  TH1D *htotY[N];
  TString h = "h";
  TString fX = "fX";
  TString fY = "fY";
  TString name[N] = {"Scatter Plot #nu vs A", "Scatter Plot #nu vs #phi",
                     "Incertezza casuale sulla lettura di un'onda quadra"};
  TString Xname[N - 1] = {
      "Incertezza casuale sulla frequenza dell'onda di potenziale erogata (A)",
      "Incertezza casuale sulla frequenza dell'onda di potenziale erogata "
      "(#phi)"};
  TString Yname[N] = {
      "Incertezza casuale sull'ampiezza dell'onda di potenziale erogata",
      "Incertezza casuale sulla fase dell'onda di potenziale erogata",
      "Incertezza casuale sulla lettura dell'ampiezza di un'onda quadra"};
  Double_t XMin[N] = {499.924, 499.92, 2.5};
  Double_t XMax[N] = {499.955, 499.96, 3.5};
  Double_t YMin[N] = {2.1678, -1.25, 2.05};
  Double_t YMax[N] = {2.1685, 0, 2.3};
  Int_t XBins[N] = {25, 15, 25};
  Int_t YBins[N] = {65, 65, 65};
  for (int i = 0; i < N; ++i) {
    htot[i] = new TH2F(h + i, name[i], XBins[i], XMin[i], XMax[i], YBins[i],
                       YMin[i], YMax[i]);
  }
  for (int i = 0; i < N - 1; ++i) {
    ftotX[i] = new TF1(fX + i, "gaus", XMin[i], XMax[i]);
    ftotX[i]->SetLineColor(kOrange + 10);
  }
  for (int i = 0; i < N; ++i) {
    ftotY[i] = new TF1(fY + i, "gaus", YMin[i], YMax[i]);
    ftotY[i]->SetLineColor(kOrange + 10);
  }
  TCanvas *c = new TCanvas("c1", "MyCanvas1", 200, 200, 800, 600);
  c->Divide(3, 2);
  // reading from files
  Float_t x1, y1, x2, y2, x3, y3;
  std::ifstream in1;
  std::ifstream in2;
  std::ifstream in3;
  in1.open("IncertezzaCasualeAvsF.txt");
  in2.open("IncertezzaCasualeFvsN.txt");
  in3.open("IncertezzaCasualeLetturaV.txt");
  while (1) {
    in1 >> x1 >> y1;
    in2 >> x2 >> y2;
    in3 >> x3 >> y3;
    if (!in1.good() && !in2.good() && !in3.good()) {
      break;
    }
    htot[0]->Fill(x1, y1);
    htot[1]->Fill(x2, y2);
    htot[2]->Fill(x3, y3);
  }
  in1.close();
  in2.close();
  in3.close();
  // fitting projections
  for (int i = 0; i < N; ++i) {
    if (i != 2) {
      htotX[i] = htot[i]->ProjectionX();
      htotY[i] = htot[i]->ProjectionY();
      htotX[i]->SetFillColor(kAzure + 10);
      htotY[i]->SetFillColor(kAzure + 10);
      htotX[i]->SetTitle(Xname[i]);
      htotY[i]->SetTitle(Yname[i]);
      htotX[i]->Fit(ftotX[i], "qs0");
      htotY[i]->Fit(ftotY[i], "qs0");
    } else {
      htotY[i] = htot[i]->ProjectionY();
      htotY[i]->SetFillColor(kAzure + 10);
      htotY[i]->SetTitle(Yname[i]);
      htotY[i]->Fit(ftotY[i], "qs0");
    }
  }
  // saving data
  std::ofstream txt("./Data.txt", std::ofstream::out);
  if (txt.is_open()) {
    txt << "============================" << '\n';
    txt << "||  RISULTATI SPERIMENTALI ||" << '\n';
    txt << "============================" << '\n';
    txt << '\n';
    txt << '\n';
    txt << "==> Istogramma di dispersione Ampiezza vs Frequenza (500 Hz)"
        << '\n';
    txt << "Ingressi Totali:  " << htotX[0]->GetEntries() << '\n';
    txt << "====> Istogramma Ampiezza:" << '\n';
    txt << "Media:  " << ftotY[0]->GetParameter(1) << "  +/-  "
        << ftotY[0]->GetParError(1) << "  V" << '\n';
    txt << "Dev Std:  " << ftotY[0]->GetParameter(2) << "  +/-  "
        << ftotY[0]->GetParError(2) << "  V" << '\n';
    txt << "Chi quadro e GDL:  " << ftotY[0]->GetChisquare() << " , "
        << ftotY[0]->GetNDF() << '\n';
    txt << "Chi quadro ridotto: "
        << ftotY[0]->GetChisquare() / ftotY[0]->GetNDF() << '\n';
    txt << "====> Istogramma Frequenza:" << '\n';
    txt << "Media:  " << ftotX[0]->GetParameter(1) << "  +/-  "
        << ftotX[0]->GetParError(1) << "  Hz" << '\n';
    txt << "Dev Std:  " << ftotX[0]->GetParameter(2) << "  +/-  "
        << ftotX[0]->GetParError(2) << "  Hz" << '\n';
    txt << "Chi quadro e GDL:  " << ftotX[0]->GetChisquare() << " , "
        << ftotX[0]->GetNDF() << '\n';
    txt << "Chi quadro ridotto: "
        << ftotX[0]->GetChisquare() / ftotX[0]->GetNDF() << '\n';
    txt << '\n';
    txt << '\n';
    txt << "==> Istogramma di dispersione Fase vs Frequenza (500 Hz)" << '\n';
    txt << "Ingressi Totali:  " << htotX[1]->GetEntries() << '\n';
    txt << "====> Istogramma Fase:  " << '\n';
    txt << "Media:  " << ftotY[1]->GetParameter(1) << "  +/-  "
        << ftotY[1]->GetParError(1) << "  deg" << '\n';
    txt << "Dev Std:  " << ftotY[1]->GetParameter(2) << "  +/-  "
        << ftotY[1]->GetParError(2) << "  deg" << '\n';
    txt << "Chi quadro e GDL:  " << ftotY[1]->GetChisquare() << " , "
        << ftotY[1]->GetNDF() << '\n';
    txt << "Chi quadro ridotto: "
        << ftotY[1]->GetChisquare() / ftotY[1]->GetNDF() << '\n';
    txt << "====> Istogramma Frequenza:" << '\n';
    txt << "Media:  " << ftotX[1]->GetParameter(1) << "  +/-  "
        << ftotX[1]->GetParError(1) << "  Hz" << '\n';
    txt << "Dev Std:  " << ftotX[1]->GetParameter(2) << "  +/-  "
        << ftotX[1]->GetParError(2) << "  Hz" << '\n';
    txt << "Chi quadro e GDL:  " << ftotX[1]->GetChisquare() << " , "
        << ftotX[1]->GetNDF() << '\n';
    txt << "Chi quadro ridotto: "
        << ftotX[1]->GetChisquare() / ftotX[1]->GetNDF() << '\n';
    txt << '\n';
    txt << '\n';
    txt << "==> Istogramma lettura Ampiezza di un'onda quadra (5V pk)" << '\n';
    txt << "Ingressi Totali:  " << htotY[2]->GetEntries() << '\n';
    txt << "====> Istogramma Ampiezza:  " << '\n';
    txt << "Media:  " << ftotY[2]->GetParameter(1) << "  +/-  "
        << ftotY[2]->GetParError(1) << "  V" << '\n';
    txt << "Dev Std:  " << ftotY[1]->GetParameter(2) << "  +/-  "
        << ftotY[2]->GetParError(2) << "  V" << '\n';
    txt << "Chi quadro e GDL:  " << ftotY[2]->GetChisquare() << " , "
        << ftotY[2]->GetNDF() << '\n';
    txt << "Chi quadro ridotto: "
        << ftotY[2]->GetChisquare() / ftotY[2]->GetNDF() << '\n';
    txt.close();
  } else {
    std::cout << "Cannot open File" << '\n';
  }
  // drawing
  int j = 0;
  for (int i = 0; i < N; ++i) {
    if (i != 2) {
      c->cd(i + j + 1);
      htotX[i]->Draw("hist");
      ftotX[i]->Draw("same");
      c->cd(i + j + 2);
      htotY[i]->Draw("hist");
      ftotY[i]->Draw("same");
    } else {
      c->cd(j + i + 1);
      htotY[i]->Draw("hist");
      ftotY[i]->Draw("same");
    }
    ++j;
  }
}