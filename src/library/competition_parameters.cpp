#include "competition_parameters.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

CompetitionParameters::CompetitionParameters() {
}

std::map<int, Tier> CompetitionParameters::TierScoring() const {
  return tier_scoring_;
}

int CompetitionParameters::MinDancersInDivision() const {
  return min_dancers_in_division_;
}

int CompetitionParameters::MaxDivisions() const { return max_divisions_; }

void CompetitionParameters::ReadFile(const QString &path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  const auto json_document = QJsonDocument::fromJson(file.readAll());

  const auto json_object = json_document.object();

  max_divisions_ = json_object["max_divisions"].toInt();
  min_dancers_in_division_ = json_object["min_in_division"].toInt();

  const auto scorings = json_object["tiers"].toArray();

  foreach (const QJsonValue &value, scorings) {
    Tier tier;
    QJsonObject obj = value.toObject();
    tier.max_dancers = obj["max_dancers"].toInt();
    tier.min_dancers = obj["min_dancers"].toInt();
    const auto scoring = obj["points"].toArray();

    foreach (const auto &points, scoring) {
      tier.scoring.push_back(points.toInt());
    }
    tier_scoring_[obj["id"].toInt()] = tier;
  }

  const auto division_values = json_object["divisions"].toArray();
  foreach (const QJsonValue &value, division_values) {
      division_ceilings_.push_back(value["ceiling"].toInt());
  }
}

std::vector<int> CompetitionParameters::DivisionCeilings() const
{
    return division_ceilings_;
}
