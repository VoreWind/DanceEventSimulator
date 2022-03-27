#include "competition.h"

#include "competition_parameters.h"

#include <QDebug>

Competition::Competition() {}

Dancers Competition::CompeteOnce(const Dancers &dancers,
                                 const CompetitionParameters &parameters) {
  const auto divisions = SplitDancersToDivisions(dancers);
  Dancers updated_dancers = {};

  for (int i = 0; i < parameters.MaxDivisions(); i++) {
    const auto division = divisions.equal_range(i);
    std::multimap<int, Dancer> sorted_dancers;

    int dancer_count = 0;
    for (auto i = division.first; i != division.second; ++i) {
      const auto dancer = i->second;
      sorted_dancers.insert({dancer.GetPerformanceValue(), dancer});
      dancer_count++;
    }


    std::multimap<int, Dancer>::iterator it;

    int place = sorted_dancers.size() - 1;
    const auto tier_id = CalculateTier(dancer_count, parameters);

    for (it = sorted_dancers.begin(); it != sorted_dancers.end(); it++) {
      auto dancer = it->second;

      bool is_max_division = dancer.GetDivision()+1==parameters.MaxDivisions();
      dancer.ProcessCompetitionResults(
          CalculatePoints(place, tier_id, parameters), is_max_division);
      place--;
      updated_dancers.push_back(dancer);
    }
  }

  sort(updated_dancers.begin(), updated_dancers.end(),
       [](const Dancer &a, const Dancer &b) -> bool {
         return a.GetId() > b.GetId();
       });

  return updated_dancers;
}

std::multimap<int, Dancer>
Competition::SplitDancersToDivisions(const Dancers &dancers) {
  std::multimap<int, Dancer> divisions;
  for (const auto &dancer : dancers) {
    divisions.insert({dancer.GetDivision(), dancer});
  }
  return divisions;
}

int Competition::CalculatePoints(uint16_t place, int tier_id,
                                 const CompetitionParameters &parameters) {
    if (tier_id == -1){
        return -1;
    }
    const auto tier = parameters.TierScoring().at(tier_id);

  if (place >= tier.scoring.size()) {
    return 0;
  }
  return tier.scoring.at(place);
}

int Competition::CalculateTier(int dancers_count,
                               const CompetitionParameters &parameters) {
  for (const auto &[id, tier] : parameters.TierScoring()) {
    if (dancers_count <= tier.max_dancers &&
        dancers_count >= tier.min_dancers) {
      return id;
    }
  }
  return -1;
}
