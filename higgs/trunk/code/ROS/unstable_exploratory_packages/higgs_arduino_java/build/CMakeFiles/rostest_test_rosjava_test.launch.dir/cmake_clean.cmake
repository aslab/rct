FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/higgs_arduino_java/msg"
  "../src/higgs_arduino_java/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/rostest_test_rosjava_test.launch"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/rostest_test_rosjava_test.launch.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
