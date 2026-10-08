# API (page 18 of 19)
Previous: [API_p17.md](API_p17.md)

## progs/vedit/vedit.c
Depends on: `headers/leakcheck.h`, `kernel/string.c`, `progs/nuklear/nuklear_minios.h`, `progs/nuklear/nuklear_theme.h`
- `vedit_getc_raw` (function) `progs/vedit/vedit.c:38` `static long vedit_getc_raw(long blocking)` -- #include <stdio.h> #include <stdlib.h> #include <string.h> #include <stdint.h> #include <sys/stat.h> #include...
- `vedit_set_title` (function) `progs/vedit/vedit.c:47` `static long vedit_set_title(const char *t)` -- #define MINIOS_LEAKCHECK_IMPL #define MINIOS_LK_ENABLE #include "leakcheck.h" /** Platform syscalls vedit needs...
- `vedit_spawn` (function) `progs/vedit/vedit.c:56` `static long vedit_spawn(const char *path, const char *redir, int argc,
                        co...` -- : "rcx", "r11", "memory"); return ret; } /** Set the graphics window title. static long vedit_set_title(const char...
- `vedit_vga` (function) `progs/vedit/vedit.c:68` `static long vedit_vga(int on)` -- /** Run a program through SYS_SPAWN, preserving the IDE across the child. static long vedit_spawn(const char *path...
- `vedit_kbd_raw` (function) `progs/vedit/vedit.c:80` `static long vedit_kbd_raw(int on)` -- Force cooked keyboard mode: GETC_RAW (this editor's only key source) starves while raw mode diverts PS/2 bytes to...
- `vedit_time_ms` (function) `progs/vedit/vedit.c:89` `static unsigned long vedit_time_ms(void)` -- Force cooked keyboard mode: GETC_RAW (this editor's only key source) starves while raw mode diverts PS/2 bytes to...
- `vedit_clip_set` (function) `progs/vedit/vedit.c:97` `static long vedit_clip_set(const char *s, long len)` -- : "a"(MINIOS_SYS_KBD_RAW), "D"((long)on) : "rcx", "r11", "memory"); return ret; } /** Wall-clock milliseconds for...
- `vedit_clip_get` (function) `progs/vedit/vedit.c:105` `static long vedit_clip_get(char *out, long cap)`
- `vedit_c_bg` (function) `progs/vedit/vedit.c:182` `static struct nk_color vedit_c_bg(void)` -- /* ---- Decoded keys above any byte ---- #define VEDIT_KEY_UP 1000 #define VEDIT_KEY_DOWN 1001 #define...
- `vedit_c_gutter` (function) `progs/vedit/vedit.c:183` `static struct nk_color vedit_c_gutter(void)`
- `vedit_c_default` (function) `progs/vedit/vedit.c:184` `static struct nk_color vedit_c_default(void)`
- `vedit_c_keyword` (function) `progs/vedit/vedit.c:185` `static struct nk_color vedit_c_keyword(void)`
- `vedit_c_string` (function) `progs/vedit/vedit.c:186` `static struct nk_color vedit_c_string(void)`
- `vedit_c_comment` (function) `progs/vedit/vedit.c:187` `static struct nk_color vedit_c_comment(void)`
- `vedit_c_number` (function) `progs/vedit/vedit.c:188` `static struct nk_color vedit_c_number(void)`
- `vedit_c_preproc` (function) `progs/vedit/vedit.c:189` `static struct nk_color vedit_c_preproc(void)`
- `vedit_c_header` (function) `progs/vedit/vedit.c:190` `static struct nk_color vedit_c_header(void)`
- `vedit_c_headtxt` (function) `progs/vedit/vedit.c:191` `static struct nk_color vedit_c_headtxt(void)`
- `vedit_c_status` (function) `progs/vedit/vedit.c:192` `static struct nk_color vedit_c_status(void)`
- `vedit_c_cursor` (function) `progs/vedit/vedit.c:193` `static struct nk_color vedit_c_cursor(void)`
- `vedit_ink` (function) `progs/vedit/vedit.c:195` `static struct nk_color vedit_ink(int col)`
- `definitions` (function) `progs/vedit/vedit.c:267` `* definitions (C99, one file, no headers). */ static void vedit_str_case(char *s, int mode);`
- `vedit_set_msg` (function) `progs/vedit/vedit.c:360` `static void vedit_set_msg(const char *s)`
- `vedit_is_alpha` (function) `progs/vedit/vedit.c:367` `static int vedit_is_alpha(int c)`
- `vedit_is_digit` (function) `progs/vedit/vedit.c:371` `static int vedit_is_digit(int c)`
- `vedit_is_wordc` (function) `progs/vedit/vedit.c:375` `static int vedit_is_wordc(int c)`
- `vedit_is_kw` (function) `progs/vedit/vedit.c:379` `static int vedit_is_kw(const char *table, const char *word, int wlen)`
- `separators` (function) `progs/vedit/vedit.c:402` `* allow_quote exists because C digit separators (1'000'000) are not
 * valid in Python/Lua number...`
- `vedit_parse_number` (function) `progs/vedit/vedit.c:425` `static int vedit_parse_number(const char *t, int len, int i, int allow_quote)`
- `vedit_parse_keyword` (function) `progs/vedit/vedit.c:440` `static int vedit_parse_keyword(const char *t, int len, int i,
                               cons...`
- `vedit_lang_of` (function) `progs/vedit/vedit.c:457` `static int vedit_lang_of(const char *fname)` -- int wl = 0; int j = i; int k; while (j < len && vedit_is_wordc((unsigned char)t[j])) { if (wl < VEDIT_WORD_MAX - 1)...
- `vedit_lang_name` (function) `progs/vedit/vedit.c:478` `static const char *vedit_lang_name(int lang)`
- `vedit_scan_line` (function) `progs/vedit/vedit.c:488` `static int vedit_scan_line(const char *t, int len, int st)` -- } /** Name a highlight language for the status row. static const char *vedit_lang_name(int lang) { if (lang ==...
- `vedit_state_at` (function) `progs/vedit/vedit.c:759` `static int vedit_state_at(int row)` -- } else if (c == '"' || c == '\'') { i = vedit_parse_string(t, len, i); } else if (vedit_is_digit(c)) { i =...
- `vedit_row_ptr` (function) `progs/vedit/vedit.c:768` `static char *vedit_row_ptr(int idx)`
- `vedit_clamp` (function) `progs/vedit/vedit.c:772` `static void vedit_clamp(void)`
- `vedit_follow` (function) `progs/vedit/vedit.c:784` `static void vedit_follow(void)`
- `vedit_insert_char` (function) `progs/vedit/vedit.c:797` `static void vedit_insert_char(int c)`
- `vedit_delete_line_at` (function) `progs/vedit/vedit.c:835` `static void vedit_delete_line_at(int idx)`
- `vedit_backspace` (function) `progs/vedit/vedit.c:846` `static void vedit_backspace(void)`
- `vedit_delete_char` (function) `progs/vedit/vedit.c:882` `static void vedit_delete_char(void)`
- `vedit_split` (function) `progs/vedit/vedit.c:915` `static void vedit_split(void)`
- `vedit_tab` (function) `progs/vedit/vedit.c:968` `static void vedit_tab(void)`
- `vedit_str_case` (function) `progs/vedit/vedit.c:1004` `static void vedit_str_case(char *s, int mode)` -- Upper/lower/capitalize a NUL string in place; mode 1=upper, 2=lower, * 3=capitalize.
- `vedit_str_transpose` (function) `progs/vedit/vedit.c:1031` `static void vedit_str_transpose(char *s, int len, int pos)` -- new_word = 0; } else { if (new_word) { if (c >= 'a' && c <= 'z') s[i] = (char)(c - 32); new_word = 0; } else { if (c...
- `vedit_magic_class` (function) `progs/vedit/vedit.c:1043` `static int vedit_magic_class(int c, const char *cls)` -- Minimal magic matcher (uemacs search.c subset): '.' any, '*' repeat, '^'/'$' anchors, '[...]' classes with ranges...
- `vedit_magic_atom` (function) `progs/vedit/vedit.c:1065` `static int vedit_magic_atom(const char *pat, int c, int *atom_len)`
- `vedit_magic_here` (function) `progs/vedit/vedit.c:1088` `static int vedit_magic_here(const char *text, const char *pat, int *mlen)`
- `vedit_magic_match` (function) `progs/vedit/vedit.c:1149` `static int vedit_magic_match(const char *text, const char *pat, int *mlen)` -- if (vedit_magic_here(text + k, rest, &sub)) { mlen = total + k + sub; return 1; } if (k == 0) break; } return 0; } }...
- `vedit_buf_alloc` (function) `progs/vedit/vedit.c:1178` `static int vedit_buf_alloc(int idx)`
- `vedit_next_buffer` (function) `progs/vedit/vedit.c:1206` `static int vedit_next_buffer(void)`
- `vedit_hist_push` (function) `progs/vedit/vedit.c:1220` `static void vedit_hist_push(const char *fname)`
- `vedit_set_mark` (function) `progs/vedit/vedit.c:1239` `static void vedit_set_mark(void)`
- `vedit_region` (function) `progs/vedit/vedit.c:1247` `static int vedit_region(int *y0, int *x0, int *y1, int *x1)` -- for (k = 0; k < VEDIT_HIST_N - 1; k++) memcpy(vedit_hist[k], vedit_hist[k + 1], VEDIT_FNAME_MAX)...
- `vedit_copy_region` (function) `progs/vedit/vedit.c:1268` `static int vedit_copy_region(void)` -- int t = *y0; y0 = *y1; y1 = t; t = *x0; x0 = *x1; x1 = t; } if (*y0 == *y1 && *x0 == *x1) return 0; if (*y0 >=...
- `vedit_kill_region` (function) `progs/vedit/vedit.c:1298` `static int vedit_kill_region(void)` -- if (a > vedit_used[y]) a = vedit_used[y]; if (b > vedit_used[y]) b = vedit_used[y]; for (k = a; k < b && pos <...
- `vedit_kill_line` (function) `progs/vedit/vedit.c:1344` `static int vedit_kill_line(void)` -- } for (k = 0; k < tail; k++) first[x0 + k] = last[x1 + k]; vedit_used[y0] = x0 + tail; for (y = y1; y > y0; y--)...
- `vedit_yank` (function) `progs/vedit/vedit.c:1382` `static int vedit_yank(void)` -- vedit_kill[vedit_kill_head][0] = '\n'; vedit_kill[vedit_kill_head][1] = 0; vedit_kill_len[vedit_kill_head] = 1...
- `vedit_word_move` (function) `progs/vedit/vedit.c:1415` `static int vedit_word_move(int dir)` -- vedit_row_ptr(vedit_cy)[vedit_cx] = s[k]; vedit_cx++; vedit_dirty = 1; } else { vedit_insert_char((unsigned...
- `vedit_case_word` (function) `progs/vedit/vedit.c:1450` `static int vedit_case_word(int mode)` -- vedit_cx = vedit_used[vedit_cy]; return 0; } while (vedit_cx > 0 && !vedit_is_wordc((unsigned char)l[vedit_cx - 1]))...
- `vedit_transpose` (function) `progs/vedit/vedit.c:1489` `static int vedit_transpose(void)` -- if (mode == 1 && c >= 'a' && c <= 'z') l[k] = (char)(c - 32); else if (mode == 2 && c >= 'A' && c <= 'Z') l[k] =...
- `vedit_goto_fence` (function) `progs/vedit/vedit.c:1512` `static int vedit_goto_fence(void)` -- vedit_set_msg("nothing to transpose"); return -1; } if (vedit_cx <= 0) vedit_cx = 1; if (vedit_cx >=...
- `vedit_count_words` (function) `progs/vedit/vedit.c:1578` `static void vedit_count_words(void)` -- vedit_cy = y; vedit_cx = x; vedit_msg[0] = 0; return 0; } depth--; } } } vedit_set_msg("no match"); return -1; } /**...
- `vedit_match_at` (function) `progs/vedit/vedit.c:1621` `static int vedit_match_at(int row, int col, const char *needle, int magic,
                      ...` -- printf("vedit: %s\n", nb); } /* ---- uemacs F2: magic search, isearch, replace, fill ---- #define VEDIT_FILL_COL 72...
- `vedit_search_fwd` (function) `progs/vedit/vedit.c:1658` `static int vedit_search_fwd(int row, int col, const char *needle, int magic,
                    ...` -- if (avail > VEDIT_LINE_MAX) avail = VEDIT_LINE_MAX; for (k = 0; k < avail; k++) tmp[k] = l[col + k]; tmp[avail] = 0...
- `vedit_search_rev` (function) `progs/vedit/vedit.c:1690` `static int vedit_search_rev(int row, int col, const char *needle, int magic)`
- `vedit_isearch_step` (function) `progs/vedit/vedit.c:1713` `static void vedit_isearch_step(void)`
- `vedit_replace_at` (function) `progs/vedit/vedit.c:1740` `static int vedit_replace_at(int row, int col, const char *old_s,
                            cons...` -- vedit_set_msg("wrapped"); else vedit_msg[0] = 0; } else { if (vedit_search_rev(vedit_isearch_oy, vedit_isearch_ox...
- `vedit_replace_all` (function) `progs/vedit/vedit.c:1760` `static int vedit_replace_all(const char *old_s, const char *new_s,
                             i...` -- if (!vedit_match_at(row, col, old_s, magic, &mlen) || mlen <= 0) return -1; l = vedit_row_ptr(row); nlen =...
- `vedit_fill_paragraph` (function) `progs/vedit/vedit.c:1813` `static int vedit_fill_paragraph(void)` -- r++; c = 0; if (r >= vedit_count) break; } } { char nb[64]; snprintf(nb, sizeof(nb), "replaced %d", count)...
- `vedit_find` (function) `progs/vedit/vedit.c:1897` `static void vedit_find(const char *needle)`
- `vedit_save` (function) `progs/vedit/vedit.c:1987` `static int vedit_save(void)`
- `vedit_load` (function) `progs/vedit/vedit.c:2050` `static int vedit_load(void)`
- `vedit_open_in_buffer` (function) `progs/vedit/vedit.c:2121` `static int vedit_open_in_buffer(const char *fname, int ro)` -- { struct stat st; if (stat(vedit_fname, &st) == 0) { vedit_sizes[vedit_cur] = (long)st.st_size...
- `vedit_insert_buf` (function) `progs/vedit/vedit.c:2182` `static char *vedit_insert_buf(long size)` -- Insert scratch arena: one reusable block serves every insert-file and shell-capture load, reset per call and grown...
- `vedit_insert_file` (function) `progs/vedit/vedit.c:2195` `static int vedit_insert_file(const char *fname)` -- /** Docstring: borrow size bytes of insert scratch, growing it when short. static char *vedit_insert_buf(long size)...
- `vedit_has_ext` (function) `progs/vedit/vedit.c:2256` `static int vedit_has_ext(const char *fname, const char *ext)` -- vedit_split(); } else { vedit_insert_char((unsigned char)data[k]); } if (vedit_msg[0]) { vedit_set_msg("insert...
- `vedit_base_of` (function) `progs/vedit/vedit.c:2268` `static int vedit_base_of(const char *fname, char *dst, size_t cap)` -- /** Report whether a file name ends with the given extension. static int vedit_has_ext(const char *fname, const char...
- `vedit_join` (function) `progs/vedit/vedit.c:2289` `static int vedit_join(const char *dir, const char *base, const char *ext,
                      c...` -- if (fname[k] == '/') s = k + 1; } for (k = s; k < n; k++) { if (fname[k] == '.') e = k; } if (e <= s) e = n; len = e...
- `vedit_link_fmt` (function) `progs/vedit/vedit.c:2306` `static int vedit_link_fmt(const char *s)` -- size_t b = strlen(base); size_t e = strlen(ext); size_t k = 0; size_t i; if (d + b + e + 1 > cap) return -1; if (d +...
- `vedit_print_log` (function) `progs/vedit/vedit.c:2319` `static void vedit_print_log(const char *path)` -- /** Accept only the two linker formats, rejecting anything else. static int vedit_link_fmt(const char *s) { size_t k...
- `vedit_spawn_visible` (function) `progs/vedit/vedit.c:2336` `static long vedit_spawn_visible(const char *tool, const char *redir, int argc,
                  ...` -- size_t n; if (!f) { printf("vedit: no output captured (%s missing)\n", path); return; } while ((n = fread(buf, 1...
- `vedit_cmd_exec` (function) `progs/vedit/vedit.c:2365` `static void vedit_cmd_exec(const char *out, int kind)` -- if (rc < 0) { snprintf(nb, sizeof(nb), "%s failed (%ld)", label, rc); vedit_set_msg(nb); } else if (rc != 0) {...
- `vedit_run_kind` (function) `progs/vedit/vedit.c:2378` `static int vedit_run_kind(const char *fname)` -- /** Run a freshly linked artifact so its output lands on the console. static void vedit_cmd_exec(const char *out...
- `vedit_cmd_run` (function) `progs/vedit/vedit.c:2388` `static void vedit_cmd_run(void)` -- vedit_spawn_visible(VEDIT_TOOL_CVM, 0, 1, args, label); } /** Decide the ^R tool for a file: 1=minigcc, 2=lua...
- `vedit_cmd_link` (function) `progs/vedit/vedit.c:2465` `static void vedit_cmd_link(const char *fmt)` -- vedit_set_msg("usage: save as .c, .s, .lua, .py or .lisp first"); return; } args[0] = tool; args[1] = vedit_fname...
- `vedit_selftest_build` (function) `progs/vedit/vedit.c:2516` `static int vedit_selftest_build(void)` -- Headless build contract check: no display, no syscalls, exit status only.
- `vedit_selftest_leak` (function) `progs/vedit/vedit.c:2709` `static int vedit_selftest_leak(void)` -- Headless leak contract: the insert scratch arena and one buffer lifecycle must net zero live blocks.
- `vedit_pane_save` (function) `progs/vedit/vedit.c:2769` `static void vedit_pane_save(int p)`
- `vedit_first_open` (function) `progs/vedit/vedit.c:2777` `static int vedit_first_open(void)`
- `vedit_pane_load` (function) `progs/vedit/vedit.c:2785` `static void vedit_pane_load(int p)`
- `vedit_count_open` (function) `progs/vedit/vedit.c:2797` `static int vedit_count_open(void)`
- `vedit_split_set` (function) `progs/vedit/vedit.c:2806` `static void vedit_split_set(int on)`
- `vedit_next_pane` (function) `progs/vedit/vedit.c:2825` `static void vedit_next_pane(void)`
- `vedit_cmd_lookup` (function) `progs/vedit/vedit.c:2857` `static int vedit_cmd_lookup(const char *name)`
- `vedit_parse_key` (function) `progs/vedit/vedit.c:2873` `static int vedit_parse_key(const char *s)` -- Parse a key description into a decoded key code: ^A..^Z ^@ ^[ ^\ ^] ^^ ^_, M-<c>, or Up Down Left Right Home End...
- `vedit_cmd_bind` (function) `progs/vedit/vedit.c:2925` `static int vedit_cmd_bind(int key, int cmd)`
- `vedit_cmd_bound` (function) `progs/vedit/vedit.c:2941` `static int vedit_cmd_bound(int key)`
- `vedit_list_buffers` (function) `progs/vedit/vedit.c:2949` `static void vedit_list_buffers(void)`
- `vedit_hist_show` (function) `progs/vedit/vedit.c:2968` `static void vedit_hist_show(void)`
- `vedit_help_text` (function) `progs/vedit/vedit.c:2976` `static void vedit_help_text(void)`
- `vedit_cmd_exec_id` (function) `progs/vedit/vedit.c:2992` `static void vedit_cmd_exec_id(int id, const char *arg, int *quit,
                              i...` -- printf("arrows/Home/End/PgUp/PgDn move, ^U arg, ^A/^E bol/eol\n"); printf("M-f/M-b word, M-c/M-l/M-u case word...
- `strcmp` (function) `progs/vedit/vedit.c:3180` `strcmp(name, "describe-bindings") == 0)`
- `vedit_run_rc` (function) `progs/vedit/vedit.c:3198` `static void vedit_run_rc(const char *path)` -- Run the startup script: `bind <key> <cmd>` plus bare commands with * an optional trailing argument.
- `vedit_sel_clear` (function) `progs/vedit/vedit.c:3276` `static void vedit_sel_clear(void)`
- `vedit_sel_norm` (function) `progs/vedit/vedit.c:3281` `static void vedit_sel_norm(void)`
- `vedit_sel_copy` (function) `progs/vedit/vedit.c:3294` `static int vedit_sel_copy(void)` -- static void vedit_sel_norm(void) { if (vedit_sy0 > vedit_sy1 || (vedit_sy0 == vedit_sy1 && vedit_sx0 > vedit_sx1)) {...
- `vedit_clip_paste` (function) `progs/vedit/vedit.c:3337` `static int vedit_clip_paste(void)` -- } if (vedit_clip_set(vedit_clipbuf, pos) != 0) { vedit_set_msg("clipboard refused"); return -1; } { char nb[64]...
- `vedit_region_to_clip` (function) `progs/vedit/vedit.c:3367` `static int vedit_region_to_clip(void)` -- vedit_split(); else vedit_insert_char((unsigned char)vedit_clipbuf[k]); if (vedit_msg[0]) { vedit_set_msg("paste...
- `vedit_sh_split` (function) `progs/vedit/vedit.c:3412` `static int vedit_sh_split(const char *line, char *buf, const char **argv)` -- } if (pos <= 0) { vedit_set_msg("nothing selected"); return -1; } if (vedit_clip_set(vedit_clipbuf, pos) != 0) {...
- `vedit_shell_command` (function) `progs/vedit/vedit.c:3432` `static void vedit_shell_command(const char *line)` -- if (!*line) break; if (argc >= VEDIT_SH_ARGS) return -1; argv[argc++] = buf + k; while (*line && *line != ' ' &&...
- `vedit_write_region` (function) `progs/vedit/vedit.c:3461` `static int vedit_write_region(const char *path, int *y0o, int *x0o, int *y1o,
                   ...` -- idx = vedit_open_in_buffer("*shell*", 0); if (idx < 0) return; vedit_count = 0; vedit_cx = 0; vedit_cy = 0...
- `vedit_filter_buffer` (function) `progs/vedit/vedit.c:3505` `static void vedit_filter_buffer(const char *prog)` -- if (y < y1) putc('\n', f); } if (fclose(f) != 0) { vedit_set_msg("cannot write temp file"); return -1; } if (y0o)...
- `vedit_grep` (function) `progs/vedit/vedit.c:3565` `static void vedit_grep(const char *pat)` -- vedit_cx = x1; vedit_mark_y = y0; vedit_mark_x = x0; vedit_mark_on = 1; if (vedit_kill_region() != 0) return; if...
- `vedit_next_error` (function) `progs/vedit/vedit.c:3628` `static void vedit_next_error(void)` -- } vedit_switch_buffer(idx); vedit_grep_src = src; vedit_cx = 0; vedit_cy = 0; vedit_top = 0; { char nb[64]...
- `vedit_read_key_poll` (function) `progs/vedit/vedit.c:3676` `static int vedit_read_key_poll(void)`
- `vedit_ansi_for` (function) `progs/vedit/vedit.c:3730` `static void vedit_ansi_for(int col)` -- vedit_esc_state = 3; vedit_esc_t0 = now; return -1; } return VEDIT_KEY_ESC; } vedit_esc_state = 0; if (c != '~')...
- `vedit_console_dump` (function) `progs/vedit/vedit.c:3738` `static void vedit_console_dump(void)`
- `vedit_prompt_open` (function) `progs/vedit/vedit.c:3768` `static void vedit_prompt_open(const char *label, int mode)` -- vedit_ansi_for(vedit_cell[c]); cur = vedit_cell[c]; } putchar(l[c]); } if (cur != VEDIT_COL_DEFAULT)...
- `vedit_prompt_find` (function) `progs/vedit/vedit.c:3779` `static void vedit_prompt_find(void)`
- `vedit_prompt_isearch` (function) `progs/vedit/vedit.c:3783` `static void vedit_prompt_isearch(int dir)`
- `vedit_qrep_next` (function) `progs/vedit/vedit.c:3793` `static void vedit_qrep_next(int r, int c)` -- static void vedit_prompt_find(void) { vedit_prompt_open("find: ", VEDIT_PROMPT_FIND); } static void...
- `vedit_qrep_answer` (function) `progs/vedit/vedit.c:3805` `static void vedit_qrep_answer(int key)`
- `vedit_prompt_saveas` (function) `progs/vedit/vedit.c:3844` `static void vedit_prompt_saveas(void)`
- `vedit_draw_row` (function) `progs/vedit/vedit.c:3854` `static void vedit_draw_row(struct nk_command_buffer *canvas,
                           struct nk...`
- `vedit_draw_ui` (function) `progs/vedit/vedit.c:3952` `static void vedit_draw_ui(struct nk_context *ctx, struct nk_user_font *font,
                    ...` -- if (a < 0) a = 0; if (b > len) b = len; for (c = a; c < b; c++) { int vc = c - vedit_hoff; if (vc < 0 || vc >=...
- `vedit_prompt_key` (function) `progs/vedit/vedit.c:4232` `static void vedit_prompt_key(int key)` -- vedit_cw), (float)(vedit_status_y + 2), (float)vedit_cw, (float)vedit_ch), 0, vedit_c_cursor()); }...
- `vedit_key` (function) `progs/vedit/vedit.c:4406` `static void vedit_key(int key, int *quit, int *save_and_quit)` -- vedit_isearch_step(); } return; } if (key >= 32 && key < 127 && vedit_prompt_pos < VEDIT_LINE_MAX - 1) {...
- `vedit_sync_title` (function) `progs/vedit/vedit.c:4646` `static void vedit_sync_title(void)`
- `vedit_gui_run` (function) `progs/vedit/vedit.c:4656` `static void vedit_gui_run(void)`
- `vedit_selftest` (function) `progs/vedit/vedit.c:4747` `static int vedit_selftest(void)`
- `main` (function) `progs/vedit/vedit.c:4823` `int main(int argc, char **argv)`

## progs/wl/wl_client.h
Depends on: `progs/wl/wl_mbox.h`
Imported by: `progs/nuklear/nuklear_minios.c`, `progs/wl/wlcomp.c`
- `wl_client_emit_file` (function) `progs/wl/wl_client.h:21` `static inline int wl_client_emit_file(const char *box, unsigned int seq,
        const unsigned c...` -- N tiled windows with real multitasking under the existing preemptive scheduler.
- `wl_client_raw_file` (function) `progs/wl/wl_client.h:48` `static inline int wl_client_raw_file(const char *box,
        const unsigned char *px, int w, int h)` -- Write the pixel blob the next attach sizes.
- `wl_client_attach` (function) `progs/wl/wl_client.h:75` `static inline int wl_client_attach(const char *box, unsigned int seq0,
        const unsigned cha...` -- Attach one surface: pixels first, then display, bind, create, pool, attach and commit, each sequenced from seq0.

## progs/wl/wl_mbox.h
Depends on: `progs/wl/wl_mini.h`
Imported by: `progs/nuklear/nuklear_minios.c`, `progs/wl/wl_client.h`, `progs/wl/wlcomp.c`, `tests/test_wl.c`
- `wl_mbox_init` (function) `progs/wl/wl_mbox.h:36` `static inline void wl_mbox_init(wl_mbox_box_t *boxes)`
- `wl_mbox_box_ok` (function) `progs/wl/wl_mbox.h:51` `static inline int wl_mbox_box_ok(const char *box)` -- Box names are lowercase alphanumerics so they can never escape the * directory through dot or slash tricks.
- `wl_mbox_hex` (function) `progs/wl/wl_mbox.h:74` `static inline int wl_mbox_hex(unsigned int v, char *dst)` -- if (ch >= '0' && ch <= '9') ok = 1; if (!ok) return WL_ERR_STR; n++; if (n >= WL_MBOX_BOX_MAX) return WL_ERR_STR; }...
- `wl_mbox_unhex` (function) `progs/wl/wl_mbox.h:87` `static inline int wl_mbox_unhex(char ch, unsigned int *v)`
- `wl_mbox_name` (function) `progs/wl/wl_mbox.h:103` `static inline int wl_mbox_name(char *dst, int cap, const char *box,
        unsigned int seq)` -- Build WL_MBOX_DIR/box-seq.msg.
- `wl_mbox_parse` (function) `progs/wl/wl_mbox.h:147` `static inline int wl_mbox_parse(const char *path, char *box, int boxcap,
        unsigned int *seq)` -- Parse a mailbox path back into box plus sequence.
- `wl_mbox_raw_name` (function) `progs/wl/wl_mbox.h:194` `static inline int wl_mbox_raw_name(char *dst, int cap, const char *box)` -- path += WL_MBOX_SEQ_HEX; i = 0; while (suf[i] != '\0') { if (path[i] != suf[i]) return WL_ERR_STR; i++; } if...
- `wl_mbox_ev_name` (function) `progs/wl/wl_mbox.h:225` `static inline int wl_mbox_ev_name(char *dst, int cap, const char *box)` -- return WL_ERR_BOUND; dst[di++] = box[i++]; } i = 0; while (suf[i] != '\0') { if (di >= cap - 1) return WL_ERR_BOUND...
- `wl_client_box` (function) `progs/wl/wl_mbox.h:257` `static inline int wl_client_box(const char *prog, long pid, char *dst,
        int cap)` -- Client box name: lowercase alnum program plus decimal pid, so two * instances of one app never share a mailbox.
- `wl_mbox_frame_encode` (function) `progs/wl/wl_mbox.h:310` `static inline int wl_mbox_frame_encode(unsigned char *dst, int cap,
        unsigned int seq, con...` -- Frame one wire message: magic plus sequence plus the raw message.
- `wl_mbox_frame_decode` (function) `progs/wl/wl_mbox.h:332` `static inline int wl_mbox_frame_decode(const unsigned char *src, int len,
        unsigned int *s...`
- `wl_mbox_assign` (function) `progs/wl/wl_mbox.h:358` `static inline int wl_mbox_assign(wl_mbox_box_t *boxes, const char *box)` -- Claim the slot a box owns, stable across polls, fail-closed when * the server is full or the name is wild.
- `wl_mbox_fresh` (function) `progs/wl/wl_mbox.h:394` `static inline int wl_mbox_fresh(const wl_mbox_box_t *boxes, int slot,
        unsigned int seq)` -- Freshness of an arriving sequence: a repeat of the last accepted one is a duplicate the server already consumed...
- `wl_mbox_route` (function) `progs/wl/wl_mbox.h:409` `static inline int wl_mbox_route(wl_comp_t *c, wl_mbox_box_t *boxes,
        const char *box, unsi...` -- Route one mailbox message to the compositor state.

## progs/wl/wl_mini.h
Imported by: `progs/src/freedom_wl.c`, `progs/wl/wl_mbox.h`, `progs/wl/wlcomp.c`, `tests/test_wl.c`
- `wl_hdr_encode` (function) `progs/wl/wl_mini.h:71` `static inline int wl_hdr_encode(unsigned char *dst, int cap,
        unsigned int id, unsigned in...`
- `wl_hdr_decode` (function) `progs/wl/wl_mini.h:99` `static inline int wl_hdr_decode(const unsigned char *src, int len,
        wl_hdr_t *out)`
- `wl_u32_encode` (function) `progs/wl/wl_mini.h:128` `static inline int wl_u32_encode(unsigned char *dst, int cap, int off,
        unsigned int v)`
- `wl_u32_decode` (function) `progs/wl/wl_mini.h:139` `static inline int wl_u32_decode(const unsigned char *src, int len, int off,
        unsigned int *v)`
- `wl_strlen_bounded` (function) `progs/wl/wl_mini.h:150` `static inline int wl_strlen_bounded(const char *s)`
- `wl_str_encode` (function) `progs/wl/wl_mini.h:163` `static inline int wl_str_encode(unsigned char *dst, int cap, int off,
        const char *s)` -- static inline int wl_strlen_bounded(const char *s) { int n = 0; if (!s) return WL_ERR_STR; while (s[n] != '\0') {...
- `wl_str_decode` (function) `progs/wl/wl_mini.h:188` `static inline int wl_str_decode(const unsigned char *src, int len, int off,
        char *dst, in...`
- `wl_surface_id_valid` (function) `progs/wl/wl_mini.h:214` `static inline int wl_surface_id_valid(unsigned int id)`
- `wl_pool_id_valid` (function) `progs/wl/wl_mini.h:219` `static inline int wl_pool_id_valid(unsigned int id)`
- `wl_pool_fit` (function) `progs/wl/wl_mini.h:223` `static inline int wl_pool_fit(int w, int h)`
- `wl_comp_init` (function) `progs/wl/wl_mini.h:271` `static inline void wl_comp_init(wl_comp_t *c)`
- `wl_comp_refresh_active` (function) `progs/wl/wl_mini.h:289` `static inline void wl_comp_refresh_active(wl_comp_t *c)` -- Refresh the active flag from z-order: only the top-most mapped, non-minimized surface reads active.
- `wl_comp_add` (function) `progs/wl/wl_mini.h:309` `static inline int wl_comp_add(wl_comp_t *c, unsigned int id, int w, int h)`
- `wl_comp_remove` (function) `progs/wl/wl_mini.h:345` `static inline int wl_comp_remove(wl_comp_t *c, unsigned int id)`
- `wl_comp_focus` (function) `progs/wl/wl_mini.h:372` `static inline int wl_comp_focus(wl_comp_t *c, unsigned int id)`
- `wl_comp_hit` (function) `progs/wl/wl_mini.h:397` `static inline int wl_comp_hit(const wl_comp_t *c, int x, int y)`
- `wl_surface_hit_zone` (function) `progs/wl/wl_mini.h:415` `static inline int wl_surface_hit_zone(const wl_surface_t *s, int x, int y)` -- Classify a point inside one surface: close button first, then title drag strip, then the resize rim, else body.
- `wl_comp_top_visible` (function) `progs/wl/wl_mini.h:441` `static inline int wl_comp_top_visible(const wl_comp_t *c)` -- Slot of the top-most mapped, non-minimized surface, or -1.
- `wl_comp_set_minimized` (function) `progs/wl/wl_mini.h:460` `static inline int wl_comp_set_minimized(wl_comp_t *c, unsigned int id,
        int minimized)` -- Minimize/restore one surface.
- `wl_comp_set_color` (function) `progs/wl/wl_mini.h:487` `static inline int wl_comp_set_color(wl_comp_t *c, unsigned int id, int color)`
- `wlcomp_render` (function) `progs/wl/wl_mini.h:512` `static inline int wlcomp_render(const wl_comp_t *c, unsigned char *fb,
        int fb_w, int fb_h)`
- `wl_comp_set_rect` (function) `progs/wl/wl_mini.h:550` `static inline int wl_comp_set_rect(wl_comp_t *c, unsigned int id,
        int x, int y, int w, in...` -- Move and resize a mapped surface.
- `wl_comp_layout_tile` (function) `progs/wl/wl_mini.h:577` `static inline int wl_comp_layout_tile(wl_comp_t *c, int fb_w, int fb_h)` -- Tile every mapped surface over the frame in z-order.
- `wlcomp_blit` (function) `progs/wl/wl_mini.h:637` `static inline int wlcomp_blit(const wl_comp_t *c, unsigned char *fb,
        int fb_w, int fb_h, ...` -- Composite the surface stack with real client pixels. px, pw and ph are slot-indexed tables over items[]; a null slot...
- `body` (function) `progs/wl/wl_mini.h:698` `* resampled into the body (inside the 1 px border, below the title),
 * the exact rect wl_ev_map ...`
- `wl_scale_nearest` (function) `progs/wl/wl_mini.h:793` `static inline int wl_scale_nearest(unsigned char *dst, int dw, int dh,
        const unsigned cha...` -- Nearest-neighbour scale of an indexed frame, the compositor side of a client buffer meeting a layout cell of another...
- `wl_attach_encode` (function) `progs/wl/wl_mini.h:823` `static inline int wl_attach_encode(unsigned char *dst, int cap,
        unsigned int pool, int w,...` -- Attach payload: u32 pool id, u32 width, u32 height.
- `wl_attach_decode` (function) `progs/wl/wl_mini.h:842` `static inline int wl_attach_decode(const unsigned char *src, int len,
        unsigned int *pool,...`
- `wl_commit_encode` (function) `progs/wl/wl_mini.h:870` `static inline int wl_commit_encode(unsigned char *dst, int cap,
        unsigned int id)` -- Commit payload: u32 surface id naming the surface whose attached * buffer becomes visible.
- `wl_commit_decode` (function) `progs/wl/wl_mini.h:883` `static inline int wl_commit_decode(const unsigned char *src, int len,
        unsigned int *id)`
- `wl_clip_encode` (function) `progs/wl/wl_mini.h:907` `static inline int wl_clip_encode(unsigned char *dst, int cap,
        const unsigned char *text, ...`
- `wl_clip_decode` (function) `progs/wl/wl_mini.h:930` `static inline int wl_clip_decode(const unsigned char *src, int len,
        unsigned char *dst, i...`
- `coords` (function) `progs/wl/wl_mini.h:959` `* coords (mapped by wl_ev_map, -1 when outside), wheel is a * monotonic total the client diffs, scancodes are raw...`
- `wl_ev_encode` (function) `progs/wl/wl_mini.h:978` `static inline int wl_ev_encode(unsigned char *dst, int cap,
        const wl_ev_t *ev)`
- `wl_ev_decode` (function) `progs/wl/wl_mini.h:1008` `static inline int wl_ev_decode(const unsigned char *src, int len,
        wl_ev_t *ev)`
- `wl_ev_map` (function) `progs/wl/wl_mini.h:1051` `static inline int wl_ev_map(int fx, int fy, int sx, int sy, int sw,
        int sh, int rw, int r...` -- Map a frame point into a client's raw buffer coords.
- `wl_client_init` (function) `progs/wl/wl_mini.h:1092` `static inline void wl_client_init(wl_client_t *cl)`
- `wl_client_surface` (function) `progs/wl/wl_mini.h:1100` `static inline int wl_client_surface(wl_client_t *cl, unsigned int *id)`
- `wl_client_pool` (function) `progs/wl/wl_mini.h:1109` `static inline int wl_client_pool(wl_client_t *cl, unsigned int *id)`
- `wl_stream_init` (function) `progs/wl/wl_mini.h:1129` `static inline void wl_stream_init(wl_stream_t *s)`
- `wl_stream_feed` (function) `progs/wl/wl_mini.h:1135` `static inline int wl_stream_feed(wl_stream_t *s, const unsigned char *src,
        int n)`
- `wl_stream_next` (function) `progs/wl/wl_mini.h:1150` `static inline int wl_stream_next(wl_stream_t *s, int *size)`
- `wl_stream_consume` (function) `progs/wl/wl_mini.h:1166` `static inline int wl_stream_consume(wl_stream_t *s, int n)`
- `wl_iface_find` (function) `progs/wl/wl_mini.h:1187` `static inline int wl_iface_find(const char *name)`
- `wl_comp_attach_buf` (function) `progs/wl/wl_mini.h:1218` `static inline int wl_comp_attach_buf(wl_comp_t *c, unsigned int id,
        unsigned int pool, in...` -- Bind an attached buffer to a surface, keeping its position.
- `wl_dispatch` (function) `progs/wl/wl_mini.h:1245` `static inline int wl_dispatch(wl_comp_t *c, wl_client_t *cl,
        unsigned int id, unsigned in...` -- Route one framed request to the compositor state, the protocol.c plus server.c shape collapsed into one pure function.

## progs/wl/wl_pixbuf.h
Depends on: `kernel/string.c`
Imported by: `progs/wl/wlcomp.c`, `tests/test_wl.c`
- `wpix_init` (function) `progs/wl/wl_pixbuf.h:63` `static int wpix_init(struct wpix_store *s)` -- unsigned char *p; int w; int h; }; /** Docstring: slot caches plus one reusable raw/decode scratch pair. struct...
- `wpix_free` (function) `progs/wl/wl_pixbuf.h:78` `static void wpix_free(struct wpix_store *s)` -- size_t k = 0; if (s == NULL) return -1; for (k = 0; k < (size_t)WPIX_MAX_SLOTS; k++) { s->slots[k].p = NULL...
- `wpix_used` (function) `progs/wl/wl_pixbuf.h:95` `static size_t wpix_used(const struct wpix_store *s)` -- for (k = 0; k < (size_t)WPIX_MAX_SLOTS; k++) { free(s->slots[k].p); s->slots[k].p = NULL; s->slots[k].w = 0...
- `wpix_ptr` (function) `progs/wl/wl_pixbuf.h:107` `static unsigned char *wpix_ptr(struct wpix_store *s, int idx)` -- /** Docstring: live pixel bytes held across all slots. static size_t wpix_used(const struct wpix_store *s) { size_t...
- `wpix_raw` (function) `progs/wl/wl_pixbuf.h:115` `static unsigned char *wpix_raw(struct wpix_store *s)` -- n += (size_t)s->slots[k].w * (size_t)s->slots[k].h; } return n; } /** Docstring: readable pixels for slot idx, null...
- `wpix_dst` (function) `progs/wl/wl_pixbuf.h:121` `static unsigned char *wpix_dst(struct wpix_store *s)` -- static unsigned char *wpix_ptr(struct wpix_store *s, int idx) { if (s == NULL || idx < 0 || idx >= WPIX_MAX_SLOTS)...
- `wpix_drop` (function) `progs/wl/wl_pixbuf.h:127` `static void wpix_drop(struct wpix_store *s, int idx)` -- /** Docstring: raw scratch for mailbox file reads, null below capacity. static unsigned char *wpix_raw(struct...
- `wpix_tmp` (function) `progs/wl/wl_pixbuf.h:136` `static int wpix_tmp(struct wpix_store *s, size_t need)` -- if (s == NULL) return NULL; return s->tmp_dst; } /** Docstring: drop slot pixels and release its memory to the...
- `wpix_ensure` (function) `progs/wl/wl_pixbuf.h:153` `static int wpix_ensure(struct wpix_store *s, int idx, int w, int h)` -- if (s == NULL) return -1; if (need == 0 || need > (size_t)WPIX_SLOT_MAX) return -1; if (s->tmp_cap >= need) return...
- `wpix_commit` (function) `progs/wl/wl_pixbuf.h:175` `static int wpix_commit(struct wpix_store *s, int idx, const unsigned char *src, int w, int h)` -- if (s->slots[idx].p != NULL && s->slots[idx].w == w && s->slots[idx].h == h) return 0; if (s->slots[idx].p != NULL...

## progs/wl/wlcomp.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nk_palette.h`, `progs/wl/wl_client.h`, `progs/wl/wl_mbox.h`, `progs/wl/wl_mini.h`, `progs/wl/wl_pixbuf.h`
- `wlcomp_sys_title` (function) `progs/wl/wlcomp.c:57` `static long wlcomp_sys_title(const char *t)`
- `wlcomp_sys_present` (function) `progs/wl/wlcomp.c:65` `static long wlcomp_sys_present(long buf)`
- `wlcomp_sys_present_origin` (function) `progs/wl/wlcomp.c:73` `static long wlcomp_sys_present_origin(long buf, int *origin)`
- `wlcomp_sys_palette` (function) `progs/wl/wlcomp.c:81` `static long wlcomp_sys_palette(unsigned char *pal)`
- `wlcomp_sys_mouse` (function) `progs/wl/wlcomp.c:89` `static long wlcomp_sys_mouse(int *m)`
- `wlcomp_sys_kbd` (function) `progs/wl/wlcomp.c:97` `static long wlcomp_sys_kbd(void)`
- `wlcomp_sys_kbd_raw` (function) `progs/wl/wlcomp.c:105` `static long wlcomp_sys_kbd_raw(long on)`
- `wlcomp_sys_vga_mode` (function) `progs/wl/wlcomp.c:113` `static long wlcomp_sys_vga_mode(long on)`
- `wlcomp_sys_yield` (function) `progs/wl/wlcomp.c:121` `static long wlcomp_sys_yield(void)`
- `wlcomp_sys_dir_list` (function) `progs/wl/wlcomp.c:129` `static long wlcomp_sys_dir_list(const char *path, char *buf, long cap)`
- `wlcomp_palette` (function) `progs/wl/wlcomp.c:139` `static int wlcomp_palette(void)` -- Upload the shared hybrid palette so indexed pixels expand through * desktop-exact colors on every VBE mode instead...
- `wlcomp_pattern` (function) `progs/wl/wlcomp.c:150` `static void wlcomp_pattern(unsigned char *dst, int w, int h,
        unsigned char a, unsigned ch...` -- Paint a deterministic test pattern so the demo proves real pixels * travelled the blit path instead of solid fills.
- `wlcomp_demo` (function) `progs/wl/wlcomp.c:189` `static int wlcomp_demo(wl_comp_t *c)`
- `wlcomp_demo_blit` (function) `progs/wl/wlcomp.c:214` `static int wlcomp_demo_blit(wl_comp_t *c, unsigned char *fb)` -- if (wl_comp_add(c, s1, 320, 200) != WL_ERR_OK) return 1; if (wl_comp_set_color(c, s0, 4) != WL_ERR_OK) return 1; if...
- `wlcomp_emit` (function) `progs/wl/wlcomp.c:260` `static int wlcomp_emit(unsigned char *s, int cap, int o, unsigned int id,
        unsigned int op...` -- wlcomp_pattern(p1, w1, h1, cfg.check_a, cfg.check_b, 1); px[c->order[0]] = p0; pw[c->order[0]] = w0; ph[c->order[0]]...
- `wlcomp_session` (function) `progs/wl/wlcomp.c:272` `static int wlcomp_session(wl_comp_t *c, wl_client_t *cl)` -- Drive a full client session through stream plus dispatch.
- `wlcomp_selftest` (function) `progs/wl/wlcomp.c:345` `static int wlcomp_selftest(void)`
- `wlserv_init` (function) `progs/wl/wlcomp.c:418` `static void wlserv_init(wlserv_t *s)`
- `wlserv_slot` (function) `progs/wl/wlcomp.c:437` `static int wlserv_slot(const wl_comp_t *c, unsigned int id)` -- wpix_init(&wlserv_raw); for (i = 0; i < WL_MAX_SURFACES; i++) { s->pw[i] = 0; s->ph[i] = 0; s->rw[i] = 0; s->rh[i] =...
- `wlserv_recolor` (function) `progs/wl/wlcomp.c:450` `static void wlserv_recolor(wl_comp_t *c)` -- Paint every mapped slot a distinct desktop-exact ink so clients * without pixels still read as separate windows.
- `wlserv_present` (function) `progs/wl/wlcomp.c:467` `static int wlserv_present(wlserv_t *s)` -- Composite the cached pixels and present with palette uploaded, capturing the content origin for pointer translation.
- `wlserv_load_raw` (function) `progs/wl/wlcomp.c:502` `static int wlserv_load_raw(wlserv_t *s, int b, int idx)` -- Reload the raw copy of one slot from its box .raw file.
- `wlserv_fit` (function) `progs/wl/wlcomp.c:547` `static void wlserv_fit(wlserv_t *s)` -- Fit every mapped surface to its laid-out size: reload the box raw copy only when the client published since the last...
- `wlserv_gc_strays` (function) `progs/wl/wlcomp.c:609` `static void wlserv_gc_strays(void)` -- Unlink stray .msg files no client owns: names that fail the exact mailbox parse can never dispatch, so they are dead...
- `wlserv_focus_box` (function) `progs/wl/wlcomp.c:664` `static int wlserv_focus_box(const wlserv_t *s)` -- Server-to-client input delivery (ADR-0026 live step).
- `wlserv_key` (function) `progs/wl/wlcomp.c:686` `static void wlserv_key(wlserv_t *s, unsigned char byte)` -- Queue one raw byte for the focused client.
- `wlserv_ev_clear` (function) `progs/wl/wlcomp.c:706` `static void wlserv_ev_clear(wlserv_t *s, int b)` -- b = wlserv_focus_box(s); if (b < 0) return; n = wlserv_ev_npend[b]; if (n >= WL_EV_SC_MAX) { for (i = 0; i + 1 <...
- `wlserv_push_ev` (function) `progs/wl/wlcomp.c:717` `static void wlserv_push_ev(wlserv_t *s, int fx, int fy, int buttons)` -- Push the current input state to the focused box.
- `wlserv_clean_ev` (function) `progs/wl/wlcomp.c:765` `static void wlserv_clean_ev(void)` -- Unlink every stale .ev file so no dead input replays after a restart.
- `wlserv_close` (function) `progs/wl/wlcomp.c:798` `static int wlserv_close(wlserv_t *s, unsigned int id)` -- Close one surface by id: remove it, free its box slot for the next client, drop its cache and unlink its raw pixels.
- `wlserv_box_known` (function) `progs/wl/wlcomp.c:830` `static int wlserv_box_known(const wlserv_t *s, const char *box)` -- if (s->boxes[b].used) { if (wl_mbox_raw_name(path, sizeof path, s->boxes[b].box) > 0) unlink(path); if...
- `forever` (function) `progs/wl/wlcomp.c:844` `* one of the WL_MAX_SURFACES slots forever (eight bad names used to lock
 * every real client out...`
- `wlserv_drain` (function) `progs/wl/wlcomp.c:933` `static int wlserv_drain(wlserv_t *s)` -- Drain at most WL_MBOX_POLL_MAX mailbox files: validate every frame before dispatch, unlink what was consumed, and...
- `wlclient_find` (function) `progs/wl/wlcomp.c:1005` `static const wlclient_pat_t *wlclient_find(const char *name)`
- `wlcomp_client` (function) `progs/wl/wlcomp.c:1034` `static int wlcomp_client(const char *box, const char *pat)` -- Attach one client surface from a second process through the shared wl_client.h transport: pixels first so the server...
- `wlcomp_path` (function) `progs/wl/wlcomp.c:1103` `static int wlcomp_path(char *dst, int cap, const char *name)` -- Join WL_MBOX_DIR + '/' + name into dst.
- `wlserv_relayout_present` (function) `progs/wl/wlcomp.c:1123` `static int wlserv_relayout_present(wlserv_t *s)` -- Tile, refit pixels and present.
- `wlcomp_clean` (function) `progs/wl/wlcomp.c:1137` `static int wlcomp_clean(void)` -- static int wlserv_relayout_present(wlserv_t *s) { if (!s) return 1; if (wl_comp_layout_tile(&s->comp, WLCOMP_W...
- `wlcomp_once` (function) `progs/wl/wlcomp.c:1165` `static int wlcomp_once(void)` -- Drain once and exit so scripts prove multiprocess composition * through the gfx frames counter without an...
- `wlcomp_server` (function) `progs/wl/wlcomp.c:1197` `static int wlcomp_server(void)` -- Interactive desktop: click focuses, title drag moves, rim drag resizes, close box closes, pure pointer motion...
- `main` (function) `progs/wl/wlcomp.c:1467` `int main(int argc, char **argv)`

## qga.c
Depends on: `headers/qga.h`, `headers/rtc.h`
- `channel` (function) `qga.c:10` `* * Polled channel (no interrupt controller): qga_init sets up COM2 and * qga_poll, called from raw_blocking_getc...`
- `qga_tx_ready` (function) `qga.c:27` `static int qga_tx_ready(void)`
- `qga_rx_ready` (function) `qga.c:28` `static int qga_rx_ready(void)`
- `qga_putc` (function) `qga.c:30` `static void qga_putc(char c)`
- `qga_init` (function) `qga.c:35` `void qga_init(void)`
- `qga_ws` (function) `qga.c:56` `static int qga_ws(char c)`
- `qga_parse_object` (function) `qga.c:65` `static int qga_parse_object(const char **pp, struct qga_pair *out, int max,
                     ...` -- Parse a JSON object whose members are stored flat into out[*count..]: a nested object's members keep the parent key...
- `qga_parse_flat` (function) `qga.c:147` `static int qga_parse_flat(const char *s, struct qga_pair *out, int max)` -- Parse a request line into the flat pair table.
- `qga_get_str` (function) `qga.c:158` `static const char *qga_get_str(const struct qga_pair *pairs, int n, const char *key)`
- `qga_get_int` (function) `qga.c:166` `static int qga_get_int(const struct qga_pair *pairs, int n, const char *key, long *out)`
- `qga_resp_reset` (function) `qga.c:184` `static void qga_resp_reset(void)`
- `qga_resp_puts` (function) `qga.c:186` `static void qga_resp_puts(const char *s)`
- `qga_resp_putc_enc` (function) `qga.c:194` `static void qga_resp_putc_enc(char c)`
- `qga_resp_put_long` (function) `qga.c:201` `static void qga_resp_put_long(long v)` -- Append the decimal form of v (a separate helper so no varargs forwarding is * needed; the kernel formatter is not...
- `qga_err` (function) `qga.c:210` `static void qga_err(const char *klass, const char *desc)`
- `qga_puts_resp` (function) `qga.c:218` `static void qga_puts_resp(void)`
- `qga_b64_encode` (function) `qga.c:231` `static void qga_b64_encode(const unsigned char *in, int n)`
- `qga_cmd_get_time` (function) `qga.c:281` `static void qga_cmd_get_time(void)`
- `qga_cmd_exec` (function) `qga.c:306` `static void qga_cmd_exec(const struct qga_pair *pairs, int n)` -- guest-exec runs a shell command line; output goes to the console (the `>` redirect still captures it).
- `qga_cmd_shutdown` (function) `qga.c:316` `static void qga_cmd_shutdown(const struct qga_pair *pairs, int n)`
- `qga_file_size` (function) `qga.c:329` `static int qga_file_size(const KFILE *f)`
- `qga_cmd_file_open` (function) `qga.c:334` `static void qga_cmd_file_open(const struct qga_pair *pairs, int n)`
- `qga_cmd_file_read` (function) `qga.c:360` `static void qga_cmd_file_read(const struct qga_pair *pairs, int n)`
- `qga_cmd_file_close` (function) `qga.c:384` `static void qga_cmd_file_close(const struct qga_pair *pairs, int n)`
- `qga_dispatch` (function) `qga.c:401` `static void qga_dispatch(struct qga_pair *pairs, int n)`
- `qga_poll` (function) `qga.c:446` `void qga_poll(void)` -- Accumulate bytes until a complete line, then parse and answer it.

## smp.c
Depends on: `headers/ap_stub.h`, `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/msr.h`, `headers/sched.h`, `headers/smp.h`
- `syscall_entry` (function) `smp.c:82` `extern void syscall_entry(void);` -- Per-AP kernel stack for the idle loop entry (the 2 KB stub stack is * too shallow for the loop's C frames plus...
- `lapic_read` (function) `smp.c:84` `static unsigned lapic_read(unsigned off)`
- `lapic_write` (function) `smp.c:87` `static void lapic_write(unsigned off, unsigned val)`
- `map_lapic` (function) `smp.c:108` `static int map_lapic(void)` -- Map the LAPIC so the BSP can program the ICR, and the APs can read their id registers.
- `ap_delay` (function) `smp.c:121` `static void ap_delay(void)`
- `lapic_calibrate` (function) `smp.c:150` `static void lapic_calibrate(void)`
- `ap_lapic_timer_start` (function) `smp.c:184` `static void ap_lapic_timer_start(void)` -- ifdef MINIOS_AP_TIMER
- `ap_lapic_timer_init` (function) `smp.c:190` `static void ap_lapic_timer_init(void)` -- endif
- `BSP` (function) `smp.c:238` `* were programmed only on the BSP (syscall_init runs in kmain), so * an AP's first sysretq loaded SS from a zeroed...`
- `smp_init` (function) `smp.c:305` `void smp_init(void)`
- `INIT` (function) `smp.c:323` `* INIT (edge-triggered): resets APs to wait-for-SIPI state. * QEMU 11 drops level-triggered INIT (delivery status...`

## tools/abi_stamp.c
Depends on: `progs/minios_abi.h`
- `main` (function) `tools/abi_stamp.c:14` `int main(void)`

## tools/boot_wl.py
Depends on: `kernel/time.c`
- `WlBoot.__init__` (method) `tools/boot_wl.py:68` `def __init__(self, cfg)`
- `WlBoot.fail` (method) `tools/boot_wl.py:75` `def fail(self, msg)`
- `WlBoot.close` (method) `tools/boot_wl.py:80` `def close(self)`
- `WlBoot.boot` (method) `tools/boot_wl.py:91` `def boot(self)`
- `WlBoot.snapshot` (method) `tools/boot_wl.py:107` `def snapshot(self, timeout)`
- `WlBoot.wait_prompt` (method) `tools/boot_wl.py:124` `def wait_prompt(self)`
- `WlBoot.send` (method) `tools/boot_wl.py:135` `def send(self, line)`
- `WlBoot.send_wait` (method) `tools/boot_wl.py:142` `def send_wait(self, line, timeout)`
- `WlBoot.setup` (method) `tools/boot_wl.py:154` `def setup(self)`
- `WlBoot.qmp` (method) `tools/boot_wl.py:165` `def qmp(self, obj)`
- `WlBoot.headless` (method) `tools/boot_wl.py:182` `def headless(self)`
- `WlBoot.proxy` (method) `tools/boot_wl.py:195` `def proxy(self)`
- `WlBoot.main` (method) `tools/boot_wl.py:226` `def main()`

## tools/check_abi_numbers.py
- `normalize` (function) `tools/check_abi_numbers.py:128` `def normalize(minios_name)`
- `parse_abi` (function) `tools/check_abi_numbers.py:132` `def parse_abi(path)`
- `parse_dispatch` (function) `tools/check_abi_numbers.py:143` `def parse_dispatch(path)`
- `main` (function) `tools/check_abi_numbers.py:156` `def main()`

## tools/check_addons.py
- `load_parser` (function) `tools/check_addons.py:22` `def load_parser()`
- `main` (function) `tools/check_addons.py:31` `def main()`

## tools/check_cohesion.py
- `load_cpg` (function) `tools/check_cohesion.py:23` `def load_cpg(path)` -- Load and parse the CPG JSON-LD file.
- `compute_cohesion` (function) `tools/check_cohesion.py:31` `def compute_cohesion(community_nodes, community_edges)` -- Compute cohesion as internal_edges / max_possible_edges.
- `extract_communities` (function) `tools/check_cohesion.py:42` `def extract_communities(cpg)` -- Extract communities and their internal edges from CPG.
- `main` (function) `tools/check_cohesion.py:58` `def main()`

## tools/check_complexity.py
- `count_symbols` (function) `tools/check_complexity.py:24` `def count_symbols(filepath)` -- Count top-level function and global variable definitions.
- `load_approval` (function) `tools/check_complexity.py:46` `def load_approval(policy_path)` -- Load explicit complexity approval from ARCH_POLICY.yaml.
- `main` (function) `tools/check_complexity.py:61` `def main()`

## tools/check_kb_sync.py
- `regenerate_kb` (function) `tools/check_kb_sync.py:24` `def regenerate_kb()` -- Attempt to regenerate KNOWLEDGE_BASE.md using readmenator.
- `main` (function) `tools/check_kb_sync.py:43` `def main()`

## tools/check_mutant_anchors.py
- `Config.bash_unquote` (method) `tools/check_mutant_anchors.py:26` `def bash_unquote(expr)` -- Collapse the escapes bash applies inside the MUTATIONS string.
- `Config.parse_mutations` (method) `tools/check_mutant_anchors.py:41` `def parse_mutations(text)` -- Extract (name, expression, target) triples from the MUTATIONS block.
- `Config.anchor_matches` (method) `tools/check_mutant_anchors.py:67` `def anchor_matches(repo, target, expr)` -- Apply the sed expression to a scratch copy; True when it changes it.
- `Config.main` (method) `tools/check_mutant_anchors.py:86` `def main()` -- Entry point: report anchors that change nothing and exit nonzero.

## tools/check_spin_discipline.py
- `Config.iter_functions` (method) `tools/check_spin_discipline.py:38` `def iter_functions(path)` -- Yield (name, first_line, body_lines) with a brace-depth split.
- `Config.check_file` (method) `tools/check_spin_discipline.py:64` `def check_file(path)` -- Return a list of violation strings for one translation unit.
- `Config.main` (method) `tools/check_spin_discipline.py:99` `def main(argv)` -- Walk the configured roots and fail closed on any violation.

## tools/check_surprising.py
- `load_cpg` (function) `tools/check_surprising.py:25` `def load_cpg(path)` -- Load and parse the CPG JSON-LD file.
- `build_graph` (function) `tools/check_surprising.py:33` `def build_graph(cpg)` -- Build adjacency list from CPG nodes and edges.
- `bfs_min_hops` (function) `tools/check_surprising.py:56` `def bfs_min_hops(nodes, edges, source, target_community, max_hops)` -- BFS from source to any node in target_community, returning hop count.
- `find_surprising_connections` (function) `tools/check_surprising.py:87` `def find_surprising_connections(nodes, edges, min_hops)` -- Find connections of min_hops or more between distinct communities.
- `main` (function) `tools/check_surprising.py:118` `def main()`

## tools/check_syscall_sanitize.py
- `Config.split_functions` (method) `tools/check_syscall_sanitize.py:69` `def split_functions(lines)` -- Yield (name, start, body_lines) triples using brace depth.
- `Config.checked_names` (method) `tools/check_syscall_sanitize.py:112` `def checked_names(body)` -- Return identifiers named inside sanitizer checks in a body.
- `Config.delegated_only` (method) `tools/check_syscall_sanitize.py:122` `def delegated_only(body, alias)` -- Decide whether an alias flows only into sanitizing callees.
- `Config.split_top_args` (method) `tools/check_syscall_sanitize.py:143` `def split_top_args(argtext)` -- Split a call argument list on top-level commas only.
- `Config.audit_body` (method) `tools/check_syscall_sanitize.py:162` `def audit_body(name, body)` -- Return violation strings for one function body.
- `Config.audit_file` (method) `tools/check_syscall_sanitize.py:217` `def audit_file(path)` -- Audit every handler in one file, return violation strings.
- `Config.main` (method) `tools/check_syscall_sanitize.py:228` `def main()` -- Entry point used by lint and CI.

## tools/clip_bridge.py
- `ClipBridgeConfig.valid_dst` (method) `tools/clip_bridge.py:41` `def valid_dst(name, cfg)` -- True when name is a safe guest path.
- `ClipBridgeConfig.printable_line` (method) `tools/clip_bridge.py:52` `def printable_line(line, cfg)` -- True when every char survives the kernel readline.
- `ClipBridgeConfig.build_plan` (method) `tools/clip_bridge.py:59` `def build_plan(text, dst, cfg)` -- Return (ok, lines, diagnostic) for carrying text to dst.
- `ClipBridgeConfig.main` (method) `tools/clip_bridge.py:84` `def main(argv)` -- Entry point: clip_bridge.py <src-file> <dst-name>.

## tools/doom_pwad.py
Imported by: `tests/test_doom_pwad.py`
- `PwadError.pad_tex` (method) `tools/doom_pwad.py:165` `def pad_tex(raw)` -- Return a texture or flat name padded to its 8-byte field.
- `PwadError.parse_grid` (method) `tools/doom_pwad.py:172` `def parse_grid(text)` -- Parse grid text into rows, refusing empty or ragged input.
- `PwadError.grid_extents` (method) `tools/doom_pwad.py:195` `def grid_extents(rows)` -- Return coordinate bounds of the lattice in map units.
- `PwadError.is_wall` (method) `tools/doom_pwad.py:203` `def is_wall(rows, row, col)` -- Treat out-of-bounds cells as solid wall so maps stay closed.
- `PwadError.flood_reachable` (method) `tools/doom_pwad.py:210` `def flood_reachable(rows)` -- Return the walkable set reachable from the player start tile.
- `PwadError.validate_grid` (method) `tools/doom_pwad.py:240` `def validate_grid(rows)` -- Enforce single player, single exit, and full reachability.
- `PwadError.cell_corners` (method) `tools/doom_pwad.py:269` `def cell_corners(row, col)` -- Return cell corners as (x0, x1, y_top, y_bottom) in map units.
- `PwadError.cell_class` (method) `tools/doom_pwad.py:279` `def cell_class(cell)` -- Classify a walkable cell: doors stand alone, styles never merge.
- `PwadError.label_regions` (method) `tools/doom_pwad.py:291` `def label_regions(rows)` -- Flood same-class walkable cells into region ids; walls stay -1.
- `PwadError.region_sector` (method) `tools/doom_pwad.py:326` `def region_sector(region, door_tag)` -- Map a labelled region to its sector record fields and wall skin.
- `PwadError.compile_geometry` (method) `tools/doom_pwad.py:371` `def compile_geometry(rows, exit_pos, wall_side)` -- Compile edges into vertexes, two-sided rooms and tagged doors.
- `PwadError.vertex` (method) `tools/doom_pwad.py:386` `def vertex(x, y)` -- Deduplicate lattice points shared by adjacent edges.
- `PwadError.compile_things` (method) `tools/doom_pwad.py:485` `def compile_things(rows)` -- Compile thing stamps into mapthing records in scan order.
- `PwadError.seg_angle` (method) `tools/doom_pwad.py:506` `def seg_angle(dx, dy)` -- Return the stored short angle for a seg direction vector.
- `PwadError.build_lumps` (method) `tools/doom_pwad.py:516` `def build_lumps(rows)` -- Compile a validated grid into the eleven E1M1 lump payloads.
- `PwadError.build_pwad` (method) `tools/doom_pwad.py:597` `def build_pwad(rows)` -- Assemble lump payloads into a complete PWAD byte string.
- `PwadError.read_pwad` (method) `tools/doom_pwad.py:616` `def read_pwad(data)` -- Split PWAD bytes into header fields and an ordered lump table.
- `PwadError.check_pwad` (method) `tools/doom_pwad.py:639` `def check_pwad(data)` -- Validate lump order, record sizes and cross-lump references.
- `PwadError.payload` (method) `tools/doom_pwad.py:650` `def payload(name)` -- Slice one lump payload out of the file image.
- `PwadError.check_multiple` (method) `tools/doom_pwad.py:655` `def check_multiple(name, fmt)` -- Require the lump length to hold whole records only.
- `PwadError.cmd_build` (method) `tools/doom_pwad.py:816` `def cmd_build(grid_path, out_path)` -- Build a PWAD from a grid file, refusing to write on any error.
- `PwadError.cmd_check` (method) `tools/doom_pwad.py:826` `def cmd_check(path)` -- Validate a PWAD file and report its lump census on success.
- `PwadError.main` (method) `tools/doom_pwad.py:834` `def main(argv)` -- Dispatch the build, check and info verbs with host-safe errors.

## tools/gdb_repro.py
Depends on: `kernel/time.c`
- `rs` (function) `tools/gdb_repro.py:23` `def rs(m, t)`
- `main` (function) `tools/gdb_repro.py:27` `def main()`
- `send` (function) `tools/gdb_repro.py:65` `def send(line)`
- `quit_doom` (function) `tools/gdb_repro.py:70` `def quit_doom()`

## tools/gen_desktop_pngs.py
- `write_atomic` (function) `tools/gen_desktop_pngs.py:69` `def write_atomic(img, path)`
- `main` (function) `tools/gen_desktop_pngs.py:75` `def main()`

## tools/gen_icons.py
- `make_png` (function) `tools/gen_icons.py:179` `def make_png(pixels, palette, width, height)` -- Create a minimal indexed-colour PNG from pixel indices and a palette.
- `make_chunk` (function) `tools/gen_icons.py:209` `def make_chunk(chunk_type, data)`
- `main` (function) `tools/gen_icons.py:214` `def main()`

## tools/gen_zip_fixtures.py
- `write_zip` (function) `tools/gen_zip_fixtures.py:28` `def write_zip(path, entries)` -- entries: list of (name, data_or_None).  data None marks a directory.
- `main` (function) `tools/gen_zip_fixtures.py:42` `def main()`

## tools/kernel_feature_survey.py
- `SurveyConfig.iter_sources` (method) `tools/kernel_feature_survey.py:34` `def iter_sources(root)` -- Yield C source paths under root, skipping vendored and cache dirs.
- `SurveyConfig.find_fnptr_hits` (method) `tools/kernel_feature_survey.py:43` `def find_fnptr_hits(path, text)` -- Return line numbers declaring function pointers.
- `SurveyConfig.find_asm_constraints` (method) `tools/kernel_feature_survey.py:49` `def find_asm_constraints(path, text)` -- Return sorted constraint letters used in extended asm.
- `SurveyConfig.count_params` (method) `tools/kernel_feature_survey.py:59` `def count_params(params)` -- Count parameters, treating void and empty as zero.
- `SurveyConfig.survey` (method) `tools/kernel_feature_survey.py:67` `def survey(root)` -- Collect findings per category across all sources.
- `SurveyConfig.render_text` (method) `tools/kernel_feature_survey.py:103` `def render_text(findings)` -- Render findings as plain text.
- `SurveyConfig.main` (method) `tools/kernel_feature_survey.py:122` `def main(argv)` -- Entry point for the survey tool.


Next: [API_p19.md](API_p19.md)
