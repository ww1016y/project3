# project3 Where Am I

.Project3                                 # Where Am I Project

    ├── my_robot                              # my_robot package                   
    │   ├── config                            # AMCL configuration files   
    │   │   ├── base_local_planner_params.yaml
    │   │   ├── costmap_common_params.yaml
    │   │   ├── global_costmap_params.yaml
    │   │   ├── local_costmap_params.yaml
    │   ├── launch                            # launch folder for launch files   
    │   │   ├── amcl.launch                   # Adaptive MCL launch file
    │   │   ├── robot_description.launch
    │   │   ├── world.launch
    │   ├── maps                              # map folder made 
    │   │   ├── map.pgm
    │   │   ├── map.yaml
    │   ├── meshes                            # meshes folder for sensors
    │   │   ├── hokuyo.dae
    │   ├── urdf                              # urdf folder for xarco files
    │   │   ├── my_robot.gazebo               # my robot model
    │   │   ├── my_robot.xacro                # my robot model
    │   ├── worlds                            # world folder for world file
    │   │   ├── myworld.world
    │   ├── CMakeLists.txt                    # compiler instructions
    │   ├── package.xml                       # package info
    |   └── amcl.rviz                             
    └── teleop_twist_keyboard                 # teleop_twist_keyboard package                   
    
