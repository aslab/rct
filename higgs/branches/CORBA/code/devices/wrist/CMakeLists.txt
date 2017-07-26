# @author Francisco Jesús Arjonilla
# Last Change: Thu Feb 17 06:00 PM 2011 C
cmake_minimum_required(VERSION 2.6)
project(WRIST)
add_subdirectory(src)
add_subdirectory(doc)

install_programs(/../../../../../../../etc/init higgs_wrist.conf)
