/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx	= 5; 
static const unsigned int snap		= 32;
static int floatposgrid_x			= 5;
static int floatposgrid_y			= 5;
static const int swallowfloating	= 0;        /* 1 means swallow floating windows by default */
static const char *toggle_float_pos	= "50% 50% 80% 80%"; 

static const unsigned int gappih	= 10;
static const unsigned int gappiv	= 10;
static const unsigned int gappoh	= 20;
static const unsigned int gappov	= 20;
static int smartgaps				= 0;

static const int showbar		= 1;
static const int topbar			= 1;
static const int user_bh		= 10;
static const int vertpad		= 20;
static const int sidepad		= 20;
static const char buttonbar[]	= "";
#define ICONSIZE (bh - 14)
#define ICONSPACING 8

static const char *fonts[]	= { "JetBrainsMono Nerd Font Propo:size=13",
								"JetBrainsMono Nerd Font Mono:style=ExtraBold:size=10" };

static char normfgcolor[]		= "#bbbbbb";
static char normbgcolor[]		= "#222222";
static char normbordercolor[]	= "#444444";

static char selfgcolor[]		= "#eeeeee";
static char selbgcolor[]		= "#005577";
static char selbordercolor[]	= "#005577";

static char floatbordercolor[]	= "#006688";

static char ltsymfgcolor[]		= "#dddd00";
static char ltsymbgcolor[]		= "#222222";

static char btnfgcolor[]		= "#eeeeee";
static char btnbgcolor[]		= "#dd0000";

static char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]	= { normfgcolor,		normbgcolor,	normbordercolor },
	[SchemeSel]		= { selfgcolor,			selbgcolor,		selbordercolor },
	[SchemeFloat]	= { NULL,				NULL,			floatbordercolor },
	[SchemeBtn]		= { btnfgcolor,			btnbgcolor,		NULL  },
	[SchemeLtSym]	= { ltsymfgcolor,		ltsymbgcolor,	NULL  },
	[SchemeTagsEm]	= { normbordercolor,	normbgcolor,	NULL  },
	[SchemeTagsOcc]	= { normfgcolor,		normbgcolor,	NULL  },
	[SchemeTagsSel]	= { selfgcolor,			selbgcolor,		NULL  },
};

static const char *const autostart[] = {
	"/usr/libexec/xfce-polkit", NULL,
	"superkeys", NULL,
	"pipewire", NULL,
	"dunst", NULL,
	"nitrogen", "--restore", NULL,
	"picom", "-b", NULL,
	"slstatus", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[]		= { "1", "2", "3", "4", "5", "6", "7", "8" };
static const int viewonrulestag	= 1;

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	{ .class = "Nwg-look", .isfloating = 1, .floatpos = "50% 50% -1h -1w" },
	{ .class = "Firefox", .tags = 1 << 1 },
	{ .class = "com.mitchellh.ghostty", .isterminal = 1 },
	{ .title = "Event Tester", .isfloating = 1, .noswallow = 1 },
};

/* layout(s) */
static const float mfact		= 0.50;
static const int nmaster		= 1;  
static const int resizehints	= 0; 
static const int lockfullscreen	= 1;
static const int refreshrate	= 120;

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",	tile },    /* first entry is default */
	{ "[M]",	monocle },
	{ "TTT",	bstack },
	{ ":::",	gaplessgrid },
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define SHIFTKEY ShiftMask
#define CTRLKEY ControlMask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,					KEY,	view,			{.ui = 1 << TAG} }, \
	{ MODKEY|CTRLKEY,			KEY,	toggleview,		{.ui = 1 << TAG} }, \
	{ MODKEY|SHIFTKEY,			KEY,	tag,			{.ui = 1 << TAG} }, \
	{ MODKEY|CTRLKEY|SHIFTKEY,	KEY,	toggletag,		{.ui = 1 << TAG} },

/* commands */
static const char *dmenucmd[]	= { "dmenu_run", "-l", "6", "-p", "Run: ",  NULL };
static const char *termcmd[]	= { "ghostty", NULL };
static const char *webcmd[]		= { "firefox", NULL };

#include <X11/XF86keysym.h>
static const char *mutevol[]	= { "volume", "--toggle", NULL };
static const char *mutemic[]	= { "volume", "--toggle-mic", NULL };
static const char *upvol[]		= { "volume", "--inc",	NULL };
static const char *downvol[]	= { "volume", "--dec",	NULL };
static const char *upbl[]		= { "brightness", "--inc", NULL };
static const char *downbl[]		= { "brightness", "--dec", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ ALTKEY,					XK_F1,						spawn,			{.v = dmenucmd } },
	{ MODKEY,					XK_w,						spawn,			{.v = webcmd } },
	{ MODKEY,					XK_Return,					spawn,			{.v = termcmd } },

	{ 0, 						XF86XK_AudioMute, 			spawn,			{.v = mutevol } },
	{ 0, 						XF86XK_AudioMicMute, 		spawn,			{.v = mutemic } },
	{ 0, 						XF86XK_AudioLowerVolume, 	spawn,			{.v = downvol } },
	{ 0, 						XF86XK_AudioRaiseVolume, 	spawn,			{.v = upvol } },
	{ 0, 						XF86XK_MonBrightnessUp, 	spawn,			{.v = upbl } },
	{ 0, 						XF86XK_MonBrightnessDown, 	spawn,			{.v = downbl } },


	{ MODKEY,					XK_j,						focusstack,     {.i = +1 } },
	{ MODKEY,					XK_k,						focusstack,     {.i = -1 } },
	{ MODKEY|SHIFTKEY,			XK_j,						rotatestack,    {.i = +1 } },
	{ MODKEY|SHIFTKEY,			XK_k,						rotatestack,    {.i = -1 } },
	{ MODKEY,					XK_i,						incnmaster,     {.i = +1 } },
	{ MODKEY,					XK_d,						incnmaster,     {.i = -1 } },
	{ MODKEY,					XK_h,						setmfact,       {.f = -0.05} },
	{ MODKEY,					XK_l,						setmfact,       {.f = +0.05} },
	{ MODKEY|SHIFTKEY,			XK_h,						setcfact,       {.f = +0.25} },
	{ MODKEY|SHIFTKEY,			XK_l,						setcfact,       {.f = -0.25} },
	{ MODKEY|SHIFTKEY,			XK_o,						setcfact,       {.f =  0.00} },
	{ MODKEY,					XK_q,						killclient,     {0} },
	{ MODKEY|SHIFTKEY,			XK_q,						quit,           {0} },
	{ MODKEY,					XK_t,						setlayout,      {.v = &layouts[0]} },
	{ MODKEY,					XK_m,						setlayout,      {.v = &layouts[1]} },
	{ MODKEY,					XK_b,						setlayout,      {.v = &layouts[2]} },
	{ MODKEY,					XK_g,						setlayout,      {.v = &layouts[3]} },
	{ MODKEY|SHIFTKEY,			XK_space,					togglefloating, {0} },
	{ MODKEY|SHIFTKEY,			XK_g,						togglegaps,		{0} },
	{ MODKEY|SHIFTKEY,			XK_b,						togglebar,     	{0} },
	{ MODKEY|SHIFTKEY,			XK_f,						togglefullscr,	{0} },
	{ MODKEY,					XK_F5,						xrdb,			{.v = NULL } },
	{ MODKEY,					XK_0,						view,			{.ui = ~0 } },
	{ MODKEY|SHIFTKEY,			XK_0,						tag,			{.ui = ~0 } },
	{ MODKEY,					XK_Right,					viewnext,		{0} },
	{ MODKEY,					XK_Left,					viewprev,		{0} },
	{ MODKEY|SHIFTKEY,			XK_Right,					tagtonext,		{0} },
	{ MODKEY|SHIFTKEY,			XK_Left,					tagtoprev,		{0} },
	TAGKEYS(					XK_1,						0)
	TAGKEYS(					XK_2,						1)
	TAGKEYS(					XK_3,						2)
	TAGKEYS(					XK_4,						3)
	TAGKEYS(					XK_5,						4)
	TAGKEYS(					XK_6,						5)
	TAGKEYS(					XK_7,						6)
	TAGKEYS(					XK_8,						7)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	{ ClkButton,		0,			Button1,	spawn,			{.v = dmenucmd } },
	{ ClkLtSymbol,		0,			Button1,	setlayout,		{0} },
	{ ClkLtSymbol,		0,			Button3,	setlayout,		{.v = &layouts[2]} },
	{ ClkWinTitle,		0,			Button2,	zoom,			{0} },
	{ ClkStatusText,	0,			Button2,	spawn,			{.v = termcmd } },
	{ ClkClientWin,		MODKEY,		Button1,	movemouse,		{0} },
	{ ClkClientWin,		MODKEY,		Button2,	togglefloating,	{0} },
	{ ClkClientWin,		MODKEY,		Button3,	resizemouse,	{0} },
	{ ClkTagBar,		0,			Button1,	view,			{0} },
	{ ClkTagBar,		0,			Button3,	toggleview,		{0} },
	{ ClkTagBar,		MODKEY,		Button1,	tag,			{0} },
	{ ClkTagBar,		MODKEY,		Button3,	toggletag,		{0} },
};

