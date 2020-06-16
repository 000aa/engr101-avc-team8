#include "imageProcessing.hpp"

class Motor{
	private:
  
	double defSpeed;
    double vLeft;
    double vRight;
    
    public:

    Motor(){
		defSpeed = 20.0;
	  setMotors(defSpeed,defSpeed);   
	}
	

 void followLine(int error, double directionAdjustment, double speedAdjustment) {
	double speedBoost = 0.0;
	if(abs(error) < 2){
		speedBoost = 15; // might as well go faster if the error is small
	}
	
	double difference = (error * 0.5) + directionAdjustment;
	double speed = defSpeed + speedAdjustment + speedBoost;
	
	vLeft = speed + difference;
    vRight = speed - difference;
    
    if (vLeft < 0) { // make sure neither of the wheels are turning backwards
		vLeft = 0;
	}
	if (vRight < 0) {
		vRight = 0;
	}
	
    setMotors(vLeft,vRight);   
    std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
    
}
  
 void doFull180() {
	 vLeft = defSpeed;
	 vRight = -defSpeed;
	 setMotors(vLeft,vRight);   
    std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
 }
	
	       
};
