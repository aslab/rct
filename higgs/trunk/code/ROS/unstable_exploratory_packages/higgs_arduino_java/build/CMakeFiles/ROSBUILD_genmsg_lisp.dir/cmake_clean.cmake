FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/higgs_arduino_java/msg"
  "../src/higgs_arduino_java/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/TestDataTypes.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_TestDataTypes.lisp"
  "../msg_gen/lisp/TestBadDataTypes.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_TestBadDataTypes.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
