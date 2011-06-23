#ifndef INCLUDED_UI_EVENT_H
#define INCLUDED_UI_EVENT_H

/**
 * The various UI events that can occur.
 */
typedef enum
{
	EVT_NONE	= 0x0000,

	/* Basic events */
	EVT_KBRD	= 0x0001,	/* Keypress */
	EVT_MOUSE	= 0x0002,	/* Mousepress */
	EVT_RESIZE	= 0x0004,	/* Display resize */

	EVT_BUTTON	= 0x0008,	/* Button press */

	/* 'Abstract' events */
	EVT_ESCAPE	= 0x0010,	/* Get out of this menu */
	EVT_MOVE	= 0x0020,	/* Menu movement */
	EVT_SELECT	= 0x0040	/* Menu selection */
} ui_event_type;


/**
 * Given a character X, turn it into a control character.
 */
#define KTRL(X) \
	((X) & 0x1F)


/**
 * Given a control character X, turn it into its uppercase ASCII equivalent.
 */
#define UN_KTRL(X) \
	((X) + 64)


/**
 * Keyset mappings for various keys.
 */
#define ESCAPE	       0x1B

#define ARROW_DOWN     0x80
#define ARROW_LEFT     0x81
#define ARROW_RIGHT    0x82
#define ARROW_UP       0x83

/**
 * Type capable of holding any input key we might want to use.
 */
typedef u32b keycode_t;


/**
 * Struct holding all relevant info for keypresses.
 */
struct keypress {
	ui_event_type type;
	keycode_t code;
	byte mods;
};

/**
 * Struct holding all relevant info for mouse clicks.
 */
struct mouseclick {
	ui_event_type type;
	byte x;
	byte y;
	byte button;
};

/**
 * Union type to hold information about any given event.
 */
typedef union {
	ui_event_type type;
	struct mouseclick mouse;
	struct keypress key;
} ui_event;

#endif /* INCLUDED_UI_EVENT_H */
