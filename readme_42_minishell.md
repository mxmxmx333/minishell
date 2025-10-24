# minishell (42)

Eine kleine, interaktive Shell nach POSIX‑Vorbild – geschrieben in C – mit Quote‑Handling, Umgebungsvariablen‑Expansion, Pipes und Umleitungen sowie den geforderten Builtins.

---

## Voraussetzungen
- **make**
- **clang**
- **libreadline** (Entwicklerheaders & Runtime)

**Ubuntu (24.04)**
```bash
sudo apt update
sudo apt install -y build-essential clang libreadline-dev
```
> Laufzeitpaket ist in der Regel `libreadline8` und kommt automatisch mit.

---

## Build
```bash
make            # Release/Default
make DEBUG=1    # mit Debug-Flags
make SAN=1      # mit AddressSanitizer (ggf. langsamer)
make re         # clean + build
make clean      # Objektdateien entfernen
make fclean     # auch Binary entfernen
```
Variablen (falls euer Makefile das unterstützt):
```bash
make CC=clang CFLAGS="-Wall -Wextra -Werror"
```

---

## Start
```bash
./minishell              # interaktiv
./minishell < script.sh  # nicht-interaktiv
```

---

## Features (Pflichtteil)
- **Prompt** mit interaktivem Editieren via **readline** (History, `↑/↓`).
- **Lexing/Parsing** von Tokens: `cmd` `arg` `|` `<` `>` `>>` `<<`.
- **Quotes**: `'single'` (wörtlich), `"double"` (mit Expansion).
- **Expansion**: `$VAR`, `$?` (Exitcode des letzten Befehls).
- **Redirections**: `<` (in), `>` (truncate), `>>` (append), `<<` (heredoc).
- **Pipes**: beliebige Pipeline‑Längen (`cmd1 | cmd2 | ...`).
- **PATH‑Suche**: `execve` mit PATH‑Fallback; 127 bei „command not found“, 126 bei „permission denied“.
- **Signale (interaktiv)**:
  - `Ctrl-C` (SIGINT): Neue Zeile + neuer Prompt, Exitcode **130**.
  - `Ctrl-\` (SIGQUIT): **ignoriert** im Elternprozess.
  - `Ctrl-D` (EOF): Shell beendet sich mit letztem Status.

### Builtins (ohne Fork, außer in Pipeline)
- `echo [-n] [args…]`
- `cd [dir]` (ohne arg → `$HOME`), setzt `PWD`/`OLDPWD`.
- `pwd`
- `export [KEY[=VAL] …]` (ohne Arg: sortierte Liste)
- `unset KEY…`
- `env` (aktuelles Environment, nur mit `export` veränderbar)
- `exit [status]`

> Builtins innerhalb einer **Pipeline** werden in einem Kindprozess ausgeführt; Änderungen an der Umgebung wirken daher nur im Elternprozess, wenn es **kein** Pipeline‑Kontext ist – so wie in Bash.

---

## Heredoc‑Details (`<<`)
- Delimiter **unquoted** → **Expansion aktiv** (`$VAR`, `$?`).
- Delimiter **quoted** (`'EOF'`/`"EOF"`) → **keine Expansion**.
- Mehrere Umleitungen pro Kommando sind erlaubt; **die letzte gewinnt**.

---

## Exit‑Status (vereinbart)
- `0`: Erfolg
- `1`: Allgemeiner Fehler/Builtin‑Fehler
- `126`: Datei gefunden, aber **nicht ausführbar**
- `127`: **Command not found**
- `130`: durch **SIGINT** beendet (z. B. Ctrl‑C)

---

## Beispielsession
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

## Projektstruktur (Beispiel)
```
.
├─ includes/
│  └─ minishell.h
├─ src/
│  ├─ main.c
│  ├─ lexer/ …
│  ├─ parser/ …
│  ├─ exec/ (pipes, redirs, execve)
│  ├─ builtins/ (echo, cd, …)
│  ├─ env/ (export, unset, env‑List)
│  └─ signals/
├─ Makefile
└─ README.md
```

---

## Einschränkungen (bewusst **nicht** implementiert)
- Job‑Control (`fg`, `bg`, `jobs`), `&&`, `||`, `;`, Subshells `( … )`, Backticks `` `cmd` ``.
- Globbing/Wildcards (`*`, `?`) – nur wenn als Bonus implementiert.
- Prozesssubstitution, Brace‑Expansion, erweiterte `bash`‑Features.

> Haltet diese Liste aktuell je nach Bonusumfang.

---

## Entwicklung & Testing
- Speicherfehler prüfen:
```bash
make SAN=1   # AddressSanitizer einschalten
```
- Leaks (Linux): `valgrind --leak-check=full ./minishell` (falls erlaubt).
- Non‑interactive Tests (Pipelines/Redirs):
```bash
echo 'echo hi | wc -c' | ./minishell
```

---

## Troubleshooting
- **readline fehlt** → `sudo apt install libreadline-dev` und neu bauen.
- **STRG‑C reagiert nicht** → Signal‑Handler nur im Elternprozess setzen; Kinder sollten Default‑Handler haben.
- **$PATH wirkt nicht** → `env -i ./minishell` testen; PATH ggf. beim Start initialisieren.

---

## Autoren
- _Team <euer‑teamname>_  —  42 Vienna

> Dieses README ist für die 42‑Korrektur geschrieben: klar, kurz, reproduzierbar. Haltet es synchron mit dem Codestand (Builtins, Bonus, Make‑Targets).

