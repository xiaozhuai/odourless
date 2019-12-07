# odourless

Odourless is a tool for preventing .DS_Store file creation.

This project is just a prototype at present. So it use python and js so far, but I will provide a c/c++ version at some point.

**Use it at your own risk.**

## How it works

Odourless hooks into `Finder.app` via frida, then replace some system calls including `open`, `openx_np`, `getattrlist`, `setattrlist`.

Whenever `Finder` try call these functions with `.DS_Store` file, it will replace the path to a fake one under the odourless cage directory `/usr/local/var/.odourless_cage`.

As you see, it do not delete `.DS_Store`, but place all `.DS_Store` into one directory that you don't care about.

Many thanks to [@darwin](https://github.com/darwin) and [@JK3Y](https://github.com/JK3Y) !

This project was standing on the shoulders of [binaryage/asepsis](https://github.com/binaryage/asepsis) and [JK3Y/asepsis](https://github.com/JK3Y/asepsis)

For discussion, go [https://github.com/JK3Y/asepsis/issues/25](https://github.com/JK3Y/asepsis/issues/25)

## How to use it

### Disable SIP

You need to disable [System Integrity Protection](https://support.apple.com/en-us/HT204899).

### Install frida(python3 version)

```
pip3 install frida-tools
```

### Disable asepsis

If you already installed asepsis, you need to uninstall it first.

### Use odourless

Press three keys together: `Option`, `Command`, and `Esc`, select the Finder app in the Force Quit window, then click `Relaunch` button to restart Finder app.

```
ps -ax | grep Finder
```

Once you got `Finder` pid, run: 

```
./odourless [pid]
```