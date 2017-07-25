# Author: Javier Mata @ ASLab

include "pioneer1.inc"


# as above, but with front sonar only
define pioneer2dx_no_sonar pioneer2dx_base_no_sonar
(  
  # simplified Body shape:
  block( 
    points 8
    point[0] [-0.2 0.12]
    point[1] [-0.2 -0.12]
    point[2] [-0.12 -0.2555]
    point[3] [0.12 -0.2555]
    point[4] [0.2 -0.12]
    point[5] [0.2 0.12]
    point[6] [0.12 0.2555]
    point[7] [-0.12 0.2555]
    z [0 0.22]
  )
)

define hokuyolaser ranger
(
  sensor(       
    # laser-specific properties
    # factory settings for LMS200  
    range [ 0.0  5.0 ]
    fov 270.0
    samples 270
  )
  model
  (
    # generic model properties
    size [ 0.07 0.07 0.05 ] # dimensions from LMS200 data sheet  
    color "blue"
  )
)
