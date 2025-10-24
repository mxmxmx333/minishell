<p align="right">English | <a href="README.de.md">Deutsch</a></p>

# minishell (42)

A small interactive POSIX‑like shell written in C. Supports tokenization, quoting, environment expansion, pipes, redirections, and the required builtins.

---

## Requirements

* **make**
* **clang** (or `cc`)
* **libreadline** (headers + runtime)

**Ubuntu 24.04**

```bash
sudo apt update
sudo apt install -y build-essential clang libreadline-dev
```

> The runtime (`libreadline8`) is usually pulled in automatically.

---

## Build

```bash
make         # builds libft (./libft) and minishell
make re      # clean + build
make clean   # remove project object files (also in libft)
make fclean  # remove objects + binary (also in libft)
make my      # build and then remove project .o files (via "myclean")
make myclean # remove only the project .o files
```

**Tweak compiler/flags (optional):**

```bash
make CC=clang
make CFLAGS="-Wall -Wextra -Werror -g -I./inc -I./libft/inc"
```

**Linking:** default `LDFLAGS = -L./libft -lft -lreadline`. If the linker complains about `tgetent`/terminfo, also link **`-lncurses`** or **`-ltinfo`**.

---

## Run

```bash
./minishell              # interactive
./minishell < script.sh  # non-interactive
```

---

## Features (mandatory part)

* **Prompt** and interactive line editing via **readline** (history, ↑/↓).
* **Tokens:** `cmd` `arg` `|` `<` `>` `>>` `<<`.
* **Quotes:** `'single'` (verbatim) and `"double"` (with expansion).
* **Expansion:** `$VAR`, `$?` (exit code of the last command).
* **Redirections:** `<` (in), `>` (truncate), `>>` (append), `<<` (heredoc).
* **Pipelines:** arbitrary length (`cmd1 | cmd2 | ...`).
* **PATH lookup:** `execve` with PATH fallback; returns **127** on "command not found", **126** on "permission denied".
* **Signals (interactive):**

  * `Ctrl-C` (SIGINT): new line + new prompt, exit code **130**.
  * `Ctrl-\` (SIGQUIT): **ignored** in the parent.
  * `Ctrl-D` (EOF): exit with last status.

### Builtins (no fork unless in a pipeline)

* `echo [-n] [args…]`
* `cd [dir]` (no arg → `$HOME`), updates `PWD`/`OLDPWD`
* `pwd`
* `export [KEY[=VAL] …]` (no args → sorted list)
* `unset KEY…`
* `env`
* `exit [status]`

> Builtins inside a **pipeline** run in a child process; environment changes only affect the parent when **not** in a pipeline — just like in bash.

---

## Heredoc (`<<`)

* **Unquoted** delimiter → **expansion enabled** (`$VAR`, `$?`).
* **Quoted** delimiter (`'EOF'`/`"EOF"`) → **no expansion**.
* Multiple redirections per command are supported; **last one wins**.

---

## Exit status (convention)

* `0`   success
* `1`   general/builtin error
* `126` found but **not executable**
* `127` **command not found**
* `130` terminated by **SIGINT** (e.g., Ctrl‑C)

---

## Example session

```console
$ echo hello | tr a-z A-Z > out.txt
$ cat < out.txt
HELLO
$ export NAME=World
$ echo "hi, $NAME"
hi, World
$ echo $?
0
$ cd /nope
minishell: cd: /nope: No such file or directory
$ echo $?
1
```

---

## Project layout (example)

```
.
├─ inc/                # Header
├─ libft/              # Eigene Lib (Headers + Sources)
├─ src/
│  ├─ builtins/        # echo, cd, …
│  ├─ console/         # Prompt, History
│  ├─ errors/          # Fehlermeldungen
│  ├─ execution/       # execve, Pipes, Redirs
│  ├─ expander/        # $VAR, $?
│  ├─ initialization/  # Environment, Start
│  ├─ lexer/           # Tokenizer, Here-Doc
│  ├─ memory/          # Cleanup
│  └─ parser/          # AST/Executable
├─ Makefile
├─ README.md
└─ readline.supp       # (Valgrind-Suppressions, falls genutzt)

```

---

## Not implemented (by design)

* Job control (`fg`, `bg`, `jobs`), `&&`, `||`, `;`, subshells `( … )`, backticks `` `cmd` ``.
* Globbing (`*`, `?`) unless done as bonus.
* Process substitution, brace expansion, advanced bash features.

---

## Development & testing

* Check for memory issues (if allowed): AddressSanitizer via Makefile flags (if supported) or `valgrind --leak-check=full ./minishell`.
* Non‑interactive tests (pipes/redirs):

```bash
echo 'echo hi | wc -c' | ./minishell
```

---

## Troubleshooting

* **readline missing** → `sudo apt install libreadline-dev` and rebuild.
* **Ctrl‑C ignored** → install signal handlers only in the parent; children use defaults.
* **PATH not applied** → test with `env -i ./minishell`; initialize PATH on startup if needed.
* **Linker error for `tgetent`** → add `-lncurses` or `-ltinfo` to `LDFLAGS`.

---

## Authors

* *Team <your-team-name>* — 42 Vienna

> This README targets the 42 evaluation: concise and reproducible. Keep it in sync with your code (builtins, bonus, Make targets).
