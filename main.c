#include"include/draw.h"
#include"include/output.h"
#include"include/matrix.h"
#include"include/parser.h"

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Please state an input file\n");
		exit(1);
	}
	struct Matrix *edges = new_matrix(4, 1);
	struct Matrix *transform = new_matrix(4, 4);
	Frame f;
	memset(f, 0, sizeof(f));
	
	struct Pixel p;
	pixel_color(&p, 255, 235, 205);

	//make_circle(edges, 200, 200, 0, 100);
	//make_hermite(edges, 159, 259, 340, 200, 282, 485, 19, 16);
	/*
	parametric_exec(edges, 82, -24, 123, 159, 528, -813, 226, 259);
	printf("outside\n");
	print_matrix(edges);
	draw_lines(f, edges, &p);
	printf("outside1\n");

	display(f);
	*/

	parse_instructions("script", transform, edges, f);
	
	free_matrix(edges);
	free_matrix(transform);
	
	return 0;
}

