# odourless

Odourless is a tool for preventing .DS_Store creation.

**Use it at your own risk.**

# How it works

It use `mach_inject` to inject `Finder.app` and `frida-gum` to replace some syscall including `open`, `openx_np`, `getattrlist`, `setattrlist`.

Whenever `Finder` try call these function with `.DS_Store` file, it will replace the path to a fake one under the odourless cage directory `/usr/local/var/.odourless_cage`.

As you see, it do not delete `.DS_Store`, but place all `.DS_Store` into one directory that you donot care about.

Many thanks to [@darwin](https://github.com/darwin) and [@JK3Y](https://github.com/JK3Y) !

This project was standing on the shoulders of [binaryage/asepsis](https://github.com/binaryage/asepsis) and [JK3Y/asepsis](https://github.com/JK3Y/asepsis)

For discussion, go [https://github.com/JK3Y/asepsis/issues/25](https://github.com/JK3Y/asepsis/issues/25)

# How to use it

## Install

Download for release page. And install.

## Disable SIP

1. Click the Apple symbol in the Menu bar.
2. Click Restart...
3. Hold down Command-R to reboot into Recovery Mode.
4. Click Utilities.
5. Select Terminal.
6. Type `csrutil disable`.
7. Press Return or Enter on your keyboard.
8. Click the Apple symbol in the Menu bar.
9. Click Restart…

## Install Odourless.app in /Applications

Move `Odourless.app` to `/Applications`, open it and click to `install` daemon.

Ok, that's all.

Next time reboot, `odourless-daemon` will auto-start. Take it easy.

# How to build

Odourless can build without `xcode`. But `Command Line Tools` is needed. 

Install with `xcode-select --install`.

```bash
git clone https://github.com/xiaozhuai/odourless
cd odourless
makdir build
cmake -DCMAKE_BUILD_TYPE=Release ..
make install -j8
open dist
```

# Under the hood

## Odourless.app

Odourless.app is a GUI program for easy installing and manage `odourless-daemon`.

## odourless-daemon

A daemon process to inject `libodourless-inject.dylib` to `Finder` process. 
When `Finder` restarted, `odourless-daemon` will do re-inject.

## odourless-ctl

If you prefer command line than graphics `Odourless.app`, you may like this. (Not yet available)

## libodourless-inject.lib

Replace syscall in `Finder` process.
