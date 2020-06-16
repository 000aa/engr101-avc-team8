#include "motorControl.hpp"

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
	
	Motor robot;
    
    while(1){
		
		Image image;
				
		if (image.getLineLeft().found) { // did we find a left line to take?
			if (image.getLineLeft().location > (image.getCurrentImage().height * 0.75)) {
				robot.followLine(image.getLineAhead().error, -40.0, -10.0);
			}
		}
		else if (image.getLineRight().found && (!image.getLineAhead().found)) { // take a right turn, but only if we can't go straight
			if (image.getLineRight().location > (image.getCurrentImage().height * 0.75)) {
				robot.followLine(image.getLineAhead().error, 40.0, -10.0);
			}
		}
		else if (image.getLineBottom().found) { // is the line still in view?
			robot.followLine(image.getLineAhead().error, 0.0, 0.0);
		}
		else { // line lost, turn around
			robot.doFull180();
		}
		
       usleep(10000);
  } //while

} // main
