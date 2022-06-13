#include "chromosome.hh"

class ClimbChromosome : public Chromosome
{
public:
    ClimbChromosome(const Cities *cities_ptr)
        : Chromosome(cities_ptr)
    {
    }

    virtual ~ClimbChromosome() = default;

    // local hill climbing: searches for the best solution in a small local “neighborhood” of the current chromosome
    virtual void mutate() override;

    // Polymorphic creation method from an existing Chromosome.
    // This method allocates memory for the newly created chromosome.
    // It is the caller's responsibility to free this memory.
    virtual Chromosome *clone() const override;

protected:
    ClimbChromosome(const ClimbChromosome &) = default;
    ClimbChromosome(ClimbChromosome &&) = default;
    ClimbChromosome &operator=(const ClimbChromosome &) = default;
    ClimbChromosome &operator=(ClimbChromosome &&) = default;
};