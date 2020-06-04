#include "robot.hpp"

class Image{
	
	private:
	
		int middleRow, middleColumn;
		
		int whitePixelsFound;
		int sumWhitePixelColumns; // this variable will sum together the column numbers of each white pixel, so that an average can be found.
		int whiteLineLocation; // this variable will store the average column (ie location) for white pixels.
		
		ImagePPM currentImage;
		
	public:
		
	Image() {
		takePicture();
		currentImage = cameraView;
		
		middleRow = cameraView.height / 2;
		middleColumn = cameraView.width / 2;
		
		whitePixelsFound = 0;
		sumWhitePixelColumns = 0;
	}

	int getWhiteLineLocation() { // finds the column location of the white line.

		for (int columns = 0; columns < currentImage.width; columns++) { // loop through all columns of the image
			int pixelLuminosity = get_pixel(currentImage, middleRow, columns, 3);
			bool pixelIsWhite = pixelLuminosity > 250; // find out if the pixel is white
			if (pixelIsWhite) {
				sumWhitePixelColumns = sumWhitePixelColumns + columns; // add column number to sum of column numbers
				whitePixelsFound++;
			}
		}
		
		if (whitePixelsFound > 0) { // did we actually find any white pixels?
			whiteLineLocation = sumWhitePixelColumns / whitePixelsFound; // find the average column for white pixels
			return whiteLineLocation;
		}
		else { // as a default, return the middle column
			return middleColumn;
		}
		
	}

	int getError() { // calculates and returns the error between the white line and the center of the image.
		
		int error = getWhiteLineLocation() - middleColumn;
		std::cout<<error<<std::endl;
		return error;
		return error;
		
	}

};
