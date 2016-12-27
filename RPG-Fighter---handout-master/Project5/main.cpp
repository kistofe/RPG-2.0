#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"creatures.h"
#include "string library.h"

typedef unsigned int uint;

int value_range(int min, int max, int value)
{
	if (value > max)
	{
		return max;
	}
	else if (value < min)
	{
		return min;
	}
	else 
	{
		return value;
	}
}

void combat_flow(hero_data* hero)
{

	monster_data goblin[6];

	int wave_size				= 0;
	int dead_enemy				= 0;
	int current_enemies_dead	= 0;
	
	while (hero->combat.hp > 0)//General combat until Hero dies
	{
		srand(time(NULL));
		wave_size = rand() % 6 + 1;
		
		printf("\nA %d Goblin horde appeared! Get prepared! ", wave_size);
		getchar();

		for (int i = 0; i < wave_size; i++)//Generating the Goblin horde
		{
			goblin[i].combat.hp			= rand() % 10 + 15;
			goblin[i].combat.attack_max = rand() % 2 + 8;
			goblin[i].combat.attack_min = rand() % 3 + 4;
			goblin[i].combat.armor		= rand() % 4 + 2;

		}

		while (dead_enemy < wave_size)//Wave Combat: a random num Goblin horde is generated and combat lasts until they all die
		{
			int attacked_goblin = 1 + (rand() % wave_size);

			if (goblin[attacked_goblin].combat.hp > 0)
			{
				int total_hero_attack = hero->combat.attack_min + (rand() % (hero->combat.attack_max - hero->combat.attack_min));
				int hero_damage_to_goblin = total_hero_attack - goblin[attacked_goblin].combat.armor;
				goblin[attacked_goblin].combat.hp = goblin[attacked_goblin].combat.hp - hero_damage_to_goblin;

				if (hero_damage_to_goblin > 0)//Hero attacking the goblins
				{
					printf("\nYou attack the #%d Goblin with a fast movement. You dealt %d damage to the foe Goblin!", attacked_goblin, hero_damage_to_goblin);
					getchar();

					if (goblin[attacked_goblin].combat.hp <= 0)
					{
						current_enemies_dead++;
						printf("\nNice attack! You defeated the #%d Goblin!", attacked_goblin);
						getchar();
					}
					else
					{
						printf("\nIt's not over yet! The foe Goblin has %d HP left", goblin[attacked_goblin].combat.hp);
						getchar();
					}
				}
				else
				{
					printf("\nThe foe Goblin blocked your attack!");
					getchar();
				}

				
				int goblin_total_attack;
				int goblin_damage;

				for (int i = 0; i < wave_size; i++)//Goblins attacking the Hero
				{
					if (goblin[i].combat.hp > 0)
					{
						printf("\nBe careful %s! The enemy is preparing to attack you!", hero->name);
						getchar();

						goblin_total_attack = goblin[i].combat.attack_min + rand() % (goblin[i].combat.attack_max - goblin[i].combat.attack_min);
						goblin_damage = goblin_total_attack - hero->combat.armor;

						if (goblin_damage > hero->combat.armor)
						{
							hero->combat.hp = hero->combat.hp - goblin_damage;
							printf("\nThe foe Goblin dealt %d points of damage! You have %d HP left", goblin_damage, hero->combat.hp);
							getchar();

						}
						else
						{
							printf("\nYou blocked the enemy's attack!");
							getchar();
						}

						if (current_enemies_dead == wave_size)
						{
							current_enemies_dead == dead_enemy;
						}
					}
				}
				
			}
			
		}
		
		printf("\nGood job! You defeated the goblin horde! Now we will be able to continue our adventure");
		getchar();
	}
	printf("You died! GAME OVER");
	getchar();
}

int main(monster_data* goblin, monster_data* armored_goblin)
{
	char temp_name [11];
	int sex;
	int hero_hp			= 0;
	int hero_max_attack = 0;
	int hero_min_attack = 0;
	int hero_armor		= 0;
	int input_value		= 0;

	printf("Hello Hero! Welcome to the mighty land of Fiore! \nNow tell me. Are you a boy? Or are you a girl? Boy (type 1) Girl (type 2):");
	scanf("%d", &sex);
	if (sex == 1)
	{
		printf("That thick beard has bretrayed you. ");
	}
	else if (sex == 2)
	{
		printf("I never had any doubt. ");
	}
	printf("How should I call you?: ");
	scanf("%s", &temp_name);
	capitalize(temp_name); 
	printf("So you are %s? Alright, now introduce your combat stats in the following order:", temp_name);

	hero_data hero;
	printf("\nHP (It should be between 50 and 100, being inmortal is eventually boring):");
	scanf("%d", &hero_hp);
	hero.combat.hp = hero_hp;
	hero.combat.hp = value_range(50, 100, hero.combat.hp);
	printf("Minimum Attack Power (Between 5 and 10):");
	scanf("%d", &hero_min_attack);
	hero.combat.attack_min = hero_min_attack;
	hero.combat.attack_min = value_range(5, 10, hero.combat.attack_min);
	printf("Maximum Attack Power (Between 11 and 25):");
	scanf("%d", &hero_max_attack);
	hero.combat.attack_max = hero_max_attack;
	hero.combat.attack_max = value_range(11, 25, hero.combat.attack_max);
	printf("Armor (Between 3 and 5):");
	scanf("%d", &hero_armor);
	hero.combat.armor = hero_armor;
	hero.combat.armor = value_range(3, 5, hero.combat.armor);

	printf("Now we are ready to start our adventure! You'll start as a novice and hopefully you'll become someday a legend among mankind. Are you ready?");
	getchar();

	for (int i = 0; i <= 11; i++)
	{
		hero.name[i] = temp_name[i];
	}

	combat_flow(&hero);
		
	getchar();
	return 0;
}







 