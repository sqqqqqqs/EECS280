#include <iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include"constants.h"
#include"image.h"

using namespace std;
typedef unsigned char (*Agg)(const unsigned char values[3][3]);

void readImage( std::istream &is, Image &imI ){  //input function
    string type;
    string Max;
    is>>type>>imI.w>>imI.h>>Max;
    is.get();
    for(auto j=0U;j<imI.h;j++){
        for(auto i=0U;i<imI.w;i++){
            char parameter;     //use a temp variable to tract every RGB out and assign to corresponding value in matrix
            is.read(&parameter,1);
            imI.image[i][j].red=parameter;
            is.read(&parameter,1);
            imI.image[i][j].green=parameter;
            is.read(&parameter,1);
            imI.image[i][j].blue=parameter;
        }
    }
}

void writeImage(ostream &os, const Image &imI){    //output function
    os<<"P6"<<endl<<imI.w<<" "<<imI.h<<endl<<"255"<<endl;

    for(auto j=0u;j<imI.h;j++) {
        for (auto i = 0U; i < imI.w; i++) {
            os<<imI.image[i][j].red<<imI.image[i][j].green<<imI.image[i][j].blue;
        }
    }
}

void verticalFlip(const Image &imI, Image &imJ){  //function to realize vertical flipping
    imJ.h = imI.h;
    imJ.w = imI.w;
    for (auto j = 0U; j < imI.h; j++) {
        for (auto i = 0U; i < imI.w; i++) {
            imJ.image[i][j].red=imI.image[i][imI.h-j-1].red;
            imJ.image[i][j].green=imI.image[i][imI.h-j-1].green;
            imJ.image[i][j].blue=imI.image[i][imI.h-j-1].blue;
        }
    }
}

void rotate90(const Image &imI, Image &imJ){  //function to realize rotating 90 degree
    imJ.h = imI.w;
    imJ.w = imI.h;
    for (auto j = 0U; j < imI.h; j++) {
        for (auto i = 0U; i < imI.w; i++) {
            imJ.image[j][i].red=imI.image[i][imI.h-j-1].red;
            imJ.image[j][i].green=imI.image[i][imI.h-j-1].green;
            imJ.image[j][i].blue=imI.image[i][imI.h-j-1].blue;
        }
    }
}

void intensityInversion(const Image &imI, Image &imJ){   //function to realize inversion of intensity
    imJ.h = imI.h;
    imJ.w = imI.w;
    for (auto j = 0U; j < imI.h; j++) {
        for (auto i = 0U; i < imI.w; i++) {
            imJ.image[i][j].red=M-imI.image[i][j].red;
            imJ.image[i][j].green=M-imI.image[i][j].green;
            imJ.image[i][j].blue=M-imI.image[i][j].blue;
        }
    }
}

void filter_red(const Image &imI, Image &imJ,int i,int j,unsigned char temp[3][3]){//implement the red elements when filtering
    for(int x=i-1;x<=i+1;x++){
        for(int y=j-1;y<=j+1;y++){
            if(x<0||x>=(int)imI.w||y<0||y>=(int)imI.h){
                temp[x-i+1][y-j+1]=0;
            }
            else{
                temp[x-i+1][y-j+1]=imI.image[x][y].red;
            }
        }
    }
}

void filter_green(const Image &imI, Image &imJ,int i,int j,unsigned char temp[3][3]){//implement the green elements when filtering
    for(int x=i-1;x<=i+1;x++){
        for(int y=j-1;y<=j+1;y++){
            if(x<0||x>=(int)imI.w||y<0||y>=(int)imI.h){
                temp[x-i+1][y-j+1]=0;
            }
            else{
                temp[x-i+1][y-j+1]=imI.image[x][y].green;
            }
        }
    }
}

void filter_blue(const Image &imI, Image &imJ,int i,int j,unsigned char temp[3][3]){//implement the blue elements when filtering
    for(int x=i-1;x<=i+1;x++){
        for(int y=j-1;y<=j+1;y++){
            if(x<0||x>=(int)imI.w||y<0||y>=(int)imI.h){
                temp[x-i+1][y-j+1]=0;
            }
            else{
                temp[x-i+1][y-j+1]=imI.image[x][y].blue;
            }
        }
    }
}
void filter(const Image &imI, Image &imJ, Agg f){ // the main filter function using function pointer AGG f
    imJ.h=imI.h;
    imJ.w=imI.w;
    for(int j=0;j<(int)imI.h;j++){
        for(int i=0;i<(int)imI.w;i++){
            unsigned char temp[3][3];
            filter_red(imI,imJ,i,j,temp);
            imJ.image[i][j].red=f(temp);

            filter_green(imI,imJ,i,j,temp);
            imJ.image[i][j].green=f(temp);

            filter_blue(imI,imJ,i,j,temp);
            imJ.image[i][j].blue=f(temp);
        }
    }
}

unsigned char max(const unsigned char values[3][3]){   //the function to realize max filtering
    unsigned char Max=values[0][0];
    for(auto j=0U;j<3U;j++){
        for(auto i=0U;i<3U;i++){
            if(values[i][j]>Max){
            Max=values[i][j];}
        }
    }
    return Max;
}

unsigned char mean(const unsigned char values[3][3]) {  // the function to realize mean filtering
    int sum = 0;
    unsigned char average;
    for (auto j =0U; j < 3U; j++) {
        for (auto i = 0U; i < 3U; i++) {
            sum =sum+ values[i][j];
        }
    }
    average=sum/9;
    return average;
}

unsigned char median(const unsigned char values[3][3]) {  // the function to realize median filtering
    int data[9];
    for(auto j=0U;j<3U;j++){
        auto i=0U;
        data[j]=values[i][j];
    }
    for(auto j=0U;j<3U;j++){
        auto i=1U;
        data[j+3]=values[i][j];
    }
    for(auto j=0U;j<3U;j++){
        auto i=2U;
        data[j+6]=values[i][j];
    }
    sort(data,data+9);
    unsigned char med=data[4];
    return med;
}

void applyTransformation(const Image& imI, Image& imJ, const string& transform,bool &transform_exist) {  //function to judge which transform should be applied
    if (transform == "verticalFlip") {
        verticalFlip(imI, imJ);
    } else if (transform == "rotate90") {
        rotate90(imI, imJ);
    } else if (transform == "intensityInversion") {
        intensityInversion(imI, imJ);
    } else if (transform == "maxFilter") {
        filter(imI, imJ, max);
    } else if (transform == "meanFilter") {
        filter(imI, imJ, mean);
    } else if (transform == "medianFilter") {
        filter(imI, imJ, median);
    } else {
        cout << TRANSFORM_ERROR << endl;
        transform_exist= false;
        return ;
    }
}

int main(int argc,char *argv[]) { // the main function
   string input_name,output_name,transform;
   bool input_exist= false;
   bool output_exist= false;

   for(int i=1;i<argc;i++){
      string temp=argv[i];
      if(temp=="-h"||temp=="--help"){
           cout<<HELP_MESSAGE<<endl;
           return 0;
      }
      if(temp=="-t"){
          transform=argv[i+1];
      }
      if(temp=="-i"){
          input_exist= true;
          input_name=argv[i+1];
      }
      if(temp=="-o"){
          output_exist= true;
          output_name=argv[i+1];
      }
      
   }

    Image imI;
    Image imJ;

   if(input_exist){
       ifstream ifs(input_name,ios_base::out|ios_base::binary);
       if(!ifs){
       cout<<FILE_NOT_EXIST_ERROR<<endl;
       return 0;}
       string suffix=input_name.substr(input_name.length()-4);
       if(suffix!=".ppm"||input_name.length()<4){
           cout<<FILE_TYPE_ERROR<<endl;
           return 0;
       }
       readImage(ifs,imI);
       ifs.close();
   }
   else{
       readImage(cin,imI);
   }

    bool transform_exist=true;   //detect the existence of the transform and apply the transform by
    applyTransformation(imI,imJ,transform,transform_exist);
    if(!transform_exist){
        return 0;
    }

   if(output_exist){
     ofstream ofs(output_name,ios_base::out | ios_base::binary);
       writeImage(ofs,imJ);
       ofs.close();
   }
   else{
       writeImage(cout,imJ);//if no that kind of file, directly write to the output
   }
return 0;
}
