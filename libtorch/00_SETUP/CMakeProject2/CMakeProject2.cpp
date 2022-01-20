
#include "CMakeProject2.h"
#include <torch/torch.h>
using namespace std;

int main()
{
	torch::Tensor tensor = torch::eye(3);
	cout <<tensor << endl;
	return 0;
}
