
#include "motorMovement.hpp"
int main(){
	if (initClientRobot()  !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
	
    //double vLeft = 40.0;
    //double vRight = 30.0;
    //takePicture();
    //SavePPMFile("i0.ppm",cameraView);
    Motor motor;
    while(1){
		Image image;
      //setMotors(vLeft,vRight);   
      //std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
			//std::cout<<image.findPixels(lineAhead).averageLocation<<std::endl;
			motor.followLine(image.getLineAhead().error);
		
       usleep(10000);
       
  } //while

} // main

	
		
