#include <stdio.h>

#include <stdlib.h>

#include <math.h>

//m*n行列xを表示

void print(int m, int n, const float *x){

    int i, j;



    for (i = 0; i < m; i++){

        for (j = 0; j < n; j++){

            printf("%.4f ", x[i * n + j]);

        }

        printf("\n");

    }

}



//m*n行列xをyにコピーする

void copy(int m, int n, const float *x, float *y){

    int i, j;

    for (i = 0; i < m; i++){

        for (j = 0; j < n; j++){

            y[i * n + j] = x[i * n + j];

        }

    }

}



//m*n行列Aを用いてy = A*x +b を計算する

void fc(int m, int n, const float *x, const float *A, const float *b, float *y){

    int i, j;



    for (i = 0; i < m; i++){

        y[i] = b[i];

        for (j = 0; j < n; j++){

            y[i] += A[i * n + j] * x[j];

        }

    }

}



//m列ベクトルのxに対して、relu演算を行う y = relu(x)

void relu(int m, const float *x, float *y){

    int i;



    for (i = 0; i < m; i++){

        if (x[i] > 0){

            y[i] = x[i];

        }

        else{

            y[i] = 0;

        }

    }

}



//m列ベクトルのxに対して、prelu演算を行う y = prelu(x)

void prelu(int m, const float *x, float *y,float a){

    int i;



    for (i = 0; i < m; i++){

        if (x[i] > 0){

            y[i] = x[i];

        }

        else{

            y[i] = a * x[i];

        }

    }

}



//m行のベクトルxに対して、y = softmax(x)

void softmax(int m, const float *x, float *y){

    int i;

    float max = x[0]; //xの最大値

    float sum = 0;    //sigma(exp(x-max))



    //xの最大値を求める

    for (i = 0; i < m; i++){

        if (x[i] > max){

            max = x[i];

        }

    }



    //sigma(exp(x-max))を計算

    for (i = 0; i < m; i++)

    {

        sum += exp(x[i] - max);

    }



    //softmax演算を行う

    for (i = 0; i < m; i++)

    {

        y[i] = exp(x[i] - max) / sum;

    }

}



//3層による推論を行い、得られた結果[0:9]を返す

int inference3(const float *A, const float *b, const float *x,float * y){

    int m = 10;

    int n = 784;



    fc(m, n, x, A, b, y);

    relu(m, y, y);

    softmax(m, y, y);



    float max = y[0]; //yの要素の最大のもの

    int index = 0;    //yの要素が最大の時の添字

    int i;



    for (i = 0; i < m; i++){

        if (y[i] > max){

            max = y[i];

            index = i;

        }

    }

    return index;

}



//6層による推論を行い、得られた結果[0:9]を返す

int inference6(const float *A1,const float *A2,const float *A3, const float *b1,  const float *b2, const float *b3, const float *x,float * y){



    float * y1 = malloc(sizeof(float) * 50);

    float * y2 = malloc(sizeof(float) * 100);

    fc(50, 784, x, A1, b1, y1);

    relu(50, y1, y1);

    fc(100, 50, y1, A2, b2, y2);

    relu(100, y2, y2);

    fc(10, 100, y2, A3, b3, y);

    softmax(10, y, y);



    float max = y[0]; //yの要素の最大のもの

    int index = 0;    //yの要素が最大の時の添字

    int i;



    for (i = 0; i < 10; i++){

        if (y[i] > max){

            max = y[i];

            index = i;

        }

    }

    free(y1);

    free(y2);

    return index;

}



//softmaxの誤差逆伝播を行う

void softmaxwithloss_bwd(int m, const float *y, unsigned char t, float *dEdx){

    float answers[10] = {0};

    int i = 0;



    for (i = 0; i < 10; i++){

        if (i == t){

            answers[i] = 1;

        }

    }

    for (i = 0; i < m; i++){

        dEdx[i] = y[i] - answers[i];

    }

}



//reluの誤差逆伝播を行う

void relu_bwd(int m, const float *x, const float *dEdy, float *dEdx){

    int i = 0;

    for (i = 0; i < m; i++){

        if (x[i] > 0){

            dEdx[i] = dEdy[i];

        }

        else{

            dEdx[i] = 0;

        }

    }

}



//reluの誤差逆伝播を行う

void prelu_bwd(int m, const float *x, const float *dEdy, float *dEdx,const float a, float  dEda){

    int i = 0;

    dEda = 0.0;

    for (i = 0; i < m; i++){

        if (x[i] > 0){

            dEdx[i] = dEdy[i];

            dEda += 0.0;

        }

        else{

            dEdx[i] = a;

            dEda += dEdy[i] * x[i];

        }

    }

}



//FC層の誤差逆伝播を行う

void fc_bwd(int m, int n, const float *x, const float *dEdy, const float *A, float *dEdA, float *dEdb, float *dEdx){

   int i, j = 0;



   for (i = 0; i < m; i++){

       for (j = 0; j < n; j++){

           dEdA[i * n + j] = dEdy[i] * x[j];

       }

   }



   for (i = 0; i < m; i++){

       dEdb[i] = dEdy[i];

   }



   for (i = 0; i < n; i++){

       dEdx[i] = 0;

       for (j = 0; j < m; j++){

           dEdx[i] += A[j * m + i] * dEdy[j];

       }

   }

}



//3層の誤差逆伝播を行う

void backward3(const float *A, const float *b, const float *x, unsigned char t, float *y, float *dEdA, float *dEdb){

    int m = 10;

    int n = 784;



    float before_fc[784];

    float before_relu[10];

    float y1[10];

    float y0[784];

    //順伝播

    copy(1, n, x, before_fc);

    fc(m, n, x, A, b, y);

    copy(1, m, y, before_relu);

    relu(m, y, y);

    softmax(m, y, y);



    //逆伝播

    softmaxwithloss_bwd(m, y, t, y1);

    relu_bwd(m, before_relu, y1, y1);

    fc_bwd(m, n, before_fc, y1, A, dEdA, dEdb, y0);

}



//6層の誤差逆伝播を行う

void backward6(const float *A1,const float *A2,const float *A3, const float *b1,  const float *b2, const float *b3, const float *x, unsigned char t, float *y,

    float *dEdA1,float *dEdA2,float *dEdA3, float *dEdb1,float *dEdb2,float *dEdb3){



    float  * before_fc1 = malloc(sizeof(float) * 784);

    float  * before_fc2 = malloc(sizeof(float) * 50);

    float  * before_fc3 = malloc(sizeof(float) * 100);

    float  * before_relu1 = malloc(sizeof(float) * 50);

    float  * before_relu2 = malloc(sizeof(float) * 100);



    float * y0 = malloc(sizeof(float) * 784);

    float * y1 = malloc(sizeof(float) * 50);

    float * y2 = malloc(sizeof(float) * 100);

    float *y3 = malloc(sizeof(float) * 10);



    //順伝播

    copy(1,784,x,before_fc1);

    fc(50, 784, x, A1, b1, before_relu1);

    relu(50, before_relu1, before_fc2);

    fc(100, 50, before_fc2, A2, b2, before_relu2);

    relu(100, before_relu2, before_fc3);

    fc(10, 100, before_fc3, A3, b3, y);

    softmax(10, y, y);



    //逆伝播

    softmaxwithloss_bwd(10, y, t, y3);

    fc_bwd(10, 100, before_fc3, y3, A3, dEdA3, dEdb3, y2);

    relu_bwd(100, before_relu2, y2, y2);

    fc_bwd(100, 50, before_fc2, y2, A2, dEdA2, dEdb2, y1);

    relu_bwd(50, before_relu1, y1, y1);

    fc_bwd(50, 784, before_fc1, y1, A1, dEdA1, dEdb1, y0);



    //メモリ解放

    free(y0);free(y1);free(y2);free(y3);

    free(before_fc1);free(before_fc2);free(before_fc3);

    free(before_relu1);free(before_relu2);

}



//n行ベクトルxの配列をシャッフルする

void shuffle(int n, int *x){

    int i, j;

    for (i = 0; i < n; i++){

        j = (int)(rand()*(  n+1.0)/(1.0+RAND_MAX));

        int tmp_xi = x[i];

        x[i] = x[j];

        x[j] = tmp_xi;

    }

}



//損失関数を求める

float cross_entropy_error(const float * y, int t){

    return -1 *log(y[t] + 1e-7);

}



//n行ベクトルxをoに足す

void add(int n, const float *x, float *o){

    int i;

    for (i = 0; i < n; i++){

        o[i] += x[i];

    }

}



//n行ベクトルoにxをかける

void scale(int n, float x, float *o){

    int i;

    for (i = 0; i < n; i++){

        o[i] *= x;

    }

}



//n行ベクトルoをxで全要素を初期化

void init(int n, float x, float *o){

    int i;

    for (i = 0; i < n; i++){

        o[i] = x;

    }

}



//[-1:1]の範囲でn行ベクトルoを初期化

void rand_init(int n, float *o){

    int i;

    for (i = 0; i < n; i++){

        o[i] = ((float)rand() / ((float)RAND_MAX + 1)) * 2 - 1 ;

    }

}



//[0:1]の一様乱数を生成

//http://www.sat.t.u-tokyo.ac.jp/~omi/random_variables_generation.html#Gauss

float uniform( void ){

    return rand()/(RAND_MAX+1.0);

}



//n行ベクトルを正規分布で初期化

void rand_init_by_normal_dist(int n, float *o,float mu,float sigma){

    int i;

    for(i=0;i<n;i++){

        float z =sqrt( -2.0*log(uniform()) ) * cos( 2.0*3.1415*uniform() );

        o[i] =  sigma * z + mu;

        // printf("%f",o[i]);

    }

}





//一層分のパラメータを保存

void save(const char * filename, int m, int n, const float * A, const float * b){

    FILE *fp;

    fp = fopen(filename,"w");



    fwrite(A, sizeof(float), m*n, fp);

    fwrite(b, sizeof(float), m, fp);



    fclose(fp);

}



//一層分のパラメータを読み込む

void load(const char * filename, int m, int n, float * A, float * b){

    FILE *fp;

    fp = fopen(filename,"r");



    fread(A, sizeof(float), m*n, fp);

    fread(b, sizeof(float), m, fp);



    fclose(fp);

}

#include "nn.h"

#include <time.h>



//プロトタイプ宣言

//void learn_3layers(int train_count,int test_count,float * train_x,unsigned char * train_y,float * test_x, unsigned char * test_y );


/* 
int main(){



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



    learn_3layers(train_count,test_count,train_x,train_y,test_x,test_y);

    return 0;

}
*/

// 3層での学習

/*/void learn_3layers(int train_count,int test_count,float * train_x,unsigned char * train_y,float * test_x, unsigned char * test_y ){

    float *y = malloc(sizeof(float) * 10);

    float *dEdA = malloc(sizeof(float) * 784 * 10);

    float *dEdb = malloc(sizeof(float) * 10);

    float *dEdA_av = malloc(sizeof(float) * 784 * 10);//平均

    float *dEdb_av = malloc(sizeof(float) * 10);//平均

    float *A = malloc(sizeof(float)* 784*10);

    float *b = malloc(sizeof(float)*10);

    int * index = malloc(sizeof(int)*train_count);

    int epoch = 20;

    int batch = 100;

    float h = 0.01 ;

    int i,j,k,l,m;



    rand_init(784*10,A);

    rand_init(10,b);

    //エポックを回す

    for(i=0;i<epoch;i++){

        printf("-----------------------------------------------------\n");

        printf("Epoch %d/%d\n", i+1,epoch);

        //インデックスを作成し、並び替え



        for(l=0 ; l<train_count ; l+=1) {

            index[l] = l;

            // printf("%d\n",index[i]);

        }



        shuffle(train_count, index);



        //ミニバッチ

        for(j=0;j<train_count /batch;j++){

            //平均勾配を初期化

            init(784*10,0,dEdA_av);

            init(10,0,dEdb_av);



            //一つ一つの勾配を計算する

            for(k=0;k<batch;k++){

                backward3(A,b,train_x+ 784*index[j*batch+k] ,train_y[index[j*batch+k]],y,dEdA,dEdb);

                add(784*10,dEdA,dEdA_av);

                add(10,dEdb,dEdb_av);

            }

            //ミニバッチで割って平均を求める

            scale(784*10,-h/batch,dEdA_av);

            scale(10,-h/batch,dEdb_av);

            // print(1,10,dEdb_av);



            //係数A,bを更新

            add(784*10,dEdA_av,A);

            add(10,dEdb_av,b);

            // print(784,10,dEdA_av);



        }



        //訓練データでの推論

        int sum = 0;

        float loss_sum = 0;

        float acc = 0.0;

        for(m=0 ; m<train_count ; m++) {

            if(inference3(A,b, train_x + m*784,y) == train_y[m]) {

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

            if(inference3(A, b, test_x + m*784,y) == test_y[m]) {

                sum_test++;

            }

            loss_sum_test += cross_entropy_error(y,test_y[m]);

        }

        acc_test = sum_test * 100.0 / test_count;



        printf("Accuracy Val : %f ％ \n",acc_test);

        printf("Loss  Average Val : %f\n",loss_sum_test/test_count);

    }

}
*/
#include "nn.h"



#include <time.h>



//プロトタイプ宣言

void learn_6layers(int train_count,int test_count,float * train_x,unsigned char * train_y,float * test_x, unsigned char * test_y, char *argv[]);



/*

第1~3引数 : FC1~FC3のパラメータの保存先

*/

int main(int argc,char *argv[]){



    //パラメータの保存先が指定されていない場合エラーを返す

    if (argc <4){

        printf("データの保存先を引数で設定してください。\n");

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

    int epoch = 10;

    int batch = 100;

    float h = 0.1;

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

                printf("%f \r", (float)j * 100 / (train_count / batch));

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