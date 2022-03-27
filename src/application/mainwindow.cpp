#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  simulation_ = new Simulation;

  ui->setupUi(this);
  SetSelectionMode(ui->combo_iteration_type->currentIndex());
  connect(ui->calculate_button, SIGNAL(pressed()), SLOT(RunFullSimulation()));
  connect(ui->iterate_button, SIGNAL(pressed()), SLOT(RunOneIteration()));
  connect(ui->reset_button, SIGNAL(pressed()), SLOT(ResetSimulation()));
  connect(ui->combo_iteration_type, SIGNAL(activated(int)),
          SLOT(SetSelectionMode(int)));
}

MainWindow::~MainWindow() {
  delete simulation_;
  delete ui;
}

void MainWindow::RunFullSimulation() {
  simulation_->InitiateSimulation(
      ui->top_amount_spin_box->value(), ui->spin_initial_motivation->value(),
      {ui->spin_newcomers_min->value(), ui->spin_newcomers_max->value()});

  QString result;
  if (ui->combo_iteration_type->currentIndex() == 0) {
    result = simulation_->Run(ui->iteration_spin_box->value());
  } else {
    result = simulation_->RunTillTopLevel(ui->top_amount_spin_box->value());
  }

  ui->textBrowser->setText(result);
}

void MainWindow::RunOneIteration() {
  if (!is_initialized_) {
    simulation_->InitiateSimulation(
        ui->top_amount_spin_box->value(), ui->spin_initial_motivation->value(),
        {ui->spin_newcomers_min->value(), ui->spin_newcomers_max->value()});
    is_initialized_ = true;
  }
  const auto result = simulation_->Step();
  ui->textBrowser->setText(result);
}

void MainWindow::ResetSimulation() { is_initialized_ = false; }

void MainWindow::SetSelectionMode(int mode) {
  if (mode == 0) {
    ui->iteration_widget->show();
    ui->division_widget->hide();

  } else {
    ui->iteration_widget->hide();
    ui->division_widget->show();
  }
}
