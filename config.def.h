/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 4; /* border pixel of windows */
static const unsigned int gappx = 15;   /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"monospace:size=16:style=Bold"};
//static const char *fonts[] = {"Inconsolata:size=16"};
static const char dmenufont[] = "monospace:size=16:style=Bold";
// static const char dmenufont[] = "Inconsolata:size=16";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_gray5[] = "#545454";
// static const char col_gray5[]       = "#707070";
static const char col_cyan[] = "#005577";
static const char col_yellow[] = "#b58900";
static const char col_white[] = "#ffffff";
static const char col_cyan2[] = "#02d9bc";

/* solarized colors http://ethanschoonover.com/solarized */
static const char s_base03[] = "#002b36";
static const char s_base02[] = "#073642";
static const char s_base01[] = "#586e75";
static const char s_base00[] = "#657b83";
static const char s_base0[] = "#839496";
static const char s_base1[] = "#93a1a1";
static const char s_base2[] = "#eee8d5";
static const char s_base3[] = "#fdf6e3";

static const char col_orange[] = "#ff8205";
// static const char *colors[][3] = {
//     /*               fg         bg         border   */
//     [SchemeNorm] = {col_cyan2, col_gray1, col_gray2},
//     [SchemeSel] = {col_gray4, col_gray1, col_white},
// };

 static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_gray1, col_white},
};

// solarized colors

//static const char *colors[][3] = {
//    /*               fg         bg         border   */
//    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
//    [SchemeSel] = {col_gray4, col_cyan, col_yellow},
//};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"floating", NULL, NULL, 0, 1, -1},
    {"Pavu", NULL, NULL, 0, 1, -1},
    {"Pulse Mixer", NULL, NULL, 0, 1, -1},
    {"Signal", NULL, NULL, 1 << 3, 0, -1},
    {"Slack", NULL, NULL, 1 << 3, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "grid.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},  {"[D]", deck},           {"[@]", spiral},
    {"[\\]", dwindle}, {"|M|", centeredmaster}, {">M>", centeredfloatingmaster},
    {"HHH", grid},
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",  dmenumon,  "-fn", dmenufont, "-nb", col_gray1, "-nf",
    col_gray4,   "-sb", col_gray4, "-sf", col_gray5, NULL};
static const char *passmenucmd[] = {
    "/usr/bin/passmenu", "-m",  dmenumon,  "-fn", dmenufont, "-nb", col_gray1, "-nf",
    col_gray4,   "-sb", col_gray4, "-sf", col_gray5, NULL};

// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn",
// dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf",
// col_gray4, NULL };
static const char *termcmd[] = {"st", "-e", "/bin/zsh", NULL};
static const char *brightness_up[] = {
    "~/.local/bin/dwm-bar-restart", "~/.local/bin/dwm-brightness", "up", NULL};
static const char *brightness_down[] = {"~/.local/bin/dwm-bar-restart", "~/.local/bin/dwm-brightness",
                                        "down", NULL};

static const char *min_brightness[] = {"~/.local/bin/dwm-bar-restart", "~/.local/bin/min-brightness", NULL};
static const char *max_brightness[] = {"~/.local/bin/dwm-bar-restart", "~/.local/bin/max-brightness", NULL};
static const char *volume_up[] = {"~/.local/bin/dwm-bar-restart", "pamixer", "-i", "5",    NULL};
static const char *volume_down[] = {"~/.local/bin/dwm-bar-restart", "pamixer", "-d", "5",    NULL};
static const char *volume_mute[] = {"~/.local/bin/dwm-bar-restart", "pamixer", "-t", NULL};
static const char *chromiumcmd[] = {"~/.local/bin/browser", NULL};
static const char *firefoxcmd[] = {"~/.local/bin/browser", NULL};
static const char *shortcutscmd[] = {"~/.local/bin/browser", "--app=file://~/projects/suckless/dwm/dwm-shortcuts.html", NULL};
static const char *signalcmd[] = {"/usr/bin/signal-desktop", NULL};
static const char *slackcmd[] = {"/usr/bin/slack", "--disable-gpu", NULL};
static const char *pulsemixercmd[] = {"st", "-c", "Pulse Mixer", "pulsemixer",
                                      NULL};
static const char *screengrab_select[] = {"~/.local/bin/screengrab-select",
                                          NULL};
static const char *screengrab_paste[] = {
    "~/.local/bin/screen_select_with_filename_in_buffer.sh", NULL};
static const char *screengrab[] = {"~/.local/bin/screengrab", NULL};
static const char *screenlock[] = {"~/.local/bin/lock-screen", NULL};

static const char *bookmarks[] = {"~/.local/bin/bookmarks", "NULL"};
static const char *snippits[] = {"st",
                                 "-c",
                                 "floating",
                                 "-g",
                                 "100x35+500+1",
                                 "-e",
                                 "/usr/bin/vim",
                                 "~/.local/share/snippets",
                                 NULL};

static const char *gptclip[] = {"st",          "-c", "floating", "-g",
                                "90x25+500+1", "-e", "gptclip",  NULL};
static const char *gptmenu[] = {"~/.local/bin/gptmenu", NULL};
static const char *notesmenu[] = {"~/.local/bin/notesmenu", NULL};
static const char *newnote[] = {"~/.local/bin/new-note.sh", NULL};
static const char *searchnotes[] = {"~/.local/bin/search-note-tags.sh", NULL};

// static const char *screenlock[] = {"/usr/local/bin/slock", "-mode", "blank",
// NULL};
static const char *surfersearch[] = {"~/.local/bin/surfer-search", "-m",  dmenumon,  "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray4,   "-sb", col_gray4, "-sf", col_gray5, NULL};
static const char *surfer[] = {"~/.local/bin/surfer", "-m",  dmenumon,  "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray4,   "-sb", col_gray4, "-sf", col_gray5, NULL};

static const char *search[] = {"/usr/local/bin/dmenu", NULL};
static const char *notes[] = {
    "st",          "-c", "floating",     "-g",
    "90x25+500+1", "-e", "/usr/bin/vim", "~/notes/NOTES",
    NULL};
static const char *commands[] = {
    "st",          "-c", "floating",     "-g",
    "90x25+500+1", "-e", "/usr/bin/vim", "~/notes/COMMANDS",
    NULL};
static const char *tasks[] = {"st",          "-c", "floating",      "-g",
                              "90x25+500+1", "-e", "/usr/bin/task", NULL};
static const char *pronotes[] = {
    "st",
    "-c",
    "floating",
    "-g",
    "110x50+500+1",
    "-e",
    "/usr/bin/vim",
    "~/notes/00.areas/00.professional/index.md",
    NULL};

static const char *dmenu_clipboard_llm_query[] = {"~/.local/bin/dmenu-clipboard-llm-query.sh", NULL};
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

/* key reference - https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h */

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY, XK_minus, setgaps, {.i = -1}},
    {MODKEY, XK_equal, setgaps, {.i = +1}},
    {MODKEY, XK_Home, spawn, {.v = bookmarks}},
	  {MODKEY, XK_grave, togglescratch, {.v = scratchpadcmd } },
    {MODKEY, XK_bracketleft, spawn, {.v = gptmenu}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY, XK_a, spawn, {.v = passmenucmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_c, spawn, {.v = commands}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_e, setlayout, {.v = &layouts[7]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_g, setlayout, {.v = &layouts[8]}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_n, spawn, {.v = notesmenu}},
    {MODKEY, XK_o, setlayout, {.v = &layouts[4]}},
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY, XK_q, spawn, {.v = dmenu_clipboard_llm_query}},
    // {MODKEY, XK_r, spawn, {.v = pronotes}},

    {MODKEY, XK_s, togglesticky, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_u, setlayout, {.v = &layouts[3]}},
    {MODKEY, XK_w, setlayout, {.v = &layouts[4]}},


    {0, XF86XK_MonBrightnessUp, spawn, {.v = brightness_up}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = brightness_down}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = volume_up}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = volume_down}},
    {0, XF86XK_AudioMute, spawn, {.v = volume_mute}},
    {0, XK_F5, spawn, {.v = min_brightness}},
    {0, XK_F6, spawn, {.v = max_brightness}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},

    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_b, spawn, {.v = chromiumcmd}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY | ShiftMask, XK_f, spawn, {.v = firefoxcmd}},
    {MODKEY | ShiftMask, XK_h, spawn, {.v = shortcutscmd}},
    {MODKEY | ShiftMask, XK_i, spawn, {.v = signalcmd}},
    {MODKEY | ShiftMask, XK_r, spawn, {.v = slackcmd}},

    {MODKEY | ShiftMask, XK_l, spawn, {.v = screenlock}},
    {MODKEY | ShiftMask, XK_p, spawn, {.v = pulsemixercmd}},
    {MODKEY | ShiftMask, XK_s, spawn, {.v = surfersearch}},
    {MODKEY | ShiftMask, XK_u, spawn, {.v = surfer}},

    {MODKEY | ShiftMask, XK_equal, setgaps, {.i = 0}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY | ShiftMask, XK_j,      pushdown,       {0} },
    {MODKEY | ShiftMask, XK_k,      pushup,         {0} },
    {MODKEY | ShiftMask, XK_v, spawn, {.v = newnote}},
    {MODKEY | ShiftMask, XK_t, spawn, {.v = searchnotes}},

    {ControlMask | ShiftMask, XK_Home, spawn, {.v = snippits}},
    {ControlMask, XK_Print, spawn, {.v = screengrab_select}},
    {ControlMask | ShiftMask, XK_p, spawn, {.v = screengrab_select}},
    {ControlMask | ShiftMask, XK_o, spawn, {.v = screengrab_paste}},



    {0, XK_Print, spawn, {.v = screengrab}},
    // {MODKEY, XK_backslash, spawn, {.v = gptclip}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
