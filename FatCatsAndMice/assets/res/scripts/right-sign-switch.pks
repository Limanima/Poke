set withInput:false;
set position: 310, -200;
rotate to:5; speed:400; direction:ccw; 
rotate to:-90; speed:400; accel:300; direction:cw; async;
move to: 450, -360; speed:1000; accel:500; 
set signType:%SIGN_TYPE%;
move to: 310, -200; speed:350; decel:800;  async;
rotate to:0; speed:200; decel:800; direction:ccw; 
set withInput:true;



