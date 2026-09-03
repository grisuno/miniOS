"""tools/extract_shell.py -- Plan for Phase 6.1 shell extraction.

This script documents the shell extraction plan. The actual extraction
requires careful handling of cross-dependencies between shell code and
kernel internals.

DEPENDENCIES (shell -> kernel):
  VFS:       kfopen, kfclose, kfread, kfwrite, kfgets, kfputs, kfseek, kftell
  FS:        fs_resolve, fs_dir_exists, fs_is_dir
  Ramdisk:   ramdisk_open, ramdisk_read, ramdisk_list, ramdisk_create
  MiniFS:    minifs_resolve_path, minifs_stat, minifs_read, minifs_mkdir_p,
             minifs_create, minifs_write, minifs_sync, minifs_is_mounted,
             minifs_list
  Process:   k_exec_user, k_run_rel, k_spawn, k_register_program,
             k_register_process, k_register_symbol, elf_load, load_exec_elf
  Audio:     pcspk_tone, pcspk_set_volume, pcspk_get_volume
  Graphics:  vga_fb_* functions (desktop, WM, GFX_SET_TITLE syscall)
  Hashing:   xxh64_* functions
  Network:   net_*, tls_* functions
  Compress:  lzss_*, lz4_*, zip_* functions
  Crypto:    aes_* functions
  Editor:    edit_* functions
  Other:     kprintf, kmemset, kmemcpy, kstrlen, kstrcmp, kstrncmp,
             kstrcpy, kstrncpy, kstrchr, kstrstr, kstrncat,
             redirect_begin, redirect_commit, redirect_suspend, redirect_resume

FUNCTIONS TO EXTRACT (38 functions, ~2070 lines):
  Shell core:    shell_init, shell_run, shell_prompt, shell_parse,
                 shell_exec_builtin, shell_report_exit, shell_report
  Line editing:  shell_readline, shell_readline_buf, shell_readline_hist,
                 shell_line_repaint, shell_line_insert, shell_line_backspace,
                 shell_line_delete, shell_line_kill_front, shell_line_kill_tail,
                 shell_line_kill_word, shell_line_hist_nav, shell_hist_show
  Completion:    shell_complete_replace
  Redirect:      shell_take_redirect
  Command run:   shell_run_any, shell_run_file, shell_run_elf_buf,
                 shell_run_elf_file, shell_run_elf_minifs, shell_run_cvm
  Resolution:    shell_resolve_run, shell_file_is_real
  Builtins:      shell_cmd_edit, shell_cmd_poweroff, shell_cmd_gfx,
                 shell_cmd_wm, shell_cmd_hash, shell_parse_vol
  Launch:        shell_queue_launch, shell_pending_cmd, shell_pending_len
  Data:          shell_run_dirs, shell_hist, shell_hist_count,
                 shell_hist_idx, cmd_buf

BUILD INTEGRATION:
  Add shell.c to the Makefile kernel object list.
  The shell.h header is already included by kernel.h.
"""
