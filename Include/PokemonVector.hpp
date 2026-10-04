/**
 * Abstract interface for all Pokemon collections.
 *
 * This class defines common operations for all storage collections: searching,
 * access, display, and sorting. It is the basis for polymorphism in the project.
 */

#ifndef POKEMON_VECTOR_HPP
#define POKEMON_VECTOR_HPP

#include <functional>
#include <string>
#include <vector>

#include "Pokemon.hpp"

class PokemonVector {
public:
    // Destroys the abstract instance and its derived classes safely.
    virtual ~PokemonVector() = default;

    // Finds a Pokemon by ID.
    virtual Pokemon findPokemonById(int id) const = 0;

    // Finds a Pokemon by its exact name.
    virtual Pokemon findPokemonByName(const std::string& name) const = 0;

    // Provides read-only access to the internal collection.
    virtual const std::vector<Pokemon>& getPokemonList() const = 0;

    // Displays the collection contents.
    virtual void displayAllPokemon() const = 0;

    // Sorts the collection using an external comparison rule.
    virtual void sortBy(const std::function<bool(const Pokemon&, const Pokemon&)>& comparator) = 0;
};

#endif
