#!/bin/sh
#
#  Make OTI build of current firmware
#
cp config_oti.mk ../onetimeisp/config.mk
cd ../onetimeisp
make
