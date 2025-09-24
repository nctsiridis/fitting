#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float sigmoid(float x) {
	return 1.0f / (1.0f + expf(-x));
}

float nrand() {
	return ((float) rand() / (float) RAND_MAX) * 2.0f - 1.0f;
}

void init_rand(float *arr, int size) {
	for (int i = 0; i < size; i++) arr[i] = nrand();
}

void forward(float *weights, float *biases, float *act, int n) {
	for (int i = 1; i < n; i++) {
		act[i] = (act[i - 1] * weights[i - 1]) + biases[i - 1];
		act[i] = sigmoid(act[i]);
	}
}

void backward(float *weights, float *biases, float *act, float xe, int n) {
	float lr = 1e-2;
	float carry = (act[n - 1] - xe);
	for (int i = n - 1; i >= 1; i--) {
		float part = act[i] * (1 - act[i]);
		float delta = carry * part;
		float wtemp = weights[i - 1];
		weights[i - 1] -= lr * delta * act[i - 1];
		biases[i - 1] -= lr * delta;
		carry = delta * wtemp;
	}
}

float hidden_function(float x) {
	return sigmoid((2 * x) + 0.5);
}

int main() {
	printf("Multi Layer One Node Network\n");
	size_t n = 10;
	size_t training_rounds = 1000;
	float weights[n - 1] = {}, biases[n - 1] = {}, act[n] = {};

	init_rand(weights, n - 1);
	init_rand(biases, n - 1);

	for (int i = 0; i < training_rounds; i++) {
		act[0] = sigmoid((float)i);
		float ex = hidden_function(act[0]);
		forward(weights, biases, act, n);
		backward(weights, biases, act, ex, n);
		printf("Cost at iteration %d: %f\n", i, pow((act[n - 1] - ex), 2));
	}

	return 0;
}
