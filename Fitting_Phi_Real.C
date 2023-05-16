#include <fstream>

#include "Phase.h"
#include "TCanvas.h"
#include "TGraph.h"

void Fit() {
  TCanvas *c = new TCanvas("c", "myCanvas", 200, 200, 1000, 600);
  TGraph *g = new TGraph();
  std::fstream in;
  in.open("F330.txt");
  Double_t x, y;
  int i = 0;
  while (1) {
    in >> x >> y;
    if (!in.good()) {
      break;
    }
    g->SetPoint(i, x, (y - (0.000195723 * x) )* (M_PI / 180)); // 0.0005 dà fit perfetto
    ++i;
  }
  in.close();
  g->SetMarkerStyle(25);
  TF1 *f = new TF1("f", Real_PhaseR, 4e3, 30e3, 5);
  f->SetParameters(330, 10.16e-3, 10.15e-9, 37.41, 50);
  g->Fit("f", "s0");
  g->Draw("ap");
  f->Draw("same");
}
