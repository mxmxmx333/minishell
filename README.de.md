<p align="right">English | <a href="README.de.md">Deutsch</a></p>

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

## Nicht implementiert

Job‑Control, `&&`/`||`/`;`, Subshells, Backticks, Globbing (falls kein Bonus), etc.

## Troubleshooting

* `libreadline` fehlt → `sudo apt install libreadline-dev`
* `tgetent`‑Fehler → `-lncurses`/`-ltinfo` linken
* PATH prüfen: `env -i ./minishell`

## Autoren

* *Team <euer‑Teamname>* — 42 Vienna
