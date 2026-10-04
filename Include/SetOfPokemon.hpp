/**
 * Abstract base class shared by all Pokemon collections.
 *
 * It centralizes storage in a vector and gives all classes in the hierarchy
 * a common interface for searching and sorting.
 */

#ifndef SETOFPOKEMON_HPP
#define SETOFPOKEMON_HPP

#include <functional>
#include <string>
#include <vector>
#include "Pokemon.hpp"
#include "PokemonVector.hpp"

using std::string;
using std::vector;

class SetOfPokemon : public PokemonVector {
protected:
    // Stores the Pokemon in a collection such as the PC, team, or Pokedex.
    vector<Pokemon> pokemonList;

public:
    // Destroys the collection without additional cleanup.
    ~SetOfPokemon() override = default;

    // Finds a Pokemon by ID and returns it by value.
    Pokemon findPokemonById(int id) const override;

    // Finds a Pokemon by its exact name.
    Pokemon findPokemonByName(const string& name) const override;

    // Provides read-only access to the internal collection.
    const vector<Pokemon>& getPokemonList() const override;

    // Displays all Pokemon in the collection.
    void displayAllPokemon() const override;

    // Sorts the collection using a comparator supplied by the caller.
    void sortBy(const std::function<bool(const Pokemon&, const Pokemon&)>& comparator) override;
};

#endif