/**
 * Represents the player's PC storage.
 *
 * The PC stores Pokemon outside the active team. It supports adding, extracting,
 * and transferring Pokemon between storage and the active team.
 */

#ifndef POKEBALL_HPP
#define POKEBALL_HPP

#include "SetOfPokemon.hpp"

class Pokeball : public SetOfPokemon {
public:
    // Creates empty storage ready to hold Pokemon.
    Pokeball();

    // Adds a Pokemon to the PC without removing it from its original location.
    void addPokemon(const Pokemon& p);

    // Removes a Pokemon from the PC by ID and returns it to the caller.
    Pokemon takePokemonById(int id);

    // Removes a Pokemon from the PC by name.
    Pokemon takePokemonByName(const string& name);
};

#endif