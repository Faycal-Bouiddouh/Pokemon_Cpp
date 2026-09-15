/**
 * Rôle    : Déclaration de la classe mère SetOfPokemon.
 * 
 * Fonctionnalités :
 * - Sert de base (héritage) pour toutes les classes gérant des listes de Pokémon.
 * - Définit la structure de données commune : un vecteur protégé de Pokémon.
 * - Déclare les méthodes virtuelles de recherche qui pourront être redéfinies.
 */

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