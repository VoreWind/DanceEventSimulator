#ifndef DANCER_H
#define DANCER_H

#include <string>
#include <vector>

#include <QString>

class Dancer;

using Dancers = std::vector<Dancer>;

class Dancer {
public:
    Dancer(int satisfaction, int id =0);

    uint16_t GetDivision() const;
    void SetDivision(const uint16_t &division);
    uint16_t GetPerformanceValue() const;
    void UpdateDivision(uint16_t new_division);
    void ProcessCompetitionResults(int16_t points, bool is_top_division);
    std::pair<uint16_t, uint16_t> GetPointsInDivision() const;
    int16_t GetSatisfaction() const;
    uint16_t GetId() const;
    QString DancerToString() const;
private:
    uint16_t id_;
    uint16_t skill_;
    int16_t satisfaction_;
    uint16_t points_ = 0;
    uint16_t division_ = 0;
};

#endif // DANCER_H
