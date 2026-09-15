#  Projet Pokémon C++

Ce projet académique développé en C++ modélise un système de gestion de Pokémon. Il implémente des concepts avancés de la programmation orientée objet (POO) pour gérer une base de données de Pokémon, un système de stockage (PC) et l'équipe active d'un dresseur.

##  Fonctionnalités

*   **Pokédex (Singleton) :** Chargement automatique des statistiques des Pokémon depuis un fichier `pokedex.csv`. Implémentation du *Design Pattern Singleton* pour garantir une instance unique de la base de données.
*   **Pokeball (PC de stockage) :** Boîte permettant de stocker les Pokémon capturés.
*   **PokemonParty (Équipe) :** Gestion de l'équipe du joueur (limitée à 6 Pokémon).
*   **Logique de transfert :** Mécanisme de déplacement réaliste. L'ajout d'un Pokémon dans l'équipe le retire automatiquement du PC de stockage.
*   **Moteur Graphique :** Environnement configuré avec **CMake** pour une intégration de la bibliothèque **SFML 3**.

##  Architecture du Projet


```text
📁 Pokemon_C++
 ├── 📁 Include/          # Fichiers d'en-tête (.hpp)
 │    ├── Pokeball.hpp
 │    ├── Pokedex.hpp
 │    ├── Pokemon.hpp
 │    ├── PokemonParty.hpp
 │    └── SetOfPokemon.hpp
 ├── 📁 Src/              # Code source de l'application (.cpp)
 │    ├── main.cpp
 │    └── ... 
 ├── 📁 ressources/       # Base de données
 │    └── pokedex.csv
 ├── 📄 CMakeLists.txt    # Configuration de compilation CMake
 └── 📄 .gitignore        # Règles d'exclusion pour GitHub