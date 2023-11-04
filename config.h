/* See LICENSE file for copyright and license details. */
/* clang-format off */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static const int vertpadbar         = 2;        /* vertical padding for statusbar */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12:anti-alias=true:autohint=true", 
	                                      "NotoColorEmoji:size=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_fg[]          = "#f8f8f2";
static const char col_fg2[]         = "#50fa7b";
static const char col_bg1[]         = "#1e1e2e";
static const char col_bg2[]         = "#11111b";
static const char *colors[][3]      = {
	/*               fg      bg       border   */
	[SchemeNorm] = { col_fg, col_bg2, col_bg2 },
	[SchemeSel]  = { col_fg, col_bg1, col_bg1  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" , "10" };

static const char *const autostart[] = {
	"dwmblocks", NULL,
	"scritches", NULL,
	"mpdup", NULL,
	NULL /* terminate */
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Firefox", NULL,     NULL,           1 << 1,    0,          0,          -1,        -1 },
	{ "st",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "float",   NULL,     NULL,           0,         1,          1,           0,        -1 },
	{ "tabbed",  NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "Signal",  NULL,     NULL,           1 << 3,    0,          0,          -1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL, NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define DMENU_COLORS "-fn", dmenufont, "-nb", col_bg2, "-nf", col_fg, "-sb", col_bg1, "-sf", col_fg2

/* commands */
static const char *termcmd[] = {"tabbed", "-r", "2", "st", "-w", "''", NULL };
static const char *upbright[] 	= {"xbacklight", "+2", NULL};
static const char *downbright[] = {"xbacklight", "-2", NULL};
static const char *upvol[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%",     NULL };
static const char *downvol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%",     NULL };
static const char *mutevol[] = { "pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle",  NULL };

#include "shiftview.c"

static const Key keys[] = {
	{ MODKEY, XK_grave,	      spawn, {.v = (const char*[]){ "dmenu-emoji", DMENU_COLORS, NULL } } },
	{ MODKEY, XK_d,               spawn, {.v = (const char*[]){ "dmenu_run", DMENU_COLORS, NULL } } },
	{ MODKEY|ShiftMask, XK_d,     spawn, {.v = (const char*[]){ "passmenu", DMENU_COLORS, NULL } } },
	{ MODKEY, XK_s,               spawn, {.v = (const char*[]){ "st", "newsboat", NULL }  } },
	{ MODKEY, XK_a,               spawn, {.v = (const char*[]){ "st", "ncmpcpp" , NULL }  } },
	{ MODKEY, XK_e,               spawn, {.v = (const char*[]){ "st", "aerc" , NULL }  } },
	{ MODKEY|ShiftMask, XK_e,     spawn, {.v = (const char*[]){ "st", "-c", "xmpp", "profanity" , NULL }  } },
	{ MODKEY, XK_p,               spawn, {.v = (const char*[]){ "mpc", "toggle", NULL }  } },
	{ MODKEY, XK_bracketleft,     spawn, {.v = (const char*[]){ "mpc", "prev", NULL }  } },
	{ MODKEY, XK_bracketright,    spawn, {.v = (const char*[]){ "mpc", "next", NULL }  } },
	{ MODKEY, XK_backslash,	      spawn, {.v = (const char*[]){ "mpc", "clear", NULL }  } },
	{ MODKEY, XK_w,               spawn, {.v = (const char*[]){ "dmenu-notes", DMENU_COLORS, NULL } } },
	{ MODKEY, XK_x,               spawn, {.v = (const char*[]){ "dmenu-radio", DMENU_COLORS, NULL } } },
	{ MODKEY, XK_z,               spawn, {.v = (const char*[]){ "dmenu-playlists", "-z", DMENU_COLORS, NULL } } },
	{ MODKEY|ShiftMask,  XK_z,    spawn, {.v = (const char*[]){ "dmenu-playlists", DMENU_COLORS, NULL } } },
	
    	{ 0, XF86XK_MonBrightnessUp,   spawn, {.v = upbright}},
    	{ 0, XF86XK_MonBrightnessDown, spawn, {.v = downbright}},
	{ 0, XF86XK_AudioLowerVolume,  spawn, {.v = downvol } },
	{ 0, XF86XK_AudioMute, 	       spawn, {.v = mutevol } },
	{ 0, XF86XK_AudioRaiseVolume,  spawn, {.v = upvol   } },

	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,			XK_Print,  spawn,          {.v = (const char*[]){ "dmenu-maim", DMENU_COLORS, NULL } } },
	{ MODKEY|ControlMask,           XK_z,      spawn,          {.v = (const char*[]){ "shuffle-albums", NULL } } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    	{ MODKEY|ControlMask,           XK_j,      pushdown,       {0}},
    	{ MODKEY|ControlMask,           XK_k,      pushup,         {0}},
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ControlMask,           XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,              		XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,    		XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|ControlMask, 		XK_u,      defaultgaps,    {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,		XK_r,      quit,           {1} }, 
	{ MODKEY,                       XK_n,      shiftview,      {.i = +1} },
	{ MODKEY,                       XK_b,      shiftview,      {.i = -1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
/* clang-format on */
