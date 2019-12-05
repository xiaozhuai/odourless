# odourless

Odourless is tool for preventing .DS_Store creation.

This project is just a prototype at present, so use it as your own risk.

# How it works

It use frida to hook into `Finder.app`, and replace the `open` syscall.

Whenever `Finder` try to `open` a file name ends with `/.DS_Store`, call `remove` and then return `-1`.

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