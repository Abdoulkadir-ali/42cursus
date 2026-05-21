*This project has been created as part of the 42 curriculum by abdoali, agallot.*

# ft_irc

## Description

ft_irc is an IRC server written in C++98. Its goal is to implement a subset of the IRC
protocol (RFC 1459 / RFC 2812) that lets multiple clients connect simultaneously,
exchange messages, and manage channels — all without blocking I/O, using a single
`poll()` call.

The server handles the following commands: `PASS`, `NICK`, `USER`, `JOIN` (including
`JOIN 0` to leave all channels), `PART`, `PRIVMSG`, `NOTICE`, `KICK`, `INVITE`,
`TOPIC`, `MODE` (`+i`, `+t`, `+k`, `+o`, `+l`), `PING`/`PONG`, `QUIT`, `CAP`, and
`WHOIS`.

Bonus features include an in-process IRC bot (`IRCBot`) that responds to channel
commands (`!help`, `!ping`, `!time`, `!echo`, `!info`), and a DCC SEND relay that
proxies file transfers through the server.

## Instructions

### Compilation

```sh
make          # build the ircserv binary
make re       # full rebuild
make clean    # remove object files
make fclean   # remove object files and binary
```

Requires a C++98-compatible compiler (`c++`).

### Execution

```sh
./ircserv <port> <password>
```

- `<port>` — TCP port to listen on (e.g. `6667`)
- `<password>` — connection password clients must supply via `PASS`

### Connecting

Any standard IRC client works (e.g. `irssi`, `weechat`, `HexChat`). For quick raw
testing:

```sh
nc 127.0.0.1 6667
PASS <password>
NICK testnick
USER testuser 0 * :Test User
```

## Resources

### References

- [RFC 1459 – Internet Relay Chat Protocol](https://tools.ietf.org/html/rfc1459)
- [RFC 2812 – IRC: Client Protocol](https://tools.ietf.org/html/rfc2812)
- [Modern IRC documentation](https://modern.ircdocs.horse/)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)

### AI usage
AI was used as a learning aid for documentation, debugging, and code review.
The tool was used for:
- Documentation & RFC Parsing: Clarifying complex IRC protocol rules (like JOIN 0 and WHOIS edge cases) and cross-referencing C++98 constraints.
- Concept Validation: Reviewing the theory behind low-level networking paradigms, such as non-blocking I/O multiplexing with poll() and socket pairs.
