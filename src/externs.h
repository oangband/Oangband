/* File: externs.h */

/* Variable and function definitions.
 *
 * Copyright (c) 1997 Ben Harrison
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.
 */


/*
 * Note that some files have their own header files
 * (z-virt.h, z-util.h, z-form.h, term.h, random.h)
 */


/*
 * Automatically generated "variable" declarations
 */

/* tables.c */
extern s16b ddd[9];
extern s16b ddx[10];
extern s16b ddy[10];
extern s16b ddx_ddd[9];
extern s16b ddy_ddd[9];
extern char hexsym[16];
extern bool legal_class[MAX_P_IDX][MAX_CLASS];
extern byte adj_mag_study[];
extern byte adj_mag_mana[];
extern byte adj_mag_fail[];
extern byte adj_mag_stat[];
extern byte adj_chr_gold[];
extern byte adj_int_dev[];
extern byte adj_wis_sav[];
extern byte adj_dex_dis[];
extern byte adj_int_dis[];
extern byte adj_dex_ta[];
extern byte adj_str_td[];
extern byte adj_dex_th[];
extern byte adj_str_th[];
extern byte adj_str_wgt[];
extern byte adj_str_hold[];
extern byte adj_str_dig[];
extern byte adj_str_blow[];
extern byte adj_dex_shots[];
extern byte adj_dex_blow[];
extern byte adj_dex_safe[];
extern byte adj_con_fix[];
extern byte adj_con_mhp[];
extern byte adj_dex_evas[];
extern byte blows_table[12][12];
extern owner_type owners[MAX_STORES][MAX_B_IDX];
extern byte extract_energy[200];
extern int extract_resistance[60];
extern s32b player_exp[PY_MAX_LEVEL];
extern player_sex sex_info[MAX_SEXES];
extern player_magic magic_info[MAX_CLASS];
extern const char * spell_names[287];
extern byte deadliness_conversion[151];
extern int chest_traps[100];
extern const char * color_names[16];
extern int new_group_index[];
extern grouper group_item[];
extern const char * stat_names[A_MAX];
extern const char * stat_names_reduced[A_MAX];
extern const char * window_flag_desc[32];
extern const char * option_text[OPT_MAX];
extern const char * option_desc[OPT_MAX];
extern bool option_norm[OPT_MAX];
extern byte option_page[OPT_PAGE_MAX][OPT_PAGE_PER];
extern druid_blows d_blow[NUM_D_BLOWS];
extern const char * feel_text[FEEL_MAX];
extern byte mana_cost_RF4[32];
extern byte mana_cost_RF5[32];
extern byte mana_cost_RF6[32];
extern byte mana_cost_RF7[32];
extern byte spell_desire_RF4[32][8];
extern byte spell_desire_RF5[32][8];
extern byte spell_desire_RF6[32][8];
extern byte spell_desire_RF7[32][8];
extern byte spell_range_RF4[32];
extern byte spell_range_RF5[32];
extern byte spell_range_RF6[32];
extern byte spell_range_RF7[32];
extern const char * specialty_names[TOTAL_SPECIALTIES];

/* variable.c */
extern const char * copyright[5];
extern byte version_major;
extern byte version_minor;
extern byte version_patch;
extern byte version_extra;
extern byte o_version_major;
extern byte o_version_minor;
extern byte o_version_patch;
extern byte sf_major;
extern byte sf_minor;
extern byte sf_patch;
extern byte sf_extra;
extern byte o_sf_major;
extern byte o_sf_minor;
extern byte o_sf_patch;
extern byte o_sf_extra;
extern u32b sf_xtra;
extern u32b sf_when;
extern u16b sf_lives;
extern u16b sf_saves;
extern bool arg_fiddle;
extern bool arg_wizard;
extern bool arg_sound;
extern bool arg_graphics;
extern bool arg_monochrome;
extern bool arg_force_original;
extern bool arg_force_roguelike;
extern bool character_generated;
extern bool character_dungeon;
extern bool character_loaded;
extern bool character_saved;
extern bool character_existed;
extern s16b character_icky;
extern s16b character_xtra;
extern u32b seed_flavor;
extern u32b seed_town;
extern s16b min_hgt;
extern s16b max_hgt;
extern s16b min_wid;
extern s16b max_wid;
extern s16b num_repro;
extern s16b object_level;
extern s16b monster_level;
extern char summon_kin_type;
extern s32b turn;
extern s32b old_turn;
extern bool use_sound;
extern bool use_graphics;
extern bool use_transparency;
extern int image_count;
extern s16b signal_count;
extern bool msg_flag;
extern bool inkey_base;
extern bool inkey_xtra;
extern bool inkey_scan;
extern bool inkey_flag;
extern s16b coin_type;
extern bool opening_chest;
extern bool shimmer_monsters;
extern bool shimmer_objects;
extern bool repair_mflag_show;
extern bool repair_mflag_mark;
extern s16b o_max;
extern s16b o_cnt;
extern s16b m_max;
extern s16b m_cnt;
extern s16b screen_x;
extern s16b screen_y;
extern s16b SCREEN_HGT;
extern s16b SCREEN_WID;
extern s16b feeling;
extern s16b rating;
extern bool empty_level;
extern bool good_item_flag;
extern bool closing_flag;
extern bool fake_monochrome;
extern s16b max_panel_rows, max_panel_cols;
extern s16b panel_row_min, panel_row_max;
extern s16b panel_col_min, panel_col_max;
extern s16b panel_col_prt, panel_row_prt;
extern bool panel_extra_rows;
extern byte *mp_a;
extern char *mp_c;
#ifdef USE_TRANSPARENCY
extern byte *mp_ta;
extern char *mp_tc;
#endif /* USE_TRANSPARENCY */
extern int player_euid;
extern char savefile[1024];
extern s16b macro__num;
extern const char * *macro__pat;
extern const char * *macro__act;
extern s16b quark__num;
extern const char * *quark__str;
extern u16b message__next;
extern u16b message__last;
extern u16b message__head;
extern u16b message__tail;
extern u16b *message__ptr;
extern char *message__buf;
extern u16b *message__type;
extern byte message__color[MSG_MAX];
extern u16b *message__type;
extern byte message__color[MSG_MAX];
extern term *angband_term[TERM_WIN_MAX];
extern char angband_term_name[TERM_WIN_MAX][16];
extern byte angband_color_table[256][4];
extern char angband_sound_name[SOUND_MAX][16];
extern int view_n;
extern u16b *view_g;
extern int temp_n;
extern u16b *temp_g;
extern byte *temp_y;
extern byte *temp_x;
extern byte (*cave_info)[256];
extern byte (*cave_feat)[DUNGEON_WID];
extern s16b (*cave_o_idx)[DUNGEON_WID];
extern s16b (*cave_m_idx)[DUNGEON_WID];

#ifdef MONSTER_FLOW

extern byte (*cave_cost)[DUNGEON_WID];
extern byte (*cave_when)[DUNGEON_WID];
extern int scent_when;
extern int flow_center_y;
extern int flow_center_x;
extern int update_center_y;
extern int update_center_x;
extern int cost_at_center;

#endif

extern object_type *o_list;
extern monster_type *m_list;
extern monster_lore *l_list;
extern effect_type *x_list;
extern quest *q_list;
extern store_type *store;
extern object_type *inventory;
extern object_type *quiver;
extern s16b alloc_kind_size;
extern alloc_entry *alloc_kind_table;
extern s16b alloc_ego_size;
extern alloc_entry *alloc_ego_table;
extern s16b alloc_race_size;
extern alloc_entry *alloc_race_table;
extern u32b alloc_race_total;
extern byte misc_to_attr[256];
extern char misc_to_char[256];
extern byte tval_to_attr[128];
extern char macro_buffer[1024];
extern const char * keymap_act[KEYMAP_MODES][256];
extern player_sex *sp_ptr;
extern player_race *rp_ptr;
extern player_class *cp_ptr;
extern player_magic *mp_ptr;
extern chest_drops *ch_ptr;
extern player_other *op_ptr;
extern player_type *p_ptr;
extern int add_wakeup_chance;
extern u32b total_wakeup_chance;
extern header *v_head;
extern vault_type *v_info;
extern char *v_name;
extern char *v_text;
extern header *t_head;
extern vault_type *t_info;
extern char *t_name;
extern char *t_text;
extern header *f_head;
extern feature_type *f_info;
extern char *f_name;
extern char *f_text;
extern header *k_head;
extern object_kind *k_info;
extern char *k_name;
extern char *k_text;
extern header *a_head;
extern artifact_type *a_info;
extern char *a_name;
extern char *a_text;
extern header *s_head;
extern set_type *s_info;
extern char *s_name;
extern char *s_text;
extern header *e_head;
extern ego_item_type *e_info;
extern char *e_name;
extern char *e_text;
extern header *r_head;
extern monster_race *r_info;
extern char *r_name;
extern char *r_text;
extern header *h_head;
extern hist_type *h_info;
extern char *h_text;
extern header *rp_head;
extern player_race *rp_info;
extern char *rp_name;
extern char *rp_text;
extern header *cp_head;
extern player_class *cp_info;
extern char *cp_name;
extern char *cp_text;
extern header *mp_head;
extern player_magic *mp_info;
extern header *ch_head;
extern chest_drops *ch_info;
extern header *b_head;
extern owner_type *b_info;
extern char *b_name;
extern header *g_head;
extern byte *g_info;
extern const char * ANGBAND_SYS;
extern const char * ANGBAND_GRAF;
extern const char * ANGBAND_DIR;
extern const char * ANGBAND_DIR_APEX;
extern const char * ANGBAND_DIR_BONE;
extern const char * ANGBAND_DIR_DATA;
extern const char * ANGBAND_DIR_EDIT;
extern const char * ANGBAND_DIR_SCRIPT;
extern const char * ANGBAND_DIR_FILE;
extern const char * ANGBAND_DIR_HELP;
extern const char * ANGBAND_DIR_INFO;
extern const char * ANGBAND_DIR_SAVE;
extern const char * ANGBAND_DIR_PREF;
extern const char * ANGBAND_DIR_USER;
extern const char * ANGBAND_DIR_XTRA;
extern bool item_tester_full;
extern byte item_tester_tval;
extern bool (*item_tester_hook)(object_type*);
extern bool (*ang_sort_comp)(void * u, void * v, int a, int b);
extern void (*ang_sort_swap)(void * u, void * v, int a, int b);
extern bool (*get_mon_num_hook)(int r_idx);
extern bool (*get_obj_num_hook)(int k_idx);
extern int highscore_fd;
extern char themed_feeling[80];
extern byte required_tval;
extern byte bones_selector;
extern int r_ghost;
extern char ghost_name[80];
extern int ghost_string_type;
extern char ghost_string[80];
extern bool ghost_has_spoken;
extern bool is_autosave;
extern bool autosave;
extern s16b autosave_freq;
extern byte player_is_crossing;
extern byte number_of_thefts_on_level;
extern byte num_trap_on_level;
extern byte num_glyph_on_level;
extern int *artifact_normal, *artifact_special;
extern int artifact_normal_cnt, artifact_special_cnt;
extern bool angband_keymap_flag;

/*
 * Automatically generated "function declarations"
 */

/* attack.c */
extern void py_attack(int y, int x);
extern bool do_cmd_fire(int mode);
extern bool do_cmd_throw(int mode);

/* birth.c */
extern void player_clear(bool full);
extern void player_birth(void);

/* cave.c */
extern int distance(int y1, int x1, int y2, int x2);
extern bool los(int y1, int x1, int y2, int x2);
extern bool no_lite(void);
extern bool cave_valid_bold(int y, int x);
#ifdef USE_TRANSPARENCY
extern void map_info(int y, int x, byte *ap, char *cp, byte *tap, char *tcp);
#else /* USE_TRANSPARENCY */
extern void map_info(int y, int x, byte *ap, char *cp);
#endif /* USE_TRANSPARENCY */
extern void move_cursor_relative(int y, int x);
extern void print_rel(char c, byte a, int y, int x);
extern void note_spot(int y, int x);
extern void lite_spot(int y, int x);
extern void prt_map(void);
extern void display_map(int *cy, int *cx);
extern void do_cmd_view_map(void);
extern errr vinfo_init(void);
extern void forget_view(void);
extern void update_view(void);
extern void update_noise(void);
extern void update_smell(void);
extern void map_area(int y, int x, bool extended);
extern void wiz_lite(bool wizard);
extern void wiz_dark(void);
extern void town_illuminate(bool daytime);
extern void cave_set_feat(int y, int x, int feat);
extern int project_path(u16b *gp, int range, \
                         int y1, int x1, int y2, int x2, int flg);
extern byte projectable(int y1, int x1, int y2, int x2, int flg);
extern void scatter(int *yp, int *xp, int y, int x, int d, int m);
extern void health_track(int m_idx);
extern void monster_race_track(int r_idx);
extern void object_kind_track(int k_idx);
extern void disturb(int seriousness, int unused_flag);
extern bool is_quest(int level);

/* cmd1.c */
extern void search(void);
extern byte py_pickup(int pickup);
extern void hit_trap(int y, int x);
extern void move_player(int dir, int do_pickup);
extern void run_step(int dir);

/* cmd2.c */
extern void do_cmd_go_up(void);
extern void do_cmd_go_down(void);
extern void do_cmd_search(void);
extern void do_cmd_toggle_search(void);
extern void do_cmd_open(void);
extern void do_cmd_close(void);
extern void do_cmd_tunnel(void);
extern void do_cmd_disarm(void);
extern void do_cmd_bash(void);
extern void do_cmd_alter(void);
extern bool do_cmd_spike_test(int y, int x);
extern void do_cmd_spike(void);
extern void do_cmd_walk(void);
extern void do_cmd_jump(void);
extern void do_cmd_run(void);
extern void do_cmd_hold(void);
extern void do_cmd_pickup(void);
extern void do_cmd_rest(void);
extern bool easy_open_door(int y, int x);

/* cmd3.c */
extern void do_cmd_floor(void);
extern void do_cmd_inven(void);
extern void do_cmd_equip(void);
extern void do_cmd_wield(void);
extern void do_cmd_takeoff(void);
extern void do_cmd_drop(void);
extern void do_cmd_destroy(void);
extern void do_cmd_observe(object_type *o_ptr, bool in_store);
extern void do_cmd_uninscribe(void);
extern void do_cmd_inscribe(void);
extern void do_cmd_refill(void);
extern void do_cmd_target(void);
extern void do_cmd_look(void);
extern void do_cmd_locate(void);
extern void do_cmd_query_symbol(void);
extern bool ang_sort_comp_hook(void * u, void * v, int a, int b);
extern void ang_sort_swap_hook(void * u, void * v, int a, int b);
extern void py_steal(int y, int x);
extern void py_set_trap(int y, int x);
extern void py_modify_trap(int y, int x);

/* cmd4.c */
extern void do_cmd_redraw(void);
extern void resize_map(void);
extern void redraw_window(void);
extern void do_cmd_change_name(void);
extern void do_cmd_message_one(void);
extern void do_cmd_messages(void);
extern void ghost_challenge(void);
extern void do_cmd_options(void);
extern void do_cmd_pref(void);
extern void do_cmd_macros(void);
extern void do_cmd_visuals(void);
extern void do_cmd_colors(void);
extern void do_cmd_note(void);
extern void do_cmd_version(void);
extern void do_cmd_feeling(void);
extern void do_cmd_load_screen(void);
extern void do_cmd_save_screen(void);
extern void do_cmd_knowledge(void);
extern void do_cmd_time(void);

/* cmd5.c */
extern void shapechange(s16b shape);
extern void create_athelas(void);
extern bool dimen_door(void);
extern int get_spell_level_boost(void);
extern void do_cmd_browse(void);
extern void do_cmd_cast_or_pray(void);
extern bool check_ability(int ability);
extern bool check_ability_specialty(int ability);
extern bool check_specialty_gain(int specialty);
extern void do_cmd_specialty(void);

/* cmd6.c */
extern void do_cmd_eat_food(void);
extern void do_cmd_quaff_potion(void);
extern void do_cmd_read_scroll(void);
extern bool get_attune(object_type *o_ptr);
extern void do_cmd_use_staff(void);
extern void do_cmd_aim_wand(void);
extern void do_cmd_zap_rod(void);
extern void do_cmd_activate(void);
extern void do_cmd_bear_shape(void);
extern void do_cmd_unchange(void);

/* dungeon.c */
extern void play_game(bool new_game);

/* files.c */
extern s16b tokenize(char *buf, s16b num, char **tokens);
extern errr process_pref_file_command(char *buf);
extern errr process_pref_file(const char * name);
extern void display_player(int mode);
extern errr file_character(const char * name, bool full);
extern bool show_file(const char * name, const char * what, int line, int mode);
extern void do_cmd_help(void);
extern void process_player_name(bool sf);
extern void get_name(void);
extern void do_cmd_suicide(void);
extern void do_cmd_save_game(bool autosave);
extern long total_points(void);
extern void center_string(char *buf, const char * str);
extern void display_scores(int from, int to);
extern errr predict_score(void);
extern void close_game(void);
extern void exit_game_panic(void);
extern errr get_rnd_line(char *file_name, char *output);
extern void signals_ignore_tstp(void);
extern void signals_handle_tstp(void);
extern void signals_init(void);
extern void display_scores_aux(int from, int to, int note, high_score *score);
extern void player_flags(u32b *f1, u32b *f2, u32b *f3, bool shape);

/* generate.c */
extern void destroy_level(bool new_level);
extern void map_panel_size(void);
extern void generate_cave(void);

/* info.c */
extern const char * obj_class_info[101];
extern const char * obj_special_info[6][50];
extern const char * spell_tips[];
extern const char * specialty_tips[TOTAL_SPECIALTIES];
extern void object_info(char buf[2048], object_type *o_ptr, bool in_store);
extern const char * item_activation(object_type *o_ptr);
extern void identify_fully_aux(object_type *o_ptr);
extern void self_knowledge(void);
extern s16b spell_chance(int spell);
extern bool spell_okay(int spell);
extern void spell_info(char *p, int spell);
extern void print_spells(int tval, int sval, int y, int x);
extern void do_cmd_view_abilities(void);

/* init1.c */
extern int color_char_to_attr(char c);
extern errr init_v_info_txt(FILE *fp, char *buf);
extern errr init_t_info_txt(FILE *fp, char *buf, byte chosen_level);
extern errr init_f_info_txt(FILE *fp, char *buf);
extern errr init_rp_info_txt(FILE *fp, char *buf);
extern errr init_cp_info_txt(FILE *fp, char *buf);
extern errr init_mp_info_txt(FILE *fp, char *buf);
extern errr init_ch_info_txt(FILE *fp, char *buf);
extern errr init_k_info_txt(FILE *fp, char *buf);
extern errr init_a_info_txt(FILE *fp, char *buf);
extern errr init_s_info_txt(FILE *fp, char *buf);
extern errr init_e_info_txt(FILE *fp, char *buf);
extern errr init_r_info_txt(FILE *fp, char *buf);
extern errr init_b_info_txt(FILE *fp, char *buf);
extern errr init_g_info_txt(FILE *fp, char *buf);
extern errr init_h_info_txt(FILE *fp, char *buf);

/* init2.c */
extern void init_artifacts(void);
extern errr init_t_info(byte chosen_level);
extern void kill_t_info(void);
extern void init_file_paths(char *path);
extern void init_angband(void);

/* load1.c */
extern void save_savefile_names();
extern void savefile_load(bool force_menu);

/* load2.c */
extern errr rd_savefile_new(void);
extern errr rd_version_info(void);

/* monattk.c */
extern bool make_attack_normal(monster_type *m_ptr, int y, int x);
extern bool make_attack_ranged(monster_type *m_ptr, int attack);

/* monmove.c */
extern int get_scent(int y, int x);
extern bool cave_exist_mon(monster_race *r_ptr, int y, int x, bool occupied_ok);
extern void process_monsters(byte minimum_energy);
extern void reset_monsters(void);

/* monster1.c */
extern void screen_roff(int r_idx);
extern void display_roff(int r_idx);
extern bool prepare_ghost(int r_idx, monster_type *m_ptr, bool from_savefile);

/* monster2.c */
extern void delete_monster_idx(int i);
extern void delete_monster(int y, int x);
extern void compact_monsters(int size);
extern void wipe_m_list(void);
extern s16b m_pop(void);
extern errr get_mon_num_prep(void);
extern s16b get_mon_num(int level);
extern s16b get_mon_num_quick(int level);
extern void display_monlist(void);
extern void monster_desc(char *desc, monster_type *m_ptr, int mode);
extern void lore_do_probe(int m_idx);
extern void lore_treasure(int m_idx, int num_item, int num_gold);
extern void update_mon(int m_idx, bool full);
extern void update_monsters(bool full);
extern s16b monster_carry(int m_idx, object_type *j_ptr);
extern void monster_swap(int y1, int x1, int y2, int x2);
extern s16b player_place(int y, int x);
extern s16b monster_place(int y, int x, monster_type *n_ptr);
extern bool place_monster_aux(int y, int x, int r_idx, bool slp, bool grp);
extern bool place_monster(int y, int x, bool slp, bool grp, bool quick);
extern bool alloc_monster(int dis, bool slp, bool quick);
extern int summon_specific(int y1, int x1, bool scattered, int lev, int type, int num);
extern bool multiply_monster(int m_idx);
extern void message_pain(int m_idx, int dam);
extern void update_smart_learn(int m_idx, int what);

/* object1.c */
extern void flavor_init(void);
byte proc_list_color_hack(object_type *o_ptr);
extern void reset_visuals(bool prefs);
extern void object_flags(object_type *o_ptr, u32b *f1, u32b *f2, u32b *f3);
extern void object_flags_known(object_type *o_ptr, u32b *f1, u32b *f2, u32b *f3);
extern void object_desc(char *buf, object_type *o_ptr, int pref, int mode);
extern void object_desc_spoil(char *buf, object_type *o_ptr, int pref, int mode);
extern void object_desc_store(char *buf, object_type *o_ptr, int pref, int mode);
extern void strip_name(char *buf, int k_idx);
extern char index_to_label(int i);
extern s16b label_to_inven(int c);
extern s16b label_to_equip(int c);
extern s16b wield_slot(object_type *o_ptr);
extern const char * mention_use(int i);
extern const char * describe_use(int i);
extern bool item_tester_okay(object_type *o_ptr);
extern void display_inven(void);
extern void display_equip(void);
extern void show_inven(void);
extern void show_equip(void);
extern void toggle_inven_equip(void);
extern bool get_item(int *cp, const char * pmt, const char * str, int mode);
extern bool scan_floor(int *items, int *item_num, int y, int x, int mode);
extern void show_floor(const int *floor_list, int floor_num, bool gold);
extern bool get_item_floor(int *cp, const char * pmt, const char * str, int mode);
extern const char * object_adj(int tval, int sval);
extern bool destroy_squelched_items(void);
extern bool check_set(byte s_idx);
extern void apply_set(int s_idx);
extern void remove_set(int s_idx);
// extern void object_info_screen(const object_type *o_ptr);

/* object2.c */
extern void excise_object_idx(int o_idx);
extern void delete_object_idx(int o_idx);
extern void delete_object(int y, int x);
extern void compact_objects(int size);
extern void wipe_o_list(void);
extern s16b o_pop(void);
extern errr get_obj_num_prep(void);
extern s16b get_obj_num(int level);
extern void object_known(object_type *o_ptr);
extern void object_aware(object_type *o_ptr);
extern void object_tried(object_type *o_ptr);
extern s32b object_value(object_type *o_ptr);
extern void distribute_charges(object_type *o_ptr, object_type *q_ptr, int amt);
extern void reduce_charges(object_type *o_ptr, int amt);
extern bool object_similar(object_type *o_ptr, object_type *j_ptr);
extern void object_absorb(object_type *o_ptr, object_type *j_ptr);
extern s16b lookup_kind(int tval, int sval);
extern void object_wipe(object_type *o_ptr);
extern void object_copy(object_type *o_ptr, object_type *j_ptr);
extern void object_prep(object_type *o_ptr, int k_idx);
extern void apply_magic(object_type *o_ptr, int lev, bool okay, bool good, bool great);
extern bool make_object(object_type *j_ptr, bool good, bool great, bool exact_kind);
extern bool make_gold(object_type *j_ptr);
extern s16b floor_carry(int y, int x, object_type *j_ptr);
extern void drop_near(object_type *j_ptr, int chance, int y, int x);
extern void acquirement(int y1, int x1, int num, bool great);
extern void place_object(int y, int x, bool good, bool great, bool exact_kind);
extern void place_gold(int y, int x);
extern void pick_trap(int y, int x);
extern void place_trap(int y, int x);
extern void inven_item_charges(int item);
extern void inven_item_describe(int item);
extern void inven_item_increase(int item, int num);
extern void inven_item_optimize(int item);
extern void floor_item_charges(int item);
extern void floor_item_describe(int item);
extern void floor_item_increase(int item, int num);
extern void floor_item_optimize(int item);
extern bool inven_carry_okay(object_type *o_ptr);
extern s16b inven_carry(object_type *o_ptr);
extern s16b inven_takeoff(int item, int amt);
extern void inven_drop(int item, int amt);
extern void combine_pack(void);
extern void reorder_pack(void);
extern int quiver_count(void);
extern void find_quiver_size(void);
extern int process_quiver(int num_new, object_type *o_ptr);
extern void display_koff(int k_idx);
extern void place_secret_door(int y, int x);
extern void place_unlocked_door(int y, int x);
extern void place_closed_door(int y, int x);
extern void place_random_door(int y, int x);

/* randart.c */
extern void initialize_random_artifacts(void);

/* save.c */
extern bool save_player(void);
extern bool load_player(bool silent);
extern void savefile_load(bool force_menu);

/* spells1.c */
extern bool check_save(int roll);
extern s16b poly_r_idx(int r_idx);
extern void teleport_away(int m_idx, int dis);
extern void teleport_player(int dis, bool safe);
extern void teleport_player_to(int ny, int nx, bool friendly);
extern void teleport_player_level(bool friendly);
extern void add_heighten_power(int value);
extern void add_speed_boost(int value);
extern int resist_damage(int dam, byte resist, byte rand_factor);
extern void take_hit(int dam, const char * kb_str);
extern void acid_dam(int dam, const char * kb_str);
extern void elec_dam(int dam, const char * kb_str);
extern void fire_dam(int dam, const char * kb_str);
extern void cold_dam(int dam, const char * kb_str);
extern void pois_dam(int dam, const char * kb_str);
extern bool pois_hit(int pois_inc);
extern bool inc_stat(int stat);
extern bool dec_stat(int stat, int amount, int permanent);
extern bool res_stat(int stat);
extern int remove_player_mana(int power);
extern int apply_dispel(int power);
extern bool apply_disenchant(int mode);
extern bool project(int who, int rad, int y, int x, int dam, int typ,
	int flg, int degrees_of_arc, byte diameter_of_source);
extern void teleport_towards(int oy, int ox, int ny, int nx);

/* spells2.c */
extern bool hp_player(int num);
extern void magic_spiking(void);
extern bool warding_glyph(void);
extern bool do_dec_stat(int stat);
extern bool do_res_stat(int stat);
extern bool do_inc_stat(int stat);
extern void identify_pack(void);
extern bool remove_curse(void);
extern bool remove_all_curse(void);
extern bool restore_level(void);
extern bool lose_all_info(void);
extern bool detect_traps(int range, bool show);
extern bool detect_doors(int range, bool show);
extern bool detect_stairs(int range, bool show);
extern bool detect_treasure(int range, bool show);
extern bool detect_objects_gold(int range, bool show);
extern bool detect_objects_normal(int range, bool show);
extern bool detect_objects_magic(int range, bool show);
extern bool detect_monsters_normal(int range, bool show);
extern bool detect_monsters_invis(int range, bool show);
extern bool detect_monsters_evil(int range, bool show);
extern bool detect_monsters_living(int range, bool show);
extern bool detect_all(int range, bool show);
extern void stair_creation(void);
extern bool enchant(object_type *o_ptr, int n, int eflag);
extern bool enchant_spell(int num_hit, int num_dam, int num_ac);
extern bool brand_missile(int ammo_type, int brand_type);
extern void set_ele_attack(u32b attack_type, int duration);
extern bool curse_armor(void);
extern bool curse_weapon(void);
extern bool ident_spell(void);
extern bool identify_fully(void);
extern bool recharge(int num);
extern bool tap_magical_energy(void);
extern void do_starlight(int burst_number, int dam, bool strong);
extern bool listen_to_natural_creatures(void);
extern void unmake(int dir);
extern void ele_air_smite(void);
extern bool project_los_not_player(int y1, int x1, int dam, int typ);
extern bool speed_monsters(void);
extern bool slow_monsters(int dam);
extern bool sleep_monsters(int dam);
extern bool fear_monsters(int dam);
extern bool confu_monsters(int dam);
extern bool banish_evil(int dist);
extern bool turn_undead(int dam);
extern bool turn_evil(int dam);
extern bool dispel_undead(int dam);
extern bool dispel_evil(int dam);
extern bool dispel_demons(int dam);
extern bool dispel_not_evil(int dam);
extern bool dispel_monsters(int dam);
extern bool dispel_small_monsters(int dam);
extern bool dispel_living(int dam);
extern bool dispel_light_hating(int dam);
extern bool hold_undead(void);
extern void aggravate_monsters(int who, bool entire_level);
extern bool genocide(void);
extern bool mass_genocide(void);
extern bool probing(void);
extern void destroy_area(int y1, int x1, int r, bool full);
extern void earthquake(int cy, int cx, int r, bool volcano);
extern void lite_room(int y1, int x1);
extern void unlite_room(int y1, int x1);
extern bool lite_area(int dam, int rad);
extern bool unlite_area(int dam, int rad);
extern bool fire_ball(int typ, int dir, int dam, int rad, bool jump);
extern bool fire_sphere(int typ, int dir, int dam, int rad,
	byte diameter_of_source);
extern bool fire_cloud(int typ, int dir, int dam, int rad);
extern bool fire_meteor(int who, int typ, int y, int x, int dam, int rad,
	bool hurt_player);
extern bool fire_arc(int typ, int dir, int dam, int rad, int degrees_of_arc);
extern bool fire_bolt(int typ, int dir, int dam);
extern bool fire_beam(int typ, int dir, int dam);
extern bool fire_bolt_or_beam(int prob, int typ, int dir, int dam);
extern bool lite_line(int dir);
extern bool drain_life(int dir, int dam);
extern bool wall_to_mud(int dir);
extern bool destroy_door(int dir);
extern bool disarm_trap(int dir);
extern bool heal_monster(int dir);
extern bool speed_monster(int dir);
extern bool slow_monster(int dir, int dam);
extern bool sleep_monster(int dir, int dam);
extern bool confuse_monster(int dir, int dam);
extern bool poly_monster(int dir);
extern bool clone_monster(int dir);
extern bool fear_monster(int dir, int dam);
extern bool dispel_an_undead(int dir, int dam);
extern bool dispel_a_demon(int dir, int dam);
extern bool dispel_a_dragon(int dir, int dam);
extern bool teleport_monster(int dir, int dist);
extern bool door_creation(void);
extern bool trap_creation(void);
extern bool destroy_doors_touch(void);
extern bool sleep_monsters_touch(int dam);

/* store.c */
extern void display_home_inventory_remote(void);
extern void do_cmd_store(void);
extern void store_shuffle(int which);
extern void store_maint(int which);
extern void store_init(int which);

/* util.c */
extern errr path_parse(char *buf, int max, const char * file);
extern errr path_temp(char *buf, int max);
extern errr path_build(char *buf, int max, const char * path, const char * file);
extern FILE *my_fopen(const char * file, const char * mode);
extern FILE *my_fopen_temp(char *buf, size_t max);
extern errr my_fclose(FILE *fff);
extern errr my_fgets(FILE *fff, char *buf, size_t n);
extern errr my_fputs(FILE *fff, const char * buf, size_t n);
extern errr fd_kill(const char * file);
extern errr fd_move(const char * file, const char * what);
extern errr fd_copy(const char * file, const char * what);
extern int fd_make(const char * file, int mode);
extern int fd_open(const char * file, int flags);
extern errr fd_lock(int fd, int what);
extern errr fd_seek(int fd, long n);
extern errr fd_read(int fd, char *buf, size_t n);
extern errr fd_write(int fd, const char * buf, size_t n);
extern errr fd_close(int fd);
extern errr check_modification_date(int fd, const char * template_file);
extern void text_to_ascii(char *buf, const char * str);
extern void ascii_to_text(char *buf, const char * str);
extern int macro_find_exact(const char * pat);
extern errr macro_add(char *pat, char *act);
extern errr macro_init(void);
extern void flush(void);
extern char inkey(void);
extern void bell(const char * reason);
extern void sound(int val);
extern s16b quark_add(const char * str);
extern const char * quark_str(s16b i);
extern errr quark_init(void);
extern s16b message_num(void);
extern const char * message_str(s16b age);
extern void message_add(const char * str, u16b type);
extern errr message_init(void);
extern void move_cursor(int row, int col);
extern void msg_print(const char * msg);
extern void msg_format(const char * fmt, ...);
extern s16b message_num(void);
extern const char * message_str(s16b age);
extern u16b message_type(s16b age);
extern byte message_color(s16b age);
extern void message(u16b message_type, s16b extra, const char * message);
extern void message_format(u16b message_type, s16b extra, const char * fmt, ...);
extern void screen_save(void);
extern void screen_load(void);
extern void c_put_str(byte attr, const char * str, int row, int col);
extern void put_str(const char * str, int row, int col);
extern void put_str_center(const char * str, int row);
extern void c_prt(byte attr, const char * str, int row, int col);
extern void prt(const char * str, int row, int col);
extern void prt_center(const char * str, int row);
extern void c_roff(byte a, const char * str, byte l_margin, byte r_margin);
extern void roff(const char * str, byte l_margin, byte r_margin);
extern void clear_from(int row);
extern bool askfor_aux(char *buf, int len);
extern bool get_string(const char * prompt, char *buf, int len);
extern s16b get_quantity(const char * prompt, int max);
extern bool get_check(const char * prompt);
extern bool get_com(const char * prompt, char *command);
extern void pause_line(int row);
extern void request_command(bool shopping);
extern unsigned int damroll(unsigned int num, unsigned int sides);
extern unsigned int maxroll(unsigned int num, unsigned int sides);
extern bool is_a_vowel(int ch);

extern void repeat_push(int what);
extern bool repeat_pull(int *what);
extern void repeat_clear(void);
extern void repeat_check(void);
extern int make_metric(int wgt);
extern byte get_angle_to_grid[41][41];

#ifdef SUPPORT_GAMMA
extern byte gamma_table[256];
extern void build_gamma_table(int gamma);
#endif /* SUPPORT_GAMMA */

#ifdef PRIVATE_USER_PATH
extern void create_user_dirs(void);
#endif /* PRIVATE_USER_PATH */

/* xtra1.c */
extern void cnv_stat(int val, char *out_val);
extern s16b modify_stat_value(int value, int amount);
extern void notice_stuff(void);
extern void update_stuff(void);
extern void redraw_stuff(void);
extern void window_stuff(void);
extern void handle_stuff(void);
extern int add_special_missile_skill(byte pclass, s16b weight, object_type *o_ptr);
extern int add_special_melee_skill(byte pclass, s16b weight, object_type *o_ptr);

/* xtra2.c */
extern bool set_blind(int v);
extern bool set_confused(int v);
extern bool set_poisoned(int v);
extern bool set_afraid(int v);
extern bool set_paralyzed(int v);
extern bool set_image(int v);
extern bool set_fast(int v);
extern bool set_slow(int v);
extern bool set_shield(int v);
extern bool set_blessed(int v);
extern bool set_hero(int v);
extern bool set_shero(int v);
extern bool set_protevil(int v);
extern bool set_extra_defences(int v);
extern bool set_tim_invis(int v);
extern bool set_tim_esp(int v);
extern bool set_superstealth(int v);
extern bool set_tim_infra(int v);
extern bool set_oppose_acid(int v);
extern bool set_oppose_elec(int v);
extern bool set_oppose_fire(int v);
extern bool set_oppose_cold(int v);
extern bool set_oppose_pois(int v);
extern bool set_stun(int v);
extern bool set_cut(int v);
extern bool set_food(int v);
extern bool set_recall(int v);
extern void word_recall(int v);
extern void check_experience(void);
extern void gain_exp(s32b amount);
extern void lose_exp(s32b amount);
extern void monster_death(int m_idx);
extern bool mon_take_hit(int m_idx, int dam, bool *fear, const char * note);
extern void verify_panel(void);
extern const char * look_mon_desc(int m_idx);
extern void ang_sort_aux(void * u, void * v, int p, int q);
extern void ang_sort(void * u, void * v, int n);
extern int target_dir(char ch);
extern bool target_able(int m_idx);
extern bool target_okay(void);
extern void target_set_monster(int m_idx);
extern void target_set_location(int y, int x);
extern bool target_set_interactive(int mode);
extern bool get_aim_dir(int *dp);
extern bool get_rep_dir(int *dp);
extern bool confuse_dir(int *dp);
extern bool tgt_pt (int *x, int *y);
extern void panel_center(void);
extern bool change_panel(int dy, int dx);
extern void verify_panel(void);

/* squelch.c */
extern byte squelch_level[24];
extern void do_cmd_squelch(void);
extern int squelch_itemp(object_type *, byte, int);
extern void do_squelch_pile(int y, int x);
extern void do_squelch_item(int item, object_type *);

/*
 * Hack -- conditional (or "bizarre") externs
 */

#ifdef SET_UID
# ifndef HAVE_USLEEP
/* util.c */
extern int usleep(unsigned long usecs);
# endif
extern void user_name(char *buf, int id);
#endif

#ifdef MACINTOSH
/* main-mac.c */
/* extern void main(void); */
#endif

#ifdef WINDOWS
/* main-win.c */
/* extern int FAR PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, ...); */
#endif


#if defined(MAC_MPW) || defined(MACH_O_CARBON)
/* main-mac.c, or its derivatives */
extern u32b _fcreator;
extern u32b _ftype;
# if defined(MAC_MPW) && defined(CARBON)
extern void convert_pathname(char *path);
# endif
# if defined(MACH_O_CARBON)
extern void fsetfileinfo(const char * path, u32b fcreator, u32b ftype);
# endif
#endif



/* main.c */
/* extern int main(int argc, char *argv[]); */


