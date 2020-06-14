
#include "imageProcessing.hpp"

class Motor{
	private:
  
	double defSpeed = 25.0;
    
    public:
    double vLeft;
    double vRight;

    Motor(){
	  setMotors(defSpeed,defSpeed);   
	}
	

 void followLine(int error) {
	 double speedUp = 0.0;
	 if(abs(error) < 2){
		 speedUp = 15;
	 }
	int difference = error*0.5;
	vLeft = defSpeed + speedUp + difference;
    vRight = defSpeed + speedUp - difference;
    setMotors(vLeft,vRight);   
    std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
    
}
  
 void turnLeft(){
	 vRight = 15;
	 vLeft = 0;
	 setMotors(vLeft,vRight);   
     std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
 }
  
 void turnRight(){
	 vRight = 0;
	 vLeft = 15;
	 setMotors(vLeft,vRight);   
     std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
 } 
	
	 
	 // if multiple white lines - always follow left, if line ends turn around 180 degrees
      
};
