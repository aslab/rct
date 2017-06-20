FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/higgs_arduino_java/msg"
  "../src/higgs_arduino_java/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_java_higgs_arduino_java"
  "../srv_gen/java/ros/pkg/higgs_arduino_java/srv/TestTwoInts.java"
  "../srv_gen/java/ros/pkg/higgs_arduino_java/srv/AddTwoInts.java"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_java_higgs_arduino_java.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
