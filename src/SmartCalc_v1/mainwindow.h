#ifndef MAINWINDOW_H 
#define MAINWINDOW_H
#include <QMainWindow>
#include <graph_my.h>
extern "C"
{
#include "../Project/s21_calc.h"
#include "../Project/s21_credit_calc.h"
}

#define DEF_X 3.1

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE



class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  graph_my *graph;

signals:
    void signal(char *str);


 private slots:
  void buttons_clicked();
  void result();
  void delite_one();
  void clear();
  void graph_print();
  void credit();


};
#endif  // MAINWINDOW_H
