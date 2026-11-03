# snore

A small power management utility written in C for Linux, supporting systemd and runit.

## Usage

```sh
snore -s    # Suspend
snore -p    # Power off
snore -r    # Reboot
snore -h    # Help
```

## Building

Requires [Xmake](https://xmake.io).

```sh
xmake
xmake run snore --help
```

## Status

Still in development. Power operations are not yet fully implemented.

## License

ISC © 2026 voltik
