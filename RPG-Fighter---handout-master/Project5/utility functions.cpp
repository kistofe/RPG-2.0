#include "utility functions.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"creatures.h"
#include "string library.h"

typedef unsigned int uint;

int stats_range(int min, int max, int value)
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

void hero_recovery(hero_data* hero)
{
	int healing_choice;
	if (hero->bag.potions != 0)
	{
		if (hero->combat.hp <= 50)
		{
			printf("\n--------------------------------------------------------------------\n");
			printf("Hey hero, you look exhausted. Do you want to use a Potion?	\nPress 1 to use a Potion and recover 50 HP		Press 2 to continue fighting");
			scanf("%d", &healing_choice);
			if (healing_choice == 1)
			{
				hero->combat.hp = hero->combat.hp + 50;
				printf("\nYou used a Potion, now you have %d HP", hero->combat.hp);
				getchar();
				printf("\n--------------------------------------------------------------------\n");
			}
		}
	}
}

void hero_level_up(hero_data* hero)
{
	if (hero->xp >= hero->level_up_xp)//Level up prototype
	{
		hero->level++;
		hero->level_up_xp = hero->level_up_xp + (20 * hero->level);

		hero->combat.hp			= hero->combat.full_hp + 10 * (hero->level - 1);
		hero->combat.attack_max = hero->combat.attack_max + 4;
		hero->combat.attack_min = hero->combat.attack_min + 4;
		hero->combat.armor		= hero->combat.armor + 2;

		hero->xp = 0;
		printf("\n--------------------------------------------------------------------\n");
		printf("Congratulations! You grew to level %d! Now you're even stronger than before!", hero->level);
		getchar();
		printf("\nYour stats increased and your HP was fully restored", hero->level);
		getchar();
		printf("HP: %d",hero->combat.hp);
		printf("\nATK MAX: %d", hero->combat.attack_max);
		printf("\nATK MIN: %d", hero->combat.attack_min);
		printf("\nARMOR: %d", hero->combat.armor);
		printf("\n--------------------------------------------------------------------\n");
	}
}

void shop(hero_data* hero)
{
	int shop_choice; 
	printf("\n--------------------------------------------------------------------\n");
	printf("Sun Town");
	printf("\n--------------------------------------------------------------------\n");
	getchar();
	printf("You've arrived to a small town, with a few houses and some shops");
	getchar();
	printf("\nYou found a small shop were Potions are sold, do you want to enter?		\nPress 1 to enter the Shop		Press 2 to leave the town");
	scanf("%d", &shop_choice);

	if (shop_choice == 1)
	{
		printf("\nCLERK: Hello traveler, wellcome to my small shop");
		getchar();
		printf("\nYou can have a Potion for only 50 coins, do you want to buy some?		\nYes (1)		No(2)");
		scanf("%d", &shop_choice);
		if (shop_choice == 1)
		{
			for (int i = 0; i < 1;)
			{
				uint num_of_potions;
				printf("\nHow many Potions do you want? ");
				scanf("%d", &num_of_potions);
				if (hero->bag.coins >= (50 * num_of_potions))
				{
					hero->bag.potions	= hero->bag.potions + num_of_potions;
					hero->bag.coins		= hero->bag.coins - (50 * num_of_potions);
					printf("\nHere you have! You obtained %d Potions", num_of_potions);
					getchar();
					break;
				}
				else
				{
					printf("\nYou don't have enough coins!");
					getchar();
				}
			}
		}
		else
		{
			printf("\nHave a good journey!");
			getchar();
		}
	}
	
	else
	{
		printf("\nYou continue your journey to the mountain");
		getchar();
	}
	
}


