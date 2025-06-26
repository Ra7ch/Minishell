# Minishell

Minishell is a custom Unix shell written in C, designed to mimic the behavior of popular shells like `bash` and `zsh`. It supports command parsing, execution, environment variables, built-in commands, redirections, pipes, and more. Additionally, it features AI integration using the Groq API to suggest shell commands based on natural language queries.

## Features
- Custom shell prompt with emoji and color
- Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`
- Command execution with pipes and redirections
- Environment variable management
- Heredoc and wildcard support
- Syntax error detection
- AI-powered command suggestion (Groq API)
- Dockerized for easy setup and isolation

## Requirements
- GCC and Make
- [libreadline-dev](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [libncurses-dev](https://invisible-island.net/ncurses/)
- [libcurl4-openssl-dev](https://curl.se/libcurl/)
- [libjson-c-dev](https://github.com/json-c/json-c)
- Docker and Docker Compose (for containerized usage)

## Building Locally
1. Install dependencies:
   ```sh
   sudo apt-get update
   sudo apt-get install build-essential libreadline-dev libncurses-dev libcurl4-openssl-dev libjson-c-dev
   ```
2. Build the shell:
   ```sh
   make
   ```
3. Run the shell:
   ```sh
   ./minishell
   ```

## Running with Docker
1. Set your Groq API key in your environment:
   ```sh
   export GROQ_API_KEY=sk-...yourkey...
   ```
2. Build and run the container:
   ```sh
   docker-compose up --build
   ```
   The project directory is bind-mounted into the container, so changes are reflected live.

## AI Integration (Groq)
- When you enter a natural language query, the shell sends it to the Groq API.
- The AI responds with a shell command (no explanations, no markdown).
- You are prompted to confirm before the command is executed for safety.
- If you enter an empty line, no command is suggested or run.

## Security Note
- Always review AI-suggested commands before running them.
- The shell will prompt for confirmation before executing any AI-generated command.

## Example Usage
```
😊 app> check how much this folder takes in disk space
AI suggests: du -sh .
Do you want to run this command? [y/N]: y
[output of du -sh .]
```

## Authors
- raitmous <raitmous@student.42.fr>
- mben-zeh <mben-zeh@student.42.fr>

## License
This project is for educational purposes. 