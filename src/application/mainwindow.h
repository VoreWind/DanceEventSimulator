#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "simulation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void RunFullSimulation();
    void RunOneIteration();
    void ResetSimulation();
    void SetSelectionMode(int);
private:
    Ui::MainWindow *ui;
    Simulation *simulation_;

    bool is_initialized_ = false;
};
#endif // MAINWINDOW_H
