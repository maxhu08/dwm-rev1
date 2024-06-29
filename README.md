# dwm-rev1

This is a revision of my build of dwm. It is built off of `dwm-6.5`

## patches

- `movestack` https://dwm.suckless.org/patches/movestack
  - makes it so that MOD+J & MOD+K moves windows up & down the stack (better than stacker)
- `resizehere` https://dwm.suckless.org/patches/resizehere
  - prevents mouse from warping to bottom right corner when resizing window
- `vanitygaps` https://dwm.suckless.org/patches/vanitygaps
  - provides adjustable gaps with keybinds and more layouts
- `statusallmons` https://dwm.suckless.org/patches/statusallmons
  - makes it so that status bar gets updated on all monitors instead of just the focused one
- `pertag` https://dwm.suckless.org/patches/pertag
  - preserves mfact and other stuff per tag
- `tiledmove` https://dwm.suckless.org/patches/tiledmove
  - makes it so MOD+lmb allows windows to stay tiled while moving them
- `unfloatvisible` https://dwm.suckless.org/patches/unfloatvisible
  - make floating window tiled again with MOD+T

## quick-start

to get started run these commands:

```
git clone https://github.com/maxhu08/dwm-rev1
cd dwm-rev1
sudo make clean install
```

then add this to your `~/.xinitrc`

```
exec dwm
```
