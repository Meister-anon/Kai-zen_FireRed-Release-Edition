# Default variables

GAME_VERSION  ?= FIRERED
GAME_REVISION ?= 0
GAME_LANGUAGE ?= ENGLISH
MODERN        ?= 1
COMPARE       ?= 0
TEST         ?= 0

ifeq (compare,$(MAKECMDGOALS))
  COMPARE := 1
endif

# For gbafix
MAKER_CODE  := 01

# Version
ifeq ($(GAME_VERSION),FIRERED)
TITLE       := POKEMON FIRE
GAME_CODE   := BPR
BUILD_NAME  := firered
else
ifeq ($(GAME_VERSION),LEAFGREEN)
TITLE       := POKEMON LEAF
GAME_CODE   := BPG
BUILD_NAME  := leafgreen
else
$(error unknown version $(GAME_VERSION))
endif
endif

ifeq (check,$(MAKECMDGOALS))
  TEST := 1
endif

# Revision
ifeq ($(GAME_REVISION),0)
BUILD_NAME  := $(BUILD_NAME)
else
ifeq ($(GAME_REVISION),1)
BUILD_NAME  := $(BUILD_NAME)_rev1
else
$(error unknown revision $(GAME_REVISION))
endif
endif

#ifeq (agbcc,$(MAKECMDGOALS))
ifeq (old,$(MAKECMDGOALS))
  MODERN := 0
endif

# Language
ifeq ($(GAME_LANGUAGE),ENGLISH)
BUILD_NAME  := $(BUILD_NAME)
GAME_CODE   := $(GAME_CODE)E
else
$(error unknown language $(GAME_LANGUAGE))
endif

# Modern GCC
ifeq ($(MODERN), 0)
  BUILD_NAME := $(BUILD_NAME)
else
  BUILD_NAME := $(BUILD_NAME)_modern
endif
