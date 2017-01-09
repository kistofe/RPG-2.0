#include"creatures.h"
#include<stdlib.h>
#include<time.h>

void goblin_generator(monster_data* goblin, int wave_size, int wave_num)
{
	for (int i = 0; i < wave_size; i++)//Generating the Goblin horde
	{
		if (wave_num < 3)//Current Goblins
		{
			goblin[i].combat.hp			= 10 + rand() % 16;//HP 10, 25
			goblin[i].combat.attack_max = 8 + rand() % 3;//Atk Max 8, 10
			goblin[i].combat.attack_min = 3 + rand() % 5;//Atk min 3, 7
			goblin[i].combat.armor		= 4 + rand() % 4;//Armor 4, 7
			goblin[i].coins				= rand() % 15 + 1;
			goblin[i].monster_xp		= 20;
		}
		
		if (wave_num >= 3 && wave_num < 9)//Improved Goblins
		{
			goblin[i].combat.hp			= 15 + rand() % 21;//HP 15, 35
			goblin[i].combat.attack_max = 10 + rand() % 6;//Atk Max 10, 15
			goblin[i].combat.attack_min = 5 + rand() % 3;//Atk Min 5, 9
			goblin[i].combat.armor		= 6 + rand () % 5;//Armor 6, 10
			goblin[i].coins				= rand() % 15 + 1;
			goblin[i].monster_xp		= 25;
		}
	}
}

void necromancer_generator(monster_data* necromancer, hero_data* hero)
{
	for (int i = 0; i < 2; i++)
	{
		necromancer[i].combat.hp			= 150;
		necromancer[i].combat.armor			= 10;
		necromancer[i].monster_xp			= 70;
	}
}

int damage_to_enemy(hero_data* hero, monster_data* attacked_enemy)
{	
	hero->combat.total_attack	= hero->combat.attack_min + rand() % (hero->combat.attack_max - hero->combat.attack_min);
	int hero_damage_to_enemy	= hero->combat.total_attack - attacked_enemy->combat.armor;
	if (hero_damage_to_enemy > 0)
	{
		attacked_enemy->combat.hp = attacked_enemy->combat.hp - hero_damage_to_enemy;
	}
	
	return hero_damage_to_enemy;
}
