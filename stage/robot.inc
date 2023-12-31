define kinect ranger
(
  sensor
  (
    fov 360.0
    samples 640
    range [0 5]
  )
  # generic model properties
  color "black"
  size [ 0.06 0.15 0.03 ]
)

define robot position
(
  pose [ 0.0 0.0 0.0 0.0 ]
  
  localization "odom"

  odom_error [0.1 0.1  0.00  0.1]

  size [ 0.60 0.40 0.50 ]
  origin [ 0.0 0.0 0.0 0.0 ]
  gui_nose 1
  drive "diff"
  color "gray"
  
  kinect(pose [ 0.1 0.0 0.0 0.0 ])
)
