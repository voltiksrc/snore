# snore

A small power management utility written in C for Linux, supporting systemd and runit.

## Usage

```sh
snore -s    # Suspend
snore -p    # Power off
snore -r    # Reboot
snore -h    # Help
```

## Install

Run the installer.sh script:

```sh
./installer.sh
```

## Manually Building

Requires [Xmake](https://xmake.io).

```sh
xmake
xmake run snore --help
```

Install:

```sh
sudo install -Dm755 build/linux/x86_64/release/snore /usr/local/bin/snore
```

## Status

Still in development, suspend command is buggy.

## License

ISC © 2026 voltik
