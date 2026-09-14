#ifndef POKEBALL_HPP
#define POKEBALL_HPP

#include "SetOfPokemon.hpp"

class Pokeball : public SetOfPokemon {
public:
    Pokeball();

    void addPokemon(const Pokemon& p);

    Pokemon getPokemonWithId(const Pokemon& p) override;
    Pokemon getPokemonWithName(const Pokemon& p) override;
};

#endif