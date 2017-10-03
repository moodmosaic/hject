# hject
Eject removable media without leaving the command line.

## Building

In order to compile the source code, ensure that you have [Stack][stack] installed.

Clone a copy of the repo:

```
git clone https://github.com/moodmosaic/hject
```

Change to the hject directory:

```
cd hject
```

Compile the source code:

```
$ stack setup
$ stack exec -- ghc --make eject.hs c_eject.c
```

[stack]: https://docs.haskellstack.org/en/stable/README/
