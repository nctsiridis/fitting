#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	double dw1, dw2, db;
} Gradient;

typedef struct {
	double x, y;
} Pair;

typedef struct {
	Pair input;
	double output;
} DataPoint;

double hidden_function(double x, double y) {
	return (45 * x) + (-299 * y) - 102;
}

double rand_double() {
	return (double)rand() / RAND_MAX;
}

DataPoint* init_data(int size) {
	DataPoint *res = (DataPoint*)malloc(size * sizeof(DataPoint));
	for (int i = 0; i < size; i++) {
		double x = rand_double(), y = rand_double();
		res[i].input.x = x;
		res[i].input.y = y;
		res[i].output = hidden_function(x, y);
	}
	return res;
}

Gradient gradient(double x, double y, double w1, double w2, double bias, double z) {
	double dw1 = 2 * ((x * w1) + (y * w2) + bias - z) * x;
	double dw2 = 2 * ((x * w1) + (y * w2) + bias - z) * y;
	double db = 2 * ((x * w1) + (y * w2) + bias - z);
	return (Gradient){.dw1 = dw1, .dw2 = dw2, .db = db};
}

double cost(double w1, double w2, double bias, DataPoint* data, int size) {
	double res = 0;
	for (int i = 0; i < size; i++) {
		res += pow((data[i].input.x * w1) + (data[i].input.y * w2) + bias - data[i].output, 2);
	}
	return res;
}

int main() {

	double alpha = 1e-1;
	int sample_size = 500;
	int training_epochs = 1000;
	srand(time(NULL));

	double w1 = rand_double(), w2 = rand_double();
	double bias = rand_double();
	DataPoint* data = init_data(sample_size);

	for (int i = 0; i < training_epochs; i++) {
		double w1_delta = 0, w2_delta = 0, bias_delta = 0;
		for (int j = 0; j < sample_size; j++) {
			Gradient g = gradient(data[j].input.x, data[j].input.y, w1, w2, bias, data[j].output);
			w1_delta -= (alpha * g.dw1);
			w2_delta -= (alpha * g.dw2);
			bias_delta -= (alpha * g.db);
		}
		w1 += w1_delta / sample_size;
		w2 += w2_delta / sample_size;
		bias += bias_delta / sample_size;
		printf("Cost after round %d = %lf\n", i + 1, cost(w1, w2, bias, data, sample_size));
	}

	printf("Trained parameters: \nw1=%lf \nw2=%lf\nb=%lf\n", w1, w2, bias);

	return 0;
}
