# Pipex

A simple implementation of Unix pipes in C. This program emulates the behavior of a shell pipeline, taking an input file, executing two commands, and writing the output to an output file.

## Features

- **Command Execution**: Executes two commands connected by a pipe.
- **File Handling**:
  - Reads input from a file.
  - Writes output to another file.
- **Error Handling**: Detects invalid commands, missing files, and incorrect arguments.
- **Environment Integration**: Resolves commands using the system's `PATH`.

## Requirements

To build and run the project, you need:

- **C Compiler** (e.g., `gcc`)
- A Unix-based system (Linux or macOS).

## Installation and Setup

1. Clone the repository:

   ```bash
   git clone <repository-url>
   cd <repository-directory>
   ```

2. Modify the `Makefile` if needed to match your environment.

## Compilation

To compile the project, run:

```bash
make
```

This will produce an executable named `pipex`.

## Running the Program

Run the program with the following syntax:

```bash
./pipex <input_file> <command1> <command2> <output_file>
```

- `<input_file>`: The file to read input from.
- `<command1>`: The first command in the pipeline.
- `<command2>`: The second command in the pipeline.
- `<output_file>`: The file to write output to.

### Example:

```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```

This replicates:

```bash
< input.txt grep hello | wc -l > output.txt
```

## Notes

- Ensure the commands and files provided are valid.
- Environment variables are used to resolve command paths.
- The program supports argument splitting and quoted arguments for commands.

## Error Handling

- Missing or invalid files.
- Commands not found or not executable.
- Incorrect number of arguments.

## License

This project is open-source and available under the MIT License. Contributions are welcome!

---

Have fun piping commands together with Pipex!
