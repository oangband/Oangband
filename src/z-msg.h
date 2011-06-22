#ifndef INCLUDED_Z_MSG_H
#define INCLUDED_Z_MSG_H

#include "h-basic.h"

/*** Constants ***/


/*** Message constants ***/

enum
{
	MSG_GENERIC       = 0,
	MSG_HIT           = 1,
	MSG_MISS          = 2,
	MSG_FLEE          = 3,
	MSG_DROP          = 4,
	MSG_KILL          = 5,
	MSG_LEVEL         = 6,
	MSG_DEATH         = 7,
	MSG_STUDY         = 8,
	MSG_TELEPORT      = 9,
	MSG_SHOOT         = 10,
	MSG_QUAFF         = 11,
	MSG_ZAP           = 12,
	MSG_WALK          = 13,
	MSG_TPOTHER       = 14,
	MSG_HITWALL       = 15,
	MSG_EAT           = 16,
	MSG_STORE1        = 17,
	MSG_STORE2        = 18,
	MSG_STORE3        = 19,
	MSG_STORE4        = 20,
	MSG_DIG           = 21,
	MSG_OPENDOOR      = 22,
	MSG_SHUTDOOR      = 23,
	MSG_TPLEVEL       = 24,
	MSG_BELL          = 25,
	MSG_NOTHING_TO_OPEN = 26,
	MSG_LOCKPICK_FAIL = 27,
	MSG_STAIRS        = 28,

	MSG_MAX           = 29
};


/*** Functions ***/

/** Initialisation/exit **/

/**
 * Initialise the messages package.  Should be called before using any other
 * functions in the package.
 */
errr messages_init(void);

/**
 * Free the message package.
 */
void messages_free(void);


/** General info **/

/**
 * Return the current number of messages stored.
 */
u16b messages_num(void);


/** Individual message handling **/

/**
 * Save a new message into the memory buffer, with text `str` and type `type`.
 * The type should be one of the MSG_ constants defined above.
 *
 * The new message may not be saved if it is identical to the one saved before
 * it, in which case the "count" of the message will be increased instead.
 * This count can be fetched using the message_count() function.
 */
void message_add(const char *str, u16b type);


/**
 * Returns the text of the message of age `age`.  The age of the most recently
 * saved message is 0, the one before that is of age 1, etc.
 *
 * Returns the empty string if no messages of the age specified are
 * available.
 */
const char *message_str(u16b age);

/**
 * Returns the number of times the message of age `age` was saved. The age of
 * the most recently saved message is 0, the one before that is of age 1, etc.
 *
 * In other words, if message_add() was called five times, one after the other,
 * with the message "The orc sets your hair on fire.", then the text will only
 * have one age (age = 0), but will have a count of 5.
 */
u16b message_count(u16b age);

/**
 * Returns the type of the message of age `age`.  The age of the most recently
 * saved message is 0, the one before that is of age 1, etc.
 *
 * The type is one of the MSG_ constants, defined above.
 */
u16b message_type(u16b age);

/**
 * Returns the display colour of the message memorised `age` messages ago.
 * (i.e. age = 0 represents the last memorised message, age = 1 is the one
 * before that, etc).
 */
byte message_color(u16b age);


/** Message type changes **/

/**
 * Returns the colour for the message type `type`.
 */
byte message_type_color(u16b type);

/**
 * Defines the color `color` for the message type `type`.
 */
void message_color_define(u16b type, byte color);


#endif /* !INCLUDED_Z_MSG_H */
