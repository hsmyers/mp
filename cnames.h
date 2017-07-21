//
// cnames.h
//
#ifndef CNAMES_H_   /* Include guard */
#define CNAMES_H_
#include <stdbool.h>
#include "palette.h"
#define COLOR_NAMES_MAX 865

typedef struct ColorInfo {
  const char *name;
  const char *hex;
  Rgb rgb;
} ColorInfo;

typedef enum Color {
  COLOR_AIR_FORCE_BLUE_RAF=0,
  COLOR_AIR_FORCE_BLUE_USAF,
  COLOR_AIR_SUPERIORITY_BLUE,
  COLOR_ALABAMA_CRIMSON,
  COLOR_ALICE_BLUE,
  COLOR_ALIZARIN_CRIMSON,
  COLOR_ALLOY_ORANGE,
  COLOR_ALMOND,
  COLOR_AMARANTH,
  COLOR_AMBER,
  COLOR_AMBER_SAE_ECE,
  COLOR_AMERICAN_ROSE,
  COLOR_AMETHYST,
  COLOR_ANDROID_GREEN,
  COLOR_ANTI_FLASH_WHITE,
  COLOR_ANTIQUE_BRASS,
  COLOR_ANTIQUE_FUCHSIA,
  COLOR_ANTIQUE_RUBY,
  COLOR_ANTIQUE_WHITE,
  COLOR_AO_ENGLISH,
  COLOR_APPLE_GREEN,
  COLOR_APRICOT,
  COLOR_AQUA,
  COLOR_AQUAMARINE,
  COLOR_ARMY_GREEN,
  COLOR_ARSENIC,
  COLOR_ARYLIDE_YELLOW,
  COLOR_ASH_GREY,
  COLOR_ASPARAGUS,
  COLOR_ATOMIC_TANGERINE,
  COLOR_AUBURN,
  COLOR_AUREOLIN,
  COLOR_AUROMETALSAURUS,
  COLOR_AVOCADO,
  COLOR_AZURE,
  COLOR_AZURE_MIST_WEB,
  COLOR_BABY_BLUE,
  COLOR_BABY_BLUE_EYES,
  COLOR_BABY_PINK,
  COLOR_BALL_BLUE,
  COLOR_BANANA_MANIA,
  COLOR_BANANA_YELLOW,
  COLOR_BARN_RED,
  COLOR_BATTLESHIP_GREY,
  COLOR_BAZAAR,
  COLOR_BEAU_BLUE,
  COLOR_BEAVER,
  COLOR_BEIGE,
  COLOR_BIG_DIP_O_RUBY,
  COLOR_BISQUE,
  COLOR_BISTRE,
  COLOR_BITTERSWEET,
  COLOR_BITTERSWEET_SHIMMER,
  COLOR_BLACK,
  COLOR_BLACK_BEAN,
  COLOR_BLACK_LEATHER_JACKET,
  COLOR_BLACK_OLIVE,
  COLOR_BLANCHED_ALMOND,
  COLOR_BLAST_OFF_BRONZE,
  COLOR_BLEU_DE_FRANCE,
  COLOR_BLIZZARD_BLUE,
  COLOR_BLOND,
  COLOR_BLUE,
  COLOR_BLUE_BELL,
  COLOR_BLUE_CRAYOLA,
  COLOR_BLUE_GRAY,
  COLOR_BLUE_GREEN,
  COLOR_BLUE_MUNSELL,
  COLOR_BLUE_NCS,
  COLOR_BLUE_PIGMENT,
  COLOR_BLUE_RYB,
  COLOR_BLUE_SAPPHIRE,
  COLOR_BLUE_VIOLET,
  COLOR_BLUSH,
  COLOR_BOLE,
  COLOR_BONDI_BLUE,
  COLOR_BONE,
  COLOR_BOSTON_UNIVERSITY_RED,
  COLOR_BOTTLE_GREEN,
  COLOR_BOYSENBERRY,
  COLOR_BRANDEIS_BLUE,
  COLOR_BRASS,
  COLOR_BRICK_RED,
  COLOR_BRIGHT_CERULEAN,
  COLOR_BRIGHT_GREEN,
  COLOR_BRIGHT_LAVENDER,
  COLOR_BRIGHT_MAROON,
  COLOR_BRIGHT_PINK,
  COLOR_BRIGHT_TURQUOISE,
  COLOR_BRIGHT_UBE,
  COLOR_BRILLIANT_LAVENDER,
  COLOR_BRILLIANT_ROSE,
  COLOR_BRINK_PINK,
  COLOR_BRITISH_RACING_GREEN,
  COLOR_BRONZE,
  COLOR_BROWN_TRADITIONAL,
  COLOR_BROWN_WEB,
  COLOR_BUBBLE_GUM,
  COLOR_BUBBLES,
  COLOR_BUFF,
  COLOR_BULGARIAN_ROSE,
  COLOR_BURGUNDY,
  COLOR_BURLYWOOD,
  COLOR_BURNT_ORANGE,
  COLOR_BURNT_SIENNA,
  COLOR_BURNT_UMBER,
  COLOR_BYZANTINE,
  COLOR_BYZANTIUM,
  COLOR_CADET,
  COLOR_CADET_BLUE,
  COLOR_CADET_GREY,
  COLOR_CADMIUM_GREEN,
  COLOR_CADMIUM_ORANGE,
  COLOR_CADMIUM_RED,
  COLOR_CADMIUM_YELLOW,
  COLOR_CAF_AU_LAIT,
  COLOR_CAF_NOIR,
  COLOR_CAL_POLY_GREEN,
  COLOR_CAMBRIDGE_BLUE,
  COLOR_CAMEL,
  COLOR_CAMEO_PINK,
  COLOR_CAMOUFLAGE_GREEN,
  COLOR_CANARY_YELLOW,
  COLOR_CANDY_APPLE_RED,
  COLOR_CANDY_PINK,
  COLOR_CAPRI,
  COLOR_CAPUT_MORTUUM,
  COLOR_CARDINAL,
  COLOR_CARIBBEAN_GREEN,
  COLOR_CARMINE,
  COLOR_CARMINE_M_P,
  COLOR_CARMINE_PINK,
  COLOR_CARMINE_RED,
  COLOR_CARNATION_PINK,
  COLOR_CARNELIAN,
  COLOR_CAROLINA_BLUE,
  COLOR_CARROT_ORANGE,
  COLOR_CATALINA_BLUE,
  COLOR_CEIL,
  COLOR_CELADON,
  COLOR_CELADON_BLUE,
  COLOR_CELADON_GREEN,
  COLOR_CELESTE_COLOUR,
  COLOR_CELESTIAL_BLUE,
  COLOR_CERISE,
  COLOR_CERISE_PINK,
  COLOR_CERULEAN,
  COLOR_CERULEAN_BLUE,
  COLOR_CERULEAN_FROST,
  COLOR_CG_BLUE,
  COLOR_CG_RED,
  COLOR_CHAMOISEE,
  COLOR_CHAMPAGNE,
  COLOR_CHARCOAL,
  COLOR_CHARM_PINK,
  COLOR_CHARTREUSE_TRADITIONAL,
  COLOR_CHARTREUSE_WEB,
  COLOR_CHERRY,
  COLOR_CHERRY_BLOSSOM_PINK,
  COLOR_CHESTNUT,
  COLOR_CHINA_PINK,
  COLOR_CHINA_ROSE,
  COLOR_CHINESE_RED,
  COLOR_CHOCOLATE_TRADITIONAL,
  COLOR_CHOCOLATE_WEB,
  COLOR_CHROME_YELLOW,
  COLOR_CINEREOUS,
  COLOR_CINNABAR,
  COLOR_CINNAMON,
  COLOR_CITRINE,
  COLOR_CLASSIC_ROSE,
  COLOR_COBALT,
  COLOR_COCOA_BROWN,
  COLOR_COFFEE,
  COLOR_COLUMBIA_BLUE,
  COLOR_CONGO_PINK,
  COLOR_COOL_BLACK,
  COLOR_COOL_GREY,
  COLOR_COPPER,
  COLOR_COPPER_CRAYOLA,
  COLOR_COPPER_PENNY,
  COLOR_COPPER_RED,
  COLOR_COPPER_ROSE,
  COLOR_COQUELICOT,
  COLOR_CORAL,
  COLOR_CORAL_PINK,
  COLOR_CORAL_RED,
  COLOR_CORDOVAN,
  COLOR_CORN,
  COLOR_CORNELL_RED,
  COLOR_CORNFLOWER_BLUE,
  COLOR_CORNSILK,
  COLOR_COSMIC_LATTE,
  COLOR_COTTON_CANDY,
  COLOR_CREAM,
  COLOR_CRIMSON,
  COLOR_CRIMSON_GLORY,
  COLOR_CYAN,
  COLOR_CYAN_PROCESS,
  COLOR_DAFFODIL,
  COLOR_DANDELION,
  COLOR_DARK_BLUE,
  COLOR_DARK_BROWN,
  COLOR_DARK_BYZANTIUM,
  COLOR_DARK_CANDY_APPLE_RED,
  COLOR_DARK_CERULEAN,
  COLOR_DARK_CHESTNUT,
  COLOR_DARK_CORAL,
  COLOR_DARK_CYAN,
  COLOR_DARK_ELECTRIC_BLUE,
  COLOR_DARK_GOLDENROD,
  COLOR_DARK_GRAY,
  COLOR_DARK_GREEN,
  COLOR_DARK_IMPERIAL_BLUE,
  COLOR_DARK_JUNGLE_GREEN,
  COLOR_DARK_KHAKI,
  COLOR_DARK_LAVA,
  COLOR_DARK_LAVENDER,
  COLOR_DARK_MAGENTA,
  COLOR_DARK_MIDNIGHT_BLUE,
  COLOR_DARK_OLIVE_GREEN,
  COLOR_DARK_ORANGE,
  COLOR_DARK_ORCHID,
  COLOR_DARK_PASTEL_BLUE,
  COLOR_DARK_PASTEL_GREEN,
  COLOR_DARK_PASTEL_PURPLE,
  COLOR_DARK_PASTEL_RED,
  COLOR_DARK_PINK,
  COLOR_DARK_POWDER_BLUE,
  COLOR_DARK_RASPBERRY,
  COLOR_DARK_RED,
  COLOR_DARK_SALMON,
  COLOR_DARK_SCARLET,
  COLOR_DARK_SEA_GREEN,
  COLOR_DARK_SIENNA,
  COLOR_DARK_SLATE_BLUE,
  COLOR_DARK_SLATE_GRAY,
  COLOR_DARK_SPRING_GREEN,
  COLOR_DARK_TAN,
  COLOR_DARK_TANGERINE,
  COLOR_DARK_TAUPE,
  COLOR_DARK_TERRA_COTTA,
  COLOR_DARK_TURQUOISE,
  COLOR_DARK_VIOLET,
  COLOR_DARK_YELLOW,
  COLOR_DARTMOUTH_GREEN,
  COLOR_DAVY_S_GREY,
  COLOR_DEBIAN_RED,
  COLOR_DEEP_CARMINE,
  COLOR_DEEP_CARMINE_PINK,
  COLOR_DEEP_CARROT_ORANGE,
  COLOR_DEEP_CERISE,
  COLOR_DEEP_CHAMPAGNE,
  COLOR_DEEP_CHESTNUT,
  COLOR_DEEP_COFFEE,
  COLOR_DEEP_FUCHSIA,
  COLOR_DEEP_JUNGLE_GREEN,
  COLOR_DEEP_LILAC,
  COLOR_DEEP_MAGENTA,
  COLOR_DEEP_PEACH,
  COLOR_DEEP_PINK,
  COLOR_DEEP_RUBY,
  COLOR_DEEP_SAFFRON,
  COLOR_DEEP_SKY_BLUE,
  COLOR_DEEP_TUSCAN_RED,
  COLOR_DENIM,
  COLOR_DESERT,
  COLOR_DESERT_SAND,
  COLOR_DIM_GRAY,
  COLOR_DODGER_BLUE,
  COLOR_DOGWOOD_ROSE,
  COLOR_DOLLAR_BILL,
  COLOR_DRAB,
  COLOR_DUKE_BLUE,
  COLOR_EARTH_YELLOW,
  COLOR_EBONY,
  COLOR_ECRU,
  COLOR_EGGPLANT,
  COLOR_EGGSHELL,
  COLOR_EGYPTIAN_BLUE,
  COLOR_ELECTRIC_BLUE,
  COLOR_ELECTRIC_CRIMSON,
  COLOR_ELECTRIC_CYAN,
  COLOR_ELECTRIC_GREEN,
  COLOR_ELECTRIC_INDIGO,
  COLOR_ELECTRIC_LAVENDER,
  COLOR_ELECTRIC_LIME,
  COLOR_ELECTRIC_PURPLE,
  COLOR_ELECTRIC_ULTRAMARINE,
  COLOR_ELECTRIC_VIOLET,
  COLOR_ELECTRIC_YELLOW,
  COLOR_EMERALD,
  COLOR_ENGLISH_LAVENDER,
  COLOR_ETON_BLUE,
  COLOR_FALLOW,
  COLOR_FALU_RED,
  COLOR_FANDANGO,
  COLOR_FASHION_FUCHSIA,
  COLOR_FAWN,
  COLOR_FELDGRAU,
  COLOR_FERN_GREEN,
  COLOR_FERRARI_RED,
  COLOR_FIELD_DRAB,
  COLOR_FIRE_ENGINE_RED,
  COLOR_FIREBRICK,
  COLOR_FLAME,
  COLOR_FLAMINGO_PINK,
  COLOR_FLAVESCENT,
  COLOR_FLAX,
  COLOR_FLORAL_WHITE,
  COLOR_FLUORESCENT_ORANGE,
  COLOR_FLUORESCENT_PINK,
  COLOR_FLUORESCENT_YELLOW,
  COLOR_FOLLY,
  COLOR_FOREST_GREEN_TRADITIONAL,
  COLOR_FOREST_GREEN_WEB,
  COLOR_FRENCH_BEIGE,
  COLOR_FRENCH_BLUE,
  COLOR_FRENCH_LILAC,
  COLOR_FRENCH_LIME,
  COLOR_FRENCH_RASPBERRY,
  COLOR_FRENCH_ROSE,
  COLOR_FUCHSIA,
  COLOR_FUCHSIA_CRAYOLA,
  COLOR_FUCHSIA_PINK,
  COLOR_FUCHSIA_ROSE,
  COLOR_FULVOUS,
  COLOR_FUZZY_WUZZY,
  COLOR_GAINSBORO,
  COLOR_GAMBOGE,
  COLOR_GHOST_WHITE,
  COLOR_GINGER,
  COLOR_GLAUCOUS,
  COLOR_GLITTER,
  COLOR_GOLD_METALLIC,
  COLOR_GOLD_WEB_GOLDEN,
  COLOR_GOLDEN_BROWN,
  COLOR_GOLDEN_POPPY,
  COLOR_GOLDEN_YELLOW,
  COLOR_GOLDENROD,
  COLOR_GRANNY_SMITH_APPLE,
  COLOR_GRAY,
  COLOR_GRAY_ASPARAGUS,
  COLOR_GRAY_HTML_CSS_GRAY,
  COLOR_GRAY_X11_GRAY,
  COLOR_GREEN_COLOR_WHEEL_X11_GREEN,
  COLOR_GREEN_CRAYOLA,
  COLOR_GREEN_HTML_CSS_GREEN,
  COLOR_GREEN_MUNSELL,
  COLOR_GREEN_NCS,
  COLOR_GREEN_PIGMENT,
  COLOR_GREEN_RYB,
  COLOR_GREEN_YELLOW,
  COLOR_GRULLO,
  COLOR_GUPPIE_GREEN,
  COLOR_HALAY_BE,
  COLOR_HAN_BLUE,
  COLOR_HAN_PURPLE,
  COLOR_HANSA_YELLOW,
  COLOR_HARLEQUIN,
  COLOR_HARVARD_CRIMSON,
  COLOR_HARVEST_GOLD,
  COLOR_HEART_GOLD,
  COLOR_HELIOTROPE,
  COLOR_HOLLYWOOD_CERISE,
  COLOR_HONEYDEW,
  COLOR_HONOLULU_BLUE,
  COLOR_HOOKER_S_GREEN,
  COLOR_HOT_MAGENTA,
  COLOR_HOT_PINK,
  COLOR_HUNTER_GREEN,
  COLOR_ICEBERG,
  COLOR_ICTERINE,
  COLOR_IMPERIAL_BLUE,
  COLOR_INCHWORM,
  COLOR_INDIA_GREEN,
  COLOR_INDIAN_RED,
  COLOR_INDIAN_YELLOW,
  COLOR_INDIGO,
  COLOR_INDIGO_DYE,
  COLOR_INDIGO_WEB,
  COLOR_INTERNATIONAL_KLEIN_BLUE,
  COLOR_INTERNATIONAL_ORANGE_AEROSPACE,
  COLOR_INTERNATIONAL_ORANGE_ENGINEERING,
  COLOR_INTERNATIONAL_ORANGE_GOLDEN_GATE_BRIDGE,
  COLOR_IRIS,
  COLOR_ISABELLINE,
  COLOR_ISLAMIC_GREEN,
  COLOR_IVORY,
  COLOR_JADE,
  COLOR_JASMINE,
  COLOR_JASPER,
  COLOR_JAZZBERRY_JAM,
  COLOR_JET,
  COLOR_JONQUIL,
  COLOR_JUNE_BUD,
  COLOR_JUNGLE_GREEN,
  COLOR_KELLY_GREEN,
  COLOR_KENYAN_COPPER,
  COLOR_KHAKI_HTML_CSS_KHAKI,
  COLOR_KHAKI_X11_LIGHT_KHAKI,
  COLOR_KU_CRIMSON,
  COLOR_LA_SALLE_GREEN,
  COLOR_LANGUID_LAVENDER,
  COLOR_LAPIS_LAZULI,
  COLOR_LASER_LEMON,
  COLOR_LAUREL_GREEN,
  COLOR_LAVA,
  COLOR_LAVENDER_BLUE,
  COLOR_LAVENDER_BLUSH,
  COLOR_LAVENDER_FLORAL,
  COLOR_LAVENDER_GRAY,
  COLOR_LAVENDER_INDIGO,
  COLOR_LAVENDER_MAGENTA,
  COLOR_LAVENDER_MIST,
  COLOR_LAVENDER_PINK,
  COLOR_LAVENDER_PURPLE,
  COLOR_LAVENDER_ROSE,
  COLOR_LAVENDER_WEB,
  COLOR_LAWN_GREEN,
  COLOR_LEMON,
  COLOR_LEMON_CHIFFON,
  COLOR_LEMON_LIME,
  COLOR_LICORICE,
  COLOR_LIGHT_APRICOT,
  COLOR_LIGHT_BLUE,
  COLOR_LIGHT_BROWN,
  COLOR_LIGHT_CARMINE_PINK,
  COLOR_LIGHT_CORAL,
  COLOR_LIGHT_CORNFLOWER_BLUE,
  COLOR_LIGHT_CRIMSON,
  COLOR_LIGHT_CYAN,
  COLOR_LIGHT_FUCHSIA_PINK,
  COLOR_LIGHT_GOLDENROD_YELLOW,
  COLOR_LIGHT_GRAY,
  COLOR_LIGHT_GREEN,
  COLOR_LIGHT_KHAKI,
  COLOR_LIGHT_PASTEL_PURPLE,
  COLOR_LIGHT_PINK,
  COLOR_LIGHT_RED_OCHRE,
  COLOR_LIGHT_SALMON,
  COLOR_LIGHT_SALMON_PINK,
  COLOR_LIGHT_SEA_GREEN,
  COLOR_LIGHT_SKY_BLUE,
  COLOR_LIGHT_SLATE_GRAY,
  COLOR_LIGHT_TAUPE,
  COLOR_LIGHT_THULIAN_PINK,
  COLOR_LIGHT_YELLOW,
  COLOR_LILAC,
  COLOR_LIME_COLOR_WHEEL,
  COLOR_LIME_GREEN,
  COLOR_LIME_WEB_X11_GREEN,
  COLOR_LIMERICK,
  COLOR_LINCOLN_GREEN,
  COLOR_LINEN,
  COLOR_LION,
  COLOR_LITTLE_BOY_BLUE,
  COLOR_LIVER,
  COLOR_LUST,
  COLOR_MAGENTA,
  COLOR_MAGENTA_DYE,
  COLOR_MAGENTA_PROCESS,
  COLOR_MAGIC_MINT,
  COLOR_MAGNOLIA,
  COLOR_MAHOGANY,
  COLOR_MAIZE,
  COLOR_MAJORELLE_BLUE,
  COLOR_MALACHITE,
  COLOR_MANATEE,
  COLOR_MANGO_TANGO,
  COLOR_MANTIS,
  COLOR_MARDI_GRAS,
  COLOR_MAROON_CRAYOLA,
  COLOR_MAROON_HTML_CSS,
  COLOR_MAROON_X11,
  COLOR_MAUVE,
  COLOR_MAUVE_TAUPE,
  COLOR_MAUVELOUS,
  COLOR_MAYA_BLUE,
  COLOR_MEAT_BROWN,
  COLOR_MEDIUM_AQUAMARINE,
  COLOR_MEDIUM_BLUE,
  COLOR_MEDIUM_CANDY_APPLE_RED,
  COLOR_MEDIUM_CARMINE,
  COLOR_MEDIUM_CHAMPAGNE,
  COLOR_MEDIUM_ELECTRIC_BLUE,
  COLOR_MEDIUM_JUNGLE_GREEN,
  COLOR_MEDIUM_LAVENDER_MAGENTA,
  COLOR_MEDIUM_ORCHID,
  COLOR_MEDIUM_PERSIAN_BLUE,
  COLOR_MEDIUM_PURPLE,
  COLOR_MEDIUM_RED_VIOLET,
  COLOR_MEDIUM_RUBY,
  COLOR_MEDIUM_SEA_GREEN,
  COLOR_MEDIUM_SLATE_BLUE,
  COLOR_MEDIUM_SPRING_BUD,
  COLOR_MEDIUM_SPRING_GREEN,
  COLOR_MEDIUM_TAUPE,
  COLOR_MEDIUM_TURQUOISE,
  COLOR_MEDIUM_TUSCAN_RED,
  COLOR_MEDIUM_VERMILION,
  COLOR_MEDIUM_VIOLET_RED,
  COLOR_MELLOW_APRICOT,
  COLOR_MELLOW_YELLOW,
  COLOR_MELON,
  COLOR_MIDNIGHT_BLUE,
  COLOR_MIDNIGHT_GREEN_EAGLE_GREEN,
  COLOR_MIKADO_YELLOW,
  COLOR_MINT,
  COLOR_MINT_CREAM,
  COLOR_MINT_GREEN,
  COLOR_MISTY_ROSE,
  COLOR_MOCCASIN,
  COLOR_MODE_BEIGE,
  COLOR_MOONSTONE_BLUE,
  COLOR_MORDANT_RED_19,
  COLOR_MOSS_GREEN,
  COLOR_MOUNTAIN_MEADOW,
  COLOR_MOUNTBATTEN_PINK,
  COLOR_MSU_GREEN,
  COLOR_MULBERRY,
  COLOR_MUSTARD,
  COLOR_MYRTLE,
  COLOR_NADESHIKO_PINK,
  COLOR_NAPIER_GREEN,
  COLOR_NAPLES_YELLOW,
  COLOR_NAVAJO_WHITE,
  COLOR_NAVY_BLUE,
  COLOR_NEON_CARROT,
  COLOR_NEON_FUCHSIA,
  COLOR_NEON_GREEN,
  COLOR_NEW_YORK_PINK,
  COLOR_NON_PHOTO_BLUE,
  COLOR_NORTH_TEXAS_GREEN,
  COLOR_OCEAN_BOAT_BLUE,
  COLOR_OCHRE,
  COLOR_OFFICE_GREEN,
  COLOR_OLD_GOLD,
  COLOR_OLD_LACE,
  COLOR_OLD_LAVENDER,
  COLOR_OLD_MAUVE,
  COLOR_OLD_ROSE,
  COLOR_OLIVE,
  COLOR_OLIVE_DRAB_7,
  COLOR_OLIVE_DRAB_WEB_OLIVE_DRAB_3,
  COLOR_OLIVINE,
  COLOR_ONYX,
  COLOR_OPERA_MAUVE,
  COLOR_ORANGE_COLOR_WHEEL,
  COLOR_ORANGE_PEEL,
  COLOR_ORANGE_RED,
  COLOR_ORANGE_RYB,
  COLOR_ORANGE_WEB_COLOR,
  COLOR_ORCHID,
  COLOR_OTTER_BROWN,
  COLOR_OU_CRIMSON_RED,
  COLOR_OUTER_SPACE,
  COLOR_OUTRAGEOUS_ORANGE,
  COLOR_OXFORD_BLUE,
  COLOR_PAKISTAN_GREEN,
  COLOR_PALATINATE_BLUE,
  COLOR_PALATINATE_PURPLE,
  COLOR_PALE_AQUA,
  COLOR_PALE_BLUE,
  COLOR_PALE_BROWN,
  COLOR_PALE_CARMINE,
  COLOR_PALE_CERULEAN,
  COLOR_PALE_CHESTNUT,
  COLOR_PALE_COPPER,
  COLOR_PALE_CORNFLOWER_BLUE,
  COLOR_PALE_GOLD,
  COLOR_PALE_GOLDENROD,
  COLOR_PALE_GREEN,
  COLOR_PALE_LAVENDER,
  COLOR_PALE_MAGENTA,
  COLOR_PALE_PINK,
  COLOR_PALE_PLUM,
  COLOR_PALE_RED_VIOLET,
  COLOR_PALE_ROBIN_EGG_BLUE,
  COLOR_PALE_SILVER,
  COLOR_PALE_SPRING_BUD,
  COLOR_PALE_TAUPE,
  COLOR_PALE_VIOLET_RED,
  COLOR_PANSY_PURPLE,
  COLOR_PAPAYA_WHIP,
  COLOR_PARIS_GREEN,
  COLOR_PASTEL_BLUE,
  COLOR_PASTEL_BROWN,
  COLOR_PASTEL_GRAY,
  COLOR_PASTEL_GREEN,
  COLOR_PASTEL_MAGENTA,
  COLOR_PASTEL_ORANGE,
  COLOR_PASTEL_PINK,
  COLOR_PASTEL_PURPLE,
  COLOR_PASTEL_RED,
  COLOR_PASTEL_VIOLET,
  COLOR_PASTEL_YELLOW,
  COLOR_PATRIARCH,
  COLOR_PAYNE_S_GREY,
  COLOR_PEACH,
  COLOR_PEACH_CRAYOLA,
  COLOR_PEACH_ORANGE,
  COLOR_PEACH_PUFF,
  COLOR_PEACH_YELLOW,
  COLOR_PEAR,
  COLOR_PEARL,
  COLOR_PEARL_AQUA,
  COLOR_PEARLY_PURPLE,
  COLOR_PERIDOT,
  COLOR_PERIWINKLE,
  COLOR_PERSIAN_BLUE,
  COLOR_PERSIAN_GREEN,
  COLOR_PERSIAN_INDIGO,
  COLOR_PERSIAN_ORANGE,
  COLOR_PERSIAN_PINK,
  COLOR_PERSIAN_PLUM,
  COLOR_PERSIAN_RED,
  COLOR_PERSIAN_ROSE,
  COLOR_PERSIMMON,
  COLOR_PERU,
  COLOR_PHLOX,
  COLOR_PHTHALO_BLUE,
  COLOR_PHTHALO_GREEN,
  COLOR_PIGGY_PINK,
  COLOR_PINE_GREEN,
  COLOR_PINK,
  COLOR_PINK_LACE,
  COLOR_PINK_ORANGE,
  COLOR_PINK_PEARL,
  COLOR_PINK_SHERBET,
  COLOR_PISTACHIO,
  COLOR_PLATINUM,
  COLOR_PLUM_TRADITIONAL,
  COLOR_PLUM_WEB,
  COLOR_PORTLAND_ORANGE,
  COLOR_POWDER_BLUE_WEB,
  COLOR_PRINCETON_ORANGE,
  COLOR_PRUNE,
  COLOR_PRUSSIAN_BLUE,
  COLOR_PSYCHEDELIC_PURPLE,
  COLOR_PUCE,
  COLOR_PUMPKIN,
  COLOR_PURPLE_HEART,
  COLOR_PURPLE_HTML_CSS,
  COLOR_PURPLE_MOUNTAIN_MAJESTY,
  COLOR_PURPLE_MUNSELL,
  COLOR_PURPLE_PIZZAZZ,
  COLOR_PURPLE_TAUPE,
  COLOR_PURPLE_X11,
  COLOR_QUARTZ,
  COLOR_RACKLEY,
  COLOR_RADICAL_RED,
  COLOR_RAJAH,
  COLOR_RASPBERRY,
  COLOR_RASPBERRY_GLACE,
  COLOR_RASPBERRY_PINK,
  COLOR_RASPBERRY_ROSE,
  COLOR_RAW_UMBER,
  COLOR_RAZZLE_DAZZLE_ROSE,
  COLOR_RAZZMATAZZ,
  COLOR_RED,
  COLOR_RED_BROWN,
  COLOR_RED_DEVIL,
  COLOR_RED_MUNSELL,
  COLOR_RED_NCS,
  COLOR_RED_ORANGE,
  COLOR_RED_PIGMENT,
  COLOR_RED_RYB,
  COLOR_RED_VIOLET,
  COLOR_REDWOOD,
  COLOR_REGALIA,
  COLOR_RESOLUTION_BLUE,
  COLOR_RICH_BLACK,
  COLOR_RICH_BRILLIANT_LAVENDER,
  COLOR_RICH_CARMINE,
  COLOR_RICH_ELECTRIC_BLUE,
  COLOR_RICH_LAVENDER,
  COLOR_RICH_LILAC,
  COLOR_RICH_MAROON,
  COLOR_RIFLE_GREEN,
  COLOR_ROBIN_EGG_BLUE,
  COLOR_ROSE,
  COLOR_ROSE_BONBON,
  COLOR_ROSE_EBONY,
  COLOR_ROSE_GOLD,
  COLOR_ROSE_MADDER,
  COLOR_ROSE_PINK,
  COLOR_ROSE_QUARTZ,
  COLOR_ROSE_TAUPE,
  COLOR_ROSE_VALE,
  COLOR_ROSEWOOD,
  COLOR_ROSSO_CORSA,
  COLOR_ROSY_BROWN,
  COLOR_ROYAL_AZURE,
  COLOR_ROYAL_BLUE_TRADITIONAL,
  COLOR_ROYAL_BLUE_WEB,
  COLOR_ROYAL_FUCHSIA,
  COLOR_ROYAL_PURPLE,
  COLOR_ROYAL_YELLOW,
  COLOR_RUBINE_RED,
  COLOR_RUBY,
  COLOR_RUBY_RED,
  COLOR_RUDDY,
  COLOR_RUDDY_BROWN,
  COLOR_RUDDY_PINK,
  COLOR_RUFOUS,
  COLOR_RUSSET,
  COLOR_RUST,
  COLOR_RUSTY_RED,
  COLOR_SACRAMENTO_STATE_GREEN,
  COLOR_SADDLE_BROWN,
  COLOR_SAFETY_ORANGE_BLAZE_ORANGE,
  COLOR_SAFFRON,
  COLOR_SALMON,
  COLOR_SALMON_PINK,
  COLOR_SAND,
  COLOR_SAND_DUNE,
  COLOR_SANDSTORM,
  COLOR_SANDY_BROWN,
  COLOR_SANDY_TAUPE,
  COLOR_SANGRIA,
  COLOR_SAP_GREEN,
  COLOR_SAPPHIRE,
  COLOR_SAPPHIRE_BLUE,
  COLOR_SATIN_SHEEN_GOLD,
  COLOR_SCARLET,
  COLOR_SCARLET_CRAYOLA,
  COLOR_SCHOOL_BUS_YELLOW,
  COLOR_SCREAMIN_GREEN,
  COLOR_SEA_BLUE,
  COLOR_SEA_GREEN,
  COLOR_SEAL_BROWN,
  COLOR_SEASHELL,
  COLOR_SELECTIVE_YELLOW,
  COLOR_SEPIA,
  COLOR_SHADOW,
  COLOR_SHAMROCK_GREEN,
  COLOR_SHOCKING_PINK,
  COLOR_SHOCKING_PINK_CRAYOLA,
  COLOR_SIENNA,
  COLOR_SILVER,
  COLOR_SINOPIA,
  COLOR_SKOBELOFF,
  COLOR_SKY_BLUE,
  COLOR_SKY_MAGENTA,
  COLOR_SLATE_BLUE,
  COLOR_SLATE_GRAY,
  COLOR_SMALT_DARK_POWDER_BLUE,
  COLOR_SMOKEY_TOPAZ,
  COLOR_SMOKY_BLACK,
  COLOR_SNOW,
  COLOR_SPIRO_DISCO_BALL,
  COLOR_SPRING_BUD,
  COLOR_SPRING_GREEN,
  COLOR_ST_PATRICK_S_BLUE,
  COLOR_STEEL_BLUE,
  COLOR_STIL_DE_GRAIN_YELLOW,
  COLOR_STIZZA,
  COLOR_STORMCLOUD,
  COLOR_STRAW,
  COLOR_SUNGLOW,
  COLOR_SUNSET,
  COLOR_TAN,
  COLOR_TANGELO,
  COLOR_TANGERINE,
  COLOR_TANGERINE_YELLOW,
  COLOR_TANGO_PINK,
  COLOR_TAUPE,
  COLOR_TAUPE_GRAY,
  COLOR_TEA_GREEN,
  COLOR_TEA_ROSE_ORANGE,
  COLOR_TEA_ROSE_ROSE,
  COLOR_TEAL,
  COLOR_TEAL_BLUE,
  COLOR_TEAL_GREEN,
  COLOR_TELEMAGENTA,
  COLOR_TENN_TAWNY,
  COLOR_TERRA_COTTA,
  COLOR_THISTLE,
  COLOR_THULIAN_PINK,
  COLOR_TICKLE_ME_PINK,
  COLOR_TIFFANY_BLUE,
  COLOR_TIGER_S_EYE,
  COLOR_TIMBERWOLF,
  COLOR_TITANIUM_YELLOW,
  COLOR_TOMATO,
  COLOR_TOOLBOX,
  COLOR_TOPAZ,
  COLOR_TRACTOR_RED,
  COLOR_TROLLEY_GREY,
  COLOR_TROPICAL_RAIN_FOREST,
  COLOR_TRUE_BLUE,
  COLOR_TUFTS_BLUE,
  COLOR_TUMBLEWEED,
  COLOR_TURKISH_ROSE,
  COLOR_TURQUOISE,
  COLOR_TURQUOISE_BLUE,
  COLOR_TURQUOISE_GREEN,
  COLOR_TUSCAN_RED,
  COLOR_TWILIGHT_LAVENDER,
  COLOR_TYRIAN_PURPLE,
  COLOR_UA_BLUE,
  COLOR_UA_RED,
  COLOR_UBE,
  COLOR_UCLA_BLUE,
  COLOR_UCLA_GOLD,
  COLOR_UFO_GREEN,
  COLOR_ULTRA_PINK,
  COLOR_ULTRAMARINE,
  COLOR_ULTRAMARINE_BLUE,
  COLOR_UMBER,
  COLOR_UNBLEACHED_SILK,
  COLOR_UNITED_NATIONS_BLUE,
  COLOR_UNIVERSITY_OF_CALIFORNIA_GOLD,
  COLOR_UNMELLOW_YELLOW,
  COLOR_UP_FOREST_GREEN,
  COLOR_UP_MAROON,
  COLOR_UPSDELL_RED,
  COLOR_UROBILIN,
  COLOR_USAFA_BLUE,
  COLOR_USC_CARDINAL,
  COLOR_USC_GOLD,
  COLOR_UTAH_CRIMSON,
  COLOR_VANILLA,
  COLOR_VEGAS_GOLD,
  COLOR_VENETIAN_RED,
  COLOR_VERDIGRIS,
  COLOR_VERMILION_CINNABAR,
  COLOR_VERMILION_PLOCHERE,
  COLOR_VERONICA,
  COLOR_VIOLET,
  COLOR_VIOLET_BLUE,
  COLOR_VIOLET_COLOR_WHEEL,
  COLOR_VIOLET_RYB,
  COLOR_VIOLET_WEB,
  COLOR_VIRIDIAN,
  COLOR_VIVID_AUBURN,
  COLOR_VIVID_BURGUNDY,
  COLOR_VIVID_CERISE,
  COLOR_VIVID_TANGERINE,
  COLOR_VIVID_VIOLET,
  COLOR_WARM_BLACK,
  COLOR_WATERSPOUT,
  COLOR_WENGE,
  COLOR_WHEAT,
  COLOR_WHITE,
  COLOR_WHITE_SMOKE,
  COLOR_WILD_BLUE_YONDER,
  COLOR_WILD_STRAWBERRY,
  COLOR_WILD_WATERMELON,
  COLOR_WINE,
  COLOR_WINE_DREGS,
  COLOR_WISTERIA,
  COLOR_WOOD_BROWN,
  COLOR_XANADU,
  COLOR_YALE_BLUE,
  COLOR_YELLOW,
  COLOR_YELLOW_GREEN,
  COLOR_YELLOW_MUNSELL,
  COLOR_YELLOW_NCS,
  COLOR_YELLOW_ORANGE,
  COLOR_YELLOW_PROCESS,
  COLOR_YELLOW_RYB,
  COLOR_ZAFFRE,
  COLOR_ZINNWALDITE_BROWN
} Color;

bool str2Rgb( char *s, Rgb *color );
bool RgbNE( Rgb a, Rgb b );

#endif // CNAMES_H_
