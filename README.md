# odourless

Odourless is a tool for preventing .DS_Store creation.

This project is just a prototype at present. So it use python and js so far. Whenever it ready, it will switch to c/c++ version.

**Use it at your own risk.**

# How it works

It use frida to hook into `Finder.app`, and replace the `open`, `openx_np`, `getattrlist`, `setattrlist` syscall.

Whenever `Finder` try call these function with `.DS_Store` file, it will replace the path to a fake one under the odourless cage directory `/usr/local/var/.odourless_cage`.

As you see, it do not delete `.DS_Store`, but place all `.DS_Store` into one directory that you donot care about.

Many thanks to [@darwin](https://github.com/darwin) and [@JK3Y](https://github.com/JK3Y) !

This project was standing on the shoulders of [binaryage/asepsis](https://github.com/binaryage/asepsis) and [JK3Y/asepsis](https://github.com/JK3Y/asepsis)

For discussion, go [https://github.com/JK3Y/asepsis/issues/25](https://github.com/JK3Y/asepsis/issues/25)

# How to use it

## Disable SIP

You need to disable [System Integrity Protection](https://support.apple.com/en-us/HT204899).

## Install frida(python3 version)

```
pip3 install frida-tools
```

## Disable asepsis
If you already install asepsis, you need to uninstall it first. Then hold `option` and right click on `Finder` to restart it.

## Here you go

```
ps -ax | grep Finder
```

Here you got `Finder` pid. Then 

```
./odourless [pid]
```