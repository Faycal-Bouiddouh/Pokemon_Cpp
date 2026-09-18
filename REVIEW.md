# Revue de code : Pokemon_Cpp

**Projet relu :** [Faycal-ensea/Pokemon_Cpp](https://github.com/Faycal-ensea/Pokemon_Cpp)
**Auteur :** Fayçal Bouiddouh
**Relecteur :** Loïc Aron Mbassi Ewolo
**Commit relu :** `150500b`
**Date :** 17 septembre 2026

J’ai aussi laissé quelques `// REVIEW` directement dans le code.

## Compilation

J’ai d’abord eu quelques problèmes pour compiler le projet avec le `CMakeLists.txt`.

Tu demandes SFML 3 alors que la commande donnée dans le sujet m’installe la 2.5. En plus, je n’ai pas trouvé d’utilisation de SFML dans le code pour l’instant. Je pense donc que tu peux simplement retirer la dépendance et la remettre quand tu commenceras l’interface.

Il y avait aussi `<windows.h>` inclus directement dans `main.cpp`, donc ça ne compilait pas sous Linux. J’ai mis un `#ifdef _WIN32` autour dans ma branche.

Pour tester le projet, j’ai finalement compilé avec :

```bash
g++ -std=c++17 -Wall -I Include Src/*.cpp -o build/Pokemon
cd build && ./Pokemon
```

Il faut aussi lancer le programme depuis `build/`, sinon le chemin vers le CSV ne fonctionne plus. J’en reparle plus bas.

## Par rapport au sujet

Dans l’ensemble, la structure du projet est claire avec `Include/`, `Src/` et `ressources/`.

Le polymorphisme est préparé avec les `virtual` et `override`, même si pour l’instant tu utilises surtout les classes directement et pas vraiment via `SetOfPokemon`.

Les vecteurs, `auto`, les itérateurs et le Singleton sont bien présents.

Par contre, je n’ai pas vu de smart pointer ni de gestion d’exception. Pour les exceptions, le chargement du CSV serait justement un bon endroit pour en ajouter.

Il manque aussi le diagramme de classe demandé dans le sujet.

## Quelques problèmes que j’ai trouvés

Le premier concerne `NumberOfPokemon`. Ton constructeur normal incrémente le compteur et le destructeur le décrémente, mais le constructeur de copie ne l’incrémente pas.

Comme les `Pokemon` sont beaucoup copiés dans les vecteurs, le compteur finit par devenir négatif. Chez moi j’ai obtenu :

```text
Pokemon vivants : -1026
```

Ajouter `++NumberOfPokemon` dans le constructeur de copie devrait régler le problème.

J’ai aussi eu ces warnings :

```text
Src/Pokedex.cpp:69:1: warning: control reaches end of non-void function
Src/SetOfPokemon.cpp:22:1: warning: control reaches end of non-void function
Src/SetOfPokemon.cpp:30:1: warning: control reaches end of non-void function
```

Ça vient de `getPokemonWithId`, `getPokemonWithName` et `getClone`. Si le Pokémon n’est pas trouvé, la fonction arrive à la fin sans rien retourner.

Je pense que ce serait justement un bon endroit pour lancer une exception, par exemple :

```cpp
throw std::runtime_error("Pokemon introuvable");
```

Même chose pour le chargement du CSV. Actuellement, si le fichier n’est pas trouvé, le constructeur affiche une erreur mais le programme continue avec un Pokedex vide.

En lançant depuis la racine, j’ai par exemple eu :

```text
File ../ressources/pokedex.csv not found
terminate called after throwing an instance of 'std::bad_alloc'
```

Il y a aussi un petit problème dans `PokemonParty::addPokemon`.

Pour chercher un Pokémon par id, tu crées un faux Pokémon :

```cpp
Pokemon Search_test(targetId, "Search", "", "", 0, 0, 0, 0, 0, 0, 0, 0, false);
```

Si la recherche échoue, cet objet peut finir dans l’équipe. J’ai réussi à me retrouver avec :

```text
****** Search ******
Id : 25
HitPoint : 0
Attack : 0
Defense : 0
```

Si la recherche échoue, je trouve que ce serait plus propre de ne pas renvoyer le Pokémon temporaire. Je mettrais plutôt un `std::optional<Pokemon>` en retour, comme ça l’appelant peut vérifier si un Pokémon a vraiment été trouvé avant de l’ajouter à l’équipe.

J’en profiterais aussi pour passer directement l’id à la fonction :

```cpp
std::optional<Pokemon> getPokemonWithId(int id);
```

Ça évite de construire un Pokémon complet juste pour transporter un id, et ça règle aussi le problème du "Search" qui peut finir dans l’équipe.

Autre petit point : `SetOfPokemon` a des méthodes virtuelles mais pas de destructeur virtuel. J’ajouterais simplement :

```cpp
virtual ~SetOfPokemon() = default;
```

Enfin, il y a deux chemins différents pour le CSV :

```text
ressources/pokedex.csv
../ressources/pokedex.csv
```

Ça explique pourquoi le programme dépend du dossier depuis lequel on le lance. Il faudrait au moins utiliser le même chemin partout.

## `Battle()`

J’ai trouvé dommage que `Battle()` ne soit jamais appelée dans le `main`.

C’est quand même une des parties les plus intéressantes du projet : tu prends en compte la vitesse, l’attaque, la défense, les PV et les KO.

Je mettrais juste un petit combat à la fin du `main` pour montrer que cette partie fonctionne.

## Quelques détails

J’éviterais les `using std::string` et `using std::vector` directement dans les `.hpp`.

Dans le constructeur de copie de `Pokemon`, l’ordre de la liste d’initialisation ne correspond pas à l’ordre de déclaration des attributs. Ça ne casse rien ici, mais `g++` le signale.

Le nommage change aussi un peu selon les endroits : `Battle`, `Total`, `Search_test`, puis du camelCase ailleurs. Ce serait plus propre de garder la même convention partout.

Pour les getters de chaînes comme `getName()`, tu peux aussi retourner une `const string&` plutôt que recopier la chaîne à chaque appel.

J’ai aussi remarqué que certains ids du CSV correspondent à plusieurs formes de Pokémon, par exemple Rotom. Une recherche uniquement par id retournera donc toujours la première forme trouvée.

## Méthode ajoutée

J’ai ajouté une méthode `sortBy` dans `SetOfPokemon` :

```cpp
void sortBy(const std::function<bool(const Pokemon&, const Pokemon&)>& comparator);
```

Elle permet de trier n’importe quelle collection de Pokémon avec le critère qu’on veut.

Par exemple, pour trier l’équipe par vitesse :

```cpp
monEquipe.sortBy([](const Pokemon& a, const Pokemon& b) {
    return a.getSpeed() > b.getSpeed();
});
```

Je l’ai mise dans `SetOfPokemon`, donc elle peut servir pour le Pokedex, la Pokeball ou l’équipe.

## Ce que j’ai bien aimé

Le Singleton du Pokedex est bien fait. Le `static` local dans `getInstance()` est simple et évite de compliquer inutilement le code.

Tu as aussi bien empêché la copie du Pokedex avec :

```cpp
Pokedex(const Pokedex&) = delete;
```

`getClone()` colle bien à l’idée du sujet aussi : le Pokedex garde ses données et renvoie des copies.

Le parsing du CSV fonctionne bien avec le fichier actuel, et les commentaires au début des `.hpp` et `.cpp` m’ont aidé à comprendre rapidement le rôle de chaque fichier.

Enfin, dans `Pokeball::getPokemonWithId`, l’utilisation de l’itérateur avec `erase` est propre.
