#include "SimulationData.h"

#include "ElementGraphics.h"
#include "ElementDefs.h"
#include "ElementClasses.h"

#include "BuiltinGOL.h"
#include "WallType.h"
#include "MenuSection.h"

#include "graphics/Renderer.h"

const BuiltinGOL builtinGol[NGOL] = {
	// * Ruleset:
	//   * bits x = 8..0: stay if x neighbours present
	//   * bits x = 16..9: begin if x-8 neighbours present
	//   * bits 20..17: 4-bit unsigned int encoding the number of states minus 2; 2 states is
	//     encoded as 0, 3 states as 1, etc.
	//   * states are kind of long until a cell dies; normal ones use two states (living and dead),
	//     for others the intermediate states live but do nothing
	//   * the ruleset constants below look 20-bit, but rulesets actually consist of 21
	//     bits of data; bit 20 just happens to not be set for any of the built-in types,
	//     as none of them have 10 or more states
	{ "GOL",  GT_GOL , 0x0080C, PIXPACK(0x0CAC00), PIXPACK(0x0CAC00), NGT_GOL,  String("Game Of Life: Begin 3/Stay 23") },
	{ "HLIF", GT_HLIF, 0x0480C, PIXPACK(0xFF0000), PIXPACK(0xFF0000), NGT_HLIF, String("High Life: B36/S23") },
	{ "ASIM", GT_ASIM, 0x038F0, PIXPACK(0x0000FF), PIXPACK(0x0000FF), NGT_ASIM, String("Assimilation: B345/S4567") },
	{ "2X2",  GT_2x2 , 0x04826, PIXPACK(0xFFFF00), PIXPACK(0xFFFF00), NGT_2x2,  String("2X2: B36/S125") },
	{ "DANI", GT_DANI, 0x1C9D8, PIXPACK(0x00FFFF), PIXPACK(0x00FFFF), NGT_DANI, String("Day and Night: B3678/S34678") },
	{ "AMOE", GT_AMOE, 0x0A92A, PIXPACK(0xFF00FF), PIXPACK(0xFF00FF), NGT_AMOE, String("Amoeba: B357/S1358") },
	{ "MOVE", GT_MOVE, 0x14834, PIXPACK(0xFFFFFF), PIXPACK(0xFFFFFF), NGT_MOVE, String("'Move' particles. Does not move things.. it is a life type: B368/S245") },
	{ "PGOL", GT_PGOL, 0x0A90C, PIXPACK(0xE05010), PIXPACK(0xE05010), NGT_PGOL, String("Pseudo Life: B357/S238") },
	{ "DMOE", GT_DMOE, 0x1E9E0, PIXPACK(0x500000), PIXPACK(0x500000), NGT_DMOE, String("Diamoeba: B35678/S5678") },
	{ "3-4",  GT_34  , 0x01818, PIXPACK(0x500050), PIXPACK(0x500050), NGT_34,   String("3-4: B34/S34") },
	{ "LLIF", GT_LLIF, 0x03820, PIXPACK(0x505050), PIXPACK(0x505050), NGT_LLIF, String("Long Life: B345/S5") },
	{ "STAN", GT_STAN, 0x1C9EC, PIXPACK(0x5000FF), PIXPACK(0x5000FF), NGT_STAN, String("Stains: B3678/S235678") },
	{ "SEED", GT_SEED, 0x00400, PIXPACK(0xFBEC7D), PIXPACK(0xFBEC7D), NGT_SEED, String("Seeds: B2/S") },
	{ "MAZE", GT_MAZE, 0x0083E, PIXPACK(0xA8E4A0), PIXPACK(0xA8E4A0), NGT_MAZE, String("Maze: B3/S12345") },
	{ "COAG", GT_COAG, 0x189EC, PIXPACK(0x9ACD32), PIXPACK(0x9ACD32), NGT_COAG, String("Coagulations: B378/S235678") },
	{ "WALL", GT_WALL, 0x1F03C, PIXPACK(0x0047AB), PIXPACK(0x0047AB), NGT_WALL, String("Walled cities: B45678/S2345") },
	{ "GNAR", GT_GNAR, 0x00202, PIXPACK(0xE5B73B), PIXPACK(0xE5B73B), NGT_GNAR, String("Gnarl: B1/S1") },
	{ "REPL", GT_REPL, 0x0AAAA, PIXPACK(0x259588), PIXPACK(0x259588), NGT_REPL, String("Replicator: B1357/S1357") },
	{ "MYST", GT_MYST, 0x139E1, PIXPACK(0x0C3C00), PIXPACK(0x0C3C00), NGT_MYST, String("Mystery: B3458/S05678") },
	{ "LOTE", GT_LOTE, 0x48938, PIXPACK(0xFF0000), PIXPACK(0xFFFF00), NGT_LOTE, String("Living on the Edge: B37/S3458/4") },
	{ "FRG2", GT_FRG2, 0x20816, PIXPACK(0x006432), PIXPACK(0x00FF5A), NGT_FRG2, String("Like Frogs rule: B3/S124/3") },
	{ "STAR", GT_STAR, 0x98478, PIXPACK(0x000040), PIXPACK(0x0000E6), NGT_STAR, String("Like Star Wars rule: B278/S3456/6") },
	{ "FROG", GT_FROG, 0x21806, PIXPACK(0x006400), PIXPACK(0x00FF00), NGT_FROG, String("Frogs: B34/S12/3") },
	{ "BRAN", GT_BRAN, 0x25440, PIXPACK(0xFFFF00), PIXPACK(0x969600), NGT_BRAN, String("Brian 6: B246/S6/3" )}
};

std::vector<wall_type> LoadWalls()
{
	return
	std::vector<wall_type>{
		{PIXPACK(0x808080), PIXPACK(0x000000), 0, Renderer::WallIcon, String("ERASE"),           "DEFAULT_WL_ERASE",  String("Erases walls.")},
		{PIXPACK(0xC0C0C0), PIXPACK(0x101010), 0, Renderer::WallIcon, String("CONDUCTIVE WALL"), "DEFAULT_WL_CNDTW",  String("Blocks everything. Conductive.")},
		{PIXPACK(0x808080), PIXPACK(0x808080), 0, Renderer::WallIcon, String("EWALL"),           "DEFAULT_WL_EWALL",  String("E-Wall. Becomes transparent when electricity is connected.")},
		{PIXPACK(0xFF8080), PIXPACK(0xFF2008), 1, Renderer::WallIcon, String("DETECTOR"),        "DEFAULT_WL_DTECT",  String("Detector. Generates electricity when a particle is inside.")},
		{PIXPACK(0x808080), PIXPACK(0x000000), 0, Renderer::WallIcon, String("STREAMLINE"),      "DEFAULT_WL_STRM",   String("Streamline. Set start point of a streamline.")},
		{PIXPACK(0x8080FF), PIXPACK(0x000000), 1, Renderer::WallIcon, String("FAN"),             "DEFAULT_WL_FAN",    String("Fan. Accelerates air. Use the line tool to set direction and strength.")},
		{PIXPACK(0xC0C0C0), PIXPACK(0x101010), 2, Renderer::WallIcon, String("LIQUID WALL"),     "DEFAULT_WL_LIQD",   String("Allows liquids, blocks all other particles. Conductive.")},
		{PIXPACK(0x808080), PIXPACK(0x000000), 1, Renderer::WallIcon, String("ABSORB WALL"),     "DEFAULT_WL_ABSRB",  String("Absorbs particles but lets air currents through.")},
		{PIXPACK(0x808080), PIXPACK(0x000000), 3, Renderer::WallIcon, String("WALL"),            "DEFAULT_WL_WALL",   String("Basic wall, blocks everything.")},
		{PIXPACK(0x3C3C3C), PIXPACK(0x000000), 1, Renderer::WallIcon, String("AIRONLY WALL"),    "DEFAULT_WL_AIR",    String("Allows air, but blocks all particles.")},
		{PIXPACK(0x575757), PIXPACK(0x000000), 1, Renderer::WallIcon, String("POWDER WALL"),     "DEFAULT_WL_POWDR",  String("Allows powders, blocks all other particles.")},
		{PIXPACK(0xFFFF22), PIXPACK(0x101010), 2, Renderer::WallIcon, String("CONDUCTOR"),       "DEFAULT_WL_CNDTR",  String("Conductor. Allows all particles to pass through and conducts electricity.")},
		{PIXPACK(0x242424), PIXPACK(0x101010), 0, Renderer::WallIcon, String("EHOLE"),           "DEFAULT_WL_EHOLE",  String("E-Hole. absorbs particles, releases them when powered.")},
		{PIXPACK(0x579777), PIXPACK(0x000000), 1, Renderer::WallIcon, String("GAS WALL"),        "DEFAULT_WL_GAS",    String("Allows gases, blocks all other particles.")},
		{PIXPACK(0xFFEE00), PIXPACK(0xAA9900), 4, Renderer::WallIcon, String("GRAVITY WALL"),    "DEFAULT_WL_GRVTY",  String("Gravity wall. Newtonian Gravity has no effect inside a box drawn with this.")},
		{PIXPACK(0xFFAA00), PIXPACK(0xAA5500), 4, Renderer::WallIcon, String("ENERGY WALL"),     "DEFAULT_WL_ENRGY",  String("Allows energy particles, blocks all other particles.")},
		{PIXPACK(0xDCDCDC), PIXPACK(0x000000), 1, Renderer::WallIcon, String("AIRBLOCK WALL"),   "DEFAULT_WL_NOAIR",  String("Allows all particles, but blocks air.")},
		{PIXPACK(0x808080), PIXPACK(0x000000), 0, Renderer::WallIcon, String("ERASEALL"),        "DEFAULT_WL_ERASEA", String("Erases walls, particles, and signs.")},
		{PIXPACK(0x800080), PIXPACK(0x000000), 0, Renderer::WallIcon, String("STASIS WALL"),     "DEFAULT_WL_STASIS", String("Freezes particles inside the wall in place until powered.")},
	};
}

std::vector<menu_section> LoadMenus()
{
	return
	std::vector<menu_section>{
		{0xE041, String("Walls"), 0, 1},
		{0xE042, String("Electronics"), 0, 1},
		{0xE056, String("Powered Materials"), 0, 1},
		{0xE019, String("Sensors"), 0, 1},
		{0xE062, String("Force"), 0, 1},
		{0xE043, String("Explosives"), 0, 1},
		{0xE045, String("Gases"), 0, 1},
		{0xE044, String("Liquids"), 0, 1},
		{0xE050, String("Powders"), 0, 1},
		{0xE051, String("Solids"), 0, 1},
		{0xE076, String("Organic"), 0, 1 },
		{0xE046, String("Radioactive"), 0, 1},
		{0xE04C, String("Special"), 0, 1},
		{0xE052, String("Game Of Life"), 0, 1},
		{0xE057, String("Tools"), 0, 1},
		{0xE067, String("Favorites"), 0, 1},
		{0xE064, String("Decoration tools"), 0, 1},
		{0xE048, String("Cracker"), 0, 0},
		{0xE048, String("Cracker!"), 0, 0},
	};
}

std::vector<unsigned int> LoadLatent()
{
	return
	std::vector<unsigned int>{
		/* NONE */ 0,
		/* DUST */ 0,
		/* WATR */ 7500,
		/* OIL  */ 0,
		/* FIRE */ 0,
		/* STNE */ 0,
		/* LAVA */ 0,
		/* GUN  */ 0,
		/* NITR */ 0,
		/* CLNE */ 0,
		/* GAS  */ 0,
		/* C-4  */ 0,
		/* GOO  */ 0,
		/* ICE  */ 1095,
		/* METL */ 919,
		/* SPRK */ 0,
		/* SNOW */ 1095,
		/* WOOD */ 0,
		/* NEUT */ 0,
		/* PLUT */ 0,
		/* PLNT */ 0,
		/* ACID */ 0,
		/* VOID */ 0,
		/* WTRV */ 0,
		/* CNCT */ 0,
		/* DSTW */ 7500,
		/* SALT */ 0,
		/* SLTW */ 7500,
		/* DMND */ 0,
		/* BMTL */ 0,
		/* BRMT */ 0,
		/* PHOT */ 0,
		/* URAN */ 0,
		/* WAX  */ 0,
		/* MWAX */ 0,
		/* PSCN */ 0,
		/* NSCN */ 0,
		/* LN2  */ 0,
		/* INSL */ 0,
		/* VACU */ 0,
		/* VENT */ 0,
		/* RBDM */ 0,
		/* LRBD */ 0,
		/* NTCT */ 0,
		/* SAND */ 0,
		/* GLAS */ 0,
		/* PTCT */ 0,
		/* BGLA */ 0,
		/* THDR */ 0,
		/* PLSM */ 0,
		/* ETRD */ 0,
		/* NICE */ 0,
		/* NBLE */ 0,
		/* BTRY */ 0,
		/* LCRY */ 0,
		/* STKM */ 0,
		/* SWCH */ 0,
		/* SMKE */ 0,
		/* DESL */ 0,
		/* COAL */ 0,
		/* LO2  */ 0,
		/* O2   */ 0,
		/* INWR */ 0,
		/* YEST */ 0,
		/* DYST */ 0,
		/* THRM */ 0,
		/* GLOW */ 0,
		/* BRCK */ 0,
		/* CFLM */ 0,
		/* FIRW */ 0,
		/* FUSE */ 0,
		/* FSEP */ 0,
		/* AMTR */ 0,
		/* BCOL */ 0,
		/* PCLN */ 0,
		/* HSWC */ 0,
		/* IRON */ 0,
		/* MORT */ 0,
		/* LIFE */ 0,
		/* DLAY */ 0,
		/* CO2  */ 0,
		/* DRIC */ 0,
		/* CBNW */ 7500,
		/* STOR */ 0,
		/* STOR */ 0,
		/* FREE */ 0,
		/* FREE */ 0,
		/* FREE */ 0,
		/* FREE */ 0,
		/* FREE */ 0,
		/* SPNG */ 0,
		/* RIME */ 0,
		/* FOG  */ 0,
		/* BCLN */ 0,
		/* LOVE */ 0,
		/* DEUT */ 0,
		/* WARP */ 0,
		/* PUMP */ 0,
		/* FWRK */ 0,
		/* PIPE */ 0,
		/* FRZZ */ 0,
		/* FRZW */ 0,
		/* GRAV */ 0,
		/* BIZR */ 0,
		/* BIZRG*/ 0,
		/* BIZRS*/ 0,
		/* INST */ 0,
		/* ISOZ */ 0,
		/* ISZS */ 0,
		/* PRTI */ 0,
		/* PRTO */ 0,
		/* PSTE */ 0,
		/* PSTS */ 0,
		/* ANAR */ 0,
		/* VINE */ 0,
		/* INVS */ 0,
		/* EQVE */ 0,
		/* SPWN2*/ 0,
		/* SPAWN*/ 0,
		/* SHLD1*/ 0,
		/* SHLD2*/ 0,
		/* SHLD3*/ 0,
		/* SHLD4*/ 0,
		/* LOlZ */ 0,
		/* WIFI */ 0,
		/* FILT */ 0,
		/* ARAY */ 0,
		/* BRAY */ 0,
		/* STKM2*/ 0,
		/* BOMB */ 0,
		/* C-5  */ 0,
		/* SING */ 0,
		/* QRTZ */ 0,
		/* PQRT */ 0,
		/* EMP  */ 0,
		/* BREL */ 0,
		/* ELEC */ 0,
		/* ACEL */ 0,
		/* DCEL */ 0,
		/* TNT  */ 0,
		/* IGNP */ 0,
		/* BOYL */ 0,
		/* GEL  */ 0,
		/* FREE */ 0,
		/* FREE */ 0,
		/* FREE */ 0,
		/* FREE */ 0,
		/* WIND */ 0,
		/* H2   */ 0,
		/* SOAP */ 0,
		/* NBHL */ 0,
		/* NWHL */ 0,
		/* MERC */ 0,
		/* PBCN */ 0,
		/* GPMP */ 0,
		/* CLST */ 0,
		/* WIRE */ 0,
		/* GBMB */ 0,
		/* FIGH */ 0,
		/* FRAY */ 0,
		/* REPL */ 0,
	};
}
