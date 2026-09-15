/**
 * Rôle    : Déclaration de la classe Pokeball (le "PC" du joueur).
 * 
 * Fonctionnalités :
 * - Hérite de SetOfPokemon pour représenter une boîte de stockage.
 * - Déclare la méthode addPokemon() pour y ranger de nouveaux Pokémon.
 * - Signale (via override) la redéfinition des méthodes de récupération pour 
 *   modifier leur comportement standard.
 */

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