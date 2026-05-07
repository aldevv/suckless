# Suckless tools — Claude Code notes

This repo holds the user's customized suckless software. One git repo, one branch (`master`), one tool per top-level directory.

## Repo layout

- `st/` — terminal emulator (see `st/CLAUDE.md` for details)
- `dwm/` — window manager (git submodule)
- `dwm-6.1/` — older dwm fork with full patch stack and config
- `dmenu/` — application launcher with custom patches
- `dragon/` — drag-and-drop tool (vendored)
- `sxiv/` — image viewer (vendored)
- `patchGuide` — submodule with patching reference

## Convention: built binaries are tracked

Each tool's directory checks in the **compiled binary** (`st/st`, `dmenu/dmenu`, etc.) alongside the source. This is unusual but intentional — the user runs the binary from `~/.local/builds/<tool>/bin/<tool>` symlinked into `~/.local/bin/`. Don't try to "fix" this by gitignoring binaries.

## Patch hygiene

`patch` leaves `*.orig` and `*.rej` files. **Never commit them** — `rm -f *.orig *.rej` before `git add`. They're not in `.gitignore` because the user hasn't asked for it.

## Commit conventions

- Use conventional-commit prefixes: `feat:`, `fix:`, `patch(<tool>):`, `build(<tool>):`, `chore:`, `docs:`.
- One patch upgrade = one commit (per user preference).
- Body should explain *why* and any manual ports needed.
- **Never mention Claude or add Co-Authored-By: Claude** — the user's `~/CLAUDE.md` is explicit on this.

## Don't

- Don't gitignore tracked binaries.
- Don't run `make clean install` without `sudo`.
- Don't apply patches blindly — many `.diff` files in patch directories target older versions and need manual reconciliation against the current source.
- Don't touch `~/work/*` paths in this session — that's the work repo.
