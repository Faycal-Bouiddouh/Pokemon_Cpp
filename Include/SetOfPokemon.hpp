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
#include <functional>
#include "Pokemon.hpp"

using std::string;
using std::vector;

class SetOfPokemon {
protected:
    vector<Pokemon> pokemonList;

public:
    // REVIEW : Comme SetOfPokemon a des méthodes virtual, j'ajouterais aussi un destructeur
    // virtuel. Ça évitera des problèmes si un objet dérivé est un jour supprimé via un
    // SetOfPokemon*.
    // virtual ~SetOfPokemon() = default;
    virtual Pokemon getPokemonWithId(const Pokemon& p);
    virtual Pokemon getPokemonWithName(const Pokemon& p);
    void displayAllPokemon() const;

    // AJOUT REVUE : méthode ajoutée pour le point 1.4 du sujet.
    // Elle permet de trier les Pokémon avec le critère qu'on veut, par exemple la vitesse.
    void sortBy(const std::function<bool(const Pokemon&, const Pokemon&)>& comparator);
};

#endif