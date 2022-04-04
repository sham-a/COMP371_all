Ayah Shamma - 40100256

- Shapes 
	Both spheres and rectangle are properly captured. Intersection methods have been implement and work well.

- Light 
	Point light is properly implemented such that the light ray originates from the centre of the light. For the 
	area light, I found the point at the centre of the area and used that to create a Point light, as I was not 
	able to figure out the proper implementation of the area light.

- Local Illumination
	Local illumination is implemented and works well.

- Antialiasing
	Antialiasing is also implemented and works ok, it takes a long time to run though. I create nested for loops 
	representing the grid. Within those loops I iterate through the numbers of rays required and take the average 
	of the colour value at the end when adding to the buffer.

- Global Illumination
	Global illumination was not implemented due to lack of time.

