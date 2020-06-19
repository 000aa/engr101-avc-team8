#include "motorControl.hpp"

bool peekedLeft = false; // we might need to get the robot to "peek" in each direction, so remember where it's already looked.
bool peekedRight = false;
bool peekedAhead = false;

void actionSuccessful() { // every time there is a successful action, reset the peek status for next time we lose the path.
	peekedLeft = false;
	peekedRight = false;
	peekedAhead = false;
}

void regainPath(Motor robot) { // try to regain the path by peeking in each direction
	if (!peekedLeft) {
		robot.rotateLeft(3, 0.25); // peek left.
		peekedLeft = true;
	}
	else if (!peekedRight) {
		robot.rotateRight(6, 0.25); // correct the rotate we did when peeking left, as well as peek right.
		peekedRight = true;
	}
	else if (!peekedAhead) {
		robot.rotateLeft(3, 0.25); // correct the rotation we did when peeking right.
		robot.goForwards(16, 1.0); // peek forwards.
		peekedAhead = true;
	}
	else {
		actionSuccessful();
		robot.goForwards(16, -1.0); // correct the peeking forwards.
		robot.rotateLeft(15, 1.0); // do a full 180
	}
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
	
	Motor robot;
    
    while(1){
		
		Image image;
					
			if (image.getLineLeft().found && (image.getLineLeft().location > (image.getCurrentImage().height * 0.75))) { // did we find a left line to take, and is it close enough?
				actionSuccessful();
				robot.followLine(image.getLineAhead().error, -40.0, -10.0);
			}
			else if (image.getLineRight().found && (!image.getLineAhead().found) && (image.getLineRight().location > (image.getCurrentImage().height * 0.75))) { // take a right turn if one is available, but only if we can't go straight and it's close enough.
				actionSuccessful();
				robot.followLine(image.getLineAhead().error, 40.0, -10.0);
			}
			else if (image.getLineBottom().found) { // is the line still in view?
				actionSuccessful();
				robot.followLine(image.getLineAhead().error, 0.0, 0.0);
			}
			// there's no line, but we might be able to follow a maze of red walls.
			else if (!image.getWallProximity().foundLeft && (image.getWallProximity().foundRight || image.getWallProximity().foundTop)) { // are we near walls and is a left turn available?
				actionSuccessful();
				if (!image.getWallProximity().foundTop) { // if there's no wall ahead, we'll have to move forward blindly before turning.
					robot.goForwards(24, 1.5);
					robot.rotateLeft(15, 0.5);
					robot.goForwards(12, 1.0);
				}
				else { // if there is a wall ahead, we can position ourselves perfectly in front of it
					if (image.getWallProximity().top > (image.getCurrentImage().height * 0.25)) {
						robot.goForwards(2, 1.0);
					}
					else {
						robot.rotateLeft(15, 0.5);
						robot.goForwards(12, 1.0);
					}
				}
			}
			else if (!image.getWallProximity().foundRight && image.getWallProximity().foundTop) { // are we at a dead end and can turn right?
				actionSuccessful();
				if (image.getWallProximity().top > (image.getCurrentImage().height * 0.25)) { // move forward until we are close to the wall ahead
					robot.goForwards(2, 1.0);
				}
				else {
					robot.rotateRight(15, 0.5);
					robot.goForwards(12, 1.0);
				}
			}
			else if (image.getWallProximity().foundLeft && image.getWallProximity().foundRight && !image.getWallProximity().foundTop) { // are we between two walls we could keep between?
				actionSuccessful();
				robot.keepBetweenWalls(image.getWallProximity().left, image.getWallProximity().right);
			}
			else if (image.getWallProximity().foundLeft && image.getWallProximity().foundRight && image.getWallProximity().foundTop) { // are we at a complete dead end?
				robot.rotateLeft(15, 1.0); // do a full 180
			}
			else if (image.getWallProximity().foundLeft) { // could we stick to a wall left?
				actionSuccessful();
				robot.followLine((image.getMiddleColumn() - image.getWallProximity().left - 3), 0.0, 0.0);
			}
			else if (image.getWallProximity().foundRight) { // could we stick to a wall right?
				actionSuccessful();
				robot.followLine(-(image.getMiddleColumn() - image.getWallProximity().right - 3), 0.0, 0.0);
			}
			else { // path lost
				regainPath(robot);
			}
		usleep(10000);
	} //while

} // main
