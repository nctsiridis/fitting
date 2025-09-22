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
	weights[0] = mat_rand(hidden_layer_nodes, input_size);
	for (int i = 1; i < num_transforms - 1; i++) {
		weights[i] = mat_rand(hidden_layer_nodes, hidden_layer_nodes);
	}
	weights[num_transforms - 1] = mat_rand(output_size, hidden_layer_nodes);
	return weights;
}

void forward(Matrix* m, Matrix** weights, int num_transforms) {
	for (int i = 0; i < num_transforms; i++) {
		mat_dot(weights[i], m);
	}
}

void backward() {
	// TODO implement back prop
}

int main() {
	size_t hidden_layers = 2;
	size_t hidden_layer_nodes = 2;
	size_t num_transforms = hidden_layers + 1;
	size_t input_size = 2;
	size_t output_size = 1;

	Matrix **weights = init_weights(input_size, output_size, hidden_layer_nodes, num_transforms);

	Matrix *m = mat_rand(2, 1);

	mat_print(m, "before");
	forward(m, weights, num_transforms);
	mat_print(m, "after");

	return 0;
}
