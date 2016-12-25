# consoleChat

A simple command line chat client and server written in C.

## Installation

First clone the repository with `git clone https://github.com/asnermino/consoleChat`.

### Server

Run `make` from inside `consoleChat/server`. By default `make` will set the port number to 59248. To specifiy the port for incoming connections run `make PORT=####` where `####` is your desired port number.  

### Client

Run `make` from inside `consoleChat/client`. By default `make` will set the port number to 59248. To specifiy the port of the server run`make PORT=####` where `####` is your desired port number.  

## Running server

Run `consoleChat/chat_server`.

## Running client

Run `consoleChat/chat_client 127.0.0.1`. Replace `127.0.0.1` with the servers IP address.
