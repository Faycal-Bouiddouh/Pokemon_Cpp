#ifndef SETOFPOKEMON_HPP
#define SETOFPOKEMON_HPP

#include <string>
#include <vector>
#include "Pokemon.hpp"

using std::string;
using std::vector;

class SetOfPokemon {
protected:
    vector<Pokemon> pokemonList;

public:
    virtual Pokemon getPokemonWithId(const Pokemon& p);
    virtual Pokemon getPokemonWithName(const Pokemon& p);
    void displayAllPokemon() const;
};

#endif