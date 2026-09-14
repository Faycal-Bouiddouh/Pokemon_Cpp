#ifndef POKEDEX_HPP
#define POKEDEX_HPP

#include <string>
#include "SetOfPokemon.hpp"
#include "Pokemon.hpp"

class Pokedex : public SetOfPokemon {
private:
    Pokedex(std::string fileName = "ressources/pokedex.csv");

    Pokedex(const Pokedex&) = delete;
    Pokedex& operator=(const Pokedex&) = delete;

public:
    static Pokedex& getInstance();

    Pokemon getClone(int targetId) const;
};

#endif

