#include "mainwindow.h" 
#include "./ui_mainwindow.h"
#include "../Project/s21_calc.h"
#include "../Project/s21_credit_calc.h"
#include "graph_my.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    graph = new graph_my;
    connect(this, &MainWindow::signal, graph, &graph_my::slot);
//    graph->show();
//    graph->hide();



    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(buttons_clicked()));





    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(buttons_clicked()));

    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(buttons_clicked()));

    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(buttons_clicked()));


    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_left, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_right, SIGNAL(clicked()), this, SLOT(buttons_clicked()));

    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(buttons_clicked()));

    connect(ui->lineEdit_main, SIGNAL(returnPressed()), this, SLOT(result()));


    connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(result()));


    connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(clear()));
    connect(ui->pushButton_C, SIGNAL(clicked()), this, SLOT(delite_one()));

    connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(graph_print()));

    connect(ui->pushButton_credit, SIGNAL(clicked()), this, SLOT(credit()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::buttons_clicked()
{
    QPushButton* button = (QPushButton *) sender();
    QString new_label = ui->lineEdit_main->text() + button->text();
    ui->lineEdit_main->setText(new_label);
}


void MainWindow::result(){
    double x = DEF_X;
    double res = 0.0012;
    bool ok = true;


    if(!ui->lineEdit_x->text().isEmpty()){
     x = ui->lineEdit_x->text().toDouble(&ok);
     }


    if(!ok){
       ui->lineEdit_main->setText("x isn't valid");
    }else{
      if(ui->lineEdit_main->text().length() < 256){
       QByteArray ba = ui->lineEdit_main->text().toLocal8Bit();
       int err = s21_calc(ba.data(), x, &res);
       if(err == 1){
           ui->lineEdit_main->setText("inf");
       }else if(err == 2){
           ui->lineEdit_main->setText("nan");
       }else if(err == 0){
           QString result = QString::number(res, 'g', 7);
           ui->lineEdit_main->setText(result);
       }else{
           ui->lineEdit_main->setText("ERROR");
       }
     }else{
          ui->lineEdit_main->setText("string too long");

      }
    }
}


void MainWindow::clear(){
    ui->lineEdit_main->setText("");
}
void MainWindow::delite_one(){
    ui->lineEdit_main->backspace();
}


void MainWindow::graph_print() {
  graph->show();
  QByteArray ba = ui->lineEdit_main->text().toLocal8Bit();
  char * str = ba.data();
  emit signal(str);

}

void MainWindow::credit(){
    double *monthly_payment;
    bool ok_term = true;
    bool ok_interest = true;
    bool ok_sum = true;

    enum credit_type type = CREDIT_ANNUITY;
    struct credit_return_info result = {.monthly_payment = NULL, .overpayment = 0, .psk = 0};

    size_t term = ui->lineEdit_term->text().toUInt(&ok_term);
    double interest = ui->lineEdit_interest->text().toDouble(&ok_interest);
    double sum = ui->lineEdit_sum->text().toDouble(&ok_sum);

    if(ui->radioButton_ann->isChecked()){
        type = CREDIT_ANNUITY;
    }else if(ui->radioButton_diff->isChecked()){
        type = CREDIT_DIFFER;
    }

    if(ui->comboBox_term_type->currentText() == "лет"){
        term *= 12;
    }


    if(interest <=0 || interest >999) ok_interest = false;
    if(sum <= 0) ok_sum = false;

    if(ok_term && ok_interest && ok_sum){
         QString ArrStr;
        if(type == CREDIT_DIFFER){
            monthly_payment = new double[term];
        }else{
            monthly_payment = new double[0];
        }

        result.monthly_payment = monthly_payment;
        credit_calc(sum, term, interest, type, &result);

        if(type == CREDIT_DIFFER){
            for(size_t i = 0; i < term; i++){
                ArrStr += QString::number(result.monthly_payment[i]) + '\n';
            }
        }else{
            ArrStr = QString::number(result.monthly_payment[0]);
        }

        ui->label_monthly_payment->setText(ArrStr);
        QString overpay = QString::number(result.overpayment, 'g', 7);
        ui->label_overpay->setText(overpay);
        QString psk = QString::number(result.psk, 'g', 7);
        ui->label_psk->setText(psk);

        delete[] monthly_payment;
    }
}

