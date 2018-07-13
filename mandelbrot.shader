//const vec2 offset = vec2(-0.79, 0.15);
//const vec2 offset = vec2(-0.162, 1.04);
//const vec2 offset = vec2(-1.467, 0.0);
//const vec2 offset = vec2(-0.12, -0.77);
//const vec2 offset = vec2(0.3, -0.01);
//const vec2 offset = vec2(0.28, 0.008);
const vec2 offset = vec2(-0.7463, 0.1102);

void run(vec4 image) {
	vec2 pos_scaled = vec2(map(position.x, 0.0, 1.0, -2.5, 1.0), map(position.y, 1.0, 0.0, -1.0, 1.0)) * (1.0 / pow(2, time / 2)) + offset;
	vec2 pos = vec2(0.0);
	int i = 0;
	int max_iterations = 10000;

	while (pos.x * pos.x + pos.y * pos.y < 2 * 2 && i < max_iterations) {
		float temp = pos.x * pos.x - pos.y * pos.y + pos_scaled.x;
		pos.y = 2 * pos.x * pos.y + pos_scaled.y;
		pos.x = temp;
		i++;
	}

	if (i == max_iterations)
		color = vec4(0.0);
	else
		color = vec4(0.0, float(i) / float(max_iterations) * 100.0, 0.0, 1.0);
}
