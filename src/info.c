

/* File: info.c */

/*
 * Tables containing object kind descriptions, extra numerical info.
 * Detailed info on spells.  Text for extended object descriptions of
 * various kinds, artifact and DSM activation and flag descriptions.  Self
 * Knowledge.  Spell failure chance, if is OK to cast, extra info shown in
 * books, and print spells of a given spellbook.
 *
 * Copyright (c) 1999 Leon Marrick, Ben Harrison, James E. Wilson,
 * Robert A. Koeneke
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.  Other copyrights may also apply.
 */

#include "angband.h"



/*
 * General information about classes of objects. -LM-
 *
 * Index is tval.
 */
cptr obj_class_info[101] =
{
	"",	"",	"",	"",	"",
	"",	"",	"Chests may have some really good treasures hidden inside, but can be perilous to open...",	"",	"",

	"",	"",	"",	"",	"",
	"",	"Sling ammo.",	"Bow ammo.",	"Crossbow ammo.",	"Missile launchers allow you to inflict damage from a distance without using magic.",

	"Diggers, especially heavy ones, are invaluable for forced entry and escape and can make a lucky miner rich.",	"Hafted weapons rely on blunt force to inflict damage.  Since they spill relatively little blood, priests much prefer to carry one.",	"Pole-mounted weapons are often cumbersome and may require two hands to wield, but some offer both a high degree of protection and powerful attacks.",	"The effectiveness of edged weapons depends on keen edges and sharp points.  They tend to be quite light and are easy to use, but some may not deal enough damage for your liking.",	"",
	"",	"",	"",	"",	"",

	"Footwear protects the feet only, but some rare items of this type have magics to render them fleet, light, or steady.",	"Your hands would benefit from protection too, but most magic users need to keep their fingers unencumbered or magically supple.",	"Many a blow will be struck upon your head, and protection here will certainly be helpful.  Some rare items may protect and enhance your mind.",	"Many a blow will be struck upon your head, and protection here will certainly be helpful.  Some rare items may protect and enhance your mind.",	"Shields can be worn on your arm, or on your back if you need both hands to use your weapon.  So protective can a shield be that it can reduce damage as much or more than body armour, and you can perhaps deflect physical missiles (even shards) or take advantage of opportunities to bash your foe if you have one on your arm.",
	"Experienced adventurers wrap a cloak around their body.  Some rare items of this type may allow you to slip silently around less alert enemies.",	"Some kind of body protection will become a necessity as you face ever more dangerous opponents; rare items of this type may hold many and varied protective magics.",	"Some kind of body protection will become a necessity as you face ever more dangerous opponents; rare items of this type may hold many and varied protective magics.",	"Armour made of dragon scales is rare indeed, and powerful dragon magics allow you to sometimes breathe even as great wyrms do.",	"An adventurer who cannot see is jackal food.  The further away your illumination ends, the greater your chance to ready yourself for desperate combat.",

	"Amulets slip around your neck, and almost all have magics wondrous or perilous bound inside.",	"",	"",	"",	"",
	"You may wear a ring upon each of your two ring fingers, and benefit or suffer from the magics it contains.",	"",	"",	"",	"",

	"",	"",	"",	"",	"",
	"Staffs are heavy, and take up plenty of space in your backpack, but can hold a lot of sometimes powerful spells that affect large areas.  Staffs recharge easily and well.",	"",	"",	"",	"",

	"",	"",	"",	"",	"",
	"Wands hold a variety of spells, useful both in combat and for exploration.  Bolt spells in wands often beam, and ball spells affect large areas.  Once its charges are exhausted, a wand is useless until recharged.",	"The magics stored in rods never run out, given enough time between uses to recover.  Rods can do a lot of damage, but they affect only small areas.  Bolt spells in rods seldom or never beam.",	"",	"",	"",

	"One will often find sheets of parchment with magic spells.  They are easy to read, and are a warrior or paladin's best chance at making use of magic.",	"",	"",	"",	"",
	"Healers, alchemists, and sages create potions in vast quantities, and store them in small flasks of clear glass or gleaming crystal.  Once quaffed, a potion is guaranteed to work, but not every strange liquid was mixed for your benefit...",	"",	"",	"",	"",

	"Deep in the murky dungeons strange mushrooms grow, and monsters rout about sealed packets of food that their owners will never need again.",	"",	"",	"",	"",
	"",	"",	"",	"",	"",

	"A manual of sorcerous magics, bound in fine linen dyed deep red.",	"A shining gospel of piety in flawless white and gold.",	"A runed stone with earthly and natural magics chiseled in brown and rich greens.",	"A black tome of necromantic rituals, with shadows lying deep around it.",	"",
	"",	"",	"",	"",	"",

	"Small valuables and coins."
};


/*
 * Extra numerical information about magical devices. -LM-
 *
 * Y-coordinate:  Dragon Scale Mails = 0, Amulets = 1, Rings = 2,
 *                Staffs = 3, Wands = 4, Rods = 5.
 * X-coordinate:  object's sval (can currently accept an sval of up to 49)
 */
cptr obj_special_info[6][50] =
{
	/* Dragon Scale Mails. */
	{
		"",								/*  */
		"(It can breathe acid for 150 damage)",				/* Black */
		"(It can breathe lightning for 130 damage)",			/* Blue */
		"(It can breathe frost for 140 damage)",			/* White */
		"(It can breathe fire for 160 damage)",				/* Red */
		"(It can breathe poison for 150 damage)",			/* Green */
		"(It can breathe any of various elements for 190 damage)",	/* Multihued */
		"",	"",	"",						/*  */
		"(It can breathe light or darkness for 160 damage)",		/* Shining */
		"",								/*  */
		"(It can breathe sound or shards for 190 damage)",		/* Law */
		"",								/*  */
		"(It can breathe confusion for 130 damage)",			/* Bronze */
		"",								/*  */
		"(It can breathe sound for 130 damage)",			/* Gold */
		"",								/*  */
		"(It can breathe chaos or disenchantment for 180 damage)",	/* Chaos */
		"",								/*  */
		"(It can breathe sound, shards, chaos, or disenchantment for 210 damage)",	/* Balance */
		"",	"",	"",	"",	"",	"",	"",	"",	"",
		"(It can breathe just about anything for 240 damage)",		/* Power */
		"",	"",	"",	"",	"",	"",	"",	"",	"",	"",
		"",	"",	"",	"",	"",	"",	"",	"",	""
	},

	/* Amulets. */
	{
		"",		/* Doom */
		"",		/* Teleport */
		"",		/* Intelligence */
		"",		/* Slow Digestion */
		"",		/* Resist Acid */
		"",		/* Magical Item Mastery */
		"",		/* Wisdom */
		"",		/* Charisma */
		"",		/* the Magi */
		"",		/* Escaping */

		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		""		/*  */
	},

	/* Rings. */
	{
		"",		/* Woe */
		"",		/* Aggravation */
		"",		/* Weakness */
		"",		/* Stupidity */
		"",		/* Teleportation */
		"",		/* Telepathy */
		"",		/* Slow Digestion */
		"",		/* Feather Fall */
		"",		/* Resist Fire */
		"",		/* Resist Cold */
		"",		/* Sustain Str & Chr */
		"",		/* Sustain Int & Wis */
		"",		/* Sustain Dex & Con */
		"",		/* Resist Nether */
		"",		/* Light and Dark Resistance */
		"(damage: 45 - 120)",		/* Electricity */
		"",		/* Protection */
		"(damage: 45 - 120)",		/* Acid */
		"(damage: 45 - 120)",		/* Flames */
		"(damage: 45 - 120)",		/* Ice */
		"",		/* Resist Poison */
		"",		/* Free Action */
		"",		/* See Invisible */
		"",		/* Searching */
		"",		/* Strength */
		"",		/*  */
		"",		/* Dexterity */
		"",		/* Constitution */
		"",		/* Skill */
		"",		/* Deadliness */
		"",		/* Combat */
		"",		/* Speed */
		"",		/*  */
		"",		/*  */
		"",		/*  */
		"",		/*  */
		"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		""		/*  */
	},

	/* Staffs. */
	{
		"",					/* Darkness */
		"",					/* Slowness */
		"",					/* Haste Monsters */
		"",					/* Summoning */
		"",					/* Teleportation */
		"",					/* Perception */
		"",					/* Remove Curse */
		"(damage: 12 - 60+)",		/* Starlight */
		"",					/* Light */
		"",					/* Magic Mapping */
		"",					/* Treasure Location */
		"",					/* Object Location */
		"",					/* Trap Location */
		"",					/* Door/Stair Location */
		"",					/* Detect Invisible */
		"",					/* Detect Evil */
		"(heal: 10 - 30)",		/* Cure Medium Wounds */
		"",					/* Curing */
		"(heal: 300)",			/* Healing */
		"",					/* Banish Evil */
		"",					/* Sleep Monsters */
		"",					/* Slow Monsters */
		"",					/* Speed */
		"",					/* Probing */
		"(damage: 55)",			/* Dispel Evil */
		"(damage: 90)",			/* Power */
		"(damage: 110)",			/* Holiness */
		"",					/* Genocide */
		"",					/* Earthquakes */
		"",					/* *Destruction* */
		"",					/* Detection */
		"(damage: 110 - 180)",		/* Mana Storm */
		"(damage: 90 - 150)",		/* Starburst */
		"",					/* Mass Confusion */
		"",		/*  */
		"",		/*  */
		"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"(damage: 30 - 90+)",		/* Gandalf */
		"(damage: 100 - 200)",		/* Winds */
		"",					/* Meneltarma */
		"",					/* Radagast */
		"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		""		/*  */
	},

	/* Wands. */
	{
		"",		/* Heal Monster */
		"",		/* Haste Monster */
		"",		/* Clone Monster */
		"(distance: 55-80)",		/* Teleport Away */
		"(chance: 95%)",		/* Disarming */
		"",		/* Door Destruction */
		"",		/* Stone to Mud */
		"(damage: 4 - 20)",		/* Light */
		"",		/* Sleep Monster */
		"",		/* Slow Monster */
		"",		/* Confuse Monster */
		"",		/* Scare Monster */
		"(damage: 45 - 90)",		/* Drain Life */
		"",		/* Polymorph */
		"(damage: 12)",		/* Stinking Cloud */
		"(damage: 2 - 12)",		/* Magic Missile */
		"(damage: 5 - 70)",		/* Acid Bolts */
		"(damage: 3 - 42)",		/* Lightning Bolts */
		"(damage: 6 - 84)",		/* Fire Bolts */
		"(damage: 4 - 56)",		/* Cold Bolts */
		"(damage: 55 - 80)",		/* Acid Balls */
		"(damage: 35 - 60)",		/* Lightning Balls */
		"(damage: 60 - 85)",		/* Fire Balls */
		"(damage: 45 - 70)",		/* Cold Balls */
		"",					/* Wonder */
		"(damage: 90 - 265)",		/* Annihilation */
		"(damage: 145)",			/* Dragon's Flame */
		"(damage: 145)",			/* Dragon's Frost */
		"(damage: 160 - 190)",		/* Dragon's Breath */
		"(damage: 10 - 208)",		/* Striking */
		"(damage: 23 - 124)",		/* Storms */
		"(damage: 4 - 49)",		/* Shrapnel */
		"",		/*  */
		"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */
		"(damage ~55 - 280.  hurt 30.)",/* Ilkorin */
		"",	/* Saruman */
		"(various chaotic effects)",	/* Unmaking */
		"((damage: 3 * plev + d80)",	/* Ulpion */
		"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		""		/*  */
	},

	/* Rods. */
	{
		"",				/* Trap Detection */
		"",				/* Door Detection */
		"",				/* Identify */
		"",				/* Recall */
		"",				/* Illumination */
		"",				/* Magic Mapping */
		"",				/*  */
		"",				/* Probing */
		"",				/* Curing */
		"(Heal: 500)",		/* Healing */
		"",				/* Restoration */
		"",				/* Speed */
		"",				/*  */
		"(distance: 45-60+)",				/* Teleport Away */
		"(chance: 95%)",		/* Disarming */
		"(damage: 4 - 20)",	/* Light */
		"",				/* Sleep Monster */
		"",				/* Slow Monster */
		"(damage: 45 - 107)",	/* Drain Life */
		"",				/* Polymorph */
		"(damage: 6 - 77)",	/* Acid Bolts */
		"(damage: 4 - 49)",	/* Lightning Bolts */
		"(damage: 7 - 91)",	/* Fire Bolts */
		"(damage: 5 - 63)",	/* Frost Bolts */
		"(damage: 55 - 92)",	/* Acid Balls */
		"(damage: 35 - 72)",	/* Lightning Balls */
		"(damage: 60 - 97)",	/* Fire Balls */
		"(damage: 45 - 82)",	/* Cold Balls */
		"(damage: 18 - 238)",	/* Lightning Strike */
		"(damage: 21 - 259)",	/* Northwinds */
		"(damage: 24 - 280)",	/* Dragonfire */
		"(damage: 27 - 301)",	/* Glaurung's Blood */
		"",				/* Aggravate Level */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */
		"",				/* Delving */
		"",				/* Shadow */
		"",				/* Air */
		"",				/* Portals */
		"",		/*  */
		"",		/*  */	"",		/*  */	"",		/*  */
		"",		/*  */
		""		/*  */
	}
};


/*
 * Prints "User's tips" for various spells.  User's tips only appear after
 * a learnt spell is browsed. -LM-
 */
cptr spell_tips[287] =
{
	"Fires a bolt of mana.",	/* 0 - Magic Missile */
	"Detects nearby monsters that are not invisible.",
	"Random minor displacement.",
	"Permanently lights up the area lit by your light source or a room.",
	"Reduces the amount of poison in your system.",
	"Reduces cuts and heals you a little.",
	"Detects nearby treasure and gold seams.",
	"Detects nearby objects.",
	"Fires a ball of poison.",
	"Attempts to confuse one monster.",
	"Fires a bolt or beam of lightning.",	/* 10 - Lightning Bolt */
	"Destroys all doors next to you.",
	"Attempts to put a monster to sleep.",
	"Removes all poison from your body.",
	"Random major displacement.",
	"Fires a line of weak light.  Affects light-hating creatures.",
	"Minor recharging.",
	"Fires an arc of cold.",
	"Fully feeds you.",
	"Attempts to disarm a trap adjacent to you.",
	"Attempts to change a monster.",	/* 20 - Polymorph Other */
	"Standard identification.",
	"Attempts to put all monster in line of sight to sleep.",
	"Fires a bolt or beam of fire.",
	"Attempts to slow a monster down.",
	"Turns rod, wand, or staff energy into mana.  Rods have little energy.",
	"Fires a ball of frost.",
	"Medium-strength recharging spell.",
	"Teleports an opponent away.",
	"Temporarily hasten yourself.",
	"Fires a ball of fire.",		/* 30 - Fire Ball */
	"Puts target creatures in Stasis.  They are completely paralyzed and invulnerable.",
	"Destroys almost all objects nearby, deletes ordinary monsters, and banishes uniques from the level.",
	"Temporary opposition to fire.  Cumulative with equipment resistances.",
	"Temporary opposition to cold.  Cumulative with equipment resistances.",
	"Temporary opposition to acid.  Cumulative with equipment resistances.",
	"Temporary opposition to poison.  Cumulative with equipment resistances.",
	"Temporary opposition to the elements and poison.  Cumulative with equipment resistances.",
	"Creates a barrier of doors around you.",
	"Creates a staircase nearby.  Random choice between up or down, except on quest levels.",
	"Immediately takes you to the next level up or down.",	/* 40 - Teleport Level */
	"Recalls you to the town, or as deep in the dungeon as you have ever gone.",
	"Controlled minor displacement.  Hint:  use the 'p' option when you enter targeting mode.",
	"Detects all nearby evil monsters, even invisible ones.",
	"Detects nearby enchanted objects.",
	"Shakes the nearby dungeon, randomly swapping walls and floors.",
	"Very powerful attempt to confuse, slow, and then sleep all monsters.",
	"Fires a ball of light centered on you.",
	"Recovers mana much more rapidly than normal resting.  Assign this spell to a key for best results.",
	"Temporarily increases armour class by 50.",
	"Powerful recharging spell.",		/* 50 - Recharge Item III */
	"Long-duration haste spell.",
	"Greatly increases saving throw and armour class.  Perfect protection from blindness and confusion.",
	"Fires a bolt or beam of acid.",
	"Fires a large poison ball.",
	"Fires a large acid ball.",
	"Fires a large frost ball.",
"Fires a small but unresistible magic ball.",
	"Fires a large, very powerful mana ball.",
	"The next time you hit or steal from a monster, you will teleport away.",
	"Renders you hasted and berserk.",	/* 60 - Day of Misrule */
	"",
	"",
	"",
	"Detects all nearby evil monsters, even invisible ones.",
	"Reduces cuts and heals you a little.",
	"Short-duration bonus to fighting ability and armour class.",
	"Removes any fear you currently feel.",
	"Permanently lights up the area lit by your light source or a room.",
	"Detects all nearby traps.",
	"Detects all nearby doors and stairs.", /* 70 - Detect Doors/Stairs */
	"Reduces the amount of poison in your system.",
	"Reduces cuts and heals you a moderate amount.",
	"Attempts to frighten one monster.",
	"Random medium-range displacement.",
	"Medium-duration bonus to fighting ability and armour class.",
	"Attempts to put all monsters next to you to sleep.",
	"Fully feeds you.",
	"Removes standard curses.",
	"Temporary opposition to fire and frost.  Cumulative with equipment resistances.",
	"Removes all poison from your body.",	/* 80 - Neutralize Poison */
	"Fires an orb of holy force that does extra damage to evil creatures.",
	"Temporary see invisible.",
	"Temporary protection from lesser evil creatures.",
	"Reduces cuts and heals you a large amount.",
	"Shakes the nearby dungeon, randomly swapping walls and floors.",
	"Maps the local area.",
	"Attempts to make all undead monsters in line of sight turn and run.",
	"Long-duration bonus to fighting ability and armour class.",
	"Dispels all undead in line of sight.",
	"A large amount of healing, eliminates cuts and stunning.",	/* 90 - Heal */
	"Dispels all evil monsters in line of sight.",
	"Temporarily increases armour class by 50.",
	"Places a glyph on the floor that monsters cannot pass over or be summoned on until broken.  Max of four glyphs on a level; disarm extras.",
	"Strong dispel evil, healing, and remove poisoning, fear, stunning, and cuts.",
	"Minor random displacement.",
	"Long-range random displacement.",
	"Teleports an opponent away.",
	"Immediately takes you to the next level up or down.",
	"Recalls you to the town, or as deep in the dungeon as you have ever gone.",
	"Regenerates the dungeon level.",	/* 100 - Alter Reality */
	"Detects nearby monsters that are not invisible.",
	"Detects all nearby monsters, traps, doors, stairs, gold seams, and objects.",
	"Learns about a monster's attributes and resistances.",
	"Standard identification of an object.",
	"Permanently light up the entire dungeon level, except for vaults, and detect everything nearby.",
	"Teleports away all evil monsters in line of sight.",
	"An extremely strong healing spell.  Removes cuts and stuns.",
	"Full *identification* of any object.",
	"Restores all stats.",
	"Restores experience level.",	/* 110 - Remembrance */
	"Destroys all doors next to you.",
	"Medium strength recharging spell.",
	"Removes both normal and heavy curses.",
	"Attempts to disarm an adjacent trap.",
	"Attempts to put a monster in stasis or fully bar a door.",
	"Adds plusses to Skill and Deadliness to weapons or plusses to armour class to armour.",
	"Fires a large ball of light.",
	"Fires a beam of holy magic that does extra damage to evil creatures.",
	"Destroys almost all objects nearby, deletes ordinary monsters, and banishes uniques from the level.",
	"Strikes at the soul of a living monster.",	/* 120 - Annihilation */
	"Large ball of light centered on you, healing, and a powerful frighten monsters spell.",
	"Select a temporary elemental brand.  More brands become available as you gain levels.  Only one brand is available at a time.  For Paladins, only works on melee weapons.",
	"Temporary Slay Evil.  Acts like (and can replace) a standard Slay evil weapon.",
	"Heroism, frightens monsters, also a little healing and recovery of courage.",
	"Smites a foe with a divine blast.",
	"",
	"",
	"Detects all nearby living monsters, even invisible ones.",
	"Permanently lights up the area lit by your light source or a room.",
	"Fully feeds you.",	/* 130 - foraging */
	"Minor random displacement.",
	"Reduces the amount of poison in your system.",
	"Short-range beam of lightning.",
	"Destroys all doors next to you.",
	"Melts a wall square to floor.",
	"Fires a line of weak light.  Affects light-hating creatures.",
	"Removes all poison from your body.",
	"Fires a bolt or beam of frost.",
	"Attempts to put a monster to sleep.",
	"Attempts to frighten a monster.",	/* 140 - frighten creature */
	"Detects nearby traps, doors, and stairs.",
	"Kills all weak monsters in line of sight; spell has no effect on stronger creatures.",
	"Fires a bolt or beam of fire.",
	"Temporary heroism.",
	"Breaks ordinary curses.",
	"Fires a bolt or beam of acid.",
	"Teleports a monster away.",
	"Fires a bolt or beam of poison.",
	"Temporary opposition to poison.  Cumulative with equipment resistances.",
	"Shakes the nearby dungeon, randomly swapping walls and floors.",	/* 150 - earthquake */
	"Temporary opposition to fire and cold.  Cumulative with equipment resistances.",
	"Detects all nearby monsters, traps, doors, stairs, gold seams, and objects.",
	"Recovers from wounds, poison and physical damage far more rapidly than normal resting.  This is a good spell to assign to a key.",
	"Temporary opposition to acid and electricity.  Cumulative with equipment resistances.",
	"Hurts a monster, then attempts to slow and confuse it.",
	"Attempts to disarm an adjacent trap.",
	"Standard identification of an object.",
	"Creates Athelas.",
	"Fires a large lightning ball.",
	"Fires a very large sound ball.",	/* 160 - thunderclap */
	"Turns you into a silent mouse.",
	"Turns you into a ferret, most crafty of animals.",
	"Turns you into a hound always aware of its surroundings.",
	"Turns you into a speedy gazelle.",
	"Turns you into a dauntless lion.",
	"Detects all nearby evil monsters, even invisible ones.",
	"Attempts (strongly) to frighten all monsters in line of sight.",
	"Maps the local area.",
	"Detects all nearby monsters, traps, doors, and stairs, and grants temporary see invisible.",
	"Healing, plus removal of all cuts and poison.",	/* 170 - herbal healing */
	"Fires a very large cold ball.",
	"Hurls water outwards from yourself in all directions.",
	"Fires a very large fire ball and trigger an earthquake.",
	"Fires a small, intense plasma ball.",
	"Fires a large ball of light centered on yourself.",
	"Attempts to slow and sleep all monsters in line of sight.",
	"Temporarily increases armour class by 50.",
	"Dispels all monsters in line of sight.  Extra damage to evil creatures.",
	"Places a glyph on the floor that monsters cannot pass over or be summoned on until broken.",
	"Restores all your stats.",	/* 180 - song of renewal */
	"Fires a bolt or beam of time.",
	"Temporarily hastens you.",
	"Recharges a magical item.",
	"Turns you into a wise and powerful Elder Ent.   Use potions or spells to protect yourself from fire!",
	"Restores your experience.",
	"Dispels evil monsters, heals you, blesses you, and removes fear, poisoning, stunning, and cuts.  You get results when you ask aid of Yavanna.",
	"Low-level probing spell that lets you learn about racial type and basic resistances.",
	"",
	"",
	"",	/* 190 */
	"",
	"Fires a mana bolt.",
	"Detects all nearby evil monsters, even invisible ones.",
	"Increases the range at which you can see warm-blooded creatures by 3.",
	"Removes ordinary curses.",
	"Attempts to slow a monster.",
	"Attempts to put a monster to sleep.",
	"Attempts to frighten a monster.",
	"Turns you into a fast-fluttering bat.",
	"Destroys all doors next to you.",	/* 200 - door destruction */
	"Fires a bolt or beam of darkness.",
	"Covers the immediate area with a cloud of poison.  Does not quickly lose strength with distance from the center.",
	"Attempts to make all undead monsters in line of sight flee.",
	"Attempts to make all evil monsters in line of sight flee.",
	"Removes all poison from your system.",
	"Attacks all undead creatures in line of sight.",
	"Attacks all evil creatures in line of sight.",
	"Grants temporary see invisible.",
	"Random minor displacement.",
	"Detects all nearby traps.",	/* 210 - detect traps */
	"Detects all nearby doors.",
	"Attempts to put all monsters in line of sight to sleep.",
	"Attempts to slow all monsters in line of sight.",
	"Detects nearby magical objects.",
	"Fires a bolt or beam of life-draining magic.",
	"Temporary opposition to poison.  Cumulative with equipment resistances.",
	"Attacks all demons in line of sight.",
	"Fires a beam of darkness.",
	"Fires a heavy mana bolt.",
	"Deletes all monsters of the symbol you choose from the level.",	/* 220 - genocide */
	"Fires a large ball of darkness.",
	"Dispels living creatures, attempts to confuse all survivors, and then blankets everything in a cloud of poison.",
	"Learns most attributes of all monsters in line of sight.",
	"Maps the immediate area.",
	"Normal identify spell.",
	"Random large-range displacement.",
	"",
	"Temporary opposition to cold and acid.  Cumulative with equipment resistances.",
	"Removes all cuts and stunning.",
	"Grants temporary protection from evil.",	/* 230 - protection from evil */
	"Temporary increase to armour class and fighting ability.",
	"Teleports away all evil monsters in line of sight.",
	"Increases armour class by 35 temporarily.",
	"Detects all nearby monsters.",
	"Fires a nether bolt.",
	"Fires a life-draining orb.",
	"Attacks all living creatures in line of sight.",
	"Fires a life-draining bolt, heals you, and increases your food by a set amount.",
	"Medium-strength recharging spell.",
	"Turns you into a raging werewolf.",	/* 240 - become werewolf */
	"Breaks both normal and heavy curses.",
	"Turns you into a fell vampire.",
	"Hastens you temporarily.",
	"Allows you to infect a monster with the Black Breath, which prevents regeneration.",
	"Destroys almost all objects nearby, deletes ordinary monsters, and banishes uniques from the level.",
	"Teleports a monster away.",
	"Attacks all undead in line of sight.",
	"Places all undead in a powerful Statis.",
	"Fires a large darkness ball.",
	"Grants temporary telepathy.",	/* 250 - timed ESP */
	"Renders you almost imperceptible to sleeping monsters and those not normally found deeper than twice your depth.  You become fully visible as soon as you inflict any damage on or steal from a monster.",
	"Hastens you and drives you into a berserk rage.",
	"Grants any non-artifact throwing weapon perfect balance.  Be careful about using this spell on weapons that have a hidden quality (use the 'I'nspect command).",
	"",
	"Magically splits your shot.",
	"",
	"",
	"",
	"",
	"",							/* 260 */
	"",
	"",
	"A more accurate shot with a ranged weapon.  Normal shooting speed and damage.",
	"Magically splits your arrow.",
	"A lightning empowered shot that causes a thunderclap on impact.",      /* 265 - storm shot */
	"A shot which deals extra damage to dragons.",
	"A shot which deals extra damage to orcs and trolls.",
	"",
	"",
	"",							/* 270 */
	"A throwing attack which may inflict the Black Breath on your victim.",
	"Fires a venomous shot.",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",							/* 280 */
	"",
	"",
	"",
	"",
	"",
	""
};

/*
 * Prints information about specialty abilties
 */
cptr specialty_tips[TOTAL_SPECIALTIES]=
{
	"Increases the effects of body armor.",
	"Improves shield AC, chance of shield deflection, and damage from shield bashes.",
	"Reduces mana penalties for armor use.",
	"Gives a good chance to avoid melee attacks and a great chance to avoid missile weapons when lightly armored.",
	"Improves your saving throws.",
	"Causes you to speed up after teleporting.  Gives resistance to hostile teleportation.",
	"Increases AC and gives damage resistance in the dark.  Gives stealth and resist darkness.  Allows you to take actions (like reading) without light.  Reduces light radius.",
	"","","","","","","","","","","","","",
	"Grants extra critical hits with melee weapons.",
	"Gives you extra melee attacks; better when you have more attacks to begin with.  Works armed and unarmed.",
	"Grants extra critical hits in ranged combat.",
	"Gives your successful bow and crossbow attacks a chance of continuing to additional targets.",
	"Allows you to hurl throwing weapons and other objects great distances.",
	"Gives you a stronger barehanded attack.",
	"Gives you a powerful unarmed attack.",
	"Allows you to burn monster mana in melee.  Mana burned adds to melee damage.",
	"","","","","","","","","","","","",
	"Enhances your power to slow, sleep, confuse, or turn your enemies.",
	"Increases the effects and durations of beneficial magical effects.",
	"Increases spell casting speed, especially for low level spells from high level casters.",
	"Steals mana from monsters after they cast spells.",
	"Causes spells cast in rapid succession to become increasingly powerful.",
	"Gives you mana when you slay monsters.  May cause damage when overloaded.",
	"Causes you to gain hit points when casting spells.",
	"",
	"Makes your spells stronger when your mana level is high.",
	"Allows you to become 'attuned' to one type of rod, wand, or staff at a time.  Attuned items are easier to activate and more likely to have critical effects.",
	"","","","","","","","","","",
	"Increases and partially sustains Dexterity and Constitution and provides a 5% hitpoint boost.",
	"Increases and partially sustains Intelligence and Wisdom and provides a 5% mana boost.",
	"",
	"Allows you to move faster after attacking or being damaged.",
	"Improves mana regeneration; cumulative with other forms of regeneration.",
	"Improves hit point regeneration; cumulative with other forms of regeneration.",
	"Allows you to set an additional monster trap, and to learn to set more advanced types of traps.",
	"Increases light radius.  Causes undead, evil, and light-sensitive creatures to take extra melee damage and makes them fear your light-based spells.  Grants resistance to light.",
	"","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","", /* 80 - 99 */
	"","","","","","","","","","","","","","","","","","","","", /* 100 - 119 */
	"","","","","","","","",                   /* 120 - 127 */
	"You are slightly more skilled with swords than other melee weapons.",
	"You are slightly more skilled with axes and polearms than other melee weapons.",
	"You are slightly more skilled with blunt weapons than other melee weapons.",
	"You are slightly more skilled with slings than other ranged weapons.",
	"You are slightly more skilled with bows than other ranged weapons.",
	"You are slightly more skilled with crossbows than other ranged weapons.",
	"","","",
	"You are slightly less skilled with swords than other melee weapons.",
	"You are slightly less skilled with axes and polearms than other melee weapons.",
	"You are slightly less skilled with blunt weapons than other melee weapons.",
	"You are slightly less skilled with slings than other ranged weapons.",
	"You are slightly less skilled with bows than other ranged weapons.",
	"You are slightly less skilled with crossbows than other ranged weapons.",
	"","","",
	"You recover quickly from poison and cuts, and succumb slowly to the Black Breath",
	"You eat.  A lot.",
	"You recover very quickly from negative effects.",
	"You are incredibly stealthy, but are vulnerable to bright light.",
	"Your bare hands tear through stone, but you are vulnerable to fire and falling.",
	"You can take the form of a bear (use the ']' command).",
	"","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","", /* 160 - 179 */
	"","","","","","","","","","","","",
	"Your shooting speed with a bow increases quickly with Dexterity.",
	"Your shooting speed with a bow increases very quickly with Dexterity.",
	"Your shooting speed with a sling increases quickly with Dexterity.",
	"Your shooting speed with a sling increases very quickly with Dexterity.",
	"Your shooting speed with a crossbow increases quickly with Dexterity.",
	"Your shooting speed with a crossbow increases very quickly with Dexterity.",
	"","","",
	"You effectively assassinate unsuspecting creatures in melee and with ranged attacks.",
	"You do extra damage when shooting.",
	"You effectively backstab unsuspecting creatures in melee.",
	"You can efficiently spread your attacks over multiple weak opponents at level 40.",
	"You are adept at fighting with your shield as well as your weapon.",
	"You are skilled in hand to hand combat, and are somewhat talented with slings.",
	"You are not comfortable with edged melee weapons, unless they have been Blessed.",
	"",
	"You have a bonus to cause sleep, confusion, and slow.",
	"You have a great understanding of magical devices and can recharge them very reliably.",
	"You are an expert spellcaster and have a large reserve of mana.",
	"Your spells are more likely to 'beam', striking multiple targets.",
	"",
	"You learn quickly about monster abilities.",
	"You carry a pious authority.  You glow with an inner light at level 35 (Priest) or level 45 (Paladin).  You are protected from evil at level 50 (Priest).",
	"You resist fear intrinsically at level 30.  You regenerate hitpoints intrinsically at level 40.",
	"You can learn details of monster attributes at level 35.",
	"You deal with dark forces.  Beware!",
	"You can rob gold from living monsters.",
	"You obtain relatively specific pseudoidentify information.",
	"You can set monster traps.",
	"You are attuned to nature.  You easily move and hide in trees.",
	"You can learn an extra specialty abilty at level 1."
        "","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","",""                 /* 240 - 255 */
};

/*
 * Output numerical values for magical device damages, healing, etc., for
 * an item belonging to an object class whose effects are fully known.  The
 * only way this information can appear is through *identifying*, or by
 * eventual learning through use. -LM-
 */
static cptr extra_data(object_type *o_ptr)
{
	byte tval_to_index;

	/* Boundary control. */
	if (o_ptr->sval > 49) return(NULL);

	/* Table can handle Dragon Scale Mails, */
	if (o_ptr->tval == TV_DRAG_ARMOR) tval_to_index = 0;

	/* Amulets, */
	else if (o_ptr->tval == TV_AMULET) tval_to_index = 1;

	/* Rings, */
	else if (o_ptr->tval == TV_RING) tval_to_index = 2;

	/* Staffs, */
	else if (o_ptr->tval == TV_STAFF) tval_to_index = 3;

	/* Wands, */
	else if (o_ptr->tval == TV_WAND) tval_to_index = 4;

	/* and Rods... */
	else if (o_ptr->tval == TV_ROD) tval_to_index = 5;

	/* ...But nothing else. */
	else return(NULL);


	/* Locate the object in the table, and return the description. */
	return(format("%s", obj_special_info[tval_to_index][o_ptr->sval]));
}




/*
 * Extract and return extended information about an object, including
 * (usually) flavor, (sometimes) damage information for magical items,
 * and (if appropriate) ego and artifact lore. -LM-
 *
 * Code mostly from object_desc and roff_aux.
 */
void object_info(char buf[2048], object_type *o_ptr, bool in_store)
{
	object_kind *k_ptr = &k_info[o_ptr->k_idx];

	char *t;
	cptr s;
	cptr u;
	cptr v;
	cptr w;
	cptr x;

	/* Assume no flavor string, no ego info, and no base info. */
	cptr modstr = "";
	cptr egoinfo = "";
	cptr baseinfo = "";



	/* Standard artifacts have unique descriptions. */
	if ((artifact_p(o_ptr)) && (o_ptr->name1 < ART_MIN_RANDOM) && (object_known_p(o_ptr)))
	{
		artifact_type *a_ptr = &a_info[o_ptr->name1];

#ifdef DELAY_LOAD_A_TEXT

		int fd;

		/* Build the filename */
		path_build(buf, 1024, ANGBAND_DIR_DATA, "a_info.raw");

		/* Open the "raw" file */
		fd = fd_open(buf, O_RDONLY);

		/* Use file */
		if (fd >= 0)
		{
			huge pos;

			/* Starting position */
			pos = a_ptr->text;

			/* Additional offsets */
			pos += a_head->head_size;
			pos += a_head->info_size;
			pos += a_head->name_size;

			/* Seek */
			fd_seek(fd, pos);

			/* Read a chunk of data */
			fd_read(fd, buf, 2048);

			/* Close it */
			fd_close(fd);
		}

#else
		/* If already in memory, simple to access */
		strcpy(buf, a_text + a_ptr->text);

#endif

		/* Return the description, if any. */
		return;
	}

	/* All non-artifact or random artifact objects. */
	else
	{

#ifdef DELAY_LOAD_K_TEXT

		int fd;

		/* Build the filename */
		path_build(buf, 1024, ANGBAND_DIR_DATA, "k_info.raw");

		/* Open the "raw" file */
		fd = fd_open(buf, O_RDONLY);

		/* Use file */
		if (fd >= 0)
		{
			huge pos;

			/* Starting position */
			pos = k_ptr->text;

			/* Additional offsets */
			pos += k_head->head_size;
			pos += k_head->info_size;
			pos += k_head->name_size;

			/* Seek */
			fd_seek(fd, pos);

			/* Read a chunk of data */
			fd_read(fd, buf, 2048);

			/* Close it */
			fd_close(fd);
		}

#else

		/* If already in memory, simple to access */
		strcpy(buf, k_text + k_ptr->text);

#endif

		/* No object description, so return failure. */
		if (!buf[0]) return;


		/* Various object types have different kinds of information. */
		switch(o_ptr->tval)
		{
			/* Dragon Scale Mails */
			case TV_DRAG_ARMOR:
			{
				/* Allow processing of activation information. */
				baseinfo = format("%s", buf);
				break;
			}

			/* Amulets */
			case TV_AMULET:
			{
				/* Color the object, unless in store. */
				if (in_store)
				{
					modstr = "";
					baseinfo = format("An amulet %s", buf);
				}
				else
				{
					modstr = object_adj(o_ptr->tval, o_ptr->sval);
					baseinfo = format("& # amulet %s", buf);
				}

				break;
			}

			/* Rings (including a few "Specials") */
			case TV_RING:
			{
				/* Color the object, unless in store. */
				if (in_store)
				{
					modstr = "";
					baseinfo = format("A ring %s", buf);
				}
				else
				{
					modstr = object_adj(o_ptr->tval, o_ptr->sval);
					baseinfo = format("& # ring %s", buf);
				}

				break;
			}

			/* Staffs */
			case TV_STAFF:
			{
				/* Color the object, unless in store. */
				if (in_store)
				{
					modstr = "";
					baseinfo = format("A staff %s", buf);
				}
				else
				{
					modstr = object_adj(o_ptr->tval, o_ptr->sval);
					baseinfo = format("& # staff %s", buf);
				}

				break;
			}

			/* Wands */
			case TV_WAND:
			{
				/* Color the object, unless in store. */
				if (in_store)
				{
					modstr = "";
					baseinfo = format("A wand %s", buf);
				}
				else
				{
					modstr = object_adj(o_ptr->tval, o_ptr->sval);
					baseinfo = format("& # wand %s", buf);
				}

				break;
			}

			/* Rods */
			case TV_ROD:
			{
				/* Color the object, unless in store. */
				if (in_store)
				{
					modstr = "";
					baseinfo = format("A rod %s", buf);
				}
				else
				{
					modstr = object_adj(o_ptr->tval, o_ptr->sval);
					baseinfo = format("& # rod %s", buf);
				}

				break;
			}

			/* Scrolls */
			case TV_SCROLL:
			{
				/* Color the object, unless in store. */
				if (in_store)
				{
					modstr = "";
					baseinfo = format("A parchment scroll %s", buf);
				}
				else
				{
					modstr = object_adj(o_ptr->tval, o_ptr->sval);
					baseinfo = format("A parchment scroll %s It is titled \"#\".", buf);
				}

				break;
			}

			/* Potions */
			case TV_POTION:
			{
				/* Color the object, unless in store. */
				if (in_store)
				{
					modstr = "";
					baseinfo = format("A potion %s", buf);
				}
				else
				{
					modstr = object_adj(o_ptr->tval, o_ptr->sval);
					baseinfo = format("& # potion %s", buf);
				}

				break;
			}

			/* All other objects can just display the info text. */
			default:
			{
				/* Store the basic info text. */
				baseinfo = format("%s", buf);
			}
		}


		/* Ego-object descriptions are added to any base description. */
		if ((o_ptr->name2) && (object_known_p(o_ptr)))
		{
			ego_item_type *e_ptr = &e_info[o_ptr->name2];
			char ebuf[2048];

			/* First, find the information in memory, or get it from
			 * the binary file.
			 */
#ifdef DELAY_LOAD_E_TEXT

			int fd;

			/* Build the filename */
			path_build(ebuf, 1024, ANGBAND_DIR_DATA, "e_info.raw");

			/* Open the "raw" file */
			fd = fd_open(ebuf, O_RDONLY);

			/* Use file */
			if (fd >= 0)
			{
				huge pos;

				/* Starting position */
				pos = e_ptr->text;

				/* Additional offsets */
				pos += e_head->head_size;
				pos += e_head->info_size;
				pos += e_head->name_size;

				/* Seek */
				fd_seek(fd, pos);

				/* Read a chunk of data */
				fd_read(fd, ebuf, 2048);

				/* Close it */
				fd_close(fd);
			}

#else

			/* If already in memory, simple to access */
			strcpy(ebuf, e_text + e_ptr->text);

#endif

			/* Point to the ego-item information. */
			egoinfo = ebuf;
		}



		/* Point to "buf", and start dumping the result */
		t = buf;


		/*** Assemble the object information. ***/

		/* The object needs an article */
		if (baseinfo[0] == '&')
		{
			/* Skip ampersand and space. */
			s = baseinfo + 2;

			/* Flavor starts with a vowel */
			if (is_a_vowel(modstr[0])) w = "An ";

			/* Flavor starts with a non-vowel */
			else w = "A ";
		}
		else
		{
			w = "";

			/* Start at beginning of base info. */
			s = baseinfo;
		}

		/* Copy the base info, inserting flavor and info text. */
		for (; *s; s++)
		{
			/* Insert article */
			if (s != baseinfo)
			{
				for (; *w; w++) *t++ = *w;
			}

			/* Insert flavor, make it lowercase */
			if (*s == '#')
			{
				char make_lower;

				if (strlen(modstr))
				{
					for (u = modstr; *u; u++)
					{
						make_lower = *u;
						*t++ = tolower(make_lower);
					}
				}
			}

			/* Insert numerical info. */
			else if (*s == '~')
			{
				/* Extra info if object is fully known. */
				if (o_ptr->ident & (IDENT_MENTAL) || k_ptr->known_effect)
				{
					/* Grab the numerical info. */
					cptr moddata = extra_data(o_ptr);

					/* If there is any numerical data,  */
					if (strlen(moddata) > 0)
					{
						/* ...insert a space, and */
						*t++ = ' ';

						/* insert the mumerical data into the string. */
						for (v = moddata; *v; v++) *t++ = *v;
					}
				}

				/* Otherwise, nothing. */
			}

			/* Normally copy. */
			else *t++ = *s;
		}

		/* Extra info for ego items. */
		if ((o_ptr->name2) && (object_known_p(o_ptr)))
		{
			cptr divider = "                                   ---";

			/* Insert a return, a divider, and another return. */
			*t++ = '\n';
			for (x = divider; *x; x++) *t++ = *x;
			*t++ = '\n';

			/* Copy the ego info to the information string. */
			for (x = egoinfo; *x; x++) *t++ = *x;
		}

		/* End the string. */
		*t = '\0';

		/* Return the string. */
		return;
	}
}



/*
 * Describe the "Activation" (if any) for an object or artifact.
 * Return a string, or NULL for "no activation"
 */
cptr item_activation(object_type *o_ptr)
{
	u32b f1, f2, f3;

	/* Extract the flags */
	object_flags(o_ptr, &f1, &f2, &f3);

	/* Require activation ability */
	if (o_ptr->xtra1 != OBJECT_XTRA_TYPE_ACTIVATION) return (NULL);

	/* Some objects and artifacts can be activated */
	switch (o_ptr->xtra2)
	{
		case ACT_GALADRIEL:
		{
			return "illumination (2d15 damage) every 10+d10 turns";
		}
		case ACT_ELENDIL:
		{
			return "magic mapping every 40+d40 turns";
		}
		case ACT_THRAIN:
		{
			return "clairvoyance every 120+d120 turns";
		}
		case ACT_CARLAMMAS:
		{
			return "protection from evil every 225+d225 turns";
		}
		case ACT_INGWE:
		{
			return "dispel evil (x4) every 300+d300 turns";
		}
		case ACT_BOROMIR:
		{
			return "frighten monsters every 40+d40 turns";
		}
		case ACT_FARAMIR:
		{
			return "dispel small life (damage 8) every 55+d55 turns";
		}
		case ACT_TULKAS:
		{
			return "haste self (75+d75 turns) every 150+d150 turns";
		}
		case ACT_NARYA:
		{
			return "large fire ball (225) every 275+d275 turns";
		}
		case ACT_NENYA:
		{
			return "large frost ball (250) every 325+d325 turns";
		}
		case ACT_VILYA:
		{
			return "large lightning ball (275) every 375+d375 turns";
		}
		case ACT_POWER:
		{
			return "bizarre things every 450+d450 turns";
		}
		case ACT_STONE_LORE:
		{
			return "perilous identify every turn";
		}
		case ACT_RAZORBACK:
		{
			return "Assume Dragonform; Activation in Dragonform: star ball (150) every 1000 turns";
		}
		case ACT_BLADETURNER:
		{
			return "Assume Dragonform; Activation in Dragonform: heroism, bless, and resistance every 400 turns";
		}
		case ACT_SOULKEEPER:
		{
			return "heal (1000) every 888 turns";
		}
		case ACT_BELEGENNON:
		{
			return "phase door every 2 turns";
		}
		case ACT_CELEBORN:
		{
			return "genocide every 500 turns";
		}
		case ACT_CASPANION:
		{
			return "door destruction every turn";
		}
		case ACT_HIMRING:
		{
			return "protection from evil every 200 + d200 turns";
		}
		case ACT_ELEMENTS:
		{
			return "protection from the elements every 160 turns";
		}
		case ACT_EARENDIL:
		{
			return "curing every 100 turns";
		}
		case ACT_GIL_GALAD:
		{
			return "blinding light (75) every 250 turns";
		}
		case ACT_HOLHENNETH:
		{
			return "detection every 55+d55 turns";
		}
		case ACT_GONDOR:
		{
			return "heal (500) every 500 turns";
		}
		case ACT_VALINOR:
		{
			return "resistance (20+d20 turns) every 200 turns";
		}
		case ACT_HOLCOLLETH:
		{
			return "Sleep II every 55 turns";
		}
		case ACT_THINGOL:
		{
			return "recharge magical device every 90 turns";
		}
		case ACT_COLANNON:
		{
			return "teleport (100) every 45 turns";
		}
		case ACT_LUTHIEN:
		{
			return "restore life levels every 450 turns";
		}
		case ACT_CAMMITHRIM:
		{
			return "magic missile (2d6) every turn";
		}
		case ACT_EOL:
		{
			return "mana bolt (9d8) every 7+d7 turns";
		}
		case ACT_PAURNIMMEN:
		{
			return "add cold damage to your melee attacks (50 turns) every 100+d50 turns";
		}
		case ACT_PAURAEGEN:
		{
			return "add lightning damage to your melee attacks (40 turns) every 100+d50 turns";
		}
		case ACT_PAURNEN:
		{
			return "add acid damage to your melee attacks (30 turns) every 100+d50 turns";
		}
		case ACT_FINGOLFIN:
		{
			return "instant tunnelling every 3+d3 turns";
		}
		case ACT_FEANOR:
		{
			return "haste self (20+d20 turns) every 200 turns";
		}
		case ACT_DAL:
		{
			return "remove fear and cure poison every 5 turns";
		}
		case ACT_GIMLI:
		{
			return "magic mapping every 35+d35 turns";
		}
		case ACT_NARTHANC:
		{
			return "fire bolt (6d8) every 7+d7 turns";
		}
		case ACT_NIMTHANC:
		{
			return "frost bolt (5d8) every 6+d6 turns";
		}
		case ACT_DETHANC:
		{
			return "lightning bolt (4d8) every 5+d5 turns";
		}
		case ACT_RILIA:
		{
			return "stinking cloud (12) every 4+d4 turns";
		}
		case ACT_BELANGIL:
		{
			return "frost ball (3 * level / 2) every 5+d5 turns";
		}
		case ACT_ARUNRUTH:
		{
			return "frost bolt (12d8) every 300 turns";
		}
		case ACT_RINGIL:
		{
			return "frost cone (250) every 200 turns";
		}
		case ACT_ANDURIL:
		{
			return "fire ball (150) every 200 turns";
		}
		case ACT_THEODEN:
		{
			return "drain life (120) every 400 turns";
		}
		case ACT_AEGLOS:
		{
			return "frost ball (100) every 500 turns";
		}
		case ACT_OROME:
		{
			return "stone to mud every 5 turns";
		}
		case ACT_EONWE:
		{
			return "mass genocide every 1000 turns";
		}
		case ACT_LOTHARANG:
		{
			return "cure wounds (4d12) every 3+d3 turns";
		}
		case ACT_ULMO:
		{
			return "teleport away every 75 turns (distance: 45-60+)";
		}
		case ACT_AVAVIR:
		{
			return "word of recall every 200 turns";
		}
		case ACT_TOTILA:
		{
			return "confuse monster every 15 turns";
		}
		case ACT_FIRESTAR:
		{
			return "large fire ball (125) every 150 turns";
		}
		case ACT_TARATOL:
		{
			return "haste self (20+d20 turns) every 100+d100 turns";
		}
		case ACT_ERIRIL:
		{
			return "identify every 10 turns";
		}
		case ACT_OLORIN:
		{
			return "probing every 20 turns";
		}
		case ACT_TURMIL:
		{
			return "drain life (90) every 70 turns";
		}
		case ACT_HARAD:
		{
			return "a deadly shot every 200+d200 turns";
		}
		case ACT_CUBRAGOL:
		{
			return "fire branding of bolts every 999 turns";
		}
		case ACT_BUCKLAND:
		{
			return "elemental branding of shots every 1500 turns";
		}


		case ACT_RANDOM_FIRE1:
		{
			return "fire bolt (3 + level / 8)d8 every 7+d7 turns";
		}
		case ACT_RANDOM_FIRE2:
		{
			return "sphere of fire (90) every 250 turns";
		}
		case ACT_RANDOM_FIRE3:
		{
			return "fire storm (150) every 600 turns";
		}
		case ACT_RANDOM_COLD1:
		{
			return "frost bolt (3 + level / 8)d8 every 7+d7 turns";
		}
		case ACT_RANDOM_COLD2:
		{
			return "sphere of frost (90) every 250 turns";
		}
		case ACT_RANDOM_COLD3:
		{
			return "frost storm (150) every 600 turns";
		}
		case ACT_RANDOM_ACID1:
		{
			return "acid bolt (3 + level / 8)d8 every 7+d7 turns";
		}
		case ACT_RANDOM_ACID2:
		{
			return "sphere of acid (90) every 300 turns";
		}
		case ACT_RANDOM_ACID3:
		{
			return "acid storm (160) every 800 turns";
		}
		case ACT_RANDOM_ELEC1:
		{
			return "electricity bolt (3 + level / 8)d8 every 7+d7 turns";
		}
		case ACT_RANDOM_ELEC2:
		{
			return "ball lightning (100) every 300 turns";
		}
		case ACT_RANDOM_ELEC3:
		{
			return "lightning strike (130+25) every 800 turns";
		}
		case ACT_RANDOM_POIS1:
		{
			return "poison dart (3 + level / 10)d8 every 22+d22 turns";
		}
		case ACT_RANDOM_POIS2:
		{
			return "poison cloud (110) every 300 turns";
		}
		case ACT_RANDOM_LIGHT1:
		{
			return "blinding ball of light (50+10) every 250 turns";
		}
		case ACT_RANDOM_LIGHT2:
		{
			return "dispel light-hating (175) every 600 turns";
		}

		case ACT_RANDOM_DISPEL_UNDEAD:
		{
			return "dispel undead (100) every 300 turns";
		}
		case ACT_RANDOM_DISPEL_EVIL:
		{
			return "dispel evil (100) every 400 turns";
		}
		case ACT_RANDOM_SMITE_UNDEAD:
		{
			return "dispel an undead (level / 4)d33 every 200 turns";
		}
		case ACT_RANDOM_SMITE_DEMON:
		{
			return "dispel a demon (level / 4)d33 every 200 turns";
		}
		case ACT_RANDOM_SMITE_DRAGON:
		{
			return "dispel a dragon (level / 4)d33 every 200 turns";
		}
		case ACT_RANDOM_HOLY_ORB:
		{
			return "holy orb (60) every 175 turns";
		}
		case ACT_RANDOM_BLESS:
		{
			return "blessing (24+d24) every 200 turns";
		}
		case ACT_RANDOM_FRIGHTEN_ALL:
		{
			return "frighten adversaries every 120+d120 turns";
		}
		case ACT_RANDOM_HEAL1:
		{
			return "heal (5d20) every 85 turns";
		}
		case ACT_RANDOM_HEAL2:
		{
			return "heal (7d40) every 225 turns";
		}
		case ACT_RANDOM_HEAL3:
		{
			return "heal (10d60) every 500 turns";
		}
		case ACT_RANDOM_CURE:
		{
			return "cure ailments every 500 turns";
		}
		case ACT_RANDOM_PROT_FROM_EVIL:
		{
			return "protection from evil (24+d24) every 250 turns";
		}
		case ACT_RANDOM_CHAOS:
		{
			return "chaos ball (d300) every 600 turns";
		}
		case ACT_RANDOM_SHARD_SOUND:
		{
			return "shard or sound ball (150) every 600 turns";
		}
		case ACT_RANDOM_NETHR:
		{
			return "nether orb (100) every 400 turns";
		}
		case ACT_RANDOM_LINE_LIGHT:
		{
			return "ray of light (4d5) every 6+d6 turns";
		}
		case ACT_RANDOM_STARLIGHT:
		{
			return "starlight (4d5) every 8+d8 turns";
		}
		case ACT_RANDOM_EARTHQUAKE:
		{
			return "earthquake (radius 10) every 40+d40 turns";
		}
		case ACT_RANDOM_IDENTIFY:
		{
			return "identify every 30 turns";
		}
		case ACT_RANDOM_SPEED:
		{
			return "haste self (20+d20) every 120+d120 turns";
		}
		case ACT_RANDOM_TELEPORT_AWAY:
		{
			return "teleport away every 110 turns (distance: 45-60+)";
		}
		case ACT_RANDOM_HEROISM:
		{
			return "heroism every 200 turns";
		}
		case ACT_RANDOM_STORM_DANCE:
		{
			return "storm dance every 300 turns";
		}
		case ACT_RANDOM_RESIST_ELEMENTS:
		{
			return "resistance to the elements every 400 turns";
		}
		case ACT_RANDOM_RESIST_ALL:
		{
			return "resistance every 400 turns";
		}
		case ACT_RANDOM_TELEPORT1:
		{
			return "teleport self (30) every 10+d10 turns";
		}
		case ACT_RANDOM_TELEPORT2:
		{
			return "major displacement (200) every 80 turns";
		}
		case ACT_RANDOM_RECALL:
		{
			return "recall every 350 turns";
		}
		case ACT_RANDOM_REGAIN:
		{
			return "restore level every 800 turns";
		}
		case ACT_RANDOM_RESTORE:
		{
			return "restore stats every 800 turns";
		}
		case ACT_RANDOM_SHIELD:
		{
			return "magic shield every 400 turns";
		}
		case ACT_RANDOM_BRAND_MISSILE:
		{
			return "brand missiles every 1750 turns";
		}
		case ACT_RANDOM_SUPER_SHOOTING:
		{
			return "an especially deadly shot every 200+d200 turns";
		}
		case ACT_RANDOM_DETECT_MONSTERS:
		{
			return "detect monsters every 4+d4 turns";
		}
		case ACT_RANDOM_DETECT_EVIL:
		{
			return "detect evil every 4+d4 turns";
		}
		case ACT_RANDOM_DETECT_ALL:
		{
			return "detection every 30+d30 turns";
		}
		case ACT_RANDOM_MAGIC_MAP:
		{
			return "sense surroundings every 30+d30 turns";
		}
		case ACT_RANDOM_DETECT_D_S_T:
		{
			return "detect traps, doors, and stairs every 10+d10 turns";
		}
		case ACT_RANDOM_CONFU_FOE:
		{
			return "strong confuse monster every 250 turns";
		}
		case ACT_RANDOM_SLEEP_FOE:
		{
			return "strong sleep monster every 250 turns";
		}
		case ACT_RANDOM_TURN_FOE:
		{
			return "strong frighten monster every 250 turns";
		}
		case ACT_RANDOM_SLOW_FOE:
		{
			return "strong slow monster every 250 turns";
		}
		case ACT_RANDOM_BANISH_EVIL:
		{
			return "banish evil every 400 turns";
		}
		case ACT_RANDOM_DISARM:
		{
			return "disarming every 7+d7 turns";
		}
		case ACT_RANDOM_CONFU_FOES:
		{
			return "confuse monsters every 300 turns";
		}
		case ACT_RANDOM_SLEEP_FOES:
		{
			return "sleep monsters every 300 turns";
		}
		case ACT_RANDOM_TURN_FOES:
		{
			return "frighten monsters every 300 turns";
		}
		case ACT_RANDOM_SLOW_FOES:
		{
			return "slow monsters every 300 turns";
		}

		case ACT_DRAGON_BLUE:
		{
			return "assume dragon form; Activation in dragon form: breathe lightning (130) every 350+d350 turns";
		}
		case ACT_DRAGON_WHITE:
		{
			return "assume dragon form; Activation in dragon form: breathe frost (140) every 350+d350 turns";
		}
		case ACT_DRAGON_BLACK:
		{
			return "assume dragon form; Activation in dragon form: breathe acid (150) every 350+d350 turns";
		}
		case ACT_DRAGON_GREEN:
		{
			return "assume dragon form; Activation in dragon form: breathe poison gas (150) every 350+d350 turns";
		}
		case ACT_DRAGON_RED:
		{
			return "assume dragon form; Activation in dragon form: breathe fire (160) every 350+d350 turns";
		}
		case ACT_DRAGON_MULTIHUED:
		{
			return "assume dragon form; Activation in dragon form: breathe an element or poison (190) every 350+d350 turns";
		}
		case ACT_DRAGON_BRONZE:
		{
			return "assume dragon form; Activation in dragon form: breathe confusion (130) every 300+d300 turns";
		}
		case ACT_DRAGON_GOLD:
		{
			return "assume dragon form; Activation in dragon form: breathe sound (130) every 300+d300 turns";
		}
		case ACT_DRAGON_CHAOS:
		{
			return "assume dragon form; Activation in dragon form: breathe chaos/disenchant (180) every 300+d300 turns";
		}
		case ACT_DRAGON_LAW:
		{
			return "assume dragon form; Activation in dragon form: breathe sound/shards (190) every 300+d300 turns";
		}
		case ACT_DRAGON_BALANCE:
		{
			return "assume dragon form; Activation in dragon form: breathe balance (210) every 300+d300 turns";
		}
		case ACT_DRAGON_SHINING:
		{
			return "assume dragon form; Activation in dragon form: breathe light/darkness (160) every 300+d300 turns";
		}
		case ACT_DRAGON_POWER:
		{
			return "assume dragon form; Activation in dragon form: breathe the elements (240) every 300+d300 turns";
		}

		case ACT_RING_ACID:
		{
			return "cast a acid ball(80) and oppose acid every 50+d100 turns";
		}
		case ACT_RING_COLD:
		{
			return "cast a cold ball(80) and oppose cold every 50+d100 turns";
		}
		case ACT_RING_FIRE:
		{
			return "cast a fire ball(80) and oppose fire every 50+d100 turns";
		}
		case ACT_RING_ELEC:
		{
			return "cast a electricity ball(80) and oppose electricity every 50+d100 turns";
		}
		case ACT_AMULET_ESCAPING:
		{
			return "teleport(40) every 40+d40 turns";
		}
		case ACT_AMULET_LION:
		{
			return "become lion every 40+d40 turns";
		}
		case ACT_BALROG_WHIP:
		{
			return "lash out at at range 2 for base weapon damage (unless target resists fire)";
		}
		default:
		{
			return "an undocumented activation";
		}
	}


	/* Nothing else activates. */
	return NULL;
}


/*
 * Describe a "fully identified" item.  Rewritten to use "roff" and to
 * harmonize with other description code. -LM-
 */
void identify_fully_aux(object_type *o_ptr)
{
	int j;

	u32b f1, f2, f3;

	int attr_listed = 0;
	int attr_num = 0;

	/* Extract the flags */
	object_flags(o_ptr, &f1, &f2, &f3);

	/* Describe activation, if present. */
	if (o_ptr->xtra1 == OBJECT_XTRA_TYPE_ACTIVATION)
	{
		roff(format("Activation: %s\n", item_activation(o_ptr)), 3, 77);
	}


	/* Hack -- describe lite's */
	if (o_ptr->tval == TV_LITE)
	{
		if (artifact_p(o_ptr) && (o_ptr->k_idx != 477))
		{
			roff("It provides light (radius 3) forever.\n", 3, 77);
		}
		else if (o_ptr->sval == SV_LITE_LANTERN)
		{
			roff("It provides light (radius 2) when fueled.\n", 3, 77);
		}
		else if (o_ptr->sval == SV_LITE_TORCH)
		{
			roff("It provides light (radius 1) when fueled.\n", 3, 77);
		}
	}


	/* And then describe it fully */

	/* Affects stats. */
	if ((o_ptr->pval) && ((f1 & (TR1_STR)) || (f1 & (TR1_INT)) ||
		(f1 & (TR1_WIS)) || (f1 & (TR1_DEX)) || (f1 & (TR1_CON)) ||
		(f1 & (TR1_CHR))))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f1 & (TR1_STR)) attr_num++;
		if (f1 & (TR1_INT)) attr_num++;
		if (f1 & (TR1_WIS)) attr_num++;
		if (f1 & (TR1_DEX)) attr_num++;
		if (f1 & (TR1_CON)) attr_num++;
		if (f1 & (TR1_CHR)) attr_num++;

		/* Special case:  all stats */
		if (attr_num == 6)
		{
			if (o_ptr->pval > 0) roff("It increases all your stats", 3, 77);
			else roff("It decreases all your stats", 3, 77);
		}
		else
		{
			if (o_ptr->pval > 0) roff("It increases your", 3, 77);
			else roff("It decreases your", 3, 77);

			/* Loop for number of attributes in this group. */
			for (j = 0; j < 6; j++)
			{
				bool list_ok = FALSE;

				if ((j == 0) && (f1 & (TR1_STR))) list_ok = TRUE;
				if ((j == 1) && (f1 & (TR1_INT))) list_ok = TRUE;
				if ((j == 2) && (f1 & (TR1_WIS))) list_ok = TRUE;
				if ((j == 3) && (f1 & (TR1_DEX))) list_ok = TRUE;
				if ((j == 4) && (f1 & (TR1_CON))) list_ok = TRUE;
				if ((j == 5) && (f1 & (TR1_CHR))) list_ok = TRUE;

				if (!list_ok) continue;

				/* Listing another attribute. */
				attr_listed++;

				/* Commas separate members of a list of more than two. */
				if ((attr_num > 2) && (attr_listed > 1)) roff(",", 3, 77);

				/* "and" before final member of a list of more than one. */
				if ((attr_num > 1) && (j != 0))
				{
					if (attr_num == attr_listed) roff(" and", 3, 77);
				}

				/* List the attribute description, in its proper place. */
				if (j == 0) roff(" strength", 3, 77);
				if (j == 1) roff(" intelligence", 3, 77);
				if (j == 2) roff(" wisdom", 3, 77);
				if (j == 3) roff(" dexterity", 3, 77);
				if (j == 4) roff(" constitution", 3, 77);
				if (j == 5) roff(" charisma", 3, 77);
			}
		}

		/* Describe exact bonus or penalty. */
		roff(format(" by %d", o_ptr->pval), 3, 77);

		/* End sentence.  Go to next line. */
		roff(". \n", 3, 77);
	}


	/* Sustain stats. */
	if ((f2 & (TR2_SUST_STR)) || (f2 & (TR2_SUST_INT)) || (f2 & (TR2_SUST_WIS))
		|| (f2 & (TR2_SUST_DEX)) || (f2 & (TR2_SUST_CON)) ||
		(f2 & (TR2_SUST_CHR)))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f2 & (TR2_SUST_STR)) attr_num++;
		if (f2 & (TR2_SUST_INT)) attr_num++;
		if (f2 & (TR2_SUST_WIS)) attr_num++;
		if (f2 & (TR2_SUST_DEX)) attr_num++;
		if (f2 & (TR2_SUST_CON)) attr_num++;
		if (f2 & (TR2_SUST_CHR)) attr_num++;

		/* Special case:  sustain all stats */
		if (attr_num == 6)
		{
			roff("It sustains all your stats", 3, 77);
		}
		else
		{
			roff("It sustains your", 3, 77);

			/* Loop for number of attributes in this group. */
			for (j = 0; j < 6; j++)
			{
				bool list_ok = FALSE;

				if ((j == 0) && (f2 & (TR2_SUST_STR))) list_ok = TRUE;
				if ((j == 1) && (f2 & (TR2_SUST_INT))) list_ok = TRUE;
				if ((j == 2) && (f2 & (TR2_SUST_WIS))) list_ok = TRUE;
				if ((j == 3) && (f2 & (TR2_SUST_DEX))) list_ok = TRUE;
				if ((j == 4) && (f2 & (TR2_SUST_CON))) list_ok = TRUE;
				if ((j == 5) && (f2 & (TR2_SUST_CHR))) list_ok = TRUE;

				if (!list_ok) continue;

				/* Listing another attribute. */
				attr_listed++;

				/* Commas separate members of a list of more than two. */
				if ((attr_num > 2) && (attr_listed > 1)) roff(",", 3, 77);

				/* "and" before final member of a list of more than one. */
				if ((attr_num > 1) && (j != 0))
				{
					if (attr_num == attr_listed) roff(" and", 3, 77);
				}

				/* List the attribute description, in its proper place. */
				if (j == 0) roff(" strength", 3, 77);
				if (j == 1) roff(" intelligence", 3, 77);
				if (j == 2) roff(" wisdom", 3, 77);
				if (j == 3) roff(" dexterity", 3, 77);
				if (j == 4) roff(" constitution", 3, 77);
				if (j == 5) roff(" charisma", 3, 77);
			}
		}

		/* End sentence.  Go to next line. */
		roff(". \n", 3, 77);
	}


	/* Affects other pval-dependant qualities. */
	if ((o_ptr->pval) && ((f1 & (TR1_MAGIC_MASTERY)) || (f1 & (TR1_STEALTH)) ||
		(f1 & (TR1_SEARCH)) || (f1 & (TR1_INFRA)) || (f1 & (TR1_TUNNEL)) ||
		(f1 & (TR1_SPEED))))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f1 & (TR1_MAGIC_MASTERY)) attr_num++;
		if (f1 & (TR1_STEALTH)) attr_num++;
		if (f1 & (TR1_SEARCH)) attr_num++;
		if (f1 & (TR1_INFRA)) attr_num++;
		if (f1 & (TR1_TUNNEL)) attr_num++;
		if (f1 & (TR1_SPEED)) attr_num++;

		if (o_ptr->pval > 0) roff("It increases your", 3, 77);
		else roff("It decreases your", 3, 77);

		/* Loop for number of attributes in this group. */
		for (j = 0; j < 6; j++)
		{
			bool list_ok = FALSE;

			if ((j == 0) && (f1 & (TR1_MAGIC_MASTERY))) list_ok = TRUE;
			if ((j == 1) && (f1 & (TR1_STEALTH))) list_ok = TRUE;
			if ((j == 2) && (f1 & (TR1_SEARCH))) list_ok = TRUE;
			if ((j == 3) && (f1 & (TR1_INFRA))) list_ok = TRUE;
			if ((j == 4) && (f1 & (TR1_TUNNEL))) list_ok = TRUE;
			if ((j == 5) && (f1 & (TR1_SPEED))) list_ok = TRUE;

			if (!list_ok) continue;

			/* Listing another attribute. */
			attr_listed++;

			/* Commas separate members of a list of more than two. */
			if ((attr_num > 2) && (attr_listed > 1)) roff(",", 3, 77);

			/* "and" before final member of a list of more than one. */
			if ((attr_num > 1) && (j != 0))
			{
				if (attr_num == attr_listed) roff(" and", 3, 77);
			}

			/* List the attribute description, in its proper place. */
			if (j == 0) roff(" magical device skill", 3, 77);
			if (j == 1) roff(" stealth", 3, 77);
			if (j == 2) roff(" searching", 3, 77);
			if (j == 3) roff(" infravision", 3, 77);
			if (j == 4) roff(" tunnelling ability", 3, 77);
			if (j == 5) roff(" speed", 3, 77);
		}

		/* Describe exact bonus or penalty. */
		roff(format(" by %d", o_ptr->pval), 3, 77);

		/* End sentence.  Go to next line. */
		roff(". \n", 3, 77);
	}


	/* Describe missile weapon attributes. */
	if (o_ptr->tval == TV_BOW)
	{
		if ((f1 & (TR1_SHOTS)) && (f1 & (TR1_MIGHT2)))
		{
			roff("It affects your shooting speed, and greatly affects your shooting power. \n", 3, 77);
		}
		else if ((f1 & (TR1_SHOTS)) && (f1 & (TR1_MIGHT1)))
		{
			roff("It affects both your shooting speed and power. \n", 3, 77);
		}
		else if (f1 & (TR1_MIGHT1))
		{
			roff("It affects your shooting power. \n", 3, 77);
		}
		else if (f1 & (TR1_SHOTS))
		{
			roff("It affects your shooting speed. \n", 3, 77);
		}
	}


	/* Slays. */
	if ((f1 & (TR1_SLAY_ANIMAL)) || (f1 & (TR1_SLAY_EVIL)) ||
		(f1 & (TR1_SLAY_UNDEAD)) || (f1 & (TR1_SLAY_DEMON)) ||
		(f1 & (TR1_SLAY_ORC)) || (f1 & (TR1_SLAY_TROLL)) ||
		(f1 & (TR1_SLAY_GIANT)) || (f1 & (TR1_SLAY_DRAGON)))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f1 & (TR1_SLAY_ANIMAL)) attr_num++;
		if (f1 & (TR1_SLAY_EVIL)) attr_num++;
		if (f1 & (TR1_SLAY_UNDEAD)) attr_num++;
		if (f1 & (TR1_SLAY_DEMON)) attr_num++;
		if (f1 & (TR1_SLAY_ORC)) attr_num++;
		if (f1 & (TR1_SLAY_TROLL)) attr_num++;
		if (f1 & (TR1_SLAY_GIANT)) attr_num++;
		if (f1 & (TR1_SLAY_DRAGON)) attr_num++;

		/* Special message for Kill brands */
		if (f1 & (TR1_SLAY_KILL))
		{
		        roff("It is the great bane of", 3, 77);
		}

		/* Ordinary message for Slay brands */
		else
		{
		        roff("It slays", 3, 77);
		}

		/* Loop for number of attributes in this group. */
		for (j = 0; j < 8; j++)
		{
			bool list_ok = FALSE;

			if ((j == 0) && (f1 & (TR1_SLAY_ANIMAL))) list_ok = TRUE;
			if ((j == 1) && (f1 & (TR1_SLAY_EVIL))) list_ok = TRUE;
			if ((j == 2) && (f1 & (TR1_SLAY_UNDEAD))) list_ok = TRUE;
			if ((j == 3) && (f1 & (TR1_SLAY_DEMON))) list_ok = TRUE;
			if ((j == 4) && (f1 & (TR1_SLAY_ORC))) list_ok = TRUE;
			if ((j == 5) && (f1 & (TR1_SLAY_TROLL))) list_ok = TRUE;
			if ((j == 6) && (f1 & (TR1_SLAY_GIANT))) list_ok = TRUE;
			if ((j == 7) && (f1 & (TR1_SLAY_DRAGON))) list_ok = TRUE;

			if (!list_ok) continue;

			/* Listing another attribute. */
			attr_listed++;

			/* Commas separate members of a list of more than two. */
			if ((attr_num > 2) && (attr_listed > 1)) roff(",", 3, 77);

			/* "and" before final member of a list of more than one. */
			if ((attr_num > 1) && (j != 0))
			{
				if (attr_num == attr_listed) roff(" and", 3, 77);
			}

			/* List the attribute description, in its proper place. */
			if (j == 0) roff(" animals", 3, 77);
			if (j == 1) roff(" evil", 3, 77);
			if (j == 2) roff(" undead", 3, 77);
			if (j == 3) roff(" demons", 3, 77);
			if (j == 4) roff(" orcs", 3, 77);
			if (j == 5) roff(" trolls", 3, 77);
			if (j == 6) roff(" giants", 3, 77);
			if (j == 7) roff(" dragons", 3, 77);
		}

		/* End sentence.  Go to next line. */
		roff(". \n", 3, 77);
	}


	/* Elemental and poison brands. */
	if ((f1 & (TR1_BRAND_ACID)) || (f1 & (TR1_BRAND_ELEC)) ||
		(f1 & (TR1_BRAND_FIRE)) || (f1 & (TR1_BRAND_COLD)) ||
		(f1 & (TR1_BRAND_POIS)))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f1 & (TR1_BRAND_ACID)) attr_num++;
		if (f1 & (TR1_BRAND_ELEC)) attr_num++;
		if (f1 & (TR1_BRAND_FIRE)) attr_num++;
		if (f1 & (TR1_BRAND_COLD)) attr_num++;
		if (f1 & (TR1_BRAND_POIS)) attr_num++;

		roff("It does extra damage from", 3, 77);

		/* Loop for number of attributes in this group. */
		for (j = 0; j < 5; j++)
		{
			bool list_ok = FALSE;

			if ((j == 0) && (f1 & (TR1_BRAND_ACID))) list_ok = TRUE;
			if ((j == 1) && (f1 & (TR1_BRAND_ELEC))) list_ok = TRUE;
			if ((j == 2) && (f1 & (TR1_BRAND_FIRE))) list_ok = TRUE;
			if ((j == 3) && (f1 & (TR1_BRAND_COLD))) list_ok = TRUE;
			if ((j == 4) && (f1 & (TR1_BRAND_POIS))) list_ok = TRUE;

			if (!list_ok) continue;

			/* Listing another attribute. */
			attr_listed++;

			/* Commas separate members of a list of more than two. */
			if ((attr_num > 2) && (attr_listed > 1)) roff(",", 3, 77);

			/* "and" before final member of a list of more than one. */
			if ((attr_num > 1) && (j != 0))
			{
				if (attr_num == attr_listed) roff(" and", 3, 77);
			}

			/* List the attribute description, in its proper place. */
			if (j == 0) roff(" acid", 3, 77);
			if (j == 1) roff(" electricity", 3, 77);
			if (j == 2) roff(" fire", 3, 77);
			if (j == 3) roff(" frost", 3, 77);
			if (j == 4) roff(" poison", 3, 77);
		}

		/* End sentence.  Go to next line. */
		roff(". \n", 3, 77);
	}


	/* Throwing weapons. */
	if (f1 & (TR1_THROWING))
	{
		if (f1 & (TR1_PERFECT_BALANCE))
		{
			roff("It can be thrown hard and fast. \n", 3, 77);
		}
		roff("It can be thrown effectively. \n", 3, 77);
	}


	/* Elemental immunities. */
	if ((f2 & (TR2_IM_ACID)) || (f2 & (TR2_IM_ELEC)) ||
		(f2 & (TR2_IM_FIRE)) || (f2 & (TR2_IM_COLD)))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f2 & (TR2_IM_ACID)) attr_num++;
		if (f2 & (TR2_IM_ELEC)) attr_num++;
		if (f2 & (TR2_IM_FIRE)) attr_num++;
		if (f2 & (TR2_IM_COLD)) attr_num++;

		roff("It provides immunity to", 3, 77);

		/* Loop for number of attributes in this group. */
		for (j = 0; j < 4; j++)
		{
			bool list_ok = FALSE;

			if ((j == 0) && (f2 & (TR2_IM_ACID))) list_ok = TRUE;
			if ((j == 1) && (f2 & (TR2_IM_ELEC))) list_ok = TRUE;
			if ((j == 2) && (f2 & (TR2_IM_FIRE))) list_ok = TRUE;
			if ((j == 3) && (f2 & (TR2_IM_COLD))) list_ok = TRUE;

			if (!list_ok) continue;

			/* Listing another attribute. */
			attr_listed++;

			/* Commas separate members of a list of more than two. */
			if ((attr_num > 2) && (attr_listed > 1)) roff(",", 3, 77);

			/* "and" before final member of a list of more than one. */
			if ((attr_num > 1) && (j != 0))
			{
				if (attr_num == attr_listed) roff(" and", 3, 77);
			}

			/* List the attribute description, in its proper place. */
			if (j == 0) roff(" acid", 3, 77);
			if (j == 1) roff(" electricity", 3, 77);
			if (j == 2) roff(" fire", 3, 77);
			if (j == 3) roff(" frost", 3, 77);
		}

		/* End sentence.  Go to next line. */
		roff(". \n", 3, 77);
	}


	/* Broad minor resistance. */
	if (f2 & (TR2_RES_BASE_MINOR))
	{
		roff("It provides minor resistance to acid, electricity, fire, and frost. \n", 3, 77);
	}

	/* Resistances. */
	if ((f2 & (TR2_RES_ACID)) || (f2 & (TR2_RES_ELEC)) ||
		(f2 & (TR2_RES_FIRE)) || (f2 & (TR2_RES_COLD)) ||
		(f2 & (TR2_RES_POIS)) || (f2 & (TR2_RES_LITE)) ||
		(f2 & (TR2_RES_DARK)) || (f2 & (TR2_RES_SOUND)) ||
		(f2 & (TR2_RES_SHARD)) || (f2 & (TR2_RES_NEXUS)) ||
		(f2 & (TR2_RES_NETHR)) || (f2 & (TR2_RES_CHAOS)) ||
		(f2 & (TR2_RES_DISEN)))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f2 & (TR2_RES_ACID)) attr_num++;
		if (f2 & (TR2_RES_ELEC)) attr_num++;
		if (f2 & (TR2_RES_FIRE)) attr_num++;
		if (f2 & (TR2_RES_COLD)) attr_num++;
		if (f2 & (TR2_RES_POIS)) attr_num++;
		if (f2 & (TR2_RES_LITE)) attr_num++;
		if (f2 & (TR2_RES_DARK)) attr_num++;
		if (f2 & (TR2_RES_SOUND)) attr_num++;
		if (f2 & (TR2_RES_SHARD)) attr_num++;
		if (f2 & (TR2_RES_NEXUS)) attr_num++;
		if (f2 & (TR2_RES_NETHR)) attr_num++;
		if (f2 & (TR2_RES_CHAOS)) attr_num++;
		if (f2 & (TR2_RES_DISEN)) attr_num++;

		roff("It provides resistance to", 3, 77);

		/* Loop for number of attributes in this group. */
		for (j = 0; j < 13; j++)
		{
			bool list_ok = FALSE;

			if ((j ==  0) && (f2 & (TR2_RES_ACID)))  list_ok = TRUE;
			if ((j ==  1) && (f2 & (TR2_RES_ELEC)))  list_ok = TRUE;
			if ((j ==  2) && (f2 & (TR2_RES_FIRE)))  list_ok = TRUE;
			if ((j ==  3) && (f2 & (TR2_RES_COLD)))  list_ok = TRUE;
			if ((j ==  4) && (f2 & (TR2_RES_POIS)))  list_ok = TRUE;
			if ((j ==  5) && (f2 & (TR2_RES_LITE)))  list_ok = TRUE;
			if ((j ==  6) && (f2 & (TR2_RES_DARK)))  list_ok = TRUE;
			if ((j ==  7) && (f2 & (TR2_RES_SOUND))) list_ok = TRUE;
			if ((j ==  8) && (f2 & (TR2_RES_SHARD))) list_ok = TRUE;
			if ((j ==  9) && (f2 & (TR2_RES_NEXUS))) list_ok = TRUE;
			if ((j == 10) && (f2 & (TR2_RES_NETHR))) list_ok = TRUE;
			if ((j == 11) && (f2 & (TR2_RES_CHAOS))) list_ok = TRUE;
			if ((j == 12) && (f2 & (TR2_RES_DISEN))) list_ok = TRUE;

			if (!list_ok) continue;

			/* Listing another attribute. */
			attr_listed++;

			/* Commas separate members of a list of more than two. */
			if ((attr_num > 2) && (attr_listed > 1)) roff(",", 3, 77);

			/* "and" before final member of a list of more than one. */
			if ((attr_num > 1) && (j != 0))
			{
				if (attr_num == attr_listed) roff(" and", 3, 77);
			}

			/* List the attribute description, in its proper place. */
			if (j ==  0) roff(" acid", 3, 77);
			if (j ==  1) roff(" electricity", 3, 77);
			if (j ==  2) roff(" fire", 3, 77);
			if (j ==  3) roff(" frost", 3, 77);
			if (j ==  4) roff(" poison", 3, 77);
			if (j ==  5) roff(" light", 3, 77);
			if (j ==  6) roff(" darkness", 3, 77);
			if (j ==  7) roff(" sound", 3, 77);
			if (j ==  8) roff(" shards", 3, 77);
			if (j ==  9) roff(" nexus", 3, 77);
			if (j == 10) roff(" nether", 3, 77);
			if (j == 11) roff(" chaos", 3, 77);
			if (j == 12) roff(" disenchantment", 3, 77);
		}

		/* End sentence.  Go to next line. */
		roff(". \n", 3, 77);
	}


	/* Clear a listing variable. */
	attr_num = 0;

	/* Special processing for the three "survival resists" */
	if (f2 & (TR2_RES_FEAR)) attr_num++;
	if (f2 & (TR2_RES_BLIND)) attr_num++;
	if (f2 & (TR2_RES_CONFU)) attr_num++;

	if (f2 & (TR2_RES_FEAR))
	{
		roff("It renders you fearless", 3, 77);
		if (attr_num == 1) roff(". \n", 3, 77);
		else roff(", and", 3, 77);
	}

	if (f2 & (TR2_RES_BLIND))
	{
		if ((attr_num > 1) && (f2 & (TR2_RES_FEAR)))
			roff(" provides resistance to blindness", 3, 77);
		else roff("It provides resistance to blindness", 3, 77);

		if (f2 & (TR2_RES_CONFU)) roff(" and", 3, 77);
		else roff(". \n", 3, 77);
	}

	if (f2 & (TR2_RES_CONFU))
	{
		if ((attr_num > 1) && (!(f2 & (TR2_RES_BLIND))))
			roff(" provides resistance to confusion.\n", 3, 77);
		else if (attr_num > 1) roff(" confusion.\n", 3, 77);
		else roff("It provides resistance to confusion.\n", 3, 77);
	}


	/* Miscellanious abilities. */
	if ((f3 & (TR3_SLOW_DIGEST)) || (f3 & (TR3_FEATHER)) ||
		(f3 & (TR3_LITE)) || (f3 & (TR3_REGEN)) ||
		(f3 & (TR3_TELEPATHY)) || (f3 & (TR3_SEE_INVIS)) ||
		(f3 & (TR3_FREE_ACT)) || (f3 & (TR3_HOLD_LIFE)) ||
		(f3 & (TR3_IMPACT)) || (f3 & (TR3_BLESSED)))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f3 & (TR3_SLOW_DIGEST)) attr_num++;
		if (f3 & (TR3_FEATHER)) attr_num++;
		if (f3 & (TR3_LITE)) attr_num++;
		if (f3 & (TR3_REGEN)) attr_num++;
		if (f3 & (TR3_TELEPATHY)) attr_num++;
		if (f3 & (TR3_SEE_INVIS)) attr_num++;
		if (f3 & (TR3_FREE_ACT)) attr_num++;
		if (f3 & (TR3_HOLD_LIFE)) attr_num++;
		if (f3 & (TR3_IMPACT)) attr_num++;
		if (f3 & (TR3_BLESSED)) attr_num++;

		roff("It", 3, 77);

		/* Loop for number of attributes in this group. */
		for (j = 0; j < 10; j++)
		{
			bool list_ok = FALSE;

			if ((j == 0) && (f3 & (TR3_SLOW_DIGEST))) list_ok = TRUE;
			if ((j == 1) && (f3 & (TR3_FEATHER))) list_ok = TRUE;
			if ((j == 2) && (f3 & (TR3_LITE))) list_ok = TRUE;
			if ((j == 3) && (f3 & (TR3_REGEN))) list_ok = TRUE;
			if ((j == 4) && (f3 & (TR3_TELEPATHY))) list_ok = TRUE;
			if ((j == 5) && (f3 & (TR3_SEE_INVIS))) list_ok = TRUE;
			if ((j == 6) && (f3 & (TR3_FREE_ACT))) list_ok = TRUE;
			if ((j == 7) && (f3 & (TR3_HOLD_LIFE)))list_ok = TRUE;
			if ((j == 8) && (f3 & (TR3_IMPACT))) list_ok = TRUE;
			if ((j == 9) && (f3 & (TR3_BLESSED))) list_ok = TRUE;

			if (!list_ok) continue;

			/* Listing another attribute. */
			attr_listed++;

			/* Commas separate members of a list of more than two. */
			if ((attr_num > 2) && (attr_listed > 1)) roff(",", 3, 77);

			/* "and" before final member of a list of more than one. */
			if ((attr_num > 1) && (j != 0))
			{
				if (attr_num == attr_listed) roff(" and", 3, 77);
			}

			/* List the attribute description, in its proper place. */
			if (j == 0) roff(" slows your metabolism", 3, 77);
			if (j == 1) roff(" induces feather falling", 3, 77);
			if (j == 2) roff(" provides permanent light", 3, 77);
			if (j == 3) roff(" speeds your regenerative powers", 3, 77);
			if (j == 4) roff(" gives telepathic powers", 3, 77);
			if (j == 5) roff(" allows you to see invisible monsters", 3, 77);
			if (j == 6) roff(" provides immunity to paralysis", 3, 77);
			if (j == 7) roff(" provides resistance to life draining", 3, 77);
			if (j == 8) roff(" induces earthquakes", 3, 77);
			if (j == 9) roff(" has been blessed by the gods", 3, 77);
		}

		/* End sentence.  Go to next line. */
		roff(". \n", 3, 77);
	}


	/* Nastyness. */
	if ((f3 & (TR3_TELEPORT)) || (f3 & (TR3_AGGRAVATE)) ||
		(f3 & (TR3_DRAIN_EXP)) || (cursed_p(o_ptr)))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f3 & (TR3_TELEPORT)) attr_num++;
		if (f3 & (TR3_AGGRAVATE)) attr_num++;
		if (f3 & (TR3_DRAIN_EXP)) attr_num++;

		/* This one will display one of three possible descriptions. */
		if (cursed_p(o_ptr)) attr_num++;

		roff("It", 3, 77);

		/* Loop for number of attributes in this group. */
		for (j = 0; j < 6; j++)
		{
			bool list_ok = FALSE;

			if ((j == 0) && (f3 & (TR3_TELEPORT))) list_ok = TRUE;
			if ((j == 1) && (f3 & (TR3_AGGRAVATE))) list_ok = TRUE;
			if ((j == 2) && (f3 & (TR3_DRAIN_EXP))) list_ok = TRUE;
			if (cursed_p(o_ptr))
			{
				if ((j == 3) && (f3 & (TR3_PERMA_CURSE))) list_ok = TRUE;
				if ((j == 4) && (f3 & (TR3_HEAVY_CURSE))) list_ok = TRUE;
				/* Hack - some items (ammunition) can be
				 * 'cursed' but have no particular flags
				 */
				if ((j == 5) && ((f3 & (TR3_LIGHT_CURSE))
				       || (attr_listed == 0))) list_ok = TRUE;
			}

			if (!list_ok) continue;

			/* Listing another attribute. */
			attr_listed++;

			/* Commas separate members of a list of more than two. */
			if ((attr_num > 2) && (attr_listed > 1)) roff(",", 3, 77);

			/* "and" before final member of a list of more than one. */
			if ((attr_num > 1) && (j != 0))
			{
				if (attr_num == attr_listed) roff(" and", 3, 77);
			}

			/* List the attribute description, in its proper place. */
			if (j == 0) roff(" induces random teleportation", 3, 77);
			if (j == 1) roff(" aggravates nearby creatures", 3, 77);
			if (j == 2) roff(" drains experience", 3, 77);
			if (j == 3)
			{
				roff(" is permanently cursed", 3, 77);

				/* Hack -- no more cursed info wanted. */
				break;
			}
			if (j == 4)
			{
				roff(" is heavily cursed", 3, 77);

				/* Hack -- no more cursed info wanted. */
				break;
			}
			if (j == 5) roff(" is cursed", 3, 77);
		}

		/* End sentence.  Go to next line. */
		roff(". \n", 3, 77);
	}


	/* Ignore various elements. */
	if ((f3 & (TR3_IGNORE_ACID)) || (f3 & (TR3_IGNORE_ELEC)) ||
		(f3 & (TR3_IGNORE_FIRE)) || (f3 & (TR3_IGNORE_COLD)))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f3 & (TR3_IGNORE_ACID)) attr_num++;
		if (f3 & (TR3_IGNORE_ELEC)) attr_num++;
		if (f3 & (TR3_IGNORE_FIRE)) attr_num++;
		if (f3 & (TR3_IGNORE_COLD)) attr_num++;

		roff("It cannot be damaged by", 3, 77);

		/* Loop for number of attributes in this group. */
		for (j = 0; j < 4; j++)
		{
			bool list_ok = FALSE;

			if ((j == 0) && (f3 & (TR3_IGNORE_ACID))) list_ok = TRUE;
			if ((j == 1) && (f3 & (TR3_IGNORE_ELEC))) list_ok = TRUE;
			if ((j == 2) && (f3 & (TR3_IGNORE_FIRE))) list_ok = TRUE;
			if ((j == 3) && (f3 & (TR3_IGNORE_COLD))) list_ok = TRUE;

			if (!list_ok) continue;

			/* Listing another attribute. */
			attr_listed++;

			/* Commas separate members of a list of more than two. */
			if ((attr_num > 2) && (attr_listed > 1)) roff(",", 3, 77);

			/* "or" before final member of a list of more than one. */
			if ((attr_num > 1) && (j != 0))
			{
				if (attr_num == attr_listed) roff(" or", 3, 77);
			}

			/* List the attribute description, in its proper place. */
			if (j == 0) roff(" acid", 3, 77);
			if (j == 1) roff(" electricity", 3, 77);
			if (j == 2) roff(" fire", 3, 77);
			if (j == 3) roff(" frost", 3, 77);
		}

		/* End sentence.  Go to next line. */
		roff(". \n", 3, 77);
	}
}



/*
 * Hack -- acquire self knowledge.  Idea originally from Nethack.
 *
 * List various information about the player and/or his current equipment.
 *
 * See also "identify_fully()".
 *
 * Use the "roff()" routines, perhaps.  XXX XXX XXX
 *
 * Use the "show_file()" method, perhaps.  XXX XXX XXX
 */
void self_knowledge(void)
{
	int i = 0, j, k;

	u32b f1 = 0L, f2 = 0L, f3 = 0L;

	object_type *o_ptr;

	cptr info[128];


	/* Acquire item flags from equipment */
	for (k = INVEN_WIELD; k < INVEN_SUBTOTAL; k++)
	{
		u32b t1, t2, t3;

		o_ptr = &inventory[k];

		/* Skip non-objects */
		if (!o_ptr->k_idx) continue;

		/* Extract the flags */
		object_flags(o_ptr, &t1, &t2, &t3);

		/* Extract flags */
		f1 |= t1;
		f2 |= t2;
		f3 |= t3;
	}

	switch (p_ptr->schange)
	{
		case SHAPE_MOUSE:
			info[i++] = "You are wearing the body of a mouse.";
			break;
		case SHAPE_FERRET:
			info[i++] = "You are wearing the body of a ferret.";
			break;
		case SHAPE_HOUND:
			info[i++] = "You are wearing the body of a hound.";
			break;
		case SHAPE_GAZELLE:
			info[i++] = "You are wearing the body of a gazelle.";
			break;
		case SHAPE_LION:
			info[i++] = "You are wearing the body of a lion.";
			break;
		case SHAPE_ENT:
			info[i++] = "You are wearing the body of a ent.";
			break;
		case SHAPE_BAT:
			info[i++] = "You are wearing the body of a bat.";
			break;
		case SHAPE_WEREWOLF:
			info[i++] = "You are wearing the body of a werewolf.";
			break;
		case SHAPE_VAMPIRE:
			info[i++] = "You are wearing the body of a vampire.";
			break;
		case SHAPE_WYRM:
			info[i++] = "You are wearing the body of a dragon.";
			break;
		case SHAPE_BEAR:
			info[i++] = "You are wearing the body of a bear.";
			break;
	}

	if (p_ptr->blind)
	{
		info[i++] = "You cannot see.";
	}
	if (p_ptr->confused)
	{
		info[i++] = "You are confused.";
	}
	if (p_ptr->afraid)
	{
		info[i++] = "You are terrified.";
	}
	if (p_ptr->cut)
	{
		info[i++] = "You are bleeding.";
	}
	if (p_ptr->stun)
	{
		info[i++] = "You are stunned.";
	}
	if (p_ptr->poisoned)
	{
		info[i++] = "You are poisoned.";
	}
	if (p_ptr->image)
	{
		info[i++] = "You are hallucinating.";
	}

	if (p_ptr->aggravate)
	{
		info[i++] = "You aggravate monsters.";
	}
	if (p_ptr->teleport)
	{
		info[i++] = "Your position is very uncertain.";
	}

	if (p_ptr->blessed)
	{
		info[i++] = "You feel righteous.";
	}
	if (p_ptr->hero)
	{
		info[i++] = "You feel heroic.";
	}
	if (p_ptr->shero)
	{
		info[i++] = "You are in a battle rage.";
	}
	if (p_ptr->protevil)
	{
		info[i++] = "You are protected from evil.";
	}
	if (p_ptr->shield)
	{
		info[i++] = "You are protected by a mystic shield.";
	}
	if (p_ptr->magicdef)
	{
		info[i++] = "You have enhanced protection from the spells of others.";
	}
	if (p_ptr->searching)
	{
		info[i++] = "You are looking around very carefully.";
	}
	if (p_ptr->new_spells)
	{
		info[i++] = "You can learn some spells/prayers.";
	}
	if (p_ptr->new_specialties > 0)
	{
		info[i++] = "You can learn some specialty abilities.";
	}
	if (p_ptr->word_recall)
	{
		info[i++] = "You will soon be recalled.";
	}
	if (p_ptr->see_infra)
	{
		info[i++] = "Your eyes are sensitive to infrared light.";
	}

	if (p_ptr->slow_digest)
	{
		info[i++] = "Your appetite is small.";
	}
	if (p_ptr->ffall)
	{
		info[i++] = "You land gently.";
	}
	if (p_ptr->lite)
	{
		info[i++] = "You are glowing with light.";
	}
	if (p_ptr->regenerate)
	{
		info[i++] = "You regenerate quickly.";
	}
	if (p_ptr->telepathy)
	{
		info[i++] = "You have ESP.";
	}
	if (p_ptr->see_inv)
	{
		info[i++] = "You can see invisible creatures.";
	}
	if (p_ptr->free_act)
	{
		info[i++] = "You have free action.";
	}
	if (p_ptr->hold_life)
	{
		info[i++] = "You have a firm hold on your life force.";
	}

	if (p_immune(P_RES_ACID)) info[i++] = "You are immune to acid.";
	else if (p_resist_strong(P_RES_ACID)) info[i++] = "You resist acid exceptionally well.";
	else if (p_resist_pos(P_RES_ACID)) info[i++] = "You resist acid.";
	else if (p_vulnerable(P_RES_ACID)) info[i++] = "You are vulnerable to acid.";

	if (p_immune(P_RES_ELEC)) info[i++] = "You are immune to lightning.";
	else if (p_resist_strong(P_RES_ELEC)) info[i++] = "You resist lightning exceptionally well.";
	else if (p_resist_pos(P_RES_ELEC)) info[i++] = "You resist lightning.";
	else if (p_vulnerable(P_RES_ELEC)) info[i++] = "You are vulnerable to lightning.";

	if (p_immune(P_RES_FIRE)) info[i++] = "You are immune to fire.";
	else if (p_resist_strong(P_RES_FIRE)) info[i++] = "You resist fire exceptionally well.";
	else if (p_resist_pos(P_RES_FIRE)) info[i++] = "You resist fire.";
	else if (p_vulnerable(P_RES_FIRE)) info[i++] = "You are vulnerable to fire.";

	if (p_immune(P_RES_COLD)) info[i++] = "You are immune to cold.";
	else if (p_resist_strong(P_RES_COLD)) info[i++] = "You resist cold exceptionally well.";
	else if (p_resist_pos(P_RES_COLD)) info[i++] = "You resist cold.";
	else if (p_vulnerable(P_RES_COLD)) info[i++] = "You are vulnerable to cold.";

	if (p_immune(P_RES_POIS)) info[i++] = "You are immune to poison.";
	else if (p_resist_strong(P_RES_POIS)) info[i++] = "You resist poison exceptionally well.";
	else if (p_resist_pos(P_RES_POIS)) info[i++] = "You resist poison.";
	else if (p_vulnerable(P_RES_POIS)) info[i++] = "You are vulnerable to poison.";

	if (p_immune(P_RES_LITE)) info[i++] = "You are immune to light.";
	else if (p_resist_strong(P_RES_LITE)) info[i++] = "You resist light exceptionally well.";
	else if (p_resist_pos(P_RES_LITE)) info[i++] = "You resist light.";
	else if (p_vulnerable(P_RES_LITE)) info[i++] = "You are vulnerable to light.";

	if (p_immune(P_RES_DARK)) info[i++] = "You are immune to darkness.";
	else if (p_resist_strong(P_RES_DARK)) info[i++] = "You resist darkness exceptionally well.";
	else if (p_resist_pos(P_RES_DARK)) info[i++] = "You resist darkness.";
	else if (p_vulnerable(P_RES_DARK)) info[i++] = "You are vulnerable to darkness.";

	if (p_immune(P_RES_CONFU)) info[i++] = "You are immune to confusion.";
	else if (p_resist_strong(P_RES_CONFU)) info[i++] = "You resist confusion exceptionally well.";
	else if (p_resist_pos(P_RES_CONFU)) info[i++] = "You resist confusion.";
	else if (p_vulnerable(P_RES_CONFU)) info[i++] = "You are vulnerable to confusion.";

	if (p_immune(P_RES_SOUND)) info[i++] = "You are immune to sound.";
	else if (p_resist_strong(P_RES_SOUND)) info[i++] = "You resist sound exceptionally well.";
	else if (p_resist_pos(P_RES_SOUND)) info[i++] = "You resist sound.";
	else if (p_vulnerable(P_RES_SOUND)) info[i++] = "You are vulnerable to sound.";

	if (p_immune(P_RES_SHARD)) info[i++] = "You are immune to blasts of shards.";
	else if (p_resist_strong(P_RES_SHARD)) info[i++] = "You resist blasts of shards exceptionally well.";
	else if (p_resist_pos(P_RES_SHARD)) info[i++] = "You resist blasts of shards.";
	else if (p_vulnerable(P_RES_SHARD)) info[i++] = "You are vulnerable to blasts of shards.";

	if (p_immune(P_RES_NEXUS)) info[i++] = "You are immune to nexus attacks.";
	else if (p_resist_strong(P_RES_NEXUS)) info[i++] = "You resist nexus attacks exceptionally well.";
	else if (p_resist_pos(P_RES_NEXUS)) info[i++] = "You resist nexus attacks.";
	else if (p_vulnerable(P_RES_NEXUS)) info[i++] = "You are vulnerable to nexus attacks.";

	if (p_immune(P_RES_NETHR)) info[i++] = "You are immune to nether forces.";
	else if (p_resist_strong(P_RES_NETHR)) info[i++] = "You resist nether forces exceptionally well.";
	else if (p_resist_pos(P_RES_NETHR)) info[i++] = "You resist nether forces.";
	else if (p_vulnerable(P_RES_NETHR)) info[i++] = "You are vulnerable to nether forces.";

	if (p_immune(P_RES_CHAOS)) info[i++] = "You are immune to chaos.";
	else if (p_resist_strong(P_RES_CHAOS)) info[i++] = "You resist chaos exceptionally well.";
	else if (p_resist_pos(P_RES_CHAOS)) info[i++] = "You resist chaos.";
	else if (p_vulnerable(P_RES_CHAOS)) info[i++] = "You are vulnerable to chaos.";

	if (p_immune(P_RES_DISEN)) info[i++] = "You are immune to disenchantment.";
	else if (p_resist_strong(P_RES_DISEN)) info[i++] = "You resist disenchantment exceptionally well.";
	else if (p_resist_pos(P_RES_DISEN)) info[i++] = "You resist disenchantment.";
	else if (p_vulnerable(P_RES_DISEN)) info[i++] = "You are vulnerable to disenchantment.";

	if (p_ptr->no_fear)
	{
		info[i++] = "You are completely fearless.";
	}
	if (p_ptr->no_blind)
	{
		info[i++] = "Your eyes are resistant to blindness.";
	}

	if (p_ptr->sustain_str)
	{
		info[i++] = "Your strength is sustained.";
	}
	if (p_ptr->sustain_int)
	{
		info[i++] = "Your intelligence is sustained.";
	}
	if (p_ptr->sustain_wis)
	{
		info[i++] = "Your wisdom is sustained.";
	}
	if (p_ptr->sustain_con)
	{
		info[i++] = "Your constitution is sustained.";
	}
	if (p_ptr->sustain_dex)
	{
		info[i++] = "Your dexterity is sustained.";
	}
	if (p_ptr->sustain_chr)
	{
		info[i++] = "Your charisma is sustained.";
	}

	if (f1 & (TR1_STR))
	{
		info[i++] = "Your strength is affected by your equipment.";
	}
	if (f1 & (TR1_INT))
	{
		info[i++] = "Your intelligence is affected by your equipment.";
	}
	if (f1 & (TR1_WIS))
	{
		info[i++] = "Your wisdom is affected by your equipment.";
	}
	if (f1 & (TR1_DEX))
	{
		info[i++] = "Your dexterity is affected by your equipment.";
	}
	if (f1 & (TR1_CON))
	{
		info[i++] = "Your constitution is affected by your equipment.";
	}
	if (f1 & (TR1_CHR))
	{
		info[i++] = "Your charisma is affected by your equipment.";
	}

	if (f1 & (TR1_STEALTH))
	{
		info[i++] = "Your stealth is affected by your equipment.";
	}
	if (f1 & (TR1_SEARCH))
	{
		info[i++] = "Your searching ability is affected by your equipment.";
	}
	if (f1 & (TR1_INFRA))
	{
		info[i++] = "Your infravision is affected by your equipment.";
	}
	if (f1 & (TR1_TUNNEL))
	{
		info[i++] = "Your digging ability is affected by your equipment.";
	}
	if (f1 & (TR1_SPEED))
	{
		info[i++] = "Your speed is affected by your equipment.";
	}

	if (f1 & (TR1_SHOTS))
	{
		info[i++] = "Your shooting speed is affected by your equipment.";
	}
	if (f1 & (TR1_MIGHT1))
	{
		info[i++] = "Your shooting might is affected by your equipment.";
	}
	if (f1 & (TR1_MIGHT2))
	{
		info[i++] = "Your shooting might is affected by your equipment.";
	}


	/* Access the current weapon */
	o_ptr = &inventory[INVEN_WIELD];

	/* Analyze the weapon */
	if (o_ptr->k_idx)
	{
		/* Special "Attack Bonuses" */
		if (f1 & (TR1_BRAND_ACID))
		{
			info[i++] = "Your weapon melts your foes.";
		}
		if (f1 & (TR1_BRAND_ELEC))
		{
			info[i++] = "Your weapon shocks your foes.";
		}
		if (f1 & (TR1_BRAND_FIRE))
		{
			info[i++] = "Your weapon burns your foes.";
		}
		if (f1 & (TR1_BRAND_COLD))
		{
			info[i++] = "Your weapon freezes your foes.";
		}
		if (f1 & (TR1_BRAND_POIS))
		{
			info[i++] = "Your weapon poisons your foes.";
		}

		/* Special "slay" flags */
		if (f1 & (TR1_SLAY_ANIMAL))
		{
			info[i++] = "Your weapon strikes at animals with extra force.";
		}
		if (f1 & (TR1_SLAY_EVIL))
		{
			info[i++] = "Your weapon strikes at evil with extra force.";
		}
		if (f1 & (TR1_SLAY_UNDEAD))
		{
			info[i++] = "Your weapon strikes at undead with holy wrath.";
		}
		if (f1 & (TR1_SLAY_DEMON))
		{
			info[i++] = "Your weapon strikes at demons with holy wrath.";
		}
		if (f1 & (TR1_SLAY_ORC))
		{
			info[i++] = "Your weapon is especially deadly against orcs.";
		}
		if (f1 & (TR1_SLAY_TROLL))
		{
			info[i++] = "Your weapon is especially deadly against trolls.";
		}
		if (f1 & (TR1_SLAY_GIANT))
		{
			info[i++] = "Your weapon is especially deadly against giants.";
		}
		if (f1 & (TR1_SLAY_DRAGON))
		{
			info[i++] = "Your weapon is especially deadly against dragons.";
		}

		/* Indicate Blessing */
		if (f3 & (TR3_BLESSED))
		{
			info[i++] = "Your weapon has been blessed by the gods.";
		}

		/* Hack */
		if (f3 & (TR3_IMPACT))
		{
			info[i++] = "Your weapon can induce earthquakes.";
		}
	}


	/* Save screen */
	screen_save();


	/* Clear the screen */
	Term_clear();

	/* Label the information */
	prt("     Your Attributes:", 1, 0);

	/* Dump the info */
	for (k = 2, j = 0; j < i; j++)
	{
		/* Show the info */
		prt(info[j], k++, 0);

		/* Page wrap */
		if ((k == Term->hgt - 2) && (j+1 < i))
		{
			prt("-- more --", k, 0);
			inkey();

			/* Clear the screen */
			Term_clear();

			/* Label the information */
			prt("     Your Attributes:", 1, 0);

			/* Reset */
			k = 2;
		}
	}

	/* Pause */
	prt("[Press any key to continue]", k, 0);
	(void)inkey();


	/* Load screen */
	screen_load();
}




/*
 * Returns chance of failure for a spell
 */
s16b spell_chance(int spell)
{
	int chance, minfail;

	magic_type *s_ptr;


	/* Paranoia -- must be literate */
	if (!mp_ptr->spell_book) return (100);

	/* Access the spell */
	s_ptr = &mp_ptr->info[spell];

	/* Extract the base spell failure rate */
	chance = s_ptr->sfail;

	/* Reduce failure rate by "effective" level adjustment */
	chance -= 4 * (p_ptr->lev - s_ptr->slevel);

	/* Reduce failure rate by INT/WIS adjustment */
	chance -= 3 * (adj_mag_stat[p_ptr->stat_ind[mp_ptr->spell_stat]] - 1);

	/* Not enough mana to cast */
	if (s_ptr->smana > p_ptr->csp)
	{
		chance += 5 * (s_ptr->smana - p_ptr->csp);
	}

	/* Extract the minimum failure rate */
	minfail = adj_mag_fail[p_ptr->stat_ind[mp_ptr->spell_stat]];

	/* Minimum failure rate */
	if (chance < minfail) chance = minfail;

	/* Stunning makes spells harder (after minfail) */
	if (p_ptr->stun > 50) chance += 20;
	else if (p_ptr->stun) chance += 10;

	/* Always a 5 percent chance of working */
	if (chance > 95) chance = 95;

	/* Return the chance */
	return (chance);
}



/*
 * Determine if a spell is "okay" for the player to cast or study
 * The spell must be legible, not forgotten, and also, to cast,
 * it must be known, and to study, it must not be known.
 */
bool spell_okay(int spell)
{
	magic_type *s_ptr;

	/* Access the spell */
	s_ptr = &mp_ptr->info[spell];

	/* Spell is illegal */
	if (s_ptr->slevel > p_ptr->lev) return (FALSE);

	/* Okay to cast */
	return (TRUE);
}



/*
 * Extra information on a spell		-DRS-
 *
 * We can use up to 20 characters of the buffer 'p'
 *
 * The strings in this function were extracted from the code in the
 * functions "do_cmd_cast()" and "do_cmd_pray()" and are up to date
 * (as of 0.4.0). -LM-
 */
void spell_info(char *p, int spell_index)
{
	int plev = p_ptr->lev;

	int beam, beam_low;

	bool beguile;

        /* Specialty Ability */
	plev += get_spell_level_boost();

	beguile = check_ability(SP_BEGUILE);

	/* Beaming chance */
	beam = (((check_ability(SP_BEAM)))
		? plev : (plev / 2));
	beam_low = (beam - 10 > 0 ? beam - 10 : 0);

	/* Default */
	strcpy(p, "");

	/* Analyze the spell */
	switch (spell_index)
	{
		/* Sorcery */

		case 0: sprintf(p, " dam 2d%d", 4 + plev / 10); break;
		case 2: strcpy(p, " range 10"); break;
		case 3: sprintf(p, " dam 2d%d, rad %d",
			1 + (plev / 5), ( plev / 10) + 1); break;
		case 5: sprintf(p, " heal 2d%d", plev / 4 + 5); break;
		case 8: sprintf(p, " dam %d, rad 2", 5 + (plev / 3)); break;
		case 9: sprintf(p, " pow %d", (beguile ? (int)((plev + 10) * 3 / 2) : plev + 10)); break;
		case 10: sprintf(p, " dam %dd8, beam %d%%", (2+((plev-5)/5)), beam);
			break;
		case 12: sprintf(p, " pow %d", (beguile ? (int)((plev + 10) * 3 / 2) : plev + 10)); break;
		case 14: sprintf(p, " range %d", 50 + plev * 2); break;
		case 15: strcpy(p, " dam 4d5"); break;
		case 17: sprintf(p, " dam %d, range %d", 20+plev, 3+plev/10); break;
		case 22: sprintf(p, " pow %d", (beguile ? (int)((plev + 10) * 3 / 2) : plev + 10)); break;
		case 23: sprintf(p, " dam %dd8, beam %d%%", (7+((plev-5)/5)), beam);
			break;
		case 24: sprintf(p, " pow %d", (beguile ? (int)((plev + 10) * 3 / 2) : plev + 10)); break;
		case 26: sprintf(p, " dam %d, rad 2", 30 + plev); break;
		case 28: sprintf(p, " dist %d", 45 + (plev/2)); break;
		case 29: sprintf(p, " dur %d+d20", plev); break;
		case 30: sprintf(p, " dam %d, rad 2", 55 + plev); break;
		case 31: sprintf(p, " radius %d", 2); break;
		case 32: strcpy(p, " rad 15"); break;
		case 33: sprintf(p, " dur %d+d%d", plev, plev); break;
		case 34: sprintf(p, " dur %d+d%d", plev, plev); break;
		case 35: sprintf(p, " dur %d+d%d", plev, plev); break;
		case 36: sprintf(p, " dur %d+d%d", plev, plev); break;
		case 37: strcpy(p, " dur 20+d20"); break;
		case 42: strcpy(p, " range 25"); break;
		case 45: strcpy(p, " radius 10"); break;
		case 46: sprintf(p, " pow %d", (beguile ? (int)((5 * plev / 3) * 3 / 2) : (5 *  plev / 3))); break;
		case 47: sprintf(p, " dam %d, rad %d", 5 * plev / 2, plev / 12); break;
		case 48: sprintf(p, " recover %d", 1 + plev / 12); break;
		case 49: strcpy(p, " dur 30+d20"); break;
		case 51: sprintf(p, " dur %d+d30", 10+plev); break;
		case 52: strcpy(p, " dur 30"); break;
		case 53: sprintf(p, " dam %dd8, beam %d%%", (5+((plev-5)/5)), beam);
			break;
		case 54: sprintf(p, " dam %d, rad 3", 10 + plev); break;
		case 55: sprintf(p, " dam %d, rad 2", 2 * plev); break;
		case 56: sprintf(p, " dam %d, rad 3", 3 * plev); break;
		case 57: sprintf(p, " dam %d, rad 1", 80 + plev * 2); break;
		case 58: sprintf(p, " dam %d, rad 4", 120 + plev * 2); break;


		/* Piety */
		case 65: sprintf(p, " heal 2d%d", plev / 4 + 5); break;
		case 66: strcpy(p, " dur 12+d12"); break;
		case 68: sprintf(p, " dam 2d%d, rad %d", 1 + plev/3, plev/10+1); break;
		case 71: strcpy(p, " halve poison"); break;
		case 72: sprintf(p, " heal 4d%d", plev / 4 + 6); break;
		case 73: sprintf(p, " pow %d", (beguile ? (int)(((3 * plev / 2) + 10) * 3 / 2) : (int)(3 * plev / 2) + 10)); break;
		case 74: sprintf(p, " range %d", 2 * plev); break;
		case 75: strcpy(p, " dur 24+d24"); break;
		case 76: sprintf(p, " pow %d", (beguile ? (int)((plev + 25) * 3 / 2) : plev + 25)); break;
		case 79: sprintf(p, " dur %d+d10", plev / 2); break;
		case 81: sprintf(p, " dam %d+3d6, rad %d", plev / 4 +
			(plev / ((check_ability(SP_STRONG_MAGIC)) ? 2 : 4)),
			(plev < 30) ? 1 : 2); break;
		case 82: sprintf(p, " dur %d+d24", plev); break;
		case 83: sprintf(p, " dur %d+d24", 3 * plev / 2); break;
		case 84: sprintf(p, " heal 9d%d, any cut", plev / 3 + 12); break;
		case 85: strcpy(p, " radius 10"); break;
		case 87: sprintf(p, " pow %d", (beguile ? (int)(((3 * plev / 2) + 10) * 3 / 2) : (3 * plev / 2) + 10)); break;
		case 88: strcpy(p, " dur 48+d48"); break;
		case 89: sprintf(p, " dam d%d", 3 * plev); break;
		case 90: strcpy(p, " heal 300, any cut"); break;
		case 91: sprintf(p, " dam d%d", 3 * plev); break;
		case 92: sprintf(p, " dur %d+d20", plev / 2); break;
		case 94: sprintf(p, " dam d%d, heal 300", plev * 4); break;
		case 95: strcpy(p, " range 10"); break;
		case 96: sprintf(p, " range %d", 4 * plev); break;
		case 97: sprintf(p, " dist %d", 45 + (plev/3)); break;
		case 107: strcpy(p, " heal 700, any cut"); break;
		case 117: sprintf(p, " dam %d, rad 3", 2 * plev); break;
		case 118: sprintf(p, " dam %d", 3 * plev / 2); break;
		case 120: sprintf(p, " dam %d+d100", plev * 3); break;
		case 121: sprintf(p, " dam %d, heal 500", plev * 5); break;
		case 124: sprintf(p, " pow %d", (beguile ? (int)((plev) * 3 / 2) : plev)); break;
		case 125: sprintf(p, " dam %d+d%d", 25 + plev, plev); break;


		/* Nature Magics */

		case 129: sprintf(p, " dam 2d%d, rad %d", 1 + plev/4, plev/10+1); break;
		case 131: strcpy(p, " range 10"); break;
		case 132: strcpy(p, " halve poison"); break;
		case 133: sprintf(p, " dam %dd6, length %d", 2+plev/8, 1+plev/5); break;
		case 135: strcpy(p, " dam 20+d30"); break;
		case 136: strcpy(p, " dam 4d5"); break;
		case 138: sprintf(p, " dam %dd8, beam %d%%", 2+plev/5, beam_low); break;
		case 139: sprintf(p, " pow %d", (beguile ? (int)((plev + 10) * 3 / 2) : plev + 10)); break;
		case 140: sprintf(p, " pow %d", (beguile ? (int)((plev + 10) * 3 / 2) : plev + 10)); break;
		case 142: sprintf(p, " dam %d", 2 + plev / 5); break;
		case 143: sprintf(p, " dam %dd8, beam %d%%", 3 + plev / 5, beam_low);
			break;
		case 144: strcpy(p, " dur 20+d20"); break;
		case 146: sprintf(p, " dam %dd8, beam %d%%", 5+plev/5, beam_low); break;
		case 147: sprintf(p, " dist %d", 45 + (plev/3)); break;
		case 148: sprintf(p, " dam %dd8, beam %d%%", 7+plev/4, beam_low); break;
		case 149: strcpy(p, " dur 20+d20"); break;
		case 150: strcpy(p, " radius 10"); break;
		case 151: strcpy(p, " dur 20+d20"); break;
		case 153: sprintf(p, " heal 2d%d, pois/cut", plev / 5); break;
		case 154: strcpy(p, " dur 20+d20"); break;
		case 155: sprintf(p, " dam %dd8, conf/slow", plev / 7); break;
		case 159: sprintf(p, " dam %d+d%d, rad %d", plev, 60 + plev * 2,
			1 + plev / 15); break;
		case 160: sprintf(p, " dam %d+d%d, rad %d", plev, 40 + plev * 2,
			plev / 8); break;
		case 167: sprintf(p, " pow %d", (beguile ? (int)((3 * plev / 2 + 10) * 3 / 2) : 3 * plev / 2 + 10)); break;
		case 169: strcpy(p, " dur 24+d24"); break;
		case 170: sprintf(p, " heal %dd12, any cut", 25 + plev / 2); break;
		case 171: sprintf(p, " dam %d+d%d, rad %d", plev, 50 + plev * 2,
			1 + plev / 12); break;
		case 172: sprintf(p, " dam %d+d%d, rad %d", 30 + ((4 * plev) / 5),
			30 + plev * 2, plev / 7); break;
		case 173: sprintf(p, " dam %d+d%d, rad %d", 3 * plev / 2, 50 + plev * 3,
			1 + plev / 15); break;
		case 174: sprintf(p, " dam %d+d%d, rad 1", 35+(2*plev), 90+plev*4); break;
		case 175: sprintf(p, " dam %d+d%d, rad %d", 40 + (3 * plev / 2), plev * 3,
			plev / 10); break;
		case 176: sprintf(p, " pow %d", (beguile ? (int)((5 * plev / 3) * 3 / 2) : 5 * plev / 3)); break;
		case 177: sprintf(p, " dur %d+d30", plev / 2); break;
		case 178: sprintf(p, " dam d%d", plev * 2); break;
		case 181: sprintf(p, " dam %dd8, beam %d%%", plev / 6, plev * 2); break;
		case 182: sprintf(p, " dur %d+d10", plev / 2); break;
		case 186: strcpy(p, " heal 500, dam 100"); break;


		/* Necromantic Spells */

		case 192: sprintf(p, " dam 2d%d", 5 + plev / 7); break;
		case 194: strcpy(p, " dur 70+d70"); break;
		case 196: sprintf(p, " pow %d", (beguile ? (int)((plev + 5) * 3 / 2) : plev + 5)); break;
		case 197: sprintf(p, " pow %d", (beguile ? (int)((plev + 5) * 3 / 2) : plev + 5)); break;
		case 198: sprintf(p, " pow %d", (beguile ? (int)((plev + 15) * 3 / 2) : plev + 15)); break;
		case 199: strcpy(p, " hurt 2d4"); break;
		case 201: sprintf(p, " dam %dd8, beam %d%%", 3+plev/7, beam_low); break;
		case 202: sprintf(p, " dam %d, poison", 10 + plev); break;
		case 203: sprintf(p, " pow %d", (beguile ? (int)((3 * plev / 2) * 3 / 2) : (3 * plev / 2))); break;
		case 204: sprintf(p, " pow %d", (beguile ? (int)((5 * plev / 4) * 3 / 2) : (5 * plev / 4))); break;
		case 206: sprintf(p, " dam %d+d%d", plev + 15, 3 * plev / 2); break;
		case 207: sprintf(p, " dam %d+d%d", plev, plev); break;
		case 208: sprintf(p, " dur 20+d%d", plev / 2); break;
		case 209: strcpy(p, " range 16, hurt 1d4"); break;
		case 212: sprintf(p, " pow %d", (beguile ? (int)((plev + 5) * 3 / 2) : plev + 5)); break;
		case 213: sprintf(p, " pow %d", (beguile ? (int)((plev + 5) * 3 / 2) : plev + 5)); break;
		case 215: sprintf(p, " dam %dd8, hurt 1d6", 2 + plev / 3); break;
		case 216: sprintf(p, " dur %d+d20", plev / 2); break;
		case 217: sprintf(p, " dam %d+d%d", 2 * plev, 2 * plev); break;
		case 218: sprintf(p, " dam %d", 12 + plev); break;
		case 219: sprintf(p, " dam %dd8, beam %d%%", 1 + plev / 2, beam); break;
		case 221: sprintf(p, " dam %d, rad 2", 50 + plev * 2); break;
		case 222: sprintf(p, " dam %d+d%d, hit ~9", 50 + plev * 2, plev); break;
		case 226: sprintf(p, " range %d, hurt 2d6", plev * 3); break;
		case 228: strcpy(p, " dur 20+d20"); break;
		case 230: sprintf(p, " %d+d%d", plev / 2, plev); break;
		case 231: strcpy(p, " dur d66"); break;
		case 233: strcpy(p, " dur 10+d20"); break;
		case 235: sprintf(p, " dam %dd13", 3 * plev / 5); break;
		case 236: sprintf(p, " dam %d, hurt 2d8", 20 + (4 * plev)); break;
		case 237: sprintf(p, " dam %d+d%d", 60, plev * 2); break;
		case 238: sprintf(p, " dam %dd11, heal %d", plev / 3, 3 * plev); break;
		case 240: strcpy(p, " hurt 2d7"); break;
		case 242: strcpy(p, " hurt 3d6"); break;
		case 243: strcpy(p, " dur 10+d20"); break;
		case 245: strcpy(p, " radius 15"); break;
		case 246: sprintf(p, " dist %d", 45 + (plev/3)); break;
		case 247: sprintf(p, " dam %d+d50", plev * 3); break;
		case 249: sprintf(p, " dam %d, rad %d", 11 * plev / 2, plev/7); break;
		case 250: sprintf(p, " dur 30+d40"); break;
		case 251: sprintf(p, " dur 40"); break;
		case 252: sprintf(p, " dur 40"); break;


		/* Archery Spells */

		case 255: strcpy(p, " 3-5 @ 50% dam"); break;
		case 263: strcpy(p, " +15 skill"); break;
		case 264: strcpy(p, " 3-5 @ 50% dam"); break;
		case 265: sprintf(p, " rad 1, %d dam", p_ptr->lev); break;
	}
}


/*
 * Print out a list of available spells for any spellbook given.
 * Revised by -LM-
 *
 * Input y controls lines from top for list, and input x controls columns
 * from left.
 */
void print_spells(int tval, int sval, int y, int x)
{
	int i, left_justi;
	int j = 0;
	int first_spell, after_last_spell;

	magic_type *s_ptr;

	byte attr_book, attr_name, attr_extra;

	cptr comment;
	char info[80];
	char out_val[160];

	object_kind *k_ptr = &k_info[lookup_kind(tval, sval)];
	cptr basenm = (k_name + k_ptr->name);


	/* Currently must be a legal spellbook of the correct realm. */
	if ((tval != mp_ptr->spell_book) || (sval > SV_BOOK_MAX)) return;


	/* Choose appropriate spellbook color. */
	if (tval == TV_MAGIC_BOOK)
	{
		if (sval < SV_BOOK_MIN_GOOD) attr_book = TERM_L_RED;
		else attr_book = TERM_RED;
	}
	else if (tval == TV_PRAYER_BOOK)
	{
		if (sval < SV_BOOK_MIN_GOOD) attr_book = TERM_L_BLUE;
		else attr_book = TERM_BLUE;
	}
	else if (tval == TV_DRUID_BOOK)
	{
		if (sval < SV_BOOK_MIN_GOOD) attr_book = TERM_L_GREEN;
		else attr_book = TERM_GREEN;
	}
	else if (tval == TV_NECRO_BOOK)
	{
		if (sval < SV_BOOK_MIN_GOOD) attr_book = TERM_L_DARK;
		else attr_book = TERM_VIOLET;
	}
	else attr_book = TERM_WHITE;


	/* Find the array index of the spellbook's first spell. */
	first_spell = mp_ptr->book_start_index[sval];

	/* Find the first spell in the next book. */
	after_last_spell = mp_ptr->book_start_index[sval+1];

	/* Choose a left margin for the spellbook name. */
	left_justi = ((80 - x) - strlen(basenm)) / 2;

	/* Center the spellbook name */
	prt("", y, x);
	c_put_str(attr_book, format("%s", basenm), y, x + left_justi);


	/* Title the list */
	prt("", y + 1, x);
	put_str("Name", y + 1, x + 5);
	put_str("Lv Mana Fail Info", y + 1, x + 35);

	/* Dump the spells in the book. */
	for (i = first_spell; i < after_last_spell; i++)
	{
		/* Access the spell */
		s_ptr = &mp_ptr->info[i];

		/* Increment the current line */
		j++;

		/* Skip illegible spells.  This should actually never appear. */
		if (s_ptr->slevel >= 99)
		{
			sprintf(out_val, "  %c) %-30s", I2A(i - first_spell),
				"(illegible)");
			c_prt(TERM_SLATE, out_val, y + j + 1, x);
			continue;
		}

		/* Get extra info */
		spell_info(info, s_ptr->index);

		/* Use that info */
		comment = info;

		/* Analyze the spell */
		if (!spell_okay(i))
		{
			comment = " too difficult";

			/* Spells above the player's level are colored light gray. */
			attr_name = TERM_L_WHITE;
			attr_extra = TERM_L_WHITE;
		}
		else if (!((i < 32) ?
		           (p_ptr->spell_worked1 & (1L << i)) :
		           (p_ptr->spell_worked2 & (1L << (i - 32)))))
		{
			comment = " untried";
			attr_name = TERM_WHITE;
			attr_extra = TERM_WHITE;
		}
		else
		{
			/* Vivid color for known, cast spells */
			attr_name = attr_book;
			attr_extra = TERM_L_BLUE;
		}

		/* Clear line */
		prt("", y + j + 1, x);

		/* Print out (colored) information about a single spell. */
		put_str(format("  %c) ", I2A(i - first_spell)), y + j + 1, x);
		c_put_str(attr_name, format("%-30s", spell_names[s_ptr->index]),
			y + j + 1, x + 5);
		put_str(format("%2d %4d %3d%%", s_ptr->slevel,
			s_ptr->smana, spell_chance(i)), y + j + 1, x + 35);
		c_put_str(attr_extra, format("%s", comment), y + j + 1, x + 47);
	}

	/* Clear the bottom line */
	prt("", y + j + 2, x);
}


/*
 * For a string describing the player's intrinsic racial flags.
 */
static cptr view_abilities_aux(char *desc)
{
  //	u32b f1 = rp_ptr->flags1;
	u32b f2 = rp_ptr->flags2;
	u32b f3 = rp_ptr->flags3;

	int attr_num, attr_listed, j;

	/* Sustain stats. */
	if ((f2 & (TR2_SUST_STR)) || (f2 & (TR2_SUST_INT)) || (f2 & (TR2_SUST_WIS))
		|| (f2 & (TR2_SUST_DEX)) || (f2 & (TR2_SUST_CON)) ||
		(f2 & (TR2_SUST_CHR)))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f2 & (TR2_SUST_STR)) attr_num++;
		if (f2 & (TR2_SUST_INT)) attr_num++;
		if (f2 & (TR2_SUST_WIS)) attr_num++;
		if (f2 & (TR2_SUST_DEX)) attr_num++;
		if (f2 & (TR2_SUST_CON)) attr_num++;
		if (f2 & (TR2_SUST_CHR)) attr_num++;

		/* Special case:  sustain all stats */
		if (attr_num == 6)
		{
			strcat(desc, "Your stats are all sustained.  ");
		}
		else
		{
			strcat(desc, "Your");

			/* Loop for number of attributes in this group. */
			for (j = 0; j < 6; j++)
			{
				bool list_ok = FALSE;

				if ((j == 0) && (f2 & (TR2_SUST_STR))) list_ok = TRUE;
				if ((j == 1) && (f2 & (TR2_SUST_INT))) list_ok = TRUE;
				if ((j == 2) && (f2 & (TR2_SUST_WIS))) list_ok = TRUE;
				if ((j == 3) && (f2 & (TR2_SUST_DEX))) list_ok = TRUE;
				if ((j == 4) && (f2 & (TR2_SUST_CON))) list_ok = TRUE;
				if ((j == 5) && (f2 & (TR2_SUST_CHR))) list_ok = TRUE;

				if (!list_ok) continue;

				/* Listing another attribute. */
				attr_listed++;

				/* Commas separate members of a list of more than two. */
				if ((attr_num > 2) && (attr_listed > 1)) strcat(desc, ",");

				/* "and" before final member of a list of more than one. */
				if ((attr_num > 1) && (j != 0))
				{
					if (attr_num == attr_listed) strcat(desc, " and");
				}

				/* List the attribute description, in its proper place. */
				if (j == 0) strcat(desc, " strength");
				if (j == 1) strcat(desc, " intelligence");
				if (j == 2) strcat(desc, " wisdom");
				if (j == 3) strcat(desc, " dexterity");
				if (j == 4) strcat(desc, " constitution");
				if (j == 5) strcat(desc, " charisma");
			}
		}

		/* Pluralize the verb. */
		if (attr_num > 1) strcat(desc, " are");
		else strcat(desc, " is");

		/* End sentence.  Go to next line. */
		strcat(desc, " sustained.  ");
	}

	/* Elemental immunities. */
	if ((f2 & (TR2_IM_ACID)) || (f2 & (TR2_IM_ELEC)) ||
		(f2 & (TR2_IM_FIRE)) || (f2 & (TR2_IM_COLD)))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f2 & (TR2_IM_ACID)) attr_num++;
		if (f2 & (TR2_IM_ELEC)) attr_num++;
		if (f2 & (TR2_IM_FIRE)) attr_num++;
		if (f2 & (TR2_IM_COLD)) attr_num++;

		strcat(desc, "You are immune to");

		/* Loop for number of attributes in this group. */
		for (j = 0; j < 4; j++)
		{
			bool list_ok = FALSE;

			if ((j == 0) && (f2 & (TR2_IM_ACID))) list_ok = TRUE;
			if ((j == 1) && (f2 & (TR2_IM_ELEC))) list_ok = TRUE;
			if ((j == 2) && (f2 & (TR2_IM_FIRE))) list_ok = TRUE;
			if ((j == 3) && (f2 & (TR2_IM_COLD))) list_ok = TRUE;

			if (!list_ok) continue;

			/* Listing another attribute. */
			attr_listed++;

			/* Commas separate members of a list of more than two. */
			if ((attr_num > 2) && (attr_listed > 1)) strcat(desc, ",");

			/* "and" before final member of a list of more than one. */
			if ((attr_num > 1) && (j != 0))
			{
				if (attr_num == attr_listed) strcat(desc, " and");
			}

			/* List the attribute description, in its proper place. */
			if (j == 0) strcat(desc, " acid");
			if (j == 1) strcat(desc, " electricity");
			if (j == 2) strcat(desc, " fire");
			if (j == 3) strcat(desc, " frost");
		}

		/* End sentence.  Go to next line. */
		strcat(desc, ".  ");
	}


	/* Resistances. */
	if ((f2 & (TR2_RES_ACID)) || (f2 & (TR2_RES_ELEC)) ||
		(f2 & (TR2_RES_FIRE)) || (f2 & (TR2_RES_COLD)) ||
		(f2 & (TR2_RES_POIS)) || (f2 & (TR2_RES_LITE)) ||
		(f2 & (TR2_RES_DARK)) || (f2 & (TR2_RES_SOUND)) ||
		(f2 & (TR2_RES_SHARD)) || (f2 & (TR2_RES_NEXUS)) ||
		(f2 & (TR2_RES_NETHR)) || (f2 & (TR2_RES_CHAOS)) ||
		(f2 & (TR2_RES_DISEN)) || (f2 & (TR2_RES_CONFU)))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f2 & (TR2_RES_ACID)) attr_num++;
		if (f2 & (TR2_RES_ELEC)) attr_num++;
		if (f2 & (TR2_RES_FIRE)) attr_num++;
		if (f2 & (TR2_RES_COLD)) attr_num++;
		if (f2 & (TR2_RES_POIS)) attr_num++;
		if (f2 & (TR2_RES_LITE)) attr_num++;
		if (f2 & (TR2_RES_DARK)) attr_num++;
		if (f2 & (TR2_RES_SOUND)) attr_num++;
		if (f2 & (TR2_RES_SHARD)) attr_num++;
		if (f2 & (TR2_RES_NEXUS)) attr_num++;
		if (f2 & (TR2_RES_NETHR)) attr_num++;
		if (f2 & (TR2_RES_CHAOS)) attr_num++;
		if (f2 & (TR2_RES_DISEN)) attr_num++;
		if (f2 & (TR2_RES_CONFU)) attr_num++;

		strcat(desc, "You are resistant to");

		/* Loop for number of attributes in this group. */
		for (j = 0; j < 14; j++)
		{
			bool list_ok = FALSE;

			if ((j ==  0) && (f2 & (TR2_RES_ACID)))  list_ok = TRUE;
			if ((j ==  1) && (f2 & (TR2_RES_ELEC)))  list_ok = TRUE;
			if ((j ==  2) && (f2 & (TR2_RES_FIRE)))  list_ok = TRUE;
			if ((j ==  3) && (f2 & (TR2_RES_COLD)))  list_ok = TRUE;
			if ((j ==  4) && (f2 & (TR2_RES_POIS)))  list_ok = TRUE;
			if ((j ==  5) && (f2 & (TR2_RES_LITE)))  list_ok = TRUE;
			if ((j ==  6) && (f2 & (TR2_RES_DARK)))  list_ok = TRUE;
			if ((j ==  7) && (f2 & (TR2_RES_SOUND))) list_ok = TRUE;
			if ((j ==  8) && (f2 & (TR2_RES_SHARD))) list_ok = TRUE;
			if ((j ==  9) && (f2 & (TR2_RES_NEXUS))) list_ok = TRUE;
			if ((j == 10) && (f2 & (TR2_RES_NETHR))) list_ok = TRUE;
			if ((j == 11) && (f2 & (TR2_RES_CHAOS))) list_ok = TRUE;
			if ((j == 12) && (f2 & (TR2_RES_DISEN))) list_ok = TRUE;
			if ((j == 12) && (f2 & (TR2_RES_CONFU))) list_ok = TRUE;

			if (!list_ok) continue;

			/* Listing another attribute. */
			attr_listed++;

			/* Commas separate members of a list of more than two. */
			if ((attr_num > 2) && (attr_listed > 1)) strcat(desc, ",");

			/* "and" before final member of a list of more than one. */
			if ((attr_num > 1) && (j != 0))
			{
				if (attr_num == attr_listed) strcat(desc, " and");
			}

			/* List the attribute description, in its proper place. */
			if (j ==  0) strcat(desc, " acid");
			if (j ==  1) strcat(desc, " electricity");
			if (j ==  2) strcat(desc, " fire");
			if (j ==  3) strcat(desc, " frost");
			if (j ==  4) strcat(desc, " poison");
			if (j ==  5) strcat(desc, " light");
			if (j ==  6) strcat(desc, " darkness");
			if (j ==  7) strcat(desc, " sound");
			if (j ==  8) strcat(desc, " shards");
			if (j ==  9) strcat(desc, " nexus");
			if (j == 10) strcat(desc, " nether");
			if (j == 11) strcat(desc, " chaos");
			if (j == 12) strcat(desc, " disenchantment");
			if (j == 13) strcat(desc, " confusion");
		}

		/* End sentence.  Go to next line. */
		strcat(desc, ".  ");
	}


	/* Clear a listing variable. */
	attr_num = 0;

	/* Special processing for the three "survival resists" */
	if (f2 & (TR2_RES_FEAR)) attr_num++;
	if (f2 & (TR2_RES_BLIND)) attr_num++;

	if (f2 & (TR2_RES_FEAR))
	{
		strcat(desc, "You are fearless");
		if (attr_num == 1) strcat(desc, ".  ");
		else strcat(desc, ", and");
	}

	if (f2 & (TR2_RES_BLIND))
	{
		if ((attr_num > 1) && (f2 & (TR2_RES_FEAR)))
			strcat(desc, " can not be blinded.  ");
		else strcat(desc, "You can not be blinded.  ");
	}

	/* Miscellanious abilities. */
	if ((f3 & (TR3_SLOW_DIGEST)) || (f3 & (TR3_FEATHER)) ||
		(f3 & (TR3_LITE)) || (f3 & (TR3_REGEN)) ||
		(f3 & (TR3_TELEPATHY)) || (f3 & (TR3_SEE_INVIS)) ||
		(f3 & (TR3_FREE_ACT)) || (f3 & (TR3_HOLD_LIFE)))
	{
		/* Clear number of items to list, and items listed. */
		attr_num = 0;
		attr_listed = 0;

		/* How many attributes need to be listed? */
		if (f3 & (TR3_SLOW_DIGEST)) attr_num++;
		if (f3 & (TR3_FEATHER)) attr_num++;
		if (f3 & (TR3_LITE)) attr_num++;
		if (f3 & (TR3_REGEN)) attr_num++;
		if (f3 & (TR3_TELEPATHY)) attr_num++;
		if (f3 & (TR3_SEE_INVIS)) attr_num++;
		if (f3 & (TR3_FREE_ACT)) attr_num++;
		if (f3 & (TR3_HOLD_LIFE)) attr_num++;

		strcat(desc, "You");

		/* Loop for number of attributes in this group. */
		for (j = 0; j < 10; j++)
		{
			bool list_ok = FALSE;

			if ((j == 0) && (f3 & (TR3_SLOW_DIGEST))) list_ok = TRUE;
			if ((j == 1) && (f3 & (TR3_FEATHER))) list_ok = TRUE;
			if ((j == 2) && (f3 & (TR3_LITE))) list_ok = TRUE;
			if ((j == 3) && (f3 & (TR3_REGEN))) list_ok = TRUE;
			if ((j == 4) && (f3 & (TR3_TELEPATHY))) list_ok = TRUE;
			if ((j == 5) && (f3 & (TR3_SEE_INVIS))) list_ok = TRUE;
			if ((j == 6) && (f3 & (TR3_FREE_ACT))) list_ok = TRUE;
			if ((j == 7) && (f3 & (TR3_HOLD_LIFE)))list_ok = TRUE;

			if (!list_ok) continue;

			/* Listing another attribute. */
			attr_listed++;

			/* Commas separate members of a list of more than two. */
			if ((attr_num > 2) && (attr_listed > 1)) strcat(desc, ",");

			/* "and" before final member of a list of more than one. */
			if ((attr_num > 1) && (j != 0))
			{
				if (attr_num == attr_listed) strcat(desc, " and");
			}

			/* List the attribute description, in its proper place. */
			if (j == 0) strcat(desc, " digest slowly");
			if (j == 1) strcat(desc, " falling gently");
			if (j == 2) strcat(desc, " glow with permanent light");
			if (j == 3) strcat(desc, " regenerative quickly");
			if (j == 4) strcat(desc, " have telepathic powers");
			if (j == 5) strcat(desc, " can see invisible monsters");
			if (j == 6) strcat(desc, " are immune to paralysis");
			if (j == 7) strcat(desc, " are resistant to life draining");
		}

		/* End sentence.  Go to next line. */
		strcat(desc, ".");
	}

	return(desc);

}
/*
 * Browse known specialty abilities -BR-
 * Adapted from birth.c get_player_choice
 */
void do_cmd_view_abilities(void)
{
	int top = 0, cur = 0;
	int i, spec_known, racial_known, class_known, dir;
	int total_known = 0;
	int race_start, class_start, race_other_start;
	char c;
	int hgt;
	byte racial_list[32];
	byte class_list[32];
	char buf[80];
	bool done;
	byte color;
	char race_other_desc[1000] ="";

        /* Count the number of specialties we know */
	for (i = 0, spec_known = 0; i < MAX_SPECIALTIES; i++)
	{
		if (p_ptr->specialty_order[i] != SP_NO_SPECIALTY) spec_known++;
	}

	total_known += spec_known;

	/* Count the number of class powers we have */
        for (i = 0, class_known = 0; i < 32; i++)
        {
                if (cp_ptr->flags_special & (0x00000001L << i))
		{
			class_list[class_known++] = i;
		}
        }

	total_known += class_known;

	/* Count the number of racial powers we have */
        for (i = 0, racial_known = 0; i < 32; i++)
        {
                if (rp_ptr->flags_special & (0x00000001L << i))
		{
			racial_list[racial_known++] = i;
		}
        }

	total_known += racial_known;

	/* Standard racial flags */
	if (rp_ptr->flags1 | rp_ptr->flags2 | rp_ptr->flags3)
	{
		total_known++;
		view_abilities_aux(race_other_desc);
	}

	class_start = spec_known;
	race_start = spec_known + class_known;
	race_other_start = spec_known + class_known + racial_known;

	/* Save and clear creen */
	screen_save();
	Term_clear();

	/* Find height of selection interface */
	hgt = Term->hgt - 7;
	if (hgt > total_known) hgt = total_known;

	/* Prompt choices */
	sprintf(buf, "Race, class, and specialties abilities (%c-%c, ESC=exit): ",
			 I2A(0), I2A(total_known-1));

	Term_putstr(5, 0, 66, TERM_WHITE, buf);


	/* View choices until user exits */
	done = FALSE;
	while (!done)
	{
		/* Redraw the list */
		for (i = 0; ((i + top < total_known) && (i < hgt)); i++)
		{
			char index;

			if (i + top < 26) index = I2A(i + top);
			else index = 'A' + (i + top - 26);

			if (i + top < class_start)
			{
				bool forgotten = (p_ptr->new_specialties < i + top + 1 - spec_known);

				sprintf(buf, "%c) Specialty Ability: %s %s", index, specialty_names[p_ptr->specialty_order[i + top]],
					(forgotten) ? "(forgotten)" : "");
				color = forgotten ? TERM_SLATE : TERM_GREEN;
			}
			else if (i + top < race_start)
			{
				sprintf(buf, "%c) Class: %s", index, specialty_names[SP_CLASS_START + class_list[i - class_start + top]]);
				color = TERM_UMBER;
			}
			else if (i + top < race_other_start)
			{
				sprintf(buf, "%c) Racial: %s", index, specialty_names[SP_RACIAL_START + racial_list[i - race_start + top]]);
				color = TERM_YELLOW;
			}
			else
			{
				sprintf(buf, "%c) Racial: Other", index);
				color = TERM_YELLOW;
			}

			/* Clear */
			Term_erase(5, i + 2, 66);

			/* Display */
			Term_putstr(5, i + 2, 66, color, buf);
		}

		/* Display that specialty's information. */
		roff("",5,0);
		Term_erase(5, hgt + 5, 255);
		Term_erase(5, hgt + 4, 255);
		Term_erase(5, hgt + 3, 255);
		if (cur < class_start) c_roff(TERM_L_BLUE, specialty_tips[p_ptr->specialty_order[cur]], 5, 0);
		else if (cur < race_start) c_roff(TERM_L_BLUE, specialty_tips[SP_CLASS_START + class_list[cur - class_start]], 5, 0);
		else if (cur < race_other_start) c_roff(TERM_L_BLUE, specialty_tips[SP_RACIAL_START + racial_list[cur - race_start]], 5, 0);
		else c_roff(TERM_L_BLUE, race_other_desc, 5, 0);

		/* Move the cursor */
		put_str("", 2 + cur - top, 5);

		/* get input */
		c = inkey();

		/* Numbers are used for scolling */
		if (isdigit(c))
		{
			/* Get a direction from the key */
			dir = target_dir(c);

			/* Going up? */
			if (dir == 8)
			{
				if (cur != 0)
				{
					/* Move selection */
					cur--;
				}

				if ((top > 0) && ((cur - top) < 4))
				{
					/* Scroll up */
					top--;
				}
			}

			/* Going down? */
			if (dir == 2)
			{
				if (cur != (total_known - 1))
				{
					/* Move selection */
					cur++;
				}

				if ((top + hgt - 1 < (total_known - 1)) && ((top + hgt - 1 - cur) < 4))
				{
					/* Scroll down */
					top++;
				}
			}
		}

		/* Letters are used for selection */
		else if (isalpha(c))
		{
			int choice;

			if (islower(c))
			{
				choice = A2I(c);
			}
			else
			{
				choice = c - 'A' + 26;
			}

			/* Validate input */
			if ((choice > -1) && (choice < total_known))
			{
				cur = choice;
			}

			else
			{
				bell("Illegal response to question!");
			}
		}

		/* Allow user to exit the fuction */
		else if (c == ESCAPE)
		{
			done = TRUE;
		}

		/* Invalid input */
		else bell("Illegal response to question!");
	}

	/* Load screen */
	screen_load();

	/* exit */
	return;
}


