# Security Findings

## CRITICAL (23)

- `mcp/mutate_mcp.sh:85` -- Command injection via eval — can execute arbitrary commands [CWE-78]
  Fix: Avoid shell=True and string-built commands; use argument arrays and input allowlists.
- `tools/check_abi_numbers.py:122` -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_abi_numbers.py:123` -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_abi_numbers.py:124` -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_fork_stubs.py:19` (in `Config`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_fork_stubs.py:24` (in `handler_body`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_syscall_sanitize.py:22` (in `Config`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_syscall_sanitize.py:25` (in `Config`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_syscall_sanitize.py:29` (in `Config`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_syscall_sanitize.py:30` (in `Config`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_syscall_sanitize.py:35` (in `Config`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_syscall_sanitize.py:36` (in `Config`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_syscall_sanitize.py:37` (in `Config`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_syscall_sanitize.py:74` (in `split_functions`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/kernel_feature_survey.py:24` (in `SurveyConfig`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/kernel_feature_survey.py:25` (in `SurveyConfig`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/kernel_feature_survey.py:26` (in `SurveyConfig`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/kernel_feature_survey.py:27` (in `SurveyConfig`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/kernel_feature_survey.py:28` (in `SurveyConfig`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/kernel_feature_survey.py:29` (in `SurveyConfig`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/kernel_feature_survey.py:30` (in `SurveyConfig`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/kernel_feature_survey.py:31` (in `SurveyConfig`) -- Use of eval/exec — can lead to arbitrary code execution [CWE-95]
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/mutate.sh:349` (in `find_index`) -- Command injection via eval — can execute arbitrary commands [CWE-78]
  Fix: Avoid shell=True and string-built commands; use argument arrays and input allowlists.

## HIGH (304)

- `kernel/cvm_host.c:38` (in `n_strcpy`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/doomgeneric/i_system.c:274` (in `ZenityAvailable`) -- Command injection via system() — use execve instead [CWE-78]
  Fix: Avoid shell=True and string-built commands; use argument arrays and input allowlists.
- `progs/doomgeneric/i_system.c:342` (in `M_snprintf`) -- Command injection via system() — use execve instead [CWE-78]
  Fix: Avoid shell=True and string-built commands; use argument arrays and input allowlists.
- `progs/file/file.c:185` (in `strcpy`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/file/file.c:186` (in `strcpy`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/file/file.c:398` (in `nk_label`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/file/file.c:403` (in `nk_label`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/file/file.c:408` (in `nk_label`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/file/file.c:413` (in `nk_label`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/file/file.c:467` (in `file_selftest`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/file/file.c:468` (in `file_selftest`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/file/file.c:469` (in `file_selftest`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/file/file.c:470` (in `file_selftest`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/file/file.c:471` (in `file_selftest`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/file/file.c:472` (in `file_selftest`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/file/file.c:544` (in `nk_theme_apply`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/paint/paint.c:959` (in `nk_theme_apply`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/paint/paint.c:996` (in `strcpy`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_ents.c:797` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_ents.c:805` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:315` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:316` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:320` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:321` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:556` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:558` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:559` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:563` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:564` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:648` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:1250` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:1256` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_main.c:1357` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_parse.c:85` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_parse.c:91` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_parse.c:155` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_parse.c:162` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_parse.c:418` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_parse.c:427` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_parse.c:434` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_parse.c:448` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_parse.c:528` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_scrn.c:495` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_scrn.c:1092` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_tent.c:161` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_view.c:263` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_view.c:281` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/cl_view.c:285` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/console.c:437` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/console.c:438` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/console.c:649` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/console.c:651` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/console.c:652` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/console.c:669` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/keys.c:178` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/keys.c:261` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/keys.c:321` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/keys.c:343` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/keys.c:522` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/keys.c:599` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/keys.c:601` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:421` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:422` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2058` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2283` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2332` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2411` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2444` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2581` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2585` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2589` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2641` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2651` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2668` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2670` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:2680` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3315` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3429` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3431` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3490` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3491` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3502` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3503` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3547` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3572` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3628` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3632` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3637` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3642` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3643` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/menu.c:3680` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/qmenu.c:667` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/qmenu.c:670` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/snd_dma.c:243` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/snd_dma.c:263` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/snd_dma.c:279` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/snd_dma.c:606` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/snd_dma.c:614` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/snd_dma.c:1170` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/snd_dma.c:1171` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/snd_dma.c:1174` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/client/snd_mem.c:125` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_chase.c:102` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_cmds.c:34` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_cmds.c:57` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_cmds.c:58` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_cmds.c:790` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_cmds.c:793` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_cmds.c:905` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_cmds.c:906` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_cmds.c:907` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_cmds.c:918` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_cmds.c:925` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:377` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1031` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1642` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1659` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1661` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1674` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1682` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1684` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1692` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1697` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1709` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1717` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1721` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1729` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1733` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1759` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1760` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1765` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1773` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1784` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:1787` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2223` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2251` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2257` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2265` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2267` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2269` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2272` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2274` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2276` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2278` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2294` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2305` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2306` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2312` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2318` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2320` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2333` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2338` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2344` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2346` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2367` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2368` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2373` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2378` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2379` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2381` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2383` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2410` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2416` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2422` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2428` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2434` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2441` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:2640` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3089` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3155` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3156` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3326` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3329` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3336` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3342` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3491` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3502` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3513` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3525` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3537` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3549` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3556` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3563` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3658` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3662` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3666` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3670` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3674` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3678` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3682` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3686` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3808` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3837` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3839` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3855` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3865` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3875` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3879` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3898` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3900` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3912` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3923` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3927` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:3972` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_ctf.c:4011` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_save.c:451` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_spawn.c:810` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/g_utils.c:398` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/p_client.c:1315` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/p_hud.c:246` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/p_hud.c:257` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/p_menu.c:121` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/p_menu.c:131` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/p_menu.c:139` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/p_menu.c:143` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/p_menu.c:145` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/p_menu.c:147` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/q_shared.c:923` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ctf/q_shared.c:1335` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:34` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:57` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:58` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:722` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:725` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:808` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:809` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:810` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:821` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:828` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:885` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:893` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_cmds.c:897` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_save.c:474` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_spawn.c:812` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_svcmds.c:249` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_svcmds.c:251` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/g_utils.c:396` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/p_client.c:1370` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/p_hud.c:234` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/p_hud.c:245` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/q_shared.c:926` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/game/q_shared.c:1354` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/net/net_unix.c:154` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/net/net_win.c:220` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/other/vid_lib.c:301` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:318` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:320` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:339` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:340` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:463` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:470` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:472` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:474` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:588` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:589` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:591` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:660` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmd.c:678` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/cmodel.c:629` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/common.c:121` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/common.c:1038` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/files.c:490` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/files.c:497` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/files.c:522` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/files.c:528` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/qcommon/files.c:745` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ref_gl/gl_image.c:1254` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ref_gl/gl_model.c:222` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ref_gl/gl_rmain.c:1180` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ref_gl/gl_rmain.c:1183` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ref_gl/gl_rmisc.c:115` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ref_gl/qgl_system.c:3304` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ref_soft/r_image.c:422` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ref_soft/r_image.c:463` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ref_soft/r_misc.c:567` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/ref_soft/r_model.c:131` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_ccmds.c:254` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_ccmds.c:261` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_ccmds.c:263` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_ccmds.c:388` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_ccmds.c:389` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_ccmds.c:445` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_ccmds.c:804` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_ccmds.c:813` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_game.c:201` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_init.c:195` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_init.c:198` -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_init.c:203` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_init.c:209` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_init.c:222` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_init.c:223` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_init.c:406` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_init.c:427` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_init.c:435` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_main.c:121` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_main.c:122` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_main.c:135` -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_main.c:460` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/quake2generic/quake2generic/server/sv_main.c:461` -- Buffer overflow risk: strcat — use strncat instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `progs/topogpt3/topogpt3.c:30` (in `sprintf`) -- Buffer overflow risk: sprintf — use snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `tests/test_driver.c:68` (in `strcpy`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `tests/test_driver.c:114` (in `snprintf`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `tests/test_driver.c:127` (in `snprintf`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- `tests/test_driver.c:130` (in `snprintf`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.

## MEDIUM (19)

- `mcp/mutate_mcp.sh:16` -- Command substitution with user input — potential injection [CWE-78]
  Fix: Avoid shell=True and string-built commands; use argument arrays and input allowlists.
- `mcp/mutate_mcp.sh:79` -- Command substitution with user input — potential injection [CWE-78]
  Fix: Avoid shell=True and string-built commands; use argument arrays and input allowlists.
- `mcp/test_minios_mcp.py:697` (in `setUpClass`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `mcp/test_minios_mcp.py:775` (in `test_install_multi_chunk_reassembly`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `mcp/test_minios_mcp.py:828` (in `setUpClass`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `mcp/test_minios_mcp.py:837` (in `setUpClass`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `tools/gdb_repro.py:43` (in `main`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `tools/gdb_repro.py:59` (in `main`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `tools/gen_desktop_pngs.py:95` (in `main`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `tools/gen_desktop_pngs.py:102` (in `main`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `tools/mkpak1.py:37` (in `main`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `tools/mutate.sh:34` -- Command substitution with user input — potential injection [CWE-78]
  Fix: Avoid shell=True and string-built commands; use argument arrays and input allowlists.
- `tools/probe_compute_vga.py:117` (in `dump`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `tools/probe_compute_vga.py:118` (in `dump`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `tools/test_bdd.sh:1167` (in `http_fixture_stop`) -- Command substitution with user input — potential injection [CWE-78]
  Fix: Avoid shell=True and string-built commands; use argument arrays and input allowlists.
- `tools/test_gui_wm.py:229` (in `main`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `tools/test_gui_wm.py:318` (in `main`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `tools/tls_test.py:217` (in `gen_header`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
- `tools/tls_test.py:237` (in `gen_header`) -- Path traversal risk — file operation with variable path [CWE-22]
  Fix: Canonicalize paths and confine file access to an allowlisted base directory.
