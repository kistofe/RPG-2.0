#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"creatures.h"
#include"utility functions.h"
#include"combats.h"
#include "string library.h"

typedef unsigned int uint;

int main()
{
	char temp_name [11];
	int sex;
	int hero_hp			= 0;
	int hero_max_attack = 0;
	int hero_min_attack = 0;
	int hero_armor		= 0;
	int input_value		= 0;
	int wave_turn		= 1;

	printf("Hello Hero! Welcome to the mighty land of Fiore!");
	getchar();
	printf("Our land was once peaceful and prosperous but now dark times have come and evil creatures rule our precious reign.");
	getchar();
	printf("You've sent by Gods to defeat the Darkness in this kigndom and return it to its past days.");
	getchar();
	printf("Now tell me. Are you a boy? Or are you a girl? Boy(type 1) Girl(type 2): ");
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
	printf("\nHP (Between 100 and 200):");
	scanf("%d", &hero_hp);
	hero.combat.hp				= hero_hp;
	hero.combat.hp				= stats_range(100, 200, hero.combat.hp);
	printf("\nMinimum Attack Power (Between 5 and 10):");
	scanf("%d", &hero_min_attack);
	hero.combat.attack_min		= hero_min_attack;
	hero.combat.attack_min		= stats_range(5, 10, hero.combat.attack_min);
	printf("\nMaximum Attack Power (Between 11 and 25):");
	scanf("%d", &hero_max_attack);
	hero.combat.attack_max		= hero_max_attack;
	hero.combat.attack_max		= stats_range(11, 25, hero.combat.attack_max);
	printf("\nArmor (Between 3 and 5):");
	scanf("%d", &hero_armor);
	hero.combat.armor			= hero_armor;
	hero.combat.armor			= stats_range(3, 5, hero.combat.armor);
	getchar();

	printf("\nNow we are ready to start our adventure! You'll start as a novice and hopefully you'll become someday a legend among mankind. Are you ready?");
	getchar();

	for (int i = 0; i <= 11; i++)
	{
		hero.name[i] = temp_name[i];
	}

	
	wave_combat(&hero, wave_turn);
	
	if (hero.combat.hp > 0)
	{
		boss_combat(&hero, wave_turn);
	}
	
	printf("\nYou died! GAME OVER");
	getchar();
		
	getchar();
	return 0;
}







 