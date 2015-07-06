#!/bin/bash

tmpfile=/home/hw.tmp

rm -rf ${tmpfile}
touch ${tmpfile}

cpuid=`dmidecode -t 4|grep ID|grep -v '00 00 00 00 00 00 00 00' | awk -F: '{print $2}'`
echo ${cpuid} >> ${tmpfile}

ethx=`ls /sys/class/net/ | sed 's/lo//g'`
for i in ${ethx} 
do
	cat /sys/class/net/${i}/address >> ${tmpfile}
done

string=`cat ${tmpfile}`
echo ${string} > ${tmpfile}
