#include "imageProcessing.hpp"

class Motor{
	private:
  
	double defSpeed;
	
	/** Calculates speed based on an error and speed adjustment */
	double getSpeed(int error, double speedAdjustment) {
		double speedBoost = 0.0;
		if(abs(error) < 2){
			speedBoost = 15; // might as well go faster if the error is small
		}
		double speed = defSpeed + speedAdjustment + speedBoost;	
		return speed;
	}
	
	/** Calculates difference based on an error and direction adjustment */
	double getDifference(int error, double directionAdjustment) {
		double difference = (error * 0.5) + directionAdjustment;
		return difference;
	}
	
	/** Calculates speeds for both motors based on a base speed and difference in speed between both motors, then sets the motors. */ 
	void calculateMotorSpeeds(int speed, int difference) {
		double vLeft = speed + difference;
		double vRight = speed - difference;
		
		if (vLeft < 0) { // make sure neither of the wheels are turning backwards
			vLeft = 0;
		}
		if (vRight < 0) {
			vRight = 0;
		}
		
		setMotors(vLeft,vRight);
	}
    
    public:

    Motor(){
		defSpeed = 20.0;
	  setMotors(defSpeed,defSpeed);   
	}
	

 void followLine(int error, double directionAdjustment, double speedAdjustment) {
	 
	 double speed = getSpeed(error, speedAdjustment);
	 double difference = getDifference(error, directionAdjustment);

	calculateMotorSpeeds(speed, difference);
    
}

void keepBetweenWalls(int proximityLeft, int proximityRight) {
	int error = proximityRight - proximityLeft;
	
	double speed = getSpeed(error, 0.0);
	double difference = getDifference(error, 0.0);
	
	calculateMotorSpeeds(speed, difference);
	
}
 
 /** Rotates the robot left for a specified number of ticks at a specified speed factor */
 void rotateLeft(int ticks, double speedScale) {
	 double vLeft = -defSpeed * speedScale;
	 double vRight = defSpeed * speedScale;
	 for (int ticksDone = 0; ticksDone < ticks; ticksDone++) {
		setMotors(vLeft,vRight);
	}
	 
 }
 
 /** Rotates the robot right for a specified number of ticks at a specified speed factor */
 void rotateRight(int ticks, double speedScale) {
	 double vLeft = defSpeed * speedScale;
	 double vRight = -defSpeed * speedScale;
	 for (int ticksDone = 0; ticksDone < ticks; ticksDone++) {
		setMotors(vLeft,vRight);
	}
 }
 
 /** Moves the robot forwards for a specified number of ticks at a specified speed factor */
 void goForwards(int ticks, double speedScale) {
	 double vLeft = defSpeed * speedScale;
	 double vRight = defSpeed * speedScale;
	 for (int ticksDone = 0; ticksDone < ticks; ticksDone++) {
		setMotors(vLeft,vRight);
	}
 }
	
	       
};
