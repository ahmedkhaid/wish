# wish

`wish` is a small Unix-style command-line shell written in C. It reads commands
from standard input, starts external programs, and supports command history,
output redirection, and a single pipeline.

## Requirements

- A Unix-like system
- GCC or another C compiler
- Executable programs available under `/usr/bin`

## Build

Compile the shell and its history module:

```sh
gcc -Wall -Wextra -o wish wish.c history.c
```

Then start it:

```sh
./wish
```

The prompt is:

```text
wish>
```

## Usage

Enter a command by name, followed by its arguments:

```text
wish> ls -l
wish> echo hello
```

The shell searches for commands directly under `/usr/bin` and will not run
commands from another directory or a custom `PATH`.

### Built-in commands

- `cd <directory>` changes the shell's current working directory. Provide
  exactly one directory argument.
- `exit` ends the shell.

### Command history

Run `history` to print the commands entered during the current shell session:

```text
wish> history
ls
history
```

The history stores up to 100 commands and does not persist between runs.

### Output redirection

Redirect a command's standard output to a file with `>`:

```text
wish> ls -l > listing.txt
```

The destination file is created or overwritten.

### Pipelines

Connect two commands with `|`:

```text
wish> ls -l | grep wish
```

The shell currently supports one pipeline containing two commands.

## Exiting

Enter `exit` or press `Ctrl+C` to stop the shell.

## Error output

Invalid arguments, unavailable commands, and pipeline setup errors report:

```text
An error has occurred
```

## Source files

- `wish.c` - main shell loop, parsing, process creation, redirection, and pipes
- `history.h` - history data structure and public history functions
- `history.c` - command-history implementation