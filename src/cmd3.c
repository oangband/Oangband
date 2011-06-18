/* File: cmd3.c */

/* Inventory and equipment display and management interface, observing an
 * object, inscribing, refuelling, (l)ooking around the screen and
 * Looking around the dungeon, help info on textual chars ("8" is the home,
 * etc.), monster memory interface, stealing and setting monster traps.
 *
 * Copyright (c) 1997 Ben Harrison, James E. Wilson, Robert A. Koeneke
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.  Other copyrights may also apply.
 */

#include "angband.h"


/*
 * Display inventory
 */
void do_cmd_inven(void)
{
	char string[80];

	/* Note that we are in "inventory" mode. */
	p_ptr->command_wrk = (USE_INVEN);


	/* Save screen */
	screen_save();

	/* Hack -- show empty slots */
	item_tester_full = TRUE;

	/* Display the inventory */
	show_inven();

	/* Hack -- hide empty slots */
	item_tester_full = FALSE;

	/* Insert the total burden and character capacity into a string. */
	if (use_metric) sprintf(string,
		"(Inventory) burden %d.%d kg (%d%% of capacity). Command: ",
		make_metric(p_ptr->total_weight) / 10,
		make_metric(p_ptr->total_weight) % 10,
		p_ptr->total_weight / adj_str_wgt[p_ptr->stat_ind[A_STR]]);
	else sprintf(string,
		"(Inventory) burden %d.%d lb (%d%% of capacity). Command: ",
		p_ptr->total_weight / 10, p_ptr->total_weight % 10,
		p_ptr->total_weight / adj_str_wgt[p_ptr->stat_ind[A_STR]]);


	/* Output that string, and prompt for a command. */
	prt(string, 0, 0);

	/* Hack -- Get a new command */
	p_ptr->command_new = inkey();

	/* Load screen */
	screen_load();


	/* Hack -- Process "Escape" */
	if (p_ptr->command_new == ESCAPE)
	{
		/* Reset stuff */
		p_ptr->command_new = 0;
	}

	/* Hack -- Process normal keys */
	else
	{
		/* Hack -- Use "display" mode */
		p_ptr->command_see = TRUE;
	}
}


/*
 * Display equipment
 */
void do_cmd_equip(void)
{
	char string[80];

	/* Note that we are in "equipment" mode */
	p_ptr->command_wrk = (USE_EQUIP);


	/* Save screen */
	screen_save();

	/* Hack -- show empty slots */
	item_tester_full = TRUE;

	/* Display the equipment */
	show_equip();

	/* Hack -- undo the hack above */
	item_tester_full = FALSE;


	/* Insert the total burden and character capacity into a string. */
	if (use_metric) sprintf(string,
		"(Equipment) burden %d.%d kg (%d%% of capacity). Command: ",
		make_metric(p_ptr->total_weight) / 10,
		make_metric(p_ptr->total_weight) % 10,
		p_ptr->total_weight / adj_str_wgt[p_ptr->stat_ind[A_STR]]);
	else sprintf(string,
		"(Equipment) burden %d.%d lb (%d%% of capacity). Command: ",
		p_ptr->total_weight / 10, p_ptr->total_weight % 10,
		p_ptr->total_weight / adj_str_wgt[p_ptr->stat_ind[A_STR]]);


	/* Output that string, and prompt for a command. */
	prt(string, 0, 0);

	/* Hack -- Get a new command */
	p_ptr->command_new = inkey();

	/* Load screen */
	screen_load();


	/* Hack -- Process "Escape" */
	if (p_ptr->command_new == ESCAPE)
	{
		/* Reset stuff */
		p_ptr->command_new = 0;
	}

	/* Hack -- Process normal keys */
	else
	{
		/* Enter "display" mode */
		p_ptr->command_see = TRUE;
	}
}


/*
 * The "wearable" tester
 */
static bool item_tester_hook_wear(object_type *o_ptr)
{
	/* Check for a usable slot */
	if (wield_slot(o_ptr) >= INVEN_WIELD) return (TRUE);

	/* Assume not wearable */
	return (FALSE);
}


/*
 * Wield or wear a single item from the pack or floor, if not shapechanged.
 */
void do_cmd_wield(void)
{
	int item, slot, num;

	object_type *o_ptr;

	object_type *i_ptr;
	object_type object_type_body;

	u32b f1, f2, f3;

	cptr act;

	cptr q, s;

	bool throwing;

	char o_name[120];

        if (SCHANGE)
        {
                msg_print("You cannot wield equipment while shapechanged.");
                msg_print("Use the ']' command to return to your normal form.");
                return;
        }

	/* Restrict the choices */
	item_tester_hook = item_tester_hook_wear;

	/* Get an item */
	q = "Wear/Wield which item? ";
	s = "You have nothing you can wear or wield.";
	if (!get_item(&item, q, s, (USE_INVEN | USE_FLOOR))) return;

	/* Get the item (in the pack) */
	if (item >= 0)
	{
		o_ptr = &inventory[item];
	}

	/* Get the item (on the floor) */
	else
	{
		o_ptr = &o_list[0 - item];
	}


	/* Extract the flags */
	object_flags(o_ptr, &f1, &f2, &f3);

	/* Throwing weapon or ammo? */
	throwing = (f1 & TR1_THROWING ? TRUE : FALSE);

	/* Check the slot */
	slot = wield_slot(o_ptr);

	/* Ask for ring to replace */
	if ((o_ptr->tval == TV_RING) &&
		inventory[INVEN_LEFT].k_idx &&
		inventory[INVEN_RIGHT].k_idx)
	{
		/* Restrict the choices */
		item_tester_tval = TV_RING;

		/* Choose a ring from the equipment only */
		q = "Replace which ring? ";
		s = "Oops.";
		if (!get_item(&slot, q, s, USE_EQUIP)) return;
	}

	/* Ask where to put a throwing weapon */
	if (((o_ptr->tval == TV_DIGGING) || (o_ptr->tval == TV_HAFTED) ||
	     (o_ptr->tval == TV_SWORD) || (o_ptr->tval == TV_POLEARM)) &&
	    (f1 & TR1_THROWING))
	{
		char answer;

		/* Stick it in the belt? */
		msg_print("Equip in throwing belt? (y/n)");
		answer = inkey();
		if ((answer == 'Y') || (answer == 'y')) slot = INVEN_Q0;
	}

	/* Prevent wielding into a cursed slot */
	if ((slot < INVEN_Q0) && cursed_p(&inventory[slot]))
	{
		/* Describe it */
		object_desc(o_name, &inventory[slot], FALSE, 0);

		/* Message */
		msg_format("The %s you are %s appears to be cursed.",
			   o_name, describe_use(slot));

		/* Cancel the command */
		return;
	}

	/* Take a turn */
	p_ptr->energy_use = 100;

	/* Get local object */
	i_ptr = &object_type_body;

	/* Obtain local object */
	object_copy(i_ptr, o_ptr);


	/* Usually, we wear or wield only one item. */
	num = 1;

	/* Ammo goes in quiver slots, which have special rules. */
	if (slot == INVEN_Q0)
	{
		int ammo_num = 0;
		int added_ammo_num;
		int attempted_quiver_slots;

		/* Get a quantity */
		num = get_quantity(NULL, o_ptr->number);

		/* Cancel */
		if (!num) return;

		/* Count number of missiles in the quiver slots. */
		ammo_num = quiver_count();

		/* Effective added count */
		added_ammo_num = (throwing ? num * THROWER_AMMO_FACTOR : num);

		/*
		 * If the ammo now being added will make the quiver take up another
		 * backpack slot, and there are none available, refuse to wield
		 * the new ammo.
		 */

		/* How many quiver slots would be needed */
		/* Rebate one if the equip action would free a space */
		attempted_quiver_slots = ((ammo_num + added_ammo_num + 98) / 99) -
		  (((item >= 0) && (num == o_ptr->number)) ? 1 : 0);

		/* Is there room, given normal inventory? */
		if ((attempted_quiver_slots + p_ptr->inven_cnt) > INVEN_PACK)
		{
			msg_print("Your quiver needs more backpack space.");
			return;
		}

		/* Find a slot that can hold more ammo. */
		slot = process_quiver(num, o_ptr);

		if (!slot)
		{
			/* No space. */
			msg_print("Your quiver is full.");
			return;
		}

		/* Quiver will be reorganized (again) later. */
		p_ptr->notice |= (PN_COMBINE);
	}

	/* Modify quantity */
	i_ptr->number = num;


	/* Decrease the item (from the pack) */
	if (item >= 0)
	{
		inven_item_increase(item, -num);
		inven_item_optimize(item);
	}

	/* Decrease the item (from the floor) */
	else
	{
		floor_item_increase(0 - item, -num);
		floor_item_optimize(0 - item);
	}

	/* Access the wield slot */
	o_ptr = &inventory[slot];


	/* Handle existing item. */
	if (o_ptr->k_idx)
	{
		/* Take off existing item, unless in the quiver. */
		if ((slot < INVEN_Q0) || (slot > INVEN_Q9))
		{
			(void)inven_takeoff(slot, 255);
		}

		/* Combine existing ammo with new. */
		else
		{
			p_ptr->equip_cnt--;
			p_ptr->total_weight -= o_ptr->weight * o_ptr->number;
			i_ptr->number += o_ptr->number;
		}
	}

	/* Wear the new stuff */
	object_copy(o_ptr, i_ptr);

	/* Increase the weight */
	p_ptr->total_weight += i_ptr->weight * i_ptr->number;

	/* Increment the equip counter by hand */
	p_ptr->equip_cnt++;


	/* If he wields a weapon that requires two hands, or hasn't the
	 * strength to wield a weapon that is usually wielded with both hands
	 * one-handed (normally requires 18/140 to 18/160 STR), the
	 * character will automatically carry any equipped shield on his back. -LM-
	 */
	if ((slot == INVEN_WIELD) && (inventory[INVEN_ARM].k_idx))
	{
		if (f3 & (TR3_TWO_HANDED_REQ) || (f3 & (TR3_TWO_HANDED_DES) &&
			(p_ptr->stat_ind[A_STR] <
			29 + ((o_ptr->weight / 50 > 8) ? 8 : (o_ptr->weight / 50)))))
		{
			p_ptr->shield_on_back = TRUE;
		}
		else p_ptr->shield_on_back = FALSE;
	}

	/* A character using both hands to wield his melee weapon will use his
	 * back to carry an equipped shield. -LM-
	 */
	if ((slot == INVEN_ARM) && (inventory[INVEN_WIELD].k_idx))
	{
		/* Access the wield slot */
		i_ptr = &inventory[INVEN_WIELD];

		/* Extract the flags */
		object_flags(i_ptr, &f1, &f2, &f3);


		if (f3 & (TR3_TWO_HANDED_REQ) || (f3 & (TR3_TWO_HANDED_DES) &&
			(p_ptr->stat_ind[A_STR] <
			29 + (i_ptr->weight / 50 > 8 ? 8 : i_ptr->weight / 50))))
		{
			p_ptr->shield_on_back = TRUE;
		}
		else p_ptr->shield_on_back = FALSE;

	}

	/* Where is the item now */
	if (slot == INVEN_WIELD)
	{
		act = "You are wielding";
	}
	else if (slot == INVEN_BOW)
	{
		act = "You are shooting with";
	}
	else if (slot == INVEN_LITE)
	{
		act = "Your light source is";
	}
	else if ((slot < INVEN_Q0) || (slot > INVEN_Q9))
	{
		act = "You are wearing";
	}
	else
	{
		act = "You have readied";
	}

	/* Describe the result */
	object_desc(o_name, o_ptr, TRUE, 3);

	/* Message */
	msg_format("%s %s (%c).", act, o_name, index_to_label(slot));

	/* Set item handling -GS- */
	if (o_ptr->name1)
	{

		/* Is the artifact a set item? */
		artifact_type *a_ptr = &a_info[o_ptr->name1];
		if (a_ptr->set_no!=0)
		{
			/*
			 * The object is part of a set. Check to see if rest of
			 * set is equiped.
			 */
			if (check_set(a_ptr->set_no))
			{
				/* add bonuses */
				apply_set(a_ptr->set_no);
			}
		}
	}

	/* Cursed! */
	if (cursed_p(o_ptr))
	{
		/* Warn the player */
		msg_print("Oops! It feels deathly cold!");

		/* Note the curse */
		o_ptr->ident |= (IDENT_SENSE);
	}

	/* Recalculate bonuses */
	p_ptr->update |= (PU_BONUS);

	/* Recalculate torch */
	p_ptr->update |= (PU_TORCH);

	/* Recalculate mana */
	p_ptr->update |= (PU_MANA);

	/* Window stuff */
	p_ptr->window |= (PW_INVEN | PW_EQUIP | PW_PLAYER_0 | PW_PLAYER_1);
}



/*
 * Take off an item, if not shapechanged.
 */
void do_cmd_takeoff(void)
{
	int item;

	object_type *o_ptr;

	cptr q, s;

	if (SCHANGE)
	{
		msg_print("You cannot take off equipment while shapechanged.");
		msg_print("Use the ']' command to return to your normal form.");
		return;
	}


	/* Get an item */
	q = "Take off which item? ";
	s = "You are not wearing anything to take off.";
	if (!get_item(&item, q, s, (USE_EQUIP))) return;

	/* Get the item (in the pack) */
	if (item >= 0)
	{
		o_ptr = &inventory[item];
	}

	/* Get the item (on the floor) */
	else
	{
		o_ptr = &o_list[0 - item];
	}


	/* Item is cursed */
	if (cursed_p(o_ptr))
	{
		/* Oops */
		msg_print("Hmmm, it seems to be cursed.");

		/* Nope */
		return;
	}


	/* Take a partial turn */
	p_ptr->energy_use = 50;

	/* Ensure that the shield hand is used, if a shield is available. */
	if (wield_slot(o_ptr) == INVEN_WIELD) p_ptr->shield_on_back = FALSE;

	/* Take off the item */
	(void)inven_takeoff(item, 255);
}


/*
 * Drop an item
 */
void do_cmd_drop(void)
{
	int item, amt;

	object_type *o_ptr;

	cptr q, s;


	/* Get an item */
	q = "Drop which item? ";
	s = "You have nothing to drop.";
	if (SCHANGE)
	{
		if (!get_item(&item, q, s, (USE_INVEN))) return;
	}
	else
	{
		if (!get_item(&item, q, s, (USE_EQUIP | USE_INVEN))) return;
	}

	/* Get the item (in the pack) */
	if (item >= 0)
	{
		o_ptr = &inventory[item];
	}

	/* Get the item (on the floor) */
	else
	{
		o_ptr = &o_list[0 - item];
	}

	/* Get a quantity */
	amt = get_quantity(NULL, o_ptr->number);

	/* Allow user abort */
	if (amt <= 0) return;

	/* Hack -- Cannot remove cursed items */
	if ((item >= INVEN_WIELD) && cursed_p(o_ptr))
	{
		/* Oops */
		msg_print("Hmmm, it seems to be cursed.");

		/* Nope */
		return;
	}

	/* Ensure that the shield hand is used, if a shield is available. */
	if (item == INVEN_WIELD) p_ptr->shield_on_back = FALSE;

	/* Take a partial turn */
	p_ptr->energy_use = 50;

	/* Drop (some of) the item */
	inven_drop(item, amt);
}

/*
 * Destroy an item
 *
 * No longer takes a turn -BR-
 */
void do_cmd_destroy(void)
{
	int item, amt;
	int old_number;

	object_type *o_ptr;
	object_kind *k_ptr;

	char o_name[120];

	char out_val[160];

	cptr q, s;

	/* Get an item */
	q = "Destroy which item? ";
	s = "You have nothing to destroy.";
	if (!get_item(&item, q, s, (USE_INVEN | USE_FLOOR | CAN_SQUELCH))) return;

	/* Try to destroy all items marked SQUELCH */
	if (item == ALL_SQUELCHED)
	{
		(void)(destroy_squelched_items());
		return;
	}

	/* Get the item (in the pack) */
	if (item >= 0)
	{
		o_ptr = &inventory[item];
	}

	/* Get the item (on the floor) */
	else
	{
		o_ptr = &o_list[0 - item];
	}

	/* Get the object kind. */
	k_ptr = &k_info[o_ptr->k_idx];

	/* Get a quantity */
	amt = get_quantity(NULL, o_ptr->number);

	/* Allow user abort */
	if (amt <= 0) return;

	/* Describe the object */
	old_number = o_ptr->number;
	o_ptr->number = amt;
	object_desc(o_name, o_ptr, TRUE, 3);
	o_ptr->number = old_number;

	/* Verify destruction */
	if (verify_destroy && (verify_destroy_junk || (object_value(o_ptr) >= 1)))
	{
		sprintf(out_val, "Really destroy %s? ", o_name);
		if (!get_check(out_val)) return;
	}

	/* Artifacts cannot be destroyed */
	if (artifact_p(o_ptr))
	{
		int feel = FEEL_SPECIAL;

		/* Message */
		msg_format("You cannot destroy %s.", o_name);

		/* Hack -- Handle icky artifacts */
		if (cursed_p(o_ptr) || broken_p(o_ptr)) feel = FEEL_TERRIBLE;

		/* Hack -- inscribe the artifact, if not identified. */
		if (!object_known_p(o_ptr)) o_ptr->feel = feel;

		/* We have "felt" it (again) */
		o_ptr->ident |= (IDENT_SENSE);

		/* Combine the pack */
		p_ptr->notice |= (PN_COMBINE);

		/* Window stuff */
		p_ptr->window |= (PW_INVEN | PW_EQUIP);

		/* Done */
		return;
	}

	/* Message */
	msg_format("You destroy %s.", o_name);

	/* Reduce the charges of rods/wands */
	reduce_charges(o_ptr, amt);

	/* Eliminate the item (from the pack) */
	if (item >= 0)
	{
		inven_item_increase(item, -amt);
		inven_item_describe(item);
		inven_item_optimize(item);
	}

	/* Eliminate the item (from the floor) */
	else
	{
		floor_item_increase(0 - item, -amt);
		floor_item_describe(0 - item);
		floor_item_optimize(0 - item);
	}
}


/*
 * Display specialized object information.  -LM-
 *
 * Unidentified:
 *	Weapons and armour -> description of specific object type (dagger,
 *	  etc.).
 *	Others -> descrtiption only of general object kind (scroll, etc.)
 * Identified or aware:
 *	Artifacts -> artifact-specific description.
 *	Most objects -> description of specific object type.
 *	Scrolls, potions, spellbooks, rings, and amulets -> description
 *	  only of general object kind.
 * *Identified*:
 *	All -> description of object type or artifact description,
 *	  complete listing of attributes and flags.
 *
 * Objects may also be members of a class with known effects.  If so,
 * extra information about effects when used will appear if the effects
 * can be quantified.
 *
 * Boolean value "in_store" only takes effect if player is in some store.
 */
void do_cmd_observe(object_type *o_ptr, bool in_store)
{
	int item;
	int y, x;
	int i;

	bool aware, known, known_effects, mental;

	object_kind *k_ptr;

	char o_name[120];

	char info_text[2048];
	char *object_kind_info;

	cptr q, s;


	/* Initialize object description. */
	strcpy(info_text, "");

	/* If not called in a store, we must get an object to inspect. */
	if (!o_ptr)
	{
		/* Get an item */
		q = "Examine which item? ";
		s = "You have nothing to examine.";
		if (!get_item(&item, q, s, (USE_EQUIP | USE_INVEN | USE_FLOOR))) return;

		/* Get the item (in the pack) */
		if (item >= 0)
		{
			o_ptr = &inventory[item];
		}

		/* Get the item (on the floor) */
		else
		{
			o_ptr = &o_list[0 - item];
		}
	}


	/* Get the object kind. */
	k_ptr = &k_info[o_ptr->k_idx];


	/* Create and output a status message (hack - not in stores). */
	if (!in_store)
	{
		object_desc(o_name, o_ptr, TRUE, 3);
		msg_format("Examining %s...", o_name);
	}


	/* What is our level of knowledge about the object? */
	aware = object_aware_p(o_ptr);
	known = (object_known_p(o_ptr) || in_store);
	known_effects = k_ptr->known_effect;
	mental = o_ptr->ident & (IDENT_MENTAL);

	/* Hack - Avoid giving away too much info in normal stores about objects
	 * other than weapons and armour (no sneaky learning about wand damages!).
	 */
	if ((in_store) && ((!k_ptr->known_effect) &&
		((o_ptr->tval < TV_SHOT) || (o_ptr->tval > TV_DRAG_ARMOR))))
	{
		known = TRUE;
		mental = FALSE;
	}

	/* Object is fully known - give maximal information. */
	if (mental)
	{
		/* Get the specific object type's information. */
		object_info(info_text, o_ptr, in_store);

		/* No object kind info. */
		object_kind_info = "";
	}

	/* Object or object type is identified - show all basic information. */
	else if ((known) || (aware))
	{
		/* Get the specific object type's information, if any. */
		object_info(info_text, o_ptr, in_store);

		/* Get information about the general object kind. */
		object_kind_info = format("%s", obj_class_info[o_ptr->tval]);
	}


	/* Nothing is known about the object or object type - show only
	 * information about the general object kind.
	 */
	else
	{
		/* Get information about the general object kind. */
		object_kind_info = format("%s", obj_class_info[o_ptr->tval]);
	}


	/* Save screen */
	screen_save();

	/* Erase the screen */
	Term_clear();


	/* Label the information. */
	roff("Item Information:", 3, 0);
	for (i = 0; i < 3; i++) roff("\n", 0, 0);

	/* Object type or artifact information. */
	c_roff(TERM_L_BLUE, info_text, 3, 77);

	/*
	 * If it is a set item, describe it as such.
	 */
	if ((known) && (o_ptr->name1))
	{
		artifact_type *a_ptr = &a_info[o_ptr->name1];

		/* Is it a set item? */
		if (a_ptr->set_no)
		{

			/* Advance a line */
			for (i = 0; i < 2; i++) roff("\n", 0, 0);

			/* Set notification */
			c_roff(TERM_GREEN,"Set Item: ",3,77);

			/* Fully ID describtion? */
			if (mental)
			{
				set_type *s_ptr = &s_info[a_ptr->set_no];
				strcpy(info_text, s_text + s_ptr->text);
				c_roff(TERM_GREEN,info_text,3,77);
			}

			/* Generic describtion */
			else c_roff(TERM_GREEN,"It gains power when combined with matching items",3,77);

			/* End sentence */
			c_roff(TERM_GREEN,".",3,77);
		}
	}

	/* Fully identified objects. */
	if (mental)
	{
		for (i = 0; i < 3; i++) roff("\n", 0, 0);

		/* Fully describe the object flags and attributes. */
		identify_fully_aux(o_ptr);

		/* Obtain the cursor location */
		(void)Term_locate(&x, &y);

		/* Hack -- attempt to stay on screen. */
		for (i = y; i < Term->hgt; i++)
		{
			/* No more space! */
			if (i > Term->hgt - 2) break;

			/* Advance one line. */
			roff("\n", 0, 0);

			/* Enough clear space.  Done. */
			if (i == (y + 2)) break;
		}
	}
	else
	{
		/* Spacing. */
		for (i = 0; i < 9; i++) roff("\n", 0, 0);
		/* Object kind information. */
		roff(object_kind_info, 3, 77);
		for (i = 0; i < 3; i++) roff("\n", 0, 0);
	}

	/* The exit sign. */
	roff("(Press any key to continue.)", 25, 0);
	(void)inkey();

	/* Load screen */
	screen_load();

}



/*
 * Remove the inscription from an object
 * XXX Mention item (when done)?
 */
void do_cmd_uninscribe(void)
{
	int item;

	object_type *o_ptr;

	cptr q, s;


	/* Get an item */
	q = "Un-inscribe which item? ";
	s = "You have nothing to un-inscribe.";
	if (!get_item(&item, q, s, (USE_EQUIP | USE_INVEN | USE_FLOOR))) return;

	/* Get the item (in the pack) */
	if (item >= 0)
	{
		o_ptr = &inventory[item];
	}

	/* Get the item (on the floor) */
	else
	{
		o_ptr = &o_list[0 - item];
	}

	/* Nothing to remove */
	if (!o_ptr->note)
	{
		msg_print("That item had no inscription to remove.");
		return;
	}

	/* Message */
	msg_print("Inscription removed.");

	/* Remove the incription */
	o_ptr->note = 0;

	/* Combine the pack (or the quiver) */
	p_ptr->notice |= (PN_COMBINE);

	/* Window stuff */
	p_ptr->window |= (PW_INVEN | PW_EQUIP);
}


/*
 * Inscribe an object with a comment
 */
void do_cmd_inscribe(void)
{
	int item;

	object_type *o_ptr;

	char o_name[120];

	char tmp[81];

	cptr q, s;


	/* Get an item */
	q = "Inscribe which item? ";
	s = "You have nothing to inscribe.";
	if (!get_item(&item, q, s, (USE_EQUIP | USE_INVEN | USE_FLOOR))) return;

	/* Get the item (in the pack) */
	if (item >= 0)
	{
		o_ptr = &inventory[item];
	}

	/* Get the item (on the floor) */
	else
	{
		o_ptr = &o_list[0 - item];
	}

	/* Describe the activity */
	object_desc(o_name, o_ptr, TRUE, 3);

	/* Message */
	msg_format("Inscribing %s.", o_name);
	msg_print(NULL);

	/* Start with nothing */
	strcpy(tmp, "");

	/* Use old inscription */
	if (o_ptr->note)
	{
		/* Start with the old inscription */
		strcpy(tmp, quark_str(o_ptr->note));
	}

	/* Get a new inscription (possibly empty) */
	if (get_string("Inscription: ", tmp, 81))
	{
		/* Save the inscription */
		o_ptr->note = quark_add(tmp);

		/* Combine the pack (or the quiver) */
		p_ptr->notice |= (PN_COMBINE);

		/* Window stuff */
		p_ptr->window |= (PW_INVEN | PW_EQUIP);
	}
}



/*
 * An "item_tester_hook" for refilling lanterns
 */
static bool item_tester_refill_lantern(object_type *o_ptr)
{
	/* Flasks of oil are okay */
	if (o_ptr->tval == TV_FLASK) return (TRUE);

	/* Non-empty lanterns are okay */
	if ((o_ptr->tval == TV_LITE) && (o_ptr->sval == SV_LITE_LANTERN) &&
		(o_ptr->pval > 0))
	{
		return (TRUE);
	}

	/* Assume not okay */
	return (FALSE);
}


/*
 * Refill the players lamp (from the pack or floor)
 */
static void do_cmd_refill_lamp(void)
{
	int item;

	object_type *o_ptr;
	object_type *j_ptr;

	cptr q, s;


	/* Restrict the choices */
	item_tester_hook = item_tester_refill_lantern;

	/* Get an item */
	q = "Refill with which flask? ";
	s = "You have no flasks of oil.";
	if (!get_item(&item, q, s, (USE_INVEN | USE_FLOOR))) return;

	/* Get the item (in the pack) */
	if (item >= 0)
	{
		o_ptr = &inventory[item];
	}

	/* Get the item (on the floor) */
	else
	{
		o_ptr = &o_list[0 - item];
	}


	/* Take a partial turn */
	p_ptr->energy_use = 50;

	/* Access the lantern */
	j_ptr = &inventory[INVEN_LITE];

	/* Refuel */
	j_ptr->pval += o_ptr->pval;

	/* Message */
	msg_print("You fuel your lamp.");

	/* Comment */
	if (j_ptr->pval >= FUEL_LAMP)
	{
		j_ptr->pval = FUEL_LAMP;
		msg_print("Your lamp is full.");
	}

	/* Use fuel from a lantern */
	if (o_ptr->sval == SV_LITE_LANTERN)
	{
		/* No more fuel */
		o_ptr->pval = 0;

		/* Combine / Reorder the pack (later) */
		p_ptr->notice |= (PN_COMBINE | PN_REORDER);

		/* Window stuff */
		p_ptr->window |= (PW_INVEN);
	}

	/* Decrease the item (from the pack) */
	else if (item >= 0)
	{
		inven_item_increase(item, -1);
		inven_item_describe(item);
		inven_item_optimize(item);
	}

	/* Decrease the item (from the floor) */
	else
	{
		floor_item_increase(0 - item, -1);
		floor_item_describe(0 - item);
		floor_item_optimize(0 - item);
	}

	/* Recalculate torch */
	p_ptr->update |= (PU_TORCH);
}



/*
 * An "item_tester_hook" for refilling torches
 */
static bool item_tester_refill_torch(object_type *o_ptr)
{
	/* Torches are okay */
	if ((o_ptr->tval == TV_LITE) &&
		(o_ptr->sval == SV_LITE_TORCH)) return (TRUE);

	/* Assume not okay */
	return (FALSE);
}


/*
 * Refuel the players torch (from the pack or floor)
 */
static void do_cmd_refill_torch(void)
{
	int item;

	object_type *o_ptr;
	object_type *j_ptr;

	cptr q, s;


	/* Restrict the choices */
	item_tester_hook = item_tester_refill_torch;

	/* Get an item */
	q = "Refuel with which torch? ";
	s = "You have no extra torches.";
	if (!get_item(&item, q, s, (USE_INVEN | USE_FLOOR))) return;

	/* Get the item (in the pack) */
	if (item >= 0)
	{
		o_ptr = &inventory[item];
	}

	/* Get the item (on the floor) */
	else
	{
		o_ptr = &o_list[0 - item];
	}


	/* Take a partial turn */
	p_ptr->energy_use = 50;

	/* Access the primary torch */
	j_ptr = &inventory[INVEN_LITE];

	/* Refuel */
	j_ptr->pval += o_ptr->pval + 5;

	/* Message */
	msg_print("You combine the torches.");

	/* Over-fuel message */
	if (j_ptr->pval >= FUEL_TORCH)
	{
		j_ptr->pval = FUEL_TORCH;
		msg_print("Your torch is fully fueled.");
	}

	/* Refuel message */
	else
	{
		msg_print("Your torch glows more brightly.");
	}

	/* Decrease the item (from the pack) */
	if (item >= 0)
	{
		inven_item_increase(item, -1);
		inven_item_describe(item);
		inven_item_optimize(item);
	}

	/* Decrease the item (from the floor) */
	else
	{
		floor_item_increase(0 - item, -1);
		floor_item_describe(0 - item);
		floor_item_optimize(0 - item);
	}

	/* Recalculate torch */
	p_ptr->update |= (PU_TORCH);
}




/*
 * Refill the players lamp, or restock his torches
 */
void do_cmd_refill(void)
{
	object_type *o_ptr;

	/* Get the light */
	o_ptr = &inventory[INVEN_LITE];

	/* It is nothing */
	if (o_ptr->tval != TV_LITE)
	{
		msg_print("You are not wielding a light.");
	}

	/* It's a lamp */
	else if (o_ptr->sval == SV_LITE_LANTERN)
	{
		do_cmd_refill_lamp();
	}

	/* It's a torch */
	else if (o_ptr->sval == SV_LITE_TORCH)
	{
		do_cmd_refill_torch();
	}

	/* No torch to refill */
	else
	{
		msg_print("Your light cannot be refilled.");
	}
}






/*
 * Target command
 */
void do_cmd_target(void)
{
	/* Target set */
	if (target_set_interactive(TARGET_KILL))
	{
		msg_print("Target Selected.");
	}

	/* Target aborted */
	else
	{
		msg_print("Target Aborted.");
	}
}



/*
 * Look command
 */
void do_cmd_look(void)
{
	/* Look around */
	if (target_set_interactive(TARGET_LOOK))
	{
		msg_print("Target Selected.");
	}
}



/*
 * Allow the player to examine other sectors on the map
 */
void do_cmd_locate(void)
{
	int dir, y1, x1, y2, x2;
	int wid, hgt;
	char tmp_val[80];
	char out_val[160];


	/* Get size */
	Term_get_size(&wid, &hgt);

	/* Offset */
	wid -= COL_MAP + 1;
	hgt -= ROW_MAP + 1;

	if (panel_extra_rows) hgt -= 2;

	/* Start at current panel */
	y2 = y1 = panel_row_min;
	x2 = x1 = panel_col_min;

	/* Show panels until done */
	while (1)
	{
		/* Describe the location */
		if ((y2 == y1) && (x2 == x1))
		{
			tmp_val[0] = '\0';
		}
		else
		{
			sprintf(tmp_val, "%s%s of",
				((y2 < y1) ? " North" : (y2 > y1) ? " South" : ""),
				((x2 < x1) ? " West" : (x2 > x1) ? " East" : ""));
		}

		/* Prepare to ask which way to look */
		sprintf(out_val,
			"Map sector [%d(%02d),%d(%02d)], which is%s your sector.  Direction?",
			y2 / (hgt / 2), y2 % (hgt / 2),
			x2 / (wid / 2), x2 % (wid / 2), tmp_val);

		/* Assume no direction */
		dir = 0;

		/* Get a direction */
		while (!dir)
		{
			char command;

			/* Get a command (or Cancel) */
			if (!get_com(out_val, &command)) break;

			/* Extract the action (if any) */
			dir = target_dir(command);

			/* Error */
			if (!dir) bell(NULL);
		}

		/* No direction */
		if (!dir) break;

		/* Apply the motion */
		if (change_panel(ddy[dir], ddx[dir]))
		{
			y2 = panel_row_min;
			x2 = panel_col_min;
		}
	}


	/* Recenter the map around the player */
	verify_panel();

	/* Update stuff */
	p_ptr->update |= (PU_MONSTERS);

	/* Redraw map */
	p_ptr->redraw |= (PR_MAP);

	/* Window stuff */
	p_ptr->window |= (PW_OVERHEAD | PW_DUNGEON);

	/* Handle stuff */
	handle_stuff();
}



/*
 * The table of "symbol info" -- each entry is a string of the form
 * "X:desc" where "X" is the trigger, and "desc" is the "info".
 */
static cptr ident_info[] =
{
	" :A dark grid",
	"!:A potion (or oil)",
	"\":An amulet (or necklace)",
	"#:A wall (or secret door)",
	"$:Treasure (gold or gems)",
	"%:A vein (magma or quartz)",
	/* "&:unused", */
	"':An open door",
	"(:Soft armor",
	"):A shield",
	"*:A vein with treasure",
	"+:A closed door",
	",:Food (or mushroom patch)",
	"-:A wand (or rod)",
	".:Floor",
	"/:A polearm (Axe/Pike/etc)",
	/* "0:unused", */
	"1:Entrance to General Store",
	"2:Entrance to Armory",
	"3:Entrance to Weaponsmith",
	"4:Entrance to Temple",
	"5:Entrance to Alchemy shop",
	"6:Entrance to Magic store",
	"7:Entrance to Black Market",
	"8:Entrance to your home",
	"9:Entrance to Bookseller",
	"::Rubble",
	";:A glyph of warding",
	"<:An up staircase",
	"=:A ring",
	">:A down staircase",
	"?:A scroll",
	"@:You",
	/* "A:unused", */
	"B:Bird",
	"C:Canine",
	"D:Ancient Dragon/Wyrm",
	"E:Elemental",
	"F:Dragon Fly",
	"G:Ghost",
	"H:Hybrid",
	"I:Insect",
	"J:Snake",
	"K:Killer Beetle",
	"L:Lich",
	"M:Mummy",
	/* "N:unused", */
	"O:Ogre",
	"P:Giant Humanoid",
	"Q:Quylthulg (Pulsing Flesh Mound)",
	"R:Reptile/Amphibian",
	"S:Spider/Scorpion/Tick",
	"T:Troll",
	"U:Major Demon",
	"V:Vampire",
	"W:Wight/Wraith/etc",
	"X:Xorn/Xaren/etc",
	"Y:Yeti",
	"Z:Zephyr Hound",
	"[:Hard armor",
	"\\:A hafted weapon (mace/whip/etc)",
	"]:Misc. armor",
	"^:A trap",
	"_:A staff",
	"`:A tool or junk",
	"a:Ant",
	"b:Bat",
	"c:Centipede",
	"d:Dragon",
	"e:Floating Eye",
	"f:Feline",
	"g:Golem",
	"h:Hobbit/Elf/Dwarf",
	"i:Icky Thing",
	"j:Jelly",
	"k:Kobold",
	"l:Louse",
	"m:Mold",
	"n:Naga",
	"o:Orc",
	"p:Person/Human",
	"q:Quadruped",
	"r:Rodent",
	"s:Skeleton",
	"t:Townsperson",
	"u:Minor Demon",
	"v:Vortex",
	"w:Worm/Worm-Mass",
	/* "x:unused", */
	"y:Yeek",
	"z:Zombie/Mummy",
	"{:A missile (arrow/bolt/shot)",
	"|:An edged weapon (sword/dagger/etc)",
	"}:A launcher (bow/crossbow/sling)",
	"~:A chest or light",
	NULL
};



/*
 * Sorting hook -- Comp function -- see below
 *
 * We use "u" to point to array of monster indexes,
 * and "v" to select the type of sorting to perform on "u".
 */
bool ang_sort_comp_hook(vptr u, vptr v, int a, int b)
{
	u16b *who = (u16b*)(u);

	u16b *why = (u16b*)(v);

	int w1 = who[a];
	int w2 = who[b];

	int z1, z2;


	/* Sort by player kills */
	if (*why >= 4)
	{
		/* Extract player kills */
		z1 = l_list[w1].pkills;
		z2 = l_list[w2].pkills;

		/* Compare player kills */
		if (z1 < z2) return (TRUE);
		if (z1 > z2) return (FALSE);
	}


	/* Sort by total kills */
	if (*why >= 3)
	{
		/* Extract total kills */
		z1 = l_list[w1].tkills;
		z2 = l_list[w2].tkills;

		/* Compare total kills */
		if (z1 < z2) return (TRUE);
		if (z1 > z2) return (FALSE);
	}


	/* Sort by monster level */
	if (*why >= 2)
	{
		/* Extract levels */
		z1 = r_info[w1].level;
		z2 = r_info[w2].level;

		/* Compare levels */
		if (z1 < z2) return (TRUE);
		if (z1 > z2) return (FALSE);
	}


	/* Sort by monster experience */
	if (*why >= 1)
	{
		/* Extract experience */
		z1 = r_info[w1].mexp;
		z2 = r_info[w2].mexp;

		/* Compare experience */
		if (z1 < z2) return (TRUE);
		if (z1 > z2) return (FALSE);
	}


	/* Compare indexes */
	return (w1 <= w2);
}


/*
 * Sorting hook -- Swap function -- see below
 *
 * We use "u" to point to array of monster indexes,
 * and "v" to select the type of sorting to perform.
 */
void ang_sort_swap_hook(vptr u, vptr v, int a, int b)
{
	u16b *who = (u16b*)(u);

	u16b holder;

	/* Swap */
	holder = who[a];
	who[a] = who[b];
	who[b] = holder;
}



/*
 * Hack -- Display the "name" and "attr/chars" of a monster race
 */
static void roff_top(int r_idx)
{
	monster_race *r_ptr = &r_info[r_idx];

	byte a1, a2;
	char c1, c2;


	/* Access the chars */
	c1 = r_ptr->d_char;
	c2 = r_ptr->x_char;

	/* Access the attrs */
	a1 = r_ptr->d_attr;
	a2 = r_ptr->x_attr;


	/* Clear the top line */
	Term_erase(0, 0, 255);

	/* Reset the cursor */
	Term_gotoxy(0, 0);

	/* A title (use "The" for non-uniques) */
	if (!(r_ptr->flags1 & (RF1_UNIQUE)))
	{
		Term_addstr(-1, TERM_WHITE, "The ");
	}

	/* Special title for Player ghosts. */
	if (r_ptr->flags2 & (RF2_PLAYER_GHOST))
	{
		Term_addstr(-1, TERM_WHITE, format("%s, the ", ghost_name));
	}

	/* Dump the name */
	Term_addstr(-1, TERM_WHITE, (r_name + r_ptr->name));

	/* Append the "standard" attr/char info */
	Term_addstr(-1, TERM_WHITE, " ('");
	Term_addch(a1, c1);
	Term_addstr(-1, TERM_WHITE, "')");

	/* Append the "optional" attr/char info */
	Term_addstr(-1, TERM_WHITE, "/('");
	Term_addch(a2, c2);
	Term_addstr(-1, TERM_WHITE, "'):");
}


/*
 * Identify a character, allow recall of monsters
 *
 * Several "special" responses recall "mulitple" monsters:
 *   ^A (all monsters)
 *   ^U (all unique monsters)
 *   ^N (all non-unique monsters)
 *
 * The responses may be sorted in several ways, see below.
 *
 */
void do_cmd_query_symbol(void)
{
	int i, j, n, r_idx;
	int start = 0, last_level = 0;
	char sym, query;
	char search_str[60] = "";
	char monster_name[80];
	char buf[128];
	char *sp;

	bool all = FALSE;
	bool uniq = FALSE;
	bool norm = FALSE;

	bool recall = FALSE;

	u16b why = 0;
	u16b who[MAX_R_IDX];


	/* Get a character, or abort */
	if (!get_com("Enter character to be identified: ", &sym)) return;

	/* Find that character info, and describe it */
	for (i = 0; ident_info[i]; ++i)
	{
		if (sym == ident_info[i][0]) break;
	}

	/* Describe */
	if (sym == KTRL('A'))
	{
		all = TRUE;
		strcpy(buf, "Full monster list.");
	}
	else if (sym == KTRL('U'))
	{
		all = uniq = TRUE;
		strcpy(buf, "Unique monster list.");
	}
	else if (sym == KTRL('N'))
	{
		all = norm = TRUE;
		strcpy(buf, "Non-unique monster list.");
	}
	else if (sym == KTRL('F'))
	{
		if (!get_string("Substring to search: ", search_str, sizeof(search_str)))
		  return;

		for(sp = search_str; *sp; sp++) *sp = tolower(*sp);

		sprintf(buf, "Monsters matching '%s'", search_str);
		all = FALSE;
	}
	else if (ident_info[i])
	{
		sprintf(buf, "%c - %s.", sym, ident_info[i] + 2);
	}
	else
	{
		sprintf(buf, "%c - %s.", sym, "Unknown Symbol");
	}

	/* Display the result */
	prt(buf, 0, 0);


	/* Collect matching monsters */
	for (n = 0, i = 1; i < MAX_R_IDX; i++)
	{
		monster_race *r_ptr = &r_info[i];
		monster_lore *l_ptr = &l_list[i];

		/* Nothing to recall
		 * Even cheat_know does not allow viewing non-existant
		 * player ghosts.
		 */
		if ((!cheat_know || (r_ptr->flags2 & (RF2_PLAYER_GHOST)))
		    && !l_ptr->sights)
			 continue;

		/* Require non-unique monsters if needed */
		if (norm && (r_ptr->flags1 & (RF1_UNIQUE))) continue;

		/* Require unique monsters if needed */
		if (uniq && !(r_ptr->flags1 & (RF1_UNIQUE))) continue;

		/* Collect "appropriate" monsters */
		if (*search_str)
		{
			strncpy(monster_name, r_name + r_ptr->name,
					      sizeof monster_name);
			for(sp = monster_name; *sp; sp++) *sp = tolower(*sp);
			if (strstr(monster_name, search_str)) who[n++] = i;
			continue;
		}
		if (all || (r_ptr->d_char == sym)) who[n++] = i;
	}

	/* Nothing to recall */
	if (!n) return;


	/* Prompt */
	put_str("Recall details? (k/p/y/n): ", 0, 40);

	/* Query */
	query = inkey();

	/* Restore */
	prt(buf, 0, 0);


	/* Sort by kills (and level) */
	if (query == 'k')
	{
		why = 4;
		query = 'y';
	}

	/* Sort by level */
	if (query == 'p')
	{
		why = 2;
		query = 'y';
	}

	/* Catch "escape" */
	if (query != 'y') return;


	/* Sort if needed */
	if (why)
	{
		/* Select the sort method */
		ang_sort_comp = ang_sort_comp_hook;
		ang_sort_swap = ang_sort_swap_hook;

		/* Sort the array */
		ang_sort(who, &why, n);
	}


	/* Start at the current level */
	i = 0;

	/*
	 * Find the monster whose level is the closest to the
	 * current depth, without being greater than it.
	 */
	for (j = 0; j < n; j++)
	{
		monster_race *r_ptr = &r_info[who[j]];

		if ((r_ptr->level <= p_ptr->depth) && (r_ptr->level >= last_level))
		{
			start = j;
			last_level = r_ptr->level;
		}
	}

	/* Start at the chosen monster. */
	i = start;

	/* Scan the monster memory */
	while (TRUE)
	{
		/* Extract a race */
		r_idx = who[i];

		/* Hack -- Auto-recall */
		monster_race_track(r_idx);

		/* Hack -- Handle stuff */
		handle_stuff();

		/* Hack -- Begin the prompt */
		roff_top(r_idx);

		/* Hack -- Complete the prompt */
		Term_addstr(-1, TERM_WHITE, "[(r)ecall, ESC]");
		prt(format("(#%d of %d)", i + 1, n), 0 , 65);

		/* Interact */
		while (TRUE)
		{
			/* Recall */
			if (recall)
			{
				/* Save screen */
				screen_save();

				/* Recall on screen */
				screen_roff(who[i]);

				/* Hack -- Complete the prompt (again) */
				Term_addstr(-1, TERM_WHITE, "[(r)ecall, ESC]");
				prt(format("(#%d of %d)", i + 1, n), 0 , 65);

			}

			/* Command */
			query = inkey();

			/* Unrecall */
			if (recall)
			{
				/* Load screen */
				screen_load();
			}

			/* Normal commands */
			if (query != 'r') break;

			/* Toggle recall */
			recall = !recall;
		}

		/* Stop scanning */
		if (query == ESCAPE) break;

		/* Move to "prev" monster */
		if (query == '-')
		{
			if (i-- == 0)
			{
				i = n - 1;
			}
		}

		/* Move to "next" monster */
		else
		{
			if (++i == n)
			{
				i = 0;
			}
		}
	}


	/* Re-display the identity */
	prt(buf, 0, 0);
}



/* Hack -- possible victim outcry. -LM- */
static cptr desc_victim_outcry[] =
{
	"'My money, where's my money?'",
	"'Thief! Thief! Thief! Baggins! We hates it forever!'",
	"'Tell me, have you seen a purse wandering around?'",
	"'Thieves, Fire, Murder!'",
	"''Ere, 'oo are you?'",
	"'Hey, look what I've copped!'",
	"'How dare you!'",
	"'Help yourself again, thief, there is plenty and to spare!'",
	"'All the world detests a thief.'",
	"'Catch me this thief!'",
	"'Hi! Ho! Robbery!'",
	"'My gold, my precious gold!'",
	"'My gold is costly, thief!'",
	"'Your blood for my gold?  Agreed!'",
	"'I scrimp, I save, and now it's gone!'",
	"'Robbers like you are part of the problem!'",
	"'Banditti!  This dungeon's just not safe anymore!'",
	"'Ruined!  I'm ruined!'",
	"'Where, where is the common decency?'",
	"'Your knavish tricks end here and now!'",
};



/*
 * Rogues may steal gold from monsters.  The monster needs to have
 * something to steal (it must drop some form of loot), and should
 * preferably be asleep.  Humanoids and dragons are a rogue's favorite
 * targets.  Steal too often on a level, and monsters will be more wary,
 * and the hue and cry will be eventually be raised.  Having every
 * monster on the level awake and aggravated is not pleasant. -LM-
 */
void py_steal(int y, int x)
{
	cptr act = NULL;

	monster_type *m_ptr = &m_list[cave_m_idx[y][x]];
	monster_race *r_ptr = &r_info[m_ptr->r_idx];

	char m_name[80];

	int i;
	int effect, theft_protection;
	int filching_power = 0;
	int purse = 0;

	bool thief = FALSE;
	bool success = FALSE;

	/* Hard limit on theft. */
	if (number_of_thefts_on_level > 4)
	{
		msg_print("Everyone is keeping a lookout for you.  You can steal nothing here.");
		return;
	}

	/* Determine the cunning of the thief. */
	filching_power = 2 * p_ptr->lev;

	/* Penalize some conditions */
	if (p_ptr->blind || no_lite()) filching_power = filching_power / 10;
	if (p_ptr->confused || p_ptr->image) filching_power = filching_power / 10;

	/* Determine how much protection the monster has. */
	theft_protection = (7 * (r_ptr->level + 2) / 4);
	theft_protection += (m_ptr->mspeed - p_ptr->pspeed);
	if (theft_protection < 1) theft_protection = 1;

	/* Send a thief to catch a thief. */
	for (i = 0; i < 4; i++)
	{
		/* Extract infomation about the blow effect */
		effect = r_ptr->blow[i].effect;
		if (effect == RBE_EAT_GOLD) thief = TRUE;
		if (effect == RBE_EAT_ITEM) thief = TRUE;
	}
	if (thief) theft_protection += 30;

	if (m_ptr->csleep) theft_protection = 3 * theft_protection / 5;

	/* Special player stealth magics aid stealing, but are lost in the process. */
	if (p_ptr->superstealth)
	{
		theft_protection = 3 * theft_protection / 5;
		set_superstealth(0);
	}

	/* The more you steal on a level, the more wary the monsters. */
	theft_protection += number_of_thefts_on_level * 15;

	/* Did the theft succeed?  */
	if (randint(theft_protection) < filching_power) success = TRUE;


	/* If the theft succeeded, determine the value of the purse. */
	if (success)
	{
		purse = (r_ptr->level + 1) + randint(3 * (r_ptr->level + 1) / 2);

		/* Uniques are juicy targets. */
		if (r_ptr->flags1 & (RF1_UNIQUE)) purse *= 3;

		/* But some monsters are dirt poor. */
		if (!((r_ptr->flags1 & (RF1_DROP_40)) ||
			(r_ptr->flags1 & (RF1_DROP_60)) ||
			(r_ptr->flags1 & (RF1_DROP_ONE)) ||
			(r_ptr->flags1 & (RF1_DROP_TWO)))) purse = 0;

		/* Some monster races are far better to steal from than others. */
		if ((r_ptr->d_char == 'D') || (r_ptr->d_char == 'd') ||
			(r_ptr->d_char == 'p') || (r_ptr->d_char == 'h'))
			purse *= 2 + randint(3) + randint(r_ptr->level / 20);
		else if ((r_ptr->d_char == 'P') || (r_ptr->d_char == 'o') ||
			(r_ptr->d_char == 'O') || (r_ptr->d_char == 'T') ||
			(r_ptr->d_char == 'n') || (r_ptr->d_char == 'W') ||
			(r_ptr->d_char == 'k') || (r_ptr->d_char == 'L') ||
			(r_ptr->d_char == 'V') || (r_ptr->d_char == 'y'))
			purse *= 1 + randint(3) + randint(r_ptr->level / 30);

		/* Pickings are scarce in a land of many thieves. */
		purse = purse * (p_ptr->depth + 5) / (p_ptr->max_depth + 5);

		/* Increase player gold. */
		p_ptr->au += purse;

		/* Redraw gold */
		p_ptr->redraw |= (PR_GOLD);

		/* Announce the good news. */
		if (purse) msg_format("You burgle %d gold.", purse);

		/* Pockets are empty. */
		else msg_print("You burgle only dust.");
	}

	/* The victim normally, but not always, wakes up and is aggravated. */
	if (randint(4) != 1)
	{
		m_ptr->csleep = 0;
		m_ptr->mflag |= (MFLAG_ACTV);
		if (m_ptr->mspeed < r_ptr->speed + 3) m_ptr->mspeed += 10;


		/* Occasionally, amuse the player with a message. */
		if ((randint(5) == 1) && (purse) && (r_ptr->flags2 & (RF2_SMART)))
		{
			monster_desc(m_name, m_ptr, 0);
			act = desc_victim_outcry[rand_int(20)];
			msg_format("%^s cries out %s", m_name, act);
		}
		/* Otherwise, simply explain what happened. */
		else
		{
			monster_desc(m_name, m_ptr, 0);
			msg_format("You have aroused %s.", m_name);
		}
	}

	/* The thief also speeds up, but only for just long enough to escape. */
	if (!p_ptr->fast) p_ptr->fast += 2;

	/* Recalculate bonuses */
	p_ptr->update |= (PU_BONUS);

	/* Handle stuff */
	handle_stuff();


	/* Increment the number of thefts, and possibly raise the hue and cry. */
	number_of_thefts_on_level++;

	if (number_of_thefts_on_level > 4)
	{
		/* Notify the player of the trouble he's in. */
		msg_print("All the level is in an uproar over your misdeeds!");

		/* Aggravate and speed up all monsters on level. */
		aggravate_monsters(1, TRUE);
	}

	else if ((number_of_thefts_on_level > 2) || (randint(8) == 1))
	{
		msg_print("You hear hunting parties scouring the area for a notorious burgler.");

		/* Aggravate monsters nearby. */
		aggravate_monsters(1, FALSE);
	}

	/* Rogue "Hit and Run" attack. */
	if (p_ptr->special_attack & (ATTACK_FLEE))
	{
		/* Cancel the fleeing spell */
		p_ptr->special_attack &= ~(ATTACK_FLEE);

		/* Message */
		msg_print("You escape into the shadows!");

		/* Teleport. */
		teleport_player(6 + p_ptr->lev / 5, TRUE);

		/* Redraw the state */
		p_ptr->redraw |= (PR_STATUS);
	}
}


/*
 * Rogues may set traps.  Only one such trap may exist at any one time,
 * but an old trap can be disarmed to free up equipment for a new trap.
 * -LM-
 */
void py_set_trap(int y, int x)
{
	int max_traps;

	max_traps = 1 + ((p_ptr->lev >= 25) ? 1 : 0) + (check_ability(SP_EXTRA_TRAP) ? 1 : 0);

	if (p_ptr->blind || no_lite())
	{
		msg_print("You can not see to set a trap.");
		return;
	}

	if (p_ptr->confused || p_ptr->image)
	{
		msg_print("You are too confused.");
		return;
	}

	/* Paranoia -- Forbid more than one trap being set. */
	if (num_trap_on_level >= max_traps)
	{
		msg_print("You must disarm your existing trap to free up your equipment.");
		return;
	}

	/* No setting traps while shapeshifted */
	if (SCHANGE)
	{
		msg_print("You can not set traps while shapechanged.");
		msg_print("Use the ']' command to return to your normal form.");
		return;
	}

	/* Set the trap, and draw it. */
	cave_set_feat(y, x, FEAT_MTRAP_BASE);

	/* Notify the player. */
	msg_print("You set a monster trap.");

	/* Increment the number of monster traps. */
	num_trap_on_level++;
}

/*
 * Choose advanced monster trap type
 */
bool choose_mtrap(byte *choice)
{
	int num, temp=0;

	char c;

	bool done=FALSE;
	bool chosen=FALSE;

	/* Save screen */
	screen_save();

	prt("        Choose an advanced monster trap (ESC to cancel):", 1, 8);


	if (check_ability(SP_EXTRA_TRAP)) num = 1 + (p_ptr->lev / 4);
	else num = 1 + (p_ptr->lev / 6);

        prt("        a) Sturdy Trap      (less likely to break)", 2, 8);
	if (num >= 2) prt("        b) Netted Trap      (effective versus flyers)", 3, 8);
	if (num >= 3) prt("        c) Confusion Trap   (confuses monsters)", 4, 8);
	if (num >= 4) prt("        d) Poison Gas Trap  (creates a toxic cloud)", 5, 8);
	if (num >= 5) prt("        e) Spirit Trap      (effective versus insubstantial monsters)", 6, 8);
	if (num >= 6) prt("        f) Lightning Trap   (shoots a lightning bolt)", 7, 8);
	if (num >= 7) prt("        g) Explosive Trap   (causes area damage)", 8, 8);
	if (num >= 8) prt("        h) Portal Trap      (teleports monsters)", 9, 8);
	if (num >= 9) prt("        i) Stasis Trap      (freezes time for a monster)", 10, 8);
	if (num >= 10) prt("        j) Drain Life Trap  (hurts living monsters)", 11, 8);
	if (num >= 11) prt("        k) Unmagic Trap     (deals damage and reduces mana)", 12, 8);
	if (num >= 12) prt("        l) Dispelling Trap  (hurts all monster in sight)", 13, 8);

	while (!done)
	{
		c = inkey();

		/* Letters are used for selection */
		if (isalpha(c))
		{
			if (islower(c))
			{
				temp = A2I(c);
			}
			else
			{
				temp = c - 'A' + 26;
			}

			/* Validate input */
			if ((temp > -1) && (temp < num))
			{
				done = TRUE;
				*choice = (byte) temp;
				chosen = TRUE;
			}

			else
			{
				bell("Illegal response to question!");
			}
		}

		/* Allow user to exit the fuction */
                else if (c == ESCAPE)
                {
			*choice = 0;
                        done = TRUE;
                }

                /* Invalid input */
                else bell("Illegal response to question!");
	}

	/* Load screen */
	screen_load();

	/* Return */
	return (chosen);
}

/*
 * Turn a basic monster trap into an advanced one -BR-
 */
void py_modify_trap(int y, int x)
{
	byte choice;

	if (p_ptr->blind || no_lite())
	{
		msg_print("You can not see to modify your trap.");
		return;
	}

	if (p_ptr->confused || p_ptr->image)
	{
		msg_print("You are too confused.");
		return;
	}

	/* No setting traps while shapeshifted */
	if (SCHANGE)
	{
		msg_print("You can not set traps while shapechanged.");
		msg_print("Use the ']' command to return to your normal form.");
		return;
	}

	/* get choice */
	if (choose_mtrap(&choice))
	{
		/* Set the trap, and draw it. */
		cave_set_feat(y, x, FEAT_MTRAP_BASE + 1 + choice);

		/* Notify the player. */
		msg_print("You modify the monster trap.");
	}
}

