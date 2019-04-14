#ifndef HERO_H
#define HERO_H

#include <string>
#include <vector>

// Class representing a Dota hero
// The construction is constrained to existing hero ids and names
class Hero
{

public:
  // Properties accessors
  inline uint32_t GetId() const { return id_; };
  inline std::string GetCodeName() const { return code_name_; };
  inline std::string GetFormatedName() const { return formated_name_; };

  // Restricted constructor, creates the Hero with specified id
  // Create a empty Hero placeholder if no hero with such id
  Hero(uint32_t id);
  // Copy constructor
  Hero(const Hero& hero);

private:
  // Default constructor
  // Create a Hero with all properties
  // Only used to create the heroes database
  Hero(uint32_t id, std::string code_name, std::string formated_name);

  // Unique hero identifier inside all Dota APIs
  uint32_t id_;
  // Codename used by Valve to name some files
  std::string code_name_;
  // Beautiful name ready to display
  std::string formated_name_;

  // Static storage of all possible heroes
  static std::vector<Hero> heroes_;
};

#endif // HERO_H
