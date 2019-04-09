#ifndef HERO_H
#define HERO_H

#include <string>
#include <vector>

class Hero
{
	// Class containing details of one hero.
	// - id_ Valve id of a hero
	// - name_ Name string used multiple times by Valve, not easy to read
	// - localized_name_ Beautiful hero name ready to display

public:
	int32_t GetId() { return id_; };
	int32_t GetId() const { return id_; };
	std::string GetName() { return name_; };
	std::string GetName() const { return name_; };
	std::string GetLocalizedName() { return localized_name_; };
	std::string GetLocalizedName() const { return localized_name_; };

	static const Hero& FindHeroById(int32_t id);
	static const Hero& FindHeroByName();
	static const Hero& FindHeroByLocalizedName();

private:
	Hero(int32_t id, std::string name, std::string localized_name);

	// Private properties
	const int32_t id_;
	const std::string name_;
	const std::string localized_name_;

	// Static storage of all possible heroes
	static const std::vector<Hero> heros_;
};

#endif // HERO_H
