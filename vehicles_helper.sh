#!/bin/sh
# vehicles generation helper
# usage: vehicles_helper <time_from> <time_to> <location_from> <location_to> <vehicles_count> <max_speed> <traffic_increase_caused>

get_random_time() { #range: FROM TO
	random=`tr -cd 0-9 < /dev/urandom | head -c 10 | sed s/^0*//`
	echo $(( ( $random % ($2 - $1) ) + $1))
}

for i in `seq 1 $5`; do
	echo "`get_random_time $1 $2`:veh$i:$3:$4:max_speed=$6:traffic_increase_caused=$7"
done 