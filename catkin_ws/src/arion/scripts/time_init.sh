#!/bin/bash

/etc/init.d/chrony stop  
ntpdate master  
/etc/init.d/chrony start
