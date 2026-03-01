#ifndef BATTLE_PARTNER_H
#define BATTLE_PARTNER_H

#include "constants/battle_partner.h"

//had some form of error unsure what is
//this extern is also in data.h assumption 
//is actually linked to trainerproc which I don't use
//extern const struct Trainer gBattlePartners[PARTNER_COUNT];

void FillPartnerParty(u16 trainerId);

#endif // BATTLE_PARTNER_H
