#ifndef COMPETITION_H
#define COMPETITION_H

#include <QObject>

#include "dancer.h"

class CompetitionParameters;

class Competition
{
public:
    Competition();
    static Dancers CompeteOnce(const Dancers& dancers, const CompetitionParameters& parameters);
private:
    static std::multimap<int, Dancer> SplitDancersToDivisions(const Dancers& dancers);
    static int CalculatePoints(uint16_t place, int tier_id, const CompetitionParameters &parameters);
    static int CalculateTier(int dancers_count, const CompetitionParameters& parameters);

};

#endif // COMPETITION_H
