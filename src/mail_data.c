#include "global.h"
#include "gflib.h"
#include "mail.h"
#include "mail_data.h"
#include "constants/items.h"
#include "pokemon_icon.h"

void ClearMailData(void)
{
    u8 i;

    for (i = 0; i < MAIL_COUNT; i++)
        ClearMailStruct(&gSaveBlock1Ptr->mail[i]);
}

void ClearMailStruct(struct MailStruct *mail)
{
    s32 i;

    for (i = 0; i < MAIL_WORDS_COUNT; i++)
        mail->words[i] = 0xFFFF;
    for (i = 0; i < PLAYER_NAME_LENGTH + 1; i++)
        mail->playerName[i] = EOS;
    for (i = 0; i < 4; i++)
        mail->trainerId[i] = 0;
    mail->species = SPECIES_BULBASAUR;
    mail->itemId = ITEM_NONE;
}

bool8 BoxMonHasMail(struct BoxPokemon *mon)
{
    u16 heldItem = GetBoxMonData(mon, MON_DATA_HELD_ITEM);
    if (ItemIsMail(heldItem) && GetBoxMonData(mon, MON_DATA_MAIL) != MAIL_NONE)
        return TRUE;
    else
        return FALSE;
}

bool8 MonHasMail(struct Pokemon *mon)
{
    u16 heldItem = GetMonData(mon, MON_DATA_HELD_ITEM);
    if (ItemIsMail(heldItem) && GetMonData(mon, MON_DATA_MAIL) != MAIL_NONE)
        return TRUE;
    else
        return FALSE;
}

u8 GiveMailToMon(struct Pokemon *mon, u16 itemId)
{
    u8 heldItem[2];
    u8 id, i;
    u16 species;
    u32 personality;

    heldItem[0] = itemId;
    heldItem[1] = itemId >> 8;
    for (id = 0; id < PARTY_SIZE; id++)
    {
        if (gSaveBlock1Ptr->mail[id].itemId == 0)
        {
            for (i = 0; i < MAIL_WORDS_COUNT; i++)
                gSaveBlock1Ptr->mail[id].words[i] = 0xFFFF;
            for (i = 0; i < PLAYER_NAME_LENGTH && gSaveBlock2Ptr->playerName[i] != EOS; i++)
                gSaveBlock1Ptr->mail[id].playerName[i] = gSaveBlock2Ptr->playerName[i];
            for (; i <= 5; i++)
            	gSaveBlock1Ptr->mail[id].playerName[i] = CHAR_SPACE;
            gSaveBlock1Ptr->mail[id].playerName[i] = EOS;
            for (i = 0; i < 4; i++)
                gSaveBlock1Ptr->mail[id].trainerId[i] = gSaveBlock2Ptr->playerTrainerId[i];
            species = GetBoxMonData(&mon->box, MON_DATA_SPECIES);
            personality = GetBoxMonData(&mon->box, MON_DATA_PERSONALITY);
            gSaveBlock1Ptr->mail[id].species = SpeciesToMailSpecies(species, personality);
            gSaveBlock1Ptr->mail[id].itemId = itemId;
            SetMonData(mon, MON_DATA_MAIL, &id);
            SetMonData(mon, MON_DATA_HELD_ITEM, heldItem);
            return id;
        }
    }
    return 0xFF;
}

u16 SpeciesToMailSpecies(u16 species, u32 personality)
{
    if (species == SPECIES_UNOWN) {
        u32 mailSpecies = GetUnownLetterByPersonality(personality) + 30000;
        return mailSpecies;
    }
    return species;
}

u16 MailSpeciesToSpecies(u16 mailSpecies, u16 *unownLetter)
{
    u16 result;

    if (mailSpecies >= 30000 && mailSpecies < (30000 + UNOWN_FORM_COUNT))
    {
        result = SPECIES_UNOWN;
        *unownLetter = mailSpecies - 30000;
    }
    else
    {
        result = mailSpecies;
    }
    return result;
}

u8 GiveMailToMon2(struct Pokemon *mon, struct MailStruct *mail)
{
    u8 heldItem[2];
    u16 itemId = mail->itemId;
    u8 mailId = GiveMailToMon(mon, itemId);

    if (mailId == MAIL_NONE)
        return MAIL_NONE;
    gSaveBlock1Ptr->mail[mailId] = *mail;
    SetMonData(mon, MON_DATA_MAIL, &mailId);
    heldItem[0] = itemId;
    heldItem[1] = itemId >> 8;

    SetMonData(mon, MON_DATA_HELD_ITEM, heldItem);

    return mailId;
}

static bool32 DummyMailFunc(void)
{
    return FALSE;
}

void TakeMailFromMon(struct Pokemon *mon)
{
    u8 heldItem[2];
    u8 mailId;

    if (MonHasMail(mon))
    {
        mailId = GetMonData(mon, MON_DATA_MAIL);
        gSaveBlock1Ptr->mail[mailId].itemId = ITEM_NONE;
        mailId = MAIL_NONE;
        heldItem[0] = ITEM_NONE;
        heldItem[1] = ITEM_NONE << 8;
        SetMonData(mon, MON_DATA_MAIL, &mailId);
        SetMonData(mon, MON_DATA_HELD_ITEM, heldItem);
    }
}

void TakeMailFromBoxMon(struct BoxPokemon *mon)
{
    u8 heldItem[2];
    u8 mailId;

    if (BoxMonHasMail(mon))
    {
        mailId = GetBoxMonData(mon, MON_DATA_MAIL);
        gSaveBlock1Ptr->mail[mailId].itemId = ITEM_NONE;
        mailId = MAIL_NONE;
        heldItem[0] = ITEM_NONE;
        heldItem[1] = ITEM_NONE << 8;
        SetBoxMonData(mon, MON_DATA_MAIL, &mailId);
        SetBoxMonData(mon, MON_DATA_HELD_ITEM, heldItem);
    }
}

void ClearMailItemId(u8 mailId)
{
    gSaveBlock1Ptr->mail[mailId].itemId = ITEM_NONE;
}

u8 TakeMailFromMon2(struct Pokemon *mon)
{
    u8 i, newMailId;
    u8 newHeldItem[2];

    newHeldItem[0] = ITEM_NONE;
    newHeldItem[1] = ITEM_NONE << 8;
    newMailId = 0xFF;
    for (i = PARTY_SIZE; i < MAIL_COUNT; i++)
    {
        if (gSaveBlock1Ptr->mail[i].itemId == ITEM_NONE)
        {
            memcpy(&gSaveBlock1Ptr->mail[i], &gSaveBlock1Ptr->mail[GetMonData(mon, MON_DATA_MAIL)], sizeof(struct MailStruct));
            gSaveBlock1Ptr->mail[GetMonData(mon, MON_DATA_MAIL)].itemId = ITEM_NONE;
            SetMonData(mon, MON_DATA_MAIL, &newMailId);
            SetMonData(mon, MON_DATA_HELD_ITEM, newHeldItem);
            return i;
        }
    }
    return 0xFF;
}

bool8 ItemIsMail(u16 itemId)
{
    switch (itemId)
    {
    case ITEM_ORANGE_MAIL:
    case ITEM_HARBOR_MAIL:
    case ITEM_GLITTER_MAIL:
    case ITEM_MECH_MAIL:
    case ITEM_WOOD_MAIL:
    case ITEM_WAVE_MAIL:
    case ITEM_BEAD_MAIL:
    case ITEM_SHADOW_MAIL:
    case ITEM_TROPIC_MAIL:
    case ITEM_DREAM_MAIL:
    case ITEM_FAB_MAIL:
    case ITEM_RETRO_MAIL:
        return TRUE;
    default:
        return FALSE;
    }
}
