#include <algorithm>
#include <string>
#include <vector>

#include "hero.h"

// Restricted constructor, creates the Hero with specified id
// Create a empty Hero placeholder if no hero with such id
Hero::Hero(uint32_t id, std::string code_name, std::string formated_name, std::string tag_name) :
  id_{ id },
  code_name_{ code_name },
  formated_name_{ formated_name },
  tag_name_{ tag_name }
{
}

// Copy constructor
Hero::Hero(const Hero& hero) :
  id_{ hero.GetId() },
  code_name_{ hero.GetCodeName() },
  formated_name_{ hero.GetFormatedName() },
  tag_name_{ hero.GetTagName() }
{
}

// Only public constructor
// Creates the Hero with specified id
// Create a empty Hero placeholder if no hero with such id
Hero::Hero(uint32_t id) {
  auto result = std::find_if(Hero::heroes_.begin(),
    Hero::heroes_.end(),
    [&id](const Hero& hero) { return hero.GetId() == id; });
  if (result != Hero::heroes_.end()) {
    id_ = result->GetId();
    code_name_ = result->GetCodeName();
    formated_name_ = result->GetFormatedName();
    tag_name_ = result->GetTagName();
  }
  else {
    id_ = Hero::heroes_[0].GetId();
    code_name_ = Hero::heroes_[0].GetCodeName();
    formated_name_ = Hero::heroes_[0].GetFormatedName();
    tag_name_ = Hero::heroes_[0].GetTagName();
  }
}

// All valid heroes
std::vector<Hero> Hero::heroes_ = {
  { 0, "empty", "Empty", "empty" },
  { 1, "npc_dota_hero_antimage", "Anti-Mage", "am" },
  { 2, "npc_dota_hero_axe", "Axe", "axe" },
  { 3, "npc_dota_hero_bane", "Bane", "bane" },
  { 4, "npc_dota_hero_bloodseeker", "Bloodseeker", "bs" },
  { 5, "npc_dota_hero_crystal_maiden", "Crystal Maiden", "cm" },
  { 6, "npc_dota_hero_drow_ranger", "Drow Ranger", "drow" },
  { 7, "npc_dota_hero_earthshaker", "Earthshaker", "shaker" },
  { 8, "npc_dota_hero_juggernaut", "Juggernaut", "jugger" },
  { 9, "npc_dota_hero_mirana", "Mirana", "mirana" },
  { 10, "npc_dota_hero_morphling", "Morphling", "morph" },
  { 11, "npc_dota_hero_nevermore", "Shadow Fiend", "sf" },
  { 12, "npc_dota_hero_phantom_lancer", "Phantom Lancer", "pl" },
  { 13, "npc_dota_hero_puck", "Puck", "puck" },
  { 14, "npc_dota_hero_pudge", "Pudge", "pudge" },
  { 15, "npc_dota_hero_razor", "Razor", "razor" },
  { 16, "npc_dota_hero_sand_king", "Sand King", "sk" },
  { 17, "npc_dota_hero_storm_spirit", "Storm Spirit", "storm" },
  { 18, "npc_dota_hero_sven", "Sven", "sven" },
  { 19, "npc_dota_hero_tiny", "Tiny", "tiny" },
  { 20, "npc_dota_hero_vengefulspirit", "Vengeful Spirit", "venge" },
  { 21, "npc_dota_hero_windrunner", "Windranger", "wind" },
  { 22, "npc_dota_hero_zuus", "Zeus", "zeus" },
  { 23, "npc_dota_hero_kunkka", "Kunkka", "kunkka" },
  { 25, "npc_dota_hero_lina", "Lina", "lina" },
  { 26, "npc_dota_hero_lion", "Lion", "lion" },
  { 27, "npc_dota_hero_shadow_shaman", "Shadow Shaman", "shaman" },
  { 28, "npc_dota_hero_slardar", "Slardar", "slardar" },
  { 29, "npc_dota_hero_tidehunter", "Tidehunter", "tide" },
  { 30, "npc_dota_hero_witch_doctor", "Witch Doctor", "wd" },
  { 31, "npc_dota_hero_lich", "Lich", "lich" },
  { 32, "npc_dota_hero_riki", "Riki", "riki" },
  { 33, "npc_dota_hero_enigma", "Enigma", "enigma" },
  { 34, "npc_dota_hero_tinker", "Tinker", "tinker" },
  { 35, "npc_dota_hero_sniper", "Sniper", "sniper" },
  { 36, "npc_dota_hero_necrolyte", "Necrophos", "necro" },
  { 37, "npc_dota_hero_warlock", "Warlock", "wl" },
  { 38, "npc_dota_hero_beastmaster", "Beastmaster", "bm" },
  { 39, "npc_dota_hero_queenofpain", "Queen of Pain", "qop" },
  { 40, "npc_dota_hero_venomancer", "Venomancer", "veno" },
  { 41, "npc_dota_hero_faceless_void", "Faceless Void", "void" },
  { 42, "npc_dota_hero_skeleton_king", "Wraith King", "wk" },
  { 43, "npc_dota_hero_death_prophet", "Death Prophet", "dp" },
  { 44, "npc_dota_hero_phantom_assassin", "Phantom Assassin", "pa" },
  { 45, "npc_dota_hero_pugna", "Pugna", "pugna" },
  { 46, "npc_dota_hero_templar_assassin", "Templar Assassin", "ta" },
  { 47, "npc_dota_hero_viper", "Viper", "viper" },
  { 48, "npc_dota_hero_luna", "Luna", "luna" },
  { 49, "npc_dota_hero_dragon_knight", "Dragon Knight", "dk" },
  { 50, "npc_dota_hero_dazzle", "Dazzle", "dazzle" },
  { 51, "npc_dota_hero_rattletrap", "Clockwerk", "clock" },
  { 52, "npc_dota_hero_leshrac", "Leshrac", "lesh" },
  { 53, "npc_dota_hero_furion", "Nature\'s Prophet", "np" },
  { 54, "npc_dota_hero_life_stealer", "Lifestealer", "naix" },
  { 55, "npc_dota_hero_dark_seer", "Dark Seer", "ds" },
  { 56, "npc_dota_hero_clinkz", "Clinkz", "clinkz" },
  { 57, "npc_dota_hero_omniknight", "Omniknight", "omni" },
  { 58, "npc_dota_hero_enchantress", "Enchantress", "enchant" },
  { 59, "npc_dota_hero_huskar", "Huskar", "huskar" },
  { 60, "npc_dota_hero_night_stalker", "Night Stalker", "ns" },
  { 61, "npc_dota_hero_broodmother", "Broodmother", "brood" },
  { 62, "npc_dota_hero_bounty_hunter", "Bounty Hunter", "bh" },
  { 63, "npc_dota_hero_weaver", "Weaver", "weaver" },
  { 64, "npc_dota_hero_jakiro", "Jakiro", "jaki" },
  { 65, "npc_dota_hero_batrider", "Batrider", "bat" },
  { 66, "npc_dota_hero_chen", "Chen", "chen" },
  { 67, "npc_dota_hero_spectre", "Spectre", "spectre" },
  { 68, "npc_dota_hero_ancient_apparition", "Ancient Apparition", "aa" },
  { 69, "npc_dota_hero_doom_bringer", "Doom", "doom" },
  { 70, "npc_dota_hero_ursa", "Ursa", "ursa" },
  { 71, "npc_dota_hero_spirit_breaker", "Spirit Breaker", "sb" },
  { 72, "npc_dota_hero_gyrocopter", "Gyrocopter", "gyro" },
  { 73, "npc_dota_hero_alchemist", "Alchemist", "alche" },
  { 74, "npc_dota_hero_invoker", "Invoker", "invo" },
  { 75, "npc_dota_hero_silencer", "Silencer", "sile" },
  { 76, "npc_dota_hero_obsidian_destroyer", "Outworld Devourer", "od" },
  { 77, "npc_dota_hero_lycan", "Lycan", "lycan" },
  { 78, "npc_dota_hero_brewmaster", "Brewmaster", "brew" },
  { 79, "npc_dota_hero_shadow_demon", "Shadow Demon", "sd" },
  { 80, "npc_dota_hero_lone_druid", "Lone Druid", "ld" },
  { 81, "npc_dota_hero_chaos_knight", "Chaos Knight", "ck" },
  { 82, "npc_dota_hero_meepo", "Meepo", "meepo" },
  { 83, "npc_dota_hero_treant", "Treant Protector", "treant" },
  { 84, "npc_dota_hero_ogre_magi", "Ogre Magi", "ogre" },
  { 85, "npc_dota_hero_undying", "Undying", "ud" },
  { 86, "npc_dota_hero_rubick", "Rubick", "rub" },
  { 87, "npc_dota_hero_disruptor", "Disruptor", "disru" },
  { 88, "npc_dota_hero_nyx_assassin", "Nyx Assassin", "nyx" },
  { 89, "npc_dota_hero_naga_siren", "Naga Siren", "naga" },
  { 90, "npc_dota_hero_keeper_of_the_light", "Keeper of the Light", "kotl" },
  { 91, "npc_dota_hero_wisp", "Io","io" },
  { 92, "npc_dota_hero_visage", "Visage", "visage" },
  { 93, "npc_dota_hero_slark", "Slark", "slark" },
  { 94, "npc_dota_hero_medusa", "Medusa", "medusa" },
  { 95, "npc_dota_hero_troll_warlord", "Troll Warlord", "troll" },
  { 96, "npc_dota_hero_centaur", "Centaur Warrunner", "centaur" },
  { 97, "npc_dota_hero_magnataur", "Magnus", "mag" },
  { 98, "npc_dota_hero_shredder", "Timbersaw", "timber" },
  { 99, "npc_dota_hero_bristleback", "Bristleback", "bristle" },
  { 100, "npc_dota_hero_tusk", "Tusk", "tusk" },
  { 101, "npc_dota_hero_skywrath_mage", "Skywrath Mage", "sky" },
  { 102, "npc_dota_hero_abaddon", "Abaddon", "aba" },
  { 103, "npc_dota_hero_elder_titan", "Elder Titan", "et" },
  { 104, "npc_dota_hero_legion_commander", "Legion Commander", "legion" },
  { 105, "npc_dota_hero_techies", "Techies", "techies" },
  { 106, "npc_dota_hero_ember_spirit", "Ember Spirit", "ember" },
  { 107, "npc_dota_hero_earth_spirit", "Earth Spirit", "es" },
  { 108, "npc_dota_hero_abyssal_underlord", "Underlord", "ul" },
  { 109, "npc_dota_hero_terrorblade", "Terrorblade", "tb" },
  { 110, "npc_dota_hero_phoenix", "Phoenix", "phoenix" },
  { 111, "npc_dota_hero_oracle", "Oracle", "oracle" },
  { 112, "npc_dota_hero_winter_wyvern", "Winter Wyvern", "ww" },
  { 113, "npc_dota_hero_arc_warden", "Arc Warden", "aw" },
  { 114, "npc_dota_hero_monkey_king", "Monkey King", "mk" },
  { 119, "npc_dota_hero_dark_willow", "Dark Willow", "dw" },
  { 120, "npc_dota_hero_pangolier", "Pangolier", "pango" },
  { 121, "npc_dota_hero_grimstroke", "Grimstroke", "grim" },
  { 129, "npc_dota_hero_mars", "Mars", "mars" }
};
