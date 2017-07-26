#!/bin/bash
/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */

date >> /var/log/higgs/restart_servants.sh

killall -v -9 wrist_server.sh wrist_server 2>&1 >> /var/log/higgs/restart_servants.sh || true
killall -v -9 arduino.sh java 2>&1 >> /var/log/higgs/restart_servants.sh || true
killall -v -9 camera.sh camera 2>&1 >> /var/log/higgs/restart_servants.sh || true
killall -v -9 laser_server.sh laser_server 2>&1 >> /var/log/higgs/restart_servants.sh || true
killall -v -9 batteries.sh java 2>&1 >> /var/log/higgs/restart_servants.sh || true
killall -v -9 gps_server.sh gps_server 2>&1 >> /var/log/higgs/restart_servants.sh || true

