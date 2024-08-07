/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char buttonbar[]       = " ";
#define ICONSIZE (bh - 8)
#define ICONSPACING 8 
static const char *fonts[]          = { "Noto Sans:size=24",
                                        "JetBrainsMono Nerd Font:style=Medium:size=22",
                                        "JetBrainsMono Nerd Font:style=Medium:size=26",
                                        "JetBrainsMono Nerd Font:style=ExtraBold:size=18" };

#include "themes/onedark.h"

static const char *colors[][4]      = {
	/*                      fg      bg          border  float */
	[SchemeNorm]        = { white,  black,      gray2,  gray2 },
	[SchemeSel]         = { white,  black,      blue,   pink  },
	[SchemeScratchNorm] = { white,  black,      gray2,  gray2 },
	[SchemeScratchSel]  = { white,  black,      red,    red   },
	[SchemeStButton]    = { green,  "#aa0000",  black,  black },
	[SchemeLtSymbol]    = { yellow, black,      black,  black },
    [SchemeTagEmpty]    = { gray2,  black,      black,  black },
    [SchemeTag1]        = { blue,   black,      black,  black },
    [SchemeTag2]        = { red,    black,      black,  black },
    [SchemeTag3]        = { orange, black,      black,  black },
    [SchemeTag4]        = { green,  black,      black,  black },
    [SchemeTag5]        = { pink,   black,      black,  black },
};

static const int tagschemes[] = {
    SchemeTag1, SchemeTag2, SchemeTag3, SchemeTag4, SchemeTag5
};

static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][4]      = {
    /*                      fg      bg        border       float */
    [SchemeNorm]        = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeSel]         = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeScratchNorm] = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeScratchSel]  = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeStButton]    = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeLtSymbol]    = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeTagEmpty]    = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeTag1]        = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeTag2]        = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeTag3]        = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeTag4]        = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeTag5]        = { OPAQUE, baralpha, borderalpha, borderalpha },
};

/* tagging */
/*static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8" };*/
static char *tags[] = { "", "", "", "", "" };


static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	{ .class = "Lxappearance", .isfloating = 1, .floatpos = "50% 50% -1w -1h" },
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
static const char *termcmd[]    = { "alacritty", NULL };
static const char *roficmd[]    = { "rofi", "-show", "drun", NULL };
static const char *firefoxcmd[] = { "firefox", NULL };

static const char *sptermcmd[]   = { "t", "alacritty", "--class", "spterm,spterm", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = firefoxcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = sptermcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_equal,  incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,  incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_g,      togglegaps,     {0} },
	{ MODKEY|ControlMask,           XK_g,      defaultgaps,    {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[11]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
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
	{ ClkButton,		    0,		        Button1,	    spawn,		    {.v = roficmd } },
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

