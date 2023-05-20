#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"

void Draw() {
  TFile *file = new TFile("MyDrawings.root");
  TF1 *f1 = (TF1 *)file->Get("fR3");
  f1->SetLineColor(kViolet + 1);
  TF1 *f2 = (TF1 *)file->Get("fM3");
  f2->SetLineColor(kSpring - 8);
  /*TF1 *f3 = (TF1 *)file->Get("fM4");
  f3->SetLineColor(46);*/
  //TF1 *f = new TF1("f", "2.5/sqrt(2)", 0, 30000);
 // f->SetLineColor(kOrange + 3);
  TGraphErrors *g1 = (TGraphErrors *)file->Get("gR3");
  TGraphErrors *g2 = (TGraphErrors *)file->Get("gM3");
  // TGraph *g3 = (TGraph *)file->Get("gR4");
  TCanvas *c1 = new TCanvas("c1", "Mycanvas1", 200, 200, 1000, 600);
  // TCanvas *c2 = new TCanvas("c2", "Mycanvas2", 200, 200, 1000, 600);
  //  TCanvas *c3 = new TCanvas("c3", "Mycanvas3", 200, 200, 1000, 600);
  c1->Print("RandM.pdf[");
  g1->Draw("ape");
  f1->Draw("same");
  //f->Draw("same");
  g2->Draw("same");
  f2->Draw("same");
  // g3->GetHistogram()->GetYaxis()->SetRangeUser(0, 2.52);
  // g3->Draw("same");
  // f3->Draw("same");
  c1->SetGrid();
  c1->BuildLegend();
  c1->Print("RandM.pdf");
  c1->Print("RandM.pdf]");
  // c2->Print("Maglia330.pdf[");
  //  c3->Print("Fase330.pdf[");
  /* c1->cd();
   g1->Draw("ape");
   f1->Draw("same");
   c1->BuildLegend();
   c1->SetGrid();
  // c2->cd();
   g2->Draw("ape");
   f2->Draw("same");
  // c2->SetGrid();
  // c2->BuildLegend();
   c3->cd();
   g3->Draw("ape");
   f3->Draw("same");
   c3->BuildLegend();
   c3->SetGrid();
   c1->Print("Notch330.pdf");
   c1->Print("Notch330.pdf]");
   c2->Print("Maglia330.pdf");
   c2->Print("Maglia330.pdf]");
   c3->Print("Fase330.pdf");
   c3->Print("Fase330.pdf]");*/
}