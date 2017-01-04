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
	if (value < min)
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

	monster_data goblin[6], boss;

	int wave_size				= 0;
	int dead_enemy				= 0;
	int total_coins				= 0;
	int total_experience		= 0;
	int level_up_xp				= 50;
	int hero_level				= 1;
	int run_prob				= 0;
	hero->combat.mana			= 5;
	hero->potions				= 0;
	int combat_menu;



	while (hero->combat.hp > 0)//General combat until Hero dies
	{
		srand(time(NULL));

		while (hero_level < 7)
		{
			wave_size = rand() % 6 + 1;

			printf("\nA %d Goblin horde appeared! Get prepared! ", wave_size);
			getchar();

			for (int i = 0; i < wave_size; i++)//Generating the Goblin horde
			{
				goblin[i].combat.hp			= rand() % 10 + 15;
				goblin[i].combat.attack_max = rand() % 2 + 8;
				goblin[i].combat.attack_min = rand() % 3 + 4;
				goblin[i].combat.armor		= rand() % 4 + 2;
				goblin[i].coins				= rand() % 15;
				goblin[i].received_xp		= 10;

			}

			while (dead_enemy < wave_size)//Wave Combat: a random num Goblin horde is generated and combat lasts until they all die
			{
				int attacked_goblin = rand() % wave_size;

				int total_hero_attack = hero->combat.attack_min + (rand() % (hero->combat.attack_max - hero->combat.attack_min));
				int hero_damage_to_goblin = total_hero_attack - goblin[attacked_goblin].combat.armor;
				goblin[attacked_goblin].combat.hp = goblin[attacked_goblin].combat.hp - hero_damage_to_goblin;

				printf("Fight[1]	Objects[2]	\nSpells[3]	Escape[4]");
				scanf("%d", &combat_menu);

				run_prob = 0;
				for (combat_menu; combat_menu < 5;)
				{
					if (combat_menu == 1)
					{
						if (goblin[attacked_goblin].combat.hp > 0)
						{

							if (hero_damage_to_goblin > 0)//Hero attacking the goblins
							{
								printf("\nYou attack the #%d Goblin with a fast movement. You dealt %d damage to the foe Goblin!", attacked_goblin + 1, hero_damage_to_goblin);
								getchar();

								if (goblin[attacked_goblin].combat.hp <= 0)
								{
									int object_drop_chance = rand() % 100 + 1;
									dead_enemy++;
									total_coins			= total_coins + goblin[attacked_goblin].coins;
									total_experience	= total_experience + goblin[attacked_goblin].received_xp;
									printf("\nNice attack! You defeated the #%d Goblin! You take %d coins from the death Goblin and receive %d experience", attacked_goblin + 1, goblin[attacked_goblin].coins, goblin[attacked_goblin].received_xp);
									getchar();

									if (object_drop_chance <= 10)
									{
										hero->potions++;
										printf("You obtain a Potion!");
										getchar();
									}

									if (total_experience >= level_up_xp)//Level up prototype
									{
										hero_level++;
										level_up_xp = level_up_xp + 20;

										hero->combat.hp = hero->combat.hp + 10 * (hero_level - 1);
										hero->combat.attack_max = hero->combat.attack_max + 5;
										hero->combat.attack_min = hero->combat.attack_min + 2;
										hero->combat.armor = hero->combat.armor + 1;
										hero->combat.mana = hero->combat.mana + 1;

										total_experience = 0;
										if (hero_level == 2)
										{
											printf("You learned the spell 'Heal'!");
											getchar();

										}

										printf("Congratulations! You leveled up! Now you're even stronger than before!");
										getchar();
										printf("Now you reached level %d your stats increased and your HP was fully restored", hero_level);
										getchar();
									}
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
						}
						break;
					}

					if (combat_menu == 2)
					{
						int choice;
						printf("You have %d Potions in your bag. What do you want to do?", hero->potions);
						getchar();
						printf("\nPress 1 to use a Potion and heal 20 HP	Press 2 to close your bag");
						scanf("%d", &choice);
						if (choice == 1)
						{
							if (hero->potions == 0)
							{
								printf("You don't have any Potion in your Bag!");
								getchar();
							}
							else
							{
								hero->potions--;
								hero->combat.hp = hero->combat.hp + 20;
								printf("You used a Potion. Now you have %d Potions in your bag", hero->potions);
								getchar;
								break;
							}
							
						}
						else
						{
							printf("You closed the bag");
							getchar();
						}
						
					}

					if (combat_menu == 3)
					{
						//spells
						break;
					}

					if (combat_menu == 4)
					{
						run_prob = rand() % 2;

						if (run_prob == 1)
						{
							printf("You escaped from the horde succesfully");
							getchar();

						}
						else
						{
							printf("A Goblin blocked your path!");
							getchar();
						}
						break;
					}
				}

				int goblin_total_attack;
				int goblin_damage;

				
				if (run_prob != 1)//Condition to fight -> Player does not escape from combat
				{
					for (int i = 0; i < wave_size; i++)//Goblins attacking the Hero
					{
						if (goblin[i].combat.hp > 0)
						{
							printf("\nBe careful %s! The enemy is preparing to attack you!", hero->name);
							getchar();

							goblin_total_attack = goblin[i].combat.attack_min + rand() % (goblin[i].combat.attack_max - goblin[i].combat.attack_min);
							goblin_damage = goblin_total_attack - hero->combat.armor;

							if (goblin_damage > 0)
							{

								hero->combat.hp = hero->combat.hp - goblin_damage;
								printf("\nThe #%d Goblin comes forward to you!", i + 1);
								printf(" It dealt %d points of damage! You have %d HP left", goblin_damage, hero->combat.hp);
								getchar();

							}

							else
							{
								printf("\nThe #%d Goblin comes forward to you!", i + 1);
								printf(" Nice! You blocked its attack!");
								getchar();
							}
						}
					}
					
					printf("\nGood job! You defeated the goblin horde! You got %d coins from your combat and %d total experience", total_coins, total_experience);
					getchar();
					printf("Now we will be able to continue our adventure, but don't low your guard %s, more enemies are waiting for shure", hero->name);
					getchar();
					dead_enemy = 0;
					total_coins = 0;
					total_experience = 0;
				}

				else
				{
					dead_enemy = wave_size;
				}

			}//Run prob closer
			
			
		}// Horde combat until level 7, at level 7 Hero meets Boss


		boss.combat.hp			= 500;
		boss.combat.attack_max	= 50;
		boss.combat.attack_min	= 25;
		boss.combat.armor		= 20;
		boss.combat.mana		= 10;

		printf("You walk slowly through a dark, humid corridor...");
		getchar();
		printf("You can hear nothing and the darkness is so dense you can barely see your own hands...");
		getchar();
		printf("Suddenly, a weak light starts to shine in the horizon and a loud voice starts to sound all over the corridor...");
		getchar();
		printf("~You've done well Hero~");
		getchar();
		printf("~I didn't expect any human to defeat my Goblins and to arrive to me, just like you've done~");
		getchar();
		printf("~It is obvious you have some hidden power that makes you special, but let me tell you something...~");
		getchar();
		printf("~I've witnessed thousands of stupid mortals just like you that thought they could defeat me~");
		getchar();
		printf("~But I'm Chechu, the King of all Goblins, and I will strike down upon you with great vengeance and furious anger those who would attempt to poison and destroy my brothers~");
		getchar();
		printf("~And you will know my name is the Lord when I lay my vengeance upon you~");
		getchar();

		printf("It's Chechu, the King of all Goblins!");
		getchar();
		printf("Prepare for combat %s!!! He's coming up to you!!", hero->name);
		getchar();

		while (boss.combat.hp > 0)
		{
			
			int boss_total_attack		= boss.combat.attack_min + rand() % (boss.combat.attack_max - boss.combat.attack_min);
			int boss_damage_to_hero		= boss_total_attack - hero->combat.armor;
			int total_hero_attack		= hero->combat.attack_min + (rand() % (hero->combat.attack_max - hero->combat.attack_min));
			int hero_damage_to_boss		= total_hero_attack - boss.combat.armor;
			boss.combat.mana++;

			printf("Fight[1]	Objects[2]	\nSpells[3]	Escape[4]");
			scanf("%s", &combat_menu);
			for (combat_menu; combat_menu < 5;)//BOSS COMBAT MENU
			{
				if (combat_menu == 1)
				{
					if (hero_damage_to_boss > 0)
					{
						boss.combat.hp = boss.combat.hp - hero_damage_to_boss;
						printf("Well done %s! You hit him well! You dealt %d points of damage!", hero->name, boss.combat.hp);
						getchar();
					}
					else
					{
						printf("Damn! The Goblin King blocked your attack!");
						getchar();
					}
					break;
				}
				
				if (combat_menu == 2)
				{
					//object selection
					break;
				}
				
				if (combat_menu == 3)
				{
					//spells selection
					break;
				}

				if (combat_menu == 4)
				{
					printf("You can't escape from this fight!");
					break;
				}
			}
		
			//Boss special attack (this attack basically instakills you, so hurry up and kill the boss)
			//if (boss.combat.mana == 20)
			//{
			//	boss_damage_to_hero = 300;
			//	hero->combat.hp = hero->combat.hp - boss_damage_to_hero;
			//	printf("~Now you'll witness my true power~");
			//	getchar();
			//	printf("The Goblin King Chechu unleashes a toxic wave");
			//	getchar();
			//	printf("Oh god it looks so bad. You took %d points of damage... your current HP is %d...", boss_damage_to_hero, hero->combat.hp);
			//	getchar();
			if (boss_damage_to_hero > 0)
			{
				int double_attack_chance = rand() % 10 + 1;

				if (double_attack_chance == 1 || double_attack_chance == 2)//The boss hits twice
				{
					hero->combat.hp = hero->combat.hp - (2 * boss_damage_to_hero);
					printf("WHAT WAS THAT?! You were hit twice!! Are you okay?? It dealt %d points of damage and you have %d HP left... ", boss_damage_to_hero * 2, hero->combat.hp);
					getchar();
				}
				else//The boss hits once
				{
					hero->combat.hp = hero->combat.hp - boss_damage_to_hero;
					printf("What a hit! Are you okay? It dealt %d points of damage! You have %d HP left", boss_damage_to_hero, hero->combat.hp);
					getchar();
				}
			}
			else
			{
				printf("Great!! You blocked it's attack!");
				getchar();
			}

		}//combat boss closer
		printf("You did it!! You defeated the King of all Goblins!!");
		getchar();
	}//General combat closer
	printf("You died! GAME OVER");
	getchar();
}//Void closer


int main(monster_data* goblin, monster_data* armored_goblin)
{
	char temp_name [11];
	int sex;
	int hero_hp			= 0;
	int hero_max_attack = 0;
	int hero_min_attack = 0;
	int hero_armor		= 0;
	int input_value		= 0;

	printf("Hello Hero! Welcome to the mighty land of Fiore!");
	getchar();
	printf("Now tell me. Are you a boy ? Or are you a girl ? Boy(type 1) Girl(type 2): ");
	scanf("%d", &sex);
	
	switch (sex)//SEX SELECTOR
	{
	case 1:
		printf("That thick beard has bretrayed you. ");
		getchar();
		break;
	case 2:
		printf("I never had any doubt. ");
		getchar();
		break;
	}

	getchar();
	printf("How should I call you?: ");
	scanf("%s", &temp_name);
	capitalize(temp_name); 
	printf("So you are %s? Alright, now introduce your combat stats in the following order:", temp_name);
	getchar();
	
	hero_data hero;
	getchar();
	printf("\nHP (It should be between 50 and 100, being inmortal is eventually boring):");
	scanf("%d", &hero_hp);
	hero.combat.hp				= hero_hp;
	hero.combat.hp				= value_range(100, 200, hero.combat.hp);
	printf("\nMinimum Attack Power (Between 5 and 10):");
	scanf("%d", &hero_min_attack);
	hero.combat.attack_min		= hero_min_attack;
	hero.combat.attack_min		= value_range(5, 10, hero.combat.attack_min);
	printf("\nMaximum Attack Power (Between 11 and 25):");
	scanf("%d", &hero_max_attack);
	hero.combat.attack_max		= hero_max_attack;
	hero.combat.attack_max		= value_range(11, 25, hero.combat.attack_max);
	printf("\nArmor (Between 3 and 5):");
	scanf("%d", &hero_armor);
	hero.combat.armor			= hero_armor;
	hero.combat.armor			= value_range(3, 5, hero.combat.armor);
	getchar();

	printf("\nNow we are ready to start our adventure! You'll start as a novice and hopefully you'll become someday a legend among mankind. Are you ready?");
	getchar();

	for (int i = 0; i <= 11; i++)
	{
		hero.name[i] = temp_name[i];
	}

	combat_flow(&hero);

	
		
	getchar();
	return 0;
}







 