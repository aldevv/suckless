# st — Claude Code notes

The user's patched build of [st](https://st.suckless.org). Currently at **0.9.3** with 10 patches stacked on top.

## Build + install

```sh
cd st
sudo make clean install        # installs to /usr/local/bin/st
# Then sync the user-local copy that's actually in PATH:
sudo cp st /home/kanon/.local/builds/st/bin/st.new
sudo mv /home/kanon/.local/builds/st/bin/st.new /home/kanon/.local/builds/st/bin/st
```

The `cp .new && mv` dance avoids `Text file busy` errors when running st instances hold the file open.

`~/.local/bin/st` is the symlink that `which st` resolves to — it points at `~/.local/builds/st/bin/st`. Forgetting to update that copy is the easiest way to "rebuild and see no change" because new windows still launch the old binary.

## Patches live in `stpatches/`

Applied patches are kept there as `.diff` files. To upgrade a patch, replace the file with the newer version from <https://st.suckless.org/patches/>. Order of application matters — see commit history for canonical order. Currently:

1. `st-scrollback-0.9.2.diff` (foundational)
2. `st-focus-20230610-68d1ad9.diff` (alpha + focus highlight, multi-section git format-patch)
3. `st-ligatures-alpha-scrollback-0.9.2.diff` (assumes scrollback + alpha already applied)
4. `st-boxdraw_v2-0.8.5.diff` (manual port — hook into harfbuzz codepoint check, not XftCharIndex)
5. `st-font2-0.8.5.diff`
6. `st-anysize-20220718-baa9357.diff`
7. `st-externalpipe-0.8.5.diff`
8. `st-xresources-20230320-45a15676.diff`
9. `st-w3m-0.8.3.diff`
10. `st-fix-keyboard-input-20180605-dc3b5ba.diff`

## Color scheme

Two palettes live in `config.h`. The active one is the **uncommented** block — toggle by commenting/uncommenting:

- **GRUVBOX** (commented): standard gruvbox dark.
- **KITTY defaults** (active): kitty's default 16-ANSI palette; bright blue `#1a8fff` makes `ls` dirs render as a vivid normal blue.

`bg`, `fg`, and cursor colors (256-259) are kept stable across both palettes (`bg = #282828`, `fg = #FFFFFF`, cursor = `#add8e6`).

## Important config.h notes

- `defaultcs` and `defaultrcs` must be **non-static** (the xresources patch declares them `extern` in `st.h`).
- `bg = 16, bgUnfocused = 16` references `colorname[16]` which isn't defined — focus patch falls back gracefully but worth knowing.
- `font2[]` is the spare-font array used by the font2 patch.

## Truecolor inside tmux

The user runs st inside tmux. For 24-bit colors (e.g. `hunk diff` backgrounds) to render correctly, `~/.config/tmux/tmux.conf` must include `st-256color:Tc` in its `terminal-overrides`. Already configured — just call out if the user reports washed-out or grayish colors.

## What changed

### 2026-05-07 — Upgraded st from 0.8.4 → 0.9.3

**Color fix**

- Restored canonical gruvbox palette (color 2 was teal `#1e7f76`, breaking diff green backgrounds; now `#98971a`).
- Then switched the active palette to **kitty defaults** so `ls` directory color is a normal vivid blue (`#1a8fff`) instead of gruvbox's teal `#83a598`.

**Version bump: 0.8.4 → 0.9.2 → 0.9.3**

Each patch upgraded to the newest available version when one existed:

| Patch | 0.8.4 setup | 0.9.3 setup |
|---|---|---|
| scrollback | `20190331-21367a0` | `0.9.2` |
| alpha + focus | `20200731-43a395a` | `20230610-68d1ad9` (0.9, multi-commit format-patch) |
| ligatures | `20200430-0.8.3` (×2 manually merged) | `0.9.2 alpha-scrollback` combo |
| boxdraw_v2 | `0.8.3` | `0.8.5` (manual port for ligatures coexistence) |
| font2 | `20190416-ba72400` | `0.8.5` |
| anysize | `20220718` | unchanged |
| externalpipe | `0.8.2` | `0.8.5` |
| xresources | `20200604-9ba7ecf` | `20230320-45a15676` |
| w3m | `0.8.3` | unchanged |
| fix-keyboard-input | `20180605-dc3b5ba` | unchanged |

**New upstream features from 0.9.2 → 0.9.3**

- Support colons in SGR character attributes (modern truecolor escape forms)
- Fix BadMatch error when embedding on some windows
- Clear-screen edge case fix
- Don't interpret `CSI ? u` as DECRC
- Eat up `CSI 58` sequences
- Support OSC 110/111/112 to reset cursor/foreground/background colors

**New upstream features from 0.8.4 → 0.9.x baseline**

- `tsetdirt()` guard against zero-sized terminal
- Various OSC/CSI handling fixes accumulated over the 0.8.5 → 0.9.2 releases

**Manual port hotspots (be aware if re-doing)**

- `xinit()` in `x.c`: BadMatch fix (root + XReparentWindow) had to coexist with the alpha patch (`xw.depth = 32`). XCreateWindow uses `root`, reparent only if embedding, GC stays on `xw.buf`.
- `xmakeglyphfontspecs()` in `x.c`: boxdraw hook moved into the harfbuzz codepoint branch (the original patch hooked into `XftCharIndex` which ligatures had already replaced).
- `st.h`: `tfulldirt` declared non-static (focus patch needs it from x.c); `defaultcs/defaultrcs` declared `extern` (xresources patch).
