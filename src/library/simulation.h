#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>

#include <dancer.h>
#include <competition_parameters.h>

class Simulation
{
public:
    Simulation();

    void InitiateSimulation(int amount, int satisfaction, std::pair<int, int> new_dancers);
    QString Run(int iterations);
    QString RunTillTopLevel(int tops_amount);

    QString Step();

private:
    void CreateInitialDancers();
    bool IsDancerPromotable(uint16_t points, uint16_t division);
    int TopLevelDancersAmount() const;
    Dancers all_the_dancers_;
    CompetitionParameters parameters_;
    int dancer_amount_=0;

    std::pair<int, int> new_dancers_ = {5, 10};
    int initial_amount_ = 50;
    int initial_satisfaction_ = 40;
};

#endif // SIMULATION_H
