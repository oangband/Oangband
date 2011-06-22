/* File: variable.c */

/* The copyright.  Definitions for a large number of variables, arrays,
 * and pointers, plus the color table and sound names.
 *
 * Copyright (c) 1997 Ben Harrison, James E. Wilson, Robert A. Koeneke
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.  Other copyrights may also apply.
 */

#include "angband.h"


/*
 * Hack -- Link a copyright message into the executable
 */
const char * copyright[5] =
{
	"Copyright (c) 1997 Ben Harrison, James E. Wilson, Robert A. Keoneke",
	"",
	"This software may be copied and distributed for educational, research,",
	"and not for profit purposes provided that this copyright and statement",
	"are included in all such copies.  Other copyrights may also apply."
};


/*
 * Release of standard Angband from which this version of Oangband
 * is derived.
 */
byte version_major = VERSION_MAJOR;
byte version_minor = VERSION_MINOR;
byte version_patch = VERSION_PATCH;
byte version_extra = VERSION_EXTRA;

/* Version of Oangband. */
byte o_version_major = O_VERSION_MAJOR;
byte o_version_minor = O_VERSION_MINOR;
byte o_version_patch = O_VERSION_PATCH;


/*
 * Savefile version - Angband reckoning
 */
byte sf_major;			/* Savefile's "version_major" */
byte sf_minor;			/* Savefile's "version_minor" */
byte sf_patch;			/* Savefile's "version_patch" */
byte sf_extra;			/* Savefile's "version_extra". Used for enryption */

/*
 * Savefile version - Oangband reckoning
 */
byte o_sf_major;			/* Savefile's "version_major" */
byte o_sf_minor;			/* Savefile's "version_minor" */
byte o_sf_patch;			/* Savefile's "version_patch" */
byte o_sf_extra;			/* Savefile's "version_extra".  Not currently used */

/*
 * Savefile information
 */
u32b sf_xtra;			/* Operating system info */
u32b sf_when;			/* Time when savefile created */
u16b sf_lives;			/* Number of past "lives" with this file */
u16b sf_saves;			/* Number of "saves" during this life */

/*
 * Run-time arguments
 */
bool arg_fiddle;			/* Command arg -- Request fiddle mode */
bool arg_wizard;			/* Command arg -- Request wizard mode */
bool arg_sound;				/* Command arg -- Request special sounds */
bool arg_graphics;			/* Command arg -- Request graphics mode */
bool arg_monochrome;		/* Command arg -- Request monochrome mode */
bool arg_force_original;	/* Command arg -- Request original keyset */
bool arg_force_roguelike;	/* Command arg -- Request roguelike keyset */

/*
 * Various things
 */

bool character_generated;	/* The character exists */
bool character_dungeon;		/* The character has a dungeon */
bool character_loaded;		/* The character was loaded from a savefile */
bool character_saved;		/* The character was just saved to a savefile */
bool character_existed;			/* A character once existed on this savefile */

s16b character_icky;		/* Depth of the game in special mode */
s16b character_xtra;		/* Depth of the game in startup mode */

u32b seed_flavor;		/* Hack -- consistent object colors */
u32b seed_town;			/* Hack -- consistent town layout */

s16b num_repro;			/* Current reproducer count */
s16b object_level;		/* Current object creation level */
s16b monster_level;		/* Current monster creation level */

char summon_kin_type;		/* Hack -- See summon_specific() */

s32b turn;				/* Current game turn */

s32b old_turn;			/* Hack -- Level feeling counter */

bool use_sound;			/* The "sound" mode is enabled */
bool use_graphics;		/* The "graphics" mode is enabled */

bool use_transparency = FALSE; /* Use transparent tiles */

int image_count;  		/* Grids until next random image    */
                  		/* Optimizes the hallucination code */

s16b signal_count;		/* Hack -- Count interupts */

bool msg_flag;			/* Player has pending message */

bool inkey_base;		/* See the "inkey()" function */
bool inkey_xtra;		/* See the "inkey()" function */
bool inkey_scan;		/* See the "inkey()" function */
bool inkey_flag;		/* See the "inkey()" function */

s16b coin_type;			/* Hack -- force coin type */

bool opening_chest;		/* Hack -- prevent chest generation */

bool shimmer_monsters;	/* Hack -- optimize multi-hued monsters */
bool shimmer_objects;	/* Hack -- optimize multi-hued objects */

bool repair_mflag_show;	/* Hack -- repair monster flags (show) */
bool repair_mflag_mark;	/* Hack -- repair monster flags (mark) */

s16b o_max = 1;			/* Number of allocated objects */
s16b o_cnt = 0;			/* Number of live objects */

s16b m_max = 1;			/* Number of allocated monsters */
s16b m_cnt = 0;			/* Number of live monsters */

/*
 * Height of dungeon map on screen.
 */
s16b SCREEN_HGT = 22;
s16b SCREEN_WID = 66;

/*
 * Dungeon variables
 */

s16b feeling;			/* Most recent feeling */
s16b rating;			/* Level's current rating */
bool good_item_flag;	/* True if "Artifact" on this level */

bool closing_flag;		/* Dungeon is closing */

bool fake_monochrome;	/* Use fake monochrome for effects */


/*
 * Dungeon size info
 */

s16b max_panel_rows, max_panel_cols;
s16b panel_row_min, panel_row_max;
s16b panel_col_min, panel_col_max;
s16b panel_col_prt, panel_row_prt;
bool panel_extra_rows=FALSE;

byte *mp_a = NULL;
char *mp_c = NULL;

byte *mp_ta = NULL;
char *mp_tc = NULL;

/*
 * Player info
 */
int player_euid;


/*
 * Buffer to hold the current savefile name
 */
char savefile[1024];


/*
 * Number of active macros.
 */
s16b macro__num;

/*
 * Array of macro patterns [MACRO_MAX]
 */
const char * *macro__pat;

/*
 * Array of macro actions [MACRO_MAX]
 */
const char * *macro__act;


/*
 * The array[TERM_WIN_MAX] of window pointers
 */
term *angband_term[TERM_WIN_MAX];


/*
 * The array[TERM_WIN_MAX] of window names (modifiable?)
 */
char angband_term_name[TERM_WIN_MAX][16] =
{
	"OAngband",
	"Term-1",
	"Term-2",
	"Term-3",
	"Term-4",
	"Term-5",
	"Term-6",
	"Term-7"
};


/*
 * Global table of color definitions (mostly zeros)
 */
byte angband_color_table[MAX_COLORS][4] =
{
	{0x00, 0x00, 0x00, 0x00},	/* TERM_DARK */
	{0x00, 0xFF, 0xFF, 0xFF},	/* TERM_WHITE */
	{0x00, 0x80, 0x80, 0x80},	/* TERM_SLATE */
	{0x00, 0xFF, 0x80, 0x00},	/* TERM_ORANGE */
	{0x00, 0xC0, 0x00, 0x00},	/* TERM_RED */
	{0x00, 0x00, 0x80, 0x40},	/* TERM_GREEN */
	{0x00, 0x00, 0x40, 0xFF},	/* TERM_BLUE */
	{0x00, 0x80, 0x40, 0x00},	/* TERM_UMBER */
	{0x00, 0x60, 0x60, 0x60},	/* TERM_L_DARK */
	{0x00, 0xC0, 0xC0, 0xC0},	/* TERM_L_WHITE */
	{0x00, 0xFF, 0x00, 0xFF},	/* TERM_L_PURPLE */
	{0x00, 0xFF, 0xFF, 0x00},	/* TERM_YELLOW */
	{0x00, 0xFF, 0x00, 0x00},	/* TERM_L_RED */
	{0x00, 0x00, 0xFF, 0x00},	/* TERM_L_GREEN */
	{0x00, 0x00, 0xFF, 0xFF},	/* TERM_L_BLUE */
	{0x00, 0xC0, 0x80, 0x40},	/* TERM_L_UMBER */
	{0x00, 0x90, 0x00, 0x90}, /* 16 TERM_PURPLE */
	{0x00, 0x90, 0x20, 0xff}, /* 17 TERM_VIOLET */
	{0x00, 0x00, 0xa0, 0xa0}, /* 18 TERM_TEAL */
	{0x00, 0x6c, 0x6c, 0x30}, /* 19 TERM_MUD */
	{0x00, 0xff, 0xff, 0x90}, /* 20 TERM_L_YELLOW */
	{0x00, 0xff, 0x00, 0xa0}, /* 21 TERM_MAGENTA */
	{0x00, 0x20, 0xff, 0xdc}, /* 22 TERM_L_TEAL */
	{0x00, 0xb8, 0xa8, 0xff}, /* 23 TERM_L_VIOLET */
	{0x00, 0xff, 0x80, 0x80}, /* 24 TERM__PINK */
	{0x00, 0xb4, 0xb4, 0x00}, /* 25 TERM_MUSTARD */
	{0x00, 0xa0, 0xc0, 0xd0}, /* 26 TERM_BLUE_SLATE */
	{0x00, 0x00, 0xb0, 0xff}, /* 27 TERM_DEEP_L_BLUE */
};


/*
 * Standard sound names (modifiable?)
 */
char angband_sound_name[SOUND_MAX][16] =
{
	"",
	"hit",
	"miss",
	"flee",
	"drop",
	"kill",
	"level",
	"death",
	"study",
	"teleport",
	"shoot",
	"quaff",
	"zap",
	"walk",
	"tpother",
	"hitwall",
	"eat",
	"store1",
	"store2",
	"store3",
	"store4",
	"dig",
	"opendoor",
	"shutdoor",
	"tplevel"
};


/*
 * Array[VIEW_MAX] used by "update_view()"
 */
int view_n = 0;
u16b *view_g;

/*
 * Arrays[TEMP_MAX] used for various things
 */
int temp_n = 0;
u16b *temp_g;
byte *temp_y;
byte *temp_x;


/*
 * Array[DUNGEON_HGT][256] of cave grid info flags (padded)
 *
 * This array is padded to a width of 256 to allow fast access to elements
 * in the array via "grid" values (see the GRID() macros).
 */
byte (*cave_info)[256];

/*
 * Array[DUNGEON_HGT][DUNGEON_WID] of cave grid feature codes
 */
byte (*cave_feat)[DUNGEON_WID];


/*
 * Array[DUNGEON_HGT][DUNGEON_WID] of cave grid object indexes
 *
 * Note that this array yields the index of the top object in the stack of
 * objects in a given grid, using the "next_o_idx" field in that object to
 * indicate the next object in the stack, and so on, using zero to indicate
 * "nothing".  This array replicates the information contained in the object
 * list, for efficiency, providing extremely fast determination of whether
 * any object is in a grid, and relatively fast determination of which objects
 * are in a grid.
 */
s16b (*cave_o_idx)[DUNGEON_WID];

/*
 * Array[DUNGEON_HGT][DUNGEON_WID] of cave grid monster indexes
 *
 * Note that this array yields the index of the monster or player in a grid,
 * where negative numbers are used to represent the player, positive numbers
 * are used to represent a monster, and zero is used to indicate "nobody".
 * This array replicates the information contained in the monster list and
 * the player structure, but provides extremely fast determination of which,
 * if any, monster or player is in any given grid.
 */
s16b (*cave_m_idx)[DUNGEON_WID];


#ifdef MONSTER_FLOW

/*
 * Array[DUNGEON_HGT][DUNGEON_WID] of cave grid flow "cost" values
 * Used to simulate character noise.
 */
byte (*cave_cost)[DUNGEON_WID];

/*
 * Array[DUNGEON_HGT][DUNGEON_WID] of cave grid flow "when" stamps.
 * Used to store character scent trails.
 */
byte (*cave_when)[DUNGEON_WID];

/*
 * Current scent age marker.  Counts down from 250 to 0 and then loops.
 */
int scent_when = 250;


/*
 * Centerpoints of the last flow (noise) rebuild and the last flow update.
 */
int flow_center_y;
int flow_center_x;
int update_center_y;
int update_center_x;

/*
 * Flow cost at the center grid of the current update.
 */
int cost_at_center = 0;

#endif	/* MONSTER_FLOW */

/*
 * Array[MAX_O_IDX] of dungeon objects
 */
object_type *o_list;

/*
 * Array[MAX_M_IDX] of dungeon monsters
 */
monster_type *m_list;

/*
 * Array[MAX_EFFECTS] of dungeon effects
 */
effect_type *x_list;

/*
 * Array[MAX_M_IDX] of monster lore
 */
monster_lore *l_list;

/*
 * Hack -- Array[MAX_Q_IDX] of quests
 */
quest *q_list;


/*
 * Array[MAX_STORES] of stores
 */
store_type *store;

/*
 * Array[INVEN_TOTAL] of objects in the player's inventory
 */
object_type *inventory;


/*
 * The size of "alloc_kind_table" (at most MAX_K_IDX * 4)
 */
s16b alloc_kind_size;

/*
 * The array[alloc_kind_size] of entries in the "kind allocator table"
 */
alloc_entry *alloc_kind_table;

/*
 * The size of the "alloc_ego_table"
 */
s16b alloc_ego_size;

/*
 * The array[alloc_ego_size] of entries in the "ego allocator table"
 */
alloc_entry *alloc_ego_table;

/*
 * The size of "alloc_race_table" (at most MAX_R_IDX)
 */
s16b alloc_race_size;

/*
 * The array[alloc_race_size] of entries in the "race allocator table"
 */
alloc_entry *alloc_race_table;

/*
 * The total of all final monster generation probabilities
 */
u32b alloc_race_total;

/*
 * Specify attr/char pairs for visual special effects
 * Be sure to use "index & 0xFF" to avoid illegal access
 */
byte misc_to_attr[256];
char misc_to_char[256];


/*
 * Specify color for inventory item text display (by tval)
 * Be sure to use "index & 0x7F" to avoid illegal access
 */
byte tval_to_attr[128];


/*
 * Current (or recent) macro action
 */
char macro_buffer[1024];


/*
 * Keymaps for each "mode" associated with each keypress.
 */
const char * keymap_act[KEYMAP_MODES][256];



/*** Player information ***/

/*
 * Pointer to the player tables (sex, race, class, magic, chest drops)
 */
player_sex *sp_ptr;
player_race *rp_ptr;
player_class *cp_ptr;
player_magic *mp_ptr;
chest_drops *ch_ptr;

/*
 * The player other record (static)
 */
static player_other player_other_body;

/*
 * Pointer to the player other record
 */
player_other *op_ptr = &player_other_body;

/*
 * The player info record (static)
 */
static player_type player_type_body;

/*
 * Pointer to the player info record
 */
player_type *p_ptr = &player_type_body;

/*
 * The character generates both directed (extra) noise (by doing noisy
 * things) and ambiant noise (the combination of directed and innate
 * noise).  Directed noise can immediately wake up monsters in LOS.
 * Ambient noise determines how quickly monsters wake up and how often
 * they get new information on the current character position.
 *
 * Each player turn, more noise accumulates.  Every time monster
 * temporary conditions are processed, all non-innate noise is cleared.
 */
int add_wakeup_chance = 0;
u32b total_wakeup_chance = 0;

/*
 * The vault generation arrays
 */
header *v_head;
vault_type *v_info;
char *v_name;
char *v_text;

/*
 * The themed level generation arrays. -LM-
 */
header *t_head;
vault_type *t_info;
char *t_name;
char *t_text;

/*
 * The terrain feature arrays
 */
header *f_head;
feature_type *f_info;
char *f_name;
char *f_text;

/*
 * The object kind arrays
 */
header *k_head;
object_kind *k_info;
char *k_name;
char *k_text;

/*
 * The artifact arrays
 */
header *a_head;
artifact_type *a_info;
char *a_name;
char *a_text;

/*
 * The set item arrays
 */
header *s_head;
set_type *s_info;
char *s_name;
char *s_text;

/*
 * The ego-item arrays
 */
header *e_head;
ego_item_type *e_info;
char *e_name;
char *e_text;

/*
 * The monster race arrays
 */
header *r_head;
monster_race *r_info;
char *r_name;
char *r_text;

/*
 * The player race arrays
 */
header *rp_head;
player_race *rp_info;
char *rp_name;
char *rp_text;


/*
 * The player class arrays
 */
header *cp_head;
player_class *cp_info;
char *cp_name;
char *cp_text;


/*
 * The player magic arrays
 */
header *mp_head;
player_magic *mp_info;


/*
 * The chest drop arrays
 */
header *ch_head;
chest_drops *ch_info;


/*
 * The player history arrays
 */
header *h_head;
hist_type *h_info;
char *h_text;

/*
 * The shop owner arrays
 */
header *b_head;
owner_type *b_info;
char *b_name;

/*
 * The racial price adjustment arrays
 */
header *g_head;
byte *g_info;


/*
 * Hack -- The special Angband "System Suffix"
 * This variable is used to choose an appropriate "pref-xxx" file
 */
const char * ANGBAND_SYS = "xxx";

/*
 * Hack -- The special Angband "Graphics Suffix"
 * This variable is used to choose an appropriate "graf-xxx" file
 */
const char * ANGBAND_GRAF = "old";

/*
 * Path name: The main "lib" directory
 * This variable is not actually used anywhere in the code
 */
const char * ANGBAND_DIR;

/*
 * High score files (binary)
 * These files may be portable between platforms
 */
const char * ANGBAND_DIR_APEX;

/*
 * Bone files for player ghosts (ascii)
 * These files are portable between platforms
 */
const char * ANGBAND_DIR_BONE;

/*
 * Binary image files for the "*_info" arrays (binary)
 * These files are not portable between platforms
 */
const char * ANGBAND_DIR_DATA;

/*
 * Textual template files for the "*_info" arrays (ascii)
 * These files are portable between platforms
 */
const char * ANGBAND_DIR_EDIT;

/*
 * Script files
 * These files are portable between platforms.
 */
const char * ANGBAND_DIR_SCRIPT;

/*
 * Various extra files (ascii)
 * These files may be portable between platforms
 */
const char * ANGBAND_DIR_FILE;

/*
 * Help files (normal) for the online help (ascii)
 * These files are portable between platforms
 */
const char * ANGBAND_DIR_HELP;

/*
 * Miscellanious text files, also contains any spoilers.
 * These files are portable between platforms
 */
const char * ANGBAND_DIR_INFO;

/*
 * Savefiles for current characters (binary)
 * These files are portable between platforms
 */
const char * ANGBAND_DIR_SAVE;

/*
 * Default user "preference" files (ascii)
 * These files are rarely portable between platforms
 */
const char * ANGBAND_DIR_PREF;

/*
 * User "preference" files (ascii)
 * These files are rarely portable between platforms
 */
const char * ANGBAND_DIR_USER;

/*
 * Various extra files (binary)
 * These files are rarely portable between platforms
 */
const char * ANGBAND_DIR_XTRA;


/*
 * Total Hack -- allow all items to be listed (even empty ones)
 * This is only used by "do_cmd_inven_e()" and is cleared there.
 */
bool item_tester_full;


/*
 * Here is a "pseudo-hook" used during calls to "get_item()" and
 * "show_inven()" and "show_equip()", and the choice window routines.
 */
byte item_tester_tval;


/*
 * Here is a "hook" used during calls to "get_item()" and
 * "show_inven()" and "show_equip()", and the choice window routines.
 */
bool (*item_tester_hook)(object_type*);



/*
 * Current "comp" function for ang_sort()
 */
bool (*ang_sort_comp)(void * u, void * v, int a, int b);

/*
 * Current "swap" function for ang_sort()
 */
void (*ang_sort_swap)(void * u, void * v, int a, int b);


/*
 * Hack -- function hook to restrict "get_mon_num_prep()" function
 */
bool (*get_mon_num_hook)(int r_idx);

/*
 * Hack -- function hook to restrict "get_obj_num_prep()" function
 */
bool (*get_obj_num_hook)(int k_idx);

/*
 * The "highscore" file descriptor, if available.
 */
int highscore_fd = -1;

/*
 * Themed levels generate their own feeling mesaages. -LM-
 */
char themed_feeling[80];

/*
 * The type of object the item generator should make, if specified. -LM-
 */
byte required_tval = 0;

/* The bones file a restored player ghost should use to collect extra
 * flags, a sex, and a unique name.  This also indicates that there is
 * a ghost active.  -LM-
 */
byte bones_selector;

/*
 * The player ghost template index. -LM-
 */
int r_ghost;

/*
 * The player ghost name is stored here for quick reference by the
 * description function.  -LM-
 */
char ghost_name[80];

/*
 * The type (if any) of the player ghost's personalized string, and
 * the string itself. -LM-
 */
int ghost_string_type = 0;
char ghost_string[80];

/*
 * Variable to insure that ghosts say their special message only once.
 * This variable is deliberately not saved, so reloaded ghosts may speak
 * again. -LM-
 */
bool ghost_has_spoken = FALSE;


/*
 * Autosave-related global variables adopted from Zangband. -LM-
 */
bool is_autosave = FALSE;		/* Is the save an autosave */
bool autosave;				/* Timed autosave */
s16b autosave_freq;			/* Autosave frequency */


/*
 * Is the player partly through trees or rubble and, if so, in which
 * direction is he headed?  Monsters are handled more simply:  They have
 * a 33% or 50% chance of walking through. -LM-
 */
byte player_is_crossing;


/*
 * Two variables that limit rogue stealing and creation of traps.  The
 * third prevents Priests from using the "sea of runes" trick.
 * Cleared when a level is created. -LM-
 */
byte number_of_thefts_on_level;
byte num_trap_on_level;
byte num_glyph_on_level;


/* XXX Mega-Hack - See main-win.c */
bool angband_keymap_flag = TRUE;
