#include "graph_my.h" 
#include "ui_graph_my.h"

graph_my::graph_my(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graph_my)
{
    ui->setupUi(this);
    connect(ui->pushButton_draw, SIGNAL(clicked()), this, SLOT(graph_change()));

}

void graph_my::graph_change(){
    QByteArray ba = ui->label_graph->text().toLocal8Bit();
    char * str = ba.data();
    slot(str);
}

void graph_my::slot(char * str){
    h = 0.01;
    Xmax = ui->lineEdit_xmax->text().toDouble();
    Xmin = ui->lineEdit_xmin->text().toDouble();
    Ymax = ui->lineEdit_ymax->text().toDouble();
    Ymin = ui->lineEdit_ymin->text().toDouble();

      ui->widget->clearGraphs();
      ui->widget->xAxis->setRange(Xmin, Xmax);
      ui->widget->yAxis->setRange(Ymin, Ymax);
      double tmp = 0;
      int a = s21_calc(str, 1, &tmp);
      if(a == 0 || a == CALC_ERROR_NUM_INF){
        for (X = Xmin; X <= Xmax; X += h) {
          double Y = 0.0;
          a = s21_calc(str, X, &Y);
          if (Y <= Ymin * 2 || Y >= Ymax * 2 ||a == CALC_ERROR_NUM_NAN) {
            Y = qQNaN();
          }

          x.push_back(X);
          y.push_back(Y);
        }
      }
      ui->widget->addGraph();
      ui->widget->graph(0)->addData(x, y);
      ui->widget->replot();
      x.clear();
      y.clear();
      x.squeeze();
      y.squeeze();
      ui->label_graph->setText(str);

}


graph_my::~graph_my()
{
    delete ui;
}
