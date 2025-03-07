#ifndef GUARD_ITEM_H
#define GUARD_ITEM_H

#include "global.h"

typedef void (*ItemUseFunc)(u8);

struct Item
{
    u8 name[ITEM_NAME_LENGTH];
    u16 itemId;
    u16 price;
    u8 holdEffect;
    u8 holdEffectParam;
    const u8 *description;
    u8 importance;
    u8 exitsBagOnUse;
    u8 pocket;
    u8 type;    //first glance this seems to just be about how the menu callback works, i.e fadeout etc., will copy emerald setup, value 1 seems ot be from party, other values seem to be use from bag?
    ItemUseFunc fieldUseFunc; //seems only value 1 and 2 have an effect, otherwise just executes a default behavior? idk, seems work diff for pokeballs
    //u8 battleUsage;     //doesn't exist in emerald, searched seems this is only relevant to firered because its only used for contextmenu i.e help menu, which I've removed
    ItemUseFunc battleUseFunc; //meaning I could remove this to save room for adding fling logic, logic for it is only necessary because json, so just remove and it'll be fine
    u16 secondaryId; //actually battleUsage doesnt seem to have special json rule so maybe not an issue?
    u8 flingPower;
};//got battleusage wrong context menu isn't help menu, it tells it what strings to display i.e use, give, cancel, etc. instead of usage value try to get to check for battle usage func not 0
//replacing with battleusefunc check worked, can remove
//removed item.json values for json_data_rules.mk able to build without battleUsage, but still follows json rull for moveinfo etc.
//turned secondaryId into u16, so can store move id there for tms like in EE
struct BagPocket
{
    struct ItemSlot *itemSlots;
    u8 capacity;
};

extern const struct Item gItems[];
extern struct BagPocket gBagPockets[];

void GetBerryCountString(u8* dst, const u8* berryName, u32 quantity);
void CopyItemName(u16 itemId, u8 *string);
void CopyItemNameHandlePlural(u16 itemId, u8 *string, u32 quantity);
bool8 IsBagPocketNonEmpty(u8 pocket);
bool8 CheckBagHasItem(u16 itemId, u16 count);
bool8 CheckBagHasSpace(u16 itemId, u16 count);
bool8 RemoveBagItem(u16 itemId, u16 count);
u8 GetPocketByItemId(u16 itemId);
void ClearItemSlots(struct ItemSlot *itemSlots, u8 b);
u8 CountUsedPCItemSlots(void);
bool8 CheckPCHasItem(u16 itemId, u16 count);
bool8 AddPCItem(u16 itemId, u16 count);
void SwapRegisteredBike(void);
const u8 *ItemId_GetName(u16 itemId);
u16 ItemId_GetId(u16 itemId);   //added here, could use, but most use hold effect, no reason not to...
u16 ItemId_GetPrice(u16 itemId);
u8 ItemId_GetHoldEffect(u16 itemId);
u8 ItemId_GetHoldEffectParam(u16 itemId);
const u8 *ItemId_GetDescription(u16 itemId);
bool32 ItemId_CopyDescription(u8 *a, u32 itemId, u32 c);
u8 ItemId_GetImportance(u16 itemId);
u8 ItemId_GetUnknownValue(u16 itemId);
u8 ItemId_GetPocket(u16 itemId);
u8 ItemId_GetType(u16 itemId);
ItemUseFunc ItemId_GetFieldFunc(u16 itemId);
u8 ItemId_GetBattleUsage(u16 itemId);   //not using now, usnig battlfunc check instead
ItemUseFunc ItemId_GetBattleFunc(u16 itemId);
u8 ItemId_GetSecondaryId(u16 itemId);
u16 itemid_get_market_price(u16 itemId);
u16 itemid_get_Id(u16 itemId);
void ClearBag(void);
void ClearPCItemSlots(void);
void TrySetObtainedItemQuestLogEvent(u16 itemId);
bool8 AddBagItem(u16 itemId, u16 amount);

u16 GetBagItemQuantity(u16 * quantity); //global in advance of applying ghoul slash bag sort

void SortPocketAndPlaceHMsFirst(struct BagPocket * pocket);
u16 BagGetItemIdByPocketPosition(u8 pocketId, u16 itemId);
u16 BagGetQuantityByPocketPosition(u8 pocketId, u16 itemId);
u16 BagGetQuantityByItemId(u16 item);
bool8 itemid_is_unique(u16 itemId);
void BagPocketCompaction(struct ItemSlot * slots, u8 capacity);
u16 GetPcItemQuantity(u16 *);
void SetBagPocketsPointers(void);

void ItemPcCompaction(void);
void RemovePCItem(u16 itemId, u16 quantity);
void SortAndCompactBagPocket(struct BagPocket * pocket);
void SortAndCompactTmCase(struct BagPocket * pocket); //comparable function specific for tmcase
u8 CountItemsInPC(void);
void ApplyNewEncryptionKeyToBagItems_(u32 newKey);
bool8 CheckHasAtLeastOneBerry(void);

u16 SanitizeItemId(u16 itemId);

#endif // GUARD_ITEM_H
