FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/higgs_arduino_java/msg"
  "../src/higgs_arduino_java/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_java_higgs_arduino_java"
  "../msg_gen/java/ros/pkg/higgs_arduino_java/msg/TestDataTypes.java"
  "../msg_gen/java/ros/pkg/higgs_arduino_java/msg/TestBadDataTypes.java"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_java_higgs_arduino_java.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
