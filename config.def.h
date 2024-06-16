/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
#define ICONSIZE (bh - 8)   /* icon size */
#define ICONSPACING 10 /* space between icon and title */
static const char *fonts[]          = { "NotoSans Nerd Font:size=22",
										"NotoSans Nerd Font:size=20",
										"Noto Sans Symbols 2:size=22",
										"JetBrainsMono Nerd Font:style=ExtraBold:size=20" };

static char normfgcolor[]           = "#bbbbbb";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char selfgcolor[]            = "#eeeeee";
static char selbgcolor[]            = "#005577";
static char selbordercolor[]        = "#005577";
static char floatfgcolor[]          = "#eeeeee";
static char floatbgcolor[]          = "#005577";
static char floatbordercolor[]      = "#cc7788";
static char stickyfgcolor[]          = "#bbbbbb";
static char stickybgcolor[]          = "#222222";
static char stickybordercolor[]      = "#dddd00";
static char scratchnormfgcolor[]          = "#eeeeee";
static char scratchnormbgcolor[]          = "#005577";
static char scratchnormbordercolor[]      = "#cc7788";
static char scratchselfgcolor[]          = "#eeeeee";
static char scratchselbgcolor[]          = "#005577";
static char scratchselbordercolor[]      = "#cc7788";
static char tagsnormfgcolor[]           = "#444444";
static char tagsnormbgcolor[]           = "#222222";
static char tagsnormbordercolor[]       = "#222222";
static char tagsoccfgcolor[]           = "#bbbbbb";
static char tagsoccbgcolor[]           = "#222222";
static char tagsoccbordercolor[]       = "#222222";
static char tagsselfgcolor[]           = "#eeeeee";
static char tagsselbgcolor[]           = "#222222";
static char tagsselbordercolor[]       = "#222222";
static char ltsymbolfgcolor[]           = "#eeeeee";
static char ltsymbolbgcolor[]           = "#222222";
static char ltsymbolbordercolor[]       = "#dddd00";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
       [SchemeFloat]  = { floatfgcolor,  floatbgcolor,  floatbordercolor  },
       [SchemeSticky]  = { stickyfgcolor, stickybgcolor,  stickybordercolor  },
       [SchemeScratchNorm]  = { scratchnormfgcolor,  scratchnormbgcolor,  scratchnormbordercolor  },
       [SchemeScratchSel]  = { scratchselfgcolor,  scratchselbgcolor,  scratchselbordercolor  },
       [SchemeTagsNorm]  = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor  },
       [SchemeTagsOcc]  = { tagsoccfgcolor,  tagsoccbgcolor,  tagsoccbordercolor  },
       [SchemeTagsSel]  = { tagsselfgcolor,  tagsselbgcolor,  tagsselbordercolor  },
       [SchemeLtSymbol]  = { ltsymbolfgcolor,  ltsymbolbgcolor,  ltsymbolbordercolor  },
};

#include "termcolors.h"

static const unsigned int baralpha = 0xa0;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFloat]  = { OPAQUE, baralpha, borderalpha },
	[SchemeSticky]  = { OPAQUE, baralpha, borderalpha },
	[SchemeScratchNorm]  = { OPAQUE, baralpha, borderalpha },
	[SchemeScratchSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsNorm]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsOcc]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeLtSymbol]  = { OPAQUE, baralpha, borderalpha },
};

static const char *const autostart[] = {
	"/usr/libexec/polkit-gnome-authentication-agent-1", NULL,
	"nitrogen", "--restore", NULL,
	"picom", "-b", NULL,
	NULL /* terminate */
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = { "🯱", "🯲", "🯳", "🯴", "🯵", "🯶", "🯷", "🯸" };

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 1;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	{ .class = "Lxappearance", .isfloating = 1, .floatpos = "50% 50% -1h -1w" },
	{ .class = "Gimp", .isfloating = 1, .floatpos = "50% 50% -1h -1w" },
	{ .class = "pavucontrol", .isfloating = 1, .floatpos = "50% 50% -1h -1w" },
	{ .class = "Firefox", .tags = 1 << 1 },
	{ .class = "spterm", .scratchkey = 't', .isfloating = 1, .floatpos = "50% 50% 80% 80%" },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static int floatposgrid_x           = 5;        /* float grid columns */
static int floatposgrid_y           = 5;        /* float grid rows */
static const char *toggle_float_pos      = "50% 50% 80% 80%"; // default floating position when triggering togglefloating


#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
	{ NULL,       NULL },
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

/* commands */
static const char *termcmd[]  = { "alacritty", NULL };
static const char *roficmd[]  = { "rofi", "-show", "drun", NULL };

static const char *sptermcmd[] = { "t", "alacritty", "--class", "spterm,spterm", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_g,      togglescratch,  {.v = sptermcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Up,     incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_Down,   incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_g,      togglegaps,     {0} },
	{ MODKEY|ControlMask,           XK_g,      defaultgaps,    {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Left,   viewtoleft,     {0} },
	{ MODKEY,                       XK_Right,  viewtoright,    {0} }, 
	{ MODKEY|ShiftMask,             XK_Left,   tagandviewtoleft,   {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagandviewtoright,  {0} }, 
	{ MODKEY|ControlMask,           XK_Left,   tagtoleft,          {0} }, 
	{ MODKEY|ControlMask,           XK_Right,  tagtoright,         {0} }, 
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
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

