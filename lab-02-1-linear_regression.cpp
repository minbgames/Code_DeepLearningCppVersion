#include <iostream>
#include <cmath>

#define COUNT_SIZE 201
#define M_COUNT 3

using namespace std;

float x_train[3]={1, 3, 5};
float y_train[3]={3, 7, 11};

//float hypothesis[]
float cost=0;
float learning_rate = 0.1;

float Cost_Make(float _W, float _b);
float Gradient_Descent(float &_W, float &_b);

int main(void){

    srand((unsigned int)time(NULL));

    float W = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;


    for (int step = 0; step < COUNT_SIZE; step++)
    {
        Gradient_Descent(W,b);
        cost = Cost_Make(W,b);

        if(step % 20 == 0){
            cout << "[ cost = " << cost << " , W = " << W << " , b = " << b << " ] " << endl;
        }
    }
}

float Cost_Make(float _W, float _b)
{
    float cost_ = 0;
    for (int i = 0; i < M_COUNT; i++) {
        cost_=cost_+(float)pow(_W*x_train[i]+_b-y_train[i],2);
    }
    cost_= cost_ / (2*M_COUNT);
    return cost_;
}

float Gradient_Descent(float &_W, float &_b)
{
    float W_sum_=0, b_sum_=0;
    for (int i = 0; i < M_COUNT; i++) {
        W_sum_=W_sum_+(_W*x_train[i]+_b-y_train[i])*x_train[i];
        b_sum_=b_sum_+(_W*x_train[i]+_b-y_train[i]);
    }
    _W = _W - learning_rate / M_COUNT * (W_sum_);
    _b = _b - learning_rate / M_COUNT * (b_sum_);
}