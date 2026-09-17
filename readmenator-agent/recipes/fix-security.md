# Recipe: Fix a Security Finding

- `mcp/mutate_mcp.sh:85` [critical] S001: Command injection via eval — can execute arbitrary commands
  Fix: Avoid shell=True and string-built commands; use argument arrays and input allowlists.
- `tools/check_abi_numbers.py:122` [critical] PY002: Use of eval/exec — can lead to arbitrary code execution
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- `tools/check_abi_numbers.py:123` [critical] PY002: Use of eval/exec — can lead to arbitrary code execution
  Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.

Verify: `readmenator . --audit && grep -c 'CRITICAL\|HIGH' readmenator-agent/SECURITY.md`
