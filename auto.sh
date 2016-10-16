#!/bin/sh
python getOtherProject.py > /tmp/gzgtmp
cat /tmp/gzgtmp |sort|uniq > /tmp/gzgtmpuniq
