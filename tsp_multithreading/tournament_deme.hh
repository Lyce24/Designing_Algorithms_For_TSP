#include "deme.hh"

using namespace std;

class TournamentDeme : public Deme
{
public:
    TournamentDeme(const Cities *cities_ptr, unsigned pop_size, double mut_rate)
        : Deme(cities_ptr, pop_size, mut_rate)
    {
    }

    virtual ~TournamentDeme() = default;
    // selecting chromosome based on the result of the tournament
    virtual Chromosome *select_parent() override;
};