cmake_minimum_required(VERSION 2.6)
project(GPS)
add_subdirectory(src)

install_programs(/../../../../../../../etc/init higgs_gps.conf)
