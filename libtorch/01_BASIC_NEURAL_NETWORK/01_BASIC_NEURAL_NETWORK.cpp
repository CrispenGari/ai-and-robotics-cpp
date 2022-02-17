
#include "01_BASIC_NEURAL_NETWORK.h"
#include <torch/torch.h>
#include <memory>

using namespace std;

struct Net:torch::nn::Module {
	Net() {
		fc1 = register_module("fc1", torch::nn::Linear(784, 64));
		fc2 = register_module("fc2", torch::nn::Linear(64, 32));
		fc3 = register_module("fc3", torch::nn::Linear(32, 10));
	}
	torch::Tensor forward(torch::Tensor x, bool train = true) {
		x = torch::relu(fc1->forward(x));
		x = torch::dropout(x, 0.5, train);
		x = torch::relu(fc2->forward(x));
		x = torch::log_softmax(fc3->forward(x), 1);
		return x;
	}
	torch::nn::Linear fc1{ nullptr }, fc2{ nullptr }, fc3{ nullptr };
};

int main(){
	Net net();
	int BATCH_SIZE = 64;
	int N_EPOCHS = 3;

	auto trainset = torch::data::datasets::MNIST("./data").map(
		torch::data::transforms::Stack<>()
	);
	auto trainloader = torch::data::make_data_loader(
		move(trainset), BATCH_SIZE
	);

	while (true) {
		for (auto& batch : *trainloader) {
			cout << batch.target << endl; break;
		}
		break;
	}

	/* OPTIMIZER AND CRITERION */
	/*torch::optim::SGD optimizer(net->parameters(), 0.01);
	torch::nn::NLLLoss criterion;

	net->train();
	for (std::size_t epoch = 1; epoch <= N_EPOCHS; ++epoch) {
		torch::Tensor epoch_loss;
		for (auto& batch : *trainloader) {
			optimizer.zero_grad();
			torch::Tensor prediction = net-> forward(batch.data);
			torch::Tensor loss = criterion->forward(prediction, batch.target);
			epoch_loss = loss;
			loss.backward();
			optimizer.step();
		}
		cout << "EPOCH " << epoch << "/" << N_EPOCHS << endl;
		cout << "loss: " << epoch_loss << endl<<endl;
	}*/
	return 0;
}
