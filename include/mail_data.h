#ifndef GUARD_MAIL_DATA_H
#define GUARD_MAIL_DATA_H

#include "global.h"

// Exported type declarations

// Exported RAM declarations

// Exported ROM declarations

void ClearMailData(void);
void ClearMailStruct(struct MailStruct *mail);
bool8 MonHasMail(struct Pokemon *mon);
bool8 BoxMonHasMail(struct BoxPokemon *mon); //not really used
u8 GiveMailToMon(struct Pokemon *mon, u16 itemId);
u16 SpeciesToMailSpecies(u16 species, u32 personality);
u16 MailSpeciesToSpecies(u16 mailSpecies, u16 *buffer);
u8 GiveMailToMon2(struct Pokemon *mon, struct MailStruct *mail);
void TakeMailFromMon(struct Pokemon *mon);
void TakeMailFromBoxMon(struct BoxPokemon *mon);
void ClearMailItemId(u8 mailId);
u8 TakeMailFromMon2(struct Pokemon *mon);
bool8 ItemIsMail(u16 itemId);

#endif //GUARD_MAIL_DATA_H
