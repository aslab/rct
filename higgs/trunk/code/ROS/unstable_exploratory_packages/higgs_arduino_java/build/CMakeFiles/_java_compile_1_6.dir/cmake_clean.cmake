FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/higgs_arduino_java/msg"
  "../src/higgs_arduino_java/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/_java_compile_1_6"
  "../bin/AddTwoIntsClient.class"
  "../bin/Testee.class"
  "../bin/AddTwoIntsServer.class"
  "../bin/Listener.class"
  "../bin/Talker.class"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/_java_compile_1_6.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
