#include "nn.h"
#include "nn_module.h"
#include <time.h>


int main(int argc, char *argv[]){

    //パラメータの保存先が指定されていない場合エラーを返す
    if (argc <5){
        printf("File don't exist\n");
        return -1;
    }
    float *train_x = NULL;
    unsigned char *train_y = NULL;
    int train_count = -1;

    float *test_x = NULL;
    unsigned char *test_y = NULL;
    int test_count = -1;

    int width = -1;
    int height = -1;

    load_mnist(&train_x, &train_y, &train_count,
               &test_x, &test_y, &test_count,
               &width, &height);

    //初期化
    float *A1 = malloc(sizeof(float)* 784*50);
    float *A2 = malloc(sizeof(float)* 50*100);
    float *A3 = malloc(sizeof(float)* 100*10);
    float *b1 = malloc(sizeof(float)*50);
    float *b2 = malloc(sizeof(float)*100);
    float *b3 = malloc(sizeof(float)*10);
    float *y = malloc(sizeof(float) * 10);

    //パラメータを読み込み
    load(argv[1], 50, 784, A1, b1);
    load(argv[2], 100, 50, A2, b2);
    load(argv[3], 10, 100, A3, b3);

    //パラメータを確認
    int m;
    int sum = 0;
    float loss_sum = 0;
    float acc = 0.0;
    for (m = 0; m < train_count; m++)
    {
        if (inference6(A1, A2, A3, b1, b2, b3, train_x + m * 784, y) == train_y[m])
        {
            sum++;
        }
        loss_sum += cross_entropy_error(y, train_y[m]);
        }
        acc = sum * 100.0 / train_count;

        printf("Accuracy : %f ％ \n",acc);
        printf("Loss  Average: %f\n",loss_sum/train_count);

        int sum_test = 0;
        float loss_test = 0;
        float accuracy_test = 0.0;
        for(m=0 ; m<test_count ; m++) {
            if(inference6(A1, A2, A3, b1, b2, b3, test_x + m*784, y) == test_y[m]) {
                sum_test++;
            }
            loss_test += cross_entropy_error(y, test_y[m]);
        }
        accuracy_test = sum_test * 100.0 / test_count;

        printf("Test Accuracy : %f ％ \n",accuracy_test);
        printf("Test Loss Average : %f\n",loss_test / test_count);
    

    //画像を読み込む
    float *x = load_mnist_bmp(argv[4]);

    //読み込んだ画像で推論
    int  predict = 0;
    predict = inference6(A1, A2, A3, b1, b2, b3, x, y);

    printf("figure is %d\n", predict);
    return 0;
}
