#ifndef PGRAPHICS_H
#define PGRAPHICS_H

#define PMODE			0x00000FFF
#define PMODE_NONE		0x00000000
#define PMODE_FLAT		0x00000001
#define PMODE_BLOB		0x00000002
#define PMODE_BLUR		0x00000004
#define PMODE_GLOW		0x00000008
#define PMODE_SPARK		0x00000010
#define PMODE_FLARE		0x00000020
#define PMODE_LFLARE	0x00000040
#define PMODE_ADD		0x00000080
#define PMODE_BLEND		0x00000100
#define PSPEC_STICKMAN	0x00000200

#define OPTIONS			0x0000F000
#define NO_DECO			0x00001000
#define DECO_FIRE		0x00002000

#define FIREMODE		0x00FF0000
#define FIRE_ADD		0x00010000
#define FIRE_BLEND		0x00020000
#define FIRE_SPARK		0x00040000

#define EFFECT			0xFF000000
#define EFFECT_GRAVIN	0x01000000
#define EFFECT_GRAVOUT	0x02000000
#define EFFECT_LINES	0x04000000
#define EFFECT_DBGLINES	0x08000000

#define RENDER_EFFE		OPTIONS | PSPEC_STICKMAN | EFFECT | PMODE_SPARK | PMODE_FLARE | PMODE_LFLARE
#define RENDER_FIRE		OPTIONS | PSPEC_STICKMAN | /*PMODE_FLAT |*/ PMODE_ADD | PMODE_BLEND | FIRE_ADD | FIRE_BLEND
#define RENDER_SPRK		OPTIONS | PSPEC_STICKMAN | PMODE_ADD | PMODE_BLEND | FIRE_SPARK
#define RENDER_GLOW		OPTIONS | PSPEC_STICKMAN | /*PMODE_FLAT |*/ PMODE_GLOW | PMODE_ADD | PMODE_BLEND
#define RENDER_BLUR		OPTIONS | PSPEC_STICKMAN | /*PMODE_FLAT |*/ PMODE_BLUR | PMODE_ADD | PMODE_BLEND
#define RENDER_BLOB		OPTIONS | PSPEC_STICKMAN | /*PMODE_FLAT |*/ PMODE_BLOB | PMODE_ADD | PMODE_BLEND
#define RENDER_BASC		OPTIONS | PSPEC_STICKMAN | PMODE_FLAT | PMODE_ADD | PMODE_BLEND | EFFECT_LINES
#define RENDER_NONE		OPTIONS | PSPEC_STICKMAN | PMODE_FLAT

#define COLOUR_HEAT		0x00000001
#define COLOUR_LIFE		0x00000002
#define COLOUR_GRAD		0x00000004
#define COLOUR_BASC		0x00000008
#define COLOUR_HEAL		0x00000010

#define COLOUR_DEFAULT 	0x00000000

#define DISPLAY_AIRC	0x00000001
#define DISPLAY_AIRP	0x00000002
#define DISPLAY_AIRV	0x00000004
#define DISPLAY_AIRH	0x00000008
#define DISPLAY_AIR		0x0000000F
#define DISPLAY_WARP	0x00000010
#define DISPLAY_PERS	0x00000020
#define DISPLAY_EFFE	0x00000040

#endif