#! /bin/sh
EXPECTED_ARGS=2

if [ $# -lt $EXPECTED_ARGS ]
then
	printf "\nAttention: you must run this script as root!\n"
	printf "Usage: `basename $0` {distro} {path}\n"
	printf "distro:\n\t0 - ArchLinux\n\t1 - Fedora/RHEL/CentOS\n\t2 - Debian/Ubuntu\n\t3 - Gentoo\n\t4 - OpenSUSE\n"
	printf "path:\n\tpath of the list with packages to install\n"
	printf "Example: `basename $0` 2 /var/input.txt\n"
	exit 1
fi

distro=$1
path=$2

if [ $distro = 0 ]; then
	#printf "ArchLinux selected\n"
	pacman -S $(cat $path)
elif [ $distro = 1 ]; then
	#printf "Fedora/OpenSUSE/RHEL/CentOS selected\n"
	yum install $(cat $path)
elif [ $distro = 2 ]; then
	#printf "Debian/Ubuntu selected\n"
	aptitude install $(cat $path)
elif [ $distro = 3 ]; then
	#printf "Gentoo selected\n"
	emerge $(cat $path)
elif [ $distro = 4 ]; then
	#printf "OpenSUSE selected\n"
	zypper in $(cat $path)
fi

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd ) #get the directory of this script (no matter where it is being called from)

sh $DIR/listpkg.sh $distro tmp_out.txt
if [ $# = 3 ]; then #This args is used by the GUI application to save the result to an output file
	diff $path tmp_out.txt | grep "<" | sed 's/^< //g' > $3
else
	printf "ATTENTION: The following packages may not have been properly installed, maybe you should manually reinstall them.\n"
	diff $path tmp_out.txt | grep "<" | sed 's/^< //g'
	printf "If you don't see any package name is because are all installed succesfully!\n"
fi
rm tmp_out.txt
