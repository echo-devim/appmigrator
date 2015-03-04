# AppMigrator

AppMigrator is a gui application to help you to migrate your programs from a GNU/Linux distro to another. Basically the gui runs a script to get installed packages and then a script to install them into the new distro.

At the moment, the current supported distros are:

  - ArchLinux
  - Fedora/RHEL/CentOS/OpenSUSE
  - Debian/Ubuntu
  - Gentoo

and their derivatives. If you want request the support for a new distro (or something else), send me an email (see at the bottom of this document).

### Version
Beta 0.1

ATTENTION: This software has not been tested enough. I do not take any responsibility for any damage.

### Screenshot
![GitHub Logo](/Screenshot/appmigrator.jpg)

### Technical Details

This software was developed with Anjuta IDE and is required the support to GTK 3.10.

If you want use this software with Fedora/RHEL/CentOS, you must install yum-utils (package-cleanup needed).

### Installation

The easiest method to compile the code is run install_script.sh.

```sh
$ install_script.sh
```

This script make a folder (named 'bin') with the program.

If you want try to configure with more options the compilation process, try to compile the source code in the 'AnjutaSource' folder.

```sh
$ cd AnjutaSource
$ ./configure <options>
$ make
```

for more details you can read the INSTALL file in the AnjutaSource folder.

License
----

GPL v3.0

###Contacts

You can contact me at: devim [at] outlook [dot] it

