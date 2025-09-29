#include <stdio.h>
#include <cmatrix.h>
#include <math.h>

struct {
	Matrix **weights;
	Matrix **biases;
	Matrix **activations;
	size_t input_size, output_size;
	size_t num_transforms;
} Network;

float hidden_function(float x1, float x2) {
	return pow(x1, 2) + pow(x2, 4) + 7;
}

Network init_network(
	size_t input_size, 
	size_t output_size, 
	size_t hidden_layer_nodes, 
	size_t num_transforms
) {
	Network network = malloc(sizeof(Network));
	
	Matrix **weights = malloc(num_transforms * sizeof(Matrix*));
	weights[0] = mat_rand(hidden_layer_nodes, input_size);
	for (int i = 1; i < num_transforms - 1; i++) {
		weights[i] = mat_rand(hidden_layer_nodes, hidden_layer_nodes);
	}
	weights[num_transforms - 1] = mat_rand(output_size, hidden_layer_nodes);

	Matrix **biases = malloc(num_transforms * sizeof(Matrix*));
	for (int i = 0; i < num_transforms - 1; i++) {
		biases[i] = mat_rand(hidden_layer_nodes, 1);
	}
	biases[num_transforms - 1] = mat_rand(output_size, 1);

	Matrix **activations = malloc((num_transforms + 1) * sizeof(Matrix*));
	activations[0] = mat_rand(input_size, 1);
	for (int i = 1; i < num_transforms; i++) {
		activations[i] = mat_rand(hidden_layer_nodes, 1);
	}
	activations[num_transforms] = mat_rand(output_size, 1);

	network.weights = weights;
	network.biases = biases;
	network.activations = activations;
	network.input_size = input_size;
	network.output_size = output_size;
	network.num_transforms = num_transforms;

	return network;
}

void forward(Network *network) {
	Matrix* m = network->activations[0];
	for (int i = 0; i < network->num_transforms; i++) {
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

	Network network = init_network(input_size, output_size, hidden_layer_nodes, num_transforms);

	forward(&network);

	return 0;
}
