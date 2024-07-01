// clang-format off
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        // border pixel of windows
static const unsigned int snap      = 32;       // snap pixel
static const unsigned int gappih    = 0;        // horiz inner gap between windows
static const unsigned int gappiv    = 0;        // vert inner gap between windows
static const unsigned int gappoh    = 0;        // horiz outer gap between windows and screen edge
static const unsigned int gappov    = 0;        // vert outer gap between windows and screen edge
static       int smartgaps          = 0;        // 1 means no outer gap when there is only one window
static const int showbar            = 1;        // 0 means no bar
static const int topbar             = 1;        // 0 means bottom bar
static const char *fonts[]          = { "Jetbrains Mono NerdFont:size=12:style=Bold", "monospace:size=12" };
static const char dmenufont[]       = "Jetbrains Mono NerdFont:size=12:style=Bold";
#include "themes/mhtheme.h"
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_accnt, col_accnt  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5;   /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;     /* number of clients in master area */
static const int resizehints = 0;     /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;  /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "unfloat.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-c", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_accnt, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key                    function        argument */
	{ MODKEY,                       XK_r,                  spawn,          {.v = dmenucmd } },                                // open app launcher MOD+r
	{ MODKEY,                       XK_Return,             spawn,          {.v = termcmd } },                                 // spawn terminal MOD+return
	{ MODKEY,                       XK_s,                  spawn,          SHCMD("exec ~/Dev/scripts/screenshot.sh") },       // screenshot MOD+s (requires script in ~/Dev/scripts/screenshot.sh)
	{ MODKEY|ShiftMask,             XK_s,                  spawn,          SHCMD("flameshot gui") },                          // screenshot MOD+S (requires script in ~/Dev/scripts/screenshot_crop.sh)
	{ MODKEY,                       XK_e,                  spawn,          SHCMD("exec nemo") },                              // open file manager (nemo) MOD+e
	{ MODKEY,                       XK_b,                  togglebar,      {0} },                                             // show hide bar MOD+b
	{ MODKEY|ALTKEY|ShiftMask,      XK_l,                  spawn,          SHCMD("exec slock") },                             // lockscreen MOD+ALT+L
	{ MODKEY,                       XK_j,                  focusstack,     {.i = +1 } },                                      // focus window up stack MOD+J
	{ MODKEY,                       XK_k,                  focusstack,     {.i = -1 } },                                      // focus window down stack MOD+K
	{ MODKEY|ShiftMask,             XK_j,                  movestack,      {.i = +1 } },                                      // move window up stack MOD+J
	{ MODKEY|ShiftMask,             XK_k,                  movestack,      {.i = -1 } },                                      // move window down stack MOD+K
	{ MODKEY,                       XK_i,                  incnmaster,     {.i = +1 } },                                      // increase windows in master stack MOD+i
	{ MODKEY,                       XK_d,                  incnmaster,     {.i = -1 } },                                      // decrease windows in master stack MOD+d
	{ MODKEY,                       XK_h,                  setmfact,       {.f = -0.05} },                                    // adjust mfact MOD+h
	{ MODKEY,                       XK_l,                  setmfact,       {.f = +0.05} },                                    // adjust mfact MOD+l
	{ MODKEY|ShiftMask,             XK_h,                  setcfact,       {.f = +0.25} },                                    // adjust cfact MOD+H
	{ MODKEY|ShiftMask,             XK_l,                  setcfact,       {.f = -0.25} },                                    // adjust cfact MOD+L
	{ MODKEY|ShiftMask,             XK_o,                  setcfact,       {.f =  0.00} },                                    // adjust cfact MOD+O
	{ MODKEY,                       XK_Return,             zoom,           {0} },                                             // MOD+Return
	{ MODKEY|ALTKEY,                XK_u,                  incrgaps,       {.i = +10 } },                                     // adjust gaps MOD+ALT+u
	{ MODKEY|ALTKEY|ShiftMask,      XK_u,                  incrgaps,       {.i = -10 } },                                     // adjust gaps MOD+ALT+U
	{ MODKEY|ShiftMask,             XK_bracketleft,        setborderpx,    {.i = -2 } },                                      // increase border width MOD+{
	{ MODKEY|ShiftMask,             XK_bracketright,       setborderpx,    {.i = +2 } },                                      // decrease border width MOD+}
	{ MODKEY,                       XK_Tab,                view,           {0} },                                             // tab tag MOD+Tab
	{ MODKEY,                       XK_c,                  killclient,     {0} },                                             // close window MOD+c
	{ MODKEY|ShiftMask,             XK_z,                  unfloatvisible, {.v = &layouts[0]} },                              // make floating window tiled MOD+Z
	{ MODKEY|ALTKEY,                XK_1,                  setlayout,      {.v = &layouts[0]} },                              // change layout to tile MOD+ALT+1
	{ MODKEY|ALTKEY,                XK_2,                  setlayout,      {.v = &layouts[13]} },                             // change layout to float MOD+ALT+2
	{ MODKEY|ALTKEY,                XK_3,                  setlayout,      {.v = &layouts[1]} },                              // change layout to monocle MOD+ALT+3
	{ MODKEY|ALTKEY,                XK_4,                  setlayout,      {.v = &layouts[11]} },                             // change layout to centeredmaster MOD+ALT+4
	{ MODKEY|ALTKEY,                XK_5,                  setlayout,      {.v = &layouts[5]} },                              // change layout to bstac MOD+ALT+5
	{ MODKEY|ALTKEY,                XK_6,                  setlayout,      {.v = &layouts[7]} },                              // change layout to grid MOD+ALT+6
	{ MODKEY|ALTKEY,                XK_7,                  setlayout,      {.v = &layouts[2]} },                              // change layout to spiral MOD+ALT+7
	{ MODKEY,                       XK_0,                  view,           {.ui = ~0 } },                                     // view all windows MOD+0
	{ MODKEY|ShiftMask,             XK_0,                  tag,            {.ui = ~0 } },                                     // make window on all tags MOD+SHIFT+0
	{ MODKEY,                       XK_comma,              focusmon,       {.i = -1 } },                                      // move window to monitor MOD+,
	{ MODKEY,                       XK_period,             focusmon,       {.i = +1 } },                                      // move window to monitor MOD+.
	{ MODKEY|ShiftMask,             XK_comma,              tagmon,         {.i = -1 } },                                      // move window to monitor MOD+SHIFT+,
	{ MODKEY|ShiftMask,             XK_period,             tagmon,         {.i = +1 } },                                      // move window to monitor MOD+SHIFT+.
	TAGKEYS(                        XK_1,                                    0)                                               // change tag MOD+[1-9]
	TAGKEYS(                        XK_2,                                    1)
	TAGKEYS(                        XK_3,                                    2)
	TAGKEYS(                        XK_4,                                    3)
	TAGKEYS(                        XK_5,                                    4)
	TAGKEYS(                        XK_6,                                    5)
	TAGKEYS(                        XK_7,                                    6)
	TAGKEYS(                        XK_8,                                    7)
	TAGKEYS(                        XK_9,                                    8)
	{ MODKEY|ShiftMask,             XK_BackSpace,          quit,           {0} },                                             // quit dwm MOD+SHIFT+backspace
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
