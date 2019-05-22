# Chauve
Dota coaching tools.

## Tags Manual

##### General logic

Add any number of tags into the filter list and the software will show only the games respecting all the tags. 

You can do a reverse tag using `!` in front of a tag. For example, `!morph-pick` will show all games where morph is not picked.

##### Leagues

* `league` -> set if a league id is detected.
* `league-<leagueid>` will also be set where leagueid is the Valve Id for the league.
* Using reverse tags, `!league` will return all games not in a league (scrims).

##### Teams

Using the Team name in lowercase will give you a filter per team (`og`, `secret`, `eg`, `liquid`...). 
Respect the team name appearing in Radiant and Dire columns. 

Also, the `<t_tag>-dire`, `<t_tag>-dire` are set after parse.

##### Hero Tags

* `<h_tag>` -> games with the hero picked or banned.
* `<h_tag>-pick` -> games with the hero picked
* `<h_tag>-ban` -> games with the hero banned

| Hero Name   |    h_tag    |
| ----------- | ----------- |
| Anti-Mage | am |
| Axe | axe |
| Bane | bane |
| Bloodseeker | bs |
| Crystal Maiden | cm |
| Drow Ranger | drow |
| Earthshaker | shaker |
| Juggernaut | jugger |
| Mirana | mirana |
| Morphling | morph |
| Shadow Fiend | sf |
| Phantom Lancer | pl |
| Puck | puck |
| Pudge | pudge |
| Razor | razor |
| Sand King | sk |
| Storm Spirit | storm |
| Sven | sven |
| Tiny | tiny |
| Vengeful Spirit | venge |
| Windranger | wind |
| Zeus | zeus |
| Kunkka | kunkka |
| Lina | lina |
| Lion | lion |
| Shadow Shaman | shaman |
| Slardar | slardar |
| Tidehunter | tide |
| Witch Doctor | wd |
| Lich | lich |
| Riki | riki |
| Enigma | enigma |
| Tinker | tinker |
| Sniper | sniper |
| Necrophos | necro |
| Warlock | wl |
| Beastmaster | bm |
| Queen of Pain | qop |
| Venomancer | veno |
| Faceless Void | void |
| Wraith King | wk |
| Death Prophet | dp |
| Phantom Assassin | pa |
| Pugna | pugna |
| Templar Assassin | ta |
| Viper | viper |
| Luna | luna |
| Dragon Knight | dk |
| Dazzle | dazzle |
| Clockwerk | clock |
| Leshrac | lesh |
| Nature's Prophet | np |
| Lifestealer | naix |
| Dark Seer | ds |
| Clinkz | clinkz |
| Omniknight | omni |
| Enchantress | enchant |
| Huskar | huskar |
| Night Stalker | ns |
| Broodmother | brood |
| Bounty Hunter | bh |
| Weaver | weaver |
| Jakiro | jaki |
| Batrider | bat |
| Chen | chen |
| Spectre | spectre |
| Ancient Apparition | aa |
| Doom | doom |
| Ursa | ursa |
| Spirit Breaker | sb |
| Gyrocopter | gyro |
| Alchemist | alche |
| Invoker | invo |
| Silencer | sile |
| Outworld Devourer | od |
| Lycan | lycan |
| Brewmaster | brew |
| Shadow Demon | sd |
| Lone Druid | ld |
| Chaos Knight | ck |
| Meepo | meepo |
| Treant Protector | treant |
| Ogre Magi | ogre |
| Undying | ud |
| Rubick | rub |
| Disruptor | disru |
| Nyx Assassin | nyx |
| Naga Siren | naga |
| Keeper of the Light | kotl |
| Io | io |
| Visage | visage |
| Slark | slark |
| Medusa | medusa |
| Troll Warlord | troll |
| Centaur Warrunner | centaur |
| Magnus | mag |
| Timbersaw | timber |
| Bristleback | bristle |
| Tusk | tusk |
| Skywrath Mage | sky |
| Abaddon | aba |
| Elder Titan | et |
| Legion Commander | legion |
| Techies | techies |
| Ember Spirit | ember |
| Earth Spirit | es |
| Underlord | ul |
| Terrorblade | tb |
| Phoenix | phoenix |
| Oracle | oracle |
| Winter Wyvern | ww |
| Arc Warden | aw |
| Monkey King | mk |
| Dark Willow | dw |
| Pangolier | pango |
| Grimstroke | grim |
| Mars | mars |
