include_directories(/usr/include/)
link_directories(/usr/lib/)

add_library (control EKalman.cpp PredictionModel.cpp ObservationModel.cpp HiggsModels.cpp)

add_executable (sample simpleEKalman.cpp EKalman.cpp PredictionModel.cpp ObservationModel.cpp)

target_link_libraries(control newmat)
target_link_libraries(sample newmat)
