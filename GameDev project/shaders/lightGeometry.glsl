#version 420 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 projection;
//uniform mat4 mvp;

in Vertex{
	vec3 Position;
	vec3 Colour;
	float Radius;
} IN[];

out Vertex{
	vec3 Position;
    vec3 Colour;
	float Radius;
} OUT;


void bounds(vec3 center, float radius, inout vec3 boxMin, inout vec3 boxMax) {
	
	float d2 = dot(center, center);
	float a = sqrt(d2 - radius * radius);
	
	vec3 right = (radius / a) * vec3(-center.z, 0, center.x);
    vec3 up = vec3(0,radius,0);

    vec4 projectedRight  = projection * vec4(right,0);
    vec4 projectedUp     = projection * vec4(up,0);

    vec4 projectedCenter = projection * vec4(center,1);

    vec4 north  = projectedCenter + projectedUp;
    vec4 east   = projectedCenter + projectedRight;
    vec4 south  = projectedCenter - projectedUp;
    vec4 west   = projectedCenter - projectedRight;

    north /= north.w ;
    east  /= east.w  ;
    west  /= west.w  ;
    south /= south.w ;

    boxMin = min(min(min(east,west),north),south).xyz;
    boxMax = max(max(max(east,west),north),south).xyz;

	
}


void main() {
	for (int i = 0; i < gl_in.length(); i++) {
		OUT.Colour = IN[i].Colour;
		OUT.Position = IN[i].Position;
		OUT.Radius = IN[i].Radius;
		
		float r = IN[i].Radius;

		//vec4 a = vec4(1,1,1,1) * projection;
		
		vec3 boxMax = vec3(-1,-1,0);
		vec3 boxMin = vec3(1,1,0);
		
		//bounds(gl_in[i].gl_Position.xyz, r, boxMax, boxMin);
		
		gl_Position = vec4(boxMax.xy, 0, 1);
		EmitVertex();
		gl_Position = vec4(boxMin.x, boxMax.y, 0, 1);
		EmitVertex();
		gl_Position = vec4(boxMax.x, boxMin.y, 0, 1);
		EmitVertex();
		gl_Position = vec4(boxMin.xy, 0, 1);
		EmitVertex();
		
		
		//top right 
		/*gl_Position = gl_in[i].gl_Position;
		gl_Position.z -= r;
		gl_Position.x += r;
		gl_Position.y += r;
		gl_Position = projection * gl_Position;
		EmitVertex();

		//top left
		gl_Position = gl_in[i].gl_Position;
		gl_Position.z -= r;
		gl_Position.x -= r;
		gl_Position.y += r;
		gl_Position = projection * gl_Position;
		EmitVertex();

		//bottom right
		gl_Position = gl_in[i].gl_Position;
		gl_Position.z -= r;
		gl_Position.x += r;
		gl_Position.y -= r;
		gl_Position = projection * gl_Position;
		EmitVertex();

		//bottom left
		gl_Position = gl_in[i].gl_Position;
		gl_Position.z -= r;
		gl_Position.x -= r;
		gl_Position.y -= r;

		gl_Position = projection * gl_Position;
		EmitVertex();*/
		
		EndPrimitive();
	}
}