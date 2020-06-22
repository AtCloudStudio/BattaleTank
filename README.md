# BattaleTank
This is my Udemy Unreal course repository for the practice project called "Battle Tank". 

You're welcome to download and do whatever else legal with all the files. 
You can check out the course here: [Unreal Engine Developer]( http://gdev.tv/urcgithub)

### Game Engine
* Unreal Engine Version: 4.25.1

## Daily Update 
### Day 01
* Setup this repository
* Create new Unreal project of this
* Update .gitignore file
* Create new landscape "battle ground" by Landscape tool

### Day 02
* Create new low polygon landscape to replace high polygon game map
* Create tank blueprint
* Tank blueprint add 3rd person camera
* Create new blueprint class "Input Setup", input binding for camera control
* Build Input setup blueprint, implement camera x axis and y axis control , zoom in and out 

### Day 03
* Create player tank aim point UI
* Create main menu Level  and UI, build  main menu UI blueprint
* Create pause menu UI, build single key pause menu blueprint
* Create PlayerTankController.C++ class and AITankController.C++ class
* UE_LOG check those controllers correctly control their tank

### Day 04
* Code player tank aiming system (aim through crosshair)
* Code AI tank auto aiming system (Find player tank location and aim at it)
* Create TankAimingComponent C++ class
* Create TankBarrel C++ class
* Try to make barrel elevate, failed

### Day 05
* Make barrel auto elevate towards aim direction
* Create TankTurret C++ class
* Make turret auto rotate towards aim direction
* Create Projectile C++ class and create a blueprint class based on it
* Make tanks fire, but projectiles have no parabolic
* Make some refactor of codes