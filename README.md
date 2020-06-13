# nscd-disable

Simple library to `LD_PRELOAD` into any process causing it to stop using nscd.
If you don't know what any of this means, this probably not the project for you.
Works around [nix#2693](https://github.com/NixOS/nix/issues/3693).

Build it like this:
```
gcc ./nscd-disable.c -o nscd-disable.so -fPIC -shared -ldl
```

Use it like this:
```
LD_PRELOAD=nscd-disable.so id
```
