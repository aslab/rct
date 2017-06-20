include_directories(/usr/include/)
link_directories(/usr/lib/)

add_library (control EKalman.cpp StateModel.cpp HiggsStateModel.cpp)
#add_library (timer timer.cc)

target_link_libraries(control newmat libcv)
