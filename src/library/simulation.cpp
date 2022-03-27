#include "simulation.h"

#include "competition.h"
#include "competition_parameters.h"

#include <QDebug>
#include <QRandomGenerator>

Simulation::Simulation() {
  parameters_.ReadFile(
      "D:/Programming/DancingEventSimulator/DancingEventSimulator/"
      "MSA_rules.json");
  CreateInitialDancers();
}

void Simulation::InitiateSimulation(int amount, int satisfaction,
                                    std::pair<int, int> new_dancers) {
  initial_amount_ = amount;
  initial_satisfaction_ = satisfaction;
  new_dancers_ = new_dancers;

  all_the_dancers_.clear();
  dancer_amount_=0;
  CreateInitialDancers();
}

int Simulation::TopLevelDancersAmount() const
{
    int max_division_dancers = 0;
    for (const auto &dancer : all_the_dancers_) {
        if (dancer.GetDivision() == parameters_.MaxDivisions()-1) {
            max_division_dancers++;
        }
    }
    return max_division_dancers;
}

QString Simulation::Run(int iterations) {
  for (int i = 0; i < iterations; i++) {
    Step();
  }

  return "Прогон закончен. \nВсего было танцоров: " +
         QString::number(dancer_amount_) +
         "\nОсталось: " + QString::number(all_the_dancers_.size()) +
         "\nТоповых танцоров: " + QString::number(TopLevelDancersAmount());
}

QString Simulation::RunTillTopLevel(int tops_amount)
{
    for (int i = 0; i < 10000; i++) {
        Step();

        if (TopLevelDancersAmount() >= tops_amount){
            return "Прогон закончен. \nВсего было танцоров: " +
                   QString::number(dancer_amount_) +
                   "\nОсталось: " + QString::number(all_the_dancers_.size()) +
                   "\nТоповых танцоров: " + QString::number(TopLevelDancersAmount())+
                   "\nПрошло конкурсов: " + QString::number(i);
        }
    }
    return "Не удалось сгенерировать столько топов за 10000 конкурсов";
}

QString Simulation::Step() {
  all_the_dancers_ = Competition::CompeteOnce(all_the_dancers_, parameters_);

  for (auto it = all_the_dancers_.begin(); it != all_the_dancers_.end();) {
    if (it->GetSatisfaction() <= 0) {
      it = all_the_dancers_.erase(it);
      continue;
    }
    const auto [points, division] = it->GetPointsInDivision();
    if (IsDancerPromotable(points, division)) {
      it->UpdateDivision(division + 1);
    }
    ++it;
  }
  const auto new_dancers_amount =
      new_dancers_.first + QRandomGenerator::global()->bounded(
                               new_dancers_.second - new_dancers_.first);

  for (int i = 0; i < new_dancers_amount; i++) {
    all_the_dancers_.emplace_back(
        Dancer(initial_satisfaction_, dancer_amount_));
    dancer_amount_++;
  }
  QString return_string;
  for (const auto &dancer : all_the_dancers_) {
    return_string.append(dancer.DancerToString() + "\n");
  }

  return return_string;
}

void Simulation::CreateInitialDancers() {
  for (int i = 0; i < initial_amount_; i++) {
    all_the_dancers_.emplace_back(Dancer(initial_satisfaction_, i));
    dancer_amount_++;
  }
}

bool Simulation::IsDancerPromotable(uint16_t points, uint16_t division) {
  const auto division_points = parameters_.DivisionCeilings().at(division);
  return (points >= division_points);
}
