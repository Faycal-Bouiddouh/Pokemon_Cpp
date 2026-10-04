/**
 * Unique database of all Pokemon in the game.
 *
 * The Pokedex is implemented as a singleton to ensure that only one database
 * is loaded by the application. It reads the CSV file, stores all Pokemon in a
 * collection, and provides a shared data source for the other classes.
 */

#ifndef POKEDEX_HPP
#define POKEDEX_HPP

#include <string>
#include <vector>
#include "SetOfPokemon.hpp"
#include "Pokemon.hpp"

class Pokedex : public SetOfPokemon {
private:
    // Loads the CSV file and fills the internal Pokemon collection.
    Pokedex(std::string fileName = "ressources/pokedex.csv");

    Pokedex(const Pokedex&) = delete;
    Pokedex& operator=(const Pokedex&) = delete;

public:
    // Returns the single Pokedex instance shared by the application.
    static Pokedex& getInstance();

    // Returns a copy of a Pokemon without modifying the source entry.
    Pokemon getClone(int targetId) const;

    // Selects random Pokemon, optionally excluding specified names.
    std::vector<Pokemon> getRandomPokemon(
        std::size_t count,
        const std::vector<std::string>& excludedNames = {}) const;
};

#endif
