#!/bin/bash
#xargs -a params.txt  -n 7 -P 8 ./go4xargs.sh
#-n liczba argumentow
#-P procesy

{
echo $(date)
echo "arguments: $@"

DISPLAY="" RiskM=$1 Policy=$2 Nets=$3 OptimF=$4 Weight=$7 CrashData=$5 NetData=$6  matlab  -r ga2015fast 

} 2>&1 | tee  job.$$.log
