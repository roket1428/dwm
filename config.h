/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */
static const char *fonts[]          = { "Hack:size=9", "Font Awesome 6 Free Solid:size=13", "Font Awesome 6 Free:size=13", "Font Awesome 6 Brands:size=13", "Font Awesome v4 Compatibility:size=13"  };
static const char dmenufont[]       = "Hack:size=9";
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#000000";
static const char col_gray3[]       = "#ffffff";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#005577";
static const char col_red[]         = "#FF0000";
static const char col_orange[]      = "#FF8800";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeTitle]  = { col_gray3, col_gray1,  col_gray2  },
	[SchemeScratchSel]  = { col_gray4, col_cyan,  col_red  },
	[SchemeScratchNorm] = { col_gray4, col_cyan,  col_orange },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, 0, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTitle]  = { OPAQUE, 0, borderalpha },
	[SchemeScratchSel] = { OPAQUE, baralpha, borderalpha },
	[SchemeScratchNorm] = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor  isgame  scratch key */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1,      0,        0   },
	{ "Steam",    NULL,       NULL,       0,            0,           -1,      1,        0   },
	{ "steam_app",NULL,       NULL,       0,            0,           -1,      1,        0   },
	{ NULL,       NULL,   "ircpad",       0,            1,           -1,      0,        'i' },
	{ NULL,       NULL,   "todopad",      0,            1,           -1,      0,        't' },
	{ NULL,       NULL,   "musicpad",     0,            1,           -1,      0,        'm' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "###",      gaplessgrid },/* first entry is default */
	{ "[]=",      tile },
	{ "><>",      NULL },       /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

#include <X11/XF86keysym.h>

/* key definitions */
#define NOMOD 0
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

/*First arg only serves to match against key in rules*/
static const char *ircpadcmd[] = {"i", "st", "-g", "100x30", "-t", "ircpad", "-e", "irssi", NULL};
static const char *todopadcmd[] = {"t", "st", "-g", "100x30", "-z", "20", "-t", "todopad", "-e", "hx", "/home/roket1428/files/tintka", NULL};
static const char *musicpadcmd[] = {"m", "st", "-t", "musicpad", "-e", "cmus", NULL};

static const Key keys[] = {
	/* modifier              key                         function        argument */
	{ MODKEY,                XK_d,                       spawn,          {.v = dmenucmd } },
	{ MODKEY,                XK_Return,                  spawn,          {.v = termcmd } },
	{ MODKEY,                XK_i,                       togglescratch,  {.v = ircpadcmd } },
	{ MODKEY,                XK_m,                       togglescratch,  {.v = musicpadcmd } },
	{ MODKEY,                XK_b,                       togglescratch,  {.v = todopadcmd } },
	{ MODKEY|ShiftMask,      XK_q,                       killclient,     {0} },
	{ MODKEY|ShiftMask,      XK_f,                       togglebar,      {0} },
	{ MODKEY,                XK_f,                       togglefullscr,  {0} },
	{ MODKEY|ShiftMask,      XK_space,                   togglefloating, {0} },

	{ NOMOD,                 XF86XK_AudioPlay,           spawn,          SHCMD("playerctl play && kill -35 $(pidof dwmblocks)") },
	{ NOMOD,                 XF86XK_AudioStop,           spawn,          SHCMD("playerctl pause && kill -35 $(pidof dwmblocks)") },
	{ NOMOD,                 XF86XK_AudioNext,           spawn,          SHCMD("playerctl next && kill -35 $(pidof dwmblocks)") },
	{ NOMOD,                 XF86XK_AudioPrev,           spawn,          SHCMD("playerctl previous && kill -35 $(pidof dwmblocks)") },

	{ NOMOD,                 XF86XK_AudioRaiseVolume,    spawn,          SHCMD("pamixer -i 5 && kill -37 $(pidof dwmblocks)") },
	{ NOMOD,                 XF86XK_AudioLowerVolume,    spawn,          SHCMD("pamixer -d 5 && kill -37 $(pidof dwmblocks)") },
	{ NOMOD,                 XF86XK_AudioMute,           spawn,          SHCMD("pamixer -t && kill -37 $(pidof dwmblocks)") },

	{ NOMOD,                 XF86XK_MonBrightnessUp,     spawn,          SHCMD("sb-backlight -i 10 && kill -36 $(pidof dwmblocks)") },
	{ NOMOD,                 XF86XK_MonBrightnessDown,   spawn,          SHCMD("sb-backlight -d 10 && kill -36 $(pidof dwmblocks)") },

	{ NOMOD,                 XK_Print,                   spawn,          SHCMD("maim -u -s ~/files/screenshots/$(date +%s).png") },
	{ MODKEY,                XK_x,                       spawn,          SHCMD("maim -m 1 -u -s | xclip -selection clipboard -t image/png") },

	{ MODKEY,                XK_h,                       focusdir,       {.i = 0 } }, // left
	{ MODKEY,                XK_l,                       focusdir,       {.i = 1 } }, // right
	{ MODKEY,                XK_k,                       focusdir,       {.i = 2 } }, // up
	{ MODKEY,                XK_j,                       focusdir,       {.i = 3 } }, // down

	{ MODKEY|ShiftMask,      XK_h,                       placedir,       {.i = 0 } }, // left
	{ MODKEY|ShiftMask,      XK_l,                       placedir,       {.i = 1 } }, // right
	{ MODKEY|ShiftMask,      XK_k,                       placedir,       {.i = 2 } }, // up
	{ MODKEY|ShiftMask,      XK_j,                       placedir,       {.i = 3 } }, // down

	{ MODKEY,                XK_Left,                    incnmaster,     {.i = +1 } },
	{ MODKEY,                XK_Right,                   incnmaster,     {.i = -1 } },
	{ MODKEY,                XK_Up,                      setmfact,       {.f = -0.05} },
	{ MODKEY,                XK_Down,                    setmfact,       {.f = +0.05} },

	{ MODKEY|ShiftMask,      XK_Return,                  zoom,           {0} },
	{ MODKEY,                XK_Tab,                     view,           {0} },
	{ MODKEY,                XK_c,                       layoutscroll,   {.i = -1 } },
	{ MODKEY,                XK_v,                       layoutscroll,   {.i = +1 } },

	{ MODKEY,                XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY,                XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,      XK_comma,                   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,      XK_period,                  tagmon,         {.i = +1 } },
	TAGKEYS(                 XK_1,                       0)
	TAGKEYS(                 XK_2,                       1)
	TAGKEYS(                 XK_3,                       2)
	TAGKEYS(                 XK_4,                       3)
	TAGKEYS(                 XK_5,                       4)
	TAGKEYS(                 XK_6,                       5)
	TAGKEYS(                 XK_7,                       6)
	TAGKEYS(                 XK_8,                       7)
	TAGKEYS(                 XK_9,                       8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          NOMOD,          Button1,        layoutscroll,   {.i = -1 } },
	{ ClkLtSymbol,          NOMOD,          Button3,        layoutscroll,   {.i = +1 } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            NOMOD,          Button1,        view,           {0} },
	{ ClkTagBar,            NOMOD,          Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

