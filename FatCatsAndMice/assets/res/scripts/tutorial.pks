pause duration:1200;
label name:beginning;

# show position the right hand
select control:fc_tutorialRightHand;
set position: -150, -350;
set visible: true;


# move cat down and right
select control:fc_tutorialCat;
set position: 0, 150;
set visible: true;
move to: 0, -100; speed:1000; accel:500; 
move to: 500, -100; speed:1000; accel:1000; async;

# move hand right
select control:fc_tutorialRightHand;
move to: 100, -350; speed:1000; accel:800; 
pause duration:500;
set visible: false;

# show position the left hand
select control:fc_tutorialLeftHand;
set position: 150, -350;
set visible: true;

# move mouse down and right
select control:fc_tutorialMouse;
set position: 0, 150;
set visible: true;
move to: 0, -100; speed:1000; accel:500; 
move to: -500, -100; speed:1000; accel:1000; async;

select control:fc_tutorialLeftHand;
move to: -100, -350; speed:1000; accel:800; 
pause duration:500;
set visible: false;

# show touch to start
select control:fc_tutorial_continueLbl;
set visible: true;

loop label:beginning;



