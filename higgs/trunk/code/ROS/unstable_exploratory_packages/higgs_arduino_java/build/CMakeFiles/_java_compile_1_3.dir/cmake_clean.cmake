FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/higgs_arduino_java/msg"
  "../src/higgs_arduino_java/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/_java_compile_1_3"
  "../bin/ros/pkg/roscpp/srv/SetLoggerLevel.class"
  "../bin/ros/pkg/roscpp/srv/GetLoggers.class"
  "../bin/ros/pkg/roscpp/srv/Empty.class"
  "../bin/ros/pkg/higgs_arduino_java/srv/AddTwoInts.class"
  "../bin/ros/pkg/higgs_arduino_java/srv/TestTwoInts.class"
  "../srv_gen/java/ros/pkg/roscpp/srv/SetLoggerLevel.java"
  "../srv_gen/java/ros/pkg/roscpp/srv/GetLoggers.java"
  "../srv_gen/java/ros/pkg/roscpp/srv/Empty.java"
  "../srv_gen/java/ros/pkg/higgs_arduino_java/srv/AddTwoInts.java"
  "../srv_gen/java/ros/pkg/higgs_arduino_java/srv/TestTwoInts.java"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/_java_compile_1_3.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
