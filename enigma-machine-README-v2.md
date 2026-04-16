# Enigma Machine

A software simulation of the WWII Enigma cipher machine, implemented in C. Models the rotor-based substitution cipher with configurable rotor selection, ordering, and rotation — run entirely from the command line.

---

## Features

- **8 historical rotors** — Includes wiring tables for all 8 standard Enigma rotors (I–VIII)
- **Configurable rotor selection** — Choose any combination of rotors and how many to use
- **Rotor rotation** — Rotate rotors by any number of positions before encryption
- **Encrypt & Decrypt** — Encrypt a plaintext message or reverse the process to recover the original
- **Case-insensitive input** — Handles both uppercase and lowercase letters; non-alpha characters pass through unchanged

---

## How It Works

Each character passes through the rotor stack in sequence:

1. The character is converted to a 0–25 index
2. It passes forward through each rotor, which substitutes it using that rotor's wiring table
3. For decryption, the inverse substitution is applied — each rotor is searched in reverse to find the original index

Rotors are pre-rotated before any encryption begins, shifting each wiring table by the specified number of positions.

---

## Build & Run

```bash
gcc -o enigma enigma.c
```

**Usage:**
```
./enigma <mode> <message> <num_rotors> <rotor_indices> <rotations>
```

| Argument | Description |
|---|---|
| `mode` | `e` to encrypt, `d` to decrypt |
| `message` | The message to process (use quotes for spaces) |
| `num_rotors` | How many rotors to use |
| `rotor_indices` | Space-separated rotor numbers (1–8) in quotes |
| `rotations` | How many positions to rotate all rotors before processing |

---

## Example

```bash
# Encrypt
./enigma e "HELLO" 3 "1 2 4" 0
Encrypted message: MFNCU

# Decrypt with same settings
./enigma d "MFNCU" 3 "1 2 4" 0
Decrypted message: HELLO
```

---

## Concepts Demonstrated

- Rotor-based substitution cipher with configurable wiring tables
- Dynamic memory allocation with `malloc` and full cleanup
- Inverse lookup via linear search for decryption
- Modular arithmetic for rotor rotation
- Command-line argument parsing in C

---

## Tech
**Language:** C  
**Environment:** Linux / Unix  
**Build:** GCC
