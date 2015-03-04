#! /bin/sh
EXPECTED_ARGS=2

if [ $# -lt $EXPECTED_ARGS ]
then
    printf "\nUsage: `basename $0` {distro} {path}\n"
    printf "distro:\n\t0 - ArchLinux\n\t1 - Fedora/OpenSUSE/RHEL/CentOS\n\t2 - Debian/Ubuntu\n\t3 - Gentoo\n"
    printf "path:\n\tpath where to save the output\n"
    printf "Example: `basename $0` 2 /var/output.txt\n"
    exit 1
fi

distro=$1
path=$2

if [ $distro = 0 ]; then
    #printf "ArchLinux selected\n"
    pacman -Qet | awk '{print $1}' | sort -u > $path 
    pacman -Qm | awk '{print $1}' | sort -u >> $path
elif [ $distro = 1 ]; then
    #printf "Fedora/OpenSUSE/RHEL/CentOS selected\n"
    package-cleanup --leaves --all | sed 's/-[0-9][0-9]*\.[0-9].*//' | tail --lines=+2 | sort -u > $path
elif [ $distro = 2 ]; then
    #printf "Debian/Ubuntu selected\n"
    aptitude search '~i !~M' -F '%p' --disable-columns | sort -u > $path
elif [ $distro = 3 ]; then
    #printf "Gentoo selected\n"
    cat /var/lib/portage/world | sed 's/^.*\///' | sed 's/:.*$//' | sort -u > $path
fi

printf "Complete! Output saved to $path\n"
