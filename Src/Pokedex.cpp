/**
 * Purpose: Implements the Pokedex database.
 *
 * Features:
 * - Opens, reads, and safely parses the pokedex.csv file.
 * - Converts CSV rows into Pokemon objects in the internal collection.
 * - Provides copies of stored Pokemon so the source database is not modified.
 */

#include "Pokedex.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <optional>
#include <random>
#include <vector>

using namespace std;

namespace {
constexpr size_t expectedColumnCount = 13;

// Searches the current directory and its parent directories for the CSV file.
filesystem::path resolvePokedexPath(const string& fileName) {
    const filesystem::path requestedPath(fileName);
    if (filesystem::exists(requestedPath)) {
        return requestedPath;
    }

    const filesystem::path fallbackPath = filesystem::current_path() / ".." / "ressources" / "pokedex.csv";
    if (filesystem::exists(fallbackPath)) {
        return fallbackPath;
    }

    throw runtime_error("Erreur critique : Fichier " + fileName + " introuvable.");
}

// Splits a CSV row into columns containing Pokemon data.
vector<string> splitCsvLine(const string& line) {
    stringstream lineStream(line);
    string cell;
    vector<string> columns;
    while (getline(lineStream, cell, ',')) {
        columns.push_back(cell);
    }
    return columns;
}

// Converts parsed columns into a Pokemon object.
Pokemon createPokemon(const vector<string>& columns) {
    return Pokemon(
        stoi(columns.at(0)),
        columns.at(1),
        columns.at(2),
        columns.at(3),
        stod(columns.at(4)),
        stod(columns.at(5)),
        stod(columns.at(6)),
        stod(columns.at(7)),
        stod(columns.at(8)),
        stod(columns.at(9)),
        stod(columns.at(10)),
        stoi(columns.at(11)),
        columns.at(12) == "True" || columns.at(12) == "true"
    );
}

optional<Pokemon> parsePokemonRow(const string& line) {
    const vector<string> columns = splitCsvLine(line);
    if (columns.size() < expectedColumnCount) {
        return nullopt;
    }
    return createPokemon(columns);
}

vector<Pokemon> loadPokemonData(const filesystem::path& path) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Erreur critique : Fichier " + path.string() + " inaccessible.");
    }

    string line;
    getline(file, line);
    vector<Pokemon> pokemonList;
    while (getline(file, line)) {
        const optional<Pokemon> pokemon = parsePokemonRow(line);
        if (pokemon.has_value()) {
            pokemonList.push_back(*pokemon);
        }
    }
    return pokemonList;
}
}

// Returns the single Pokedex instance used by the application.
Pokedex& Pokedex::getInstance() {
    static Pokedex instance("ressources/pokedex.csv");
    return instance;
}

// Reads the CSV file and loads all Pokemon into the internal database.
Pokedex::Pokedex(string fileName)
    : SetOfPokemon() {
    pokemonList = loadPokemonData(resolvePokedexPath(fileName));
}

// Returns a safe copy of a Pokemon without exposing the source entry.
Pokemon Pokedex::getClone(int targetId) const {
    const auto pokemon = find_if(pokemonList.begin(), pokemonList.end(), [targetId](const Pokemon& candidate) {
        return candidate.getId() == targetId;
    });
    if (pokemon == pokemonList.end()) {
        throw runtime_error("Pokemon avec l'ID " + to_string(targetId) + " introuvable dans le Pokedex.");
    }
    return *pokemon;
}

// Selects random Pokemon, optionally excluding specified names.
vector<Pokemon> Pokedex::getRandomPokemon(size_t count, const vector<string>& excludedNames) const {
    vector<Pokemon> choices;
    for (const Pokemon& pokemon : pokemonList) {
        if (find(excludedNames.begin(), excludedNames.end(), pokemon.getName()) == excludedNames.end()) {
            choices.push_back(pokemon);
        }
    }

    random_device randomDevice;
    mt19937 randomGenerator(randomDevice());
    shuffle(choices.begin(), choices.end(), randomGenerator);
    if (choices.size() > count) {
        choices.erase(choices.begin() + count, choices.end());
    }
    return choices;
}