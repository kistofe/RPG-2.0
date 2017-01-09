#ifndef __CREATURES_H__
#define __CREATURES_H__

// find here the manin data structure for the game
// feel free to expand it to suit your improvements

struct bag
{
	int potions;
	int coins;
};

struct combat_data
{
	int hp;
	int full_hp;
	int attack_min;
	int attack_max;
	int total_attack;
	int armor;
};

struct hero_data
{
	char name[11];
	struct combat_data combat;
	struct bag bag;
	int xp;
	int level;
	int level_up_xp;
};

struct monster_data
{
	struct combat_data combat;
	int coins;
	int monster_xp;
};


void goblin_generator(monster_data*, int, int);
void necromancer_generator(monster_data*, hero_data*);
int damage_to_enemy(hero_data*, monster_data*);
#endif // __CREATURES_H__