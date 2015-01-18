set withInput:false;
pause duration:%INITIAL_DELAY%;
set signType:%SIGN_TYPE%;
set position: 550, -360; rotation: 90; visible: true;
move to: %POSITION%; speed:800; decel:800;  async;
rotate to: 0; speed:200; decel:800; direction:cw; 
set withInput:true;

#efeito a mexer para n estar parado
label name:idle;
move by: -3, 0; speed:2;
move by: 3, -3; speed:2;
move by: 0, 3; speed:3;
loop label:idle;



