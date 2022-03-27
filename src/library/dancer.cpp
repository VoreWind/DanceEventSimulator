#include "dancer.h"

#include <QRandomGenerator>

Dancer::Dancer(int satisfaction, int id) : id_(id) {
  skill_ = QRandomGenerator::global()->bounded(50);
  satisfaction_ = satisfaction;
}

uint16_t Dancer::GetDivision() const { return division_; }

void Dancer::SetDivision(const uint16_t &division) { division_ = division; }

uint16_t Dancer::GetPerformanceValue() const {
  quint32 quality = QRandomGenerator::global()->bounded(50);
  return skill_ + quality;
}

void Dancer::UpdateDivision(uint16_t new_division) {
  division_ = new_division;
  satisfaction_ = satisfaction_*2;
  points_ = 0;
}

void Dancer::ProcessCompetitionResults(int16_t points, bool is_top_division) {
  if (points == -1) {
    return;
  }

  if (!is_top_division) {
      if (points > 1) {
          satisfaction_ += QRandomGenerator::global()->bounded(20);
      } else if (points == 0) {
          satisfaction_ -= QRandomGenerator::global()->bounded(20);
      } else {
          satisfaction_ += 7 - QRandomGenerator::global()->bounded(10);
      }
  } else {
      if (points > 0) {
          satisfaction_ += QRandomGenerator::global()->bounded(20);
      } else  {
          satisfaction_ -= QRandomGenerator::global()->bounded(10);
      }
  }
  points_ += points;
  skill_ += QRandomGenerator::global()->bounded(20);
}

std::pair<uint16_t, uint16_t> Dancer::GetPointsInDivision() const {
  return {points_, division_};
}

int16_t Dancer::GetSatisfaction() const { return satisfaction_; }

uint16_t Dancer::GetId() const { return id_; }

QString Dancer::DancerToString() const{
  return QString::number(id_) + ": " + QString::number(points_) + "(" +
         QString::number(division_) + ") points | " +
         QString::number(satisfaction_);
}
