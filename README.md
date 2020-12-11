# Pandorytool + Jailbreak
A tool to automate ROM installation for the Pandora Games 3D / Saga 3D compatible systems / GOLDENSKY G6 / PANDORA 9H*)

* No jailbreak yet on the 9H.

<p align="center">
  <img width="600" src="https://raw.githubusercontent.com/emuchicken/pandorytool/master/docs/pandory.gif">
</p>

## License
pandorytool is "shareware", licensed under the Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0), with the additional condition that you do not provide/redistribute compiled binaries of the source code. 
If you wish to use pandorytool commercially, exceptions to this license are available from @emuchicken.

## IMPORTANT:
We will not take any responsibility on the destruction of your device, or for anything done with this tool.
A backup of your system is recommended - so clone your microsd with win32imager before any alterations are made.  Removing 2 PLAYER PSP titles at this time is IRREVERSIBLE!  Be careful of what you remove from your original PANDORA system.

## Contact & Feedback
If you wish to provide feedback, need help, or just come to say hi! - Please join the Discord channel @ https://discord.gg/rPKhJCT Any major issues can be added to the github.

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

## USE *Windows*
**1. Target Drive preparation for roms.**
Note: - Your Pandora device searches for a main games folder in the order of drive: "USB Stick" > "microSD".  If it finds no such folder it will try installing it to the Pandora internal memory.

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
- Pandory can also create the required folders by using the argument "prepare", for example: "pandory prepare c:/roms" will create the directory tree in your c:/roms folder.

Please see the Supported_Roms.md for more info on which roms and systems Pandory can install.

**3. Scrape the game data.**

*Attention: don't add 14000 roms on your first go! It will crash the menu!*

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

3. MAME title has multiple entries.  Even if the folder is separate, the Pandora unit places the MAME/FBA titles in the same folder, and the filenames cannot be altered.  Please go through your selection and select one title- OR use a rom with another filename.  An example being captcomm.zip (parent rom) and captcommu.zip (the USA release)

## Note:
- The restricted free build will only support up to 20 titles per system.  Unrestrict this by donating a cup of coffee @ https://www.buymeacoffee.com/CKZbiXa
- This method will install games to the MicroSD inside the unit.  Please make sure you have enough space for the added titles.  If you would like to install them to the same USB stick, you need to create a folder in the root of the stick named "games", and then inside this, "download".

# STICK
- From Pandory 1.0.4, we have included the "stick" modifier to the pandory tool.  We can create USB sticks to perform different tasks for our PG3D.  For these operations, make sure we have a cleanly formatted exfat w/ 32kb partition size.

## 1. BACKUP
- It is recommended to keep a backup of your system data, in case you end up with a "brick".  You can easily backup with Pandory tool.

1. Load up command prompt (Windows key & R, then type in CMD), navigate to the folder you have extracted pandory to.
2. Use the tool.  *If the USB stick was drive O:*  pandory.exe stick backup O:/
4. Let the tool prepare the stick, then safely remove.
5. Start up your Pandora (with microsd inserted)
6. Insert your usb stick into bottom USB port, and wait.
7. Once finished, your Pandora should reboot into the games menu.
8. Turn off system, insert usbstick into PC, then copy off all files to your computer for safe keeping.

*note: It SHOULD reboot then load up into an Android robot screen backing up.  It usually takes around 10 minutes for the whole processe to complete.  If you get Chinese writing, please reboot and try once again.  It may hang on the Android robot screen-  if this is the case, please wait a little longer, longer than 30 minutes? Then try a reboot and start once more.
*note2: If the usbstick doesn't load up, reset the Pandora, try again.  Try copying the file over, try another usb stick... The Chinese jank is real with this box!

## 2. JAILBREAK (1.2)
## PLEASE BACKUP using STICK BACKUP (in the section above) BEFORE trying this!

Version 1.2 of the Pandory Jailbreak includes many new features.

## 2A. Android / Switch
- We now can enter Android / pull back to the Pandora Games menu, by tapping 5x the pause button.

## 2B. 4:3 Automatic Aspect mode switch (Pandory Ultimate only)
- Our jailbreak now automatically chooses either stretch, or 4:3 aspect mode depending on the emulator which is called.  PPSSPP, Dreamcast are left as they are, but MAME, FBA and the others will be set to 4:3.  When creating the Pandory Jailbreak stick, the user will get a choice.  If you already have a 4:3 monitor, please hit V.  On a 16:9 or 16:10, use any other key.

## 2C. 4:3 Aspect mode Switch (Pandory Ultimate only)
- P1 START and button E together. It will switch from stretch to 4:3 and vice versa.  Some MAME vertical shooters may need this when automatic switch fails.

## 2D. Pause menu switch
- P1 START and button F together.  Pause, exit, save state, load state menu.

## 2E.  System Settings switch
- P1 START, buttons D, E and F together.  Switches to the system settings.

## 2F. Video mode debrick
- From Jailbreak 1.2, we have added a method to unbrick the device with one button.  On installing JB1.2, it will automatically place a backup of your video settings.

- We've had some nutcases that started hitting up 1080p on their 720p Pandora boxes, which bricks the unit.  To fix?

1. Load up the Pandora Games system.
2. On the games menu, hold down PAUSE for 35 seconds.  Then release.
3. Celebrate!

## 2G. Remote adb
The jailbreak automatically starts the adb daemon for you and switches it to TCP listening mode. This means you can now connect to adb wirelessly over the network using the following commands:

adb connect ip-address-of-pandora:5555
adb shell

You can also install apks wirelessly with:
adb install example.apk

Or push files to the system with:
adb push C:\local\file.txt /data/file.txt

## 2H. Remote Telnet
No adb installed? No problem! The jailbreak also listens using telnet on port 4444. Use any telnet client (even from your phone) to connect to: 

ip-address-of-pandora, port 4444

Try logging in and typing: 
am start -n com.android.launcher/com.android.launcher2.Launcher

## 2I. Added LAN (wired) Network support for USB hubs
- Forgot to buy the WIFI model?  No worries!  With a USB hub (with LAN network support), we can use the internet and local network!  Note, this will not open the Pandora WIFI shop for you- but with this you will be able to use the Remote adb, Remote Telnet, and even the Android APK sites to install directly from your box!

## Installing the Jailbreak
1. Load up command prompt (Windows key & R, then type in CMD), navigate to the folder you have extracted pandory to.
2. Use the tool.  *If the USB stick was drive O:* -  pandory.exe stick jailbreak O:/
3. At the prompt, push V if you have a 4:3 display in VGA-  if not- push the any key.
4. Let the tool prepare the stick, then safely remove.
5. Start up your Pandora (with microsd inserted)
6. Insert your usb stick into bottom USB port, and wait.
7. Once Jailbreak has finished, you should be greeted by a new video.

*note: It SHOULD reboot then load up into an Android robot screen backing up.  It usually takes around 10 minutes for the whole processe to complete.  If you get Chinese writing, please reboot and try once again.  If any reason it should fail, please start from the first step.  You can also try another usb stick.

## 3. ALTERNATIVE STICKS
... To be continued...  Soon!

# PSP FIXES
## PLEASE BACKUP MICROSD BEFORE TRYING THIS!

## 4A. PSP Control fixes
- Our tool now can fix the install stock games, by fixing controls and optimizing the configs.  Controls have been changed so that the standard Pandora Games 3D arcade layout will be similar to the PSP format, with the PSP front buttons as the 4 far left buttons.  L and R are usually on the very right, but some games have been changed to play better as an arcade title.
- Kingdom Hearts, Daxter, Monster Hunter, and the Dynasty Warrior / Orochi titles are all now playable as the left stick controls have been fixed.
- Button *6* on P2 controller will flip P1 stick controls from an analogue stick to a dpad.  If you find that you cannot control the player, push this button.
- Start button on P2 controller will throw you into the PPSSPP settings screen.  Here you can save states, load states, or mess with graphics settings.  This has been removed for 2P titles.
- 2 Player titles are also configured, but this feature is only for (Pandory Ultimate only)

## 4B. PSP Settings fixes / optimizing
- We have altered some settings which should gain a few fps, or fix some stock titles.
- PES2012.  How about and English menu?  We flipped it over for you :-)
- WWE.  Optimized for quicker fps ingame.  Also how about a few more fighters to your roster?
- Tekken 5, for example had a level or two that would bug out the emulator at stock, and can be fixed by using the BUFFERED graphics setting.  Unfortunately, this makes the title look a bit worse than it was, but at least you can now complete the game in it's entirety.

## 4C. Added 2 Player games!
- We have added 2 player functionality in some stock titles!!  Soul Calibur, PES2012, and NBA06 (more to come?)  Push 2P start to smash into some VS action!
- Please note, 2P Soul Calibur cannot "see" their icon whilst choosing their character.  Just a heads up!

## 4D. PPSSPP on the menu
- The Pandory PSP Injector icon on the games menu will load up PPSSPP directly.  You will be able to also load up CSO files from a usb stick if you wish from this.  Might be a handy way to check iso/cso files from your memory stick?

## 4E. Using PSPFIX
As it alters a files, it is wise to make sure you have a backup, just in case this breaks your games.  Remember, we can only test this on the systems we own (currently, a 2448 Pandora Games 3D) - We do not have unlimited resources or time to test every single version of Pandora on the market.  Check our video to help make one for peace of mind.

1. Insert a *preferably cleanly, formatted exfat usb stick* to your computer- and find out the usb stick's drive name. 
2. Use the tool.  *If the USB stick was drive O:* -   pandory pspfix stage1 O:/
3. Let the tool prepare the usb, then safely remove.
4. Start up your Pandora (with microsd inserted w/ stock games), then insert USB stick.
5. Wait, then let the Pandora install PSPFix.
6. After installation has completed, turn off your Pandora unit, then remove the microSD and USB stick.
7. Insert microSD into your computer, then find the drive name.
8. Use the tool.  *If the microSD was drive Q:* - pandory pspfix stage2 Q:/
9. Safely remove the microSD, insert it into your Pandora device.

## UNBRICKING YOUR DEVICE
- Ended up killing your system, somehow?  We have... Many times.

1. Pandora starts, but NO VIDEO!?  Please see section 2F under the Jailbreak section above.  It's a one button process!
2. Messing with SYSTEM settings.  You did WHAAAT?  Yeah ok, try that video we made.  Restorting Partitions on our Pandory Youtube channel.
3. ALL MY GAMES ARE GONE!? - First, try turning off the Pandora, remove the MicroSD, then boot.  Insert once booted.  - Nothing? - Try inserting into your PC, see if you can see anything- then try again in the Pandora.  Still Nothing??  Then restore your microsd by burning your backed up image with win32imager / etcher... You DID back up... DIDN'T YOU!?  You DIDN'T?!?  Ah well- Throw more games at it with the Pandory tool then ;)

## MAME139 CONFIG FILES
- cfg files that are in the controls/mame139 will automatically be applied to the install when adding games with pandory.  It compares the .zip rom filenames, so if you are using a split rom, please rename the controller config to reflect that.
- You can update your controller cfg files by visiting the pandory github, and downloading from the controls master, or check out our discord
- If you would like to create your own, you can try loading mame32 on a computer, edit the controls- and check in the cfg folder of the mame32 folder.  You can take the cfg of the title you want to work on, then fiddle with the cfg in a text editor.  To test, paste the cfg file in the pandory/controls/mame139 folder, and add the game with pandory.
- Sharing is caring!  Once happy with the results, you can share with other users!  Make sure your information is added directly after the xml header (an example is in default.cfg in the controls folder)-  If you would like us to share on the github server / for the next build, please visit our discord https://discord.gg/Az94Rxn and upload to the pandory-gamecfg channel.

## SKINS!
- We have included a custom skin for your build.  If you want to help our cause, please use the skin/ logo, and share the love! ;-D
- To install, simply copy over the skin folder, and place it onto the root of your games destination folder.
- If you would like to share YOUR skin, please pop into the discord and we can possibly include it on a newer release.

## Issues:
- The Pandora Games 3D encrypts the data when we use this (mcgames) method.  Unfortunately, at this point in time, we cannot change data once it's on the device, which means no changing of controls re: PSP analogue sticks, perhaps the N64 controls etc. If you want to do this, I'd place the rom in the games/download folder, then alter the data from the configs that were created once running the Pandora.  There may be a way around it if you used a USB N64 pad or something similar however, but more testing is needed.
- PSP games imported with this tool will not include "2 player support".  Due to the way it's programmed, we cannot easily add these with our current tools.
- It is impossible to test every single game imported.  If you find a game that doesn't work, please include in the Games Compatibility list on the Pandory github.
- The current device this was programmed for is the Pandora Games 3D (GB3000, blue board), which came with many titles preinstalled.  Whilst this tool may work with other systems, it will not be a universal PANDORA "KEY".  There are too many models / clones!
- If the rom is not found in skraper, you can change the names of them, which may help SKRAPER find them.  If your game video has not been found, that is not the fault of the PANDORY tool.

## THANKS HIGHSCORE CHART:
1. Project Questor
2. Thie
3. Runningman2020
4. Someone
5. tinkleman710
6. G.M.Spectre
7. Anonymous
8. 2d2d
9. Ngoc Vu
10. Anonymous
11. edluke
12. nerton
13. lw0001
14. @daddyep

## THANKS from team-Pandory:
- Thomas Bouvrette: Providing the original pbobble3 archive demonstrating how to add roms to the Pandora unit 
- Querol: Providing some informative Pandora Games 3D pdfs to the community. 
- ZeroJay: Thanks for keeping the Pandora community alive with his awesome blog and discord channel.
- Wicked Gamer & Collector: Thanks for providing information on Pandora devices and random tech w/ boxes from China.
- akira84: Confirmation on working / PANDORA 9H 
- CrashCat: Confirmation on working / GoldenSky G6 
- Xaviertb78: Confirmation on working / Pandora SAGA units
- Robinvenderkuijl - Goldensky G6 testing - Glass breaking
- Those active, that keep us sane- Gazza7126, TotalKI, spokito, sutart, gmspectre, jpino3786, supercoco, projectquestor, bonsey and MORE! :o
- ALL in our discord and FB groups that keep the wheels turning
- Noise Complaint: Allowing us to use their music @ https://noise-complaint.bandcamp.com/
- Dirty Clide: Allowing us to use their music @ https://dirtyclide.bandcamp.com/
- Lyndsay Bullock: Allowing the use of her "Pyro" work on our default skin @ https://www.facebook.com/lyndsaybullock.artist/
- Supercoco: For his work on the Pandory Nitro skin, and helping us out with bits re: arcade goodness.  Go check his store in Spain! https://www.okcomputeronline.com/
- OCRemix - for allowing us to share awesome remixes, not pissing on content creators
- FilePirate: Providing information re: game configs, the headaches.
- and... YOU!  To anyone who has supported us, and continues to help share info with other Pandora users.
