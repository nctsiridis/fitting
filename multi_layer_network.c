#include <stdio.h>
#include <cmatrix.h>
#include <math.h>

float hidden_function(float x1, float x2) {
	return pow(x1, 2) + pow(x2, 4) + 7;
}

Matrix** init_weights(
	size_t input_size, 
	size_t output_size, 
	size_t hidden_layer_nodes, 
	size_t num_transforms
) {
	Matrix **weights = malloc(num_transforms * sizeof(Matrix*));
	weights[0] = mat_rand(input_size, hidden_layer_nodes);
	for (int i = 1; i < num_transforms - 1; i++) {
		weights[i] = mat_rand(hidden_layer_nodes, hidden_layer_nodes);
	}
	weights[num_transforms - 1] = mat_rand(hidden_layer_nodes, output_size);
	return weights;
}

void forward(Matrix* m, Matrix** weights, int num_transforms) {
	for (int i = 0; i < num_transforms; i++) {
		// TODO
	}
}

int main() {
	size_t hidden_layers = 2;
	size_t hidden_layer_nodes = 2;
	size_t num_transforms = hidden_layers + 1;
	size_t input_size = 2;
	size_t output_size = 1;

	Matrix **weights = init_weights(input_size, output_size, hidden_layer_nodes, num_transforms);
	for (int i = 0; i < num_transforms; i++) {
		char label[32];
		snprintf(label, sizeof(label), "Transform %d -> %d", i, i + 1);
		mat_print(weights[i], label);
	}

	//Matrix *m = mat_rand(5, 5);
	//mat_print(m, "my matrix");
	return 0;
}
