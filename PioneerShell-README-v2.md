# pish — A Unix Shell in C

A custom Unix shell implemented from scratch in C, supporting command execution, built-in commands, persistent history, and both interactive and batch (script) modes.

---

## Features

- **Command execution** — Parses and runs external programs using `fork()` and `execvp()`
- **Built-in commands** — `cd`, `exit`, and `history` handled directly by the shell
- **Persistent history** — All commands are saved to `~/.pish_history` and indexed for review
- **Batch / script mode** — Accepts a shell script file as input and executes it non-interactively
- **Interactive prompt** — Custom prompt rendered in interactive mode; suppressed in batch mode

---

## How It Works

pish runs a read-eval-print loop (REPL):

1. **Read** — Reads a line of input from `stdin` or a script file
2. **Parse** — Tokenizes the input into a `pish_arg` struct using whitespace as delimiters
3. **Run** — Handles built-ins internally; forks a child process for all other commands
4. **History** — Appends each command to `~/.pish_history` in interactive mode

Child processes are created with `fork()` and the parent calls `wait()` to prevent zombie processes.

---

## Build & Run

```bash
# Compile
gcc -o pish pish.c pish_history.c

# Interactive mode
./pish

# Batch / script mode
./pish script.sh
```

---

## Example Session

```
▶  ls
enigma.c  pish.c  pish.h  pish_history.c

▶  cd src

▶  history
1 ls
2 cd src

▶  exit
```

---

## File Structure

| File | Description |
|---|---|
| `pish.c` | Core shell logic — REPL, parsing, fork/exec |
| `pish.h` | Shared header — `pish_arg` struct and function declarations |
| `pish_history.c` | History file management — read/write `~/.pish_history` |

---

## Concepts Demonstrated

- Process creation and management with `fork()`, `execvp()`, `wait()`
- File I/O for persistent command history using `fopen`, `fgets`, `fprintf`
- String tokenization with `strtok()`
- Struct-based command representation (`pish_arg`)
- Dual-mode execution (interactive vs. batch) via a single flag

---

## Tech
**Language:** C  
**Environment:** Linux / Unix  
**Build:** GCC
