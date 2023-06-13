#ifndef GRAPH_MY_H
#define GRAPH_MY_H

#include <QWidget>

extern "C" {
#include "../Project/s21_calc.h" 
}


namespace Ui {
class graph_my;
}

class graph_my : public QWidget
{
    Q_OBJECT

public:
    explicit graph_my(QWidget *parent = nullptr);
    ~graph_my();

private:
    Ui::graph_my *ui;
    double h, X;
    double Xmin, Xmax, Ymin, Ymax;
    QVector<double> x, y;

public slots:
    void slot(char *str);
    void graph_change();
};

#endif // GRAPH_MY_H
