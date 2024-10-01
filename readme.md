# CED (Code EDitor)

The CED (Code EDitor) is a vim like text editor written in c with ncurses.
This is a personal learning project.

![demo screenshot 0](https://github.com/pielesju/ced/blob/master/resources/screenshot0.png)

## Requirements

**ncurses**\
How to install ncurses:
```bash
# gnu debian
sudo apt-get install libncurses5-dev libncursesw5-dev
# archlinux
sudo pacman -S ncurses

# (optional) add linting support for make lint
# gnu debian
sudo apt install cpplint
# archlinux
sudo pacman -S cpplint
```

## Build

### Compile

```bash
make
```

### Clean

```bash
make clean
```

### Lint

```bash
make lint
```

## Usage

```bash
# open without file (opens a temporary file "untitled.txt")
$ ced
# open with file
$ ced [filename]
# help
```

### Modes

#### NORMAL mode

the NORMAL mode is the default

```
i  | switch to INSERT mode
h  | move left
j  | move down
k  | move up
l  | move right
gg | move to beginning of file
G  | move to end of file
dd | remove line
dw | remove word
x  | remove character
:  | open commandline
```

#### COMMAND mode

the COMMAND mode is accessed by pressing **:** in normal mode

```
q  | quit
w  | write
wq | write and quit
```

#### INSERT mode

TODO _(not implemented yet)_
