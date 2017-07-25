# Revision: Carlos Hernandez @ aslab.org
#           - upgraded model to work with new Stage (partial 3D)
#			- added higgs_laser model
#
# Revision: Javier Mata @ aslab.org
#	    - upgraded model to work with Ros Fuerte stage version (stage 4.1)



# ros electric: define sicklaser laser 
define sicklaser ranger
(
  # laser-specific properties
  # factory settings for LMS200	
  range_max 8.0
  fov 180.0
  samples 361

  #samples 90 # still useful but much faster to compute

  # generic model properties
  color "blue"
  size [ 0.156 0.155 0.19 ] # dimensions from LMS200 data sheet	
)

define higgs_laser sicklaser
(
	pose [0.248 0 0 0.35]	# to position the laser relative to higgs center
)

# extends sicklaser to add nice-looking but relatively expensive geometry
define fancysicklaser sicklaser
(
  # bottom
  block( 
    points 4
    point[0] [ -0.02 -0.077 313]
    point[1] [  0.078 -0.077 ]
    point[2] [  0.078  0.077 ]
    point[3] [ -0.02  0.077 ]
    z [0 0.02 ]
  )

  # back
  block(
    points 4
    point[0] [ -0.078 -0.077 ]
    point[1] [ -0.02  -0.077 ]
    point[2] [ -0.02   0.077 ]
    point[3] [ -0.078  0.077 ]
    z [0 0.21 ]
  )

  # top
  block( points 4
    point[0] [ -0.02 -0.077 ]
    point[1] [  0.078 -0.077 ]
    point[2] [  0.078  0.077 ]
    point[3] [ -0.02  0.077 ]
    z [0.12 0.21 ]  
  )

  # laser bit
  block( points 4
    point[0] [ -0.02 -0.05 ]
	 point[1] [  0.06 -0.05 ]
	 point[2] [  0.06  0.05 ]
	 point[3] [ -0.02  0.05 ]
	 z [0.02 0.12 ]  
   color "gray10"
  )
)



