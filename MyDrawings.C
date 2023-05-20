#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TLegendEntry.h"

void Draw() {
  TFile *file = new TFile("MyDrawings.root");
  // extracting graphs and functions from file
  TF1 *fR[5];
  TF1 *fM[5];
  TF1 *fF[5];
  TGraphErrors *gR[5];
  TGraphErrors *gM[5];
  TGraph *gF[5];
  TString nameR = "fR";
  TString nameM = "fM";
  TString nameF = "fF";
  TString gnameR = "gR";
  TString gnameM = "gM";
  TString gnameF = "gF";
  for (int i = 0; i < 5; ++i) {
    fR[i] = (TF1 *)file->Get(nameR + i);
    fM[i] = (TF1 *)file->Get(nameM + i);
    fF[i] = (TF1 *)file->Get(nameF + i);
    gR[i] = (TGraphErrors *)file->Get(gnameR + i);
    gM[i] = (TGraphErrors *)file->Get(gnameM + i);
    gF[i] = (TGraph *)file->Get(gnameF + i);
  }
  // creating canvases
  TCanvas *ctotR[5];
  TString cR = "cR";
  TString MyCanvasR = "MyCanvasR";
  TString pdfR[5] = {"Notch150.pdf", "Notch330.pdf", "Notch560.pdf",
                     "Notch1200.pdf", "Notch2200.pdf"};
  TCanvas *ctotM[5];
  TString cM = "cM";
  TString MyCanvasM = "MyCanvasM";
  TString pdfM[5] = {"PassaBanda150.pdf", "PassaBanda330.pdf",
                     "PassaBanda560.pdf", "PassaBanda1200.pdf",
                     "PassaBanda2200.pdf"};
  TCanvas *ctotF[5];
  TString cF = "cF";
  TString MyCanvasF = "MyCanvasF";
  TString pdfF[5] = {"Fase150.pdf", "Fase330.pdf", "Fase560.pdf",
                     "Fase1200.pdf", "Fase2200.pdf"};
  for (int i = 0; i < 5; ++i) {
    ctotR[i] = new TCanvas(cR + i, MyCanvasR + i, 200, 200, 1000, 600);
    ctotR[i]->Print(pdfR[i] + "[");
    ctotR[i]->SetGridx();
    ctotR[i]->SetGridy();
  }
  for (int i = 0; i < 5; ++i) {
    ctotM[i] = new TCanvas(cM + i, MyCanvasM + i, 200, 200, 1000, 600);
    ctotM[i]->Print(pdfM[i] + "[");
    ctotM[i]->SetGridx();
    ctotM[i]->SetGridy();
  }
  for (int i = 0; i < 5; ++i) {
    ctotF[i] = new TCanvas(cF + i, MyCanvasF + i, 200, 200, 1000, 600);
    ctotF[i]->Print(pdfF[i] + "[");
    ctotF[i]->SetGridx();
    ctotF[i]->SetGridy();
  }
  // drawing
  for (int i = 0; i < 5; ++i) {
    ctotR[i]->cd();
    gR[i]->Draw("ape");
    fR[i]->Draw("same");
  }
  for (int i = 0; i < 5; ++i) {
    ctotM[i]->cd();
    gM[i]->Draw("ape");
    fM[i]->Draw("same");
  }
  for (int i = 0; i < 5; ++i) {
    ctotF[i]->cd();
    gF[i]->Draw("ape");
    fF[i]->Draw("same");
  }
  // building legends
  for (int i = 0; i < 5; ++i) {
    TLegend *l = ctotR[i]->BuildLegend();
    TList *p = l->GetListOfPrimitives();
    TIter next(p);
    TObject *obj;
    TLegendEntry *le;
    int j = 0;
    while ((obj = next())) {
      le = (TLegendEntry *)obj;
      ++j;
      if (j == 2) {
        le->SetLabel("Fit");
      }
      if (j == 1) {
        le->SetLabel("Punti sperimentali");
      }
    }
  }
  for (int i = 0; i < 5; ++i) {
    TLegend *l = ctotM[i]->BuildLegend();
    TList *p = l->GetListOfPrimitives();
    TIter next(p);
    TObject *obj;
    TLegendEntry *le;
    int j = 0;
    while ((obj = next())) {
      le = (TLegendEntry *)obj;
      ++j;
      if (j == 2) {
        le->SetLabel("Fit");
      }
      if (j == 1) {
        le->SetLabel("Punti sperimentali");
      }
    }
  }
  for (int i = 0; i < 5; ++i) {
    TLegend *l = ctotF[i]->BuildLegend();
    TList *p = l->GetListOfPrimitives();
    TIter next(p);
    TObject *obj;
    TLegendEntry *le;
    int j = 0;
    while ((obj = next())) {
      le = (TLegendEntry *)obj;
      ++j;
      if (j == 2) {
        le->SetLabel("Fit");
      }
      if (j == 1) {
        le->SetLabel("Punti sperimentali");
      }
    }
  }
  // saving drawings
  for (int i = 0; i < 5; ++i) {
    ctotR[i]->Print(pdfR[i]);
    ctotR[i]->Print(pdfR[i] + "]");
  }
  for (int i = 0; i < 5; ++i) {
    ctotM[i]->Print(pdfM[i]);
    ctotM[i]->Print(pdfM[i] + "]");
  }
  for (int i = 0; i < 5; ++i) {
    ctotF[i]->Print(pdfF[i]);
    ctotF[i]->Print(pdfF[i] + "]");
  }
  file->Close();
}