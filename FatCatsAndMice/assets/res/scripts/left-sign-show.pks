set withInput:false;
pause duration:%INITIAL_DELAY%;
play_sound asset: res/sounds/board_show;
set signType:%SIGN_TYPE%;
set position: -550, -360; rotation: -90; visible: true;
move to: %POSITION%; speed:800; decel:800;  async;
rotate to:0; speed:200; decel:800; direction:ccw; 
set withInput:true;

label name:idle;
move by: 3, 0; speed:2;
move by: -3, -3; speed:3;
move by: 0, 3; speed:2;
loop label:idle;


