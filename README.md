# pandorytool
A tool to automate ROM installation for the Pandora Games 3D  
*Also compatible with PANDORA 9H (thanks akira84!)  	
Work based upon the file "ex mame139 (manque rom zip).zip", uploaded by Thomas Bouvrette.

[![Pandory trailer](https://raw.githubusercontent.com/emuchicken/pandorytool/assets/videos/youtube-SU2iwxVzdmE.jpg)](https://www.youtube.com/watch?v=SU2iwxVzdmE)


## License
pandorytool is "shareware", licensed under the Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0). If you wish to use pandorytool commercially, exceptions to this license are available from @emuchicken.

## IMPORTANT:
We will not take any responsibility on the destruction of your device, or for anything done with this tool.
A backup of your system is recommended - so clone your microsd with win32imager before any alterations are made.  Removing 2 PLAYER PSP titles at this time is IRREVERSIBLE!  Be careful of what you remove from your original PANDORA system.

## Contact & Feedback
If you wish to provide feedback, need help, or just come to say hi! - Please join the Discord channel @ https://discord.gg/Az94Rxn  Any major issues can be added to the github.

## Support Us!
Pandorytool has been worked on with blood, sweat and tears.  If you would like us to continue work on this tool, please consider grabbing us a Coffee at https://www.buymeacoffee.com/CKZbiXa.  
*1 coffee* : The current, *unlocked*, version of Pandory will sent.  (more than 20 roms per system limit lifted)
*3 coffees* : As above, and your email will be saved to a maillist, where you will be sent all major revisions of the UNLOCKED Pandorytool.  
*5 coffees+* : All of above, and shall be remembered forever in the HIGHSCORE CHART underneath *with optional message*

## Clone and compile
```
git clone https://github.com/emuchicken/pandorytool.git
mkdir build
cd build
cmake ..
```

Pandory will also compile on operating systems for grown-ups, such as MacOS/Linux, as long as you have a gcc toolchain, make, cmake and the relevant libraries installed.

## Use *Windows*

**1. Drive preparation for roms.**
Note: - Pandora searches for a main games folder in the order of drive: "USB Stick" > "microSD".  If it finds no such folder it will try installing it to the Pandora internal memory.

*(choose one from below)*
**1a. Add to current microSD in Pandora**
May break games, so be careful.  It is recommended to CLONE your microsd before you alter it! (use win32imager or alternative).
- Format a USB stick, exfat unit size 32kb
- Keep microSD with Pandora games in system when you insert USB stick in step 5.

**1b. "Notty stick"**
Prep USB stick for rom installation- Does not alter Pandora microSD.  When removed, original Pandora games from the microsd are playable.
- Format a USB stick, exfat unit size 32kb
- Create a folder in the root of the USB Stick, named "games" then continue to step 2.

**1c. Creating a fresh microSD**
No Chinese games, but will miss 2 player functionality on PSP titles. (currently not supported)
Users who have destroyed their Pandora games library can start here.

- Format a USB stick, exfat unit size 32kb
- Format your microSD, exfat unit size 32kb.
- Create a folder in the root of ONLY the microSD, named "games"
- Make sure no games folder exists in the root folder of your USB STICK in step 5.

**2. Prepare a ROM directory on your hard drive, and distribute your roms accordingly:**
- Pandory already has the folder ready in the release build.  You can easily extract it from the archive.
	
Folder name|Required filetype
-----------|-----------------
dreamcast|CDI
fba|ZIP
gba|GBA, BIN, AGB, GBZ
gbc|GB, GBC, SGB
mame139|ZIP
mame37|ZIP
mame78|ZIP
megadrive|MDX, MD, SMD, GEN, BIN, CUE, ISO, CHD, SMS, GG, SG
n64|N64
nes|FDS, NES, UNF, UNIF
pcengine|PCE, CUE, CCD, CHD
playstation|IMG, PBP
psp|ISO
snes|SMC, SFC, SWC, FIG, BS
wswan|WSC

**3. Scrape the game data.**
	-Download Skraper (skraper.net)
	-Use the setup wizard. Create RECALBOX file type, select the root ROM folder (step 2), and check "include non-Recalbox rom folders".  Check NEXT, then FINISH.
	-Add missing arcade MAME systems using the add system option.  Click the + button next to the "Wizard", Under "Emulation Arcade" click MAME, then OK.  The new box should be highlighted, click the "GAMES & FRONTEND" then change the folder to the first mame139 directory.  Repeat this step for mame37 and mame78.
	-Click ALL SYSTEMS on the left, then MEDIA.  Click on the 4 IMAGES MIX, then change MEDIA TYPE to VIDEO.  Click on BOX 3D, then the minus to remove it.
	-HIT THE PLAY BUTTON (bottom right) to start scraping.

**4. Run pandory tool to prepare the USB stick**
	-Load up command prompt (Windows key & R, then type in CMD), navigate to the folder you have extracted pandory to.
	-Use the tool.  (If roms directory was C:/roms, and the USB stick was drive O:)
			pandory add c:/roms o:/
	-Let the tool prepare the stick, then safely remove.

**5. Install the games!**
	-Turn on your Pandora Games 3D.
	-When on the games menu, insert USB stick to the BOTTOM USB port of the Pandora Games 3D.
	-Hit the A button to install games

**6. Play!**

## TUTORIAL GUIDE
A step-by-step tutorial video can be found here:

[![Pandory tutorial](https://raw.githubusercontent.com/emuchicken/pandorytool/assets/videos/youtube-10naz1ZUOC4.jpg)](https://www.youtube.com/watch?v=10naz1ZUOC4)

or here: https://www.bitchute.com/video/AgxJKugYWDU4/

## Installation fail
There is a possibility that the install will fail.  Please go through this checklist before asking for further assistance.

1. No more space on destination drive.  Make some space by hitting the back "settings" button on the back of your Pandora device, then go to Games Settings, remove game.

2. Pandory already installed games of that device at an earlier date.  
In order to automate the process, our tool renames files in bulk.  Starting the tool once more, the counter starts from 1, so it'd be like you are trying to install a file with the same name.  As above, push the "settings" button on the back of your Pandora, Games Settings, and remove all the games you have added- FOR THAT SYSTEM ONLY.  You can then re-run Pandory and the installation process.

## Note:
- The restricted version will only support up to 20 titles per system.  Unrestrict by throwing us a cuppa!
- This method will install games to the MicroSD inside the unit.  Please make sure you have enough space for the added titles.  However, if you want to install them to the same USB stick.  You will need to make a folder in the root of the stick named "games", and then inside this, "download".

## Issues:
- The Pandora Games 3D encrypts the data when we use this (mcgames) method.  Unfortunately, at this point in time, we cannot change data once it's on the device, which means no changing of controls re: PSP analogue sticks, perhaps the N64 controls etc. If you want to do this, I'd place the rom in the games/download folder, then alter the data from the configs that were created once running the Pandora.  There may be a way around it if you used a USB N64 pad or something similar however, but more testing is needed.
- PSP games imported with this tool will not include "2 player support".  Due to the way it's programmed, we cannot easily add these with our current tools.
- It is impossible to test every single game imported.  If you find a game that doesn't work, please include in the Games Compatibility list on the Pandory github.
- The current device this was programmed for is the Pandora Games 3D (GB3000, blue board), which came with many titles preinstalled.  Whilst this tool may work with other systems, it will not be a universal PANDORA "KEY".  There are too many models / clones!
- If the rom is not found in skraper, you can change the names of them, which may help SKRAPER find them.  If your game video has not been found, that is not the fault of the PANDORY tool.

## Thanks Highscore chart
1. Runningman2020 - 5
