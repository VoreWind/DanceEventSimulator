#ifndef COMPETITION_PARAMETERS_H
#define COMPETITION_PARAMETERS_H

#include <QObject>

using Scoring = std::vector<uint16_t>;

struct Tier{
    int min_dancers;
    int max_dancers;
    Scoring scoring;
};


class CompetitionParameters
{
public:
    CompetitionParameters();
    void ReadFile(const QString& path);

    std::map<int, Tier> TierScoring() const;
    int MinDancersInDivision() const;
    int MaxDivisions() const;

    std::vector<int> DivisionCeilings() const;

private:

    std::vector<int> division_ceilings_;
    std::map<int, Tier> tier_scoring_;
    int min_dancers_in_division_;
    int max_divisions_;
};

#endif // COMPETITION_PARAMETERS_H
