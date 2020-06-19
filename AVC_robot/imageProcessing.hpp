#include "robot.hpp"

class Image {
	
	private:
	
		struct line{ // a white line in the image that the robot needs to be aware of (eg to follow)
			int location, error;
			bool found;
		};
		
		struct wallProximity{ // the proximities of the red walls in the image to the center of the field of view
			int left, right, top;
			bool foundLeft, foundRight, foundTop;
		};
		
		struct sensor{ // an imaginary line that can detect white pixels in the image
			int position;
			bool horizontal;
		};
		
		struct pixels{ // information we might want to know about white pixels found by a sensor
			int whiteCount, whiteTotalLocation, whiteAverageLocation;
		};
	
		int middleRow, middleColumn;
				
		ImagePPM currentImage;
		
		sensor lineAhead; // define some sensors where we want to detect white pixels in the image
		sensor lineLeft;
		sensor lineRight;
		sensor lineBottom;
		
		/**
		 * Finds count, total location (sum of location indexes), and average location of white pixels on sensor.
		 */
		pixels findPixels(sensor activeSensor) {
			
			pixels pixelsFound;
			pixelsFound.whiteCount = 0;
			pixelsFound.whiteTotalLocation = 0;
			int size; // this will be used in the below for loop to check each "location" (pixel) along the sensor
			
			if (activeSensor.horizontal) {
				pixelsFound.whiteAverageLocation = middleColumn;
				size = currentImage.width;
			}
			else {
				pixelsFound.whiteAverageLocation = middleRow;
				size = currentImage.height;
			}
			
			for (int locations = 0; locations < size; locations++) { // loop through all "locations" (pixels) along the sensor
				int pixelLuminosity = 0;
				if (activeSensor.horizontal) {
					pixelLuminosity = get_pixel(currentImage, activeSensor.position, locations, 3);
				}
				else {
					pixelLuminosity = get_pixel(currentImage, locations, activeSensor.position, 3);
				}
				
				bool pixelIsWhite = pixelLuminosity > 250; // find out if the pixel is white
				
				if (pixelIsWhite) {
					pixelsFound.whiteTotalLocation = pixelsFound.whiteTotalLocation + locations; // add location checked to "total" location
					pixelsFound.whiteCount++;
				}
			}
			
			if (pixelsFound.whiteCount > 0) { // did we actually find any white pixels?
				pixelsFound.whiteAverageLocation = pixelsFound.whiteTotalLocation / pixelsFound.whiteCount; // find the average location for white pixels
			}
						
			return pixelsFound;
		}
		 
		
		/**
		 * Finds the location of the white line.
		 */
		line findLine(sensor activeSensor) {

			pixels pixelsFound = findPixels(activeSensor); // find the pixels detected by this sensor
			line lineFound;
			
			lineFound.location = pixelsFound.whiteAverageLocation; // determine the location of the white line
			
			if (activeSensor.horizontal) { // determine the error of the white line from the center of the sensor
				lineFound.error = lineFound.location - middleColumn;
			}
			else {
				lineFound.error = lineFound.location - middleRow;
			}
			
			if (pixelsFound.whiteCount > 0) { // also determine if there is actually a line there
				lineFound.found = true;
			}
			else {
				lineFound.found = false;
			}
			
			return lineFound;
			
		}
		
		/** Finds out if a pixel is red */
		bool pixelIsRed(int row, int column) {
			int pixelRed = get_pixel(currentImage, row, column, 0);
			int pixelGreen = get_pixel(currentImage, row, column, 1);
			int pixelBlue = get_pixel(currentImage, row, column, 2);
			return ((pixelRed > (pixelGreen * 2.0)) && (pixelRed > (pixelBlue * 2.0)));
		}
		
		/**
		 * Finds the proximity of a red wall to the middle and bottom of field of view.
		 */
		 wallProximity findWall() {
			 
			 wallProximity proximity;
			 
			 proximity.foundLeft = false; // we haven't found any red walls yet
			 proximity.foundRight = false;
			 proximity.foundTop = false;
			 
			 proximity.left = 0; // give the proximities the most extreme values they could have when searching for them
			 proximity.right = currentImage.width;
			 proximity.top = 0;
			 
			 for (int columns = middleColumn - 25; columns < middleColumn + 25; columns++) { // loop through a range of middle columns to find top proximity. We need to know this in advance for finding the left and right proximities.
				 for (int rows = 0; rows < currentImage.height; rows++) {
					 if (pixelIsRed(rows, columns) && (rows > proximity.top)) {
						 proximity.top = rows;
						 proximity.foundTop = true;
					 }
				 }
			 }
			 
			 for (int columns = 0; columns < currentImage.width; columns ++) { // loop through all pixels in rows beneath the middle row, but only if they are beneath the top proximity.
				 for (int rows = std::max(middleRow, proximity.top + 1); rows < currentImage.height; rows++) {
					 if (pixelIsRed(rows, columns)) {
						 if ((columns < middleColumn) && (columns > proximity.left)) { // if the column is in the left half of the image, check if the wall is closer to the middle than what we've already encountered
							 proximity.left = columns;
							 proximity.foundLeft = true;
						}
						 else if ((columns > middleColumn) && (columns < proximity.right)) { // if the column is in the right half of the image, check if the wall is closer to the middle than what we've already encountered
							 proximity.right = columns;
							 proximity.foundRight = true;
						}
					 }
				 }
			 }
			 
			 proximity.left = middleColumn - proximity.left; // at this point we've found the locations, but we actually want the proximity to the middle/bottom.
			 proximity.right = proximity.right - middleColumn;
			 proximity.top = currentImage.height - proximity.top;
			 
			 return proximity;
		 }
		
	public:
		
		Image() {
			takePicture();
			currentImage = cameraView;
			
			middleRow = currentImage.height / 2;
			middleColumn = currentImage.width / 2;
			
			lineAhead.position = middleRow; // initialise sensors
			lineAhead.horizontal = true;
			
			lineBottom.position = currentImage.height - 1;
			lineBottom.horizontal = true;
			
			lineLeft.position = 1;
			lineLeft.horizontal = false;
			
			lineRight.position = currentImage.width - 1;
			lineRight.horizontal = false;
		}
		
		/**
		 * Return the lines found to the rest of the program
		 */
		line getLineAhead() {
			return findLine(lineAhead);
		}
		line getLineLeft() {
			return findLine(lineLeft);
		}
		line getLineRight() {
			return findLine(lineRight);
		}
		line getLineBottom() {
			return findLine(lineBottom);
		}
		
		/**
		 * Return the walls found to the rest of the program
		 */
		 wallProximity getWallProximity() {
			 return findWall();
		 }
		
		/**
		 * Returns other useful variables
		 */
		 ImagePPM getCurrentImage() {
			 return currentImage;
		 }
		 
		 int getMiddleColumn() {
			 return middleColumn;
		 }

};
