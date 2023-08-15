/* SPDX-License-Identifier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * Input event codes
 *
 *    *** IMPORTANT ***
 * This file is not only included from C-code but also from devicetree source
 * files. As such this file MUST only contain comments and defines.
 *
 * Copyright (c) 1999-2002 Vojtech Pavlik
 * Copyright (c) 2015 Hans de Goede <hdegoede@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */
#ifndef _LKL_INPUT_EVENT_CODES_H
#define _LKL_INPUT_EVENT_CODES_H

/*
 * Device properties and quirks
 */

#define LKL_INPUT_PROP_POINTER		0x00	/* needs a pointer */
#define LKL_INPUT_PROP_DIRECT		0x01	/* direct input devices */
#define LKL_INPUT_PROP_BUTTONPAD		0x02	/* has button(s) under pad */
#define LKL_INPUT_PROP_SEMI_MT		0x03	/* touch rectangle only */
#define LKL_INPUT_PROP_TOPBUTTONPAD		0x04	/* softbuttons at top of pad */
#define LKL_INPUT_PROP_POINTING_STICK	0x05	/* is a pointing stick */
#define LKL_INPUT_PROP_ACCELEROMETER	0x06	/* has accelerometer */

#define LKL_INPUT_PROP_MAX			0x1f
#define LKL_INPUT_PROP_CNT			(LKL_INPUT_PROP_MAX + 1)

/*
 * Event types
 */

#define LKL_EV_SYN			0x00
#define LKL_EV_KEY			0x01
#define LKL_EV_REL			0x02
#define LKL_EV_ABS			0x03
#define LKL_EV_MSC			0x04
#define LKL_EV_SW			0x05
#define LKL_EV_LED			0x11
#define LKL_EV_SND			0x12
#define LKL_EV_REP			0x14
#define LKL_EV_FF			0x15
#define LKL_EV_PWR			0x16
#define LKL_EV_FF_STATUS		0x17
#define LKL_EV_MAX			0x1f
#define LKL_EV_CNT			(LKL_EV_MAX+1)

/*
 * Synchronization events.
 */

#define LKL_SYN_REPORT		0
#define LKL_SYN_CONFIG		1
#define LKL_SYN_MT_REPORT		2
#define LKL_SYN_DROPPED		3
#define LKL_SYN_MAX			0xf
#define LKL_SYN_CNT			(LKL_SYN_MAX+1)

/*
 * Keys and buttons
 *
 * Most of the keys/buttons are modeled after USB HUT 1.12
 * (see http://www.usb.org/developers/hidpage).
 * Abbreviations in the comments:
 * AC - Application Control
 * AL - Application Launch Button
 * SC - System Control
 */

#define LKL_KEY_RESERVED		0
#define LKL_KEY_ESC			1
#define LKL_KEY_1			2
#define LKL_KEY_2			3
#define LKL_KEY_3			4
#define LKL_KEY_4			5
#define LKL_KEY_5			6
#define LKL_KEY_6			7
#define LKL_KEY_7			8
#define LKL_KEY_8			9
#define LKL_KEY_9			10
#define LKL_KEY_0			11
#define LKL_KEY_MINUS		12
#define LKL_KEY_EQUAL		13
#define LKL_KEY_BACKSPACE		14
#define LKL_KEY_TAB			15
#define LKL_KEY_Q			16
#define LKL_KEY_W			17
#define LKL_KEY_E			18
#define LKL_KEY_R			19
#define LKL_KEY_T			20
#define LKL_KEY_Y			21
#define LKL_KEY_U			22
#define LKL_KEY_I			23
#define LKL_KEY_O			24
#define LKL_KEY_P			25
#define LKL_KEY_LEFTBRACE		26
#define LKL_KEY_RIGHTBRACE		27
#define LKL_KEY_ENTER		28
#define LKL_KEY_LEFTCTRL		29
#define LKL_KEY_A			30
#define LKL_KEY_S			31
#define LKL_KEY_D			32
#define LKL_KEY_F			33
#define LKL_KEY_G			34
#define LKL_KEY_H			35
#define LKL_KEY_J			36
#define LKL_KEY_K			37
#define LKL_KEY_L			38
#define LKL_KEY_SEMICOLON		39
#define LKL_KEY_APOSTROPHE		40
#define LKL_KEY_GRAVE		41
#define LKL_KEY_LEFTSHIFT		42
#define LKL_KEY_BACKSLASH		43
#define LKL_KEY_Z			44
#define LKL_KEY_X			45
#define LKL_KEY_C			46
#define LKL_KEY_V			47
#define LKL_KEY_B			48
#define LKL_KEY_N			49
#define LKL_KEY_M			50
#define LKL_KEY_COMMA		51
#define LKL_KEY_DOT			52
#define LKL_KEY_SLASH		53
#define LKL_KEY_RIGHTSHIFT		54
#define LKL_KEY_KPASTERISK		55
#define LKL_KEY_LEFTALT		56
#define LKL_KEY_SPACE		57
#define LKL_KEY_CAPSLOCK		58
#define LKL_KEY_F1			59
#define LKL_KEY_F2			60
#define LKL_KEY_F3			61
#define LKL_KEY_F4			62
#define LKL_KEY_F5			63
#define LKL_KEY_F6			64
#define LKL_KEY_F7			65
#define LKL_KEY_F8			66
#define LKL_KEY_F9			67
#define LKL_KEY_F10			68
#define LKL_KEY_NUMLOCK		69
#define LKL_KEY_SCROLLLOCK		70
#define LKL_KEY_KP7			71
#define LKL_KEY_KP8			72
#define LKL_KEY_KP9			73
#define LKL_KEY_KPMINUS		74
#define LKL_KEY_KP4			75
#define LKL_KEY_KP5			76
#define LKL_KEY_KP6			77
#define LKL_KEY_KPPLUS		78
#define LKL_KEY_KP1			79
#define LKL_KEY_KP2			80
#define LKL_KEY_KP3			81
#define LKL_KEY_KP0			82
#define LKL_KEY_KPDOT		83

#define LKL_KEY_ZENKAKUHANKAKU	85
#define LKL_KEY_102ND		86
#define LKL_KEY_F11			87
#define LKL_KEY_F12			88
#define LKL_KEY_RO			89
#define LKL_KEY_KATAKANA		90
#define LKL_KEY_HIRAGANA		91
#define LKL_KEY_HENKAN		92
#define LKL_KEY_KATAKANAHIRAGANA	93
#define LKL_KEY_MUHENKAN		94
#define LKL_KEY_KPJPCOMMA		95
#define LKL_KEY_KPENTER		96
#define LKL_KEY_RIGHTCTRL		97
#define LKL_KEY_KPSLASH		98
#define LKL_KEY_SYSRQ		99
#define LKL_KEY_RIGHTALT		100
#define LKL_KEY_LINEFEED		101
#define LKL_KEY_HOME		102
#define LKL_KEY_UP			103
#define LKL_KEY_PAGEUP		104
#define LKL_KEY_LEFT		105
#define LKL_KEY_RIGHT		106
#define LKL_KEY_END			107
#define LKL_KEY_DOWN		108
#define LKL_KEY_PAGEDOWN		109
#define LKL_KEY_INSERT		110
#define LKL_KEY_DELETE		111
#define LKL_KEY_MACRO		112
#define LKL_KEY_MUTE		113
#define LKL_KEY_VOLUMEDOWN		114
#define LKL_KEY_VOLUMEUP		115
#define LKL_KEY_POWER		116	/* SC System Power Down */
#define LKL_KEY_KPEQUAL		117
#define LKL_KEY_KPPLUSMINUS		118
#define LKL_KEY_PAUSE		119
#define LKL_KEY_SCALE		120	/* AL Compiz Scale (Expose) */

#define LKL_KEY_KPCOMMA		121
#define LKL_KEY_HANGEUL		122
#define LKL_KEY_HANGUEL		LKL_KEY_HANGEUL
#define LKL_KEY_HANJA		123
#define LKL_KEY_YEN			124
#define LKL_KEY_LEFTMETA		125
#define LKL_KEY_RIGHTMETA		126
#define LKL_KEY_COMPOSE		127

#define LKL_KEY_STOP		128	/* AC Stop */
#define LKL_KEY_AGAIN		129
#define LKL_KEY_PROPS		130	/* AC Properties */
#define LKL_KEY_UNDO		131	/* AC Undo */
#define LKL_KEY_FRONT		132
#define LKL_KEY_COPY		133	/* AC Copy */
#define LKL_KEY_OPEN		134	/* AC Open */
#define LKL_KEY_PASTE		135	/* AC Paste */
#define LKL_KEY_FIND		136	/* AC Search */
#define LKL_KEY_CUT			137	/* AC Cut */
#define LKL_KEY_HELP		138	/* AL Integrated Help Center */
#define LKL_KEY_MENU		139	/* Menu (show menu) */
#define LKL_KEY_CALC		140	/* AL Calculator */
#define LKL_KEY_SETUP		141
#define LKL_KEY_SLEEP		142	/* SC System Sleep */
#define LKL_KEY_WAKEUP		143	/* System Wake Up */
#define LKL_KEY_FILE		144	/* AL Local Machine Browser */
#define LKL_KEY_SENDFILE		145
#define LKL_KEY_DELETEFILE		146
#define LKL_KEY_XFER		147
#define LKL_KEY_PROG1		148
#define LKL_KEY_PROG2		149
#define LKL_KEY_WWW			150	/* AL Internet Browser */
#define LKL_KEY_MSDOS		151
#define LKL_KEY_COFFEE		152	/* AL Terminal Lock/Screensaver */
#define LKL_KEY_SCREENLOCK		LKL_KEY_COFFEE
#define LKL_KEY_ROTATE_DISPLAY	153	/* Display orientation for e.g. tablets */
#define LKL_KEY_DIRECTION		LKL_KEY_ROTATE_DISPLAY
#define LKL_KEY_CYCLEWINDOWS	154
#define LKL_KEY_MAIL		155
#define LKL_KEY_BOOKMARKS		156	/* AC Bookmarks */
#define LKL_KEY_COMPUTER		157
#define LKL_KEY_BACK		158	/* AC Back */
#define LKL_KEY_FORWARD		159	/* AC Forward */
#define LKL_KEY_CLOSECD		160
#define LKL_KEY_EJECTCD		161
#define LKL_KEY_EJECTCLOSECD	162
#define LKL_KEY_NEXTSONG		163
#define LKL_KEY_PLAYPAUSE		164
#define LKL_KEY_PREVIOUSSONG	165
#define LKL_KEY_STOPCD		166
#define LKL_KEY_RECORD		167
#define LKL_KEY_REWIND		168
#define LKL_KEY_PHONE		169	/* Media Select Telephone */
#define LKL_KEY_ISO			170
#define LKL_KEY_CONFIG		171	/* AL Consumer Control Configuration */
#define LKL_KEY_HOMEPAGE		172	/* AC Home */
#define LKL_KEY_REFRESH		173	/* AC Refresh */
#define LKL_KEY_EXIT		174	/* AC Exit */
#define LKL_KEY_MOVE		175
#define LKL_KEY_EDIT		176
#define LKL_KEY_SCROLLUP		177
#define LKL_KEY_SCROLLDOWN		178
#define LKL_KEY_KPLEFTPAREN		179
#define LKL_KEY_KPRIGHTPAREN	180
#define LKL_KEY_NEW			181	/* AC New */
#define LKL_KEY_REDO		182	/* AC Redo/Repeat */

#define LKL_KEY_F13			183
#define LKL_KEY_F14			184
#define LKL_KEY_F15			185
#define LKL_KEY_F16			186
#define LKL_KEY_F17			187
#define LKL_KEY_F18			188
#define LKL_KEY_F19			189
#define LKL_KEY_F20			190
#define LKL_KEY_F21			191
#define LKL_KEY_F22			192
#define LKL_KEY_F23			193
#define LKL_KEY_F24			194

#define LKL_KEY_PLAYCD		200
#define LKL_KEY_PAUSECD		201
#define LKL_KEY_PROG3		202
#define LKL_KEY_PROG4		203
#define LKL_KEY_ALL_APPLICATIONS	204	/* AC Desktop Show All Applications */
#define LKL_KEY_DASHBOARD		LKL_KEY_ALL_APPLICATIONS
#define LKL_KEY_SUSPEND		205
#define LKL_KEY_CLOSE		206	/* AC Close */
#define LKL_KEY_PLAY		207
#define LKL_KEY_FASTFORWARD		208
#define LKL_KEY_BASSBOOST		209
#define LKL_KEY_PRINT		210	/* AC Print */
#define LKL_KEY_HP			211
#define LKL_KEY_CAMERA		212
#define LKL_KEY_SOUND		213
#define LKL_KEY_QUESTION		214
#define LKL_KEY_EMAIL		215
#define LKL_KEY_CHAT		216
#define LKL_KEY_SEARCH		217
#define LKL_KEY_CONNECT		218
#define LKL_KEY_FINANCE		219	/* AL Checkbook/Finance */
#define LKL_KEY_SPORT		220
#define LKL_KEY_SHOP		221
#define LKL_KEY_ALTERASE		222
#define LKL_KEY_CANCEL		223	/* AC Cancel */
#define LKL_KEY_BRIGHTNESSDOWN	224
#define LKL_KEY_BRIGHTNESSUP	225
#define LKL_KEY_MEDIA		226

#define LKL_KEY_SWITCHVIDEOMODE	227	/* Cycle between available video
					   outputs (Monitor/LCD/TV-out/etc) */
#define LKL_KEY_KBDILLUMTOGGLE	228
#define LKL_KEY_KBDILLUMDOWN	229
#define LKL_KEY_KBDILLUMUP		230

#define LKL_KEY_SEND		231	/* AC Send */
#define LKL_KEY_REPLY		232	/* AC Reply */
#define LKL_KEY_FORWARDMAIL		233	/* AC Forward Msg */
#define LKL_KEY_SAVE		234	/* AC Save */
#define LKL_KEY_DOCUMENTS		235

#define LKL_KEY_BATTERY		236

#define LKL_KEY_BLUETOOTH		237
#define LKL_KEY_WLAN		238
#define LKL_KEY_UWB			239

#define LKL_KEY_UNKNOWN		240

#define LKL_KEY_VIDEO_NEXT		241	/* drive next video source */
#define LKL_KEY_VIDEO_PREV		242	/* drive previous video source */
#define LKL_KEY_BRIGHTNESS_CYCLE	243	/* brightness up, after max is min */
#define LKL_KEY_BRIGHTNESS_AUTO	244	/* Set Auto Brightness: manual
					  brightness control is off,
					  rely on ambient */
#define LKL_KEY_BRIGHTNESS_ZERO	LKL_KEY_BRIGHTNESS_AUTO
#define LKL_KEY_DISPLAY_OFF		245	/* display device to off state */

#define LKL_KEY_WWAN		246	/* Wireless WAN (LTE, UMTS, GSM, etc.) */
#define LKL_KEY_WIMAX		LKL_KEY_WWAN
#define LKL_KEY_RFKILL		247	/* Key that controls all radios */

#define LKL_KEY_MICMUTE		248	/* Mute / unmute the microphone */

/* Code 255 is reserved for special needs of AT keyboard driver */

#define LKL_BTN_MISC		0x100
#define LKL_BTN_0			0x100
#define LKL_BTN_1			0x101
#define LKL_BTN_2			0x102
#define LKL_BTN_3			0x103
#define LKL_BTN_4			0x104
#define LKL_BTN_5			0x105
#define LKL_BTN_6			0x106
#define LKL_BTN_7			0x107
#define LKL_BTN_8			0x108
#define LKL_BTN_9			0x109

#define LKL_BTN_MOUSE		0x110
#define LKL_BTN_LEFT		0x110
#define LKL_BTN_RIGHT		0x111
#define LKL_BTN_MIDDLE		0x112
#define LKL_BTN_SIDE		0x113
#define LKL_BTN_EXTRA		0x114
#define LKL_BTN_FORWARD		0x115
#define LKL_BTN_BACK		0x116
#define LKL_BTN_TASK		0x117

#define LKL_BTN_JOYSTICK		0x120
#define LKL_BTN_TRIGGER		0x120
#define LKL_BTN_THUMB		0x121
#define LKL_BTN_THUMB2		0x122
#define LKL_BTN_TOP			0x123
#define LKL_BTN_TOP2		0x124
#define LKL_BTN_PINKIE		0x125
#define LKL_BTN_BASE		0x126
#define LKL_BTN_BASE2		0x127
#define LKL_BTN_BASE3		0x128
#define LKL_BTN_BASE4		0x129
#define LKL_BTN_BASE5		0x12a
#define LKL_BTN_BASE6		0x12b
#define LKL_BTN_DEAD		0x12f

#define LKL_BTN_GAMEPAD		0x130
#define LKL_BTN_SOUTH		0x130
#define LKL_BTN_A			LKL_BTN_SOUTH
#define LKL_BTN_EAST		0x131
#define LKL_BTN_B			LKL_BTN_EAST
#define LKL_BTN_C			0x132
#define LKL_BTN_NORTH		0x133
#define LKL_BTN_X			LKL_BTN_NORTH
#define LKL_BTN_WEST		0x134
#define LKL_BTN_Y			LKL_BTN_WEST
#define LKL_BTN_Z			0x135
#define LKL_BTN_TL			0x136
#define LKL_BTN_TR			0x137
#define LKL_BTN_TL2			0x138
#define LKL_BTN_TR2			0x139
#define LKL_BTN_SELECT		0x13a
#define LKL_BTN_START		0x13b
#define LKL_BTN_MODE		0x13c
#define LKL_BTN_THUMBL		0x13d
#define LKL_BTN_THUMBR		0x13e

#define LKL_BTN_DIGI		0x140
#define LKL_BTN_TOOL_PEN		0x140
#define LKL_BTN_TOOL_RUBBER		0x141
#define LKL_BTN_TOOL_BRUSH		0x142
#define LKL_BTN_TOOL_PENCIL		0x143
#define LKL_BTN_TOOL_AIRBRUSH	0x144
#define LKL_BTN_TOOL_FINGER		0x145
#define LKL_BTN_TOOL_MOUSE		0x146
#define LKL_BTN_TOOL_LENS		0x147
#define LKL_BTN_TOOL_QUINTTAP	0x148	/* Five fingers on trackpad */
#define LKL_BTN_STYLUS3		0x149
#define LKL_BTN_TOUCH		0x14a
#define LKL_BTN_STYLUS		0x14b
#define LKL_BTN_STYLUS2		0x14c
#define LKL_BTN_TOOL_DOUBLETAP	0x14d
#define LKL_BTN_TOOL_TRIPLETAP	0x14e
#define LKL_BTN_TOOL_QUADTAP	0x14f	/* Four fingers on trackpad */

#define LKL_BTN_WHEEL		0x150
#define LKL_BTN_GEAR_DOWN		0x150
#define LKL_BTN_GEAR_UP		0x151

#define LKL_KEY_OK			0x160
#define LKL_KEY_SELECT		0x161
#define LKL_KEY_GOTO		0x162
#define LKL_KEY_CLEAR		0x163
#define LKL_KEY_POWER2		0x164
#define LKL_KEY_OPTION		0x165
#define LKL_KEY_INFO		0x166	/* AL OEM Features/Tips/Tutorial */
#define LKL_KEY_TIME		0x167
#define LKL_KEY_VENDOR		0x168
#define LKL_KEY_ARCHIVE		0x169
#define LKL_KEY_PROGRAM		0x16a	/* Media Select Program Guide */
#define LKL_KEY_CHANNEL		0x16b
#define LKL_KEY_FAVORITES		0x16c
#define LKL_KEY_EPG			0x16d
#define LKL_KEY_PVR			0x16e	/* Media Select Home */
#define LKL_KEY_MHP			0x16f
#define LKL_KEY_LANGUAGE		0x170
#define LKL_KEY_TITLE		0x171
#define LKL_KEY_SUBTITLE		0x172
#define LKL_KEY_ANGLE		0x173
#define LKL_KEY_FULL_SCREEN		0x174	/* AC View Toggle */
#define LKL_KEY_ZOOM		LKL_KEY_FULL_SCREEN
#define LKL_KEY_MODE		0x175
#define LKL_KEY_KEYBOARD		0x176
#define LKL_KEY_ASPECT_RATIO	0x177	/* HUTRR37: Aspect */
#define LKL_KEY_SCREEN		LKL_KEY_ASPECT_RATIO
#define LKL_KEY_PC			0x178	/* Media Select Computer */
#define LKL_KEY_TV			0x179	/* Media Select TV */
#define LKL_KEY_TV2			0x17a	/* Media Select Cable */
#define LKL_KEY_VCR			0x17b	/* Media Select VCR */
#define LKL_KEY_VCR2		0x17c	/* VCR Plus */
#define LKL_KEY_SAT			0x17d	/* Media Select Satellite */
#define LKL_KEY_SAT2		0x17e
#define LKL_KEY_CD			0x17f	/* Media Select CD */
#define LKL_KEY_TAPE		0x180	/* Media Select Tape */
#define LKL_KEY_RADIO		0x181
#define LKL_KEY_TUNER		0x182	/* Media Select Tuner */
#define LKL_KEY_PLAYER		0x183
#define LKL_KEY_TEXT		0x184
#define LKL_KEY_DVD			0x185	/* Media Select DVD */
#define LKL_KEY_AUX			0x186
#define LKL_KEY_MP3			0x187
#define LKL_KEY_AUDIO		0x188	/* AL Audio Browser */
#define LKL_KEY_VIDEO		0x189	/* AL Movie Browser */
#define LKL_KEY_DIRECTORY		0x18a
#define LKL_KEY_LIST		0x18b
#define LKL_KEY_MEMO		0x18c	/* Media Select Messages */
#define LKL_KEY_CALENDAR		0x18d
#define LKL_KEY_RED			0x18e
#define LKL_KEY_GREEN		0x18f
#define LKL_KEY_YELLOW		0x190
#define LKL_KEY_BLUE		0x191
#define LKL_KEY_CHANNELUP		0x192	/* Channel Increment */
#define LKL_KEY_CHANNELDOWN		0x193	/* Channel Decrement */
#define LKL_KEY_FIRST		0x194
#define LKL_KEY_LAST		0x195	/* Recall Last */
#define LKL_KEY_AB			0x196
#define LKL_KEY_NEXT		0x197
#define LKL_KEY_RESTART		0x198
#define LKL_KEY_SLOW		0x199
#define LKL_KEY_SHUFFLE		0x19a
#define LKL_KEY_BREAK		0x19b
#define LKL_KEY_PREVIOUS		0x19c
#define LKL_KEY_DIGITS		0x19d
#define LKL_KEY_TEEN		0x19e
#define LKL_KEY_TWEN		0x19f
#define LKL_KEY_VIDEOPHONE		0x1a0	/* Media Select Video Phone */
#define LKL_KEY_GAMES		0x1a1	/* Media Select Games */
#define LKL_KEY_ZOOMIN		0x1a2	/* AC Zoom In */
#define LKL_KEY_ZOOMOUT		0x1a3	/* AC Zoom Out */
#define LKL_KEY_ZOOMRESET		0x1a4	/* AC Zoom */
#define LKL_KEY_WORDPROCESSOR	0x1a5	/* AL Word Processor */
#define LKL_KEY_EDITOR		0x1a6	/* AL Text Editor */
#define LKL_KEY_SPREADSHEET		0x1a7	/* AL Spreadsheet */
#define LKL_KEY_GRAPHICSEDITOR	0x1a8	/* AL Graphics Editor */
#define LKL_KEY_PRESENTATION	0x1a9	/* AL Presentation App */
#define LKL_KEY_DATABASE		0x1aa	/* AL Database App */
#define LKL_KEY_NEWS		0x1ab	/* AL Newsreader */
#define LKL_KEY_VOICEMAIL		0x1ac	/* AL Voicemail */
#define LKL_KEY_ADDRESSBOOK		0x1ad	/* AL Contacts/Address Book */
#define LKL_KEY_MESSENGER		0x1ae	/* AL Instant Messaging */
#define LKL_KEY_DISPLAYTOGGLE	0x1af	/* Turn display (LCD) on and off */
#define LKL_KEY_BRIGHTNESS_TOGGLE	LKL_KEY_DISPLAYTOGGLE
#define LKL_KEY_SPELLCHECK		0x1b0   /* AL Spell Check */
#define LKL_KEY_LOGOFF		0x1b1   /* AL Logoff */

#define LKL_KEY_DOLLAR		0x1b2
#define LKL_KEY_EURO		0x1b3

#define LKL_KEY_FRAMEBACK		0x1b4	/* Consumer - transport controls */
#define LKL_KEY_FRAMEFORWARD	0x1b5
#define LKL_KEY_CONTEXT_MENU	0x1b6	/* GenDesc - system context menu */
#define LKL_KEY_MEDIA_REPEAT	0x1b7	/* Consumer - transport control */
#define LKL_KEY_10CHANNELSUP	0x1b8	/* 10 channels up (10+) */
#define LKL_KEY_10CHANNELSDOWN	0x1b9	/* 10 channels down (10-) */
#define LKL_KEY_IMAGES		0x1ba	/* AL Image Browser */
#define LKL_KEY_NOTIFICATION_CENTER	0x1bc	/* Show/hide the notification center */
#define LKL_KEY_PICKUP_PHONE	0x1bd	/* Answer incoming call */
#define LKL_KEY_HANGUP_PHONE	0x1be	/* Decline incoming call */

#define LKL_KEY_DEL_EOL		0x1c0
#define LKL_KEY_DEL_EOS		0x1c1
#define LKL_KEY_INS_LINE		0x1c2
#define LKL_KEY_DEL_LINE		0x1c3

#define LKL_KEY_FN			0x1d0
#define LKL_KEY_FN_ESC		0x1d1
#define LKL_KEY_FN_F1		0x1d2
#define LKL_KEY_FN_F2		0x1d3
#define LKL_KEY_FN_F3		0x1d4
#define LKL_KEY_FN_F4		0x1d5
#define LKL_KEY_FN_F5		0x1d6
#define LKL_KEY_FN_F6		0x1d7
#define LKL_KEY_FN_F7		0x1d8
#define LKL_KEY_FN_F8		0x1d9
#define LKL_KEY_FN_F9		0x1da
#define LKL_KEY_FN_F10		0x1db
#define LKL_KEY_FN_F11		0x1dc
#define LKL_KEY_FN_F12		0x1dd
#define LKL_KEY_FN_1		0x1de
#define LKL_KEY_FN_2		0x1df
#define LKL_KEY_FN_D		0x1e0
#define LKL_KEY_FN_E		0x1e1
#define LKL_KEY_FN_F		0x1e2
#define LKL_KEY_FN_S		0x1e3
#define LKL_KEY_FN_B		0x1e4
#define LKL_KEY_FN_RIGHT_SHIFT	0x1e5

#define LKL_KEY_BRL_DOT1		0x1f1
#define LKL_KEY_BRL_DOT2		0x1f2
#define LKL_KEY_BRL_DOT3		0x1f3
#define LKL_KEY_BRL_DOT4		0x1f4
#define LKL_KEY_BRL_DOT5		0x1f5
#define LKL_KEY_BRL_DOT6		0x1f6
#define LKL_KEY_BRL_DOT7		0x1f7
#define LKL_KEY_BRL_DOT8		0x1f8
#define LKL_KEY_BRL_DOT9		0x1f9
#define LKL_KEY_BRL_DOT10		0x1fa

#define LKL_KEY_NUMERIC_0		0x200	/* used by phones, remote controls, */
#define LKL_KEY_NUMERIC_1		0x201	/* and other keypads */
#define LKL_KEY_NUMERIC_2		0x202
#define LKL_KEY_NUMERIC_3		0x203
#define LKL_KEY_NUMERIC_4		0x204
#define LKL_KEY_NUMERIC_5		0x205
#define LKL_KEY_NUMERIC_6		0x206
#define LKL_KEY_NUMERIC_7		0x207
#define LKL_KEY_NUMERIC_8		0x208
#define LKL_KEY_NUMERIC_9		0x209
#define LKL_KEY_NUMERIC_STAR	0x20a
#define LKL_KEY_NUMERIC_POUND	0x20b
#define LKL_KEY_NUMERIC_A		0x20c	/* Phone key A - HUT Telephony 0xb9 */
#define LKL_KEY_NUMERIC_B		0x20d
#define LKL_KEY_NUMERIC_C		0x20e
#define LKL_KEY_NUMERIC_D		0x20f

#define LKL_KEY_CAMERA_FOCUS	0x210
#define LKL_KEY_WPS_BUTTON		0x211	/* WiFi Protected Setup key */

#define LKL_KEY_TOUCHPAD_TOGGLE	0x212	/* Request switch touchpad on or off */
#define LKL_KEY_TOUCHPAD_ON		0x213
#define LKL_KEY_TOUCHPAD_OFF	0x214

#define LKL_KEY_CAMERA_ZOOMIN	0x215
#define LKL_KEY_CAMERA_ZOOMOUT	0x216
#define LKL_KEY_CAMERA_UP		0x217
#define LKL_KEY_CAMERA_DOWN		0x218
#define LKL_KEY_CAMERA_LEFT		0x219
#define LKL_KEY_CAMERA_RIGHT	0x21a

#define LKL_KEY_ATTENDANT_ON	0x21b
#define LKL_KEY_ATTENDANT_OFF	0x21c
#define LKL_KEY_ATTENDANT_TOGGLE	0x21d	/* Attendant call on or off */
#define LKL_KEY_LIGHTS_TOGGLE	0x21e	/* Reading light on or off */

#define LKL_BTN_DPAD_UP		0x220
#define LKL_BTN_DPAD_DOWN		0x221
#define LKL_BTN_DPAD_LEFT		0x222
#define LKL_BTN_DPAD_RIGHT		0x223

#define LKL_KEY_ALS_TOGGLE		0x230	/* Ambient light sensor */
#define LKL_KEY_ROTATE_LOCK_TOGGLE	0x231	/* Display rotation lock */

#define LKL_KEY_BUTTONCONFIG		0x240	/* AL Button Configuration */
#define LKL_KEY_TASKMANAGER		0x241	/* AL Task/Project Manager */
#define LKL_KEY_JOURNAL		0x242	/* AL Log/Journal/Timecard */
#define LKL_KEY_CONTROLPANEL		0x243	/* AL Control Panel */
#define LKL_KEY_APPSELECT		0x244	/* AL Select Task/Application */
#define LKL_KEY_SCREENSAVER		0x245	/* AL Screen Saver */
#define LKL_KEY_VOICECOMMAND		0x246	/* Listening Voice Command */
#define LKL_KEY_ASSISTANT		0x247	/* AL Context-aware desktop assistant */
#define LKL_KEY_KBD_LAYOUT_NEXT	0x248	/* AC Next Keyboard Layout Select */
#define LKL_KEY_EMOJI_PICKER	0x249	/* Show/hide emoji picker (HUTRR101) */
#define LKL_KEY_DICTATE		0x24a	/* Start or Stop Voice Dictation Session (HUTRR99) */

#define LKL_KEY_BRIGHTNESS_MIN		0x250	/* Set Brightness to Minimum */
#define LKL_KEY_BRIGHTNESS_MAX		0x251	/* Set Brightness to Maximum */

#define LKL_KEY_KBDINPUTASSIST_PREV		0x260
#define LKL_KEY_KBDINPUTASSIST_NEXT		0x261
#define LKL_KEY_KBDINPUTASSIST_PREVGROUP		0x262
#define LKL_KEY_KBDINPUTASSIST_NEXTGROUP		0x263
#define LKL_KEY_KBDINPUTASSIST_ACCEPT		0x264
#define LKL_KEY_KBDINPUTASSIST_CANCEL		0x265

/* Diagonal movement keys */
#define LKL_KEY_RIGHT_UP			0x266
#define LKL_KEY_RIGHT_DOWN			0x267
#define LKL_KEY_LEFT_UP			0x268
#define LKL_KEY_LEFT_DOWN			0x269

#define LKL_KEY_ROOT_MENU			0x26a /* Show Device's Root Menu */
/* Show Top Menu of the Media (e.g. DVD) */
#define LKL_KEY_MEDIA_TOP_MENU		0x26b
#define LKL_KEY_NUMERIC_11			0x26c
#define LKL_KEY_NUMERIC_12			0x26d
/*
 * Toggle Audio Description: refers to an audio service that helps blind and
 * visually impaired consumers understand the action in a program. Note: in
 * some countries this is referred to as "Video Description".
 */
#define LKL_KEY_AUDIO_DESC			0x26e
#define LKL_KEY_3D_MODE			0x26f
#define LKL_KEY_NEXT_FAVORITE		0x270
#define LKL_KEY_STOP_RECORD			0x271
#define LKL_KEY_PAUSE_RECORD		0x272
#define LKL_KEY_VOD				0x273 /* Video on Demand */
#define LKL_KEY_UNMUTE			0x274
#define LKL_KEY_FASTREVERSE			0x275
#define LKL_KEY_SLOWREVERSE			0x276
/*
 * Control a data application associated with the currently viewed channel,
 * e.g. teletext or data broadcast application (MHEG, MHP, HbbTV, etc.)
 */
#define LKL_KEY_DATA			0x277
#define LKL_KEY_ONSCREEN_KEYBOARD		0x278
/* Electronic privacy screen control */
#define LKL_KEY_PRIVACY_SCREEN_TOGGLE	0x279

/* Select an area of screen to be copied */
#define LKL_KEY_SELECTIVE_SCREENSHOT	0x27a

/* Move the focus to the next or previous user controllable element within a UI container */
#define LKL_KEY_NEXT_ELEMENT               0x27b
#define LKL_KEY_PREVIOUS_ELEMENT           0x27c

/* Toggle Autopilot engagement */
#define LKL_KEY_AUTOPILOT_ENGAGE_TOGGLE    0x27d

/* Shortcut Keys */
#define LKL_KEY_MARK_WAYPOINT              0x27e
#define LKL_KEY_SOS                                0x27f
#define LKL_KEY_NAV_CHART                  0x280
#define LKL_KEY_FISHING_CHART              0x281
#define LKL_KEY_SINGLE_RANGE_RADAR         0x282
#define LKL_KEY_DUAL_RANGE_RADAR           0x283
#define LKL_KEY_RADAR_OVERLAY              0x284
#define LKL_KEY_TRADITIONAL_SONAR          0x285
#define LKL_KEY_CLEARVU_SONAR              0x286
#define LKL_KEY_SIDEVU_SONAR               0x287
#define LKL_KEY_NAV_INFO                   0x288
#define LKL_KEY_BRIGHTNESS_MENU            0x289

/*
 * Some keyboards have keys which do not have a defined meaning, these keys
 * are intended to be programmed / bound to macros by the user. For most
 * keyboards with these macro-keys the key-sequence to inject, or action to
 * take, is all handled by software on the host side. So from the kernel's
 * point of view these are just normal keys.
 *
 * The LKL_KEY_MACRO# codes below are intended for such keys, which may be labeled
 * e.g. G1-G18, or S1 - S30. The LKL_KEY_MACRO# codes MUST NOT be used for keys
 * where the marking on the key does indicate a defined meaning / purpose.
 *
 * The LKL_KEY_MACRO# codes MUST also NOT be used as fallback for when no existing
 * KEY_FOO define matches the marking / purpose. In this case a new KEY_FOO
 * define MUST be added.
 */
#define LKL_KEY_MACRO1			0x290
#define LKL_KEY_MACRO2			0x291
#define LKL_KEY_MACRO3			0x292
#define LKL_KEY_MACRO4			0x293
#define LKL_KEY_MACRO5			0x294
#define LKL_KEY_MACRO6			0x295
#define LKL_KEY_MACRO7			0x296
#define LKL_KEY_MACRO8			0x297
#define LKL_KEY_MACRO9			0x298
#define LKL_KEY_MACRO10			0x299
#define LKL_KEY_MACRO11			0x29a
#define LKL_KEY_MACRO12			0x29b
#define LKL_KEY_MACRO13			0x29c
#define LKL_KEY_MACRO14			0x29d
#define LKL_KEY_MACRO15			0x29e
#define LKL_KEY_MACRO16			0x29f
#define LKL_KEY_MACRO17			0x2a0
#define LKL_KEY_MACRO18			0x2a1
#define LKL_KEY_MACRO19			0x2a2
#define LKL_KEY_MACRO20			0x2a3
#define LKL_KEY_MACRO21			0x2a4
#define LKL_KEY_MACRO22			0x2a5
#define LKL_KEY_MACRO23			0x2a6
#define LKL_KEY_MACRO24			0x2a7
#define LKL_KEY_MACRO25			0x2a8
#define LKL_KEY_MACRO26			0x2a9
#define LKL_KEY_MACRO27			0x2aa
#define LKL_KEY_MACRO28			0x2ab
#define LKL_KEY_MACRO29			0x2ac
#define LKL_KEY_MACRO30			0x2ad

/*
 * Some keyboards with the macro-keys described above have some extra keys
 * for controlling the host-side software responsible for the macro handling:
 * -A macro recording start/stop key. Note that not all keyboards which emit
 *  LKL_KEY_MACRO_RECORD_START will also emit LKL_KEY_MACRO_RECORD_STOP if
 *  LKL_KEY_MACRO_RECORD_STOP is not advertised, then LKL_KEY_MACRO_RECORD_START
 *  should be interpreted as a recording start/stop toggle;
 * -Keys for switching between different macro (pre)sets, either a key for
 *  cycling through the configured presets or keys to directly select a preset.
 */
#define LKL_KEY_MACRO_RECORD_START		0x2b0
#define LKL_KEY_MACRO_RECORD_STOP		0x2b1
#define LKL_KEY_MACRO_PRESET_CYCLE		0x2b2
#define LKL_KEY_MACRO_PRESET1		0x2b3
#define LKL_KEY_MACRO_PRESET2		0x2b4
#define LKL_KEY_MACRO_PRESET3		0x2b5

/*
 * Some keyboards have a buildin LCD panel where the contents are controlled
 * by the host. Often these have a number of keys directly below the LCD
 * intended for controlling a menu shown on the LCD. These keys often don't
 * have any labeling so we just name them KEY_KBD_LCD_MENU#
 */
#define LKL_KEY_KBD_LCD_MENU1		0x2b8
#define LKL_KEY_KBD_LCD_MENU2		0x2b9
#define LKL_KEY_KBD_LCD_MENU3		0x2ba
#define LKL_KEY_KBD_LCD_MENU4		0x2bb
#define LKL_KEY_KBD_LCD_MENU5		0x2bc

#define LKL_BTN_TRIGGER_HAPPY		0x2c0
#define LKL_BTN_TRIGGER_HAPPY1		0x2c0
#define LKL_BTN_TRIGGER_HAPPY2		0x2c1
#define LKL_BTN_TRIGGER_HAPPY3		0x2c2
#define LKL_BTN_TRIGGER_HAPPY4		0x2c3
#define LKL_BTN_TRIGGER_HAPPY5		0x2c4
#define LKL_BTN_TRIGGER_HAPPY6		0x2c5
#define LKL_BTN_TRIGGER_HAPPY7		0x2c6
#define LKL_BTN_TRIGGER_HAPPY8		0x2c7
#define LKL_BTN_TRIGGER_HAPPY9		0x2c8
#define LKL_BTN_TRIGGER_HAPPY10		0x2c9
#define LKL_BTN_TRIGGER_HAPPY11		0x2ca
#define LKL_BTN_TRIGGER_HAPPY12		0x2cb
#define LKL_BTN_TRIGGER_HAPPY13		0x2cc
#define LKL_BTN_TRIGGER_HAPPY14		0x2cd
#define LKL_BTN_TRIGGER_HAPPY15		0x2ce
#define LKL_BTN_TRIGGER_HAPPY16		0x2cf
#define LKL_BTN_TRIGGER_HAPPY17		0x2d0
#define LKL_BTN_TRIGGER_HAPPY18		0x2d1
#define LKL_BTN_TRIGGER_HAPPY19		0x2d2
#define LKL_BTN_TRIGGER_HAPPY20		0x2d3
#define LKL_BTN_TRIGGER_HAPPY21		0x2d4
#define LKL_BTN_TRIGGER_HAPPY22		0x2d5
#define LKL_BTN_TRIGGER_HAPPY23		0x2d6
#define LKL_BTN_TRIGGER_HAPPY24		0x2d7
#define LKL_BTN_TRIGGER_HAPPY25		0x2d8
#define LKL_BTN_TRIGGER_HAPPY26		0x2d9
#define LKL_BTN_TRIGGER_HAPPY27		0x2da
#define LKL_BTN_TRIGGER_HAPPY28		0x2db
#define LKL_BTN_TRIGGER_HAPPY29		0x2dc
#define LKL_BTN_TRIGGER_HAPPY30		0x2dd
#define LKL_BTN_TRIGGER_HAPPY31		0x2de
#define LKL_BTN_TRIGGER_HAPPY32		0x2df
#define LKL_BTN_TRIGGER_HAPPY33		0x2e0
#define LKL_BTN_TRIGGER_HAPPY34		0x2e1
#define LKL_BTN_TRIGGER_HAPPY35		0x2e2
#define LKL_BTN_TRIGGER_HAPPY36		0x2e3
#define LKL_BTN_TRIGGER_HAPPY37		0x2e4
#define LKL_BTN_TRIGGER_HAPPY38		0x2e5
#define LKL_BTN_TRIGGER_HAPPY39		0x2e6
#define LKL_BTN_TRIGGER_HAPPY40		0x2e7

/* We avoid low common keys in module aliases so they don't get huge. */
#define LKL_KEY_MIN_INTERESTING	LKL_KEY_MUTE
#define LKL_KEY_MAX			0x2ff
#define LKL_KEY_CNT			(LKL_KEY_MAX+1)

/*
 * Relative axes
 */

#define LKL_REL_X			0x00
#define LKL_REL_Y			0x01
#define LKL_REL_Z			0x02
#define LKL_REL_RX			0x03
#define LKL_REL_RY			0x04
#define LKL_REL_RZ			0x05
#define LKL_REL_HWHEEL		0x06
#define LKL_REL_DIAL		0x07
#define LKL_REL_WHEEL		0x08
#define LKL_REL_MISC		0x09
/*
 * 0x0a is reserved and should not be used in input drivers.
 * It was used by HID as LKL_REL_MISC+1 and userspace needs to detect if
 * the next REL_* event is correct or is just LKL_REL_MISC + n.
 * We define here LKL_REL_RESERVED so userspace can rely on it and detect
 * the situation described above.
 */
#define LKL_REL_RESERVED		0x0a
#define LKL_REL_WHEEL_HI_RES	0x0b
#define LKL_REL_HWHEEL_HI_RES	0x0c
#define LKL_REL_MAX			0x0f
#define LKL_REL_CNT			(LKL_REL_MAX+1)

/*
 * Absolute axes
 */

#define LKL_ABS_X			0x00
#define LKL_ABS_Y			0x01
#define LKL_ABS_Z			0x02
#define LKL_ABS_RX			0x03
#define LKL_ABS_RY			0x04
#define LKL_ABS_RZ			0x05
#define LKL_ABS_THROTTLE		0x06
#define LKL_ABS_RUDDER		0x07
#define LKL_ABS_WHEEL		0x08
#define LKL_ABS_GAS			0x09
#define LKL_ABS_BRAKE		0x0a
#define LKL_ABS_HAT0X		0x10
#define LKL_ABS_HAT0Y		0x11
#define LKL_ABS_HAT1X		0x12
#define LKL_ABS_HAT1Y		0x13
#define LKL_ABS_HAT2X		0x14
#define LKL_ABS_HAT2Y		0x15
#define LKL_ABS_HAT3X		0x16
#define LKL_ABS_HAT3Y		0x17
#define LKL_ABS_PRESSURE		0x18
#define LKL_ABS_DISTANCE		0x19
#define LKL_ABS_TILT_X		0x1a
#define LKL_ABS_TILT_Y		0x1b
#define LKL_ABS_TOOL_WIDTH		0x1c

#define LKL_ABS_VOLUME		0x20
#define LKL_ABS_PROFILE		0x21

#define LKL_ABS_MISC		0x28

/*
 * 0x2e is reserved and should not be used in input drivers.
 * It was used by HID as LKL_ABS_MISC+6 and userspace needs to detect if
 * the next ABS_* event is correct or is just LKL_ABS_MISC + n.
 * We define here LKL_ABS_RESERVED so userspace can rely on it and detect
 * the situation described above.
 */
#define LKL_ABS_RESERVED		0x2e

#define LKL_ABS_MT_SLOT		0x2f	/* MT slot being modified */
#define LKL_ABS_MT_TOUCH_MAJOR	0x30	/* Major axis of touching ellipse */
#define LKL_ABS_MT_TOUCH_MINOR	0x31	/* Minor axis (omit if circular) */
#define LKL_ABS_MT_WIDTH_MAJOR	0x32	/* Major axis of approaching ellipse */
#define LKL_ABS_MT_WIDTH_MINOR	0x33	/* Minor axis (omit if circular) */
#define LKL_ABS_MT_ORIENTATION	0x34	/* Ellipse orientation */
#define LKL_ABS_MT_POSITION_X	0x35	/* Center X touch position */
#define LKL_ABS_MT_POSITION_Y	0x36	/* Center Y touch position */
#define LKL_ABS_MT_TOOL_TYPE	0x37	/* Type of touching device */
#define LKL_ABS_MT_BLOB_ID		0x38	/* Group a set of packets as a blob */
#define LKL_ABS_MT_TRACKING_ID	0x39	/* Unique ID of initiated contact */
#define LKL_ABS_MT_PRESSURE		0x3a	/* Pressure on contact area */
#define LKL_ABS_MT_DISTANCE		0x3b	/* Contact hover distance */
#define LKL_ABS_MT_TOOL_X		0x3c	/* Center X tool position */
#define LKL_ABS_MT_TOOL_Y		0x3d	/* Center Y tool position */


#define LKL_ABS_MAX			0x3f
#define LKL_ABS_CNT			(LKL_ABS_MAX+1)

/*
 * Switch events
 */

#define LKL_SW_LID			0x00  /* set = lid shut */
#define LKL_SW_TABLET_MODE		0x01  /* set = tablet mode */
#define LKL_SW_HEADPHONE_INSERT	0x02  /* set = inserted */
#define LKL_SW_RFKILL_ALL		0x03  /* rfkill master switch, type "any"
					 set = radio enabled */
#define LKL_SW_RADIO		LKL_SW_RFKILL_ALL	/* deprecated */
#define LKL_SW_MICROPHONE_INSERT	0x04  /* set = inserted */
#define LKL_SW_DOCK			0x05  /* set = plugged into dock */
#define LKL_SW_LINEOUT_INSERT	0x06  /* set = inserted */
#define LKL_SW_JACK_PHYSICAL_INSERT 0x07  /* set = mechanical switch set */
#define LKL_SW_VIDEOOUT_INSERT	0x08  /* set = inserted */
#define LKL_SW_CAMERA_LENS_COVER	0x09  /* set = lens covered */
#define LKL_SW_KEYPAD_SLIDE		0x0a  /* set = keypad slide out */
#define LKL_SW_FRONT_PROXIMITY	0x0b  /* set = front proximity sensor active */
#define LKL_SW_ROTATE_LOCK		0x0c  /* set = rotate locked/disabled */
#define LKL_SW_LINEIN_INSERT	0x0d  /* set = inserted */
#define LKL_SW_MUTE_DEVICE		0x0e  /* set = device disabled */
#define LKL_SW_PEN_INSERTED		0x0f  /* set = pen inserted */
#define LKL_SW_MACHINE_COVER	0x10  /* set = cover closed */
#define LKL_SW_MAX			0x10
#define LKL_SW_CNT			(LKL_SW_MAX+1)

/*
 * Misc events
 */

#define LKL_MSC_SERIAL		0x00
#define LKL_MSC_PULSELED		0x01
#define LKL_MSC_GESTURE		0x02
#define LKL_MSC_RAW			0x03
#define LKL_MSC_SCAN		0x04
#define LKL_MSC_TIMESTAMP		0x05
#define LKL_MSC_MAX			0x07
#define LKL_MSC_CNT			(LKL_MSC_MAX+1)

/*
 * LEDs
 */

#define LKL_LED_NUML		0x00
#define LKL_LED_CAPSL		0x01
#define LKL_LED_SCROLLL		0x02
#define LKL_LED_COMPOSE		0x03
#define LKL_LED_KANA		0x04
#define LKL_LED_SLEEP		0x05
#define LKL_LED_SUSPEND		0x06
#define LKL_LED_MUTE		0x07
#define LKL_LED_MISC		0x08
#define LKL_LED_MAIL		0x09
#define LKL_LED_CHARGING		0x0a
#define LKL_LED_MAX			0x0f
#define LKL_LED_CNT			(LKL_LED_MAX+1)

/*
 * Autorepeat values
 */

#define LKL_REP_DELAY		0x00
#define LKL_REP_PERIOD		0x01
#define LKL_REP_MAX			0x01
#define LKL_REP_CNT			(LKL_REP_MAX+1)

/*
 * Sounds
 */

#define LKL_SND_CLICK		0x00
#define LKL_SND_BELL		0x01
#define LKL_SND_TONE		0x02
#define LKL_SND_MAX			0x07
#define LKL_SND_CNT			(LKL_SND_MAX+1)

#endif
