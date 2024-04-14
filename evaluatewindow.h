#ifndef EVALUATEWINDOW_H
#define EVALUATEWINDOW_H

#include <QWidget>

namespace Ui {
class EvaluateWindow;
}

class EvaluateWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EvaluateWindow(QWidget *parent = nullptr);
    ~EvaluateWindow();

private slots:
    void on_pushEvaluation_clicked();

private:
    Ui::EvaluateWindow *ui;
signals:
    void sendEvaluate(int i);
};

#endif // EVALUATEWINDOW_H
