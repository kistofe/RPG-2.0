#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"creatures.h"
#include"utility functions.h"

void boss_combat(hero_data* hero, int wave_turn)
{
	monster_data boss;

	boss.combat.hp = 300;
	boss.combat.attack_max = 55;
	boss.combat.attack_min = 25;
	boss.combat.armor = 15;

	hero->combat.hp = hero->combat.full_hp + 10 * (hero->level - 1);
	printf("\nYour HP was fully restored!\n");
	getchar();

	printf("\n--------------------------------------------------------------------\n");
	printf("Lanayru Cave");
	printf("\n--------------------------------------------------------------------\n");
	getchar();
	printf("You walk slowly through a dark, humid corridor...");
	getchar();
	printf("You can hear nothing and the darkness is so dense you can barely see your own hands...");
	getchar();
	printf("Suddenly, a weak light starts to shine in the horizon. You arrive to a big cave and as soon as you enter, a big rock blocks the path where you came from");
	getchar();
	printf("A loud voice starts to sound all over the cave");
	getchar();
	printf("~You've done well Hero~");
	getchar();
	printf("~I didn't expect any human to defeat my Goblins and to arrive to me, just like you've done~");
	getchar();
	printf("~It is obvious you have some hidden power that makes you special, but let me tell you something...~");
	getchar();
	printf("~I've witnessed thousands of stupid mortals just like you that thought they could defeat me~");
	getchar();
	printf("~But I'm the King of all Goblins and I will strike down upon you with great vengeance and furious anger those who would attempt to poison and destroy my brothers~");
	getchar();
	printf("~And you will know my name is the Lord when I lay my vengeance upon you~");
	getchar();

	printf("It's the King of all Goblins!");
	getchar();
	printf("Prepare for combat %s, you won't be able to escape this time!!!", hero->name);
	getchar();

	while (boss.combat.hp > 0)
	{
		boss.combat.total_attack	= boss.combat.attack_min + rand() % (boss.combat.attack_max - boss.combat.attack_min);
		int boss_damage_to_hero		= boss.combat.total_attack - hero->combat.armor;

		int hero_damage_to_enemy = damage_to_enemy(hero, &boss);
		hero_recovery(hero);

		printf("\n[TURN %d]", wave_turn);
		getchar();
		printf("\n---Your Turn---");
		getchar();

		printf("You attack the Goblin King with all your strength");
		getchar();
		if (hero_damage_to_enemy > 0)
		{
			printf("	Well done %s! You hit him well! You dealt %d points of damage!", hero->name, hero_damage_to_enemy);
			getchar();
			printf("	It has %d HP remaining", boss.combat.hp);
			getchar();
		}
		else
		{
			printf("	Damn! He blocked your attack!");
			getchar();
		}

		printf("\n---Enemy's Turn---");
		getchar();

		if (boss_damage_to_hero > 0)
		{
			int double_attack_chance = rand() % 10 + 1;
			printf("The Goblin King is preparing his attack");
			getchar();
			if (double_attack_chance == 1 || double_attack_chance == 2)//The boss hits twice
			{
				hero->combat.hp = hero->combat.hp - (2 * boss_damage_to_hero);
				printf("	WHAT WAS THAT?! You were hit twice!! Are you okay??");
				getchar();
				printf("	He dealt %d points of damage and you have %d HP left... ", boss_damage_to_hero * 2, hero->combat.hp);
				getchar();
			}
			else//The boss hits once
			{
				hero->combat.hp = hero->combat.hp - boss_damage_to_hero;
				printf("	What a hit! Are you okay?");
				getchar();
				printf("	He dealt %d points of damage! You have %d HP left", boss_damage_to_hero, hero->combat.hp);
				getchar();
			}
		}
		else
		{
			printf("	Great!! You blocked his attack!");
			getchar();
		}

		if (hero->combat.hp <= 0)
		{
			break;
		}
		wave_turn++;
	}//combat boss closer

	if (hero->combat.hp > 0)
	{
		printf("\nYou did it!! You defeated the King of all Goblins!!");
		getchar();
	}
}

void necromancer_combat(hero_data* hero, int dead_enemy, int wave_turn)
{
	monster_data necromancer[2];

	necromancer_generator(necromancer, hero);
	int resurrect_ability = 1;

	hero->combat.hp = hero->combat.full_hp + 10 * (hero->level - 1);
	printf("\n\nYour HP was fully restored!\n");
	getchar();

	printf("\n--------------------------------------------------------------------\n");
	printf("Mount Hakobe");
	printf("\n--------------------------------------------------------------------\n");
	printf("The path through the mountains has brought you to the entrance of a cave");
	getchar();
	printf("You can hear nothing but the wind and it looks like there are not enemies around");
	getchar();
	printf("You walk straight to the entrance of the cave but suddenly two black hooded figures appear in front of you");
	getchar();
	printf("They seem to talk but you can't understand a word");
	getchar();
	printf("Watch out %s! They are necromancers! They were once alive but now they are consumed by darkness", hero->name);
	getchar();
	printf("The two Necromancers are willing to fight! Get prepared!");
	getchar();

	while (dead_enemy < 2 && hero->combat.hp > 0)
	{
		int attacked_necromancer = rand() % 2;
		
		if (necromancer[attacked_necromancer].combat.hp > 0)
		{
			int avoid_chance = rand() % 100 + 1;

			hero_recovery(hero);

			printf("\n[TURN %d]", wave_turn);
			getchar();
			printf("\n---Your Turn---");
			getchar();

			printf("You attack the #%d Necromancer with great prowess!", attacked_necromancer + 1);
			getchar();

			if (avoid_chance <= 60)
			{
				int hero_damage_to_enemy = damage_to_enemy(hero, &necromancer[attacked_necromancer]);
				
				if (hero_damage_to_enemy > 0)
				{
					printf("	You dealt %d damage", hero_damage_to_enemy);
					getchar();

					if (necromancer[attacked_necromancer].combat.hp <= 0)
					{
						dead_enemy++;
						hero->xp = hero->xp + necromancer[attacked_necromancer].monster_xp;
						printf("	You spike the Necromancer right in the heart!");
						getchar();
						printf("	Well done! You killed the #%d Necromancer!", attacked_necromancer + 1);
						getchar();

						hero_level_up(hero);
					}

					else
					{
						printf("	He's still alive! He has %d HP remaining", necromancer[attacked_necromancer].combat.hp);
						getchar();
					}
				}

				else
				{
					printf("	The Necromancer blocked your attack easily");
					getchar();
				}
			}

			else
			{
				printf("	The Necromancer vanished in front of your eyes and your sword couldn't even hit him!");
				getchar();
			}
		

			if (dead_enemy != 2)
			{
				printf("\n---Enemy's Turn---");
				getchar();
			}

			for (int i = 0; i < 2; i++)
			{
				if (necromancer[i].combat.hp > 0)
				{
					printf("The #%d Necromancer stares at you", i + 1);
					getchar();

					int necromancer_damage_to_hero = 2 * hero->level;
					hero->combat.hp = hero->combat.hp - necromancer_damage_to_hero;

					printf("	He attacks you with Dark Magic! Your armor couldn't reduce the damage!");
					getchar();
					printf("	It dealt %d damage. You have %d HP left", necromancer_damage_to_hero, hero->combat.hp);
					getchar();

					if (dead_enemy == 1 && resurrect_ability == 1)
					{
						if (necromancer[0].combat.hp <= 0)
						{
							necromancer[0].combat.hp = 50;
							resurrect_ability = 0;
							dead_enemy = 0;
							printf("The #%d Necromancer is using its magic power to bring back to life his ally!", i + 1);
							getchar();
							printf("The #1 Necromancer woke up!");
							getchar();
						}

						if (necromancer[1].combat.hp <= 0)
						{
							necromancer[1].combat.hp = 50;
							resurrect_ability = 0;
							dead_enemy = 0;
							printf("The #%d Necromancer is using its magic power to bring back to life his ally!", i + 1);
							getchar();
							printf("The #2 Necromancer woke up!");
							getchar();
						}
					}

					if (hero->combat.hp <= 0)
					{
						break;
					}
				}
			}
			wave_turn++;
		}

		if (dead_enemy == 2)
		{
			wave_turn = 1;
			printf("\nWell done %s! You defeated the Necromancers!", hero->name);
			getchar();
			printf("You received 140 total experience");
			getchar();
		}
	}
}

void wave_combat(hero_data* hero, int wave_turn)
{
	monster_data goblin[6];

	int wave_size			= 0;
	int wave_num			= 1;
	int total_experience	= 0;
	int dead_enemy			= 0;
	hero->level_up_xp		= 50;
	hero->level				= 1;
	hero->xp				= 0;
	hero->bag.potions		= 0;
	hero->bag.coins			= 0;
	hero->combat.full_hp	= hero->combat.hp;
	int goblin_damage;
	int combat_choice;

	printf("\n--------------------------------------------------------------------\n");
	printf("Fiore Fields");
	printf("\n--------------------------------------------------------------------\n");
	getchar();
	printf("You are in a huge valley, following a sandy path");
	getchar();
	printf("Be careful %s, hordes of Goblins inhabit this place, we'll have to face them sooner or later", hero->name);
	getchar();
	printf("Suddenly, you hear some footstep noise and a group of Goblins appears from the bushes at your right");
	getchar();
	printf("Here they come!");
	getchar();

	while (wave_num < 9)//General combat until Hero reaches wave 9; then, he/she fights the pre-boss
	{
		srand(time(NULL));

		wave_size = rand() % 6 + 1;

		hero_recovery(hero);

		printf("\nA %d Goblin horde appeared! What do you want to do?\nFight[1]	Run away[2]", wave_size);
		scanf("%d", &combat_choice);

		goblin_generator(goblin, wave_size, wave_num);//Current (and modified) Goblin Horde generator

		if (combat_choice == 1)//Fight choice
		{
			while (hero->combat.hp > 0 && dead_enemy < wave_size)//Wave Combat: a random num Goblin horde is generated and combat lasts until they all die
			{
				int attacked_goblin = rand() % wave_size;

				if (goblin[attacked_goblin].combat.hp > 0)
				{
					
					int hero_damage_to_enemy = damage_to_enemy(hero, &goblin[attacked_goblin]);

					printf("\n[TURN %d]", wave_turn);
					getchar();
					printf("\n---Your Turn---");
					getchar();

					printf("You attack de #%d Goblin with a fast movement.", attacked_goblin + 1);
					getchar();
					if (hero_damage_to_enemy > 0)//Hero attacking the goblins
					{
						printf("	You dealt %d damage to the foe Goblin!", hero_damage_to_enemy);
						getchar();

						if (goblin[attacked_goblin].combat.hp <= 0)
						{
							int object_drop_chance = rand() % 100 + 1;

							dead_enemy++;
							hero->bag.coins		= hero->bag.coins + goblin[attacked_goblin].coins;
							hero->xp			= hero->xp + goblin[attacked_goblin].monster_xp;
							printf("	Nice attack! You defeated the #%d Goblin! You take %d coins from the death Goblin and receive %d experience", attacked_goblin + 1, goblin[attacked_goblin].coins, goblin[attacked_goblin].monster_xp);
							getchar();

							if (object_drop_chance <= 20)
							{
								hero->bag.potions++;
								printf("You obtain a Potion!");
								getchar();
							}

							hero_level_up(hero);
						}
						else
						{
							printf("	It's not over yet! The foe Goblin has %d HP left", goblin[attacked_goblin].combat.hp);
							getchar();
						}
					}
					else
					{
						printf("	The foe Goblin blocked your attack!");
						getchar();
					}

					if (dead_enemy != wave_size)
					{
						printf("\n---Enemy's Turn---");
						getchar();
					}

					for (int i = 0; i < wave_size; i++)//Goblins attacking the Hero
					{
						if (goblin[i].combat.hp > 0)
						{
							goblin->combat.total_attack = goblin[i].combat.attack_min + rand() % (goblin[i].combat.attack_max - goblin[i].combat.attack_min);
							goblin_damage				= goblin->combat.total_attack - hero->combat.armor;

							printf("The #%d Goblin comes forward to you!", i + 1);
							getchar();
							if (goblin_damage > 0)
							{

								hero->combat.hp = hero->combat.hp - goblin_damage;
								printf("	It dealt %d points of damage! You have %d HP left", goblin_damage, hero->combat.hp);
								getchar();

							}

							else
							{
								printf("	Nice! You blocked its attack!");
								getchar();
							}

							if (hero->combat.hp <= 0)
							{
								break;
							}
						}
					}
					wave_turn++;
				}
			}

			combat_choice = 0;
		}//input 1; fight

		if (combat_choice == 2)
		{
			printf("\nYou run away from the Goblin Horde!\n");
			getchar();

		}

		if (dead_enemy == wave_size)
		{
			if (goblin->monster_xp == 20)
			{
				total_experience = wave_size * 20;
			}
			else
			{
				total_experience = wave_size * 25;
			}

			wave_num++;
			
			printf("\nGood job! You defeated the goblin horde! You got %d total experience from the fight", total_experience);
			getchar();
			printf("You've got %d coins in your bag!", hero->bag.coins);
			getchar();
			printf("Now we will be able to continue our adventure, but don't low your guard %s, more enemies are waiting for shure\n", hero->name);
			getchar();
			dead_enemy			= 0;
			total_experience	= 0;
			wave_turn			= 1;
		}

		if (hero->combat.hp <= 0)
		{
			break;
		}
	}//Combat until wave 9
	shop(hero);
	necromancer_combat(hero, dead_enemy, wave_turn);
}//Void closer
