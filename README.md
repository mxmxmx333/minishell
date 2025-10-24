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
├─ includes/
│  └─ minishell.h
├─ src/
│  ├─ main.c
│  ├─ lexer/
│  ├─ parser/
│  ├─ exec/        # pipes, redirs, execve
│  ├─ builtins/    # echo, cd, …
│  ├─ env/
│  └─ signals/
├─ libft/
├─ Makefile
└─ README.md
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

---

# README.de.md (Deutsche Version)

<p align="right"><a href="README.md">English</a> | Deutsch</p>

# minishell (42)

Eine kleine, interaktive Shell nach POSIX‑Vorbild – geschrieben in C – mit Quote‑Handling, Umgebungsvariablen‑Expansion, Pipes und Umleitungen sowie den geforderten Builtins.

## Voraussetzungen

* **make**
* **clang**
* **libreadline** (Developer‑Headers & Runtime)

**Ubuntu (24.04)**

```bash
sudo apt update
sudo apt install -y build-essential clang libreadline-dev
```

## Build

```bash
make         # baut libft (./libft) und minishell
make re      # clean + build
make clean   # löscht Projekt-.o (auch in libft)
make fclean  # löscht .o + Binary (auch in libft)
make my      # baut und löscht danach die Projekt-.o ("myclean")
make myclean # löscht nur die Projekt-.o
```

Compiler/Flags anpassen (optional):

```bash
make CC=clang
make CFLAGS="-Wall -Wextra -Werror -g -I./inc -I./libft/inc"
```

**Linking:** Standard `LDFLAGS = -L./libft -lft -lreadline`. Falls der Linker über `tgetent`/`terminfo` meckert, zusätzlich **`-lncurses`** oder **`-ltinfo`** anhängen.

## Start

```bash
./minishell              # interaktiv
./minishell < script.sh  # nicht-interaktiv
```

## Features (Pflichtteil)

* Prompt mit **readline** (History, ↑/↓)
* Tokens: `cmd` `arg` `|` `<` `>` `>>` `<<`
* Quotes: `'single'` (wörtlich), `"double"` (mit Expansion)
* Expansion: `$VAR`, `$?`
* Umleitungen: `<`, `>`, `>>`, `<<`
* Pipelines beliebiger Länge
* PATH‑Suche via `execve`; **127** bei „command not found“, **126** bei „permission denied“
* Signale (interaktiv): Ctrl‑C → neuer Prompt, **130**; Ctrl‑\ ignoriert; Ctrl‑D beendet

### Builtins (ohne Fork, außer in Pipeline)

`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## Heredoc (`<<`)

* Unquoted Delimiter → Expansion aktiv
* Quoted Delimiter → keine Expansion
* Bei mehreren Umleitungen gewinnt die letzte

## Exit‑Status

`0` Erfolg • `1` Fehler • `126` nicht ausführbar • `127` not found • `130` SIGINT

## Beispiel

```console
$ echo hello | tr a-z A-Z > out.txt
$ cat < out.txt
HELLO
```

## Struktur (Beispiel)

```
.
├─ includes/
├─ src/
│  ├─ lexer/ parser/ exec/ builtins/ env/ signals/
├─ libft/
└─ Makefile
```

## Nicht implementiert

Job‑Control, `&&`/`||`/`;`, Subshells, Backticks, Globbing (falls kein Bonus), etc.

## Troubleshooting

* `libreadline` fehlt → `sudo apt install libreadline-dev`
* `tgetent`‑Fehler → `-lncurses`/`-ltinfo` linken
* PATH prüfen: `env -i ./minishell`

## Autoren

* *Team <euer‑Teamname>* — 42 Vienna
