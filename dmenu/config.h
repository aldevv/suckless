/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int instant = 0;
static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
    "JoyPixels:pixelsize=15:antialias=true:autohint=true",
    "NotoColorEmoji:pixelsize=14:antialias=true:autohint=true", // Unicode (emojis)
    /* "Hack Nerd Font Mono:pixelsize=14:antialias=true:autohint=true", // Powerline */
    /* "Inconsolata for Powerline:pixelsize=12:antialias=true:autohint=true", */
    /* "Symbola:pixelsize=16:antialias=true:autohint=true", // Unicode (emojis) */
    /* "Noto Sans Emoji:pixelsize=13:antialias=true:autohint=true", // Unicode (emojis) */
	"monospace:size=12"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
/* #include "/home/kanon/.cache/wal/colors-wal-dmenu.h" */
static const char *colors[SchemeLast][2] = {
	    /* fg         bg */
	[SchemeNorm] = { "#bbbbbb", "#222222" },
	[SchemeSel] = { "#eeeeee", "#005577" },
	[SchemeSelHighlight] = { "#ffc978", "#005577" },
	[SchemeNormHighlight] = { "#ffc978", "#222222" },
	[SchemeOut] = { "#000000", "#00ffff" },
	[SchemeOutHighlight] = { "#ffc978", "#00ffff" },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;
/* -h option; minimum height of a menu line */
static unsigned int lineheight = 0;
static unsigned int min_lineheight = 8;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
