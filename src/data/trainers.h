#include "battle.h"
#include "data.h"
#include "constants/battle.h"
#include "constants/battle_ai.h"

const struct Trainer gTrainers[] = {
    [TRAINER_NONE] = {
        
        .trainerClass = CLASS_PKMN_TRAINER_NONE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_AQUA_LEADER_ARCHIE,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = 0,
        .partySize = 0,
        .initialPartysize = 0,
        .party = NULL
    },
    [TRAINER_AQUA_LEADER_1] = {
        
        .trainerClass = CLASS_AQUA_LEADER,//works like a lookup table value define in trainer_classes.h then refers to array order in 
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,//trainer_class_names.h so renaming output is just changing names file
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_AQUA_LEADER_ARCHIE, //reverted "gamer" back to "gambler
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,//noticed trainer_class_names had .inc file, changed Gambler string there as well just in case
        .partySize = NELEMS(sTrainerMons_AquaLeader1),
        .initialPartysize = NELEMS(sTrainerMons_AquaLeader1),
        .party = sTrainerMons_AquaLeader1//got weird compiler error so reverted, may be one ofthose files u don't change
    },
    [TRAINER_TEAM_AQUA_1] = {
        
        .trainerClass = CLASS_TEAM_AQUA,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_AQUA_GRUNT_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamAqua1),
        .initialPartysize = NELEMS(sTrainerMons_TeamAqua1),
        .party = sTrainerMons_TeamAqua1 //ok rather than needing category specific see if I can just make it auto read what category the name uses, so I would only need the trainer name here
    },                                              //like its nice and readible but annoying to work with.  very rigid.  if I change it in trainerparties it breaks if I dont also change it here
    [TRAINER_TEAM_AQUA_2] = {
        
        .trainerClass = CLASS_TEAM_AQUA,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_AQUA_GRUNT_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamAqua2),
        .initialPartysize = NELEMS(sTrainerMons_TeamAqua2),
        .party = sTrainerMons_TeamAqua2
    },
    [TRAINER_AROMA_LADY_1] = {
        
        .trainerClass = CLASS_AROMA_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_AROMA_LADY,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_AromaLady1),
        .initialPartysize = NELEMS(sTrainerMons_AromaLady1),
        .party = sTrainerMons_AromaLady1,
    },
    [TRAINER_RUIN_MANIAC_1] = {
        
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_RUIN_MANIAC,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RuinManiac1),
        .initialPartysize = NELEMS(sTrainerMons_RuinManiac1),
        .party = sTrainerMons_RuinManiac1
    },
    [TRAINER_INTERVIEWER_1] = {
        
        .trainerClass = CLASS_INTERVIEWER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTERVIEWER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_INTERVIEWER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Interviewer1),
        .initialPartysize = NELEMS(sTrainerMons_Interviewer1),
        .party = sTrainerMons_Interviewer1
    },
    [TRAINER_TUBER_1] = {
        
        .trainerClass = CLASS_TUBER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_TUBER_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Tuber1),
        .initialPartysize = NELEMS(sTrainerMons_Tuber1),
        .party = sTrainerMons_Tuber1
    },
    [TRAINER_TUBER_2] = {
        
        .trainerClass = CLASS_TUBER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_TUBER_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Tuber2),
        .initialPartysize = NELEMS(sTrainerMons_Tuber2),
        .party = sTrainerMons_Tuber2
    },
    [TRAINER_COOLTRAINER_1] = {
        
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_Cooltrainer1),
        .initialPartysize = NELEMS(sTrainerMons_Cooltrainer1),
        .party = sTrainerMons_Cooltrainer1
    },
    [TRAINER_COOLTRAINER_2] = {
        
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_Cooltrainer2),
        .initialPartysize = NELEMS(sTrainerMons_Cooltrainer2),
        .party = sTrainerMons_Cooltrainer2
    },
    [TRAINER_HEX_MANIAC_1] = {
        
        .trainerClass = CLASS_HEX_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HEX_MANIAC,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HexManiac1),
        .initialPartysize = NELEMS(sTrainerMons_HexManiac1),
        .party = sTrainerMons_HexManiac1
    },
    [TRAINER_LADY_1] = {
        
        .trainerClass = CLASS_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LADY,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Lady1),
        .initialPartysize = NELEMS(sTrainerMons_Lady1),
        .party = sTrainerMons_Lady1
    },
    [TRAINER_BEAUTY_1] = {
        
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_BEAUTY,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Beauty1),
        .initialPartysize = NELEMS(sTrainerMons_Beauty1),
        .party = sTrainerMons_Beauty1
    },
    [TRAINER_RICH_BOY_1] = {
        
        .trainerClass = CLASS_RICH_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_RICH,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RICH_BOY,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RichBoy1),
        .initialPartysize = NELEMS(sTrainerMons_RichBoy1),
        .party = sTrainerMons_RichBoy1
    },
    [TRAINER_POKEMANIAC_1] = {
        
        .trainerClass = CLASS_POKEMANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_POKEMANIAC,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Pokemaniac1),
        .initialPartysize = NELEMS(sTrainerMons_Pokemaniac1),
        .party = sTrainerMons_Pokemaniac1
    },
    [TRAINER_SWIMMER_MALE_1] = {
        
        .trainerClass = CLASS_SWIMMER_MALE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_SWIMMER_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMale1),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMale1),
        .party = sTrainerMons_SwimmerMale1
    },
    [TRAINER_BLACK_BELT_1] = {
        
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBelt1),
        .initialPartysize = NELEMS(sTrainerMons_BlackBelt1),
        .party = sTrainerMons_BlackBelt1
    },
    [TRAINER_GUITARIST_1] = {
        
        .trainerClass = CLASS_GUITARIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Guitarist1),
        .initialPartysize = NELEMS(sTrainerMons_Guitarist1),
        .party = sTrainerMons_Guitarist1
    },
    [TRAINER_KINDLER_1] = {
        
        .trainerClass = CLASS_KINDLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_KINDLER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Kindler1),
        .initialPartysize = NELEMS(sTrainerMons_Kindler1),
        .party = sTrainerMons_Kindler1
    },
    [TRAINER_CAMPER_1] = {
        
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_CAMPER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Camper1),
        .initialPartysize = NELEMS(sTrainerMons_Camper1),
        .party = sTrainerMons_Camper1
    },
    [TRAINER_BUG_MANIAC_1] = {
        
        .trainerClass = CLASS_BUG_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_MANIAC,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugManiac1),
        .initialPartysize = NELEMS(sTrainerMons_BugManiac1),
        .party = sTrainerMons_BugManiac1
    },
    [TRAINER_PSYCHIC_1] = {
        
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_PSYCHIC_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Psychic1),
        .initialPartysize = NELEMS(sTrainerMons_Psychic1),
        .party = sTrainerMons_Psychic1
    },
    [TRAINER_PSYCHIC_2] = {
        
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_PSYCHIC_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Psychic2),
        .initialPartysize = NELEMS(sTrainerMons_Psychic2),
        .party = sTrainerMons_Psychic2
    },
    [TRAINER_GENTLEMAN_1] = {
        
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_RICH,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_GENTLEMAN,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Gentleman1),
        .initialPartysize = NELEMS(sTrainerMons_Gentleman1),
        .party = sTrainerMons_Gentleman1
    },
    [TRAINER_ELITE_FOUR_SIDNEY] = {
        
        .trainerClass = CLASS_ELITE_FOUR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_SIDNEY,
        .trainerName = _("SIDNEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_EliteFourSidney),
        .initialPartysize = NELEMS(sTrainerMons_EliteFourSidney),
        .party = sTrainerMons_EliteFourSidney
    },
    [TRAINER_ELITE_FOUR_PHOEBE] = {
        
        .trainerClass = CLASS_ELITE_FOUR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_PHOEBE,
        .trainerName = _("PHOEBE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_EliteFourPhoebe),
        .initialPartysize = NELEMS(sTrainerMons_EliteFourPhoebe),
        .party = sTrainerMons_EliteFourPhoebe
    },
    [TRAINER_LEADER_ROXANNE] = {
        
        .trainerClass = CLASS_GYM_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_ROXANNE,
        .trainerName = _("ROXANNE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LeaderRoxanne),
        .initialPartysize = NELEMS(sTrainerMons_LeaderRoxanne),
        .party = sTrainerMons_LeaderRoxanne
    },
    [TRAINER_LEADER_BRAWLY] = {
        
        .trainerClass = CLASS_GYM_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_LEADER_BRAWLY,
        .trainerName = _("BRAWLY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LeaderBrawly),
        .initialPartysize = NELEMS(sTrainerMons_LeaderBrawly),
        .party = sTrainerMons_LeaderBrawly
    },
    [TRAINER_LEADER_TATE_LIZA] = {
        
        .trainerClass = CLASS_GYM_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_LEADER_TATE_AND_LIZA,
        .trainerName = _("TATE&LIZA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LeaderTateLiza),
        .initialPartysize = NELEMS(sTrainerMons_LeaderTateLiza),
        .party = sTrainerMons_LeaderTateLiza
    },
    [TRAINER_SCHOOL_KID_1] = {
        
        .trainerClass = CLASS_SCHOOL_KID,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCHOOL_KID_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SchoolKid1),
        .initialPartysize = NELEMS(sTrainerMons_SchoolKid1),
        .party = sTrainerMons_SchoolKid1
    },
    [TRAINER_SCHOOL_KID_2] = {
        
        .trainerClass = CLASS_SCHOOL_KID,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SCHOOL_KID_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SchoolKid2),
        .initialPartysize = NELEMS(sTrainerMons_SchoolKid2),
        .party = sTrainerMons_SchoolKid2
    },
    [TRAINER_SR_AND_JR_1] = {
        
        .trainerClass = CLASS_SR_AND_JR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SR_AND_JR,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SrAndJr1),
        .initialPartysize = NELEMS(sTrainerMons_SrAndJr1),
        .party = sTrainerMons_SrAndJr1
    },
    [TRAINER_POKEFAN_1] = {
        
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Pokefan1),
        .initialPartysize = NELEMS(sTrainerMons_Pokefan1),
        .party = sTrainerMons_Pokefan1
    },
    [TRAINER_POKEFAN_2] = {
        
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Pokefan2),
        .initialPartysize = NELEMS(sTrainerMons_Pokefan2),
        .party = sTrainerMons_Pokefan2
    },
    [TRAINER_EXPERT_1] = {
        
        .trainerClass = CLASS_EXPERT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_EXPERT_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Expert1),
        .initialPartysize = NELEMS(sTrainerMons_Expert1),
        .party = sTrainerMons_Expert1
    },
    [TRAINER_EXPERT_2] = {
        
        .trainerClass = CLASS_EXPERT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_EXPERT_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Expert2),
        .initialPartysize = NELEMS(sTrainerMons_Expert2),
        .party = sTrainerMons_Expert2
    },
    [TRAINER_YOUNGSTER_1] = {
        
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_YOUNGSTER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Youngster1),
        .initialPartysize = NELEMS(sTrainerMons_Youngster1),
        .party = sTrainerMons_Youngster1
    },
    [TRAINER_CHAMPION_1] = {
        
        .trainerClass = CLASS_CHAMPION,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_STEVEN,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_Champion1),
        .initialPartysize = NELEMS(sTrainerMons_Champion1),
        .party = sTrainerMons_Champion1
    },
    [TRAINER_FISHERMAN_1] = {
        
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_FISHERMAN,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Fisherman1),
        .initialPartysize = NELEMS(sTrainerMons_Fisherman1),
        .party = sTrainerMons_Fisherman1
    },
    [TRAINER_TRIATHLETE_1] = {
        
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CYCLING_TRIATHLETE_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Triathlete1),
        .initialPartysize = NELEMS(sTrainerMons_Triathlete1),
        .party = sTrainerMons_Triathlete1
    },
    [TRAINER_TRIATHLETE_2] = {
        
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CYCLING_TRIATHLETE_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Triathlete2),
        .initialPartysize = NELEMS(sTrainerMons_Triathlete2),
        .party = sTrainerMons_Triathlete2
    },
    [TRAINER_TRIATHLETE_3] = {
        
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Triathlete3),
        .initialPartysize = NELEMS(sTrainerMons_Triathlete3),
        .party = sTrainerMons_Triathlete3
    },
    [TRAINER_TRIATHLETE_4] = {
        
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Triathlete4),
        .initialPartysize = NELEMS(sTrainerMons_Triathlete4),
        .party = sTrainerMons_Triathlete4
    },
    [TRAINER_TRIATHLETE_5] = {
        
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMING_TRIATHLETE_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Triathlete5),
        .initialPartysize = NELEMS(sTrainerMons_Triathlete5),
        .party = sTrainerMons_Triathlete5
    },
    [TRAINER_TRIATHLETE_6] = {
        
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMING_TRIATHLETE_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Triathlete6),
        .initialPartysize = NELEMS(sTrainerMons_Triathlete6),
        .party = sTrainerMons_Triathlete6
    },
    [TRAINER_DRAGON_TAMER_1] = {
        
        .trainerClass = CLASS_DRAGON_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_DragonTamer1),
        .initialPartysize = NELEMS(sTrainerMons_DragonTamer1),
        .party = sTrainerMons_DragonTamer1
    },
    [TRAINER_BIRD_KEEPER_1] = {
        
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_BIRD_KEEPER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeper1),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeper1),
        .party = sTrainerMons_BirdKeeper1
    },
    [TRAINER_NINJA_BOY_1] = {
        
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_NinjaBoy1),
        .initialPartysize = NELEMS(sTrainerMons_NinjaBoy1),
        .party = sTrainerMons_NinjaBoy1
    },
    [TRAINER_BATTLE_GIRL_1] = {
        
        .trainerClass = CLASS_BATTLE_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_BATTLE_GIRL,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BattleGirl1),
        .initialPartysize = NELEMS(sTrainerMons_BattleGirl1),
        .party = sTrainerMons_BattleGirl1
    },
    [TRAINER_PARASOL_LADY_1] = {
        
        .trainerClass = CLASS_PARASOL_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ParasolLady1),
        .initialPartysize = NELEMS(sTrainerMons_ParasolLady1),
        .party = sTrainerMons_ParasolLady1
    },
    [TRAINER_SWIMMER_FEMALE_1] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_SWIMMER_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemale1),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemale1),
        .party = sTrainerMons_SwimmerFemale1
    },
    [TRAINER_PICNICKER_1] = {
        
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_PICNICKER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Picnicker1),
        .initialPartysize = NELEMS(sTrainerMons_Picnicker1),
        .party = sTrainerMons_Picnicker1
    },
    [TRAINER_TWINS_1] = {
        
        .trainerClass = CLASS_TWINS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_TWINS,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Twins1),
        .initialPartysize = NELEMS(sTrainerMons_Twins1),
        .party = sTrainerMons_Twins1
    },
    [TRAINER_SAILOR_1] = {
        
        .trainerClass = CLASS_SAILOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_SAILOR,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Sailor1),
        .initialPartysize = NELEMS(sTrainerMons_Sailor1),
        .party = sTrainerMons_Sailor1
    },
    [TRAINER_BOARDER_1] = {
        
        .trainerClass = CLASS_BOARDER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_YOUNGSTER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Boarder1),
        .initialPartysize = NELEMS(sTrainerMons_Boarder1),
        .party = sTrainerMons_Boarder1
    },
    [TRAINER_BOARDER_2] = {
        
        .trainerClass = CLASS_BOARDER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_YOUNGSTER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Boarder2),
        .initialPartysize = NELEMS(sTrainerMons_Boarder2),
        .party = sTrainerMons_Boarder2
    },
    [TRAINER_COLLECTOR_1] = {
        
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Collector1),
        .initialPartysize = NELEMS(sTrainerMons_Collector1),
        .party = sTrainerMons_Collector1
    },
    [TRAINER_PKMN_TRAINER_2] = {
        
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_WALLY,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnTrainer2),
        .initialPartysize = NELEMS(sTrainerMons_PkmnTrainer2),
        .party = sTrainerMons_PkmnTrainer2
    },
    [TRAINER_PKMN_TRAINER_3] = {
        
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_BRENDAN_1,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnTrainer3),
        .initialPartysize = NELEMS(sTrainerMons_PkmnTrainer3),
        .party = sTrainerMons_PkmnTrainer3
    },
    [TRAINER_PKMN_TRAINER_4] = {
        
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_BRENDAN_1,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnTrainer4),
        .initialPartysize = NELEMS(sTrainerMons_PkmnTrainer4),
        .party = sTrainerMons_PkmnTrainer4
    },
    [TRAINER_PKMN_TRAINER_5] = {
        
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_BRENDAN_1,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnTrainer5),
        .initialPartysize = NELEMS(sTrainerMons_PkmnTrainer5),
        .party = sTrainerMons_PkmnTrainer5
    },
    [TRAINER_PKMN_TRAINER_6] = {
        
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_MAY_1,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnTrainer6),
        .initialPartysize = NELEMS(sTrainerMons_PkmnTrainer6),
        .party = sTrainerMons_PkmnTrainer6
    },
    [TRAINER_PKMN_TRAINER_7] = {
        
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_MAY_1,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnTrainer7),
        .initialPartysize = NELEMS(sTrainerMons_PkmnTrainer7),
        .party = sTrainerMons_PkmnTrainer7
    },
    [TRAINER_PKMN_TRAINER_8] = {
        
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_MAY_1,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnTrainer8),
        .initialPartysize = NELEMS(sTrainerMons_PkmnTrainer8),
        .party = sTrainerMons_PkmnTrainer8
    },
    [TRAINER_PKMN_BREEDER_1] = {
        
        .trainerClass = CLASS_PKMN_BREEDER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_POKEMON_BREEDER_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnBreeder1),
        .initialPartysize = NELEMS(sTrainerMons_PkmnBreeder1),
        .party = sTrainerMons_PkmnBreeder1
    },
    [TRAINER_PKMN_BREEDER_2] = {
        
        .trainerClass = CLASS_PKMN_BREEDER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_POKEMON_BREEDER_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnBreeder2),
        .initialPartysize = NELEMS(sTrainerMons_PkmnBreeder2),
        .party = sTrainerMons_PkmnBreeder2
    },
    [TRAINER_PKMN_RANGER_1] = {
        
        .trainerClass = CLASS_PKMN_RANGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_POKEMON_RANGER_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_PkmnRanger1),
        .initialPartysize = NELEMS(sTrainerMons_PkmnRanger1),
        .party = sTrainerMons_PkmnRanger1
    },
    [TRAINER_PKMN_RANGER_2] = {
        
        .trainerClass = CLASS_PKMN_RANGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_POKEMON_RANGER_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_PkmnRanger2),
        .initialPartysize = NELEMS(sTrainerMons_PkmnRanger2),
        .party = sTrainerMons_PkmnRanger2
    },
    [TRAINER_MAGMA_LEADER_1] = {
        
        .trainerClass = CLASS_MAGMA_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_MAGMA_LEADER_MAXIE,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_MagmaLeader1),
        .initialPartysize = NELEMS(sTrainerMons_MagmaLeader1),
        .party = sTrainerMons_MagmaLeader1
    },
    [TRAINER_TEAM_MAGMA_1] = {
        
        .trainerClass = CLASS_TEAM_MAGMA,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_MAGMA_GRUNT_M,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamMagma1),
        .initialPartysize = NELEMS(sTrainerMons_TeamMagma1),
        .party = sTrainerMons_TeamMagma1
    },
    [TRAINER_TEAM_MAGMA_2] = {
        
        .trainerClass = CLASS_TEAM_MAGMA,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_MAGMA_GRUNT_F,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamMagma2),
        .initialPartysize = NELEMS(sTrainerMons_TeamMagma2),
        .party = sTrainerMons_TeamMagma2
    },
    [TRAINER_LASS_1] = {
        
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LASS,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Lass1),
        .initialPartysize = NELEMS(sTrainerMons_Lass1),
        .party = sTrainerMons_Lass1
    },
    [TRAINER_BUG_CATCHER_1] = {
        
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcher1),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcher1),
        .party = sTrainerMons_BugCatcher1
    },
    [TRAINER_HIKER_1] = {
        
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_HIKER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Hiker1),
        .initialPartysize = NELEMS(sTrainerMons_Hiker1),
        .party = sTrainerMons_Hiker1
    },
    [TRAINER_YOUNG_COUPLE_1] = {
        
        .trainerClass = CLASS_YOUNG_COUPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_YOUNG_COUPLE,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungCouple1),
        .initialPartysize = NELEMS(sTrainerMons_YoungCouple1),
        .party = sTrainerMons_YoungCouple1
    },
    [TRAINER_OLD_COUPLE_1] = {
        
        .trainerClass = CLASS_OLD_COUPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_OLD_COUPLE,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_OldCouple1),
        .initialPartysize = NELEMS(sTrainerMons_OldCouple1),
        .party = sTrainerMons_OldCouple1
    },
    [TRAINER_SIS_AND_BRO_1] = {
        
        .trainerClass = CLASS_SIS_AND_BRO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_SIS_AND_BRO,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SisAndBro1),
        .initialPartysize = NELEMS(sTrainerMons_SisAndBro1),
        .party = sTrainerMons_SisAndBro1
    },
    [TRAINER_AQUA_ADMIN_MATT] = {
        
        .trainerClass = CLASS_AQUA_ADMIN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_AQUA_ADMIN_M,
        .trainerName = _("MATT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_AquaAdminMatt),
        .initialPartysize = NELEMS(sTrainerMons_AquaAdminMatt),
        .party = sTrainerMons_AquaAdminMatt
    },
    [TRAINER_AQUA_ADMIN_SHELLY] = {
        
        .trainerClass = CLASS_AQUA_ADMIN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_AQUA_ADMIN_F,
        .trainerName = _("SHELLY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_AquaAdminShelly),
        .initialPartysize = NELEMS(sTrainerMons_AquaAdminShelly),
        .party = sTrainerMons_AquaAdminShelly
    },
    [TRAINER_MAGMA_ADMIN_TABITHA] = {
        
        .trainerClass = CLASS_MAGMA_ADMIN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_MAGMA_ADMIN_M,
        .trainerName = _("TABITHA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_MagmaAdminTabitha),
        .initialPartysize = NELEMS(sTrainerMons_MagmaAdminTabitha),
        .party = sTrainerMons_MagmaAdminTabitha
    },
    [TRAINER_MAGMA_ADMIN_COURTNEY] = {
        
        .trainerClass = CLASS_MAGMA_ADMIN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_MAGMA_ADMIN_F,
        .trainerName = _("COURTNEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_MagmaAdminCourtney),
        .initialPartysize = NELEMS(sTrainerMons_MagmaAdminCourtney),
        .party = sTrainerMons_MagmaAdminCourtney
    },
    [TRAINER_LEADER_WATTSON] = {
        
        .trainerClass = CLASS_GYM_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_LEADER_WATTSON,
        .trainerName = _("WATTSON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LeaderWattson),
        .initialPartysize = NELEMS(sTrainerMons_LeaderWattson),
        .party = sTrainerMons_LeaderWattson
    },
    [TRAINER_LEADER_FLANNERY] = {
        
        .trainerClass = CLASS_GYM_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_FLANNERY,
        .trainerName = _("FLANNERY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LeaderFlannery),
        .initialPartysize = NELEMS(sTrainerMons_LeaderFlannery),
        .party = sTrainerMons_LeaderFlannery
    },
    [TRAINER_LEADER_NORMAN] = {
        
        .trainerClass = CLASS_GYM_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_LEADER_NORMAN,
        .trainerName = _("NORMAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LeaderNorman),
        .initialPartysize = NELEMS(sTrainerMons_LeaderNorman),
        .party = sTrainerMons_LeaderNorman
    },
    [TRAINER_LEADER_WINONA] = {
        
        .trainerClass = CLASS_GYM_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_WINONA,
        .trainerName = _("WINONA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LeaderWinona),
        .initialPartysize = NELEMS(sTrainerMons_LeaderWinona),
        .party = sTrainerMons_LeaderWinona
    },
    [TRAINER_LEADER_WALLACE] = {
        
        .trainerClass = CLASS_GYM_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_LEADER_WALLACE,
        .trainerName = _("WALLACE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LeaderWallace),
        .initialPartysize = NELEMS(sTrainerMons_LeaderWallace),
        .party = sTrainerMons_LeaderWallace
    },
    [TRAINER_ELITE_FOUR_GLACIA] = {
        
        .trainerClass = CLASS_ELITE_FOUR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_GLACIA,
        .trainerName = _("GLACIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_EliteFourGlacia),
        .initialPartysize = NELEMS(sTrainerMons_EliteFourGlacia),
        .party = sTrainerMons_EliteFourGlacia
    },
    [TRAINER_ELITE_FOUR_DRAKE] = {
        
        .trainerClass = CLASS_ELITE_FOUR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_DRAKE,
        .trainerName = _("DRAKE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_EliteFourDrake),
        .initialPartysize = NELEMS(sTrainerMons_EliteFourDrake),
        .party = sTrainerMons_EliteFourDrake
    },
    [TRAINER_YOUNGSTER_BEN] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("BEN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterBen),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterBen),
        .party = sTrainerMons_YoungsterBen
    },//proves concept of dynamic rematch sans vs seeker
    //youngster Ben has 4 variants trainer ai doesn't change
    //all it does is increase lvl of team then evolve team
    //as I thought I can easily simulate that
    //by limiting initial party size believe I should be able to adjust trainer ai flag on the go
    //the curious part is if I can add items later
    //maybe can do my idea of making trainer classes more impactful and distinct
    //make table of items by trainer calss and just add that on higher lvl rematches? 
    //vsonic important
    [TRAINER_YOUNGSTER_CALVIN] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("CALVIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterCalvin),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterCalvin),
        .party = sTrainerMons_YoungsterCalvin
    },
    [TRAINER_YOUNGSTER_JOSH] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("JOSH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterJosh),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterJosh),
        .party = sTrainerMons_YoungsterJosh
    },
    [TRAINER_YOUNGSTER_TIMMY] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("TIMMY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterTimmy),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterTimmy),
        .party = sTrainerMons_YoungsterTimmy
    },
    [TRAINER_YOUNGSTER_JOEY] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("JOEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterJoey),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterJoey),
        .party = sTrainerMons_YoungsterJoey
    },
    [TRAINER_YOUNGSTER_DAN] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("DAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterDan),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterDan),
        .party = sTrainerMons_YoungsterDan
    },
    [TRAINER_YOUNGSTER_CHAD] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("CHAD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterChad),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterChad),
        .party = sTrainerMons_YoungsterChad
    },
    [TRAINER_YOUNGSTER_TYLER] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("TYLER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterTyler),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterTyler),
        .party = sTrainerMons_YoungsterTyler
    },
    [TRAINER_YOUNGSTER_EDDIE] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("EDDIE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterEddie),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterEddie),
        .party = sTrainerMons_YoungsterEddie
    },
    [TRAINER_YOUNGSTER_DILLON] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("DILLON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterDillon),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterDillon),
        .party = sTrainerMons_YoungsterDillon
    },
    [TRAINER_YOUNGSTER_YASU] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("YASU"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterYasu),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterYasu),
        .party = sTrainerMons_YoungsterYasu
    },
    [TRAINER_YOUNGSTER_DAVE] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("DAVE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterDave),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterDave),
        .party = sTrainerMons_YoungsterDave
    },
    [TRAINER_YOUNGSTER_BEN_2] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("BEN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterBen2),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterBen2),
        .party = sTrainerMons_YoungsterBen2
    },
    [TRAINER_BUG_CATCHER_RICK] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("RICK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherRick),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherRick),
        .party = sTrainerMons_BugCatcherRick
    },
    [TRAINER_BUG_CATCHER_DOUG] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("DOUG"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherDoug),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherDoug),
        .party = sTrainerMons_BugCatcherDoug
    },
    [TRAINER_BUG_CATCHER_SAMMY] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("SAMMY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherSammy),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherSammy),
        .party = sTrainerMons_BugCatcherSammy
    },
    [TRAINER_BUG_CATCHER_COLTON] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("COLTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherColton),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherColton),
        .party = sTrainerMons_BugCatcherColton
    },
    [TRAINER_BUG_CATCHER_GREG] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("GREG"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherGreg),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherGreg),
        .party = sTrainerMons_BugCatcherGreg
    },
    [TRAINER_BUG_CATCHER_JAMES] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("JAMES"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherJames),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherJames),
        .party = sTrainerMons_BugCatcherJames
    },
    [TRAINER_BUG_CATCHER_KENT] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("KENT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherKent),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherKent),
        .party = sTrainerMons_BugCatcherKent
    },
    [TRAINER_BUG_CATCHER_ROBBY] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("ROBBY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherRobby),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherRobby),
        .party = sTrainerMons_BugCatcherRobby
    },
    [TRAINER_BUG_CATCHER_CALE] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("CALE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherCale),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherCale),
        .party = sTrainerMons_BugCatcherCale
    },
    [TRAINER_BUG_CATCHER_KEIGO] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("KEIGO"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherKeigo),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherKeigo),
        .party = sTrainerMons_BugCatcherKeigo
    },
    [TRAINER_BUG_CATCHER_ELIJAH] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("ELIJAH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherElijah),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherElijah),
        .party = sTrainerMons_BugCatcherElijah
    },
    [TRAINER_BUG_CATCHER_2] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcher2),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcher2),
        .party = sTrainerMons_BugCatcher2
    },
    [TRAINER_BUG_CATCHER_BRENT] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("BRENT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherBrent),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherBrent),
        .party = sTrainerMons_BugCatcherBrent
    },
    [TRAINER_BUG_CATCHER_CONNER] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("CONNER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherConner),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherConner),
        .party = sTrainerMons_BugCatcherConner
    },
    [TRAINER_LASS_JANICE] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("JANICE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassJanice),
        .initialPartysize = NELEMS(sTrainerMons_LassJanice),
        .party = sTrainerMons_LassJanice
    },//vsonic
    [TRAINER_LASS_SALLY] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("SALLY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassSally),
        .initialPartysize = NELEMS(sTrainerMons_LassSally),
        .party = sTrainerMons_LassSally
    },
    [TRAINER_LASS_ROBIN] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("ROBIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassRobin),
        .initialPartysize = NELEMS(sTrainerMons_LassRobin),
        .party = sTrainerMons_LassRobin
    },
    [TRAINER_LASS_CRISSY] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("CRISSY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassCrissy),
        .initialPartysize = NELEMS(sTrainerMons_LassCrissy),
        .party = sTrainerMons_LassCrissy
    },
    [TRAINER_LASS_MIRIAM] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("MIRIAM"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassMiriam),
        .initialPartysize = NELEMS(sTrainerMons_LassMiriam),
        .party = sTrainerMons_LassMiriam
    },
    [TRAINER_LASS_IRIS] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("IRIS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassIris),
        .initialPartysize = NELEMS(sTrainerMons_LassIris),
        .party = sTrainerMons_LassIris
    },
    [TRAINER_LASS_RELI] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("RELI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassReli),
        .initialPartysize = NELEMS(sTrainerMons_LassReli),
        .party = sTrainerMons_LassReli
    },
    [TRAINER_LASS_ALI] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("ALI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassAli),
        .initialPartysize = NELEMS(sTrainerMons_LassAli),
        .party = sTrainerMons_LassAli
    },
    [TRAINER_LASS_2] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Lass2),
        .initialPartysize = NELEMS(sTrainerMons_Lass2),
        .party = sTrainerMons_Lass2
    },
    [TRAINER_LASS_HALEY] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("HALEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassHaley),
        .initialPartysize = NELEMS(sTrainerMons_LassHaley),
        .party = sTrainerMons_LassHaley
    },
    [TRAINER_LASS_ANN] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("ANN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassAnn),
        .initialPartysize = NELEMS(sTrainerMons_LassAnn),
        .party = sTrainerMons_LassAnn
    },
    [TRAINER_LASS_DAWN] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("DAWN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassDawn),
        .initialPartysize = NELEMS(sTrainerMons_LassDawn),
        .party = sTrainerMons_LassDawn
    },
    [TRAINER_LASS_PAIGE] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("PAIGE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassPaige),
        .initialPartysize = NELEMS(sTrainerMons_LassPaige),
        .party = sTrainerMons_LassPaige
    },
    [TRAINER_LASS_ANDREA] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("ANDREA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassAndrea),
        .initialPartysize = NELEMS(sTrainerMons_LassAndrea),
        .party = sTrainerMons_LassAndrea
    },
    [TRAINER_LASS_MEGAN] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("MEGAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassMegan),
        .initialPartysize = NELEMS(sTrainerMons_LassMegan),
        .party = sTrainerMons_LassMegan
    },
    [TRAINER_LASS_JULIA] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("JULIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassJulia),
        .initialPartysize = NELEMS(sTrainerMons_LassJulia),
        .party = sTrainerMons_LassJulia
    },
    [TRAINER_LASS_KAY] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("KAY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassKay),
        .initialPartysize = NELEMS(sTrainerMons_LassKay),
        .party = sTrainerMons_LassKay
    },
    [TRAINER_LASS_LISA] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("LISA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassLisa),
        .initialPartysize = NELEMS(sTrainerMons_LassLisa),
        .party = sTrainerMons_LassLisa
    },
    [TRAINER_SAILOR_EDMOND] = {
        
        .trainerClass = CLASS_SAILOR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("EDMOND"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SailorEdmond),
        .initialPartysize = NELEMS(sTrainerMons_SailorEdmond),
        .party = sTrainerMons_SailorEdmond
    },
    [TRAINER_SAILOR_TREVOR] = {
        
        .trainerClass = CLASS_SAILOR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("TREVOR"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SailorTrevor),
        .initialPartysize = NELEMS(sTrainerMons_SailorTrevor),
        .party = sTrainerMons_SailorTrevor
    },
    [TRAINER_SAILOR_LEONARD] = {
        
        .trainerClass = CLASS_SAILOR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("LEONARD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SailorLeonard),
        .initialPartysize = NELEMS(sTrainerMons_SailorLeonard),
        .party = sTrainerMons_SailorLeonard
    },
    [TRAINER_SAILOR_DUNCAN] = {
        
        .trainerClass = CLASS_SAILOR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("DUNCAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SailorDuncan),
        .initialPartysize = NELEMS(sTrainerMons_SailorDuncan),
        .party = sTrainerMons_SailorDuncan
    },
    [TRAINER_SAILOR_HUEY] = {
        
        .trainerClass = CLASS_SAILOR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("HUEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SailorHuey),
        .initialPartysize = NELEMS(sTrainerMons_SailorHuey),
        .party = sTrainerMons_SailorHuey
    },
    [TRAINER_SAILOR_DYLAN] = {
        
        .trainerClass = CLASS_SAILOR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("DYLAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SailorDylan),
        .initialPartysize = NELEMS(sTrainerMons_SailorDylan),
        .party = sTrainerMons_SailorDylan
    },
    [TRAINER_SAILOR_PHILLIP] = {
        
        .trainerClass = CLASS_SAILOR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("PHILLIP"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SailorPhillip),
        .initialPartysize = NELEMS(sTrainerMons_SailorPhillip),
        .party = sTrainerMons_SailorPhillip
    },
    [TRAINER_SAILOR_DWAYNE] = {
        
        .trainerClass = CLASS_SAILOR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("DWAYNE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SailorDwayne),
        .initialPartysize = NELEMS(sTrainerMons_SailorDwayne),
        .party = sTrainerMons_SailorDwayne
    },
    [TRAINER_CAMPER_LIAM] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("LIAM"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperLiam),
        .initialPartysize = NELEMS(sTrainerMons_CamperLiam),
        .party = sTrainerMons_CamperLiam
    },
    [TRAINER_CAMPER_SHANE] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("SHANE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperShane),
        .initialPartysize = NELEMS(sTrainerMons_CamperShane),
        .party = sTrainerMons_CamperShane
    },
    [TRAINER_CAMPER_ETHAN] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("ETHAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperEthan),
        .initialPartysize = NELEMS(sTrainerMons_CamperEthan),
        .party = sTrainerMons_CamperEthan
    },
    [TRAINER_CAMPER_RICKY] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("RICKY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperRicky),
        .initialPartysize = NELEMS(sTrainerMons_CamperRicky),
        .party = sTrainerMons_CamperRicky
    },
    [TRAINER_CAMPER_JEFF] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("JEFF"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperJeff),
        .initialPartysize = NELEMS(sTrainerMons_CamperJeff),
        .party = sTrainerMons_CamperJeff
    },
    [TRAINER_CAMPER_2] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Camper2),
        .initialPartysize = NELEMS(sTrainerMons_Camper2),
        .party = sTrainerMons_Camper2
    },
    [TRAINER_CAMPER_CHRIS] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("CHRIS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperChris),
        .initialPartysize = NELEMS(sTrainerMons_CamperChris),
        .party = sTrainerMons_CamperChris
    },
    [TRAINER_CAMPER_DREW] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("DREW"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperDrew),
        .initialPartysize = NELEMS(sTrainerMons_CamperDrew),
        .party = sTrainerMons_CamperDrew
    },
    [TRAINER_PICNICKER_DIANA] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("DIANA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerDiana),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerDiana),
        .party = sTrainerMons_PicnickerDiana
    },
    [TRAINER_PICNICKER_NANCY] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("NANCY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerNancy),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerNancy),
        .party = sTrainerMons_PicnickerNancy
    },
    [TRAINER_PICNICKER_ISABELLE] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ISABELLE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerIsabelle),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerIsabelle),
        .party = sTrainerMons_PicnickerIsabelle
    },
    [TRAINER_PICNICKER_KELSEY] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("KELSEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerKelsey),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerKelsey),
        .party = sTrainerMons_PicnickerKelsey
    },
    [TRAINER_PICNICKER_ALICIA] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ALICIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerAlicia),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerAlicia),
        .party = sTrainerMons_PicnickerAlicia
    },
    [TRAINER_PICNICKER_CAITLIN] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("CAITLIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerCaitlin),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerCaitlin),
        .party = sTrainerMons_PicnickerCaitlin
    },
    [TRAINER_PICNICKER_HEIDI] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("HEIDI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerHeidi),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerHeidi),
        .party = sTrainerMons_PicnickerHeidi
    },
    [TRAINER_PICNICKER_CAROL] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("CAROL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerCarol),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerCarol),
        .party = sTrainerMons_PicnickerCarol
    },
    [TRAINER_PICNICKER_SOFIA] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("SOFIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerSofia),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerSofia),
        .party = sTrainerMons_PicnickerSofia
    },
    [TRAINER_PICNICKER_MARTHA] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("MARTHA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerMartha),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerMartha),
        .party = sTrainerMons_PicnickerMartha
    },
    [TRAINER_PICNICKER_TINA] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("TINA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerTina),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerTina),
        .party = sTrainerMons_PicnickerTina
    },
    [TRAINER_PICNICKER_HANNAH] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("HANNAH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerHannah),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerHannah),
        .party = sTrainerMons_PicnickerHannah
    },
    [TRAINER_POKEMANIAC_MARK] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("MARK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacMark),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacMark),
        .party = sTrainerMons_PokemaniacMark
    },
    [TRAINER_POKEMANIAC_HERMAN] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("HERMAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacHerman),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacHerman),
        .party = sTrainerMons_PokemaniacHerman
    },
    [TRAINER_POKEMANIAC_COOPER] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("COOPER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacCooper),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacCooper),
        .party = sTrainerMons_PokemaniacCooper
    },
    [TRAINER_POKEMANIAC_STEVE] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("STEVE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacSteve),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacSteve),
        .party = sTrainerMons_PokemaniacSteve
    },
    [TRAINER_POKEMANIAC_WINSTON] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("WINSTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacWinston),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacWinston),
        .party = sTrainerMons_PokemaniacWinston
    },
    [TRAINER_POKEMANIAC_DAWSON] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("DAWSON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacDawson),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacDawson),
        .party = sTrainerMons_PokemaniacDawson
    },
    [TRAINER_POKEMANIAC_ASHTON] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("ASHTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacAshton),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacAshton),
        .party = sTrainerMons_PokemaniacAshton
    },
    [TRAINER_SUPER_NERD_JOVAN] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("JOVAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerdJovan),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerdJovan),
        .party = sTrainerMons_SuperNerdJovan
    },
    [TRAINER_SUPER_NERD_MIGUEL] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("MIGUEL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerdMiguel),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerdMiguel),
        .party = sTrainerMons_SuperNerdMiguel
    },
    [TRAINER_SUPER_NERD_AIDAN] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("AIDAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerdAidan),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerdAidan),
        .party = sTrainerMons_SuperNerdAidan
    },
    [TRAINER_SUPER_NERD_GLENN] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("GLENN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerdGlenn),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerdGlenn),
        .party = sTrainerMons_SuperNerdGlenn
    },
    [TRAINER_SUPER_NERD_LESLIE] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("LESLIE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerdLeslie),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerdLeslie),
        .party = sTrainerMons_SuperNerdLeslie
    },
    [TRAINER_SUPER_NERD_1] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerd1),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerd1),
        .party = sTrainerMons_SuperNerd1
    },
    [TRAINER_SUPER_NERD_2] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerd2),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerd2),
        .party = sTrainerMons_SuperNerd2
    },
    [TRAINER_SUPER_NERD_3] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerd3),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerd3),
        .party = sTrainerMons_SuperNerd3
    },
    [TRAINER_SUPER_NERD_ERIK] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("ERIK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerdErik),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerdErik),
        .party = sTrainerMons_SuperNerdErik
    },
    [TRAINER_SUPER_NERD_AVERY] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("AVERY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerdAvery),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerdAvery),
        .party = sTrainerMons_SuperNerdAvery
    },
    [TRAINER_SUPER_NERD_DEREK] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("DEREK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerdDerek),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerdDerek),
        .party = sTrainerMons_SuperNerdDerek
    },
    [TRAINER_SUPER_NERD_ZAC] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("ZAC"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerdZac),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerdZac),
        .party = sTrainerMons_SuperNerdZac
    },
    [TRAINER_HIKER_MARCOS] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("MARCOS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerMarcos),
        .initialPartysize = NELEMS(sTrainerMons_HikerMarcos),
        .party = sTrainerMons_HikerMarcos
    },
    [TRAINER_HIKER_FRANKLIN] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("FRANKLIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerFranklin),
        .initialPartysize = NELEMS(sTrainerMons_HikerFranklin),
        .party = sTrainerMons_HikerFranklin
    },
    [TRAINER_HIKER_NOB] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("NOB"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerNob),
        .initialPartysize = NELEMS(sTrainerMons_HikerNob),
        .party = sTrainerMons_HikerNob
    },
    [TRAINER_HIKER_WAYNE] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("WAYNE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerWayne),
        .initialPartysize = NELEMS(sTrainerMons_HikerWayne),
        .party = sTrainerMons_HikerWayne
    },
    [TRAINER_HIKER_ALAN] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("ALAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerAlan),
        .initialPartysize = NELEMS(sTrainerMons_HikerAlan),
        .party = sTrainerMons_HikerAlan
    },
    [TRAINER_HIKER_BRICE] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("BRICE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerBrice),
        .initialPartysize = NELEMS(sTrainerMons_HikerBrice),
        .party = sTrainerMons_HikerBrice
    },
    [TRAINER_HIKER_CLARK] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("CLARK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerClark),
        .initialPartysize = NELEMS(sTrainerMons_HikerClark),
        .party = sTrainerMons_HikerClark
    },
    [TRAINER_HIKER_TRENT] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("TRENT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerTrent),
        .initialPartysize = NELEMS(sTrainerMons_HikerTrent),
        .party = sTrainerMons_HikerTrent
    },
    [TRAINER_HIKER_DUDLEY] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("DUDLEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerDudley),
        .initialPartysize = NELEMS(sTrainerMons_HikerDudley),
        .party = sTrainerMons_HikerDudley
    },
    [TRAINER_HIKER_ALLEN] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("ALLEN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerAllen),
        .initialPartysize = NELEMS(sTrainerMons_HikerAllen),
        .party = sTrainerMons_HikerAllen
    },
    [TRAINER_HIKER_ERIC] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("ERIC"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerEric),
        .initialPartysize = NELEMS(sTrainerMons_HikerEric),
        .party = sTrainerMons_HikerEric
    },
    [TRAINER_HIKER_LENNY] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("LENNY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerLenny),
        .initialPartysize = NELEMS(sTrainerMons_HikerLenny),
        .party = sTrainerMons_HikerLenny
    },
    [TRAINER_HIKER_OLIVER] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("OLIVER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerOliver),
        .initialPartysize = NELEMS(sTrainerMons_HikerOliver),
        .party = sTrainerMons_HikerOliver
    },
    [TRAINER_HIKER_LUCAS] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("LUCAS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerLucas),
        .initialPartysize = NELEMS(sTrainerMons_HikerLucas),
        .party = sTrainerMons_HikerLucas
    },
    [TRAINER_BIKER_JARED] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("JARED"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerJared),
        .initialPartysize = NELEMS(sTrainerMons_BikerJared),
        .party = sTrainerMons_BikerJared
    },
    [TRAINER_BIKER_MALIK] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("MALIK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerMalik),
        .initialPartysize = NELEMS(sTrainerMons_BikerMalik),
        .party = sTrainerMons_BikerMalik
    },
    [TRAINER_BIKER_ERNEST] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("ERNEST"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerErnest),
        .initialPartysize = NELEMS(sTrainerMons_BikerErnest),
        .party = sTrainerMons_BikerErnest
    },
    [TRAINER_BIKER_ALEX] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("ALEX"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerAlex),
        .initialPartysize = NELEMS(sTrainerMons_BikerAlex),
        .party = sTrainerMons_BikerAlex
    },
    [TRAINER_BIKER_LAO] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("LAO"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerLao),
        .initialPartysize = NELEMS(sTrainerMons_BikerLao),
        .party = sTrainerMons_BikerLao
    },
    [TRAINER_BIKER_1] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Biker1),
        .initialPartysize = NELEMS(sTrainerMons_Biker1),
        .party = sTrainerMons_Biker1
    },
    [TRAINER_BIKER_HIDEO] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("HIDEO"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerHideo),
        .initialPartysize = NELEMS(sTrainerMons_BikerHideo),
        .party = sTrainerMons_BikerHideo
    },
    [TRAINER_BIKER_RUBEN] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("RUBEN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerRuben),
        .initialPartysize = NELEMS(sTrainerMons_BikerRuben),
        .party = sTrainerMons_BikerRuben
    },
    [TRAINER_BIKER_BILLY] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("BILLY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerBilly),
        .initialPartysize = NELEMS(sTrainerMons_BikerBilly),
        .party = sTrainerMons_BikerBilly
    },
    [TRAINER_BIKER_NIKOLAS] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("NIKOLAS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerNikolas),
        .initialPartysize = NELEMS(sTrainerMons_BikerNikolas),
        .party = sTrainerMons_BikerNikolas
    },
    [TRAINER_BIKER_JAXON] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("JAXON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerJaxon),
        .initialPartysize = NELEMS(sTrainerMons_BikerJaxon),
        .party = sTrainerMons_BikerJaxon
    },
    [TRAINER_BIKER_WILLIAM] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("WILLIAM"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerWilliam),
        .initialPartysize = NELEMS(sTrainerMons_BikerWilliam),
        .party = sTrainerMons_BikerWilliam
    },
    [TRAINER_BIKER_LUKAS] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("LUKAS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerLukas),
        .initialPartysize = NELEMS(sTrainerMons_BikerLukas),
        .party = sTrainerMons_BikerLukas
    },
    [TRAINER_BIKER_ISAAC] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("ISAAC"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerIsaac),
        .initialPartysize = NELEMS(sTrainerMons_BikerIsaac),
        .party = sTrainerMons_BikerIsaac
    },
    [TRAINER_BIKER_GERALD] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("GERALD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerGerald),
        .initialPartysize = NELEMS(sTrainerMons_BikerGerald),
        .party = sTrainerMons_BikerGerald
    },
    [TRAINER_BURGLAR_1] = {
        
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Burglar1),
        .initialPartysize = NELEMS(sTrainerMons_Burglar1),
        .party = sTrainerMons_Burglar1
    },
    [TRAINER_BURGLAR_2] = {
        
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Burglar2),
        .initialPartysize = NELEMS(sTrainerMons_Burglar2),
        .party = sTrainerMons_Burglar2
    },
    [TRAINER_BURGLAR_3] = {
        
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Burglar3),
        .initialPartysize = NELEMS(sTrainerMons_Burglar3),
        .party = sTrainerMons_Burglar3
    },
    [TRAINER_BURGLAR_QUINN] = {
        
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _("QUINN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BurglarQuinn),
        .initialPartysize = NELEMS(sTrainerMons_BurglarQuinn),
        .party = sTrainerMons_BurglarQuinn
    },
    [TRAINER_BURGLAR_RAMON] = {
        
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _("RAMON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BurglarRamon),
        .initialPartysize = NELEMS(sTrainerMons_BurglarRamon),
        .party = sTrainerMons_BurglarRamon
    },
    [TRAINER_BURGLAR_DUSTY] = {
        
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _("DUSTY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BurglarDusty),
        .initialPartysize = NELEMS(sTrainerMons_BurglarDusty),
        .party = sTrainerMons_BurglarDusty
    },
    [TRAINER_BURGLAR_ARNIE] = {
        
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _("ARNIE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BurglarArnie),
        .initialPartysize = NELEMS(sTrainerMons_BurglarArnie),
        .party = sTrainerMons_BurglarArnie
    },
    [TRAINER_BURGLAR_4] = {
        
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Burglar4),
        .initialPartysize = NELEMS(sTrainerMons_Burglar4),
        .party = sTrainerMons_Burglar4
    },
    [TRAINER_BURGLAR_SIMON] = {
        
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _("SIMON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BurglarSimon),
        .initialPartysize = NELEMS(sTrainerMons_BurglarSimon),
        .party = sTrainerMons_BurglarSimon
    },
    [TRAINER_BURGLAR_LEWIS] = {
        
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _("LEWIS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BurglarLewis),
        .initialPartysize = NELEMS(sTrainerMons_BurglarLewis),
        .party = sTrainerMons_BurglarLewis
    },
    [TRAINER_ENGINEER_BAILY] = {
        
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ENGINEER,
        .trainerName = _("BAILY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_EngineerBaily),
        .initialPartysize = NELEMS(sTrainerMons_EngineerBaily),
        .party = sTrainerMons_EngineerBaily
    },
    [TRAINER_ENGINEER_BRAXTON] = {
        
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ENGINEER,
        .trainerName = _("BRAXTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_EngineerBraxton),
        .initialPartysize = NELEMS(sTrainerMons_EngineerBraxton),
        .party = sTrainerMons_EngineerBraxton
    },
    [TRAINER_ENGINEER_BERNIE] = {
        
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ENGINEER,
        .trainerName = _("BERNIE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_EngineerBernie),
        .initialPartysize = NELEMS(sTrainerMons_EngineerBernie),
        .party = sTrainerMons_EngineerBernie
    },
    [TRAINER_FISHERMAN_DALE] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("DALE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanDale),
        .initialPartysize = NELEMS(sTrainerMons_FishermanDale),
        .party = sTrainerMons_FishermanDale
    },
    [TRAINER_FISHERMAN_BARNY] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("BARNY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanBarny),
        .initialPartysize = NELEMS(sTrainerMons_FishermanBarny),
        .party = sTrainerMons_FishermanBarny
    },
    [TRAINER_FISHERMAN_NED] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("NED"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanNed),
        .initialPartysize = NELEMS(sTrainerMons_FishermanNed),
        .party = sTrainerMons_FishermanNed
    },
    [TRAINER_FISHERMAN_CHIP] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("CHIP"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanChip),
        .initialPartysize = NELEMS(sTrainerMons_FishermanChip),
        .party = sTrainerMons_FishermanChip
    },
    [TRAINER_FISHERMAN_HANK] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("HANK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanHank),
        .initialPartysize = NELEMS(sTrainerMons_FishermanHank),
        .party = sTrainerMons_FishermanHank
    },
    [TRAINER_FISHERMAN_ELLIOT] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("ELLIOT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanElliot),
        .initialPartysize = NELEMS(sTrainerMons_FishermanElliot),
        .party = sTrainerMons_FishermanElliot
    },
    [TRAINER_FISHERMAN_RONALD] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("RONALD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanRonald),
        .initialPartysize = NELEMS(sTrainerMons_FishermanRonald),
        .party = sTrainerMons_FishermanRonald
    },
    [TRAINER_FISHERMAN_CLAUDE] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("CLAUDE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanClaude),
        .initialPartysize = NELEMS(sTrainerMons_FishermanClaude),
        .party = sTrainerMons_FishermanClaude
    },
    [TRAINER_FISHERMAN_WADE] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("WADE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanWade),
        .initialPartysize = NELEMS(sTrainerMons_FishermanWade),
        .party = sTrainerMons_FishermanWade
    },
    [TRAINER_FISHERMAN_NOLAN] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("NOLAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanNolan),
        .initialPartysize = NELEMS(sTrainerMons_FishermanNolan),
        .party = sTrainerMons_FishermanNolan
    },
    [TRAINER_FISHERMAN_ANDREW] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("ANDREW"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanAndrew),
        .initialPartysize = NELEMS(sTrainerMons_FishermanAndrew),
        .party = sTrainerMons_FishermanAndrew
    },
    [TRAINER_SWIMMER_MALE_LUIS] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("LUIS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleLuis),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleLuis),
        .party = sTrainerMons_SwimmerMaleLuis
    },
    [TRAINER_SWIMMER_MALE_RICHARD] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("RICHARD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleRichard),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleRichard),
        .party = sTrainerMons_SwimmerMaleRichard
    },
    [TRAINER_SWIMMER_MALE_REECE] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("REECE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleReece),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleReece),
        .party = sTrainerMons_SwimmerMaleReece
    },
    [TRAINER_SWIMMER_MALE_MATTHEW] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("MATTHEW"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleMatthew),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleMatthew),
        .party = sTrainerMons_SwimmerMaleMatthew
    },
    [TRAINER_SWIMMER_MALE_DOUGLAS] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("DOUGLAS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleDouglas),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleDouglas),
        .party = sTrainerMons_SwimmerMaleDouglas
    },
    [TRAINER_SWIMMER_MALE_DAVID] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("DAVID"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleDavid),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleDavid),
        .party = sTrainerMons_SwimmerMaleDavid
    },
    [TRAINER_SWIMMER_MALE_TONY] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("TONY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleTony),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleTony),
        .party = sTrainerMons_SwimmerMaleTony
    },
    [TRAINER_SWIMMER_MALE_AXLE] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("AXLE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleAxle),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleAxle),
        .party = sTrainerMons_SwimmerMaleAxle
    },
    [TRAINER_SWIMMER_MALE_BARRY] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("BARRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleBarry),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleBarry),
        .party = sTrainerMons_SwimmerMaleBarry
    },
    [TRAINER_SWIMMER_MALE_DEAN] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("DEAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleDean),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleDean),
        .party = sTrainerMons_SwimmerMaleDean
    },
    [TRAINER_SWIMMER_MALE_DARRIN] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("DARRIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleDarrin),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleDarrin),
        .party = sTrainerMons_SwimmerMaleDarrin
    },
    [TRAINER_SWIMMER_MALE_SPENCER] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("SPENCER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleSpencer),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleSpencer),
        .party = sTrainerMons_SwimmerMaleSpencer
    },
    [TRAINER_SWIMMER_MALE_JACK] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("JACK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleJack),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleJack),
        .party = sTrainerMons_SwimmerMaleJack
    },
    [TRAINER_SWIMMER_MALE_JEROME] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("JEROME"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleJerome),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleJerome),
        .party = sTrainerMons_SwimmerMaleJerome
    },
    [TRAINER_SWIMMER_MALE_ROLAND] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("ROLAND"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleRoland),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleRoland),
        .party = sTrainerMons_SwimmerMaleRoland
    },
    [TRAINER_CUE_BALL_KOJI] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("KOJI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallKoji),
        .initialPartysize = NELEMS(sTrainerMons_CueBallKoji),
        .party = sTrainerMons_CueBallKoji
    },
    [TRAINER_CUE_BALL_LUKE] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("LUKE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallLuke),
        .initialPartysize = NELEMS(sTrainerMons_CueBallLuke),
        .party = sTrainerMons_CueBallLuke
    },
    [TRAINER_CUE_BALL_CAMRON] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("CAMRON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallCamron),
        .initialPartysize = NELEMS(sTrainerMons_CueBallCamron),
        .party = sTrainerMons_CueBallCamron
    },
    [TRAINER_CUE_BALL_RAUL] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("RAUL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallRaul),
        .initialPartysize = NELEMS(sTrainerMons_CueBallRaul),
        .party = sTrainerMons_CueBallRaul
    },
    [TRAINER_CUE_BALL_ISAIAH] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("ISAIAH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallIsaiah),
        .initialPartysize = NELEMS(sTrainerMons_CueBallIsaiah),
        .party = sTrainerMons_CueBallIsaiah
    },
    [TRAINER_CUE_BALL_ZEEK] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("ZEEK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallZeek),
        .initialPartysize = NELEMS(sTrainerMons_CueBallZeek),
        .party = sTrainerMons_CueBallZeek
    },
    [TRAINER_CUE_BALL_JAMAL] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("JAMAL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallJamal),
        .initialPartysize = NELEMS(sTrainerMons_CueBallJamal),
        .party = sTrainerMons_CueBallJamal
    },
    [TRAINER_CUE_BALL_COREY] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("COREY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallCorey),
        .initialPartysize = NELEMS(sTrainerMons_CueBallCorey),
        .party = sTrainerMons_CueBallCorey
    },
    [TRAINER_CUE_BALL_CHASE] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("CHASE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallChase),
        .initialPartysize = NELEMS(sTrainerMons_CueBallChase),
        .party = sTrainerMons_CueBallChase
    },
    [TRAINER_GAMBLER_HUGO] = {
        
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = _("HUGO"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GamblerHugo),
        .initialPartysize = NELEMS(sTrainerMons_GamblerHugo),
        .party = sTrainerMons_GamblerHugo
    },
    [TRAINER_GAMBLER_JASPER] = {
        
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = _("JASPER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GamblerJasper),
        .initialPartysize = NELEMS(sTrainerMons_GamblerJasper),
        .party = sTrainerMons_GamblerJasper
    },
    [TRAINER_GAMBLER_DIRK] = {
        
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = _("DIRK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GamblerDirk),
        .initialPartysize = NELEMS(sTrainerMons_GamblerDirk),
        .party = sTrainerMons_GamblerDirk
    },
    [TRAINER_GAMBLER_DARIAN] = {
        
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = _("DARIAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GamblerDarian),
        .initialPartysize = NELEMS(sTrainerMons_GamblerDarian),
        .party = sTrainerMons_GamblerDarian
    },
    [TRAINER_GAMBLER_STAN] = {
        
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = _("STAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GamblerStan),
        .initialPartysize = NELEMS(sTrainerMons_GamblerStan),
        .party = sTrainerMons_GamblerStan
    },
    [TRAINER_GAMBLER_1] = {
        
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Gambler1),
        .initialPartysize = NELEMS(sTrainerMons_Gambler1),
        .party = sTrainerMons_Gambler1
    },
    [TRAINER_GAMBLER_RICH] = {
        
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = _("RICH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GamblerRich),
        .initialPartysize = NELEMS(sTrainerMons_GamblerRich),
        .party = sTrainerMons_GamblerRich
    },
    [TRAINER_BEAUTY_BRIDGET] = {
        
        .trainerClass = CLASS_BEAUTY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("BRIDGET"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BeautyBridget),
        .initialPartysize = NELEMS(sTrainerMons_BeautyBridget),
        .party = sTrainerMons_BeautyBridget
    },
    [TRAINER_BEAUTY_TAMIA] = {
        
        .trainerClass = CLASS_BEAUTY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("TAMIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BeautyTamia),
        .initialPartysize = NELEMS(sTrainerMons_BeautyTamia),
        .party = sTrainerMons_BeautyTamia
    },
    [TRAINER_BEAUTY_LORI] = {
        
        .trainerClass = CLASS_BEAUTY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("LORI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BeautyLori),
        .initialPartysize = NELEMS(sTrainerMons_BeautyLori),
        .party = sTrainerMons_BeautyLori
    },
    [TRAINER_BEAUTY_LOLA] = {
        
        .trainerClass = CLASS_BEAUTY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("LOLA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BeautyLola),
        .initialPartysize = NELEMS(sTrainerMons_BeautyLola),
        .party = sTrainerMons_BeautyLola
    },
    [TRAINER_BEAUTY_SHEILA] = {
        
        .trainerClass = CLASS_BEAUTY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("SHEILA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BeautySheila),
        .initialPartysize = NELEMS(sTrainerMons_BeautySheila),
        .party = sTrainerMons_BeautySheila
    },
    [TRAINER_SWIMMER_FEMALE_TIFFANY] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("TIFFANY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleTiffany),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleTiffany),
        .party = sTrainerMons_SwimmerFemaleTiffany
    },
    [TRAINER_SWIMMER_FEMALE_NORA] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("NORA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleNora),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleNora),
        .party = sTrainerMons_SwimmerFemaleNora
    },
    [TRAINER_SWIMMER_FEMALE_MELISSA] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("MELISSA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleMelissa),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleMelissa),
        .party = sTrainerMons_SwimmerFemaleMelissa
    },
    [TRAINER_BEAUTY_GRACE] = {
        
        .trainerClass = CLASS_BEAUTY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("GRACE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BeautyGrace),
        .initialPartysize = NELEMS(sTrainerMons_BeautyGrace),
        .party = sTrainerMons_BeautyGrace
    },
    [TRAINER_BEAUTY_OLIVIA] = {
        
        .trainerClass = CLASS_BEAUTY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("OLIVIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BeautyOlivia),
        .initialPartysize = NELEMS(sTrainerMons_BeautyOlivia),
        .party = sTrainerMons_BeautyOlivia
    },
    [TRAINER_BEAUTY_LAUREN] = {
        
        .trainerClass = CLASS_BEAUTY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("LAUREN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BeautyLauren),
        .initialPartysize = NELEMS(sTrainerMons_BeautyLauren),
        .party = sTrainerMons_BeautyLauren
    },
    [TRAINER_SWIMMER_FEMALE_ANYA] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("ANYA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleAnya),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleAnya),
        .party = sTrainerMons_SwimmerFemaleAnya
    },
    [TRAINER_SWIMMER_FEMALE_ALICE] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("ALICE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleAlice),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleAlice),
        .party = sTrainerMons_SwimmerFemaleAlice
    },
    [TRAINER_SWIMMER_FEMALE_CONNIE] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("CONNIE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleConnie),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleConnie),
        .party = sTrainerMons_SwimmerFemaleConnie
    },
    [TRAINER_SWIMMER_FEMALE_SHIRLEY] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("SHIRLEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleShirley),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleShirley),
        .party = sTrainerMons_SwimmerFemaleShirley
    },
    [TRAINER_PSYCHIC_JOHAN] = {
        
        .trainerClass = CLASS_PSYCHIC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = _("JOHAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PsychicJohan),
        .initialPartysize = NELEMS(sTrainerMons_PsychicJohan),
        .party = sTrainerMons_PsychicJohan
    },
    [TRAINER_PSYCHIC_TYRON] = {
        
        .trainerClass = CLASS_PSYCHIC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = _("TYRON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PsychicTyron),
        .initialPartysize = NELEMS(sTrainerMons_PsychicTyron),
        .party = sTrainerMons_PsychicTyron
    },
    [TRAINER_PSYCHIC_CAMERON] = {
        
        .trainerClass = CLASS_PSYCHIC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = _("CAMERON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PsychicCameron),
        .initialPartysize = NELEMS(sTrainerMons_PsychicCameron),
        .party = sTrainerMons_PsychicCameron
    },
    [TRAINER_PSYCHIC_PRESTON] = {
        
        .trainerClass = CLASS_PSYCHIC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = _("PRESTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PsychicPreston),
        .initialPartysize = NELEMS(sTrainerMons_PsychicPreston),
        .party = sTrainerMons_PsychicPreston
    },
    [TRAINER_ROCKER_RANDALL] = {
        
        .trainerClass = CLASS_ROCKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKER,
        .trainerName = _("RANDALL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RockerRandall),
        .initialPartysize = NELEMS(sTrainerMons_RockerRandall),
        .party = sTrainerMons_RockerRandall
    },
    [TRAINER_ROCKER_LUCA] = {
        
        .trainerClass = CLASS_ROCKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKER,
        .trainerName = _("LUCA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RockerLuca),
        .initialPartysize = NELEMS(sTrainerMons_RockerLuca),
        .party = sTrainerMons_RockerLuca
    },
    [TRAINER_JUGGLER_DALTON] = {
        
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("DALTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_JugglerDalton),
        .initialPartysize = NELEMS(sTrainerMons_JugglerDalton),
        .party = sTrainerMons_JugglerDalton
    },
    [TRAINER_JUGGLER_NELSON] = {
        
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("NELSON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_JugglerNelson),
        .initialPartysize = NELEMS(sTrainerMons_JugglerNelson),
        .party = sTrainerMons_JugglerNelson
    },
    [TRAINER_JUGGLER_KIRK] = {
        
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("KIRK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_JugglerKirk),
        .initialPartysize = NELEMS(sTrainerMons_JugglerKirk),
        .party = sTrainerMons_JugglerKirk
    },
    [TRAINER_JUGGLER_SHAWN] = {
        
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("SHAWN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_JugglerShawn),
        .initialPartysize = NELEMS(sTrainerMons_JugglerShawn),
        .party = sTrainerMons_JugglerShawn
    },
    [TRAINER_JUGGLER_GREGORY] = {
        
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("GREGORY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_JugglerGregory),
        .initialPartysize = NELEMS(sTrainerMons_JugglerGregory),
        .party = sTrainerMons_JugglerGregory
    },
    [TRAINER_JUGGLER_EDWARD] = {
        
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("EDWARD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_JugglerEdward),
        .initialPartysize = NELEMS(sTrainerMons_JugglerEdward),
        .party = sTrainerMons_JugglerEdward
    },
    [TRAINER_JUGGLER_KAYDEN] = {
        
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("KAYDEN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_JugglerKayden),
        .initialPartysize = NELEMS(sTrainerMons_JugglerKayden),
        .party = sTrainerMons_JugglerKayden
    },
    [TRAINER_JUGGLER_NATE] = {
        
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("NATE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_JugglerNate),
        .initialPartysize = NELEMS(sTrainerMons_JugglerNate),
        .party = sTrainerMons_JugglerNate
    },
    [TRAINER_TAMER_PHIL] = {
        
        .trainerClass = CLASS_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("PHIL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TamerPhil),
        .initialPartysize = NELEMS(sTrainerMons_TamerPhil),
        .party = sTrainerMons_TamerPhil
    },
    [TRAINER_TAMER_EDGAR] = {
        
        .trainerClass = CLASS_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("EDGAR"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TamerEdgar),
        .initialPartysize = NELEMS(sTrainerMons_TamerEdgar),
        .party = sTrainerMons_TamerEdgar
    },
    [TRAINER_TAMER_JASON] = {
        
        .trainerClass = CLASS_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("JASON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TamerJason),
        .initialPartysize = NELEMS(sTrainerMons_TamerJason),
        .party = sTrainerMons_TamerJason
    },
    [TRAINER_TAMER_COLE] = {
        
        .trainerClass = CLASS_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("COLE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TamerCole),
        .initialPartysize = NELEMS(sTrainerMons_TamerCole),
        .party = sTrainerMons_TamerCole
    },
    [TRAINER_TAMER_VINCENT] = {
        
        .trainerClass = CLASS_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("VINCENT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TamerVincent),
        .initialPartysize = NELEMS(sTrainerMons_TamerVincent),
        .party = sTrainerMons_TamerVincent
    },
    [TRAINER_TAMER_JOHN] = {
        
        .trainerClass = CLASS_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("JOHN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TamerJohn),
        .initialPartysize = NELEMS(sTrainerMons_TamerJohn),
        .party = sTrainerMons_TamerJohn
    },
    [TRAINER_BIRD_KEEPER_SEBASTIAN] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("SEBASTIAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperSebastian),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperSebastian),
        .party = sTrainerMons_BirdKeeperSebastian
    },
    [TRAINER_BIRD_KEEPER_PERRY] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("PERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperPerry),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperPerry),
        .party = sTrainerMons_BirdKeeperPerry
    },
    [TRAINER_BIRD_KEEPER_ROBERT] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("ROBERT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperRobert),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperRobert),
        .party = sTrainerMons_BirdKeeperRobert
    },
    [TRAINER_BIRD_KEEPER_DONALD] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("DONALD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperDonald),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperDonald),
        .party = sTrainerMons_BirdKeeperDonald
    },
    [TRAINER_BIRD_KEEPER_BENNY] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("BENNY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperBenny),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperBenny),
        .party = sTrainerMons_BirdKeeperBenny
    },
    [TRAINER_BIRD_KEEPER_EDWIN] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("EDWIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperEdwin),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperEdwin),
        .party = sTrainerMons_BirdKeeperEdwin
    },
    [TRAINER_BIRD_KEEPER_CHESTER] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("CHESTER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperChester),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperChester),
        .party = sTrainerMons_BirdKeeperChester
    },
    [TRAINER_BIRD_KEEPER_WILTON] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("WILTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperWilton),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperWilton),
        .party = sTrainerMons_BirdKeeperWilton
    },
    [TRAINER_BIRD_KEEPER_RAMIRO] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("RAMIRO"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperRamiro),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperRamiro),
        .party = sTrainerMons_BirdKeeperRamiro
    },
    [TRAINER_BIRD_KEEPER_JACOB] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("JACOB"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperJacob),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperJacob),
        .party = sTrainerMons_BirdKeeperJacob
    },
    [TRAINER_BIRD_KEEPER_ROGER] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("ROGER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperRoger),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperRoger),
        .party = sTrainerMons_BirdKeeperRoger
    },
    [TRAINER_BIRD_KEEPER_REED] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("REED"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperReed),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperReed),
        .party = sTrainerMons_BirdKeeperReed
    },
    [TRAINER_BIRD_KEEPER_KEITH] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("KEITH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperKeith),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperKeith),
        .party = sTrainerMons_BirdKeeperKeith
    },
    [TRAINER_BIRD_KEEPER_CARTER] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("CARTER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperCarter),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperCarter),
        .party = sTrainerMons_BirdKeeperCarter
    },
    [TRAINER_BIRD_KEEPER_MITCH] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("MITCH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperMitch),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperMitch),
        .party = sTrainerMons_BirdKeeperMitch
    },
    [TRAINER_BIRD_KEEPER_BECK] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("BECK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperBeck),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperBeck),
        .party = sTrainerMons_BirdKeeperBeck
    },
    [TRAINER_BIRD_KEEPER_MARLON] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("MARLON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperMarlon),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperMarlon),
        .party = sTrainerMons_BirdKeeperMarlon
    },
    [TRAINER_BLACK_BELT_KOICHI] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("KOICHI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltKoichi),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltKoichi),
        .party = sTrainerMons_BlackBeltKoichi
    },
    [TRAINER_BLACK_BELT_MIKE] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("MIKE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltMike),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltMike),
        .party = sTrainerMons_BlackBeltMike
    },
    [TRAINER_BLACK_BELT_HIDEKI] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("HIDEKI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltHideki),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltHideki),
        .party = sTrainerMons_BlackBeltHideki
    },
    [TRAINER_BLACK_BELT_AARON] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("AARON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltAaron),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltAaron),
        .party = sTrainerMons_BlackBeltAaron
    },
    [TRAINER_BLACK_BELT_HITOSHI] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("HITOSHI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltHitoshi),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltHitoshi),
        .party = sTrainerMons_BlackBeltHitoshi
    },
    [TRAINER_BLACK_BELT_ATSUSHI] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("ATSUSHI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltAtsushi),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltAtsushi),
        .party = sTrainerMons_BlackBeltAtsushi
    },
    [TRAINER_BLACK_BELT_KIYO] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("KIYO"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltKiyo),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltKiyo),
        .party = sTrainerMons_BlackBeltKiyo
    },
    [TRAINER_BLACK_BELT_TAKASHI] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("TAKASHI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltTakashi),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltTakashi),
        .party = sTrainerMons_BlackBeltTakashi
    },
    [TRAINER_BLACK_BELT_DAISUKE] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("DAISUKE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltDaisuke),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltDaisuke),
        .party = sTrainerMons_BlackBeltDaisuke
    },
    [TRAINER_RIVAL_OAKS_LAB_SQUIRTLE] = {
        
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalOaksLabSquirtle),
        .initialPartysize = NELEMS(sTrainerMons_RivalOaksLabSquirtle),
        .party = sTrainerMons_RivalOaksLabSquirtle
    },
    [TRAINER_RIVAL_OAKS_LAB_BULBASAUR] = {
        
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalOaksLabBulbasaur),
        .initialPartysize = NELEMS(sTrainerMons_RivalOaksLabBulbasaur),
        .party = sTrainerMons_RivalOaksLabBulbasaur
    },
    [TRAINER_RIVAL_OAKS_LAB_CHARMANDER] = {
        
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalOaksLabCharmander),
        .initialPartysize = NELEMS(sTrainerMons_RivalOaksLabCharmander),
        .party = sTrainerMons_RivalOaksLabCharmander
    },
    [TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE] = {
        
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalRoute22EarlySquirtle),
        .initialPartysize = NELEMS(sTrainerMons_RivalRoute22EarlySquirtle),
        .party = sTrainerMons_RivalRoute22EarlySquirtle
    },
    [TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR] = {
        
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalRoute22EarlyBulbasaur),
        .initialPartysize = NELEMS(sTrainerMons_RivalRoute22EarlyBulbasaur),
        .party = sTrainerMons_RivalRoute22EarlyBulbasaur
    },
    [TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER] = {
        
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalRoute22EarlyCharmander),
        .initialPartysize = NELEMS(sTrainerMons_RivalRoute22EarlyCharmander),
        .party = sTrainerMons_RivalRoute22EarlyCharmander
    },
    [TRAINER_RIVAL_CERULEAN_SQUIRTLE] = {
        
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalCeruleanSquirtle),
        .initialPartysize = NELEMS(sTrainerMons_RivalCeruleanSquirtle),
        .party = sTrainerMons_RivalCeruleanSquirtle
    },
    [TRAINER_RIVAL_CERULEAN_BULBASAUR] = {
        
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalCeruleanBulbasaur),
        .initialPartysize = NELEMS(sTrainerMons_RivalCeruleanBulbasaur),
        .party = sTrainerMons_RivalCeruleanBulbasaur
    },
    [TRAINER_RIVAL_CERULEAN_CHARMANDER] = {
        
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalCeruleanCharmander),
        .initialPartysize = NELEMS(sTrainerMons_RivalCeruleanCharmander),
        .party = sTrainerMons_RivalCeruleanCharmander
    },
    [TRAINER_SCIENTIST_TED] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("TED"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistTed),
        .initialPartysize = NELEMS(sTrainerMons_ScientistTed),
        .party = sTrainerMons_ScientistTed
    },
    [TRAINER_SCIENTIST_CONNOR] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("CONNOR"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistConnor),
        .initialPartysize = NELEMS(sTrainerMons_ScientistConnor),
        .party = sTrainerMons_ScientistConnor
    },
    [TRAINER_SCIENTIST_JERRY] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("JERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistJerry),
        .initialPartysize = NELEMS(sTrainerMons_ScientistJerry),
        .party = sTrainerMons_ScientistJerry
    },
    [TRAINER_SCIENTIST_JOSE] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("JOSE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistJose),
        .initialPartysize = NELEMS(sTrainerMons_ScientistJose),
        .party = sTrainerMons_ScientistJose
    },
    [TRAINER_SCIENTIST_RODNEY] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("RODNEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistRodney),
        .initialPartysize = NELEMS(sTrainerMons_ScientistRodney),
        .party = sTrainerMons_ScientistRodney
    },
    [TRAINER_SCIENTIST_BEAU] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("BEAU"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistBeau),
        .initialPartysize = NELEMS(sTrainerMons_ScientistBeau),
        .party = sTrainerMons_ScientistBeau
    },
    [TRAINER_SCIENTIST_TAYLOR] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("TAYLOR"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistTaylor),
        .initialPartysize = NELEMS(sTrainerMons_ScientistTaylor),
        .party = sTrainerMons_ScientistTaylor
    },
    [TRAINER_SCIENTIST_JOSHUA] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("JOSHUA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistJoshua),
        .initialPartysize = NELEMS(sTrainerMons_ScientistJoshua),
        .party = sTrainerMons_ScientistJoshua
    },
    [TRAINER_SCIENTIST_PARKER] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("PARKER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistParker),
        .initialPartysize = NELEMS(sTrainerMons_ScientistParker),
        .party = sTrainerMons_ScientistParker
    },
    [TRAINER_SCIENTIST_ED] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("ED"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistEd),
        .initialPartysize = NELEMS(sTrainerMons_ScientistEd),
        .party = sTrainerMons_ScientistEd
    },
    [TRAINER_SCIENTIST_TRAVIS] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("TRAVIS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistTravis),
        .initialPartysize = NELEMS(sTrainerMons_ScientistTravis),
        .party = sTrainerMons_ScientistTravis
    },
    [TRAINER_SCIENTIST_BRAYDON] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("BRAYDON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistBraydon),
        .initialPartysize = NELEMS(sTrainerMons_ScientistBraydon),
        .party = sTrainerMons_ScientistBraydon
    },
    [TRAINER_SCIENTIST_IVAN] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("IVAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistIvan),
        .initialPartysize = NELEMS(sTrainerMons_ScientistIvan),
        .party = sTrainerMons_ScientistIvan
    },
    [TRAINER_BOSS_GIOVANNI] = {
        
        .trainerClass = CLASS_BOSS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_LEADER_GIOVANNI,
        .trainerName = _("GIOVANNI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BossGiovanni),
        .initialPartysize = NELEMS(sTrainerMons_BossGiovanni),
        .party = sTrainerMons_BossGiovanni
    },
    [TRAINER_BOSS_GIOVANNI_2] = {
        
        .trainerClass = CLASS_BOSS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_LEADER_GIOVANNI,
        .trainerName = _("GIOVANNI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BossGiovanni2),
        .initialPartysize = NELEMS(sTrainerMons_BossGiovanni2),
        .party = sTrainerMons_BossGiovanni2
    },
    [TRAINER_LEADER_GIOVANNI] = {
        
        .trainerClass = CLASS_GYM_LEADER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_LEADER_GIOVANNI,
        .trainerName = _("GIOVANNI"),
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_FULL_HEAL},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_LeaderGiovanni),
        .initialPartysize = NELEMS(sTrainerMons_LeaderGiovanni),
        .party = sTrainerMons_LeaderGiovanni
    },
    [TRAINER_TEAM_ROCKET_GRUNT] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt),
        .party = sTrainerMons_TeamRocketGrunt
    },
    [TRAINER_TEAM_ROCKET_GRUNT_2] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt2),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt2),
        .party = sTrainerMons_TeamRocketGrunt2
    },
    [TRAINER_TEAM_ROCKET_GRUNT_3] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt3),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt3),
        .party = sTrainerMons_TeamRocketGrunt3
    },
    [TRAINER_TEAM_ROCKET_GRUNT_4] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt4),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt4),
        .party = sTrainerMons_TeamRocketGrunt4
    },
    [TRAINER_TEAM_ROCKET_GRUNT_5] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt5),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt5),
        .party = sTrainerMons_TeamRocketGrunt5
    },
    [TRAINER_TEAM_ROCKET_GRUNT_6] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt6),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt6),
        .party = sTrainerMons_TeamRocketGrunt6
    },
    [TRAINER_TEAM_ROCKET_GRUNT_7] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt7),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt7),
        .party = sTrainerMons_TeamRocketGrunt7
    },
    [TRAINER_TEAM_ROCKET_GRUNT_8] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt8),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt8),
        .party = sTrainerMons_TeamRocketGrunt8
    },
    [TRAINER_TEAM_ROCKET_GRUNT_9] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt9),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt9),
        .party = sTrainerMons_TeamRocketGrunt9
    },
    [TRAINER_TEAM_ROCKET_GRUNT_10] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt10),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt10),
        .party = sTrainerMons_TeamRocketGrunt10
    },
    [TRAINER_TEAM_ROCKET_GRUNT_11] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt11),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt11),
        .party = sTrainerMons_TeamRocketGrunt11
    },
    [TRAINER_TEAM_ROCKET_GRUNT_12] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt12),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt12),
        .party = sTrainerMons_TeamRocketGrunt12
    },
    [TRAINER_TEAM_ROCKET_GRUNT_13] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt13),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt13),
        .party = sTrainerMons_TeamRocketGrunt13
    },
    [TRAINER_TEAM_ROCKET_GRUNT_14] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt14),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt14),
        .party = sTrainerMons_TeamRocketGrunt14
    },
    [TRAINER_TEAM_ROCKET_GRUNT_15] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt15),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt15),
        .party = sTrainerMons_TeamRocketGrunt15
    },
    [TRAINER_TEAM_ROCKET_GRUNT_16] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt16),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt16),
        .party = sTrainerMons_TeamRocketGrunt16
    },
    [TRAINER_TEAM_ROCKET_GRUNT_17] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt17),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt17),
        .party = sTrainerMons_TeamRocketGrunt17
    },
    [TRAINER_TEAM_ROCKET_GRUNT_18] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt18),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt18),
        .party = sTrainerMons_TeamRocketGrunt18
    },
    [TRAINER_TEAM_ROCKET_GRUNT_19] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt19),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt19),
        .party = sTrainerMons_TeamRocketGrunt19
    },
    [TRAINER_TEAM_ROCKET_GRUNT_20] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt20),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt20),
        .party = sTrainerMons_TeamRocketGrunt20
    },
    [TRAINER_TEAM_ROCKET_GRUNT_21] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt21),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt21),
        .party = sTrainerMons_TeamRocketGrunt21
    },
    [TRAINER_TEAM_ROCKET_GRUNT_22] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt22),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt22),
        .party = sTrainerMons_TeamRocketGrunt22
    },
    [TRAINER_TEAM_ROCKET_GRUNT_23] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt23),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt23),
        .party = sTrainerMons_TeamRocketGrunt23
    },
    [TRAINER_TEAM_ROCKET_GRUNT_24] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt24),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt24),
        .party = sTrainerMons_TeamRocketGrunt24
    },
    [TRAINER_TEAM_ROCKET_GRUNT_25] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt25),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt25),
        .party = sTrainerMons_TeamRocketGrunt25
    },
    [TRAINER_TEAM_ROCKET_GRUNT_26] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt26),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt26),
        .party = sTrainerMons_TeamRocketGrunt26
    },
    [TRAINER_TEAM_ROCKET_GRUNT_27] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt27),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt27),
        .party = sTrainerMons_TeamRocketGrunt27
    },
    [TRAINER_TEAM_ROCKET_GRUNT_28] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt28),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt28),
        .party = sTrainerMons_TeamRocketGrunt28
    },
    [TRAINER_TEAM_ROCKET_GRUNT_29] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt29),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt29),
        .party = sTrainerMons_TeamRocketGrunt29
    },
    [TRAINER_TEAM_ROCKET_GRUNT_30] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt30),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt30),
        .party = sTrainerMons_TeamRocketGrunt30
    },
    [TRAINER_TEAM_ROCKET_GRUNT_31] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt31),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt31),
        .party = sTrainerMons_TeamRocketGrunt31
    },
    [TRAINER_TEAM_ROCKET_GRUNT_32] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt32),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt32),
        .party = sTrainerMons_TeamRocketGrunt32
    },
    [TRAINER_TEAM_ROCKET_GRUNT_33] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt33),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt33),
        .party = sTrainerMons_TeamRocketGrunt33
    },
    [TRAINER_TEAM_ROCKET_GRUNT_34] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt34),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt34),
        .party = sTrainerMons_TeamRocketGrunt34
    },
    [TRAINER_TEAM_ROCKET_GRUNT_35] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt35),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt35),
        .party = sTrainerMons_TeamRocketGrunt35
    },
    [TRAINER_TEAM_ROCKET_GRUNT_36] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt36),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt36),
        .party = sTrainerMons_TeamRocketGrunt36
    },
    [TRAINER_TEAM_ROCKET_GRUNT_37] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt37),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt37),
        .party = sTrainerMons_TeamRocketGrunt37
    },
    [TRAINER_TEAM_ROCKET_GRUNT_38] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt38),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt38),
        .party = sTrainerMons_TeamRocketGrunt38
    },
    [TRAINER_TEAM_ROCKET_GRUNT_39] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt39),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt39),
        .party = sTrainerMons_TeamRocketGrunt39
    },
    [TRAINER_TEAM_ROCKET_GRUNT_40] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt40),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt40),
        .party = sTrainerMons_TeamRocketGrunt40
    },
    [TRAINER_TEAM_ROCKET_GRUNT_41] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt41),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt41),
        .party = sTrainerMons_TeamRocketGrunt41
    },
    [TRAINER_COOLTRAINER_SAMUEL] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("SAMUEL"),
        .items = {ITEM_SUPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerSamuel),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerSamuel),
        .party = sTrainerMons_CooltrainerSamuel
    },
    [TRAINER_COOLTRAINER_GEORGE] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("GEORGE"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerGeorge),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerGeorge),
        .party = sTrainerMons_CooltrainerGeorge
    },
    [TRAINER_COOLTRAINER_COLBY] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("COLBY"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerColby),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerColby),
        .party = sTrainerMons_CooltrainerColby
    },
    [TRAINER_COOLTRAINER_PAUL] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("PAUL"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerPaul),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerPaul),
        .party = sTrainerMons_CooltrainerPaul
    },
    [TRAINER_COOLTRAINER_ROLANDO] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("ROLANDO"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerRolando),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerRolando),
        .party = sTrainerMons_CooltrainerRolando
    },
    [TRAINER_COOLTRAINER_GILBERT] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("GILBERT"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerGilbert),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerGilbert),
        .party = sTrainerMons_CooltrainerGilbert
    },
    [TRAINER_COOLTRAINER_OWEN] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("OWEN"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerOwen),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerOwen),
        .party = sTrainerMons_CooltrainerOwen
    },
    [TRAINER_COOLTRAINER_BERKE] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("BERKE"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerBerke),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerBerke),
        .party = sTrainerMons_CooltrainerBerke
    },
    [TRAINER_COOLTRAINER_YUJI] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("YUJI"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerYuji),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerYuji),
        .party = sTrainerMons_CooltrainerYuji
    },
    [TRAINER_COOLTRAINER_WARREN] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("WARREN"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerWarren),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerWarren),
        .party = sTrainerMons_CooltrainerWarren
    },
    [TRAINER_COOLTRAINER_MARY] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("MARY"),
        .items = {ITEM_SUPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerMary),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerMary),
        .party = sTrainerMons_CooltrainerMary
    },
    [TRAINER_COOLTRAINER_CAROLINE] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("CAROLINE"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerCaroline),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerCaroline),
        .party = sTrainerMons_CooltrainerCaroline
    },
    [TRAINER_COOLTRAINER_ALEXA] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("ALEXA"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerAlexa),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerAlexa),
        .party = sTrainerMons_CooltrainerAlexa
    },
    [TRAINER_COOLTRAINER_SHANNON] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("SHANNON"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerShannon),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerShannon),
        .party = sTrainerMons_CooltrainerShannon
    },
    [TRAINER_COOLTRAINER_NAOMI] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("NAOMI"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerNaomi),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerNaomi),
        .party = sTrainerMons_CooltrainerNaomi
    },
    [TRAINER_COOLTRAINER_BROOKE] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("BROOKE"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerBrooke),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerBrooke),
        .party = sTrainerMons_CooltrainerBrooke
    },
    [TRAINER_COOLTRAINER_AUSTINA] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("AUSTINA"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerAustina),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerAustina),
        .party = sTrainerMons_CooltrainerAustina
    },
    [TRAINER_COOLTRAINER_JULIE] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("JULIE"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerJulie),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerJulie),
        .party = sTrainerMons_CooltrainerJulie
    },
    [TRAINER_ELITE_FOUR_LORELEI] = {
        
        .trainerClass = CLASS_ELITE_FOUR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_LORELEI,
        .trainerName = _("LORELEI"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_EliteFourLorelei),
        .initialPartysize = NELEMS(sTrainerMons_EliteFourLorelei),
        .party = sTrainerMons_EliteFourLorelei
    },
    [TRAINER_ELITE_FOUR_BRUNO] = {
        
        .trainerClass = CLASS_ELITE_FOUR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_BRUNO,
        .trainerName = _("BRUNO"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_EliteFourBruno),
        .initialPartysize = NELEMS(sTrainerMons_EliteFourBruno),
        .party = sTrainerMons_EliteFourBruno
    },
    [TRAINER_ELITE_FOUR_AGATHA] = {
        
        .trainerClass = CLASS_ELITE_FOUR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_AGATHA,
        .trainerName = _("AGATHA"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_EliteFourAgatha),
        .initialPartysize = NELEMS(sTrainerMons_EliteFourAgatha),
        .party = sTrainerMons_EliteFourAgatha
    },
    [TRAINER_ELITE_FOUR_LANCE] = {
        
        .trainerClass = CLASS_ELITE_FOUR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_LANCE,
        .trainerName = _("LANCE"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_EliteFourLance),
        .initialPartysize = NELEMS(sTrainerMons_EliteFourLance),
        .party = sTrainerMons_EliteFourLance
    },
    [TRAINER_LEADER_BROCK] = {
        
        .trainerClass = CLASS_GYM_LEADER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_LEADER_BROCK,
        .trainerName = _("BROCK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_LeaderBrock),
        .initialPartysize = NELEMS(sTrainerMons_LeaderBrock),
        .party = sTrainerMons_LeaderBrock
    },
    [TRAINER_LEADER_MISTY] = {
        
        .trainerClass = CLASS_GYM_LEADER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_MISTY,
        .trainerName = _("MISTY"),
        .items = {ITEM_SUPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_LeaderMisty),
        .initialPartysize = NELEMS(sTrainerMons_LeaderMisty),
        .party = sTrainerMons_LeaderMisty
    },
    [TRAINER_LEADER_LT_SURGE] = {
        
        .trainerClass = CLASS_GYM_LEADER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_LEADER_LT_SURGE,
        .trainerName = _("LT. SURGE"),
        .items = {ITEM_SUPER_POTION, ITEM_FULL_HEAL},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_LeaderLtSurge),
        .initialPartysize = NELEMS(sTrainerMons_LeaderLtSurge),
        .party = sTrainerMons_LeaderLtSurge
    },
    [TRAINER_LEADER_ERIKA] = {
        
        .trainerClass = CLASS_GYM_LEADER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_ERIKA,
        .trainerName = _("ERIKA"),
        .items = {ITEM_HYPER_POTION, ITEM_FULL_HEAL},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_LeaderErika),
        .initialPartysize = NELEMS(sTrainerMons_LeaderErika),
        .party = sTrainerMons_LeaderErika
    },
    [TRAINER_LEADER_KOGA] = {
        
        .trainerClass = CLASS_GYM_LEADER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_LEADER_KOGA,
        .trainerName = _("KOGA"),
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_FULL_HEAL},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_LeaderKoga),
        .initialPartysize = NELEMS(sTrainerMons_LeaderKoga),
        .party = sTrainerMons_LeaderKoga
    },
    [TRAINER_LEADER_SABRINA] = {
        
        .trainerClass = CLASS_GYM_LEADER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_SABRINA,
        .trainerName = _("SABRINA"),
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_FULL_HEAL},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_LeaderSabrina),
        .initialPartysize = NELEMS(sTrainerMons_LeaderSabrina),
        .party = sTrainerMons_LeaderSabrina
    },
    [TRAINER_LEADER_BLAINE] = {
        
        .trainerClass = CLASS_GYM_LEADER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_LEADER_BLAINE,
        .trainerName = _("BLAINE"),
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_FULL_HEAL},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_LeaderBlaine),
        .initialPartysize = NELEMS(sTrainerMons_LeaderBlaine),
        .party = sTrainerMons_LeaderBlaine
    },    
    [TRAINER_GENTLEMAN_THOMAS] = {
        
        .trainerClass = CLASS_GENTLEMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_RICH,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("THOMAS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GentlemanThomas),
        .initialPartysize = NELEMS(sTrainerMons_GentlemanThomas),
        .party = sTrainerMons_GentlemanThomas
    },
    [TRAINER_GENTLEMAN_ARTHUR] = {
        
        .trainerClass = CLASS_GENTLEMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_RICH,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("ARTHUR"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GentlemanArthur),
        .initialPartysize = NELEMS(sTrainerMons_GentlemanArthur),
        .party = sTrainerMons_GentlemanArthur
    },
    [TRAINER_GENTLEMAN_TUCKER] = {
        
        .trainerClass = CLASS_GENTLEMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_RICH,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("TUCKER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GentlemanTucker),
        .initialPartysize = NELEMS(sTrainerMons_GentlemanTucker),
        .party = sTrainerMons_GentlemanTucker
    },
    [TRAINER_GENTLEMAN_NORTON] = {
        
        .trainerClass = CLASS_GENTLEMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_RICH,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("NORTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GentlemanNorton),
        .initialPartysize = NELEMS(sTrainerMons_GentlemanNorton),
        .party = sTrainerMons_GentlemanNorton
    },
    [TRAINER_GENTLEMAN_WALTER] = {
        
        .trainerClass = CLASS_GENTLEMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_RICH,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("WALTER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GentlemanWalter),
        .initialPartysize = NELEMS(sTrainerMons_GentlemanWalter),
        .party = sTrainerMons_GentlemanWalter
    },
    [TRAINER_RIVAL_SS_ANNE_SQUIRTLE] = {
        
        .trainerClass = CLASS_RIVAL_STAGE_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalSsAnneSquirtle),
        .initialPartysize = NELEMS(sTrainerMons_RivalSsAnneSquirtle),
        .party = sTrainerMons_RivalSsAnneSquirtle
    },
    [TRAINER_RIVAL_SS_ANNE_BULBASAUR] = {
        
        .trainerClass = CLASS_RIVAL_STAGE_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalSsAnneBulbasaur),
        .initialPartysize = NELEMS(sTrainerMons_RivalSsAnneBulbasaur),
        .party = sTrainerMons_RivalSsAnneBulbasaur
    },
    [TRAINER_RIVAL_SS_ANNE_CHARMANDER] = {
        
        .trainerClass = CLASS_RIVAL_STAGE_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalSsAnneCharmander),
        .initialPartysize = NELEMS(sTrainerMons_RivalSsAnneCharmander),
        .party = sTrainerMons_RivalSsAnneCharmander
    },
    [TRAINER_RIVAL_POKENON_TOWER_SQUIRTLE] = {
        
        .trainerClass = CLASS_RIVAL_STAGE_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalPokenonTowerSquirtle),
        .initialPartysize = NELEMS(sTrainerMons_RivalPokenonTowerSquirtle),
        .party = sTrainerMons_RivalPokenonTowerSquirtle
    },
    [TRAINER_RIVAL_POKENON_TOWER_BULBASAUR] = {
        
        .trainerClass = CLASS_RIVAL_STAGE_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalPokenonTowerBulbasaur),
        .initialPartysize = NELEMS(sTrainerMons_RivalPokenonTowerBulbasaur),
        .party = sTrainerMons_RivalPokenonTowerBulbasaur
    },
    [TRAINER_RIVAL_POKENON_TOWER_CHARMANDER] = {
        
        .trainerClass = CLASS_RIVAL_STAGE_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalPokenonTowerCharmander),
        .initialPartysize = NELEMS(sTrainerMons_RivalPokenonTowerCharmander),
        .party = sTrainerMons_RivalPokenonTowerCharmander
    },
    [TRAINER_RIVAL_SILPH_SQUIRTLE] = {
        
        .trainerClass = CLASS_RIVAL_STAGE_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalSilphSquirtle),
        .initialPartysize = NELEMS(sTrainerMons_RivalSilphSquirtle),
        .party = sTrainerMons_RivalSilphSquirtle
    },
    [TRAINER_RIVAL_SILPH_BULBASAUR] = {
        
        .trainerClass = CLASS_RIVAL_STAGE_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalSilphBulbasaur),
        .initialPartysize = NELEMS(sTrainerMons_RivalSilphBulbasaur),
        .party = sTrainerMons_RivalSilphBulbasaur
    },
    [TRAINER_RIVAL_SILPH_CHARMANDER] = {
        
        .trainerClass = CLASS_RIVAL_STAGE_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalSilphCharmander),
        .initialPartysize = NELEMS(sTrainerMons_RivalSilphCharmander),
        .party = sTrainerMons_RivalSilphCharmander
    },
    [TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE] = {
        
        .trainerClass = CLASS_RIVAL_STAGE_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalRoute22LateSquirtle),
        .initialPartysize = NELEMS(sTrainerMons_RivalRoute22LateSquirtle),
        .party = sTrainerMons_RivalRoute22LateSquirtle
    },
    [TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR] = {
        
        .trainerClass = CLASS_RIVAL_STAGE_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalRoute22LateBulbasaur),
        .initialPartysize = NELEMS(sTrainerMons_RivalRoute22LateBulbasaur),
        .party = sTrainerMons_RivalRoute22LateBulbasaur
    },
    [TRAINER_RIVAL_ROUTE22_LATE_CHARMANDER] = {
        
        .trainerClass = CLASS_RIVAL_STAGE_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_RivalRoute22LateCharmander),
        .initialPartysize = NELEMS(sTrainerMons_RivalRoute22LateCharmander),
        .party = sTrainerMons_RivalRoute22LateCharmander
    },
    [TRAINER_CHAMPION_FIRST_SQUIRTLE] = {
        
        .trainerClass = CLASS_CHAMPION_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_RIVAL,
        .trainerName = _("TERRY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_ChampionFirstSquirtle),
        .initialPartysize = NELEMS(sTrainerMons_ChampionFirstSquirtle),
        .party = sTrainerMons_ChampionFirstSquirtle
    },
    [TRAINER_CHAMPION_FIRST_BULBASAUR] = {
        
        .trainerClass = CLASS_CHAMPION_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_RIVAL,
        .trainerName = _("TERRY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_ChampionFirstBulbasaur),
        .initialPartysize = NELEMS(sTrainerMons_ChampionFirstBulbasaur),
        .party = sTrainerMons_ChampionFirstBulbasaur
    },
    [TRAINER_CHAMPION_FIRST_CHARMANDER] = {
        
        .trainerClass = CLASS_CHAMPION_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_RIVAL,
        .trainerName = _("TERRY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_ChampionFirstCharmander),
        .initialPartysize = NELEMS(sTrainerMons_ChampionFirstCharmander),
        .party = sTrainerMons_ChampionFirstCharmander
    },
    [TRAINER_CHANNELER_PATRICIA] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("PATRICIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerPatricia),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerPatricia),
        .party = sTrainerMons_ChannelerPatricia
    },
    [TRAINER_CHANNELER_CARLY] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("CARLY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerCarly),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerCarly),
        .party = sTrainerMons_ChannelerCarly
    },
    [TRAINER_CHANNELER_HOPE] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("HOPE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerHope),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerHope),
        .party = sTrainerMons_ChannelerHope
    },
    [TRAINER_CHANNELER_PAULA] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("PAULA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerPaula),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerPaula),
        .party = sTrainerMons_ChannelerPaula
    },
    [TRAINER_CHANNELER_LAUREL] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("LAUREL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerLaurel),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerLaurel),
        .party = sTrainerMons_ChannelerLaurel
    },
    [TRAINER_CHANNELER_JODY] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("JODY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerJody),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerJody),
        .party = sTrainerMons_ChannelerJody
    },
    [TRAINER_CHANNELER_TAMMY] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("TAMMY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerTammy),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerTammy),
        .party = sTrainerMons_ChannelerTammy
    },
    [TRAINER_CHANNELER_RUTH] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("RUTH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerRuth),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerRuth),
        .party = sTrainerMons_ChannelerRuth
    },
    [TRAINER_CHANNELER_KARINA] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("KARINA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerKarina),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerKarina),
        .party = sTrainerMons_ChannelerKarina
    },
    [TRAINER_CHANNELER_JANAE] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("JANAE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerJanae),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerJanae),
        .party = sTrainerMons_ChannelerJanae
    },
    [TRAINER_CHANNELER_ANGELICA] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("ANGELICA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerAngelica),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerAngelica),
        .party = sTrainerMons_ChannelerAngelica
    },
    [TRAINER_CHANNELER_EMILIA] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("EMILIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerEmilia),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerEmilia),
        .party = sTrainerMons_ChannelerEmilia
    },
    [TRAINER_CHANNELER_JENNIFER] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("JENNIFER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerJennifer),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerJennifer),
        .party = sTrainerMons_ChannelerJennifer
    },
    [TRAINER_CHANNELER_1] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Channeler1),
        .initialPartysize = NELEMS(sTrainerMons_Channeler1),
        .party = sTrainerMons_Channeler1
    },
    [TRAINER_CHANNELER_2] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Channeler2),
        .initialPartysize = NELEMS(sTrainerMons_Channeler2),
        .party = sTrainerMons_Channeler2
    },
    [TRAINER_CHANNELER_3] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Channeler3),
        .initialPartysize = NELEMS(sTrainerMons_Channeler3),
        .party = sTrainerMons_Channeler3
    },
    [TRAINER_CHANNELER_4] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Channeler4),
        .initialPartysize = NELEMS(sTrainerMons_Channeler4),
        .party = sTrainerMons_Channeler4
    },
    [TRAINER_CHANNELER_5] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Channeler5),
        .initialPartysize = NELEMS(sTrainerMons_Channeler5),
        .party = sTrainerMons_Channeler5
    },
    [TRAINER_CHANNELER_6] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Channeler6),
        .initialPartysize = NELEMS(sTrainerMons_Channeler6),
        .party = sTrainerMons_Channeler6
    },
    [TRAINER_CHANNELER_7] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Channeler7),
        .initialPartysize = NELEMS(sTrainerMons_Channeler7),
        .party = sTrainerMons_Channeler7
    },
    [TRAINER_CHANNELER_8] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Channeler8),
        .initialPartysize = NELEMS(sTrainerMons_Channeler8),
        .party = sTrainerMons_Channeler8
    },
    [TRAINER_CHANNELER_AMANDA] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("AMANDA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerAmanda),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerAmanda),
        .party = sTrainerMons_ChannelerAmanda
    },
    [TRAINER_CHANNELER_STACY] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("STACY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerStacy),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerStacy),
        .party = sTrainerMons_ChannelerStacy
    },
    [TRAINER_CHANNELER_TASHA] = {
        
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("TASHA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ChannelerTasha),
        .initialPartysize = NELEMS(sTrainerMons_ChannelerTasha),
        .party = sTrainerMons_ChannelerTasha
    },
    [TRAINER_HIKER_JEREMY] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("JEREMY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerJeremy),
        .initialPartysize = NELEMS(sTrainerMons_HikerJeremy),
        .party = sTrainerMons_HikerJeremy
    },
    [TRAINER_PICNICKER_ALMA] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ALMA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerAlma),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerAlma),
        .party = sTrainerMons_PicnickerAlma
    },
    [TRAINER_PICNICKER_SUSIE] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("SUSIE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerSusie),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerSusie),
        .party = sTrainerMons_PicnickerSusie
    },
    [TRAINER_PICNICKER_VALERIE] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("VALERIE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerValerie),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerValerie),
        .party = sTrainerMons_PicnickerValerie
    },
    [TRAINER_PICNICKER_GWEN] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("GWEN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerGwen),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerGwen),
        .party = sTrainerMons_PicnickerGwen
    },
    [TRAINER_BIKER_VIRGIL] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("VIRGIL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerVirgil),
        .initialPartysize = NELEMS(sTrainerMons_BikerVirgil),
        .party = sTrainerMons_BikerVirgil
    },
    [TRAINER_CAMPER_FLINT] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("FLINT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperFlint),
        .initialPartysize = NELEMS(sTrainerMons_CamperFlint),
        .party = sTrainerMons_CamperFlint
    },
    [TRAINER_PICNICKER_MISSY] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("MISSY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerMissy),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerMissy),
        .party = sTrainerMons_PicnickerMissy
    },
    [TRAINER_PICNICKER_IRENE] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("IRENE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerIrene),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerIrene),
        .party = sTrainerMons_PicnickerIrene
    },
    [TRAINER_PICNICKER_DANA] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("DANA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerDana),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerDana),
        .party = sTrainerMons_PicnickerDana
    },
    [TRAINER_PICNICKER_ARIANA] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ARIANA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerAriana),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerAriana),
        .party = sTrainerMons_PicnickerAriana
    },
    [TRAINER_PICNICKER_LEAH] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("LEAH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerLeah),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerLeah),
        .party = sTrainerMons_PicnickerLeah
    },
    [TRAINER_CAMPER_JUSTIN] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("JUSTIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperJustin),
        .initialPartysize = NELEMS(sTrainerMons_CamperJustin),
        .party = sTrainerMons_CamperJustin
    },
    [TRAINER_PICNICKER_YAZMIN] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("YAZMIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerYazmin),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerYazmin),
        .party = sTrainerMons_PicnickerYazmin
    },
    [TRAINER_PICNICKER_KINDRA] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("KINDRA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerKindra),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerKindra),
        .party = sTrainerMons_PicnickerKindra
    },
    [TRAINER_PICNICKER_BECKY] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("BECKY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerBecky),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerBecky),
        .party = sTrainerMons_PicnickerBecky
    },
    [TRAINER_PICNICKER_CELIA] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("CELIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerCelia),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerCelia),
        .party = sTrainerMons_PicnickerCelia
    },
    [TRAINER_GENTLEMAN_BROOKS] = {
        
        .trainerClass = CLASS_GENTLEMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_RICH,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("BROOKS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GentlemanBrooks),
        .initialPartysize = NELEMS(sTrainerMons_GentlemanBrooks),
        .party = sTrainerMons_GentlemanBrooks
    },
    [TRAINER_GENTLEMAN_LAMAR] = {
        
        .trainerClass = CLASS_GENTLEMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_RICH,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("LAMAR"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GentlemanLamar),
        .initialPartysize = NELEMS(sTrainerMons_GentlemanLamar),
        .party = sTrainerMons_GentlemanLamar
    },
    [TRAINER_TWINS_ELI_ANNE] = {
        
        .trainerClass = CLASS_TWINS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_TWINS,
        .trainerName = _("ELI & ANNE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TwinsEliAnne),
        .initialPartysize = NELEMS(sTrainerMons_TwinsEliAnne),
        .party = sTrainerMons_TwinsEliAnne
    },
    [TRAINER_COOL_COUPLE_RAY_TYRA] = {
        
        .trainerClass = CLASS_COOL_COUPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOL_COUPLE,
        .trainerName = _("RAY & TYRA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CoolCoupleRayTyra),
        .initialPartysize = NELEMS(sTrainerMons_CoolCoupleRayTyra),
        .party = sTrainerMons_CoolCoupleRayTyra
    },
    [TRAINER_YOUNG_COUPLE_GIA_JES] = {
        
        .trainerClass = CLASS_YOUNG_COUPLE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNG_COUPLE,
        .trainerName = _("GIA & JES"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungCoupleGiaJes),
        .initialPartysize = NELEMS(sTrainerMons_YoungCoupleGiaJes),
        .party = sTrainerMons_YoungCoupleGiaJes
    },
    [TRAINER_TWINS_KIRI_JAN] = {
        
        .trainerClass = CLASS_TWINS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_TWINS,
        .trainerName = _("KIRI & JAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TwinsKiriJan),
        .initialPartysize = NELEMS(sTrainerMons_TwinsKiriJan),
        .party = sTrainerMons_TwinsKiriJan
    },
    [TRAINER_CRUSH_KIN_RON_MYA] = {
        
        .trainerClass = CLASS_CRUSH_KIN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("RON & MYA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushKinRonMya),
        .initialPartysize = NELEMS(sTrainerMons_CrushKinRonMya),
        .party = sTrainerMons_CrushKinRonMya
    },
    [TRAINER_YOUNG_COUPLE_LEA_JED] = {
        
        .trainerClass = CLASS_YOUNG_COUPLE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNG_COUPLE,
        .trainerName = _("LEA & JED"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungCoupleLeaJed),
        .initialPartysize = NELEMS(sTrainerMons_YoungCoupleLeaJed),
        .party = sTrainerMons_YoungCoupleLeaJed
    },
    [TRAINER_SIS_AND_BRO_LIA_LUC] = {
        
        .trainerClass = CLASS_SIS_AND_BRO_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SIS_AND_BRO,
        .trainerName = _("LIA & LUC"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SisAndBroLiaLuc),
        .initialPartysize = NELEMS(sTrainerMons_SisAndBroLiaLuc),
        .party = sTrainerMons_SisAndBroLiaLuc
    },
    [TRAINER_SIS_AND_BRO_LIL_IAN] = {
        
        .trainerClass = CLASS_SIS_AND_BRO_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SIS_AND_BRO,
        .trainerName = _("LIL & IAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SisAndBroLilIan),
        .initialPartysize = NELEMS(sTrainerMons_SisAndBroLilIan),
        .party = sTrainerMons_SisAndBroLilIan
    },
    [TRAINER_BUG_CATCHER_3] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcher3),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcher3),
        .party = sTrainerMons_BugCatcher3
    },
    [TRAINER_BUG_CATCHER_4] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcher4),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcher4),
        .party = sTrainerMons_BugCatcher4
    },
    [TRAINER_BUG_CATCHER_5] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcher5),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcher5),
        .party = sTrainerMons_BugCatcher5
    },
    [TRAINER_BUG_CATCHER_6] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcher6),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcher6),
        .party = sTrainerMons_BugCatcher6
    },
    [TRAINER_BUG_CATCHER_7] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcher7),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcher7),
        .party = sTrainerMons_BugCatcher7
    },
    [TRAINER_BUG_CATCHER_8] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcher8),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcher8),
        .party = sTrainerMons_BugCatcher8
    },
    [TRAINER_YOUNGSTER_BEN_3] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("BEN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterBen3),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterBen3),
        .party = sTrainerMons_YoungsterBen3
    },
    [TRAINER_YOUNGSTER_BEN_4] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("BEN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterBen4),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterBen4),
        .party = sTrainerMons_YoungsterBen4
    },
    [TRAINER_YOUNGSTER_CHAD_2] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("CHAD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterChad2),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterChad2),
        .party = sTrainerMons_YoungsterChad2
    },
    [TRAINER_LASS_RELI_2] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("RELI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassReli2),
        .initialPartysize = NELEMS(sTrainerMons_LassReli2),
        .party = sTrainerMons_LassReli2
    },
    [TRAINER_LASS_RELI_3] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("RELI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassReli3),
        .initialPartysize = NELEMS(sTrainerMons_LassReli3),
        .party = sTrainerMons_LassReli3
    },
    [TRAINER_YOUNGSTER_TIMMY_2] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("TIMMY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterTimmy2),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterTimmy2),
        .party = sTrainerMons_YoungsterTimmy2
    },
    [TRAINER_YOUNGSTER_TIMMY_3] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("TIMMY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterTimmy3),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterTimmy3),
        .party = sTrainerMons_YoungsterTimmy3
    },
    [TRAINER_YOUNGSTER_TIMMY_4] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("TIMMY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterTimmy4),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterTimmy4),
        .party = sTrainerMons_YoungsterTimmy4
    },
    [TRAINER_YOUNGSTER_CHAD_3] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("CHAD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterChad3),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterChad3),
        .party = sTrainerMons_YoungsterChad3
    },
    [TRAINER_LASS_JANICE_2] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("JANICE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassJanice2),
        .initialPartysize = NELEMS(sTrainerMons_LassJanice2),
        .party = sTrainerMons_LassJanice2
    },
    [TRAINER_LASS_JANICE_3] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("JANICE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassJanice3),
        .initialPartysize = NELEMS(sTrainerMons_LassJanice3),
        .party = sTrainerMons_LassJanice3
    },
    [TRAINER_YOUNGSTER_CHAD_4] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("CHAD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterChad4),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterChad4),
        .party = sTrainerMons_YoungsterChad4
    },
    [TRAINER_HIKER_FRANKLIN_2] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("FRANKLIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerFranklin2),
        .initialPartysize = NELEMS(sTrainerMons_HikerFranklin2),
        .party = sTrainerMons_HikerFranklin2
    },
    [TRAINER_PKMN_PROF_PROF_OAK] = {
        
        .trainerClass = CLASS_PKMN_PROF,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_PROFESSOR_OAK,
        .trainerName = _("PROF. OAK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnProfProfOak),
        .initialPartysize = NELEMS(sTrainerMons_PkmnProfProfOak),
        .party = sTrainerMons_PkmnProfProfOak
    },
    [TRAINER_PLAYER_BRENDAN] = {
        
        .trainerClass = CLASS_PLAYER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RS_BRENDAN_2,
        .trainerName = _("BRENDAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PlayerBrendan),
        .initialPartysize = NELEMS(sTrainerMons_PlayerBrendan),
        .party = sTrainerMons_PlayerBrendan
    },
    [TRAINER_PLAYER_MAY] = {
        
        .trainerClass = CLASS_PLAYER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_RS_MAY_2,
        .trainerName = _("MAY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PlayerMay),
        .initialPartysize = NELEMS(sTrainerMons_PlayerMay),
        .party = sTrainerMons_PlayerMay
    },
    [TRAINER_PLAYER_RED] = {
        
        .trainerClass = CLASS_PLAYER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RED,
        .trainerName = _("RED"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PlayerRed),
        .initialPartysize = NELEMS(sTrainerMons_PlayerRed),
        .party = sTrainerMons_PlayerRed
    },
    [TRAINER_PLAYER_LEAF] = {
        
        .trainerClass = CLASS_PLAYER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LEAF,
        .trainerName = _("LEAF"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PlayerLeaf),
        .initialPartysize = NELEMS(sTrainerMons_PlayerLeaf),
        .party = sTrainerMons_PlayerLeaf
    },
    [TRAINER_TEAM_ROCKET_GRUNT_42] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_F,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt42),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt42),
        .party = sTrainerMons_TeamRocketGrunt42
    },
    [TRAINER_PSYCHIC_JACLYN] = {
        
        .trainerClass = CLASS_PSYCHIC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = _("JACLYN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PsychicJaclyn),
        .initialPartysize = NELEMS(sTrainerMons_PsychicJaclyn),
        .party = sTrainerMons_PsychicJaclyn
    },
    [TRAINER_CRUSH_GIRL_SHARON] = {
        
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("SHARON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushGirlSharon),
        .initialPartysize = NELEMS(sTrainerMons_CrushGirlSharon),
        .party = sTrainerMons_CrushGirlSharon
    },
    [TRAINER_TUBER_AMIRA] = {
        
        .trainerClass = CLASS_TUBER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_TUBER_F,
        .trainerName = _("AMIRA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TuberAmira),
        .initialPartysize = NELEMS(sTrainerMons_TuberAmira),
        .party = sTrainerMons_TuberAmira
    },
    [TRAINER_PKMN_BREEDER_ALIZE] = {
        
        .trainerClass = CLASS_PKMN_BREEDER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_BREEDER_F,
        .trainerName = _("ALIZE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnBreederAlize),
        .initialPartysize = NELEMS(sTrainerMons_PkmnBreederAlize),
        .party = sTrainerMons_PkmnBreederAlize
    },
    [TRAINER_PKMN_RANGER_NICOLAS] = {
        
        .trainerClass = CLASS_PKMN_RANGER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_M,
        .trainerName = _("NICOLAS"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_PkmnRangerNicolas),
        .initialPartysize = NELEMS(sTrainerMons_PkmnRangerNicolas),
        .party = sTrainerMons_PkmnRangerNicolas
    },
    [TRAINER_PKMN_RANGER_MADELINE] = {
        
        .trainerClass = CLASS_PKMN_RANGER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_F,
        .trainerName = _("MADELINE"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_PkmnRangerMadeline),
        .initialPartysize = NELEMS(sTrainerMons_PkmnRangerMadeline),
        .party = sTrainerMons_PkmnRangerMadeline
    },
    [TRAINER_AROMA_LADY_NIKKI] = {
        
        .trainerClass = CLASS_AROMA_LADY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_AROMA_LADY,
        .trainerName = _("NIKKI"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_AromaLadyNikki),
        .initialPartysize = NELEMS(sTrainerMons_AromaLadyNikki),
        .party = sTrainerMons_AromaLadyNikki
    },
    [TRAINER_RUIN_MANIAC_STANLY] = {
        
        .trainerClass = CLASS_RUIN_MANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("STANLY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RuinManiacStanly),
        .initialPartysize = NELEMS(sTrainerMons_RuinManiacStanly),
        .party = sTrainerMons_RuinManiacStanly
    },
    [TRAINER_LADY_JACKI] = {
        
        .trainerClass = CLASS_LADY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LADY,
        .trainerName = _("JACKI"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LadyJacki),
        .initialPartysize = NELEMS(sTrainerMons_LadyJacki),
        .party = sTrainerMons_LadyJacki
    },
    [TRAINER_PAINTER_DAISY] = {
        
        .trainerClass = CLASS_PAINTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = _("DAISY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PainterDaisy),
        .initialPartysize = NELEMS(sTrainerMons_PainterDaisy),
        .party = sTrainerMons_PainterDaisy
    },
    [TRAINER_BIKER_GOON] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("GOON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerGoon),
        .initialPartysize = NELEMS(sTrainerMons_BikerGoon),
        .party = sTrainerMons_BikerGoon
    },
    [TRAINER_BIKER_GOON_2] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("GOON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerGoon2),
        .initialPartysize = NELEMS(sTrainerMons_BikerGoon2),
        .party = sTrainerMons_BikerGoon2
    },
    [TRAINER_BIKER_GOON_3] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("GOON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerGoon3),
        .initialPartysize = NELEMS(sTrainerMons_BikerGoon3),
        .party = sTrainerMons_BikerGoon3
    },
    [TRAINER_BIKER_2] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _(""),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_Biker2),
        .initialPartysize = NELEMS(sTrainerMons_Biker2),
        .party = sTrainerMons_Biker2
    },
    [TRAINER_BUG_CATCHER_ANTHONY] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("ANTHONY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherAnthony),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherAnthony),
        .party = sTrainerMons_BugCatcherAnthony
    },
    [TRAINER_BUG_CATCHER_CHARLIE] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("CHARLIE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherCharlie),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherCharlie),
        .party = sTrainerMons_BugCatcherCharlie
    },
    [TRAINER_TWINS_ELI_ANNE_2] = {
        
        .trainerClass = CLASS_TWINS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_TWINS,
        .trainerName = _("ELI & ANNE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TwinsEliAnne2),
        .initialPartysize = NELEMS(sTrainerMons_TwinsEliAnne2),
        .party = sTrainerMons_TwinsEliAnne2
    },
    [TRAINER_YOUNGSTER_JOHNSON] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("JOHNSON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterJohnson),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterJohnson),
        .party = sTrainerMons_YoungsterJohnson
    },
    [TRAINER_BIKER_RICARDO] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("RICARDO"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerRicardo),
        .initialPartysize = NELEMS(sTrainerMons_BikerRicardo),
        .party = sTrainerMons_BikerRicardo
    },
    [TRAINER_BIKER_JAREN] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("JAREN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerJaren),
        .initialPartysize = NELEMS(sTrainerMons_BikerJaren),
        .party = sTrainerMons_BikerJaren
    },
    [TRAINER_TEAM_ROCKET_GRUNT_43] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt43),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt43),
        .party = sTrainerMons_TeamRocketGrunt43
    },
    [TRAINER_TEAM_ROCKET_GRUNT_44] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt44),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt44),
        .party = sTrainerMons_TeamRocketGrunt44
    },
    [TRAINER_TEAM_ROCKET_GRUNT_45] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt45),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt45),
        .party = sTrainerMons_TeamRocketGrunt45
    },
    [TRAINER_TEAM_ROCKET_GRUNT_46] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt46),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt46),
        .party = sTrainerMons_TeamRocketGrunt46
    },
    [TRAINER_TEAM_ROCKET_GRUNT_47] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt47),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt47),
        .party = sTrainerMons_TeamRocketGrunt47
    },
    [TRAINER_TEAM_ROCKET_GRUNT_48] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt48),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt48),
        .party = sTrainerMons_TeamRocketGrunt48
    },
    [TRAINER_TEAM_ROCKET_ADMIN] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_F,
        .trainerName = _("ADMIN"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_TeamRocketAdmin),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketAdmin),
        .party = sTrainerMons_TeamRocketAdmin
    },
    [TRAINER_TEAM_ROCKET_ADMIN_2] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("ADMIN"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_TeamRocketAdmin2),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketAdmin2),
        .party = sTrainerMons_TeamRocketAdmin2
    },
    [TRAINER_SCIENTIST_GIDEON] = {
        
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("GIDEON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_ScientistGideon),
        .initialPartysize = NELEMS(sTrainerMons_ScientistGideon),
        .party = sTrainerMons_ScientistGideon
    },
    [TRAINER_SWIMMER_FEMALE_AMARA] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("AMARA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleAmara),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleAmara),
        .party = sTrainerMons_SwimmerFemaleAmara
    },
    [TRAINER_SWIMMER_FEMALE_MARIA] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("MARIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleMaria),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleMaria),
        .party = sTrainerMons_SwimmerFemaleMaria
    },
    [TRAINER_SWIMMER_FEMALE_ABIGAIL] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("ABIGAIL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleAbigail),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleAbigail),
        .party = sTrainerMons_SwimmerFemaleAbigail
    },
    [TRAINER_SWIMMER_MALE_FINN] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("FINN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleFinn),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleFinn),
        .party = sTrainerMons_SwimmerMaleFinn
    },
    [TRAINER_SWIMMER_MALE_GARRETT] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("GARRETT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleGarrett),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleGarrett),
        .party = sTrainerMons_SwimmerMaleGarrett
    },
    [TRAINER_FISHERMAN_TOMMY] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("TOMMY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanTommy),
        .initialPartysize = NELEMS(sTrainerMons_FishermanTommy),
        .party = sTrainerMons_FishermanTommy
    },
    [TRAINER_CRUSH_GIRL_TANYA] = {
        
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("TANYA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushGirlTanya),
        .initialPartysize = NELEMS(sTrainerMons_CrushGirlTanya),
        .party = sTrainerMons_CrushGirlTanya
    },
    [TRAINER_BLACK_BELT_SHEA] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("SHEA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltShea),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltShea),
        .party = sTrainerMons_BlackBeltShea
    },
    [TRAINER_BLACK_BELT_HUGH] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("HUGH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltHugh),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltHugh),
        .party = sTrainerMons_BlackBeltHugh
    },
    [TRAINER_CAMPER_BRYCE] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("BRYCE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperBryce),
        .initialPartysize = NELEMS(sTrainerMons_CamperBryce),
        .party = sTrainerMons_CamperBryce
    },
    [TRAINER_PICNICKER_CLAIRE] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("CLAIRE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerClaire),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerClaire),
        .party = sTrainerMons_PicnickerClaire
    },
    [TRAINER_CRUSH_KIN_MIK_KIA] = {
        
        .trainerClass = CLASS_CRUSH_KIN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("MIK & KIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushKinMikKia),
        .initialPartysize = NELEMS(sTrainerMons_CrushKinMikKia),
        .party = sTrainerMons_CrushKinMikKia
    },
    [TRAINER_AROMA_LADY_VIOLET] = {
        
        .trainerClass = CLASS_AROMA_LADY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_AROMA_LADY,
        .trainerName = _("VIOLET"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_AromaLadyViolet),
        .initialPartysize = NELEMS(sTrainerMons_AromaLadyViolet),
        .party = sTrainerMons_AromaLadyViolet
    },
    [TRAINER_TUBER_ALEXIS] = {
        
        .trainerClass = CLASS_TUBER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_TUBER_F,
        .trainerName = _("ALEXIS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TuberAlexis),
        .initialPartysize = NELEMS(sTrainerMons_TuberAlexis),
        .party = sTrainerMons_TuberAlexis
    },
    [TRAINER_TWINS_JOY_MEG] = {
        
        .trainerClass = CLASS_TWINS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_TWINS,
        .trainerName = _("JOY & MEG"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TwinsJoyMeg),
        .initialPartysize = NELEMS(sTrainerMons_TwinsJoyMeg),
        .party = sTrainerMons_TwinsJoyMeg
    },
    [TRAINER_SWIMMER_FEMALE_TISHA] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("TISHA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleTisha),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleTisha),
        .party = sTrainerMons_SwimmerFemaleTisha
    },
    [TRAINER_PAINTER_CELINA] = {
        
        .trainerClass = CLASS_PAINTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = _("CELINA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PainterCelina),
        .initialPartysize = NELEMS(sTrainerMons_PainterCelina),
        .party = sTrainerMons_PainterCelina
    },
    [TRAINER_PAINTER_RAYNA] = {
        
        .trainerClass = CLASS_PAINTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = _("RAYNA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PainterRayna),
        .initialPartysize = NELEMS(sTrainerMons_PainterRayna),
        .party = sTrainerMons_PainterRayna
    },
    [TRAINER_LADY_GILLIAN] = {
        
        .trainerClass = CLASS_LADY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LADY,
        .trainerName = _("GILLIAN"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LadyGillian),
        .initialPartysize = NELEMS(sTrainerMons_LadyGillian),
        .party = sTrainerMons_LadyGillian
    },
    [TRAINER_YOUNGSTER_DESTIN] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("DESTIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterDestin),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterDestin),
        .party = sTrainerMons_YoungsterDestin
    },
    [TRAINER_SWIMMER_MALE_TOBY] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("TOBY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleToby),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleToby),
        .party = sTrainerMons_SwimmerMaleToby
    },
    [TRAINER_TEAM_ROCKET_GRUNT_49] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt49),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt49),
        .party = sTrainerMons_TeamRocketGrunt49
    },
    [TRAINER_TEAM_ROCKET_GRUNT_50] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt50),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt50),
        .party = sTrainerMons_TeamRocketGrunt50
    },
    [TRAINER_TEAM_ROCKET_GRUNT_51] = {
        
        .trainerClass = CLASS_TEAM_ROCKET,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_F,
        .trainerName = _("GRUNT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamRocketGrunt51),
        .initialPartysize = NELEMS(sTrainerMons_TeamRocketGrunt51),
        .party = sTrainerMons_TeamRocketGrunt51
    },
    [TRAINER_BIRD_KEEPER_MILO] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("MILO"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperMilo),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperMilo),
        .party = sTrainerMons_BirdKeeperMilo
    },
    [TRAINER_BIRD_KEEPER_CHAZ] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("CHAZ"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperChaz),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperChaz),
        .party = sTrainerMons_BirdKeeperChaz
    },
    [TRAINER_BIRD_KEEPER_HAROLD] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("HAROLD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperHarold),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperHarold),
        .party = sTrainerMons_BirdKeeperHarold
    },
    [TRAINER_FISHERMAN_TYLOR] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("TYLOR"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanTylor),
        .initialPartysize = NELEMS(sTrainerMons_FishermanTylor),
        .party = sTrainerMons_FishermanTylor
    },
    [TRAINER_SWIMMER_MALE_MYMO] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("MYMO"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleMymo),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleMymo),
        .party = sTrainerMons_SwimmerMaleMymo
    },
    [TRAINER_SWIMMER_FEMALE_NICOLE] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("NICOLE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleNicole),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleNicole),
        .party = sTrainerMons_SwimmerFemaleNicole
    },
    [TRAINER_SIS_AND_BRO_AVA_GEB] = {
        
        .trainerClass = CLASS_SIS_AND_BRO_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SIS_AND_BRO,
        .trainerName = _("AVA & GEB"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SisAndBroAvaGeb),
        .initialPartysize = NELEMS(sTrainerMons_SisAndBroAvaGeb),
        .party = sTrainerMons_SisAndBroAvaGeb
    },
    [TRAINER_AROMA_LADY_ROSE] = {
        
        .trainerClass = CLASS_AROMA_LADY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_AROMA_LADY,
        .trainerName = _("ROSE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_AromaLadyRose),
        .initialPartysize = NELEMS(sTrainerMons_AromaLadyRose),
        .party = sTrainerMons_AromaLadyRose
    },
    [TRAINER_SWIMMER_MALE_SAMIR] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("SAMIR"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleSamir),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleSamir),
        .party = sTrainerMons_SwimmerMaleSamir
    },
    [TRAINER_SWIMMER_FEMALE_DENISE] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("DENISE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleDenise),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleDenise),
        .party = sTrainerMons_SwimmerFemaleDenise
    },
    [TRAINER_TWINS_MIU_MIA] = {
        
        .trainerClass = CLASS_TWINS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_TWINS,
        .trainerName = _("MIU & MIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TwinsMiuMia),
        .initialPartysize = NELEMS(sTrainerMons_TwinsMiuMia),
        .party = sTrainerMons_TwinsMiuMia
    },
    [TRAINER_HIKER_EARL] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("EARL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerEarl),
        .initialPartysize = NELEMS(sTrainerMons_HikerEarl),
        .party = sTrainerMons_HikerEarl
    },
    [TRAINER_RUIN_MANIAC_FOSTER] = {
        
        .trainerClass = CLASS_RUIN_MANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("FOSTER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RuinManiacFoster),
        .initialPartysize = NELEMS(sTrainerMons_RuinManiacFoster),
        .party = sTrainerMons_RuinManiacFoster
    },
    [TRAINER_RUIN_MANIAC_LARRY] = {
        
        .trainerClass = CLASS_RUIN_MANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("LARRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RuinManiacLarry),
        .initialPartysize = NELEMS(sTrainerMons_RuinManiacLarry),
        .party = sTrainerMons_RuinManiacLarry
    },
    [TRAINER_HIKER_DARYL] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("DARYL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerDaryl),
        .initialPartysize = NELEMS(sTrainerMons_HikerDaryl),
        .party = sTrainerMons_HikerDaryl
    },
    [TRAINER_POKEMANIAC_HECTOR] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("HECTOR"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacHector),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacHector),
        .party = sTrainerMons_PokemaniacHector
    },
    [TRAINER_PSYCHIC_DARIO] = {
        
        .trainerClass = CLASS_PSYCHIC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = _("DARIO"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PsychicDario),
        .initialPartysize = NELEMS(sTrainerMons_PsychicDario),
        .party = sTrainerMons_PsychicDario
    },
    [TRAINER_PSYCHIC_RODETTE] = {
        
        .trainerClass = CLASS_PSYCHIC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = _("RODETTE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PsychicRodette),
        .initialPartysize = NELEMS(sTrainerMons_PsychicRodette),
        .party = sTrainerMons_PsychicRodette
    },
    [TRAINER_AROMA_LADY_MIAH] = {
        
        .trainerClass = CLASS_AROMA_LADY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_AROMA_LADY,
        .trainerName = _("MIAH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_AromaLadyMiah),
        .initialPartysize = NELEMS(sTrainerMons_AromaLadyMiah),
        .party = sTrainerMons_AromaLadyMiah
    },
    [TRAINER_YOUNG_COUPLE_EVE_JON] = {
        
        .trainerClass = CLASS_YOUNG_COUPLE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNG_COUPLE,
        .trainerName = _("EVE & JON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungCoupleEveJon),
        .initialPartysize = NELEMS(sTrainerMons_YoungCoupleEveJon),
        .party = sTrainerMons_YoungCoupleEveJon
    },
    [TRAINER_JUGGLER_MASON] = {
        
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("MASON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_JugglerMason),
        .initialPartysize = NELEMS(sTrainerMons_JugglerMason),
        .party = sTrainerMons_JugglerMason
    },
    [TRAINER_CRUSH_GIRL_CYNDY] = {
        
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("CYNDY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushGirlCyndy),
        .initialPartysize = NELEMS(sTrainerMons_CrushGirlCyndy),
        .party = sTrainerMons_CrushGirlCyndy
    },
    [TRAINER_CRUSH_GIRL_JOCELYN] = {
        
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("JOCELYN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushGirlJocelyn),
        .initialPartysize = NELEMS(sTrainerMons_CrushGirlJocelyn),
        .party = sTrainerMons_CrushGirlJocelyn
    },
    [TRAINER_TAMER_EVAN] = {
        
        .trainerClass = CLASS_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("EVAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TamerEvan),
        .initialPartysize = NELEMS(sTrainerMons_TamerEvan),
        .party = sTrainerMons_TamerEvan
    },
    [TRAINER_POKEMANIAC_MARK_2] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("MARK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacMark2),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacMark2),
        .party = sTrainerMons_PokemaniacMark2
    },
    [TRAINER_PKMN_RANGER_LOGAN] = {
        
        .trainerClass = CLASS_PKMN_RANGER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_M,
        .trainerName = _("LOGAN"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_PkmnRangerLogan),
        .initialPartysize = NELEMS(sTrainerMons_PkmnRangerLogan),
        .party = sTrainerMons_PkmnRangerLogan
    },
    [TRAINER_PKMN_RANGER_JACKSON] = {
        
        .trainerClass = CLASS_PKMN_RANGER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_M,
        .trainerName = _("JACKSON"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_PkmnRangerJackson),
        .initialPartysize = NELEMS(sTrainerMons_PkmnRangerJackson),
        .party = sTrainerMons_PkmnRangerJackson
    },
    [TRAINER_PKMN_RANGER_BETH] = {
        
        .trainerClass = CLASS_PKMN_RANGER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_F,
        .trainerName = _("BETH"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_PkmnRangerBeth),
        .initialPartysize = NELEMS(sTrainerMons_PkmnRangerBeth),
        .party = sTrainerMons_PkmnRangerBeth
    },
    [TRAINER_PKMN_RANGER_KATELYN] = {
        
        .trainerClass = CLASS_PKMN_RANGER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_F,
        .trainerName = _("KATELYN"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_PkmnRangerKatelyn),
        .initialPartysize = NELEMS(sTrainerMons_PkmnRangerKatelyn),
        .party = sTrainerMons_PkmnRangerKatelyn
    },
    [TRAINER_COOLTRAINER_LEROY] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("LEROY"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerLeroy),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerLeroy),
        .party = sTrainerMons_CooltrainerLeroy
    },
    [TRAINER_COOLTRAINER_MICHELLE] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("MICHELLE"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerMichelle),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerMichelle),
        .party = sTrainerMons_CooltrainerMichelle
    },
    [TRAINER_COOL_COUPLE_LEX_NYA] = {
        
        .trainerClass = CLASS_COOL_COUPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOL_COUPLE,
        .trainerName = _("LEX & NYA"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CoolCoupleLexNya),
        .initialPartysize = NELEMS(sTrainerMons_CoolCoupleLexNya),
        .party = sTrainerMons_CoolCoupleLexNya
    },
    [TRAINER_RUIN_MANIAC_BRANDON] = {
        
        .trainerClass = CLASS_RUIN_MANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("BRANDON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RuinManiacBrandon),
        .initialPartysize = NELEMS(sTrainerMons_RuinManiacBrandon),
        .party = sTrainerMons_RuinManiacBrandon
    },
    [TRAINER_RUIN_MANIAC_BENJAMIN] = {
        
        .trainerClass = CLASS_RUIN_MANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("BENJAMIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RuinManiacBenjamin),
        .initialPartysize = NELEMS(sTrainerMons_RuinManiacBenjamin),
        .party = sTrainerMons_RuinManiacBenjamin
    },
    [TRAINER_PAINTER_EDNA] = {
        
        .trainerClass = CLASS_PAINTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = _("EDNA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PainterEdna),
        .initialPartysize = NELEMS(sTrainerMons_PainterEdna),
        .party = sTrainerMons_PainterEdna
    },
    [TRAINER_GENTLEMAN_CLIFFORD] = {
        
        .trainerClass = CLASS_GENTLEMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_RICH,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("CLIFFORD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GentlemanClifford),
        .initialPartysize = NELEMS(sTrainerMons_GentlemanClifford),
        .party = sTrainerMons_GentlemanClifford
    },
    [TRAINER_LADY_SELPHY] = {
        
        .trainerClass = CLASS_LADY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LADY,
        .trainerName = _("SELPHY"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LadySelphy),
        .initialPartysize = NELEMS(sTrainerMons_LadySelphy),
        .party = sTrainerMons_LadySelphy
    },
    [TRAINER_RUIN_MANIAC_LAWSON] = {
        
        .trainerClass = CLASS_RUIN_MANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("LAWSON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RuinManiacLawson),
        .initialPartysize = NELEMS(sTrainerMons_RuinManiacLawson),
        .party = sTrainerMons_RuinManiacLawson
    },
    [TRAINER_PSYCHIC_LAURA] = {
        
        .trainerClass = CLASS_PSYCHIC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = _("LAURA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PsychicLaura),
        .initialPartysize = NELEMS(sTrainerMons_PsychicLaura),
        .party = sTrainerMons_PsychicLaura
    },
    [TRAINER_PKMN_BREEDER_BETHANY] = {
        
        .trainerClass = CLASS_PKMN_BREEDER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_BREEDER_F,
        .trainerName = _("BETHANY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnBreederBethany),
        .initialPartysize = NELEMS(sTrainerMons_PkmnBreederBethany),
        .party = sTrainerMons_PkmnBreederBethany
    },
    [TRAINER_PKMN_BREEDER_ALLISON] = {
        
        .trainerClass = CLASS_PKMN_BREEDER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_BREEDER_F,
        .trainerName = _("ALLISON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnBreederAllison),
        .initialPartysize = NELEMS(sTrainerMons_PkmnBreederAllison),
        .party = sTrainerMons_PkmnBreederAllison
    },
    [TRAINER_BUG_CATCHER_GARRET] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("GARRET"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherGarret),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherGarret),
        .party = sTrainerMons_BugCatcherGarret
    },
    [TRAINER_BUG_CATCHER_JONAH] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("JONAH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherJonah),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherJonah),
        .party = sTrainerMons_BugCatcherJonah
    },
    [TRAINER_BUG_CATCHER_VANCE] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("VANCE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherVance),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherVance),
        .party = sTrainerMons_BugCatcherVance
    },
    [TRAINER_YOUNGSTER_NASH] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("NASH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterNash),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterNash),
        .party = sTrainerMons_YoungsterNash
    },
    [TRAINER_YOUNGSTER_CORDELL] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("CORDELL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterCordell),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterCordell),
        .party = sTrainerMons_YoungsterCordell
    },
    [TRAINER_LASS_DALIA] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("DALIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassDalia),
        .initialPartysize = NELEMS(sTrainerMons_LassDalia),
        .party = sTrainerMons_LassDalia
    },
    [TRAINER_LASS_JOANA] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("JOANA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassJoana),
        .initialPartysize = NELEMS(sTrainerMons_LassJoana),
        .party = sTrainerMons_LassJoana
    },
    [TRAINER_CAMPER_RILEY] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("RILEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperRiley),
        .initialPartysize = NELEMS(sTrainerMons_CamperRiley),
        .party = sTrainerMons_CamperRiley
    },
    [TRAINER_PICNICKER_MARCY] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("MARCY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerMarcy),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerMarcy),
        .party = sTrainerMons_PicnickerMarcy
    },
    [TRAINER_RUIN_MANIAC_LAYTON] = {
        
        .trainerClass = CLASS_RUIN_MANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("LAYTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RuinManiacLayton),
        .initialPartysize = NELEMS(sTrainerMons_RuinManiacLayton),
        .party = sTrainerMons_RuinManiacLayton
    },
    [TRAINER_PICNICKER_KELSEY_2] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("KELSEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerKelsey2),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerKelsey2),
        .party = sTrainerMons_PicnickerKelsey2
    },
    [TRAINER_PICNICKER_KELSEY_3] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("KELSEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerKelsey3),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerKelsey3),
        .party = sTrainerMons_PicnickerKelsey3
    },
    [TRAINER_PICNICKER_KELSEY_4] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("KELSEY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerKelsey4),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerKelsey4),
        .party = sTrainerMons_PicnickerKelsey4
    },
    [TRAINER_CAMPER_RICKY_2] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("RICKY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperRicky2),
        .initialPartysize = NELEMS(sTrainerMons_CamperRicky2),
        .party = sTrainerMons_CamperRicky2
    },
    [TRAINER_CAMPER_RICKY_3] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("RICKY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperRicky3),
        .initialPartysize = NELEMS(sTrainerMons_CamperRicky3),
        .party = sTrainerMons_CamperRicky3
    },
    [TRAINER_CAMPER_RICKY_4] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("RICKY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperRicky4),
        .initialPartysize = NELEMS(sTrainerMons_CamperRicky4),
        .party = sTrainerMons_CamperRicky4
    },
    [TRAINER_CAMPER_JEFF_2] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("JEFF"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperJeff2),
        .initialPartysize = NELEMS(sTrainerMons_CamperJeff2),
        .party = sTrainerMons_CamperJeff2
    },
    [TRAINER_CAMPER_JEFF_3] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("JEFF"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperJeff3),
        .initialPartysize = NELEMS(sTrainerMons_CamperJeff3),
        .party = sTrainerMons_CamperJeff3
    },
    [TRAINER_CAMPER_JEFF_4] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("JEFF"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperJeff4),
        .initialPartysize = NELEMS(sTrainerMons_CamperJeff4),
        .party = sTrainerMons_CamperJeff4
    },
    [TRAINER_PICNICKER_ISABELLE_2] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ISABELLE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerIsabelle2),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerIsabelle2),
        .party = sTrainerMons_PicnickerIsabelle2
    },
    [TRAINER_PICNICKER_ISABELLE_3] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ISABELLE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerIsabelle3),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerIsabelle3),
        .party = sTrainerMons_PicnickerIsabelle3
    },
    [TRAINER_PICNICKER_ISABELLE_4] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ISABELLE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerIsabelle4),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerIsabelle4),
        .party = sTrainerMons_PicnickerIsabelle4
    },
    [TRAINER_YOUNGSTER_YASU_2] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("YASU"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterYasu2),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterYasu2),
        .party = sTrainerMons_YoungsterYasu2
    },
    [TRAINER_YOUNGSTER_YASU_3] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("YASU"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterYasu3),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterYasu3),
        .party = sTrainerMons_YoungsterYasu3
    },
    [TRAINER_ENGINEER_BERNIE_2] = {
        
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ENGINEER,
        .trainerName = _("BERNIE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_EngineerBernie2),
        .initialPartysize = NELEMS(sTrainerMons_EngineerBernie2),
        .party = sTrainerMons_EngineerBernie2
    },
    [TRAINER_GAMBLER_DARIAN_2] = {
        
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = _("DARIAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GamblerDarian2),
        .initialPartysize = NELEMS(sTrainerMons_GamblerDarian2),
        .party = sTrainerMons_GamblerDarian2
    },
    [TRAINER_CAMPER_CHRIS_2] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("CHRIS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperChris2),
        .initialPartysize = NELEMS(sTrainerMons_CamperChris2),
        .party = sTrainerMons_CamperChris2
    },
    [TRAINER_CAMPER_CHRIS_3] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("CHRIS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperChris3),
        .initialPartysize = NELEMS(sTrainerMons_CamperChris3),
        .party = sTrainerMons_CamperChris3
    },
    [TRAINER_CAMPER_CHRIS_4] = {
        
        .trainerClass = CLASS_CAMPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("CHRIS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CamperChris4),
        .initialPartysize = NELEMS(sTrainerMons_CamperChris4),
        .party = sTrainerMons_CamperChris4
    },
    [TRAINER_PICNICKER_ALICIA_2] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ALICIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerAlicia2),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerAlicia2),
        .party = sTrainerMons_PicnickerAlicia2
    },
    [TRAINER_PICNICKER_ALICIA_3] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ALICIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerAlicia3),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerAlicia3),
        .party = sTrainerMons_PicnickerAlicia3
    },
    [TRAINER_PICNICKER_ALICIA_4] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ALICIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerAlicia4),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerAlicia4),
        .party = sTrainerMons_PicnickerAlicia4
    },
    [TRAINER_HIKER_JEREMY_2] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("JEREMY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerJeremy2),
        .initialPartysize = NELEMS(sTrainerMons_HikerJeremy2),
        .party = sTrainerMons_HikerJeremy2
    },
    [TRAINER_POKEMANIAC_MARK_3] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("MARK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacMark3),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacMark3),
        .party = sTrainerMons_PokemaniacMark3
    },
    [TRAINER_POKEMANIAC_HERMAN_2] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("HERMAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacHerman2),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacHerman2),
        .party = sTrainerMons_PokemaniacHerman2
    },
    [TRAINER_POKEMANIAC_HERMAN_3] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("HERMAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacHerman3),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacHerman3),
        .party = sTrainerMons_PokemaniacHerman3
    },
    [TRAINER_HIKER_TRENT_2] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("TRENT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerTrent2),
        .initialPartysize = NELEMS(sTrainerMons_HikerTrent2),
        .party = sTrainerMons_HikerTrent2
    },
    [TRAINER_LASS_MEGAN_2] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("MEGAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassMegan2),
        .initialPartysize = NELEMS(sTrainerMons_LassMegan2),
        .party = sTrainerMons_LassMegan2
    },
    [TRAINER_LASS_MEGAN_3] = {
        
        .trainerClass = CLASS_LASS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("MEGAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_LassMegan3),
        .initialPartysize = NELEMS(sTrainerMons_LassMegan3),
        .party = sTrainerMons_LassMegan3
    },
    [TRAINER_SUPER_NERD_GLENN_2] = {
        
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("GLENN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SuperNerdGlenn2),
        .initialPartysize = NELEMS(sTrainerMons_SuperNerdGlenn2),
        .party = sTrainerMons_SuperNerdGlenn2
    },
    [TRAINER_GAMBLER_RICH_2] = {
        
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = _("RICH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_GamblerRich2),
        .initialPartysize = NELEMS(sTrainerMons_GamblerRich2),
        .party = sTrainerMons_GamblerRich2
    },
    [TRAINER_BIKER_JAREN_2] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("JAREN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerJaren2),
        .initialPartysize = NELEMS(sTrainerMons_BikerJaren2),
        .party = sTrainerMons_BikerJaren2
    },
    [TRAINER_FISHERMAN_ELLIOT_2] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("ELLIOT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanElliot2),
        .initialPartysize = NELEMS(sTrainerMons_FishermanElliot2),
        .party = sTrainerMons_FishermanElliot2
    },
    [TRAINER_ROCKER_LUCA_2] = {
        
        .trainerClass = CLASS_ROCKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ROCKER,
        .trainerName = _("LUCA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RockerLuca2),
        .initialPartysize = NELEMS(sTrainerMons_RockerLuca2),
        .party = sTrainerMons_RockerLuca2
    },
    [TRAINER_BEAUTY_SHEILA_2] = {
        
        .trainerClass = CLASS_BEAUTY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("SHEILA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BeautySheila2),
        .initialPartysize = NELEMS(sTrainerMons_BeautySheila2),
        .party = sTrainerMons_BeautySheila2
    },
    [TRAINER_BIRD_KEEPER_ROBERT_2] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("ROBERT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperRobert2),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperRobert2),
        .party = sTrainerMons_BirdKeeperRobert2
    },
    [TRAINER_BIRD_KEEPER_ROBERT_3] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("ROBERT"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperRobert3),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperRobert3),
        .party = sTrainerMons_BirdKeeperRobert3
    },
    [TRAINER_PICNICKER_SUSIE_2] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("SUSIE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerSusie2),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerSusie2),
        .party = sTrainerMons_PicnickerSusie2
    },
    [TRAINER_PICNICKER_SUSIE_3] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("SUSIE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerSusie3),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerSusie3),
        .party = sTrainerMons_PicnickerSusie3
    },
    [TRAINER_PICNICKER_SUSIE_4] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("SUSIE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerSusie4),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerSusie4),
        .party = sTrainerMons_PicnickerSusie4
    },
    [TRAINER_BIKER_LUKAS_2] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("LUKAS"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerLukas2),
        .initialPartysize = NELEMS(sTrainerMons_BikerLukas2),
        .party = sTrainerMons_BikerLukas2
    },
    [TRAINER_BIRD_KEEPER_BENNY_2] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("BENNY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperBenny2),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperBenny2),
        .party = sTrainerMons_BirdKeeperBenny2
    },
    [TRAINER_BIRD_KEEPER_BENNY_3] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("BENNY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperBenny3),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperBenny3),
        .party = sTrainerMons_BirdKeeperBenny3
    },
    [TRAINER_BIRD_KEEPER_MARLON_2] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("MARLON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperMarlon2),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperMarlon2),
        .party = sTrainerMons_BirdKeeperMarlon2
    },
    [TRAINER_BIRD_KEEPER_MARLON_3] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("MARLON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperMarlon3),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperMarlon3),
        .party = sTrainerMons_BirdKeeperMarlon3
    },
    [TRAINER_BEAUTY_GRACE_2] = {
        
        .trainerClass = CLASS_BEAUTY_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("GRACE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BeautyGrace2),
        .initialPartysize = NELEMS(sTrainerMons_BeautyGrace2),
        .party = sTrainerMons_BeautyGrace2
    },
    [TRAINER_BIRD_KEEPER_CHESTER_2] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("CHESTER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperChester2),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperChester2),
        .party = sTrainerMons_BirdKeeperChester2
    },
    [TRAINER_BIRD_KEEPER_CHESTER_3] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("CHESTER"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperChester3),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperChester3),
        .party = sTrainerMons_BirdKeeperChester3
    },
    [TRAINER_PICNICKER_BECKY_2] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("BECKY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerBecky2),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerBecky2),
        .party = sTrainerMons_PicnickerBecky2
    },
    [TRAINER_PICNICKER_BECKY_3] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("BECKY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerBecky3),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerBecky3),
        .party = sTrainerMons_PicnickerBecky3
    },
    [TRAINER_PICNICKER_BECKY_4] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("BECKY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerBecky4),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerBecky4),
        .party = sTrainerMons_PicnickerBecky4
    },
    [TRAINER_CRUSH_KIN_RON_MYA_2] = {
        
        .trainerClass = CLASS_CRUSH_KIN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("RON & MYA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushKinRonMya2),
        .initialPartysize = NELEMS(sTrainerMons_CrushKinRonMya2),
        .party = sTrainerMons_CrushKinRonMya2
    },
    [TRAINER_CRUSH_KIN_RON_MYA_3] = {
        
        .trainerClass = CLASS_CRUSH_KIN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("RON & MYA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushKinRonMya3),
        .initialPartysize = NELEMS(sTrainerMons_CrushKinRonMya3),
        .party = sTrainerMons_CrushKinRonMya3
    },
    [TRAINER_CRUSH_KIN_RON_MYA_4] = {
        
        .trainerClass = CLASS_CRUSH_KIN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("RON & MYA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushKinRonMya4),
        .initialPartysize = NELEMS(sTrainerMons_CrushKinRonMya4),
        .party = sTrainerMons_CrushKinRonMya4
    },
    [TRAINER_BIKER_RUBEN_2] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("RUBEN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerRuben2),
        .initialPartysize = NELEMS(sTrainerMons_BikerRuben2),
        .party = sTrainerMons_BikerRuben2
    },
    [TRAINER_CUE_BALL_CAMRON_2] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("CAMRON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallCamron2),
        .initialPartysize = NELEMS(sTrainerMons_CueBallCamron2),
        .party = sTrainerMons_CueBallCamron2
    },
    [TRAINER_BIKER_JAXON_2] = {
        
        .trainerClass = CLASS_BIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("JAXON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BikerJaxon2),
        .initialPartysize = NELEMS(sTrainerMons_BikerJaxon2),
        .party = sTrainerMons_BikerJaxon2
    },
    [TRAINER_CUE_BALL_ISAIAH_2] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("ISAIAH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallIsaiah2),
        .initialPartysize = NELEMS(sTrainerMons_CueBallIsaiah2),
        .party = sTrainerMons_CueBallIsaiah2
    },
    [TRAINER_CUE_BALL_COREY_2] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("COREY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallCorey2),
        .initialPartysize = NELEMS(sTrainerMons_CueBallCorey2),
        .party = sTrainerMons_CueBallCorey2
    },
    [TRAINER_BIRD_KEEPER_JACOB_2] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("JACOB"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperJacob2),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperJacob2),
        .party = sTrainerMons_BirdKeeperJacob2
    },
    [TRAINER_BIRD_KEEPER_JACOB_3] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("JACOB"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperJacob3),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperJacob3),
        .party = sTrainerMons_BirdKeeperJacob3
    },
    [TRAINER_SWIMMER_FEMALE_ALICE_2] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("ALICE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleAlice2),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleAlice2),
        .party = sTrainerMons_SwimmerFemaleAlice2
    },
    [TRAINER_SWIMMER_MALE_DARRIN_2] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("DARRIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleDarrin2),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleDarrin2),
        .party = sTrainerMons_SwimmerMaleDarrin2
    },
    [TRAINER_PICNICKER_MISSY_2] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("MISSY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerMissy2),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerMissy2),
        .party = sTrainerMons_PicnickerMissy2
    },
    [TRAINER_PICNICKER_MISSY_3] = {
        
        .trainerClass = CLASS_PICNICKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("MISSY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PicnickerMissy3),
        .initialPartysize = NELEMS(sTrainerMons_PicnickerMissy3),
        .party = sTrainerMons_PicnickerMissy3
    },
    [TRAINER_FISHERMAN_WADE_2] = {
        
        .trainerClass = CLASS_FISHERMAN_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("WADE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_FishermanWade2),
        .initialPartysize = NELEMS(sTrainerMons_FishermanWade2),
        .party = sTrainerMons_FishermanWade2
    },
    [TRAINER_SWIMMER_MALE_JACK_2] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("JACK"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleJack2),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleJack2),
        .party = sTrainerMons_SwimmerMaleJack2
    },
    [TRAINER_SIS_AND_BRO_LIL_IAN_2] = {
        
        .trainerClass = CLASS_SIS_AND_BRO_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SIS_AND_BRO,
        .trainerName = _("LIL & IAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SisAndBroLilIan2),
        .initialPartysize = NELEMS(sTrainerMons_SisAndBroLilIan2),
        .party = sTrainerMons_SisAndBroLilIan2
    },
    [TRAINER_SIS_AND_BRO_LIL_IAN_3] = {
        
        .trainerClass = CLASS_SIS_AND_BRO_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SIS_AND_BRO,
        .trainerName = _("LIL & IAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SisAndBroLilIan3),
        .initialPartysize = NELEMS(sTrainerMons_SisAndBroLilIan3),
        .party = sTrainerMons_SisAndBroLilIan3
    },
    [TRAINER_SWIMMER_MALE_FINN_2] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("FINN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleFinn2),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleFinn2),
        .party = sTrainerMons_SwimmerMaleFinn2
    },
    [TRAINER_CRUSH_GIRL_SHARON_2] = {
        
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("SHARON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushGirlSharon2),
        .initialPartysize = NELEMS(sTrainerMons_CrushGirlSharon2),
        .party = sTrainerMons_CrushGirlSharon2
    },
    [TRAINER_CRUSH_GIRL_SHARON_3] = {
        
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("SHARON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushGirlSharon3),
        .initialPartysize = NELEMS(sTrainerMons_CrushGirlSharon3),
        .party = sTrainerMons_CrushGirlSharon3
    },
    [TRAINER_CRUSH_GIRL_TANYA_2] = {
        
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("TANYA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushGirlTanya2),
        .initialPartysize = NELEMS(sTrainerMons_CrushGirlTanya2),
        .party = sTrainerMons_CrushGirlTanya2
    },
    [TRAINER_CRUSH_GIRL_TANYA_3] = {
        
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("TANYA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushGirlTanya3),
        .initialPartysize = NELEMS(sTrainerMons_CrushGirlTanya3),
        .party = sTrainerMons_CrushGirlTanya3
    },
    [TRAINER_BLACK_BELT_SHEA_2] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("SHEA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltShea2),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltShea2),
        .party = sTrainerMons_BlackBeltShea2
    },
    [TRAINER_BLACK_BELT_SHEA_3] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("SHEA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltShea3),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltShea3),
        .party = sTrainerMons_BlackBeltShea3
    },
    [TRAINER_BLACK_BELT_HUGH_2] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("HUGH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltHugh2),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltHugh2),
        .party = sTrainerMons_BlackBeltHugh2
    },
    [TRAINER_BLACK_BELT_HUGH_3] = {
        
        .trainerClass = CLASS_BLACK_BELT_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("HUGH"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BlackBeltHugh3),
        .initialPartysize = NELEMS(sTrainerMons_BlackBeltHugh3),
        .party = sTrainerMons_BlackBeltHugh3
    },
    [TRAINER_CRUSH_KIN_MIK_KIA_2] = {
        
        .trainerClass = CLASS_CRUSH_KIN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("MIK & KIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushKinMikKia2),
        .initialPartysize = NELEMS(sTrainerMons_CrushKinMikKia2),
        .party = sTrainerMons_CrushKinMikKia2
    },
    [TRAINER_CRUSH_KIN_MIK_KIA_3] = {
        
        .trainerClass = CLASS_CRUSH_KIN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("MIK & KIA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushKinMikKia3),
        .initialPartysize = NELEMS(sTrainerMons_CrushKinMikKia3),
        .party = sTrainerMons_CrushKinMikKia3
    },
    [TRAINER_TUBER_AMIRA_2] = {
        
        .trainerClass = CLASS_TUBER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_TUBER_F,
        .trainerName = _("AMIRA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TuberAmira2),
        .initialPartysize = NELEMS(sTrainerMons_TuberAmira2),
        .party = sTrainerMons_TuberAmira2
    },
    [TRAINER_TWINS_JOY_MEG_2] = {
        
        .trainerClass = CLASS_TWINS_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_TWINS,
        .trainerName = _("JOY & MEG"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TwinsJoyMeg2),
        .initialPartysize = NELEMS(sTrainerMons_TwinsJoyMeg2),
        .party = sTrainerMons_TwinsJoyMeg2
    },
    [TRAINER_PAINTER_RAYNA_2] = {
        
        .trainerClass = CLASS_PAINTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = _("RAYNA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PainterRayna2),
        .initialPartysize = NELEMS(sTrainerMons_PainterRayna2),
        .party = sTrainerMons_PainterRayna2
    },
    [TRAINER_YOUNGSTER_DESTIN_2] = {
        
        .trainerClass = CLASS_YOUNGSTER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("DESTIN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungsterDestin2),
        .initialPartysize = NELEMS(sTrainerMons_YoungsterDestin2),
        .party = sTrainerMons_YoungsterDestin2
    },
    [TRAINER_PKMN_BREEDER_ALIZE_2] = {
        
        .trainerClass = CLASS_PKMN_BREEDER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_BREEDER_F,
        .trainerName = _("ALIZE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PkmnBreederAlize2),
        .initialPartysize = NELEMS(sTrainerMons_PkmnBreederAlize2),
        .party = sTrainerMons_PkmnBreederAlize2
    },
    [TRAINER_YOUNG_COUPLE_GIA_JES_2] = {
        
        .trainerClass = CLASS_YOUNG_COUPLE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNG_COUPLE,
        .trainerName = _("GIA & JES"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungCoupleGiaJes2),
        .initialPartysize = NELEMS(sTrainerMons_YoungCoupleGiaJes2),
        .party = sTrainerMons_YoungCoupleGiaJes2
    },
    [TRAINER_YOUNG_COUPLE_GIA_JES_3] = {
        
        .trainerClass = CLASS_YOUNG_COUPLE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_YOUNG_COUPLE,
        .trainerName = _("GIA & JES"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_YoungCoupleGiaJes3),
        .initialPartysize = NELEMS(sTrainerMons_YoungCoupleGiaJes3),
        .party = sTrainerMons_YoungCoupleGiaJes3
    },
    [TRAINER_BIRD_KEEPER_MILO_2] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("MILO"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperMilo2),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperMilo2),
        .party = sTrainerMons_BirdKeeperMilo2
    },
    [TRAINER_BIRD_KEEPER_CHAZ_2] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("CHAZ"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperChaz2),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperChaz2),
        .party = sTrainerMons_BirdKeeperChaz2
    },
    [TRAINER_BIRD_KEEPER_HAROLD_2] = {
        
        .trainerClass = CLASS_BIRD_KEEPER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("HAROLD"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BirdKeeperHarold2),
        .initialPartysize = NELEMS(sTrainerMons_BirdKeeperHarold2),
        .party = sTrainerMons_BirdKeeperHarold2
    },
    [TRAINER_SWIMMER_FEMALE_NICOLE_2] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("NICOLE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleNicole2),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleNicole2),
        .party = sTrainerMons_SwimmerFemaleNicole2
    },
    [TRAINER_PSYCHIC_JACLYN_2] = {
        
        .trainerClass = CLASS_PSYCHIC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = _("JACLYN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PsychicJaclyn2),
        .initialPartysize = NELEMS(sTrainerMons_PsychicJaclyn2),
        .party = sTrainerMons_PsychicJaclyn2
    },
    [TRAINER_SWIMMER_MALE_SAMIR_2] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("SAMIR"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleSamir2),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleSamir2),
        .party = sTrainerMons_SwimmerMaleSamir2
    },
    [TRAINER_HIKER_EARL_2] = {
        
        .trainerClass = CLASS_HIKER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("EARL"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_HikerEarl2),
        .initialPartysize = NELEMS(sTrainerMons_HikerEarl2),
        .party = sTrainerMons_HikerEarl2
    },
    [TRAINER_RUIN_MANIAC_LARRY_2] = {
        
        .trainerClass = CLASS_RUIN_MANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("LARRY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_RuinManiacLarry2),
        .initialPartysize = NELEMS(sTrainerMons_RuinManiacLarry2),
        .party = sTrainerMons_RuinManiacLarry2
    },
    [TRAINER_POKEMANIAC_HECTOR_2] = {
        
        .trainerClass = CLASS_POKEMANIAC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("HECTOR"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PokemaniacHector2),
        .initialPartysize = NELEMS(sTrainerMons_PokemaniacHector2),
        .party = sTrainerMons_PokemaniacHector2
    },
    [TRAINER_PSYCHIC_DARIO_2] = {
        
        .trainerClass = CLASS_PSYCHIC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = _("DARIO"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PsychicDario2),
        .initialPartysize = NELEMS(sTrainerMons_PsychicDario2),
        .party = sTrainerMons_PsychicDario2
    },
    [TRAINER_PSYCHIC_RODETTE_2] = {
        
        .trainerClass = CLASS_PSYCHIC_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = _("RODETTE"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_PsychicRodette2),
        .initialPartysize = NELEMS(sTrainerMons_PsychicRodette2),
        .party = sTrainerMons_PsychicRodette2
    },
    [TRAINER_JUGGLER_MASON_2] = {
        
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("MASON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_JugglerMason2),
        .initialPartysize = NELEMS(sTrainerMons_JugglerMason2),
        .party = sTrainerMons_JugglerMason2
    },
    [TRAINER_PKMN_RANGER_NICOLAS_2] = {
        
        .trainerClass = CLASS_PKMN_RANGER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_M,
        .trainerName = _("NICOLAS"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_PkmnRangerNicolas2),
        .initialPartysize = NELEMS(sTrainerMons_PkmnRangerNicolas2),
        .party = sTrainerMons_PkmnRangerNicolas2
    },
    [TRAINER_PKMN_RANGER_MADELINE_2] = {
        
        .trainerClass = CLASS_PKMN_RANGER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_F,
        .trainerName = _("MADELINE"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_PkmnRangerMadeline2),
        .initialPartysize = NELEMS(sTrainerMons_PkmnRangerMadeline2),
        .party = sTrainerMons_PkmnRangerMadeline2
    },
    [TRAINER_CRUSH_GIRL_CYNDY_2] = {
        
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("CYNDY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CrushGirlCyndy2),
        .initialPartysize = NELEMS(sTrainerMons_CrushGirlCyndy2),
        .party = sTrainerMons_CrushGirlCyndy2
    },
    [TRAINER_TAMER_EVAN_2] = {
        
        .trainerClass = CLASS_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("EVAN"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TamerEvan2),
        .initialPartysize = NELEMS(sTrainerMons_TamerEvan2),
        .party = sTrainerMons_TamerEvan2
    },
    [TRAINER_PKMN_RANGER_JACKSON_2] = {
        
        .trainerClass = CLASS_PKMN_RANGER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_M,
        .trainerName = _("JACKSON"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_PkmnRangerJackson2),
        .initialPartysize = NELEMS(sTrainerMons_PkmnRangerJackson2),
        .party = sTrainerMons_PkmnRangerJackson2
    },
    [TRAINER_PKMN_RANGER_KATELYN_2] = {
        
        .trainerClass = CLASS_PKMN_RANGER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_F,
        .trainerName = _("KATELYN"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_PkmnRangerKatelyn2),
        .initialPartysize = NELEMS(sTrainerMons_PkmnRangerKatelyn2),
        .party = sTrainerMons_PkmnRangerKatelyn2
    },
    [TRAINER_COOLTRAINER_LEROY_2] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("LEROY"),
        .items = {ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerLeroy2),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerLeroy2),
        .party = sTrainerMons_CooltrainerLeroy2
    },
    [TRAINER_COOLTRAINER_MICHELLE_2] = {
        
        .trainerClass = CLASS_COOLTRAINER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("MICHELLE"),
        .items = {ITEM_HYPER_POTION},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CooltrainerMichelle2),
        .initialPartysize = NELEMS(sTrainerMons_CooltrainerMichelle2),
        .party = sTrainerMons_CooltrainerMichelle2
    },
    [TRAINER_COOL_COUPLE_LEX_NYA_2] = {
        
        .trainerClass = CLASS_COOL_COUPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_COOL_COUPLE,
        .trainerName = _("LEX & NYA"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_DOUBLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_CoolCoupleLexNya2),
        .initialPartysize = NELEMS(sTrainerMons_CoolCoupleLexNya2),
        .party = sTrainerMons_CoolCoupleLexNya2
    },
    [TRAINER_BUG_CATCHER_COLTON_2] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("COLTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherColton2),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherColton2),
        .party = sTrainerMons_BugCatcherColton2
    },
    [TRAINER_BUG_CATCHER_COLTON_3] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("COLTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherColton3),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherColton3),
        .party = sTrainerMons_BugCatcherColton3
    },
    [TRAINER_BUG_CATCHER_COLTON_4] = {
        
        .trainerClass = CLASS_BUG_CATCHER_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("COLTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_BugCatcherColton4),
        .initialPartysize = NELEMS(sTrainerMons_BugCatcherColton4),
        .party = sTrainerMons_BugCatcherColton4
    },
    [TRAINER_SWIMMER_MALE_MATTHEW_2] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("MATTHEW"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleMatthew2),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleMatthew2),
        .party = sTrainerMons_SwimmerMaleMatthew2
    },
    [TRAINER_SWIMMER_MALE_TONY_2] = {
        
        .trainerClass = CLASS_SWIMMER_MALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("TONY"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerMaleTony2),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerMaleTony2),
        .party = sTrainerMons_SwimmerMaleTony2
    },
    [TRAINER_SWIMMER_FEMALE_MELISSA_2] = {
        
        .trainerClass = CLASS_SWIMMER_FEMALE_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .gender = TRAINER_GENDER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("MELISSA"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_SwimmerFemaleMelissa2),
        .initialPartysize = NELEMS(sTrainerMons_SwimmerFemaleMelissa2),
        .party = sTrainerMons_SwimmerFemaleMelissa2
    },
    [TRAINER_ELITE_FOUR_LORELEI_2] = {
        
        .trainerClass = CLASS_ELITE_FOUR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_LORELEI,
        .trainerName = _("LORELEI"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_EliteFourLorelei2),
        .initialPartysize = NELEMS(sTrainerMons_EliteFourLorelei2),
        .party = sTrainerMons_EliteFourLorelei2
    },
    [TRAINER_ELITE_FOUR_BRUNO_2] = {
        
        .trainerClass = CLASS_ELITE_FOUR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_BRUNO,
        .trainerName = _("BRUNO"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_EliteFourBruno2),
        .initialPartysize = NELEMS(sTrainerMons_EliteFourBruno2),
        .party = sTrainerMons_EliteFourBruno2
    },
    [TRAINER_ELITE_FOUR_AGATHA_2] = {
        
        .trainerClass = CLASS_ELITE_FOUR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_AGATHA,
        .trainerName = _("AGATHA"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_EliteFourAgatha2),
        .initialPartysize = NELEMS(sTrainerMons_EliteFourAgatha2),
        .party = sTrainerMons_EliteFourAgatha2
    },
    [TRAINER_ELITE_FOUR_LANCE_2] = {
        
        .trainerClass = CLASS_ELITE_FOUR_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_LANCE,
        .trainerName = _("LANCE"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_EliteFourLance2),
        .initialPartysize = NELEMS(sTrainerMons_EliteFourLance2),
        .party = sTrainerMons_EliteFourLance2
    },
    [TRAINER_CHAMPION_REMATCH_SQUIRTLE] = {
        
        .trainerClass = CLASS_CHAMPION_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_RIVAL,
        .trainerName = _("TERRY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_ChampionRematchSquirtle),
        .initialPartysize = NELEMS(sTrainerMons_ChampionRematchSquirtle),
        .party = sTrainerMons_ChampionRematchSquirtle
    },
    [TRAINER_CHAMPION_REMATCH_BULBASAUR] = {
        
        .trainerClass = CLASS_CHAMPION_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_RIVAL,
        .trainerName = _("TERRY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_ChampionRematchBulbasaur),
        .initialPartysize = NELEMS(sTrainerMons_ChampionRematchBulbasaur),
        .party = sTrainerMons_ChampionRematchBulbasaur
    },
    [TRAINER_CHAMPION_REMATCH_CHARMANDER] = {
        
        .trainerClass = CLASS_CHAMPION_FRLG,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_RIVAL,
        .trainerName = _("TERRY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY,
        .partySize = NELEMS(sTrainerMons_ChampionRematchCharmander),
        .initialPartysize = NELEMS(sTrainerMons_ChampionRematchCharmander),
        .party = sTrainerMons_ChampionRematchCharmander
    },
    [TRAINER_CUE_BALL_PAXTON] = {
        
        .trainerClass = CLASS_CUE_BALL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .gender = TRAINER_GENDER_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("PAXTON"),
        .items = {},
        .battleType = TRAINER_BATTLE_TYPE_SINGLES,
        .aiFlags = AI_FLAG_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_CueBallPaxton),
        .initialPartysize = NELEMS(sTrainerMons_CueBallPaxton),
        .party = sTrainerMons_CueBallPaxton
    },
};
