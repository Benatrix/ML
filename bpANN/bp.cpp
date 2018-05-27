#include"bp.h"

using namespace cv;
using namespace ml;
void bp_train()
{
    //input jointData
    string fileJointTxt="/home/luzj/Code_Exer2/Force_Control/bpANN/joint.txt";
    ifstream jointData(fileJointTxt.c_str(),ios_base::in);
    int matRow=0;
    int matRol=6;
    Mat matJoint;
    if(!jointData.is_open())
    {
        cout<<"jointData failed!"<<endl;
    }
    istream_iterator<float> begin(jointData);
    istream_iterator<float> end;
    vector<float> jointDataVec(begin,end);
    Mat temp=Mat(jointDataVec);
    size_t dataLength=jointDataVec.size();
    matRow=dataLength/matRol;
    if((matRow*matRol)!=dataLength)
    {
        cout<<"joint:row and rol are wrong!"<<endl;
    }
    matJoint=temp.reshape(0,matRow).clone();
    jointData.close();

    //input forceData
    string fileForceTxt="/home/luzj/Code_Exer2/Force_Control/bpANN/force.txt";
    ifstream forceData(fileForceTxt.c_str(),ios_base::in);
    int matRow1=0;
    int matRol1=6;
    Mat matForce;
    if(!forceData.is_open())
    {
        cout<<"forceData failed!"<<endl;
    }
    istream_iterator<float> begin1(forceData);
    istream_iterator<float> end1;
    vector<float> forceDataVec(begin1,end1);
    Mat temp1=Mat(forceDataVec);
    size_t dataLength1=forceDataVec.size();
    matRow1=dataLength1/matRol1;
    if((matRow*matRol)!=dataLength1)
    {
        cout<<"joint:row and rol are wrong!"<<endl;
    }
    matForce=1.63*temp1.reshape(0,matRow1).clone();
    forceData.close();

    //qDebug()<<matRow1;
    //ANN_MLP bp;
    Ptr<ANN_MLP> bp = ANN_MLP::create();
    Mat layerSize=(Mat_<int>(1,3)<<6,17,6);
    bp->setLayerSizes(layerSize);
    bp->setTrainMethod(ml::ANN_MLP::BACKPROP);
    //bp->setActivationFunctions(ANN_MLP::SIGMOID_SYM);
    bp->setActivationFunction(ANN_MLP::SIGMOID_SYM);
    bp->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER,10000,1e-6));
   //bp->set


    bool trained=bp->train(matJoint,ml::ROW_SAMPLE,matForce);
    if(trained)
    {
        bp->save("/home/luzj/Code_Exer2/Force_Control/bpANN/bp_param.xml");
    }


    //test
    Mat sample(2, 6,CV_32FC1);
    sample.at<float>(0, 0) = -85.9176;
    sample.at<float>(0, 1) = -90.5799;
    sample.at<float>(0, 2) = -99.2209;
    sample.at<float>(0, 3) = -86.4821;
    sample.at<float>(0, 4) = 77.3912;
    sample.at<float>(0, 5) = -83.8618;

    sample.at<float>(1, 0) = -78.283;
    sample.at<float>(1, 1) = -78.4797;
    sample.at<float>(1, 2) = -106.471;
    sample.at<float>(1, 3) = -23.3328;
    sample.at<float>(1, 4) = 91.1467;
    sample.at<float>(1, 5) = -66.0623;
/*
    sample.at<float>(2, 0) = -85.9203;
    sample.at<float>(2, 1) = -90.5757;
    sample.at<float>(2, 2) = -99.2189;
    sample.at<float>(2, 3) = -76.1869;
    sample.at<float>(2, 4) = 87.8138;
    sample.at<float>(2, 5) = -49.5508;



    sample.at<float>(3, 0) = -85.9162;
    sample.at<float>(3, 1) = -90.5764;
    sample.at<float>(3, 2) = -99.2203;
    sample.at<float>(3, 3) = -33.664;
    sample.at<float>(3, 4) = 87.8104;
    sample.at<float>(3, 5) = -49.546;
*/


    Mat response_result(2, 6,CV_32FC1);
    Mat response;
    response_result.at<float>(0,0)=0.1375;
    response_result.at<float>(0,1)=-0.21;
    response_result.at<float>(0,2)=0.94;
    response_result.at<float>(0,3)=0.0275;
    response_result.at<float>(0,4)=-0.6275;
    response_result.at<float>(0,5)=-0.1125;

    response_result.at<float>(1,0)=-0.72;
    response_result.at<float>(1,1)=0.305;
    response_result.at<float>(1,2)=0.53;
    response_result.at<float>(1,3)=-0.17;
    response_result.at<float>(1,4)=-0.734167;
    response_result.at<float>(1,5)=0.2575;



    bp->predict(sample,response);
    response=response/1.63;
    double err_1=sqrt(pow(response.at<float>(0,0)-response_result.at<float>(0,0),2)+pow(response.at<float>(0,1)-response_result.at<float>(0,1),2)+pow(response.at<float>(0,2)-response_result.at<float>(0,2),2))/sqrt(pow(response_result.at<float>(0,0),2)+pow(response_result.at<float>(0,1),2)+pow(response_result.at<float>(0,2),2));

    double err_2=sqrt(pow(response.at<float>(1,0)-response_result.at<float>(1,0),2)+pow(response.at<float>(1,1)-response_result.at<float>(1,1),2)+pow(response.at<float>(1,2)-response_result.at<float>(1,2),2))/sqrt(pow(response_result.at<float>(1,0),2)+pow(response_result.at<float>(1,1),2)+pow(response_result.at<float>(1,2),2));

    cout<<response<<endl<<err_1<<endl<<err_2;





}
