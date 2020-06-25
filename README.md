# BattaleTank
This is my Udemy Unreal course repository for the practice project called "Battle Tank". 

You're welcome to download and do whatever else legal with all the files. 
You can check out the course here: [Unreal Engine Developer]( http://gdev.tv/urcgithub)

### Game Engine
* Unreal Engine Version: 4.25.1

## Daily Update 
### Day 01
* Initialized this repository
* Created new Unreal project of this
* Updated .gitignore file
* Created new landscape "battle ground"

### Day 02
* Created new low polygon landscape to replace the high polygon game map
* Created tank blueprint
* Added third person camera to Tank blueprint 
* Created new blueprint class "Input Setup", setup input binding for camera control
* Wired-up Input Setup blueprint, realized controlling camera axis x and y, zoom in and out 

### Day 03
* Created player tank crosshair UI
* Created Main Menu level  and UI, built  Main Menu UI blueprint
* Created Pause Menu UI, built one key Pause Menu blueprint
* Created PlayerTankController.C++ class and AITankController.C++ class

### Day 04
* Coded player tank aiming system (aim through crosshair)
* Coded AI tank auto aiming system (Find player tank location and aim at it)
* Created TankAimingComponent C++ class
* Created TankBarrel C++ class
* Tried to make barrel elevate, but failed

### Day 05
* Realized barrel auto elevate towards aim direction
* Created TankTurret C++ class
* Realized turret auto rotate towards aim direction
* Created Projectile C++ class, created a blueprint class based on it
* Realized tanks fire, but projectiles have no parabolic
* Code refactored

### Day 06
* Tuned down projectile launch speed, now projectile has parabolic, but move speed is too low (Fix it in the future, maybe...) 
* Added simpled collision to tank and projectile
* Created TankTrack C++ class (component to apply movement force to the tank)
* Input binding for left and right track throttle
* Realized tank move (forward and backward)
* Bug: Unreal Engine crashed when tried to delete a TankTrack component from tank blueprint, which happened every time (X_X don't know how to fix it, but at least I had added both left and right track to the tank)
* After reinitialized project files (some deletes, some cuts and pastes), finally got rid of the bug above
* Created TankMovementComponent, realized tank turn (not really)
* Realized player tank turning left and right
* Realized AI Tanks auto move towards to player tank
* It is funny every tank's movement looks like skating

### Day 07
* Learned Unreal Engine C++ Enumerator, added tank aiming state (different colors for crosshair at each state)
* Aiming system code refactored, which caused lots of bugs
* Learned how to and try to fix those bugs
* All day work, whole tank architecture rebuilt, finally fixed the bugs, what a long day

### Day 08
* Fixed sideway slippage problem when tank making turns
* Improved Aiming system, now tank turret would choose the shorter route to rotate
* Improved AI tanks firing time, now they would fire only at target locked
* Created ammo display UI, added out of ammo aiming state
* Realized ammo amount display
* Created new blueprint class: AutoMortar, a stationary turret, that assembled from TankTurret, TankBarrel, and TankAimingComponent