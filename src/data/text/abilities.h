#include "config.h"

static const u8 sNoneDescription[] = _("No special ability.");
static const u8 sStenchDescription[] = _("Can repel wild POKéMON and trainers.\nAll battlers have a chance to flinch.");
static const u8 sDrizzleDescription[] = _("Summons rain in battle.");
static const u8 sSpeedBoostDescription[] = _("Gradually boosts SPEED.");
static const u8 sBattleArmorDescription[] = _("Blocks critical hits.");
static const u8 sSturdyDescription[] = _("Negates 1-hit KO moves.\nResists moves that would otherwise OHKO.");
static const u8 sDampDescription[] = _("Dampens area preventing explosions.\nAnd weakens incoming Fire damage.");
static const u8 sLimberDescription[] = _("Prevents paralysis.");
static const u8 sSandVeilDescription[] = _("Ups evasion in a sandstorm.");
static const u8 sStaticDescription[] = _("May Paralyze on contact.");
static const u8 sVoltAbsorbDescription[] = _("Turns incomming electric damage into HP.");
static const u8 sWaterAbsorbDescription[] = _("Turns incomming water damage into HP.\nSlight HP recovery in rain and fog.");
static const u8 sObliviousDescription[] = _("Prevents attraction.\nBlocks Intimidate, Taunt, and Torment.");
static const u8 sCloudNineDescription[] = _("Blocks all negative weather effects for\nthe user and most effects for the team."); //to get more benefit/synergy think will make it side based
static const u8 sCompoundEyesDescription[] = _("Raises accuracy.");
static const u8 sInsomniaDescription[] = _("Prevents sleep.");
static const u8 sColorChangeDescription[] = _("Changes secondary type\nto match last move hit by.");
static const u8 sImmunityDescription[] = _("Prevents poisoning.");
static const u8 sFlashFireDescription[] = _("Draws in and powers up fire moves");
static const u8 sShieldDustDescription[] = _("Protective dust shields the Pokémon\nfrom the additional effects of moves.");
static const u8 sOwnTempoDescription[] = _("Prevents confusion.\nBlocks Intimidate, Taunt, and Torment.");
static const u8 sSuctionCupsDescription[] = _("Firmly anchors itself, stops force switch.\nTrap move effects last longer.");
static const u8 sIntimidateDescription[] = _("Lowers the foe's ATTACK.");
static const u8 sShadowTagDescription[] = _("Prevents non-ghost foes from escaping.\nAlso drops their speed.");
static const u8 sRoughSkinDescription[] = _("Hurts to make contact.");
static const u8 sWonderGuardDescription[] = _("“Super effective” hits.\nIgnores most other damage for 4 turns.");
static const u8 sFemmeFataleDescription[] = _("Immune to Infatuation and Intimidation.\nAlso blocks Flinch, Taunt, and Torment.");
static const u8 sEffectSporeDescription[] = _("Leaves spores on contact.\nSpores apply a variety of statuses.");
static const u8 sSynchronizeDescription[] = _("Passes on status problems.");
static const u8 sClearBodyDescription[] = _("Prevents stat reduction.");
static const u8 sNaturalCureDescription[] = _("Heals status upon switching out.");
static const u8 sLightningRodDescription[] = _("Draws in electrical moves.\nAlso raises Sp. Atk one stage.");
static const u8 sSereneGraceDescription[] = _("Increases chance of added effects.");
static const u8 sSwiftSwimDescription[] = _("Raises SPEED in rain.");
static const u8 sChlorophyllDescription[] = _("Raises SPEED in sunshine.");
static const u8 sIlluminateDescription[] = _("Encounter rate increases.\nRaises accuracy and enables Flash.");
static const u8 sTraceDescription[] = _("Copies special ability.");
static const u8 sHugePowerDescription[] = _("Raises ATTACK double.");
static const u8 sPoisonPointDescription[] = _("Contact with the Pokémon\nmay poison the attacker.");
static const u8 sInnerFocusDescription[] = _("Focuses intensely to prevent Flinching,\nCritical Hits, and Intimidation.");
static const u8 sMagmaArmorDescription[] = _("Prevents freezing, burns items on contact\nboosts Sp.Def and blocks physical crits."); //has added effects to include here ...I may have gone overboard
static const u8 sWaterVeilDescription[] = _("Prevents burns.");
static const u8 sMagnetPullDescription[] = _("Traps STEEL-type POKéMON with magnetism\nAlso drops their speed.");
static const u8 sSoundproofDescription[] = _("Avoids sound-based moves.");
static const u8 sRainDishDescription[] = _("Moderate HP recovery in rain.");
static const u8 sSandStreamDescription[] = _("Summons a sandstorm.");
static const u8 sPressureDescription[] = _("Raises foe's PP usage.\nMay make foe too afraid to attack well.");
static const u8 sThickFatDescription[] = _("Reduces Heat-and-cold effectiveness.");
static const u8 sEarlyBirdDescription[] = _("Awakens quickly from sleep, refreshed.\nCleanses stat drops on awaken."); //buffed gave chance to immediately wake
static const u8 sFlameBodyDescription[] = _("May cause Burn on contact.\nCan't be frozen and hatches eggs faster.");
static const u8 sRunAwayDescription[] = _("Makes escaping easier.\nPrevents loss of speed except from traps.");
static const u8 sKeenEyeDescription[] = _("Prevents loss of accuracy. Slightly\nboosts Acc and ignores evasion changes.");
static const u8 sHyperCutterDescription[] = _("Prevents ATTACK reduction.");
static const u8 sPickupDescription[] = _("May pick up items.");
static const u8 sTruantDescription[] = _("Only moves every other turn.\nBut heals while at rest.");
static const u8 sHustleDescription[] = _("Trades a small accuracy drop for power.\n5% accuracy drop for 50% Atk boost.");
static const u8 sCuteCharmDescription[] = _("May Infatuate on contact.\nAlways Infatuates when hit.");
static const u8 sPlusDescription[] = _("Boost Sp.Atk. if MINUS or Elec. on field.\nPwr up if Elec./MINUS ally is in a pinch");
static const u8 sMinusDescription[] = _("Boost Sp.Atk. if PLUS or Elec. on field.\nPwr up when Elec./PLUS ally is in a pinch");
static const u8 sForecastDescription[] = _("Predicts, the coming weather.\nWeather extenders enhance prediction."); //since giving to non castform consider tweak a bit more, put some effects on just castform like weather drop immunity
static const u8 sStickyHoldDescription[] = _("Prevents item theft.\nAbsorbs foe's item on contact.");
static const u8 sShedSkinDescription[] = _("Heals the body by shedding.\nMay attempt to cure status."); //added comatose heal on top
static const u8 sGutsDescription[] = _("Ups ATTACK if suffering from status.");
static const u8 sMarvelScaleDescription[] = _("Ups DEFENSE if suffering from status.");
static const u8 sLiquidOozeDescription[] = _("Draining causes injury.");
static const u8 sOvergrowDescription[] = _("Ups GRASS moves in a pinch.");
static const u8 sBlazeDescription[] = _("Ups FIRE moves in a pinch.");
static const u8 sTorrentDescription[] = _("Ups WATER moves in a pinch.");
static const u8 sSwarmDescription[] = _("Ups BUG moves in a pinch.");
static const u8 sRockHeadDescription[] = _("Prevents recoil damage.\nBoosts headbutt moves.");
static const u8 sDroughtDescription[] = _("Summons sunlight in battle.");
static const u8 sArenaTrapDescription[] = _("Stops grounded foe from fleeing.\nAlso drops their speed. +Encounter rate");
static const u8 sVitalSpiritDescription[] = _("Prevents sleep.");
static const u8 sWhiteSmokeDescription[] = _("Prevents stat drops by foes.");
static const u8 sPurePowerDescription[] = _("Raises ATTACK.");
static const u8 sShellArmorDescription[] = _("Blocks critical hits.");
static const u8 sTangledFeetDescription[] = _("Ups evasion, speed, and avoids crits\nif confused. Prevents loss of speed."); //drunken fist type deal /put w bug immunity so doesn't hit itself
static const u8 sMotorDriveDescription[] = _("Raises speed if hit by Electricity.");
static const u8 sRivalryDescription[] = _("Powers up against same gender opponents.");
static const u8 sSteadfastDescription[] = _("Determination raises speed on flinch\nor taking “Super effective” hits.");
static const u8 sSnowCloakDescription[] = _("Ups evasion in Hail.");
static const u8 sGluttonyDescription[] = _("Eats Berries early.");
static const u8 sAngerPointDescription[] = _("Raises attack if hit by “Critical” hits,\n“Super effective” hits, or Intimidated.");
static const u8 sUnburdenDescription[] = _("Using a hold item ups Speed.");
static const u8 sHeatproofDescription[] = _("Lowers effectiveness of Fire and burn.");
static const u8 sSimpleDescription[] = _("Prone to wild stat changes.");
static const u8 sDrySkinDescription[] = _("Takes slight Dmg in Sun absorbs water.\nHeals in rain/fog, takes more Fire Dmg."); //removed sunlight hp drop,...added back
static const u8 sDownloadDescription[] = _("Adjusts offensive power favorably,\nto foe's defenses.");
static const u8 sIronFistDescription[] = _("Boosts Punching moves.");
static const u8 sPoisonHealDescription[] = _("Heals if poisoned or PSN-type holds\na toxic item. Also clears toxic spikes."); //may come up with better description absorb toxi spikes poison type heal effect
static const u8 sAdaptabilityDescription[] = _("Boosts same type attacks.");
static const u8 sSkillLinkDescription[] = _("Multi-hit moves hit 5 times.\nOnly first hit gets accuracy check.");
static const u8 sHydrationDescription[] = _("Cures status ailments and other\nnegative effects in rain."); //buffs still in works
static const u8 sSolarPowerDescription[] = _("Powers up in sunshine. Boosting Sp. Atk.\nBut is hurt by its uncontrollable power.");
static const u8 sQuickFeetDescription[] = _("Ups Speed if statused or Intimdated.\nPrevents loss of speed except from traps.");
static const u8 sNormalizeDescription[] = _("PKMN exudes a completely average aura.\nAll moves become True Normal.");
static const u8 sSniperDescription[] = _("Boosts critical hits.");
static const u8 sMagicGuardDescription[] = _("Only damaged by attacks\nand ignores indirect damage.");
static const u8 sNoGuardDescription[] = _("Ensures that all moves used by\nand against the user hit.");
static const u8 sStallDescription[] = _("Damaging moves go last sans Trick Room.\nIt bides its time to greatly boost power.");//think change make only affect dmging moves? need extra descriptives as people want expect it or be expected to test
static const u8 sTechnicianDescription[] = _("Boosts weaker moves.");
static const u8 sLeafGuardDescription[] = _("Prevents stat drop by hiding in leaves.\nAlso blocks status problems in sunshine.");
static const u8 sKlutzDescription[] = _("Can't use hold items, but takes less\nphysical dmg. Prevents recoil damage.");
static const u8 sMoldBreakerDescription[] = _("Moves ignore ability affects,\ninnate effects and affinities.");
static const u8 sSuperLuckDescription[] = _("Critical hits land more often.");
static const u8 sAftermathDescription[] = _("Contact hurts on faint and lowers speed.\nAlso does reduced effects on switch.");
static const u8 sAnticipationDescription[] = _("Senses danger via instinct or nature.\nEnables the Pokémon to avoid danger once");
static const u8 sForewarnDescription[] = _("Predicts a foe's move with psychic power.\nAvoids an attack from said foe once.");
static const u8 sUnawareDescription[] = _("Ignores stat changes for dmg and acc.\nBlocks Intimidate, Taunt, and Torment.");
static const u8 sTintedLensDescription[] = _("Ups damage if move's type is resisted.");
static const u8 sFilterDescription[] = _("Weakens incoming “Super effective”\nmoves.");
static const u8 sSlowStartDescription[] = _("Takes a while to get going.\nClears all ailments upon power awakening.");
static const u8 sScrappyDescription[] = _("Attacks bypass immunities of Ghost-type\nPokémon to deal neutral damage.");
static const u8 sStormDrainDescription[] = _("Draws in Water moves.\nBoosting Sp.Attack.");
static const u8 sIceBodyDescription[] = _("Slight HP recovery in Hail.");
static const u8 sSnowWarningDescription[] = _("Summons a hailstorm.");
static const u8 sHoneyGatherDescription[] = _("May gather Honey gives off a sweet scent\nRecovers a little HP if holding Honey.");
static const u8 sFriskDescription[] = _("Checks the foes' item. Also raises\nchance of extra effects on contact.");
static const u8 sRecklessDescription[] = _("Boosts moves with recoil.");
static const u8 sMultitypeDescription[] = _("The Omnipotent One.\nIs every type.");
static const u8 sFlowerGiftDescription[] = _("Transforms in sunshine.");
static const u8 sBadDreamsDescription[] = _("Damages sleeping Pokémon.");
static const u8 sPickpocketDescription[] = _("Braces itself, to steal the foe's\nheld item when they make contact.");
static const u8 sMagicianDescription[] = _("Steals foe's item when it does dmg."); //figure out better description
static const u8 sSheerForceDescription[] = _("Trades extra move effects for power.");
static const u8 sContraryDescription[] = _("Inverts stat changes.");
static const u8 sUnnerveDescription[] = _("Foes can't eat Berries.\nAlso raises their PP usage.");
static const u8 sDefiantDescription[] = _("Ups Attack if stats lowered.\nOr if suffering from status.");
static const u8 sDefeatistDescription[] = _("Lowers offense and gives up at half HP.\nRaises speed to make escaping easier.");
static const u8 sCursedBodyDescription[] = _("Disables moves on contact.");
static const u8 sHealerDescription[] = _("If partner is statused, may attempt to\nheal them. Cures status.");
static const u8 sFriendGuardDescription[] = _("Lowers damage to partner.");
static const u8 sWeakArmorDescription[] = _("When hit with a physical attack\nlowers defense and sharply raises speed.");
static const u8 sHeavyMetalDescription[] = _("Doubles weight.\nBoosts power of STEEL moves.");
static const u8 sLightMetalDescription[] = _("Halves weight.\nRaises priority of STEEL moves.");
static const u8 sMultiscaleDescription[] = _("Halves damage taken at full HP.");
static const u8 sToxicBoostDescription[] = _("Ups Attack if poisoned or has Toxic orb.\nAnd ignores poison damage.");
static const u8 sFlareBoostDescription[] = _("Ups Sp. Atk if burned or has Flame orb.\nAnd ignores burn damage.");
static const u8 sHarvestDescription[] = _("May recycle a used Berry.\nGuaranteed recycle in sunny weather."); //this is good
static const u8 sTelepathyDescription[] = _("Can't be damaged by an ally.");
static const u8 sMoodyDescription[] = _("Stats change gradually.");
static const u8 sOvercoatDescription[] = _("Blocks weather damage and powder effects");
static const u8 sPoisonTouchDescription[] = _("May poison a target when the Pokémon\nmakes contact.");
static const u8 sBigPecksDescription[] = _("Prevents Attack and Defense drop\nfrom external effects.");
static const u8 sSandRushDescription[] = _("Ups Speed in a sandstorm.");
static const u8 sWonderSkinDescription[] = _("May avoid status problems.");
static const u8 sAnalyticDescription[] = _("Moving last boosts power.");
static const u8 sIllusionDescription[] = _("Appears as a partner.");
static const u8 sImposterDescription[] = _("Transforms into the foe.");
static const u8 sInfiltratorDescription[] = _("Stealthily bypasses barriers and walls.\nAlso bypasses Substitute and Disguise.");//adjust for non ghost stealthily bypasses walls and barriers
static const u8 sMummyDescription[] = _("Spreads with contact.\nOverwrites the attackers ability.");
static const u8 sMoxieDescription[] = _("KOs raise Attack.");
static const u8 sJustifiedDescription[] = _("Raises Attack if Intimidated\nor hit by Dark or Ghost moves.");
static const u8 sBraveryDescription[] = _("Raises Sp. Attack if Intimidated\nor hit by Dark or Ghost moves.");
static const u8 sRattledDescription[] = _("Raises Speed if Intimdated or\nhit by Dark, Bug, or Ghost moves.");
static const u8 sMagicBounceDescription[] = _("Reflects status moves and non-redirected\nstat decreases from abilities."); //reflects intimidate likes, gave small bit of mirror armor effect
static const u8 sSapSipperDescription[] = _("Draws in Grass moves\nto increase Attack.");
static const u8 sPranksterDescription[] = _("Status moves get a priority boost.");
static const u8 sSandForceDescription[] = _("Powers up in a sandstorm.");
static const u8 sZenModeDescription[] = _("Transforms at half HP.");
static const u8 sVictoryStarDescription[] = _("Raises party accuracy and speed.");
static const u8 sAromaVeilDescription[] = _("Protects itself and allies from effects\nthat prevent the use of moves."); //("Prevents limiting of moves.");
static const u8 sFlowerVeilDescription[] = _("Protects Grass-types on user's side\nfrom status and stat changing effects.");
static const u8 sCheekPouchDescription[] = _("Eating Berries restores HP.\nCan Belch without eating a berry.");
static const u8 sProteanDescription[] = _("Changes type to used move.");
static const u8 sFurCoatDescription[] = _("Raises Defense.");
static const u8 sBulletproofDescription[] = _("Avoids some projectiles.");
static const u8 sCompetitiveDescription[] = _("Ups Sp. Atk. if stats lowered.\nOr if suffering from status.");
static const u8 sStrongJawDescription[] = _("Boosts biting moves.");
static const u8 sRefrigerateDescription[] = _("Normal moves become Ice.");
static const u8 sSweetVeilDescription[] = _("Protects party from sleep.");
static const u8 sStanceChangeDescription[] = _("Transforms as it battles.");
static const u8 sGaleWingsDescription[] = _("Flying moves get a priority boost\nwhen at above 50% HP.");
static const u8 sMegaLauncherDescription[] = _("Boosts pulse moves.");
static const u8 sGrassPeltDescription[] = _("Also blocks critical hits.\nUps Defense when on grassy terrain.");
static const u8 sSymbiosisDescription[] = _("Passes its item to an ally.");
static const u8 sToughClawsDescription[] = _("Boosts contact moves.");
static const u8 sPixilateDescription[] = _("Normal and Sound moves become Fairy.");
static const u8 sGooeyDescription[] = _("Lowers Speed on contact.");
static const u8 sAerilateDescription[] = _("Normal moves become Flying.");
static const u8 sParentalBondDescription[] = _("Moves hit twice.");
static const u8 sDarkAuraDescription[] = _("Boosts Dark moves.");
static const u8 sFairyAuraDescription[] = _("Boosts Fairy moves.");
static const u8 sAuraBreakDescription[] = _("Reverse aura abilities.\nWeakens Dark and Fairy moves."); //buffed aura break to actually be useful
static const u8 sPrimordialSeaDescription[] = _("Summons heavy rain.");
static const u8 sDesolateLandDescription[] = _("Summons intense sunlight.");
static const u8 sDeltaStreamDescription[] = _("Summons strong winds.");
static const u8 sStaminaDescription[] = _("Boosts Defense when hit.");
static const u8 sWimpOutDescription[] = _("Flees if HP below half after attacking.");
static const u8 sWaterCompactionDescription[] = _("Water attacks sharply boosts Defense.\nSligthtly resists water damage.");
static const u8 sMercilessDescription[] = _("Deals critical damage to poisoned foes.");
static const u8 sShieldsDownDescription[] = _("If HP above 50% boosts Def blocks status\nWhen below, shell breaks and boosts atk.");
static const u8 sStakeoutDescription[] = _("2x damage if targets switched in mid turn\n50% boost to foes replacing fainted ally"); //vsonic fix description    //Stakeout doubles the power of moves used against targets switched in mid turn.
static const u8 sWaterBubbleDescription[] = _("Reduces Fire damage and prevents burns.\nBoosts power of user water moves."); //^ability still sucks, change to just switched in, so can get boost on turn fainted mon is replaced as well, just keep to mostly weakish mon
static const u8 sSteelworkerDescription[] = _("Powers up Steel moves.");
static const u8 sBerserkDescription[] = _("Boosts the Pokémon's Sp. Atk if\nan attack drops its HP to half or less.");
static const u8 sSlushRushDescription[] = _("Raises Speed in hail.");
static const u8 sLongReachDescription[] = _("Never makes contact. Boosts priority\nof non-contact physical moves.");
static const u8 sLiquidVoiceDescription[] = _("Makes sound moves become Water Type.");
static const u8 sTriageDescription[] = _("Healing moves get a priority boost.");
static const u8 sGalvanizeDescription[] = _("Normal moves become Electric and\ngain a boost in power.");
static const u8 sSurgeSurferDescription[] = _("Faster on electric terrain.");
static const u8 sSchoolingDescription[] = _("Heals on switch, and forms together\nif lvl. 20+ and above a quarter Max HP");
static const u8 sDisguiseDescription[] = _("Decoy protects it once.");
static const u8 sBattleBondDescription[] = _("Changes form after a KO.");
static const u8 sPowerConstructDescription[] = _("Cells aid it when weakened.");
static const u8 sCorrosionDescription[] = _("Able to Poison any type\neven if otherwise immune.");
static const u8 sComatoseDescription[] = _("Always drowsing.\nRecovers HP slightly each turn.");
static const u8 sQueenlyMajestyDescription[] = _("Blocks boosted priority moves\nfor itself and allies and Intimidate."); //see gen 9 this applies to use and allies
static const u8 sDazzlingDescription[] = _("Blocks boosted priority moves\nfor itself and allies.");
static const u8 sInnardsOutDescription[] = _("On faint hurts foe for last hp dmg dealt.\nIf damaged on switch-in strikes back.");
static const u8 sDancerDescription[] = _("Dances along with others.\nUses Dance Move right after previous user");
static const u8 sBatteryDescription[] = _("Boosts ally's Sp. Atk."); //vsonic think idea was turn this into vikavolt version of tatsugiri dondozo effect
static const u8 sFluffyDescription[] = _("Takes increased damage from FIRE moves.\nTakes reduced damage from contact moves.");
static const u8 sSoulHeartDescription[] = _("KOs raise Sp. Atk.");
static const u8 sReceiverDescription[] = _("Copies ally's ability.");
static const u8 sBeastBoostDescription[] = _("KOs boost the Pokémon's best stat.");
static const u8 sRKSSystemDescription[] = _("Memories change its type.");
static const u8 sElectricSurgeDescription[] = _("Field becomes Electric. Ups Elec. moves\nand prevents grounded from sleeping.");
static const u8 sPsychicSurgeDescription[] = _("Field becomes weird. Ups Psych. moves\nNon-spread prio. moves fail on grounded.");
static const u8 sMistySurgeDescription[] = _("Field becomes misty. Weaken Dragon moves\nBoosts attack recovery & blocks statusing");
static const u8 sGrassySurgeDescription[] = _("Field becomes grassy. Ups Grass moves.\nSlight HP recovery for grounded Pokémon.");
static const u8 sFullMetalBodyDescription[] = _("Prevents stat reduction.");
static const u8 sNeuroforceDescription[] = _("Ups power of “supereffective” moves.");
static const u8 sIntrepidSwordDescription[] = _("The Hero arrives!\nUps Attack for one turn on entry.");
static const u8 sDauntlessShieldDescription[] = _("The Hero arrives!\nUps Defense for one turn on entry.");
static const u8 sLiberoDescription[] = _("Changes type to move's.");
static const u8 sBallFetchDescription[] = _("May Fetch failed Poké Balls back to bag.\nImmediately returns Ball Moves to user.");
static const u8 sCottonDownDescription[] = _("Lower Speed of all when hit.");
static const u8 sPropellerTailDescription[] = _("Ignores foe's redirection.");
static const u8 sMirrorArmorDescription[] = _("Reflect stat decreases back to the user.");
static const u8 sGulpMissileDescription[] = _("If hit, spits prey caught in its mouth.");
static const u8 sStalwartDescription[] = _("Ignores foe's redirection.");
static const u8 sSteamEngineDescription[] = _("Fire or Water hits up Speed.\nAlso shortens Egg Hatch Time.");
static const u8 sPunkRockDescription[] = _("Ups and resists sound attacks.");
static const u8 sSandSpitDescription[] = _("Creates a sandstorm if hit.");
static const u8 sIceScalesDescription[] = _("Halves special damage.");
static const u8 sRipenDescription[] = _("Doubles effect of Berries.");
static const u8 sIceFaceDescription[] = _("Take a free hit. Hail renews this ability.");
static const u8 sPowerSpotDescription[] = _("Powers up ally moves.");
static const u8 sMimicryDescription[] = _("Changes type on terrain.");
static const u8 sScreenCleanerDescription[] = _("Removes walls of light.");
static const u8 sSteelySpiritDescription[] = _("Boosts user's and ally's Steel moves.");
static const u8 sPerishBodyDescription[] = _("Foe faints in 3 turns if hit.");
static const u8 sWanderingSpiritDescription[] = _("Trade abilities on contact.");
static const u8 sGorillaTacticsDescription[] = _("Ups Attack and Sp.Attack but locks moves");
static const u8 sNeutralizingGasDescription[] = _("Opponent Abilities are nullified.");
static const u8 sPastelVeilDescription[] = _("Protects team from poison.");
static const u8 sHungerSwitchDescription[] = _("Changes form each turn.");;
static const u8 sQuickDrawDescription[] = _("Moves first occasionally.");
static const u8 sUnseenFistDescription[] = _("Contact moves at or below 75 power\nevades protection.");
static const u8 sCuriousMedicineDescription[] = _("Remove ally's stat changes.");
static const u8 sTransistorDescription[] = _("Ups Electric-type moves by 30 percent.");
static const u8 sDragonsMawDescription[] = _("Ups Dragon-type moves by 50 percent.");
static const u8 sChillingNeighDescription[] = _("KOs boost Attack stat.");
static const u8 sGrimNeighDescription[] = _("KOs boost Sp. Atk stat.");
static const u8 sAsOneIceRiderDescription[] = _("Unnerve and Chilling Neigh.");
static const u8 sAsOneShadowRiderDescription[] = _("Unnerve and Grim Neigh.");
static const u8 sAirLockDescription[] = _("Negates weather effects.");
static const u8 sDispiritGuardDescription[] = _("“Not very effective” hits.");
static const u8 sNuisanceDescription[] = _("“Weak attacks” get a priority boost.\nExcludes variable power moves.");
static const u8 sMultiTaskDescription[] = _("Damaging Attacks are multi-hit.\nMulti-hit moves hit 5 times.");
static const u8 sSiroccoDescription[] = _("Kicks up a sandstorm on contact.");
static const u8 sHipressureDescription[] = _("Sharply raises foe's PP usage.\nMay make foe too afraid to attack well.");
static const u8 sCupidsArrowDescription[] = _("Infatuates foes upon switching in.");
static const u8 sBattleMatronDescription[] = _("Powers up moves to protect young PKMN.\nBoost damage if ally not fully evolved.");
static const u8 sOceanMemoryDescription[] = _("Recalls a time it dwelled in the sea.\nReduces Damage from Water-type moves.");
static const u8 sLiquidSoulDescription[] = _("Turns users Water moves into Ghost moves\nand is immune to Water dmg."); //needed extra effects to make viable
static const u8 sOverchargeDescription[] = _("Ups ELECTRIC moves in a pinch.\nThe POKéMON charges up to the max!");
static const u8 sPhotosynthesizeDescription[] = _("Moderate HP recovery in sun.");
static const u8 sGlacialIceDescription[] = _("Is immune to fire,\nand turns ice and hail into hp.");
static const u8 sLavaFissureDescription[] = _("Draws in and powers up fire moves\nPrevents Freeze, field becomes scorched.");
static const u8 sToadstoolNymphDescription[] = _("Add STAB on FAIRY moves. A fae blessing\ngiven for devotion to nature.");
static const u8 sUnknownPowerDescription[] = _("A mysterious ability from the unown\ndimension, doubles power when with unown");
static const u8 sPurifyingAuraDescription[] = _("Status heal.The POKéMON flares its aura\npurifying itself and allies in reach.");
static const u8 sSquallDescription[] = _("Summons a rain shower,\nthat temporarily drenches the field.");
static const u8 sSundiskDescription[] = _("The POKéMON gives thanks to the sun.\nTemporarily boosting sunlight in battle.");
static const u8 sToughSpinesDescription[] = _("Stabs the foe with thorn like spines\non contact.");
static const u8 sErosionDescription[] = _("Breaks down incoming Rock-type attacks,\nand uses the minerals to heal itself.");
static const u8 sLiquidmetalDescription[] = _("A strange light-weight body, immune to\nstat reduction that resists physical dmg");
static const u8 sMusclemagicDescription[] = _("Special moves become Physical contact.\nControl the elements with pure Muscle!");
static const u8 sTigercubDescription[] = _("To rise to the high expectations\nof the pride. Ups resisted move dmg.");
static const u8 sTigerMomDescription[] = _("Postures with an overbearing presence.\nLowers the foe's DEFENSE.");
static const u8 sDarkDealDescription[] = _("Increases crit and effect chance. Halves\npartner's 80+ pwr moves to share ability."); //vsonic looks good not accurate as it doubels effect for partner
static const u8 sCorruptionDescription[] = _("The user's corrupted influence spreads\ndecay. Preventing the foe from healing.");
static const u8 sBanditKingDescription[] = _("This POKéMON posesses a covetous nature.\nIt won't let its targets use items.");
static const u8 sAviatorDescription[] = _("An uncontested ace that always escapes.\nStops speed loss, gains FLYING Affinity.");//Gains FLYING type benefits. flying type runnaway
static const u8 sUsurperDescription[] = _("Ups Atk and Sp. Atk. if stats lowered\nor if suffering from status.");
static const u8 sInverseWorldDescription[] = _("Inverts incoming damage,\nand resisted or immune attacks.");
static const u8 sSonarDescription[] = _("Emits infrasonic sound with each attack.\nBoosts sound based move damage by 1.5x");
static const u8 sEcosystemDescription[] = _("Makes Grass resist Ice damage.\nSets third type to water.");
static const u8 sAbsolutezeroDescription[] = _("Makes Dragon resist Ice damage.\nFreezes all Water-type moves.");
static const u8 sFeatherJacketDescription[] = _("Protected from the cold by\na jacket of downy feathers.");
static const u8 sPoisonedLegacyDescription[] = _("Can ignore PSN Imm/Rst. In a pinch ups\nPSN & ensures toxic if move can poison."); //ugly as hell but only way could fit all effets...
static const u8 sJewelMetabolismDescription[] = _("Consumes Rock-type moves.\nAlso raises Defense one stage.");
static const u8 sInversionDescription[] = _("Transforms into a copy that resists\nthe type of the foe.");
static const u8 sWetikoDescription[] = _("The Wendigo curse, all moves become Ice.\nHeals upon switching out.");
static const u8 sEmpathDescription[] = _("Passes on status problems.\nAs well as stat reductions.");
static const u8 sEmpathicCurseDescription[] = _("Passes on status problems.\nAnd a portion of its pain as damage.");
static const u8 sInthrallDescription[] = _("When the PKMN hits the foe with a move\nit seals their memory disabling a move.");
static const u8 sIronWillDescription[] = _("May make enemy too fearful to attack\nor unable to use their full strength.");
static const u8 sLivewireDescription[] = _("Body made of electricity\nUps damage of electric moves.");
static const u8 sGaleforceDescription[] = _("Immune to wind-based moves\nBoosts Sp. Atk when hit by them.");
static const u8 sLethalLegsDescription[] = _("Boosts Kicking moves.");
static const u8 sToxungueDescription[] = _("Strikes foe with toxungen covered tongue\nMay Paralyze on contact.");
static const u8 sOmnipotentAideDescription[] = _("Gives priority to healing effects.\nBut can only heal allies not itself.");
static const u8 sFluorescenceDescription[] = _("Naturally absorbs sunlight.\nBoosts speed and Sp.Atk in sun.");

static const u8 sPlagueWingsDescription[] = _("Spreads powder-like scales on attack.\nThat apply a variety of statuses.");
static const u8 sPhantomTouchDescription[] = _("Contact moves ignore the immunities\nof GHOST types.");
//checked in fire red limit is 40 chars per line, changing description length to 80/    changed to 82 max
//based on suction cups I kinda have more space?  so more like 41 per line?
//template - top line: literal effect\n bottom line: flavor text    -flipped usually put flavor text on top, effect on bottom
//if you can't cleanly do a mix of both. over the full space
//*note if ability text extends over the line i.e more than 40 chars on a line,
//even if max is below total limit causes a overflow glitch, that corrupts summary screen data

const struct AbilityInfo gAbilitiesInfo[ABILITIES_COUNT] =
{
    [ABILITY_NONE] =
    {
        .name = _("-------"),
        .description = COMPOUND_ABILITY_STRING("No special ability."),
        .aiRating = 0,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STENCH] =
    {
        .name = _("Stench"),
        .description = sStenchDescription,
        .aiRating = 4,
    },

    [ABILITY_DRIZZLE] =
    {
        .name = _("Drizzle"),
        .description = sDrizzleDescription,
        .aiRating = 9,
    },

    [ABILITY_SPEED_BOOST] =
    {
        .name = _("Speed Boost"),
        .description = sSpeedBoostDescription,
        .aiRating = 9,
    },

    [ABILITY_BATTLE_ARMOR] =
    {
        .name = _("Battle Armor"),
        .description = sBattleArmorDescription,
        .aiRating = 2,
        .breakable = TRUE,
    },
    //suprised this only a two

    [ABILITY_STURDY] =
    {
        .name = _("Sturdy"),
        .description = sSturdyDescription,
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DAMP] =
    {
        .name = _("Damp"),
        .description = sDampDescription,
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_LIMBER] =
    {
        .name = _("Limber"),
        .description = sLimberDescription,
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SAND_VEIL] =
    {
        .name = _("Sand Veil"),
        .description = sSandVeilDescription,
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_STATIC] =
    {
        .name = _("Static"),
        .description = sStaticDescription,
        .aiRating = 4,
    },

    [ABILITY_VOLT_ABSORB] =
    {
        .name = _("Volt Absorb"),
        .description = sVoltAbsorbDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_WATER_ABSORB] =
    {
        .name = _("Water Absorb"),
        .description = sWaterAbsorbDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_OBLIVIOUS] =
    {
        .name = _("Oblivious"),
        .description = sObliviousDescription,
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_CLOUD_NINE] =
    {
        .name = _("Cloud Nine"),
        .description = sCloudNineDescription,
        .aiRating = 6,
        .breakable = TRUE,
    },
    //may need to make breakable
    //vsonic need to work out

    [ABILITY_COMPOUND_EYES] =
    {
        .name = _("Compound Eyes"),
        .description = sCompoundEyesDescription,
        .aiRating = 7,
    },

    [ABILITY_INSOMNIA] =
    {
        .name = _("Insomnia"),
        .description = sInsomniaDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_COLOR_CHANGE] =
    {
        .name = _("Color Change"),
        .description = sColorChangeDescription,
        .aiRating = 5,
    },
    //potentially should add mold breaker leaving off for now
    //concpet stance change isn't breakable

    [ABILITY_IMMUNITY] =
    {
        .name = _("Immunity"),
        .description = sImmunityDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_FLASH_FIRE] =
    {
        .name = _("Flash Fire"),
        .description = sFlashFireDescription,
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SHIELD_DUST] =
    {
        .name = _("Shield Dust"),
        .description = sShieldDustDescription,
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_OWN_TEMPO] =
    {
        .name = _("Own Tempo"),
        .description = sOwnTempoDescription,
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SUCTION_CUPS] =
    {
        .name = _("Suction Cups"),
        .description = sSuctionCupsDescription,
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_INTIMIDATE] =
    {
        .name = _("Intimidate"),
        .description = sIntimidateDescription,
        .aiRating = 7,
    },

    [ABILITY_SHADOW_TAG] =
    {
        .name = _("Shadow Tag"),
        .description = sShadowTagDescription,
        .aiRating = 10,
    },

    [ABILITY_ROUGH_SKIN] =
    {
        .name = _("Rough Skin"),
        .description = sRoughSkinDescription,
        .aiRating = 6,
    },

    [ABILITY_WONDER_GUARD] =
    {
        .name = _("Wonder Guard"),
        .description = sWonderGuardDescription,
        .aiRating = 10,
        .breakable = TRUE,
    },

    [ABILITY_FEMME_FATALE] =
    {
        .name = _("Femme Fatale"),
        .description = sFemmeFataleDescription,
        .aiRating = 6,
        .breakable = TRUE,
    },//based off oblivious but double check effect, for flags and ratings

    [ABILITY_EFFECT_SPORE] =
    {
        .name = _("Effect Spore"),
        .description = sEffectSporeDescription,
        .aiRating = 4,
    },

    [ABILITY_SYNCHRONIZE] =
    {
        .name = _("Synchronize"),
        .description = sSynchronizeDescription,
        .aiRating = 4,
    },

    [ABILITY_CLEAR_BODY] =
    {
        .name = _("Clear Body"),
        .description = sClearBodyDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_NATURAL_CURE] =
    {
        .name = _("Natural Cure"),
        .description = sNaturalCureDescription,
        .aiRating = 7,
    },

    [ABILITY_LIGHTNING_ROD] =
    {
        .name = _("Lightning Rod"),
        .description = sLightningRodDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_SERENE_GRACE] =
    {
        .name = _("Serene Grace"),
        .description = sSereneGraceDescription,
        .aiRating = 8,
    },

    [ABILITY_SWIFT_SWIM] =
    {
        .name = _("Swift Swim"),
        .description = sSwiftSwimDescription,
        .aiRating = 6,
    },

    [ABILITY_CHLOROPHYLL] =
    {
        .name = _("Chlorophyll"),
        .description = sChlorophyllDescription,
        .aiRating = 6,
    },

    [ABILITY_ILLUMINATE] =
    {
        .name = _("Illuminate"),
        .description = sIlluminateDescription,
        .aiRating = 0,
    },
    //my version doesn't prevent stat drop so not breakable

    [ABILITY_TRACE] =
    {
        .name = _("Trace"),
        .description = sTraceDescription,
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_HUGE_POWER] =
    {
        .name = _("Huge Power"),
        .description = sHugePowerDescription,
        .aiRating = 10,
    },

    [ABILITY_POISON_POINT] =
    {
        .name = _("Poison Point"),
        .description = sPoisonPointDescription,
        .aiRating = 4,
    },

    [ABILITY_INNER_FOCUS] =
    {
        .name = _("Inner Focus"),
        .description = sInnerFocusDescription,
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_MAGMA_ARMOR] =
    {
        .name = _("Magma Armor"),
        .description = sMagmaArmorDescription,
        .aiRating = 3,
        .breakable = TRUE,
    },
    //how does breakable work
    //this burns items on contact 
    //and blocks physical crits
    //I think I'd want mold breaker to only
    //break through the crit protection
    //idk if it makes sense to avoid burning items
    //for example checkked flamebody and that 
    //isn't affected by moldbreaker
    //ok looked into EE, breakable makes it read 
    //as no ability, but despite being breakable
    //it also has ability checks that ignore moldbreaker
    //so certain times it reads the ability as is, 
    //allowing its effect to activate
    //so I would just need to use that version for item burn check
    //and the full check for physical crit
    //am just unsure if that is true to how it should be used
    //got it, from bulbapedia
    //(Ignorable Abilities are most Abilities that could 
    //potentially negatively affect the success, 
    //damage, or effects of a move.)
    //which is why magma armor is breakable but otherwise ignored 
    //for moldbreaker, it gets broken to allow freezing
    //since otherwise the move success would be affected
    //I can do what I want, break the crits
    //but keep the item burn up
    //as crits affect damage, but the item loss
    //doens't affect success or damage of moves used

    [ABILITY_WATER_VEIL] =
    {
        .name = _("Water Veil"),
        .description = sWaterVeilDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MAGNET_PULL] =
    {
        .name = _("Magnet Pull"),
        .description = sMagnetPullDescription,
        .aiRating = 9,
    },

    [ABILITY_SOUNDPROOF] =
    {
        .name = _("Soundproof"),
        .description = sSoundproofDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_RAIN_DISH] =
    {
        .name = _("Rain Dish"),
        .description = sRainDishDescription,
        .aiRating = 3,
    },

    [ABILITY_SAND_STREAM] =
    {
        .name = _("Sand Stream"),
        .description = sSandStreamDescription,
        .aiRating = 9,
    },

    [ABILITY_PRESSURE] =
    {
        .name = _("Pressure"),
        .description = sPressureDescription,
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_THICK_FAT] =
    {
        .name = _("Thick Fat"),
        .description = sThickFatDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EARLY_BIRD] =
    {
        .name = _("Early Bird"),
        .description = sEarlyBirdDescription,
        .aiRating = 5,
    },

    [ABILITY_FLAME_BODY] =
    {
        .name = _("Flame Body"),
        .description = sFlameBodyDescription,
        .aiRating = 4,
    },

    [ABILITY_RUN_AWAY] =
    {
        .name = _("Run Away"),
        .description = sRunAwayDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },
    //vsonic just realized with new effect changes
    //this is breakable now, so would need to go over 
    //and reevaluate these

    [ABILITY_KEEN_EYE] =
    {
        .name = _("Keen Eye"),
        .description = sKeenEyeDescription,
        .aiRating = 1,
        .breakable = TRUE,
    },//vsonic

    [ABILITY_HYPER_CUTTER] =
    {
        .name = _("Hyper Cutter"),
        .description = sHyperCutterDescription,
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PICKUP] =
    {
        .name = _("Pickup"),
        .description = sPickupDescription,
        .aiRating = 2,
    },

    [ABILITY_TRUANT] =
    {
        .name = _("Truant"),
        .description = sTruantDescription,
        .aiRating = -2,
        .cantBeOverwritten = TRUE,
    },//vsnoic

    [ABILITY_HUSTLE] =
    {
        .name = _("Hustle"),
        .description = sHustleDescription,
        .aiRating = 7,
    },

    [ABILITY_CUTE_CHARM] =
    {
        .name = _("Cute Charm"),
        .description = sCuteCharmDescription,
        .aiRating = 3,
    },

    [ABILITY_PLUS] =
    {
        .name = _("Plus"),
        .description = sPlusDescription,
        .aiRating = 2,
    },

    [ABILITY_MINUS] =
    {
        .name = _("Minus"),
        .description = sMinusDescription,
        .aiRating = 2,
    },

    [ABILITY_FORECAST] =
    {
        .name = _("Forecast"),
        .description = sForecastDescription,
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STICKY_HOLD] =
    {
        .name = _("Sticky Hold"),
        .description = sStickyHoldDescription,
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SHED_SKIN] =
    {
        .name = _("Shed Skin"),
        .description = sShedSkinDescription,
        .aiRating = 7,
    },

    [ABILITY_GUTS] =
    {
        .name = _("Guts"),
        .description = sGutsDescription,
        .aiRating = 6,
    },

    [ABILITY_MARVEL_SCALE] =
    {
        .name = _("Marvel Scale"),
        .description = sMarvelScaleDescription,
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_LIQUID_OOZE] =
    {
        .name = _("Liquid Ooze"),
        .description = sLiquidOozeDescription,
        .aiRating = 3,
    },

    [ABILITY_OVERGROW] =
    {
        .name = _("Overgrow"),
        .description = sOvergrowDescription,
        .aiRating = 5,
    },

    [ABILITY_BLAZE] =
    {
        .name = _("Blaze"),
        .description = sBlazeDescription,
        .aiRating = 5,
    },

    [ABILITY_TORRENT] =
    {
        .name = _("Torrent"),
        .description = sTorrentDescription,
        .aiRating = 5,
    },

    [ABILITY_SWARM] =
    {
        .name = _("Swarm"),
        .description = sSwarmDescription,
        .aiRating = 5,
    },

    [ABILITY_ROCK_HEAD] =
    {
        .name = _("Rock Head"),
        .description = sRockHeadDescription,
        .aiRating = 5,
    },

    [ABILITY_DROUGHT] =
    {
        .name = _("Drought"),
        .description = sDroughtDescription,
        .aiRating = 9,
    },

    [ABILITY_ARENA_TRAP] =
    {
        .name = _("Arena Trap"),
        .description = sArenaTrapDescription,
        .aiRating = 9,
    },

    [ABILITY_VITAL_SPIRIT] =
    {
        .name = _("Vital Spirit"),
        .description = sVitalSpiritDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_WHITE_SMOKE] =
    {
        .name = _("White Smoke"),
        .description = sWhiteSmokeDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_PURE_POWER] =
    {
        .name = _("Pure Power"),
        .description = sPurePowerDescription,
        .aiRating = 10,
    },

    [ABILITY_SHELL_ARMOR] =
    {
        .name = _("Shell Armor"),
        .description = sShellArmorDescription,
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_CACOPHONY] =
    {
        .name = _("Cacophony"),
        .description = COMPOUND_ABILITY_STRING("+Snd Dmg. Boosts ally Sound-move effects\nand helps bypass screens and protects."),
        .aiRating = 1,
    }, //low rating cuz very niche activation

    [ABILITY_AIR_LOCK] =
    {
        .name = _("Air Lock"),
        .description = sAirLockDescription,
        .aiRating = 5,
    },

    [ABILITY_TANGLED_FEET] =
    {
        .name = _("Tangled Feet"),
        .description = sTangledFeetDescription,
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_MOTOR_DRIVE] =
    {
        .name = _("Motor Drive"),
        .description = sMotorDriveDescription,
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_RIVALRY] =
    {
        .name = _("Rivalry"),
        .description = sRivalryDescription,
        .aiRating = 1,
    },

    [ABILITY_STEADFAST] =
    {
        .name = _("Steadfast"),
        .description = sSteadfastDescription,
        .aiRating = 2,
    },//vsonic

    [ABILITY_SNOW_CLOAK] =
    {
        .name = _("Snow Cloak"),
        .description = sSnowCloakDescription,
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_GLUTTONY] =
    {
        .name = _("Gluttony"),
        .description = sGluttonyDescription,
        .aiRating = 3,
    },//vsonic

    [ABILITY_ANGER_POINT] =
    {
        .name = _("Anger Point"),
        .description = sAngerPointDescription,
        .aiRating = 6,
    },

    [ABILITY_UNBURDEN] =
    {
        .name = _("Unburden"),
        .description = sUnburdenDescription,
        .aiRating = 7,
    },

    [ABILITY_HEATPROOF] =
    {
        .name = _("Heatproof"),
        .description = sHeatproofDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_SIMPLE] =
    {
        .name = _("Simple"),
        .description = sSimpleDescription,
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_DRY_SKIN] =
    {
        .name = _("Dry Skin"),
        .description = sDrySkinDescription,
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DOWNLOAD] =
    {
        .name = _("Download"),
        .description = sDownloadDescription,
        .aiRating = 7,
    },

    [ABILITY_IRON_FIST] =
    {
        .name = _("Iron Fist"),
        .description = sIronFistDescription,
        .aiRating = 6,
    },

    [ABILITY_POISON_HEAL] =
    {
        .name = _("Poison Heal"),
        .description = sPoisonHealDescription,
        .aiRating = 8,
    },

    [ABILITY_ADAPTABILITY] =
    {
        .name = _("Adaptability"),
        .description = sAdaptabilityDescription,
        .aiRating = 8,
    },

    [ABILITY_SKILL_LINK] =
    {
        .name = _("Skill Link"),
        .description = sSkillLinkDescription,
        .aiRating = 7,
    },

    [ABILITY_HYDRATION] =
    {
        .name = _("Hydration"),
        .description = sHydrationDescription,
        .aiRating = 4,
    },

    [ABILITY_SOLAR_POWER] =
    {
        .name = _("Solar Power"),
        .description = sSolarPowerDescription,
        .aiRating = 3,
    },

    [ABILITY_QUICK_FEET] =
    {
        .name = _("Quick Feet"),
        .description = sQuickFeetDescription,
        .aiRating = 5,
    },

    [ABILITY_NORMALIZE] =
    {
        .name = _("Normalize"),
        .description = sNormalizeDescription,
        .aiRating = 2,
    },

    [ABILITY_SNIPER] =
    {
        .name = _("Sniper"),
        .description = sSniperDescription,
        .aiRating = 3,
    },

    [ABILITY_MAGIC_GUARD] =
    {
        .name = _("Magic Guard"),
        .description = sMagicGuardDescription,
        .aiRating = 9,
    },

    [ABILITY_NO_GUARD] =
    {
        .name = _("No Guard"),
        .description = COMPOUND_ABILITY_STRING("Can't guard but bypasses foe guard mode.\nAll attacks used by/against the user hit."),
        .aiRating = 8,
    },

    [ABILITY_STALL] =
    {
        .name = _("Stall"),
        .description = sStallDescription,
        .aiRating = 1,
    },

    [ABILITY_TECHNICIAN] =
    {
        .name = _("Technician"),
        .description = sTechnicianDescription,
        .aiRating = 8,
    },

    [ABILITY_LEAF_GUARD] =
    {
        .name = _("Leaf Guard"),
        .description = sLeafGuardDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_KLUTZ] =
    {
        .name = _("Klutz"),
        .description = sKlutzDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_MOLD_BREAKER] =
    {
        .name = _("Mold Breaker"),
        .description = sMoldBreakerDescription,
        .aiRating = 7,
    },

    [ABILITY_SUPER_LUCK] =
    {
        .name = _("Super Luck"),
        .description = sSuperLuckDescription,
        .aiRating = 3,
    },

    [ABILITY_AFTERMATH] =
    {
        .name = _("Aftermath"),
        .description = sAftermathDescription,
        .aiRating = 5,
    },

    [ABILITY_ANTICIPATION] =
    {
        .name = _("Anticipation"),
        .description = sAnticipationDescription,
        .aiRating = 5,
    },

    [ABILITY_FOREWARN] =
    {
        .name = _("Forewarn"),
        .description = sForewarnDescription,
        .aiRating = 5,
    },

    [ABILITY_UNAWARE] =
    {
        .name = _("Unaware"),
        .description = sUnawareDescription,
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_TINTED_LENS] =
    {
        .name = _("Tinted Lens"),
        .description = sTintedLensDescription,
        .aiRating = 7,
    },

    [ABILITY_FILTER] =
    {
        .name = _("Filter"),
        .description = sFilterDescription,
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SLOW_START] =
    {
        .name = _("Slow Start"),
        .description = sSlowStartDescription,
        .aiRating = -2,
        .breakable = TRUE,
    },

    [ABILITY_SCRAPPY] =
    {
        .name = _("Scrappy"),
        .description = sScrappyDescription,
        .aiRating = 6,
    },

    [ABILITY_STORM_DRAIN] =
    {
        .name = _("Storm Drain"),
        .description = sStormDrainDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_ICE_BODY] =
    {
        .name = _("Ice Body"),
        .description = sIceBodyDescription,
        .aiRating = 3,
    },

    [ABILITY_SOLID_ROCK] =
    {
        .name = _("Solid Rock"),
        .description = sFilterDescription,
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SNOW_WARNING] =
    {
        .name = _("Snow Warning"),

        .description = COMPOUND_ABILITY_STRING("Summons snow in battle."),
        .aiRating = 8,
    },

    
    //attempt separate hail /snow set abilities
    //distribution would be a problem would want both
    //but can't have both some would have to be learned
    //...huh actually no, every mon that gets snow warning
    //has an open space I could slot in this
    //mega abomasnow would have to split base ability
    //potentially doable
    [ABILITY_CRYOSTORM] =
    {
        .name = _("Cryo-Storm"),
        .description = sSnowWarningDescription,
        .aiRating = 8,
    },
    

    [ABILITY_HONEY_GATHER] =
    {
        .name = _("Honey Gather"),
        .description = sHoneyGatherDescription,
        .aiRating = 4,
    },

    [ABILITY_FRISK] =
    {
        .name = _("Frisk"),
        .description = sFriskDescription,
        .aiRating = 4,
    },//vsonic

    [ABILITY_RECKLESS] =
    {
        .name = _("Reckless"),
        .description = sRecklessDescription,
        .aiRating = 6,
    },

    [ABILITY_MULTITYPE] =
    {
        .name = _("Multitype"),
        .description = sMultitypeDescription,
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_FLOWER_GIFT] =
    {
        .name = _("Flower Gift"),
        .description = sFlowerGiftDescription,
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },//cherrim ability needed to transform

    [ABILITY_BAD_DREAMS] =
    {
        .name = _("Bad Dreams"),
        .description = sBadDreamsDescription,
        .aiRating = 4,
    },

    [ABILITY_PICKPOCKET] =
    {
        .name = _("Pickpocket"),
        .description = sPickpocketDescription,
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SHEER_FORCE] =
    {
        .name = _("Sheer Force"),
        .description = sSheerForceDescription,
        .aiRating = 8,
    },

    [ABILITY_CONTRARY] =
    {
        .name = _("Contrary"),
        .description = sContraryDescription,
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_UNNERVE] =
    {
        .name = _("Unnerve"),
        .description = sUnnerveDescription,
        .aiRating = 6,
    },

    [ABILITY_DEFIANT] =
    {
        .name = _("Defiant"),
        .description = sDefiantDescription,
        .aiRating = 5,
    },

    [ABILITY_DEFEATIST] =
    {
        .name = _("Defeatist"),
        .description = sDefeatistDescription,
        .aiRating = -1,
    },

    [ABILITY_CURSED_BODY] =
    {
        .name = _("Cursed Body"),
        .description = sCursedBodyDescription,
        .aiRating = 4,
    },

    [ABILITY_HEALER] =
    {
        .name = _("Healer"),
        .description = sHealerDescription,
        .aiRating = 0,
    },//vsonic

    [ABILITY_FRIEND_GUARD] =
    {
        .name = _("Friend Guard"),
        .description = sFriendGuardDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_WEAK_ARMOR] =
    {
        .name = _("Weak Armor"),
        .description = sWeakArmorDescription,
        .aiRating = 2,
    },

    [ABILITY_HEAVY_METAL] =
    {
        .name = _("Heavy Metal"),
        .description = sHeavyMetalDescription,
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_LIGHT_METAL] =
    {
        .name = _("Light Metal"),
        .description = sLightMetalDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MULTISCALE] =
    {
        .name = _("Multiscale"),
        .description = sMultiscaleDescription,
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_TOXIC_BOOST] =
    {
        .name = _("Toxic Boost"),
        .description = sToxicBoostDescription,
        .aiRating = 6,
    },

    [ABILITY_FLARE_BOOST] =
    {
        .name = _("Flare Boost"),
        .description = sFlareBoostDescription,
        .aiRating = 5,
    },

    [ABILITY_HARVEST] =
    {
        .name = _("Harvest"),
        .description = sHarvestDescription,
        .aiRating = 5,
    },

    [ABILITY_TELEPATHY] =
    {
        .name = _("Telepathy"),
        .description = sTelepathyDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_MOODY] =
    {
        .name = _("Moody"),
        .description = sMoodyDescription,
        .aiRating = 10,
    },

    [ABILITY_OVERCOAT] =
    {
        .name = _("Overcoat"),
        .description = sOvercoatDescription,
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_POISON_TOUCH] =
    {
        .name = _("Poison Touch"),
        .description = sPoisonTouchDescription,
        .aiRating = 4,
    },

    [ABILITY_REGENERATOR] =
    {
        .name = _("Regenerator"),
        .description = COMPOUND_ABILITY_STRING("Restores a portion of HP\nupon switching out."),
        .aiRating = 8,
    },

    [ABILITY_BIG_PECKS] =
    {
        .name = _("Big Pecks"),
        .description = sBigPecksDescription,
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SAND_RUSH] =
    {
        .name = _("Sand Rush"),
        .description = sSandRushDescription,
        .aiRating = 6,
    },

    [ABILITY_WONDER_SKIN] =
    {
        .name = _("Wonder Skin"),
        .description = sWonderSkinDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANALYTIC] =
    {
        .name = _("Analytic"),
        .description = sAnalyticDescription,
        .aiRating = 5,
    },

    [ABILITY_ILLUSION] =
    {
        .name = _("Illusion"),
        .description = sIllusionDescription,
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_IMPOSTER] =
    {
        .name = _("Imposter"),
        .description = sImposterDescription,
        .aiRating = 9,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_INFILTRATOR] =
    {
        .name = _("Infiltrator"),
        .description = sInfiltratorDescription,
        .aiRating = 6,
    },

    [ABILITY_MUMMY] =
    {
        .name = _("Mummy"),
        .description = sMummyDescription,
        .aiRating = 5,
    },

    [ABILITY_MOXIE] =
    {
        .name = _("Moxie"),
        .description = sMoxieDescription,
        .aiRating = 7,
    },

    [ABILITY_JUSTIFIED] =
    {
        .name = _("Justified"),
        .description = sJustifiedDescription,
        .aiRating = 6,
    },

    [ABILITY_RATTLED] =
    {
        .name = _("Rattled"),
        .description = sRattledDescription,
        .aiRating = 3,
    },

    [ABILITY_MAGIC_BOUNCE] =
    {
        .name = _("Magic Bounce"),
        .description = sMagicBounceDescription,
        .aiRating = 9,
        .breakable = TRUE,
    },

    [ABILITY_SAP_SIPPER] =
    {
        .name = _("Sap Sipper"),
        .description = sSapSipperDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_PRANKSTER] =
    {
        .name = _("Prankster"),
        .description = sPranksterDescription,
        .aiRating = 8,
    },

    [ABILITY_SAND_FORCE] =
    {
        .name = _("Sand Force"),
        .description = sSandForceDescription,
        .aiRating = 4,
    },

    [ABILITY_IRON_BARBS] =
    {
        .name = _("Iron Barbs"),
        .description = sRoughSkinDescription,
        .aiRating = 6,
    },

    [ABILITY_ZEN_MODE] =
    {
        .name = _("Zen Mode"),
        .description = sZenModeDescription,
        .aiRating = -1,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
    },

    [ABILITY_VICTORY_STAR] =
    {
        .name = _("Victory Star"),
        .description = sVictoryStarDescription,
        .aiRating = 7,
    },

    [ABILITY_TURBOBLAZE] =
    {
        .name = _("Turboblaze"),
        .description = COMPOUND_ABILITY_STRING("Moldbreaker and Flash Fire."),
        .aiRating = 9,
    },

    [ABILITY_TERAVOLT] =
    {
        .name = _("Teravolt"),
        .description = COMPOUND_ABILITY_STRING("Moldbreaker and Lightning Rod."),
        .aiRating = 9,
    },
    //with change should be breakable 
    //but will take point from full metal body 
    //and leave off

    [ABILITY_AROMA_VEIL] =
    {
        .name = _("Aroma Veil"),
        .description = sAromaVeilDescription,
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_FLOWER_VEIL] =
    {
        .name = _("Flower Veil"),
        .description = sFlowerVeilDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_CHEEK_POUCH] =
    {
        .name = _("Cheek Pouch"),
        .description = sCheekPouchDescription,
        .aiRating = 4,
    },//vsonic

    [ABILITY_PROTEAN] =
    {
        .name = _("Protean"),
        .description = sProteanDescription,
        .aiRating = 8,
    },

    [ABILITY_FUR_COAT] =
    {
        .name = _("Fur Coat"),
        .description = sFurCoatDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MAGICIAN] =
    {
        .name = _("Magician"),
        .description = sMagicianDescription,
        .aiRating = 5,
    },

    [ABILITY_BULLETPROOF] =
    {
        .name = _("Bulletproof"),
        .description = sBulletproofDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_COMPETITIVE] =
    {
        .name = _("Competitive"),
        .description = sCompetitiveDescription,
        .aiRating = 5,
    },

    [ABILITY_STRONG_JAW] =
    {
        .name = _("Strong Jaw"),
        .description = sStrongJawDescription,
        .aiRating = 6,
    },

    [ABILITY_REFRIGERATE] =
    {
        .name = _("Refrigerate"),
        .description = sRefrigerateDescription,
        .aiRating = 8,
    },

    [ABILITY_SWEET_VEIL] =
    {
        .name = _("Sweet Veil"),
        .description = sSweetVeilDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_STANCE_CHANGE] =
    {
        .name = _("Stance Change"),
        .description = sStanceChangeDescription,
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_GALE_WINGS] =
    {
        .name = _("Gale Wings"),
        .description = sGaleWingsDescription,
        .aiRating = 6,
    },

    [ABILITY_MEGA_LAUNCHER] =
    {
        .name = _("Mega Launcher"),
        .description = sMegaLauncherDescription,
        .aiRating = 7,
    },

    [ABILITY_GRASS_PELT] =
    {
        .name = _("Grass Pelt"),
        .description = sGrassPeltDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_SYMBIOSIS] =
    {
        .name = _("Symbiosis"),
        .description = sSymbiosisDescription,
        .aiRating = 0,
    },

    [ABILITY_TOUGH_CLAWS] =
    {
        .name = _("Tough Claws"),
        .description = sToughClawsDescription,
        .aiRating = 7,
    },

    [ABILITY_PIXILATE] =
    {
        .name = _("Pixilate"),
        .description = sPixilateDescription,
        .aiRating = 8,
    },

    [ABILITY_GOOEY] =
    {
        .name = _("Gooey"),
        .description = sGooeyDescription,
        .aiRating = 5,
    },

    [ABILITY_AERILATE] =
    {
        .name = _("Aerilate"),
        .description = sAerilateDescription,
        .aiRating = 8,
    },

    [ABILITY_PARENTAL_BOND] =
    {
        .name = _("Parental Bond"),
        .description = sParentalBondDescription,
        .aiRating = 10,
    },

    [ABILITY_DARK_AURA] =
    {
        .name = _("Dark Aura"),
        .description = sDarkAuraDescription,
        .aiRating = 6,
    },

    [ABILITY_FAIRY_AURA] =
    {
        .name = _("Fairy Aura"),
        .description = sFairyAuraDescription,
        .aiRating = 6,
    },

    [ABILITY_AURA_BREAK] =
    {
        .name = _("Aura Break"),
        .description = sAuraBreakDescription,
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PRIMORDIAL_SEA] =
    {
        .name = _("Primordial Sea"),
        .description = sPrimordialSeaDescription,
        .aiRating = 10,
    },

    [ABILITY_DESOLATE_LAND] =
    {
        .name = _("Desolate Land"),
        .description = sDesolateLandDescription,
        .aiRating = 10,
    },

    [ABILITY_DELTA_STREAM] =
    {
        .name = _("Delta Stream"),
        .description = sDeltaStreamDescription,
        .aiRating = 10,
    },

    [ABILITY_STAMINA] =
    {
        .name = _("Stamina"),
        .description = sStaminaDescription,
        .aiRating = 6,
    },

    [ABILITY_WIMP_OUT] =
    {
        .name = _("Wimp Out"),
        .description = sWimpOutDescription,
        .aiRating = 3,
    },

    [ABILITY_EMERGENCY_EXIT] =
    {
        .name = _("Emergency Exit"),
        .description = COMPOUND_ABILITY_STRING("When HP falls below half delivers a\nsudden vindictive attack then flees."),
        .aiRating = 5,
    },

    [ABILITY_WATER_COMPACTION] =
    {
        .name = _("Water Compaction"),
        .description = sWaterCompactionDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MERCILESS] =
    {
        .name = _("Merciless"),
        .description = sMercilessDescription,
        .aiRating = 4,
    },

    [ABILITY_SHIELDS_DOWN] =
    {
        .name = _("Shields Down"),
        .description = sShieldsDownDescription,
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_STAKEOUT] =
    {
        .name = _("Stakeout"),
        .description = sStakeoutDescription,
        .aiRating = 6,
    },

    [ABILITY_WATER_BUBBLE] =
    {
        .name = _("Water Bubble"),
        .description = sWaterBubbleDescription,
        .aiRating = 8,
        .breakable = TRUE,
    },//pretty sure this should be breakable
    //allow to be burned at least

    [ABILITY_STEELWORKER] =
    {
        .name = _("Steelworker"),
        .description = sSteelworkerDescription,
        .aiRating = 6,
    },

    [ABILITY_BERSERK] =
    {
        .name = _("Berserk"),
        .description = sBerserkDescription,
        .aiRating = 5,
    },//vsonic

    [ABILITY_SLUSH_RUSH] =
    {
        .name = _("Slush Rush"),
        .description = sSlushRushDescription,
        .aiRating = 5,
    },

    [ABILITY_LONG_REACH] =
    {
        .name = _("Long Reach"),
        .description = sLongReachDescription,
        .aiRating = 5,
    },

    [ABILITY_LIQUID_VOICE] =
    {
        .name = _("Liquid Voice"),
        .description = sLiquidVoiceDescription,
        .aiRating = 5,
    },

    [ABILITY_TRIAGE] =
    {
        .name = _("Triage"),
        .description = sTriageDescription,
        .aiRating = 7,
    },

    [ABILITY_GALVANIZE] =
    {
        .name = _("Galvanize"),
        .description = sGalvanizeDescription,
        .aiRating = 8,
    },

    [ABILITY_SURGE_SURFER] =
    {
        .name = _("Surge Surfer"),
        .description = sSurgeSurferDescription,
        .aiRating = 4,
    },

    [ABILITY_SCHOOLING] =
    {
        .name = _("Schooling"),
        .description = sSchoolingDescription,
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_DISGUISE] =
    {
        .name = _("Disguise"),
        .description = sDisguiseDescription,
        .aiRating = 8,
        .breakable = TRUE,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_BATTLE_BOND] =
    {
        .name = _("Battle Bond"),
        .description = sBattleBondDescription,
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_POWER_CONSTRUCT] =
    {
        .name = _("Power Construct"),
        .description = sPowerConstructDescription,
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_CORROSION] =
    {
        .name = _("Corrosion"),
        .description = sCorrosionDescription,
        .aiRating = 5,
    },

    [ABILITY_COMATOSE] =
    {
        .name = _("Comatose"),
        .description = sComatoseDescription,
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_QUEENLY_MAJESTY] =
    {
        .name = _("Queenly Majesty"),
        .description = sQueenlyMajestyDescription,
        .aiRating = 8,//6,
        .breakable = TRUE,
    },//idk if gen 9 change but realized affects entire side o.0

    [ABILITY_INNARDS_OUT] =
    {
        .name = _("Innards Out"),
        .description = sInnardsOutDescription,
        .aiRating = 5,
    },

    [ABILITY_DANCER] =
    {
        .name = _("Dancer"),
        .description = sDancerDescription,
        .aiRating = 5,
    },

    [ABILITY_BATTERY] =
    {
        .name = _("Battery"),
        .description = sBatteryDescription,
        .aiRating = 0,
    },

    [ABILITY_FLUFFY] =
    {
        .name = _("Fluffy"),
        .description = sFluffyDescription,
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_DAZZLING] =
    {
        .name = _("Dazzling"),
        .description = sDazzlingDescription,
        .aiRating = 5,
        .breakable = TRUE,
    }, //didn't know this description repeated pretty sure effect is now different

    [ABILITY_SOUL_HEART] =
    {
        .name = _("Soul-Heart"),
        .description = sSoulHeartDescription,
        .aiRating = 7,
    },

    [ABILITY_TANGLING_HAIR] =
    {
        .name = _("Tangling Hair"),
        .description = sGooeyDescription,
        .aiRating = 5,
    },

    [ABILITY_RECEIVER] =
    {
        .name = _("Receiver"),
        .description = sReceiverDescription,
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POWER_OF_ALCHEMY] =
    {
        .name = _("Power Of Alchemy"),
        .description = sReceiverDescription,
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_BEAST_BOOST] =
    {
        .name = _("Beast Boost"),
        .description = sBeastBoostDescription,
        .aiRating = 7,
    },

    [ABILITY_RKS_SYSTEM] =
    {
        .name = _("RKS System"),
        .description = sRKSSystemDescription,
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_ELECTRIC_SURGE] =
    {
        .name = _("Electric Surge"),
        .description = sElectricSurgeDescription,
        .aiRating = 8,
    },

    [ABILITY_PSYCHIC_SURGE] =
    {
        .name = _("Psychic Surge"),
        .description = sPsychicSurgeDescription,
        .aiRating = 8,
    },

    [ABILITY_MISTY_SURGE] =
    {
        .name = _("Misty Surge"),
        .description = sMistySurgeDescription,
        .aiRating = 8,
    },

    [ABILITY_GRASSY_SURGE] =
    {
        .name = _("Grassy Surge"),
        .description = sGrassySurgeDescription,
        .aiRating = 8,
    },

    [ABILITY_FULL_METAL_BODY] =
    {
        .name = _("Full Metal Body"),
        .description = sFullMetalBodyDescription,
        .aiRating = 4,
    },//vsonic
    //not breakable for some reason

    [ABILITY_SHADOW_SHIELD] =
    {
        .name = _("Shadow Shield"),
        .description = sMultiscaleDescription,
        .aiRating = 8,
    },

    [ABILITY_PRISM_ARMOR] =
    {
        .name = _("Prism Armor"),
        .description = sFilterDescription,
        .aiRating = 6,
    },

    [ABILITY_NEUROFORCE] =
    {
        .name = _("Neuroforce"),
        .description = sNeuroforceDescription,
        .aiRating = 6,
    },

    [ABILITY_INTREPID_SWORD] =
    {
        .name = _("Intrepid Sword"),
        .description = sIntrepidSwordDescription,
        .aiRating = 3,
    },

    [ABILITY_DAUNTLESS_SHIELD] =
    {
        .name = _("Dauntless Shield"),
        .description = sDauntlessShieldDescription,
        .aiRating = 3,
    },

    [ABILITY_LIBERO] =
    {
        .name = _("Libero"),
        .description = sLiberoDescription,
    },//vsonic see if changed may revert back, to making monotype
    //oh it is set to that, type 1 and 2 are changed but type 3 stays the same

    [ABILITY_BALL_FETCH] =
    {
        .name = _("Ball Fetch"),
        .description = sBallFetchDescription,
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_COTTON_DOWN] =
    {
        .name = _("Cotton Down"),
        .description = sCottonDownDescription,
        .aiRating = 3,
    },

    [ABILITY_PROPELLER_TAIL] =
    {
        .name = _("Propeller Tail"),
        .description = sPropellerTailDescription,
        .aiRating = 2,
    },

    [ABILITY_MIRROR_ARMOR] =
    {
        .name = _("Mirror Armor"),
        .description = sMirrorArmorDescription,
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_GULP_MISSILE] =
    {
        .name = _("Gulp Missile"),
        .description = sGulpMissileDescription,
        .aiRating = 3,
        .cantBeCopied = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_STALWART] =
    {
        .name = _("Stalwart"),
        .description = sStalwartDescription,
        .aiRating = 2,
    },

    [ABILITY_STEAM_ENGINE] =
    {
        .name = _("Steam Engine"),
        .description = sSteamEngineDescription,
        .aiRating = 3,
    },

    [ABILITY_PUNK_ROCK] =
    {
        .name = _("Punk Rock"),
        .description = sPunkRockDescription,
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SAND_SPIT] =
    {
        .name = _("Sand Spit"),
        .description = sSandSpitDescription,
        .aiRating = 5,
    },

    [ABILITY_ICE_SCALES] =
    {
        .name = _("Ice Scales"),
        .description = sIceScalesDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_RIPEN] =
    {
        .name = _("Ripen"),
        .description = sRipenDescription,
        .aiRating = 4,
    },//vsonic

    [ABILITY_ICE_FACE] =
    {
        .name = _("Ice Face"),
        .description = sIceFaceDescription,
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .breakable = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_POWER_SPOT] =
    {
        .name = _("Power Spot"),
        .description = sPowerSpotDescription,
        .aiRating = 2,
    },

    [ABILITY_MIMICRY] =
    {
        .name = _("Mimicry"),
        .description = sMimicryDescription,
        .aiRating = 2,
    },

    [ABILITY_SCREEN_CLEANER] =
    {
        .name = _("Screen Cleaner"),
        .description = sScreenCleanerDescription,
        .aiRating = 3,
    },

    [ABILITY_STEELY_SPIRIT] =
    {
        .name = _("Steely Spirit"),
        .description = sSteelySpiritDescription,
        .aiRating = 2, //vsonic
    },

    [ABILITY_PERISH_BODY] =
    {
        .name = _("Perish Body"),
        .description = sPerishBodyDescription,
        .aiRating = 2,
    },
    //no longer makes user faint, only low value cuz of who its on.
    //idea being ghosts can't die.  also mon is frail is cheese

    [ABILITY_WANDERING_SPIRIT] =
    {
        .name = _("Wandering Spirit"),
        .description = sWanderingSpiritDescription,
        .aiRating = 2,
    },

    [ABILITY_GORILLA_TACTICS] =
    {
        .name = _("Gorilla Tactics"),
        .description = sGorillaTacticsDescription,
        .aiRating = 4,
    },

    [ABILITY_NEUTRALIZING_GAS] =
    {
        .name = _("Neutralizing Gas"),
        .description = sNeutralizingGasDescription,
        .aiRating = 5,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_PASTEL_VEIL] =
    {
        .name = _("Pastel Veil"),
        .description = sPastelVeilDescription,
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_HUNGER_SWITCH] =
    {
        .name = _("Hunger Switch"),
        .description = sHungerSwitchDescription,
        .aiRating = 2,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUICK_DRAW] =
    {
        .name = _("Quick Draw"),
        .description = sQuickDrawDescription,
        .aiRating = 4,
    },

    [ABILITY_UNSEEN_FIST] =
    {
        .name = _("Unseen Fist"),
        .description = sUnseenFistDescription,
        .aiRating = 6,
    },

    [ABILITY_CURIOUS_MEDICINE] =
    {
        .name = _("Curious Medicine"),
        .description = sCuriousMedicineDescription,
        .aiRating = 3,
    },

    [ABILITY_TRANSISTOR] =
    {
        .name = _("Transistor"),
        .description = sTransistorDescription,
        .aiRating = 6,
    },

    [ABILITY_DRAGONS_MAW] =
    {
        .name = _("Dragon's Maw"),
        .description = sDragonsMawDescription,
        .aiRating = 6,
    },

    [ABILITY_CHILLING_NEIGH] =
    {
        .name = _("Chilling Neigh"),
        .description = sChillingNeighDescription,
        .aiRating = 7,
    },

    [ABILITY_GRIM_NEIGH] =
    {
        .name = _("Grim Neigh"),
        .description = sGrimNeighDescription,
        .aiRating = 7,
    },

    [ABILITY_AS_ONE_ICE_RIDER] =
    {
        .name = _("As One"),
        .description = sAsOneIceRiderDescription,
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_AS_ONE_SHADOW_RIDER] =
    {
        .name = _("As One"),
        .description = sAsOneShadowRiderDescription,
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_LINGERING_AROMA] =
    {
        .name = _("Lingering Aroma"),
        .description = COMPOUND_ABILITY_STRING("Spreads with contact.\nOverwrites attacker ability."),
        .aiRating = 5,
    },

    [ABILITY_SEED_SOWER] =
    {
        .name = _("Seed Sower"),
        .description = COMPOUND_ABILITY_STRING("Turns the ground into Grassy Terrain\nwhen the Pokémon is hit by an attack."),//vsonic
        .aiRating = 5,
    },

    [ABILITY_THERMAL_EXCHANGE] =
    {
        .name = _("Thermal Exchange"),
        .description = COMPOUND_ABILITY_STRING("Boosts Attack when hit by a Fire move.\nThe Pokémon also cannot be burned."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANGER_SHELL] =
    {
        .name = _("Anger Shell"),
        .description = COMPOUND_ABILITY_STRING("When an attack drops its HP to <= half,\ndef stats fall, ups Atk stats and speed."),//vsonic
        .aiRating = 3,
    },

    [ABILITY_PURIFYING_SALT] =
    {
        .name = _("Purifying Salt"),
        .description = COMPOUND_ABILITY_STRING("The Pokémon's pure salt protects it.\nReduces Ghost damage and blocks status."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_WELL_BAKED_BODY] =
    {
        .name = _("Well-Baked Body"),
        .description = COMPOUND_ABILITY_STRING("The Pokémon takes is immune to Fire moves\nInstead, its Defense is sharply boosted."), //vsonic
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_WIND_RIDER] =
    {
        .name = _("Wind Rider"),
        .description = COMPOUND_ABILITY_STRING("Takes no damage from Wind Effects instead\nps Atk if the target of a wind effect."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_GUARD_DOG] =
    {
        .name = _("Guard Dog"),
        .description = COMPOUND_ABILITY_STRING("Boosts the Pokémon’s Atk if intimidated.\nMoves or items that force switch out fail"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ROCKY_PAYLOAD] =
    {
        .name = _("Rocky Payload"),
        .description = COMPOUND_ABILITY_STRING("Powers up Rock moves by 50 percent."),
        .aiRating = 6,
    },//didn't realize that's what this did, but its basically fake stab
    //do I need to lower it to match new stab
    //mon its on isn't that good so will live at default

    [ABILITY_WIND_POWER] =
    {
        .name = _("Wind Power"),
        .description = COMPOUND_ABILITY_STRING("The Pokémon gets charged by wind moves\nboosting its next Electric move."),
        .aiRating = 4,
    },//vsonic wind moves not set yet

    [ABILITY_ZERO_TO_HERO] =
    {
        .name = _("Zero to Hero"),
        .description = COMPOUND_ABILITY_STRING("Changes form on switch out."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_COMMANDER] =
    {
        .name = _("Commander"),
        .description = COMPOUND_ABILITY_STRING("Commands from Dondozo."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_ELECTROMORPHOSIS] =
    {
        .name = _("Electromorphosis"),
        .description = COMPOUND_ABILITY_STRING("The Pokémon gets charged when damaged,\nboosting its next Electric move."),
        .aiRating = 5,
    },

    [ABILITY_PROTOSYNTHESIS] =
    {
        .name = _("Protosynthesis"),
        .description = COMPOUND_ABILITY_STRING("Sun boosts best stat."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUARK_DRIVE] =
    {
        .name = _("Quark Drive"),
        .description = COMPOUND_ABILITY_STRING("Elec. field ups best stat."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_GOOD_AS_GOLD] =
    {
        .name = _("Good as Gold"),
        .description = COMPOUND_ABILITY_STRING("Avoids status problems."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_VESSEL_OF_RUIN] =
    {
        .name = _("Vessel of Ruin"),
        .description = COMPOUND_ABILITY_STRING("Lowers Sp.Atk by 25 percent\nfor all mon without this ability."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SWORD_OF_RUIN] =
    {
        .name = _("Sword of Ruin"),
        .description = COMPOUND_ABILITY_STRING("Lowers Defense by 25 percent\nfor all mon without this ability."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_TABLETS_OF_RUIN] =
    {
        .name = _("Tablets of Ruin"),
        .description = COMPOUND_ABILITY_STRING("Lowers Speed by 25 percent\nfor all mon without this ability."),
        .aiRating = 5,
    },

    [ABILITY_BEADS_OF_RUIN] =
    {
        .name = _("Beads of Ruin"),
        .description = COMPOUND_ABILITY_STRING("Lowers Sp.Def by 25 percent\nfor all mon without this ability."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ORICHALCUM_PULSE] =
    {
        .name = _("Orichalcum Pulse"),
        .description = COMPOUND_ABILITY_STRING("Summons sunlight in battle."),
        .aiRating = 8,
    },

    [ABILITY_HADRON_ENGINE] =
    {
        .name = _("Hadron Engine"),
        .description = COMPOUND_ABILITY_STRING("Field becomes Electric."),
        .aiRating = 8,
    },

    [ABILITY_OPPORTUNIST] =
    {
        .name = _("Opportunist"),
        .description = COMPOUND_ABILITY_STRING("Copies foe's stat change."),
        .aiRating = 5,
    },

    [ABILITY_CUD_CHEW] =
    {
        .name = _("Cud Chew"),
        .description = COMPOUND_ABILITY_STRING("Eats a used berry again."),
        .aiRating = 4,
    },

    [ABILITY_SHARPNESS] =
    {
        .name = _("Sharpness"),
        .description = COMPOUND_ABILITY_STRING("A specialist in sharp cutting attacks.\nPowers up Slicing-moves."),
        .aiRating = 7,
    },

    [ABILITY_SUPREME_OVERLORD] =
    {
        .name = _("Supreme Overlord"),
        .description = COMPOUND_ABILITY_STRING("Inherits fallen's strength."),
        .aiRating = 6,
    },

    [ABILITY_COSTAR] =
    {
        .name = _("Costar"),
        .description = COMPOUND_ABILITY_STRING("Copies ally's stat changes."),
        .aiRating = 5,
    },

    [ABILITY_TOXIC_DEBRIS] =
    {
        .name = _("Toxic Debris"),
        .description = COMPOUND_ABILITY_STRING("Throws poison spikes if hit."),
        .aiRating = 4,
    },

    [ABILITY_ARMOR_TAIL] =
    {
        .name = _("Armor Tail"),
        .description = sDazzlingDescription,
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_EARTH_EATER] =
    {
        .name = _("Earth Eater"),
        .description = COMPOUND_ABILITY_STRING("Eats ground to heal HP."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MYCELIUM_MIGHT] =
    {
        .name = _("Mycelium Might"),
        .description = COMPOUND_ABILITY_STRING("Status moves never fail."),
        .aiRating = 2,
    },

    [ABILITY_HOSPITALITY] =
    {
        .name = _("Hospitality"),
        .description = COMPOUND_ABILITY_STRING("Restores ally's HP."),
        .aiRating = 5,
    },

    [ABILITY_MINDS_EYE] =
    {
        .name = _("Mind's Eye"),
        .description = COMPOUND_ABILITY_STRING("Ignores the immunities of GHOST types.\nIgnore Evasion checks and Acc can't fall."),
        .aiRating = 8,
        .breakable = TRUE,
    },//not mix of scrappy is just foresight
    //...oh its keen eye scrappy o.0

    [ABILITY_EMBODY_ASPECT_TEAL_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_ABILITY_STRING("Raises Speed."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_ABILITY_STRING("Raises Attack."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_WELLSPRING_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_ABILITY_STRING("Raises Sp. Def."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_ABILITY_STRING("Raises Defense."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TOXIC_CHAIN] =
    {
        .name = _("Toxic Chain"),
        .description = COMPOUND_ABILITY_STRING("The corrosive chain empowers its moves.\nMay badly poison any target of attack."),
        .aiRating = 8,
    },

    [ABILITY_SUPERSWEET_SYRUP] =
    {
        .name = _("Supersweet Syrup"),
        .description = COMPOUND_ABILITY_STRING("Gives off a sweet scent.\nAlso lowers foes evasion on switch-in."),
        .aiRating = 5,
    },

    [ABILITY_TERA_SHIFT] =
    {
        .name = _("Tera Shift"),
        .description = COMPOUND_ABILITY_STRING("Terastallizes upon entry."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TERA_SHELL] =
    {
        .name = _("Tera Shell"),
        .description = COMPOUND_ABILITY_STRING("Resists all at full HP."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_TERAFORM_ZERO] =
    {
        .name = _("Teraform Zero"),
        .description = COMPOUND_ABILITY_STRING("Zeroes weather and terrain."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POISON_PUPPETEER] =
    {
        .name = _("Poison Puppeteer"),
        .description = COMPOUND_ABILITY_STRING("Confuses poisoned foes."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    //Begin of Custom abilities
    [ABILITY_DISPIRIT_GUARD] =
    {
        .name = _("Dispirit Guard"),
        .description = sDispiritGuardDescription,
        .aiRating = 8,
        .breakable = TRUE,
    },
    //may change but rn includes what was previously neutral hits as resisted
    //
    
    [ABILITY_NUISANCE] =
    {
        .name = _("Nuisance"),
        .description = sNuisanceDescription,
        .aiRating = 5,
    },
    
    [ABILITY_MULTI_TASK] =
    {
        .name = _("Multi-Task"),
        .description = sMultiTaskDescription,
        .aiRating = 4,
    },
    
    [ABILITY_SIROCCO] =
    {
        .name = _("Sirocco"),
        .description = sSiroccoDescription,
        .aiRating = 4,
    },
    
    [ABILITY_HI_PRESSURE] =
    {
        .name = _("Hi-Pressure"),
        .description = sHipressureDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },
    
    [ABILITY_CUPIDS_ARROW] =
    {
        .name = _("Cupid's Arrow"),
        .description = sCupidsArrowDescription,
        .aiRating = 0,
    },
    
    [ABILITY_BATTLE_MATRON] =
    {
        .name = _("Battle Matron"),
        .description = sBattleMatronDescription,
        .aiRating = 0,
    },
    
    [ABILITY_LIQUID_SOUL] =
    {
        .name = _("Liquid Soul"),
        .description = sLiquidSoulDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },
    
    [ABILITY_OCEAN_MEMORY] =
    {
        .name = _("Ocean Memory"),
        .description = sOceanMemoryDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_OVERCHARGE] =
    {
        .name = _("Overcharge"),
        .description = sOverchargeDescription,
        .aiRating = 5,
        
    },
    
    [ABILITY_PHOTOSYNTHESIZE] =
    {
        .name = _("Photosynthesize"),
        .description = sPhotosynthesizeDescription,
        .aiRating = 3,
    },
    
    [ABILITY_GLACIAL_ICE] =
    {
        .name = _("Glacial Ice"),
        .description = sGlacialIceDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_LAVA_FISSURE] =
    {
        .name = _("Lava Fissure"),
        .description = sLavaFissureDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_TOADSTOOL_NYMPH] =
    {
        .name = _("Toadstool Nymph"),
        .description = sToadstoolNymphDescription,
        .aiRating = 3,
    },
    
    [ABILTY_UNKNOWN_POWER] =
    {
        .name = _("Unknown Power"),
        .description = sUnknownPowerDescription,
        .aiRating = 2,
    },
    
    [ABILITY_PURIFYING_AURA] =
    {
        .name = _("Purifying Aura"),
        .description = sPurifyingAuraDescription,
        .aiRating = 0,
    },
    
    [ABILITY_SQUALL] =
    {
        .name = _("Squall"),
        .description = sSquallDescription,
        .aiRating = 7,
    },
    
    [ABILITY_SUN_DISK] =
    {
        .name = _("Sun Disk"),
        .description = sSundiskDescription,
        .aiRating = 7,
    },
    
    [ABILITY_TOUGH_SPINES] =
    {
        .name = _("Tough Spines"),
        .description = sToughSpinesDescription,
        .aiRating = 6,
    },
    
    [ABILITY_EROSION] =
    {
        .name = _("Erosion"),
        .description = sErosionDescription,
        .aiRating = 7,
        .breakable = TRUE,
    },
    
    [ABILITY_LIQUID_METAL] =
    {
        .name = _("Liquid Metal"),
        .description = sLiquidmetalDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_MUSCLE_MAGIC] =
    {
        .name = _("Muscle Magic"),
        .description = sMusclemagicDescription,
        .aiRating = 5,
    },
    
    [ABILITY_TIGER_CUB] =
    {
        .name = _("Tiger Cub"),
        .description = sTigercubDescription,
        .aiRating = 7,
    },
    
    [ABILITY_TIGER_MOM] =
    {
        .name = _("Tiger Mom"),
        .description = sTigerMomDescription,
        .aiRating = 7,
    },
    
    [ABILITY_DARK_DEAL] =
    {
        .name = _("Dark Deal"),
        .description = sDarkDealDescription,
        .aiRating = 6,
    },
    
    [ABILITY_CORRUPTION] =
    {
        .name = _("Corruption"),
        .description = sCorruptionDescription,
        .aiRating = 0,
    },//heal block
    //for sake of balance rather than enemy side
    //could potentially make it work for every battler except the user
    //so would loop all battlers except attacker/holder
    //and set heal block volatile for them
    //and rather than timer won't clear until battler is off field
    //essentailly same setup as neutralizing gas

    
    [ABILITY_BANDIT_KING] =
    {
        .name = _("Bandit King"),
        .description = sBanditKingDescription,
        .aiRating = 0,
    },
    
    [ABILITY_AVIATOR] =
    {
        .name = _("Aviator"),
        .description = sAviatorDescription, 
        .aiRating = 0,
        .breakable = TRUE,
    },//vsonic maybe just need add breakable ot do thing rather than needing moldbreaker check function?
    //yeah think all I need for moldbreaker negate is set every affinity ability as breakable
    //well no its meant to ignore affinity itself not just the ability
    //so its supposed to work through the type would still need negation function
    //or put logic directly into affinity function by adding, atk battler
    //and atk ability arguments to it?
    
    [ABILITY_USURPER] =
    {
        .name = _("Usurper"),
        .description = sUsurperDescription,
        .aiRating = 10,
    },
    
    [ABILITY_INVERSE_WORLD] =
    {
        .name = _("Inverse World"),
        .description = sInverseWorldDescription,
        .aiRating = 9,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },//vsonic IMPORTANT //is field wide effect similar to neutralizing gas unsure what to do with?
    
    [ABILITY_SONAR] =
    {
        .name = _("Sonar"),
        .description = sSonarDescription,
        .aiRating = 0,
    },
    
    [ABILITY_ECOSYSTEM] =
    {
        .name = _("Ecosystem"),
        .description = sEcosystemDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_ABSOLUTE_ZERO] =
    {
        .name = _("Absolute Zero"),
        .description = sAbsolutezeroDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_FEATHER_JACKET] =
    {
        .name = _("Feather Jacket"),
        .description = sFeatherJacketDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_POISONED_LEGACY] =
    {
        .name = _("Poisoned Legacy"),
        .description = sPoisonedLegacyDescription,
        .aiRating = 0,
    },
    
    [ABILITY_JEWEL_METABOLISM] =
    {
        .name = _("Jewel Metabolism"),
        .description = sJewelMetabolismDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_INVERSION] =
    {
        .name = _("Inversion"),
        .description = sInversionDescription,
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },//upgraded imposter
    
    [ABILITY_WETIKO] =
    {
        .name = _("Wetiko"),
        .description = sWetikoDescription,
        .aiRating = 9,
    },
    
    [ABILITY_EMPATH] =
    {
        .name = _("Empath"),
        .description = sEmpathDescription,
        .aiRating = 0,
    },//upgraded Trace same conditions
    //why am I calling this trace when its synchronize?     
    
    [ABILITY_EMPATHIC_CURSE] =
    {
        .name = _("Empathic Curse"),
        .description = sEmpathicCurseDescription,
        .aiRating = 0,
    },
    
    [ABILITY_INTHRALL] =
    {
        .name = _("Inthrall"),
        .description = sInthrallDescription,
        .aiRating = 0,
    },
    
    [ABILITY_IRON_WILL] =
    {
        .name = _("Iron Will"),
        .description = sIronWillDescription,
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_LIVEWIRE] =
    {
        .name = _("Livewire"),
        .description = sLivewireDescription,
        .aiRating = 0,
    },
    
    [ABILITY_GALEFORCE] =
    {
        .name = _("GaleForce"),
        .description = sGaleforceDescription,
        .aiRating = 6,
        .breakable = TRUE,
    },
    
    [ABILITY_LETHAL_LEGS] =
    {
        .name = _("Lethal Legs"),
        .description = sLethalLegsDescription,
        .aiRating = 6,
    },
    
    [ABILITY_TOXUNGUE] =
    {
        .name = _("Toxunge"),
        .description = sToxungueDescription,
        .aiRating = 4,
    },
    
    [ABILITY_OMNIPOTENT_AIDE] =
    {
        .name = _("Omnipotent Aide"),
        .description = sOmnipotentAideDescription,
        .aiRating = 0,
    },
    
    [ABILITY_FLUORESCENCE] =
    {
        .name = _("Fluorescence"),
        .description = sFluorescenceDescription,
        .aiRating = 0,
    },
    
    [ABILITY_SPECTRE] =
    {
        .name = _("Spectre"),
        .description = COMPOUND_ABILITY_STRING("A speeding Blur!\nBoosts Evasion on Switch-in."),
        .aiRating = 0,
    },
    
    [ABILITY_AURA_OF_LIGHT] =
    {
        .name = _("Aura of Light"),
        .description = COMPOUND_ABILITY_STRING("Wakes allies on switch-in and prevents\nsleep. Also cuts damage from dark moves."),
        .aiRating = 0,
        .breakable = TRUE,
    },//vsonic
    
    [ABILITY_DESPAIR] =
    {
        .name = _("Despair"),
        .description = COMPOUND_ABILITY_STRING("Even the waking world becomes a nightmare\nHealing becomes dmg for opposing side."),
        .aiRating = 0,
    },
    //todo - anti heal ability for opposing side plan darkrai use
    //in practice does pretty much same as bad dreams when they try to sleep
    //they'd take damage intead of healing
    //but darkrai won't be healed from it
    //considering if I should put extra protection on this
    //if heal is greater than quarter hp either divide by 2
    //or cap at quarter hp, similar to trap effects
    //use min function I think -done
    //exclusive ability
    
    [ABILITY_RISING_PHOENIX] =
    {
        .name = _("Rising Phoenix"),
        .description = COMPOUND_ABILITY_STRING("Cures status heals and cleanses field if\nhit by fire. May also burn on contact."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_DREAD_WING] =
    {
        .name = _("Dread Wings"),
        .description = COMPOUND_ABILITY_STRING("Spreads despair. Foes take more damage.\nWeakens foes Physical Attacks."),
        .aiRating = 0,
        .breakable = TRUE,
    },//potentially make these two un suppressable?
    //no being unsuppressable is only for things
    //that would break or cause glitches otherwise
    
    [ABILITY_PLAGUE_WINGS] =
    {
        .name = _("Plague Wings"),
        .description = sPlagueWingsDescription,
        .aiRating = 5,
    },
    
    [ABILITY_TOXIC_WING] =
    {
        .name = _("Toxic Wing"),
        .description = COMPOUND_ABILITY_STRING("Spreads poison powder on attack.\nMay poison the foe."),
        .aiRating = 5,
    },
    
    [ABILITY_PHANTOM_TOUCH] =
    {
        .name = _("Phantom Touch"),
        .description = sPhantomTouchDescription,
        .aiRating = 6,
    },
    
    [ABILITY_APOTHEOSCENT] =
    {
        .name = _("Apotheoscent"),
        .description = COMPOUND_ABILITY_STRING("Ignores accuracy and evasion changes.\nImmune to effects of being confused."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_WEIGHTED_GI] =
    {
        .name = _("Weighted Gi"),
        .description = COMPOUND_ABILITY_STRING("Casts off weighted clothes or fur\nwhen in a pinch boosting SPEED."),
        .aiRating = 5,
    },
    
    [ABILITY_VOLT_DASH] =
    {
        .name = _("Volt Dash"),
        .description = COMPOUND_ABILITY_STRING("Turns electricity into HP\nand gradually boosts SPEED."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_IMMUTABLE_WIND] =
    {
        .name = _("Immutable Wind"),
        .description = COMPOUND_ABILITY_STRING("Summons winds that nullify foes abilities\nand blow status moves off course."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },
    
    [ABILITY_EVERGREEN] =
    {
        .name = _("Evergreen"),
        .description = COMPOUND_ABILITY_STRING("Summons Grassy Terrain on switch-in.\nMay also Harvest a Berry."),
        .aiRating = 9,
    },
    
    [ABILITY_SHAMAN_CURE] =
    {
        .name = _("Shaman Cure"),
        .description = COMPOUND_ABILITY_STRING("Protects party from poison.\nCures own status upon switching out."),
        .aiRating = 0,
        .breakable = TRUE,
    },//vsonic
    
    [ABILITY_UNCHAINED_MELODY] =
    {
        .name = _("Unchained Melody"),
        .description = COMPOUND_ABILITY_STRING("Boosts damage of Normal moves\nand converts them to Sound type."),
        .aiRating = 7,
    },
    
    [ABILITY_ENAMEL] =
    {
        .name = _("Enamel"),
        .description = COMPOUND_ABILITY_STRING("Reduces Fire damage and prevents burns."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_BONE_ARMOR] =
    {
        .name = _("Bone Armor"),
        .description = COMPOUND_ABILITY_STRING("Reduces Fire damage and prevents burns.\nPrevents recoil and force switch."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_STORM_BREAK] =
    {
        .name = _("Storm Break"),
        .description = COMPOUND_ABILITY_STRING("User creates a gust of wind dissipating\nweather effects on entry."),
        .aiRating = 5,
    },
    
    [ABILITY_SPACE_CONTROL] =
    {
        .name = _("Space Control"),
        .description = COMPOUND_ABILITY_STRING("Attacks via portal, attacks are 100% Acc\nAdapted to space is immune to Ice Dmg."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_COLD_EMBRACE] =
    {
        .name = _("Cold Embrace"),
        .description = COMPOUND_ABILITY_STRING("Releases sub-zero breath when close.\nMay Freeze foe when they make contact."),
        .aiRating = 4,
    },
    
    [ABILITY_TIME_CONTROL] =
    {
        .name = _("Time Control"),
        .description = COMPOUND_ABILITY_STRING("Every two turns can distort time\nnegating charging and recharge turns."),
        .aiRating = 0,
    },
    
    [ABILITY_TORCHSOUL] =
    {
        .name = _("Torch Soul"),
        .description = COMPOUND_ABILITY_STRING("Possesses a burning inner-flame.\nGain FIRE Affinity and boosts Fire moves."),
        .aiRating = 5,
        .breakable = TRUE,
    },
    
    [ABILITY_GRUNGE] =
    {
        .name = _("Grunge"),
        .description = COMPOUND_ABILITY_STRING("Gain POISON Affinity and boosts damage\ndone by Poison-type moves."),
        .aiRating = 5,
        .breakable = TRUE,
    },
    
    [ABILITY_SWIFT_JUSTICE] =
    {
        .name = _("Swift Justice"),
        .description = COMPOUND_ABILITY_STRING("Stikes swiftly and decisively.\nBoosts damage if attacks before target."),
        .aiRating = 0,
    },
    
    [ABILITY_TOOLS_OF_THE_TRADE] =
    {
        .name = _("Tools of the Trade"),
        .description = COMPOUND_ABILITY_STRING("{UP_ARROW}dmg to foes switching faster or trapped\nUps DEF if statused or stat drops"),
        .aiRating = 7,
        .breakable = TRUE,
    },
    //would like this to boost pursuit dmg
    //idk if it does that
    //breaks stat buff from status not stat drop
    
    [ABILITY_TROJAN_SWORD] =
    {
        .name = _("Trojan Sword"),
        .description = COMPOUND_ABILITY_STRING("Blocks Intimdiate and\nboosts slicing attacks."),
        .aiRating = 0,
    },
    
    [ABILITY_HEAT_TRANCE] =
    {
        .name = _("Heat Trance"),
        .description = COMPOUND_ABILITY_STRING("Elated by all things spicy and hot.\nHeals by burn or sun, cuts Fire Dmg taken"),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_DESERT_DWELLER] =
    {
        .name = _("Desert Dweller"),
        .description = COMPOUND_ABILITY_STRING("Adapted to the extremes of the desert.\nLessens effect of Heat Cold and burn."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_FAIRY_MIST] =
    {
        .name = _("Fairy Mist"),
        .description = COMPOUND_ABILITY_STRING("Normal and Sound moves become Fairy.\nSets Misty Terrain upon entering battle."),
        .aiRating = 0,
    },//vsonic
    
    [ABILITY_COMPASS] =
    {
        .name = _("Compass"),
        .description = COMPOUND_ABILITY_STRING("Locks-on and moves unerringly to foe.\nAll moves used by and against will land."),
        .aiRating = 8,
    },
    
    [ABILITY_HANDS_OF_FATE] =
    {
        .name = _("Hands of Fate"),
        .description = COMPOUND_ABILITY_STRING("Protected from shadowy forces and traps.\nReduces Ghost/Dark dmg and blocks status"),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_DUST_DEVIL] =
    {
        .name = _("Dust Devil"),
        .description = COMPOUND_ABILITY_STRING("Immune to wind damage. Sets Sandstorm.\nUps Attack if the target of a wind effect"),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_PLASMA_OVERDRIVE] =
    {
        .name = _("Plasma Overdrive"),
        .description = COMPOUND_ABILITY_STRING("Moves ignore ability affects, and draws\nin FIRE/ELEC to up Fire moves or Sp. Atk"),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_CREATION_ENGINE] =
    {
        .name = _("Creation Engine"),
        .description = COMPOUND_ABILITY_STRING("Gain STAB and Immunity to Ice Fire & Elec\nWater moves targetting user become Ice."),
        .aiRating = 0,
        .breakable = TRUE,
    },//vsonic
    
    [ABILITY_DARK_CORONA] =
    {
        .name = _("Dark Corona"),
        .description = COMPOUND_ABILITY_STRING("A Tainted Crown of spikes that hurts\nand may poison when foes make contact."),
        .aiRating = 7,
    },
    
    [ABILITY_LUNAR_SOLSTICE] =
    {
        .name = _("Lunar Solstice"),
        .description = COMPOUND_ABILITY_STRING("The POKéMON celebrates the moon.\nTemporarily boosts moonlight in battle."),
        .aiRating = 9,
    },
    
    [ABILITY_LUNAR_POWER] =
    {
        .name = _("Lunar Power"),
        .description = COMPOUND_ABILITY_STRING("Powers up in strong moonlight.\nBoosts Sp. Def avoids Moon based attacks."),
        .aiRating = 3,
        .breakable = TRUE,
    },
    
    [ABILITY_NEW_MOON] =
    {
        .name = _("New Moon"),
        .description = COMPOUND_ABILITY_STRING("Moderate HP recovery in moonlight.\nAlso absorbs Moon based attacks."),
        .aiRating = 3,
        .breakable = TRUE,
    },
    
    [ABILITY_TOXIC_DELUGE] =
    {
        .name = _("Toxic Deluge"),
        .description = COMPOUND_ABILITY_STRING("Summons Acid Rain to Battle."),
        .aiRating = 9,
    },
    
    [ABILITY_RESOLUTE] =
    {
        .name = _("Resolute"),
        .description = COMPOUND_ABILITY_STRING("Changes form if suffering from status\nor if HP falls to or below half Max HP."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },
    
    [ABILITY_PIERCING_HORN] =
    {
        .name = _("Piercing Horn"),
        .description = COMPOUND_ABILITY_STRING("Boosts headbutt moves.\nAttacks foes with sharpened horns."),
        .aiRating = 5,
    },
    
    [ABILITY_X_SIGHT] =
    {
        .name = _("X Sight"),
        .description = COMPOUND_ABILITY_STRING("X-ray Vision reveals battlers held items\nand bypasses Acc check when above 50% hp."),
        .aiRating = 0,
    },//vsonic luxaray specific, may remove trace block?
    
    [ABILITY_PRECISE_STRIKE] =
    {
        .name = _("Precise Strike"),
        .description = COMPOUND_ABILITY_STRING("Powers up Critical Hits.\nDelivers attacks direct to weak points."),
        .aiRating = 3,
    },

    [ABILITY_BRAVERY] =
    {
        .name = _("Bravery"),
        .description = sBraveryDescription,
        .aiRating = 6,
    },

    [ABILITY_FUGUE] =
    {
        .name = _("Fugue"),
        .description = COMPOUND_ABILITY_STRING("Makes sleep and confusion more effective\nagainst targets. Always max turns."),
        .aiRating = 4,
    },

    [ABILITY_SECRET_ARTS] =
    {
        .name = _("Secret Arts"),
        .description = COMPOUND_ABILITY_STRING("Ignores target guard mode. Contact moves\nup to 75 power also evade protection."),
        .aiRating = 5,
    },

    [ABILITY_MIRACLE_POWER] =
    {
        .name = _("Miracle Power"),
        .description = COMPOUND_ABILITY_STRING("Psychic attacks ignore dark immunity.\nPhysical moves use Special offense stat."),
        .aiRating = 6,
    },
};

