#include <algorithm>
#include <string>
#include <vector>

#include "hero.h"


Hero::Hero(int32_t id, std::string name, std::string localized_name) :
	id_(id), name_(name), localized_name_(localized_name)
{

}

const Hero& Hero::FindHeroById(int32_t id) {
	 auto result = std::find_if(Hero::heros_.begin(), Hero::heros_.end(), [&id](const Hero& hero) { return hero.GetId() == id; });
	 if (result != Hero::heros_.end()) {
		 return *result;
	 }
	 else {
		 return Hero::heros_[0];
	 }
}

const Hero& Hero::FindHeroByName() {
	return Hero(0, "a", "a");
}

const Hero& Hero::FindHeroByLocalizedName() {
	return Hero(0, "a", "a");
}

const std::vector<Hero> Hero::heros_ = {
	Hero(0, "empty", "Empty"),
	Hero(1, "npc_dota_hero_antimage", "Anti-Mage"),
	Hero(2, "npc_dota_hero_axe", "Axe"),
	Hero(3, "npc_dota_hero_bane", "Bane"),
	Hero(4, "npc_dota_hero_bloodseeker", "Bloodseeker"),
	Hero(5, "npc_dota_hero_crystal_maiden", "Crystal Maiden"),
	Hero(6, "npc_dota_hero_drow_ranger", "Drow Ranger"),
	Hero(7, "npc_dota_hero_earthshaker", "Earthshaker"),
	Hero(8, "npc_dota_hero_juggernaut", "Juggernaut"),
	Hero(9, "npc_dota_hero_mirana", "Mirana"),
	Hero(10, "npc_dota_hero_morphling", "Morphling"),
	Hero(11, "npc_dota_hero_nevermore", "Shadow Fiend"),
	Hero(12, "npc_dota_hero_phantom_lancer", "Phantom Lancer"),
	Hero(13, "npc_dota_hero_puck", "Puck"),
	Hero(14, "npc_dota_hero_pudge", "Pudge"),
	Hero(15, "npc_dota_hero_razor", "Razor"),
	Hero(16, "npc_dota_hero_sand_king", "Sand King"),
	Hero(17, "npc_dota_hero_storm_spirit", "Storm Spirit"),
	Hero(18, "npc_dota_hero_sven", "Sven"),
	Hero(19, "npc_dota_hero_tiny", "Tiny"),
	Hero(20, "npc_dota_hero_vengefulspirit", "Vengeful Spirit"),
	Hero(21, "npc_dota_hero_windrunner", "Windranger"),
	Hero(22, "npc_dota_hero_zuus", "Zeus"),
	Hero(23, "npc_dota_hero_kunkka", "Kunkka"),
	Hero(25, "npc_dota_hero_lina", "Lina"),
	Hero(26, "npc_dota_hero_lion", "Lion"),
	Hero(27, "npc_dota_hero_shadow_shaman", "Shadow Shaman"),
	Hero(28, "npc_dota_hero_slardar", "Slardar"),
	Hero(29, "npc_dota_hero_tidehunter", "Tidehunter"),
	Hero(30, "npc_dota_hero_witch_doctor", "Witch Doctor"),
	Hero(31, "npc_dota_hero_lich", "Lich"),
	Hero(32, "npc_dota_hero_riki", "Riki"),
	Hero(33, "npc_dota_hero_enigma", "Enigma"),
	Hero(34, "npc_dota_hero_tinker", "Tinker"),
	Hero(35, "npc_dota_hero_sniper", "Sniper"),
	Hero(36, "npc_dota_hero_necrolyte", "Necrophos"),
	Hero(37, "npc_dota_hero_warlock", "Warlock"),
	Hero(38, "npc_dota_hero_beastmaster", "Beastmaster"),
	Hero(39, "npc_dota_hero_queenofpain", "Queen of Pain"),
	Hero(40, "npc_dota_hero_venomancer", "Venomancer"),
	Hero(41, "npc_dota_hero_faceless_void", "Faceless Void"),
	Hero(42, "npc_dota_hero_skeleton_king", "Wraith King"),
	Hero(43, "npc_dota_hero_death_prophet", "Death Prophet"),
	Hero(44, "npc_dota_hero_phantom_assassin", "Phantom Assassin"),
	Hero(45, "npc_dota_hero_pugna", "Pugna"),
	Hero(46, "npc_dota_hero_templar_assassin", "Templar Assassin"),
	Hero(47, "npc_dota_hero_viper", "Viper"),
	Hero(48, "npc_dota_hero_luna", "Luna"),
	Hero(49, "npc_dota_hero_dragon_knight", "Dragon Knight"),
	Hero(50, "npc_dota_hero_dazzle", "Dazzle"),
	Hero(51, "npc_dota_hero_rattletrap", "Clockwerk"),
	Hero(52, "npc_dota_hero_leshrac", "Leshrac"),
	Hero(53, "npc_dota_hero_furion", "Nature\'s Prophet"),
	Hero(54, "npc_dota_hero_life_stealer", "Lifestealer"),
	Hero(55, "npc_dota_hero_dark_seer", "Dark Seer"),
	Hero(56, "npc_dota_hero_clinkz", "Clinkz"),
	Hero(57, "npc_dota_hero_omniknight", "Omniknight"),
	Hero(58, "npc_dota_hero_enchantress", "Enchantress"),
	Hero(59, "npc_dota_hero_huskar", "Huskar"),
	Hero(60, "npc_dota_hero_night_stalker", "Night Stalker"),
	Hero(61, "npc_dota_hero_broodmother", "Broodmother"),
	Hero(62, "npc_dota_hero_bounty_hunter", "Bounty Hunter"),
	Hero(63, "npc_dota_hero_weaver", "Weaver"),
	Hero(64, "npc_dota_hero_jakiro", "Jakiro"),
	Hero(65, "npc_dota_hero_batrider", "Batrider"),
	Hero(66, "npc_dota_hero_chen", "Chen"),
	Hero(67, "npc_dota_hero_spectre", "Spectre"),
	Hero(68, "npc_dota_hero_ancient_apparition", "Ancient Apparition"),
	Hero(69, "npc_dota_hero_doom_bringer", "Doom"),
	Hero(70, "npc_dota_hero_ursa", "Ursa"),
	Hero(71, "npc_dota_hero_spirit_breaker", "Spirit Breaker"),
	Hero(72, "npc_dota_hero_gyrocopter", "Gyrocopter"),
	Hero(73, "npc_dota_hero_alchemist", "Alchemist"),
	Hero(74, "npc_dota_hero_invoker", "Invoker"),
	Hero(75, "npc_dota_hero_silencer", "Silencer"),
	Hero(76, "npc_dota_hero_obsidian_destroyer", "Outworld Devourer"),
	Hero(77, "npc_dota_hero_lycan", "Lycan"),
	Hero(78, "npc_dota_hero_brewmaster", "Brewmaster"),
	Hero(79, "npc_dota_hero_shadow_demon", "Shadow Demon"),
	Hero(80, "npc_dota_hero_lone_druid", "Lone Druid"),
	Hero(81, "npc_dota_hero_chaos_knight", "Chaos Knight"),
	Hero(82, "npc_dota_hero_meepo", "Meepo"),
	Hero(83, "npc_dota_hero_treant", "Treant Protector"),
	Hero(84, "npc_dota_hero_ogre_magi", "Ogre Magi"),
	Hero(85, "npc_dota_hero_undying", "Undying"),
	Hero(86, "npc_dota_hero_rubick", "Rubick"),
	Hero(87, "npc_dota_hero_disruptor", "Disruptor"),
	Hero(88, "npc_dota_hero_nyx_assassin", "Nyx Assassin"),
	Hero(89, "npc_dota_hero_naga_siren", "Naga Siren"),
	Hero(90, "npc_dota_hero_keeper_of_the_light", "Keeper of the Light"),
	Hero(91, "npc_dota_hero_wisp", "Io"),
	Hero(92, "npc_dota_hero_visage", "Visage"),
	Hero(93, "npc_dota_hero_slark", "Slark"),
	Hero(94, "npc_dota_hero_medusa", "Medusa"),
	Hero(95, "npc_dota_hero_troll_warlord", "Troll Warlord"),
	Hero(96, "npc_dota_hero_centaur", "Centaur Warrunner"),
	Hero(97, "npc_dota_hero_magnataur", "Magnus"),
	Hero(98, "npc_dota_hero_shredder", "Timbersaw"),
	Hero(99, "npc_dota_hero_bristleback", "Bristleback"),
	Hero(100, "npc_dota_hero_tusk", "Tusk"),
	Hero(101, "npc_dota_hero_skywrath_mage", "Skywrath Mage"),
	Hero(102, "npc_dota_hero_abaddon", "Abaddon"),
	Hero(103, "npc_dota_hero_elder_titan", "Elder Titan"),
	Hero(104, "npc_dota_hero_legion_commander", "Legion Commander"),
	Hero(105, "npc_dota_hero_techies", "Techies"),
	Hero(106, "npc_dota_hero_ember_spirit", "Ember Spirit"),
	Hero(107, "npc_dota_hero_earth_spirit", "Earth Spirit"),
	Hero(108, "npc_dota_hero_abyssal_underlord", "Underlord"),
	Hero(109, "npc_dota_hero_terrorblade", "Terrorblade"),
	Hero(110, "npc_dota_hero_phoenix", "Phoenix"),
	Hero(111, "npc_dota_hero_oracle", "Oracle"),
	Hero(112, "npc_dota_hero_winter_wyvern", "Winter Wyvern"),
	Hero(113, "npc_dota_hero_arc_warden", "Arc Warden"),
	Hero(114, "npc_dota_hero_monkey_king", "Monkey King"),
	Hero(119, "npc_dota_hero_dark_willow", "Dark Willow"),
	Hero(120, "npc_dota_hero_pangolier", "Pangolier"),
	Hero(121, "npc_dota_hero_grimstroke", "Grimstroke"),
	Hero(129, "npc_dota_hero_mars", "Mars")
};
