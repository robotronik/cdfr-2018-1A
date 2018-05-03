Makefile STM32
==============

Installation
------------
 - Exemple sur Ubuntu/Mint

        sudo apt-get install gcc-arm-none-eabi libnewlib-arm-none-eabi gdb-arm-none-eabi openocd
 
 - Exemple sur Arch/Manjaro

        sudo pacman -S arm-none-eabi-gcc arm-none-eabi-newlib arm-none-eabi-gdb openocd

Configuration
-------------
 * BOARD
Le type de carte pour laquelle vous voulez compiler, par exemple f3 ou f4.

 * PROJECT_DIR
Le répertoire du projet que vous voulez compiler

 * PROJECT_NAME
Le nom de votre projet (en général le même que PROJECT_DIR).

 * DOC_DIR (optionnel)
Le répertoire dans lequel vous avez placé le fichier stm32$(BOARD)_doc.pdf, par exemple stm32f4_doc.pdf.

Configuration du projet STM32
-----------------------------
Dans le Makefile de votre projet, modifiez la ligne BINPATH par :
BINPATH = /usr/bin
Dans C_SOURCES, ajoutez vos fichiers .c persos (à placer dans PROJECT_DIR/Src/) et supprimez les lignes en double s'il y en a.

Compilation
-----------
make c

Upload du programme sur STM32
-----------------------------
 * make f
pour flasher le programme compilé
 * make flash_file
pour flasher un local.bin contenu dans le même dossier que ce Makefile

Connexion de GDB
----------------
make debug

En cas d'erreur avec openocd
----------------------------
Si vous avez l'erreur LIBUSB_ERROR_ACCESS, lancez make f en root ou ajoutez une règle udev pour vous autoriser l'accès en lecture/écriture sur la carte STM32.
