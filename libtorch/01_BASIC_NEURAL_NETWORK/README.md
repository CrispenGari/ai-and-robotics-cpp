### Basic Neural Network

In this example we are going to show how we can create a basic neural network from scratch.

### `CMakeList.txt`

We are then going to open the `CMakeList.txt` and add the following configurations.

```cmake
cmake_minimum_required (VERSION 3.8)

project ("01_BASIC_NEURAL_NETWORK")

find_package(Torch REQUIRED)
add_executable (01_BASIC_NEURAL_NETWORK "01_BASIC_NEURAL_NETWORK.cpp" "01_BASIC_NEURAL_NETWORK.h")

target_link_libraries(01_BASIC_NEURAL_NETWORK "${TORCH_LIBRARIES}")

if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET 01_BASIC_NEURAL_NETWORK
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:01_BASIC_NEURAL_NETWORK>)
endif (MSVC)
```

### Hello World tensor
To create our hello world tensor we are going to open the `01_BASIC_NEURAL_NETWORK.cpp` file 
and add the following code to it.

```c++
#include "01_BASIC_NEURAL_NETWORK.h"
#include <torch/torch.h>
using namespace std;
int main()
{
	torch::Tensor tensor = torch::randint(2, 3);
	cout << tensor << endl;
	return 0;
}
```
We are using the `randint` function from pytorch to create a tensor of random numbers. 
If you run the programme and everythig goes well we will see the following output
from the console:

```
 0
 1
 0
[ CPUFloatType{3} ]
```

### Creating a basic `Net`

Suppose the python code for a network looks as follows:

```py
import torch
import torch.nn.functional as F

class Net(torch.nn.Module):
    def __init__(self):
        self.fc1 = torch.nn.Linear (784 , 64)
        self.fc2 = torch.nn.Linear (64 , 32)
        self.fc3 = torch.nn.Linear (32 , 10)
    def forward(self , x ):
        x = F.relu( self.fc1( x ))
        x = F.dropout (x , p =0.5)
        x = F.relu( self.fc2 ( x ))
        x = F.log_softmax (self.fc3(x) , dim =1)
    return x
```

The above code creates a hello world neural network using pyton and pytorch. This can
be transformed using libtorch and c++ as follows:

```c++
#include <torch/torch.h>
using namespace std;

struct Net :torch::nn::Module {
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
```
### Creating an instance of a `net` and train it.

Now we have our basic network instance, we can train it on the `mnist` dataset. The code for doing that in python looks 
as follows:

```py
net = Net()

trainset = torchvision.datasets.MNIST(
	root="./data", train = True ,
	download = True , transform = transform 
)
trainloader = torch.utils.data.DataLoader( 
	trainset , batch_size =64 ,
	shuffle = True , num_workers =2
)

optimizer = optim.SGD( net.parameters() , lr =0.01)
criterion = nn.NLLLoss()

for epoch in range (2):
	for batch in trainloader :
		optimizer . zero_grad ();
		inputs , labels = batch
		outputs = net( inputs )
		loss = criterion( outputs , labels )
		loss.backward()
		optimizer.step()

```
We can do the same in c++ as follows:

```c++
int main(){
	shared_ptr<Net> net = make_shared<Net>();
	int BATCH_SIZE = 64;
	int N_EPOCHS = 3;
	auto trainset = torch::data::datasets::MNIST("./data").map(
		torch::data::transforms::Stack<>()
	);
	auto trainloader = torch::data::make_data_loader(
		move(trainset), BATCH_SIZE
	);
	/* OPTIMIZER AND CRITERION */
	torch::optim::SGD optimizer(net->parameters(),  0.01);
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
	}
	return 0;
}
```

### Refs
1. [cpp_frontend](https://pytorch.org/tutorials/advanced/cpp_frontend.html)
2. [](https://cognitivedemons.wordpress.com/2018/06/08/neural-network-in-c-part-2-mnist-handwritten-digits-dataset/)