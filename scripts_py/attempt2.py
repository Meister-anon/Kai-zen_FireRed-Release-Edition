
import re

exceptions = [ # the following exceptions are hardcoded to streamline the process. you may need to manually check what happens in case you have added forms that work similar to these below
    ["AlcremieStrawberryRubyCream", "AlcremieStrawberry"],
    ["AlcremieStrawberryMatchaCream", "AlcremieStrawberry"],
    ["AlcremieStrawberryMintCream", "AlcremieStrawberry"],
    ["AlcremieStrawberryLemonCream", "AlcremieStrawberry"],
    ["AlcremieStrawberrySaltedCream", "AlcremieStrawberry"],
    ["AlcremieStrawberryRubySwirl", "AlcremieStrawberry"],
    ["AlcremieStrawberryCaramelSwirl", "AlcremieStrawberry"],
    ["AlcremieStrawberryRainbowSwirl", "AlcremieStrawberry"],
    ["AlcremieBlueberryVanillaCream", "AlcremieBlueberry"],
    ["AlcremieBlueberryRubyCream", "AlcremieBlueberry"],
    ["AlcremieBlueberryMatchaCream", "AlcremieBlueberry"],
    ["AlcremieBlueberryMintCream", "AlcremieBlueberry"],
    ["AlcremieBlueberryLemonCream", "AlcremieBlueberry"],
    ["AlcremieBlueberrySaltedCream", "AlcremieBlueberry"],
    ["AlcremieBlueberryRubySwirl", "AlcremieBlueberry"],
    ["AlcremieBlueberryCaramelSwirl", "AlcremieBlueberry"],
    ["AlcremieBlueberryRainbowSwirl", "AlcremieBlueberry"],
    ["AlcremieLoveVanillaCream", "AlcremieLove"],
    ["AlcremieLoveRubyCream", "AlcremieLove"],
    ["AlcremieLoveMatchaCream", "AlcremieLove"],
    ["AlcremieLoveMintCream", "AlcremieLove"],
    ["AlcremieLoveLemonCream", "AlcremieLove"],
    ["AlcremieLoveSaltedCream", "AlcremieLove"],
    ["AlcremieLoveRubySwirl", "AlcremieLove"],
    ["AlcremieLoveCaramelSwirl", "AlcremieLove"],
    ["AlcremieLoveRainbowSwirl", "AlcremieLove"],
    ["AlcremieStarVanillaCream", "AlcremieStar"],
    ["AlcremieStarRubyCream", "AlcremieStar"],
    ["AlcremieStarMatchaCream", "AlcremieStar"],
    ["AlcremieStarMintCream", "AlcremieStar"],
    ["AlcremieStarLemonCream", "AlcremieStar"],
    ["AlcremieStarSaltedCream", "AlcremieStar"],
    ["AlcremieStarRubySwirl", "AlcremieStar"],
    ["AlcremieStarCaramelSwirl", "AlcremieStar"],
    ["AlcremieStarRainbowSwirl", "AlcremieStar"],
    ["AlcremieCloverVanillaCream", "AlcremieClover"],
    ["AlcremieCloverRubyCream", "AlcremieClover"],
    ["AlcremieCloverMatchaCream", "AlcremieClover"],
    ["AlcremieCloverMintCream", "AlcremieClover"],
    ["AlcremieCloverLemonCream", "AlcremieClover"],
    ["AlcremieCloverSaltedCream", "AlcremieClover"],
    ["AlcremieCloverRubySwirl", "AlcremieClover"],
    ["AlcremieCloverCaramelSwirl", "AlcremieClover"],
    ["AlcremieCloverRainbowSwirl", "AlcremieClover"],
    ["AlcremieFlowerVanillaCream", "AlcremieFlower"],
    ["AlcremieFlowerRubyCream", "AlcremieFlower"],
    ["AlcremieFlowerMatchaCream", "AlcremieFlower"],
    ["AlcremieFlowerMintCream", "AlcremieFlower"],
    ["AlcremieFlowerLemonCream", "AlcremieFlower"],
    ["AlcremieFlowerSaltedCream", "AlcremieFlower"],
    ["AlcremieFlowerRubySwirl", "AlcremieFlower"],
    ["AlcremieFlowerCaramelSwirl", "AlcremieFlower"],
    ["AlcremieFlowerRainbowSwirl", "AlcremieFlower"],
    ["AlcremieRibbonVanillaCream", "AlcremieRibbon"],
    ["AlcremieRibbonRubyCream", "AlcremieRibbon"],
    ["AlcremieRibbonMatchaCream", "AlcremieRibbon"],
    ["AlcremieRibbonMintCream", "AlcremieRibbon"],
    ["AlcremieRibbonLemonCream", "AlcremieRibbon"],
    ["AlcremieRibbonSaltedCream", "AlcremieRibbon"],
    ["AlcremieRibbonRubySwirl", "AlcremieRibbon"],
    ["AlcremieRibbonCaramelSwirl", "AlcremieRibbon"],
    ["AlcremieRibbonRainbowSwirl", "AlcremieRibbon"]
]

infile = open('/usr/decomp/Kai-zen_Firered-ReleaseEdition/src/data/pokemon/species_graphic_info.h', 'r')
lines = infile.readlines()
reg = re.compile(r'\[SPECIES_(\w+?)\]')
species = None
new_lines = []
for line in lines:
    if m := reg.match(line):
        species = m.group(1).replace('_', ' ').title().replace(' ', '')#replace underscore w space to separate run title function then remove space
    if species:
        #for x in exceptions:
        #    if species == x[0]:
        #        species = x[1]
        line = line.replace('CircledQuestionMark', species)
        #line = line.replace(r'//FRONT_PIC\(Arceus\w+?\)', 'FRONT_PIC\(Arceus\)')
        #think can use, if put in all exceptions
    new_lines.append(line)
infile.close()#think group is reg stuff reg are broken into groups
#if that is correct than I might be able to use that to store 2 values
#say match group1 for mon size  and group2 for the yoffset?

outfile = open('/usr/decomp/Kai-zen_Firered-ReleaseEdition/src/data/pokemon/species_graphic_info.h', 'w')
outfile.writelines(new_lines)
outfile.close()