/*
Author : Naoki Kishi (KUEE 2T13)
GitHub URL : https://github.com/naoki-kishi/cpro2018
*/

#include "nn.h"
#include "nn_module.h"
#include <time.h>

//プロトタイプ宣言
void learn_6layers(int train_count,int test_count,float * train_x,unsigned char * train_y,float * test_x, unsigned char * test_y, char *argv[]);

/*
第1~3引数 : FC1~FC3のパラメータの保存先
*/
int main(int argc,char *argv[]){

    //パラメータの保存先が指定されていない場合エラーを返す
    if (argc <4){
        printf("save file don't exist\n");
        return 0;
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
    srand(time(NULL));

    //6層の学習
    learn_6layers  (train_count, test_count, train_x, train_y,test_x, test_y,argv);

    return 0;
}

void learn_6layers(int train_count,int test_count,float * train_x,unsigned char * train_y,float * test_x, unsigned char * test_y, char *argv[]){

    //初期化
    float *dEdA1 = malloc(sizeof(float) * 784 * 50);
    float *dEdA2 = malloc(sizeof(float) * 50 * 100);
    float *dEdA3 = malloc(sizeof(float) * 100 * 10);
    float *dEdb1 = malloc(sizeof(float) * 50);
    float *dEdb2 = malloc(sizeof(float) * 100);
    float *dEdb3 = malloc(sizeof(float) * 10);

    float *dEdA1_av = malloc(sizeof(float) * 784 * 50);
    float *dEdA2_av = malloc(sizeof(float) * 50 * 100);
    float *dEdA3_av = malloc(sizeof(float) * 100 * 10);
    float *dEdb1_av = malloc(sizeof(float) * 50);
    float *dEdb2_av = malloc(sizeof(float) * 100);
    float *dEdb3_av = malloc(sizeof(float) * 10);

    float *A1 = malloc(sizeof(float)* 784*50);
    float *A2 = malloc(sizeof(float)* 50*100);
    float *A3 = malloc(sizeof(float)* 100*10);
    float *b1 = malloc(sizeof(float)*50);
    float *b2 = malloc(sizeof(float)*100);
    float *b3 = malloc(sizeof(float)*10);
    float *y = malloc(sizeof(float) * 10);


    //変数初期化
    int * index = malloc(sizeof(int)*train_count);
    int epoch = 5;
    int batch = 100;
    float h = 0.01;
    int i,j,k,l,m;

    //配列の初期化
    // rand_init(784*50,A1);
    // rand_init(50*100,A2);
    // rand_init(100*10,A3);
    rand_init_by_normal_dist(784*50,A1,0,sqrt(2.0/784));
    rand_init_by_normal_dist(50*100,A2,0,sqrt(2.0/50));
    rand_init_by_normal_dist(100*10,A3,0,sqrt(2.0/100));
    
    init(50,0,b1);
    init(100,0,b2);
    init(10,0,b3);
    // rand_init_by_normal_dist(50,b1,0,sqrt(2.0/50));
    // rand_init_by_normal_dist(100,b2,0,sqrt(2.0/100));
    // rand_init_by_normal_dist(10,b3,0,sqrt(2.0/10));

    //インデックスを作成し、並び替え
    for(l=0 ; l<train_count ; l+=1) {
        index[l] = l;
    }

    //エポックを回す
    for(i=0;i<epoch;i++){
        printf("-----------------------------------------------------\n");
        printf("Epoch %d/%d\n", i+1,epoch);

        shuffle(train_count, index);

        //ミニバッチ
        for(j=0;j<train_count /batch;j++){
            //平均勾配を初期化
            init(784*50,0,dEdA1_av);
            init(50*100,0,dEdA2_av);
            init(100*10,0,dEdA3_av);
            init(50,0,dEdb1_av);
            init(100,0,dEdb2_av);
            init(10,0,dEdb3_av);

            //一つ一つの勾配を計算する
            for(k=0;k<batch;k++){
                backward6(A1, A2, A3, b1, b2, b3, train_x+ 784*index[j*batch+k] ,train_y[index[j*batch+k]], y, dEdA1, dEdA2, dEdA3, dEdb1, dEdb2, dEdb3);

                //平均に加える
                add(784*50,dEdA1,dEdA1_av);
                add(50*100,dEdA2,dEdA2_av);
                add(100*10,dEdA3,dEdA3_av);
                add(50,dEdb1,dEdb1_av);
                add(100,dEdb2,dEdb2_av);
                add(10,dEdb3,dEdb3_av);
            }

            //ミニバッチで割って平均を求める
            scale(784*50,-h/batch,dEdA1_av);
            scale(50*100,-h/batch,dEdA2_av);
            scale(100*10,-h/batch,dEdA3_av);
            scale(50,-h/batch,dEdb1_av);
            scale(100,-h/batch,dEdb2_av);
            scale(10,-h/batch,dEdb3_av);

            //係数A,bを更新
            add(784*50,dEdA1_av,A1);
            add(50*100,dEdA2_av,A2);
            add(100*10,dEdA3_av,A3);
            add(50,dEdb1_av,b1);
            add(100,dEdb2_av,b2);
            add(10,dEdb3_av,b3);
            printf("%.2f \r", (float)j * 100 / (train_count / batch));
        }

        //訓練データでの推論
        int sum = 0;
        float loss_sum = 0;
        float acc = 0.0;
        for(m=0 ; m<train_count ; m++) {
            if(inference6(A1, A2, A3, b1, b2, b3, train_x + m*784,y) == train_y[m]) {
                sum++;
            }
            loss_sum += cross_entropy_error(y,train_y[m]);
        }
        acc = sum * 100.0 / train_count;

        printf("Accuracy : %f ％ \n",acc);
        printf("Loss  Average: %f\n",loss_sum/train_count);

        //テストデータでの推論
        int sum_test = 0;
        float loss_sum_test = 0;
        float acc_test = 0.0;
        for(m=0 ; m<test_count ; m++) {
            if(inference6(A1, A2, A3, b1, b2, b3, test_x + m*784,y) == test_y[m]) {
                sum_test++;
            }
            loss_sum_test += cross_entropy_error(y,test_y[m]);
        }
        acc_test = sum_test * 100.0 / test_count;

        printf("Accuracy Val : %f ％ \n",acc_test);
        printf("Loss  Average Val : %f\n",loss_sum_test/test_count);
    }

    //パラメータを保存
    save(argv[1], 50, 784, A1, b1);
    save(argv[2], 100, 50, A2, b2);
    save(argv[3], 10, 100, A3, b3);
}
