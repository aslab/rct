Use:
$rosrun map_server map_saver -f mymap
to save the map before closing slam_gmapping

to save the data in file.bag:
$rosbag record -O bag/file.bag tf pioneer/cmd_vel
