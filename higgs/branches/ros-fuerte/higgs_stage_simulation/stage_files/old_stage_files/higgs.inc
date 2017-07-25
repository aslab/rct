# Author: Javier Mata @ ASLab

include "pioneer1.inc"	#Model of or higgs robot
include "sick.inc"	#Model of our laser


# The higgs Pioneer 2AT8 configuration
define higgs pioneer_base
(
  # Actual size
  size [0.68 0.50 0.22]

  # The pioneer's center of rotation is offset from its center of area
  origin [-0.04465 0.0 0.0 0.0]

  # Estimated mass in KG
  mass 40.0 

  # Body shape:
  block( 
    points 8
    point[0] [-0.30 0.25]
    point[1] [-0.34 0.15]
    point[2] [-0.34 -0.15]
    point[3] [-0.30 -0.25]
    point[4] [0.30 -0.25]
    point[5] [0.34 -0.15]
    point[6] [0.34 0.15]
    point[7] [0.30 0.25]
    z [0 0.22]
  )

  # Use the sonar array defined in pioneer.inc
  #p3at_sonar( pose [ 0 0 -0.03 0 ] ) 
  # Use the laser defined in sick.inc
  #sicklaser( pose [ 0.248 0 0 0.35 ] )
)

