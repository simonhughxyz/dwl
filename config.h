/* appearance */
static const int sloppyfocus        = 0;  /* focus follows mouse */
static const int smartgaps          = 1;  /* 1 means no outer gap when there is only one window */
static const int monoclegaps        = 0;  /* 1 means outer gaps in monocle layout */
static const unsigned int borderpx  = 4;  /* border pixel of windows */
static const unsigned int gappih    = 10; /* horiz inner gap between windows */
static const unsigned int gappiv    = 10; /* vert inner gap between windows */
static const unsigned int gappoh    = 10; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10; /* vert outer gap between windows and screen edge */
static const int lockfullscreen     = 1;  /* 1 will force focus on the fullscreen window */
static const float rootcolor[]      = {0.3, 0.3, 0.3, 1.0};
static const float bordercolor[]    = {0.0, 0.0, 0.0, 0.5};
static const float focuscolor[]     = {1.0, 0.0, 1.0, 0.5};
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]  = {0.1, 0.1, 0.1, 1.0};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22" };

static const Rule rules[] = {
	/* x, y, width, heigh are floating only
	* When x or y == 0 the client is placed at the center of the screen,
	* when width or height == 0 the default size of the client is used*/

	/* app_id     title       tags mask     isfloating   monitor scratchkey  x    y    width  height */
	/* examples:
	{ "Gimp",       NULL,       0,            1,           -1, 	  0,   0, 	 0,   500,   400 },
	*/
	{ "firefox",  NULL,       1 << 8,       0,           -1,      0,   0, 	 0,   500,   400 },
	{ NULL,     "scratchpad", 0,            1,           -1,     's',  200,  100, 0,     0 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL },
	*/
	/* defaults */
	{ NULL,       0.55, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.options = NULL,
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE       
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS       
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER 
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;
static const int cursor_timeout = 5;

/* define modifer keys */
#define LOGO WLR_MODIFIER_LOGO
#define ALT WLR_MODIFIER_ALT
#define CTRL WLR_MODIFIER_CTRL
#define SHIFT WLR_MODIFIER_SHIFT

/* If you want to use the windows key change this to LOGO */
#define MODKEY ALT

/* default terminal */
#define TERMINAL "/usr/local/bin/st"

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper to launch terminal based application */
#define TERMCMD(class, title, cmd) SHCMD(TERMINAL " -c " class " -t " title " -e " cmd)

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    -1, KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  -1, KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,-1,SKEY,toggletag,  {.ui = 1 << TAG} }

#define VOLCMD(arg) SHCMD("/bin/pulsemixer " arg)

/* commands */
static const char *termcmd[] = { TERMINAL, NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier             chain, key                 function        argument */

    /* Volume Controls */
    { MODKEY,            -1,   XKB_KEY_equal,            spawn,          VOLCMD("--change-volume +5") }, \
    { MODKEY|CTRL,       -1,   XKB_KEY_equal,            spawn,          VOLCMD("--change-volume +1") }, \
    { MODKEY|SHIFT,      -1,   XKB_KEY_plus,             spawn,          VOLCMD("--change-volume +20") }, \
    { MODKEY,            -1,   XKB_KEY_minus,            spawn,          VOLCMD("--change-volume -5") }, \
    { MODKEY|CTRL,       -1,   XKB_KEY_minus,            spawn,          VOLCMD("--change-volume -1") }, \
    { MODKEY|SHIFT,      -1,   XKB_KEY_underscore,       spawn,          VOLCMD("--change-volume -20") }, \
	{ MODKEY,            -1,   XKB_KEY_m,                spawn,          VOLCMD("--toggle-mute") },

    /* Terminal Based Applications */
	{ MODKEY,            -1,   XKB_KEY_n,                spawn,          TERMCMD("neomutt", "neomutt", "neomutt") },
	{ MODKEY,            -1,   XKB_KEY_r,                spawn,          TERMCMD("newsboat", "newsboat", "newsboat") },
	{ MODKEY|SHIFT,      -1,   XKB_KEY_Return,           spawn,          TERMCMD("lf", "lf", "lf") },
	{ MODKEY,            -1,   XKB_KEY_b,                spawn,          TERMCMD("fxwm", "fxwm", "fxwm -E -D") },
	{ MODKEY|SHIFT,      -1,   XKB_KEY_B,                spawn,          TERMCMD("fxwm", "fxwm", "fxwm -E") },
	{ MODKEY,            -1,   XKB_KEY_t,                spawn,          TERMCMD("bottom", "bottom", "btm -b") },
	{ MODKEY|SHIFT,      -1,   XKB_KEY_T,                spawn,          TERMCMD("bottom", "bottom", "btm") },
	{ MODKEY,            -1,   XKB_KEY_p,                spawn,          TERMCMD("pulsemixer", "pulsemixer", "pulsemixer") },

	{ MODKEY,            -1,   XKB_KEY_Return,     spawn,          {.v = termcmd} },
	{ MODKEY,            -1,   XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,            -1,   XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY,            -1,   XKB_KEY_i,          incnmaster,     {.i = +1} },
	{ MODKEY,            -1,   XKB_KEY_d,          incnmaster,     {.i = -1} },
	{ MODKEY,            -1,   XKB_KEY_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,            -1,   XKB_KEY_l,          setmfact,       {.f = +0.05} },
	{ MODKEY,            -1,   XKB_KEY_z,          zoom,           {0} },
	{ MODKEY,            -1,   XKB_KEY_Tab,        view,           {0} },
	{ MODKEY,            -1,   XKB_KEY_BackSpace,  view,           {0} },
	{ MODKEY,            -1,   XKB_KEY_q,          killclient,     {0} },
	{ MODKEY,            -1,   XKB_KEY_Delete,     killclient,     {0} },
	{ MODKEY,            -1,   XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,            -1,   XKB_KEY_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,            -1,   XKB_KEY_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,            -1,   XKB_KEY_space,      setlayout,      {0} },
	{ MODKEY|SHIFT,      -1,   XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY,            -1,   XKB_KEY_e,         togglefullscreen, {0} },
	{ MODKEY,            -1,   XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|SHIFT,      -1,   XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,            -1,   XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,            -1,   XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|SHIFT,      -1,   XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|SHIFT,      -1,   XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1,   XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2,   XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3,   XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4,   XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5,   XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6,   XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7,   XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8,   XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9,   XKB_KEY_parenleft,                  8),
	TAGKEYS(          XKB_KEY_0,   XKB_KEY_parenright,                 10),
	TAGKEYS(          XKB_KEY_F1,  XKB_KEY_F1,                        11),
	TAGKEYS(          XKB_KEY_F2,  XKB_KEY_F2,                        12),
	TAGKEYS(          XKB_KEY_F3,  XKB_KEY_F3,                        13),
	TAGKEYS(          XKB_KEY_F4,  XKB_KEY_F4,                        14),
	TAGKEYS(          XKB_KEY_F5,  XKB_KEY_F5,                        15),
	TAGKEYS(          XKB_KEY_F6,  XKB_KEY_F6,                        16),
	TAGKEYS(          XKB_KEY_F7,  XKB_KEY_F7,                        17),
	TAGKEYS(          XKB_KEY_F8,  XKB_KEY_F8,                        18),
	TAGKEYS(          XKB_KEY_F9,  XKB_KEY_F9,                        19),
	TAGKEYS(          XKB_KEY_F10, XKB_KEY_F10,                      20),
	TAGKEYS(          XKB_KEY_F11, XKB_KEY_F11,                      21),
	TAGKEYS(          XKB_KEY_F12, XKB_KEY_F12,                      22),
	{ MODKEY|SHIFT,   -1, XKB_KEY_Q,                   quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ CTRL|ALT,       -1, XKB_KEY_Terminate_Server,    quit,           {0} },
#define CHVT(n) { CTRL|ALT,  -1, XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
