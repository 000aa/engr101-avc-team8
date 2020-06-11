
#include "imageProcessing.hpp"

class Motor{
	private:
	double defSpeed = 30.0;
    
    
    public:
    
    Motor(){
	  setMotors(defSpeed,defSpeed);   
	}
	
 void updateMotor() {
	Image image;
	int difference = image.getError(); //difference between motors
	double vLeft = defSpeed + difference*0.1 ;
    double vRight = defSpeed - difference*0.1;
    setMotors(vLeft,vRight);   
    std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
    
}
	 
	
	 
	 // if multiple white lines - always follow left, if line ends turn around 180 degrees
      
};
