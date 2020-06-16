#include "robot.hpp"

class Image {
	
	private:
	
		struct line{ // a white line in the image that the robot needs to be aware of (eg to follow)
			int location, error;
			bool found;
		};
		
		struct sensor{ // an imaginary line that can detect white pixels in the image
			int position;
			bool horizontal;
		};
		
		struct pixels{ // information we might want to know about white pixels found by a sensor
			int count, totalLocation, averageLocation;
		};
	
		int middleRow, middleColumn;
				
		ImagePPM currentImage;
		
		sensor lineAhead; // define some sensors where we want to detect white pixels in the image
		sensor lineLeft;
		sensor lineRight;
		
		/**
		 * Finds count, total location (sum of location indexes), and average location of white pixels on sensor.
		 */
		pixels findPixels(sensor activeSensor) {
			
			pixels pixelsFound;
			pixelsFound.count = 0;
			pixelsFound.totalLocation = 0;
			int size; // this will be used in the below for loop to check each "location" (pixel) along the sensor
			
			if (activeSensor.horizontal) {
				pixelsFound.averageLocation = middleColumn;
				size = currentImage.width;
			}
			else {
				pixelsFound.averageLocation = middleRow;
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
				std::cout<<"pixelLuminosity"<<pixelLuminosity<<std::endl;
				bool pixelIsWhite = pixelLuminosity > 250; // find out if the pixel is white
				if (pixelIsWhite) {
					pixelsFound.totalLocation = pixelsFound.totalLocation + locations; // add location checked to "total" location
					pixelsFound.count++;
				}
			}
			
			if (pixelsFound.count > 0) { // did we actually find any white pixels?
				pixelsFound.averageLocation = pixelsFound.totalLocation / pixelsFound.count; // find the average location for white pixels
			}
			std::cout<<"pixelsFound="<<pixelsFound.count<<std::endl;
			return pixelsFound;
		}
		 
		
		/**
		 * Finds the location of the white line.
		 */
		line findLine(sensor activeSensor) {

			pixels pixelsFound = findPixels(activeSensor); // find the pixels detected by this sensor
			line lineFound;
			
			lineFound.location = pixelsFound.averageLocation; // determine the location of the white line
			
			if (activeSensor.horizontal) { // determine the error of the white line from the center of the sensor
				lineFound.error = lineFound.location - middleColumn;
			}
			else {
				lineFound.error = lineFound.location - middleRow;
			}
			
			if (pixelsFound.count > 0) { // also determine if there is actually a line there
				lineFound.found = true;
			}
			else {
				lineFound.found = false;
			}
			
			return lineFound;
		}
		
	public:
		
		Image() {
			takePicture();
			std::cout<<"pixel="<<(int)get_pixel(cameraView,10,10,3)<<" ";
			currentImage = cameraView;
			
			middleRow = cameraView.height / 2;
			middleColumn = cameraView.width / 2;
			
			lineAhead.position = middleRow; // each sensor already has a horizontal/vertical orientation, now give them positions.
			lineAhead.horizontal = true;
			
			lineLeft.position = 2;
			lineLeft.horizontal = false;
			
			lineRight.position = currentImage.width - 2;
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

};
