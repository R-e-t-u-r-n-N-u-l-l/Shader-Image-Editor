
// Input and uniform data:
// ---------------------------------------------------
// sampler2D rawImageSampler = the raw image data
// vec2 position = current pixel position from 0 to 1
// vec2 resolution = resolution of the image in pixels
// float time = current time in milliseconds
// vec4 image = the current pixel color of the image
// ---------------------------------------------------

// Functions
// ---------------------------------------------------
// float map(float value, float min1, float max1, float min2, float max2)
//		Maps a value that is between min1 and max1 between min2 and max2
// ---------------------------------------------------

const int r = 40;

void run(vec4 image) {

	// The gaussian blur example

	vec4 value;
	int count = 0;

	for (int i = -r; i <= r; i++) {
		for (int j = -r; j <= r; j++) {
			vec2 location = position + vec2(i, j) / resolution;
			if (location.x < 0 || location.y < 0 || location.x > 1 || location.y > 1)
				continue;

			value += texture(rawImageSampler, location);
			count++;
		}
	}

	value /= count;
	color = value;
}