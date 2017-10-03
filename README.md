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

## Credits

* [Walkthrough: Compile a C program on the command line][ccomp]
* [Ejecting CD-ROM by Haskell][hject]
* [This Stack Overflow question][impcc]
* [Ejecting Removable Media in Windows NT/Windows 2000/Windows XP][wject]
* [Foreign Function Interface][hsffi]

[stack]: https://docs.haskellstack.org/en/stable/README/
[ccomp]: https://msdn.microsoft.com/en-us/library/bb384838.aspx
[hject]: https://gist.github.com/h-hirai/5486696
[impcc]: https://stackoverflow.com/q/30412951/467754
[wject]: https://support.microsoft.com/en-us/help/165721/how-to-ejecting-removable-media-in-windows-nt-windows-2000-windows-xp
[hsffi]: https://wiki.haskell.org/Foreign_Function_Interface
