#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraphErrors.h"

void Draw() {
  TFile *file = new TFile("MyDrawings.root");
  // extracting graphs and functions from file
  TF1 *fR[5];
  TF1 *fM[5];
  TGraphErrors *gR[5];
  TGraphErrors *gM[5];
  TString nameR = "fR";
  TString nameM = "fM";
  TString gnameR = "gR";
  TString gnameM = "gM";
  for (int i = 0; i < 5; ++i) {
    fR[i] = (TF1 *)file->Get(nameR + i);
    fM[i] = (TF1 *)file->Get(nameM + i);
    gR[i] = (TGraphErrors *)file->Get(gnameR + i);
    gM[i] = (TGraphErrors *)file->Get(gnameM + i);
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
  for (int i = 0; i < 5; ++i) {
    ctotR[i] = new TCanvas(cR + i, MyCanvasR + i, 200, 200, 1000, 600);
    ctotR[i]->Print(pdfR[i] + "[");
  }
  for (int i = 0; i < 5; ++i) {
    ctotM[i] = new TCanvas(cM + i, MyCanvasM + i, 200, 200, 1000, 600);
    ctotM[i]->Print(pdfM[i] + "[");
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
  // saving drawings
  for (int i = 0; i < 5; ++i) {
    ctotR[i]->Print(pdfR[i]);
    ctotR[i]->Print(pdfR[i] + "]");
  }
  for (int i = 0; i < 5; ++i) {
    ctotM[i]->Print(pdfM[i]);
    ctotM[i]->Print(pdfM[i] + "]");
  }
  file->Close();
}