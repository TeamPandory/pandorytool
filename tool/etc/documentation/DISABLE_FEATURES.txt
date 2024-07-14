# How to disable some Pandory features

If you have installed the Pandory jailbreak/fixes, you may wish to disable some features which could let someone accidentally modify the machine. This can be done by connecting to your machine via Telnet or FTP and creating one or more of the following files. The files can be empty.

/data/
├── no-android-switch
├── no-aspect-toggle
├── no-dipswitches
├── no-pause
├── no-safe-shutdown
└── no-settings-switch

To connect via Telnet/FTP, use the following guide: https://www.youtube.com/watch?v=zlPmkuLfAoU

To create a file via telnet, use the `touch` command. e.g. `touch /data/no-android-switch`
