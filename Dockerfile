FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && \
    apt-get install -y build-essential libreadline-dev libncurses-dev curl libcurl4-openssl-dev libjson-c-dev && \
    rm -rf /var/lib/apt/lists/*

# Set workdir
WORKDIR /app

# Copy project files
COPY . /app

# Build the project
RUN make

# Run the shell by default
ENTRYPOINT ["/app/minishell"] 
# ENTRYPOINT ["sleep 1000000000000"]