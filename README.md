# pandorytool
A tool to automate ROM installation for the Pandora Games 3D

## License
pandorytool is "shareware", licensed under the Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0). If you wish to use pandorytool commercially, exceptions to this license are available from @emuchicken.

## IMPORTANT:
We will not take any responsibility on the destruction of your device, or for anything done with this tool.
A backup of your system is recommended - so clone your microsd with win32imager before any alterations are made.  Removing 2 PLAYER PSP titles at this time is IRREVERSIBLE!  Be careful of what you remove from your original PANDORA system.

## Support Us!
pandorytool has been worked on with blood, sweat and tears.  If you would like us to continue work on this tool, please consider grabbing us a Coffee at https://www.buymeacoffee.com/CKZbiXa.  
* All users that donate will be provided with the latest, unlocked and compiled version of Pandory.  If required, we will 

## Clone and compile
```
git clone https://github.com/emuchicken/pandorytool.git
mkdir build
cd build
cmake ..
```

Pandory will compile on other operating systems, such as MacOS/Linux, as long as you have a gcc toolchain, make, cmake and the relevant libraries installed.

## Use *with Windows machine:

1. Format a USB stick, exfat unit size 32kb
2. Prepare a ROM directory on your hard drive, and distribute your roms accordingly: *The archive will have all folders ready*
	
  Folder name						Required filetype
	dreamcast						CDI
	fba								ZIP
	gba								GBA / BIN / AGB / GBZ
	gbc								GB / GBC / SGB
	mame139							ZIP
	mame37							ZIP
	mame78							ZIP
	megadrive						MDX / MD / SMD / GEN / BIN / CUE / ISO / CHD / SMS / GG / SG
	n64								N64
	nes								FDS / NES / UNF / UNIF
	pcengine						PCE / CUE / CCD / CHD
	playstation						IMG / PBP (possible??)
	psp								ISO
	snes							SMC / SFC / SWC / FIG / BS
	wswan							WSC

3. Scrape the game data.
	-Download Skraper (skraper.net)
	-Use the setup wizard. Create RECALBOX file type, select the root ROM folder (step 2), and check "include non-Recalbox rom folders".  Check NEXT, then FINISH.
	-Add missing arcade MAME systems using the add system option.  Click the + button next to the "Wizard", Under "Emulation Arcade" click MAME, then OK.  The new box should be highlighted, click the "GAMES & FRONTEND" then change the folder to the first mame139 directory.  Repeat this step for mame37 and mame78.
	-Click ALL SYSTEMS on the left, then MEDIA.  Click on the 4 IMAGES MIX, then change MEDIA TYPE to VIDEO.  Click on BOX 3D, then the minus to remove it.
	-HIT THE PLAY BUTTON (bottom right) to start scraping.

4. Run pandory tool to prepare the USB stick
	-Load up command prompt (windows key & R, then type in CMD), navigate to the folder you have extracted pandory to.
	-Use the tool.  (If roms directory was C:/roms, and the USB stick was drive O:)
			pandory add c:/roms o:/
	-Let the tool prepare the stick, then safely remove.

5. Install the games!
	-Turn on your Pandora Games 3D.
	-When on the games menu, insert USB stick to the BOTTOM USB port of the Pandora Games 3D.
	-Hit the A button to install games

6. Play!

## Issues:
- The Pandora Games 3D encrypts the data when we use this (mcgames) method.  Unfortunately, at this point in time, we cannot change data once it's on the device, which means no changing of controls re: PSP analogue sticks, perhaps the N64 controls etc. If you want to do this, I'd place the rom in the games/download folder, then alter the data from the configs that were created once running the Pandora.  There may be a way around it if you used a USB N64 pad or something similar however, but more testing is needed.
- PSP games imported with this tool will not include "2 player support".  Due to the way it's programmed (Suspected faked ADHOC commands from within the emulator), we cannot easily add these with our current tools.
- The current device this was programmed for is the Pandora Games 3D (BLUE BOARD), which came with a ton of games.  Whilst this tool may work with other systems (I'm looking at the Pandora handheld, and the WIFI version), it will not be a universal PANDORA "KEY"
- If the rom is not found in skraper, you can change the names of them, which may help SKRAPER find them.  If your game video has not been found, that is not the fault of the PANDORY tool.
- All games have not been tested, so if anything is found to be not working, please add it to the games compatibility thread in the github.

## Thanks
