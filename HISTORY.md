# Releases

# Pandory v1.0.4 - 19-Apr-2020 (JAILBREAK!)
1. Added JAILBREAK.  Bumps system into Android 4.4.  Custom APK installation now possible- can also load up scripts from gamemenu.
2. Added BACKUP AUTOMATION.  Pandory can now create a quick and easy way to automate the backup processe.
3. Added GB folder. Now we can easily separate the GB and GBC titles.
4. New MAME139 cfgs added to the stack (aburner, aburner2, btimem, captcomm, gangwars, indyheat, mspacman, offroadt, qbert, ssprint)

# Pandory v1.0.3 - 20-Mar-2020
1. Added genre automation.  Automatically applies genre generated from the scrape.
2. Added Sega 32X emulation (32x folder)
3. Added Mame 0.190 emulation (mame19 folder) - Tested with some 0.185 roms.  The 3-4 player titles stock on the system are using this emulator.
4. Added Sega Mastersystem emulation (mastersystem folder)
5. Added controller cfg automation for mame139 games.  Insert your cfg files into /controls/mame139/ and it'll inject them in when adding your games.
6. Added a "prepare" modifier to the pandory command line.  This will create a rom folder tree for all your roms to go in, and also make it default for pandory.
7. Changed: More comprehensive help given from the command line (when the command "pandory" alone is given, a help message is given)
8. Changed: Switched out the x64 build for the x86 build for Windows. - Best compatibility for all windows users.
9. Added: Skin folder.  Place folder at the root of the rom destination drive (microsd/usbstick) to show some skin.

# Pandory v1.0.2 - 05-Mar-2020
1. LOADTIME settings altered for compatibility.
2. MAME SAVE STATE setting has been enabled to allow fixes for some titles.
3. PS1 / .PBP files now work.  The filename in CAPS won't run successfully, so Pandory now automatically changes filename from uppercase to lowercase.

# Pandory v1.0.1 - 25-Feb-2020
- First public release
