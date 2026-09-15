/**
 * Rôle    : Déclaration du Pokedex (Design Pattern Singleton).
 * 
 * Fonctionnalités :
 * - Hérite de SetOfPokemon pour utiliser sa liste interne.
 * - Bloque l'instanciation multiple en rendant son constructeur privé.
 * - Déclare la méthode statique getInstance() permettant l'accès global.
 * - Déclare la méthode getClone() pour extraire des copies en lecture seule.
 */

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

