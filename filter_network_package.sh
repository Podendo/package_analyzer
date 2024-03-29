#! /bin/bash
#
# This bash script parses raw network packages and prints out the list
# of package files which contain filtered fields. For now it works with
# Ethernet, Ip, UDP protocols with src and dst adresses

############################## V A R I A B L E S ##############################
OPTION=$1
PARS_DIRS=$(pwd)
ELF_FILE=$PARS_DIRS/ans
PACK_DIR=$PARS_DIRS/examples
PACK_NUM=$(ls $PACK_DIR | wc -l)

FILE_TMP=tmpfile

declare -a ARR_FILTERS
declare -a ARR_MATCHES
declare -a ARR_FILES

declare -a ARR_ETH_FILTERS
declare -a ARR_IP_FILTERS
declare -a ARR_UDP_FILTERS

########################## E N D   V A R I A B L E S ##########################

############################## F U N C T I O N S ##############################

# error handler print-out
function err()
{
	echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: $*" >&2
}


# print information about this script to console:
function show_info()
{
	echo
	echo " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "
	echo "This bash script parses raw network packages and prints out the list "
	echo "of package files which contain filtered fields. For now it works with"
	echo "Ethernet, Ip, UDP protocols with src and dst adresses"
	echo
	echo "If you want find packages by ethernet source or destination address -"
	echo "choose filter Ethernet->source address. After that, this script will "
	echo "remember your choice by adding current address to filter array. With "
	echo "this feature you also can add another filters for IP, UDP, etc - bash"
	echo "script will use all of these filters in searching procedure."
	echo
	echo " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "
	echo
}


function update_menu_main()
{
	clear
	echo "Chosen filters: ${ARR_FILTERS[@]}"
	echo
	echo "1) filter Ethernet protocol"
	echo "2) filter IP protocol"
	echo "3) filter UDP protocol"
	echo "4) Find filtered packages"
	echo "5) Quit"
}


function update_menu_eth()
{
	clear
	echo "Chosen ethernet filters: ${ARR_ETH_FILTERS[@]}"
	echo
	echo "1) filter source ethernet MAC address"
	echo "2) filter destination ethernet MAC address"
	echo "3) go back"
}


function update_menu_ip()
{
	clear
	echo "Chosen ip filters: ${ARR_IP_FILTERS[@]}"
	echo
	echo "1) filter ip source address"
	echo "2) filter ip destination address"
	echo "3) go back"
}


function update_menu_udp()
{
	clear
	echo "Chosen udp filters: ${ARR_UDP_FILTERS[@]}"
	echo "1) filter udp protocol source address"
	echo "2) filter udp protocol destination address"
	echo "3) go back"
}


function filtering_all()
{
	if [ -z "$ARR_FILTERS" ]; then
		err "Error! Filter array is empty!"
		exit 1
	else
		echo "Filters are set, trying to find matched packages..."
		sleep 1s
	fi

	# clear
	echo "Chosen filters:"
	echo "${ARR_FILTERS[@]}"
	sleep 1s
	# This file will be removed after filtering packages
	touch $FILE_TMP
	# Add packages from package directory to array
	for file in $PACK_DIR//*;
	do
		ARR_FILES=(${ARR_FILES[@]} "$file")
	done

	echo "Founded packages:"
	echo ${ARR_FILES[@]}
	echo
	sleep 1s
	# Prepare filters array for grep command: adding -e option for each element
	FILTERS=${ARR_FILTERS[@]/#/-e }

	# Calling program with every file as input, store output in tmp file, search
	# for matches and adding them to $ARR_MATCHES
	echo "Trying to find what you want:"
	echo
	sleep 1s
	for file in ${ARR_FILES[@]:0:$PACK_NUM};
	do
		$ELF_FILE $file > $FILE_TMP
		wait $!
		if grep -i $FILTERS $FILE_TMP; then
			ARR_MATCHES=(${ARR_MATCHES[@]} "$file")
			echo
			echo "match in file: $file"
			echo
		fi
	done
	echo "Done!"
	sleep 1s
	echo Filters matched next files: ${ARR_MATCHES[@]}
	rm $FILE_TMP
}


function set_package_path()
{
	clear
	echo "Please input a path of directory where the raw-packages are stored:"
	echo
	sleep 1s
	read -p "Absolute path is:" PACK_DIR
	echo
	if [ "$PACK_DIR" != "" ]; then
		echo "Ok! you've input this path: $PACK_DIR"
	else
		echo "No filepath was set, we will use origin package directory"
		sleep 1s
		PACK_DIR=$PARS_DIRS/testpack
		echo "Initial path is: $PACK_DIR"
	fi
	echo
	sleep 1s
}

########################## E N D   F U N C T I O N S ##########################


###############################################################################
# This is the main body of the script. It has a built in menu with submenus   #
###############################################################################

# Check options to show additional information about this script:
if [ "$OPTION" == "-h" ]; then
	show_info
	exit
fi

# Print to console number of raw packages in package folder:
set_package_path
if [ $PACK_NUM == 0 ]; then
	err "There is $PACK_NUM packages, change folder or add packages"
	exit 1
else
	echo "Number of raw packages found: $PACK_NUM"
fi

# Main menu for choosing filtering:
select option in ethernet ip udp find quit; do
	case $option in
		ethernet)
		clear
		echo "This is Ethernet filtering submenu, choose filter:"
		select opt in mac_source mac_destination back; do
			case $opt in
			mac_source)
				echo "Input MAC source address in hex format (aa:bb:cc:dd:ee):"
				read -p "Ethernet MAC address to search:" srcmac
				filter="^ethernet.*source.*address.*"
				filter+=$srcmac
				ARR_FILTERS=(${ARR_FILTERS[@]} "$filter")
				ARR_ETH_FILTERS=(${ARR_ETH_FILTERS[@]} "$filter")
				update_menu_eth
				;;
			mac_destination)
				echo "Input MAC destination address in hex format (aa:bb:cc:dd:ee):"
				read -p "Ethernet MAC address to search:" dstmac
				filter="^ethernet.*destination.*address.*"
				filter+=$dstmac
				ARR_FILTERS=(${ARR_FILTERS[@]} "$filter")
				ARR_ETH_FILTERS=(${ARR_ETH_FILTERS} "$filter")
				update_menu_eth
				;;
			back)
				update_menu_main
				break
				;;
			*)
				echo "Invalid option, choose another!"
				sleep 1
				update_menu_eth
				;;
			esac
		done
		;;

		ip)
		clear
		echo "This is IP filtering submenu, choose filter:"
		select opt in ip_source ip_destination go_back; do
			case $opt in
			ip_source)
				echo "Input source address as an example: 000.111.22.33:"
				read -p "IP source address to search:" srcip
				filter='^ip.*source.*address.*'
				filter+=$srcip
				ARR_FILTERS=(${ARR_FILTERS[@]} "$filter")
				ARR_IP_FILTERS=(${ARR_IP_FILTERS[@]} "$filter")
				update_menu_ip
				;;
			ip_destination)
				echo "Input destination address as an example: 000.111.22.33:"
				read -p "IP destination address to search:" dstip
				filter='^ip.*destination.*address.*'
				filter+=$dstip
				ARR_FILTERS=(${ARR_FILTERS[@]} "$filter")
				ARR_IP_FILTERS=(${ARR_IP_FILTERS[@]} "$filter")
				update_menu_ip
				;;
			go_back)
				update_menu_main
				break
				;;
			*)
				echo "Invalid option, choose another!"
				sleep 1
				update_menu_ip
				;;
			esac
		done
		;;
		udp)
		echo "This is UDP filtering subenu:"
		select opt in udp_source udp_destination go_back; do
			case $opt in
			udp_source)
				echo "Input source address as an example: aabb (in hex)"
				read -p "udp source address in hex (2 bytes):" srcudp
				filter="^udp.*source.*address.*"
				filter+=$srcudp
				ARR_UDP_FILTERS=(${ARR_UDP_FILTERS[@]} "$filter")
				ARR_FILTERS=(${ARR_FILTERS[@]} "$filter")
				update_menu_udp
				;;
			udp_destination)
				echo "Input destination address as an example: aabb (in hex)"
				read -p "udp destination address in hex (2 bytes):" dstudp
				filter="^udp.*destination.*address.*"
				filter+=$dstudp
				ARR_FILTERS=(${ARR_FILTERS[@]} "$filter")
				ARR_UDP_FILTERS=(${ARR_UDP_FILTERS[@]} "$filter")
				update_menu_udp
				;;
			go_back)
				update_menu_main
				break
				;;
			*)
				echo "Invalid option, choose another!"
				sleep 1
				update_menu_udp
				;;
			esac
		done
		;;
		find)
			clear
			filtering_all
			break
			;;
		quit)
			clear
			echo "So you chose to run away..."
		break
		;;
		*)
			echo "Invalid option, choose another!"
			;;
	esac
done
exit 0
###############################################################################
