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
	struct Matrix *trans = new_matrix(4, 4);
	Frame f;
	memset(f, 0, sizeof(f));
	parse_instructions(argv[1], trans, edges, f);

	free_matrix(edges);
	free_matrix(trans);
	
	return 0;
}

