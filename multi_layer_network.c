#include <stdio.h>
#include <cmatrix.h>

int main() {
	size_t hidden_layers = 2;
	size_t hidden_layer_nodes = 2;
	size_t total_layers = hidden_layers + 1;
	size_t input_size = 2;
	size_t output_size = 1;

	Matrix **layers = malloc(total_layers * sizeof(Matrix*));

	layers[0] = mat_rand(input_size, hidden_layer_nodes);
	for (int i = 1; i < total_layers - 1; i++) {
		layers[i] = mat_rand(hidden_layer_nodes, hidden_layer_nodes);
	}
	layers[total_layers - 1] = mat_rand(hidden_layer_nodes, output_size);

	for (int i = 0; i < total_layers; i++) {
		char label[32];
		snprintf(label, sizeof(label), "Transform %d -> %d", i, i + 1);
		mat_print(layers[i], label);
	}

	//Matrix *m = mat_rand(5, 5);
	//mat_print(m, "my matrix");
	return 0;
}
