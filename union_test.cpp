    void do_search(int color,int h,int l,int r,int c,int[][] index);
    int main(){
    Mat image = imread(infilename, 0);
	Mat image_change = imread(infilename, 0);
	int r = image.rows;
	int c = image.cols*image.channels();
    int[][] copy=new int[r][c];
    int[][] index=new int[r][c];
    int ind=1;
	for (int j = 0; j<r ; j++) {
		uchar *data = image_change.ptr<uchar>(j);
		for (int i = 0; i<c; i++) {
            copy[j][i]=data[i];
		}
	}
    for(int j=0;j<r;j++){
        for(int i=0;i<c;i++){
            if(copy[j][i]=255)
            index[j][i]=1;
            else
            index[j][i]=0;
        }
    }
    for(int j=0;j<r;j++){
        for(int i=0;i<c;i++){
            if(index[j][i]==1){
                index++;
                do_search(index,j,i,r,c);
            }
        }
    }
    free(copy);
    free(index);
   }

    void do_search(int color,int h,int l,int r,int c,int[][] index){
        index[h][l]=color;
        if(h-1>=0&&index[h-1][l]==1)do_search(color,h-1,l,r,c,index);
        if(h+1<r&&index[h+1][l]==1)do_search(color,h+1,l,r,c,index);
        if(l-1>=0&&index[h][l-1]==1)do_search(color,h,l-1,r,c,index);
        if(l+1<c&&index[h][l+1]==1)do_search(color,h,l+1,r,c,index);
    }