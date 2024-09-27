# CED (Code EDitor)
The CED (Code EDitor) is a vim like text editor written in c with ncurses

![demo screenshot 0](https://github.com/pielesju/ced/blob/master/resources/screenshot0.png)

## Requirements

ncurses\
How to install:
```bash
# gnu debian
sudo apt-get install libncurses5-dev libncursesw5-dev
# archlinux
sudo pacman -S ncurses
```

## Build

### Compile

```
make
```

### Clean

```
make clean
```

## Usage

```
# open without file (opens a temporary file "untitled.txt")
$ ced
# open with file
$ ced [filename]
```

### Modes

#### NORMAL mode

the NORMAL mode is the default

i switch to INSERT MODE
h move left
j move down
k move up
l move right
gg move to beginning of file
G move to end of file
dd remove line
dw remove word
x remove character
: open commandline

#### COMMAND mode

the COMMAND mode ist accessed by pressing : in normal mode

q quit
w write
wq write and quit

#### INSERT mode

not implemented yet
