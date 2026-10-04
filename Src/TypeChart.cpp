#include "TypeChart.hpp"

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace {
struct TypeMatchups {
    std::vector<std::string> superEffective;
    std::vector<std::string> notVeryEffective;
    std::vector<std::string> noEffect;
};

const std::unordered_map<std::string, TypeMatchups>& getTypeMatchups() {
    static const std::unordered_map<std::string, TypeMatchups> chart = {
        {"Normal", {{}, {"Rock", "Steel"}, {"Ghost"}}},
        {"Fire", {{"Grass", "Ice", "Bug", "Steel"}, {"Fire", "Water", "Rock", "Dragon"}, {}}},
        {"Water", {{"Fire", "Ground", "Rock"}, {"Water", "Grass", "Dragon"}, {}}},
        {"Electric", {{"Water", "Flying"}, {"Electric", "Grass", "Dragon"}, {"Ground"}}},
        {"Grass", {{"Water", "Ground", "Rock"}, {"Fire", "Grass", "Poison", "Flying", "Bug", "Dragon", "Steel"}, {}}},
        {"Ice", {{"Grass", "Ground", "Flying", "Dragon"}, {"Fire", "Water", "Ice", "Steel"}, {}}},
        {"Fighting", {{"Normal", "Ice", "Rock", "Dark", "Steel"}, {"Poison", "Flying", "Psychic", "Bug", "Fairy"}, {"Ghost"}}},
        {"Poison", {{"Grass", "Fairy"}, {"Poison", "Ground", "Rock", "Ghost"}, {"Steel"}}},
        {"Ground", {{"Fire", "Electric", "Poison", "Rock", "Steel"}, {"Grass", "Bug"}, {"Flying"}}},
        {"Flying", {{"Grass", "Fighting", "Bug"}, {"Electric", "Rock", "Steel"}, {}}},
        {"Psychic", {{"Fighting", "Poison"}, {"Psychic", "Steel"}, {"Dark"}}},
        {"Bug", {{"Grass", "Psychic", "Dark"}, {"Fire", "Fighting", "Poison", "Flying", "Ghost", "Steel", "Fairy"}, {}}},
        {"Rock", {{"Fire", "Ice", "Flying", "Bug"}, {"Fighting", "Ground", "Steel"}, {}}},
        {"Ghost", {{"Psychic", "Ghost"}, {"Dark"}, {"Normal"}}},
        {"Dragon", {{"Dragon"}, {"Steel"}, {"Fairy"}}},
        {"Dark", {{"Psychic", "Ghost"}, {"Fighting", "Dark", "Fairy"}, {}}},
        {"Steel", {{"Ice", "Rock", "Fairy"}, {"Fire", "Water", "Electric", "Steel"}, {}}},
        {"Fairy", {{"Fighting", "Dragon", "Dark"}, {"Fire", "Poison", "Steel"}, {}}}
    };
    return chart;
}
}

double calculateTypeEffectiveness(const std::string& attackingType, const std::string& defendingType) {
    const auto& matchups = getTypeMatchups();
    const auto matchup = matchups.find(attackingType);
    if (matchup == matchups.end()) {
        return 1.0;
    }

    const TypeMatchups& typeMatchup = matchup->second;
    if (std::find(typeMatchup.noEffect.begin(), typeMatchup.noEffect.end(), defendingType) != typeMatchup.noEffect.end()) {
        return 0.0;
    }
    if (std::find(typeMatchup.superEffective.begin(), typeMatchup.superEffective.end(), defendingType) != typeMatchup.superEffective.end()) {
        return 2.0;
    }
    if (std::find(typeMatchup.notVeryEffective.begin(), typeMatchup.notVeryEffective.end(), defendingType) != typeMatchup.notVeryEffective.end()) {
        return 0.5;
    }
    return 1.0;
}