__kernel void matrixMultiplication(__global int* matrixA, __global int* matrixB, __global int* output, int widthA){
	
	//TODO: program your kernel here
	int workItemNum = get_global_id(0); //Work item ID
	int workGroupNum = get_group_id(0); //Work group ID
	int localGroupID = get_local_id(0); //Work items ID within each work group
	//int workIremNum = get_local_id(0);

	//memory buffers
	int arg1 = *matrixA;
	int arg2 = *matrixB;
	uint global_addr = workItemNum;
	
	int row = workGroupNum;
	int col = global_addr % widthA;
	//printf("Hello World\n");
	//printf("Length: %d", arg1[1]);
	int matA = matrixA[workItemNum];
	int matB = matrixB[workItemNum];
	//output[global_addr] = arg1[2] + arg2[2];
	int sum = 0;
	for (int i = 0; i <  widthA; i++) {
		sum +=  matrixA[(row*widthA)+i] * matrixB[(widthA*i)+col];
	}
	output[global_addr] = sum;
	//printf("Hi from work item: %d	work group:%d	Arg1: %d	Arg2: %d	Output: %d\n",global_addr, workGroupNum, matA, matB, output[global_addr]);
	
	
	
	void sort(int *a, int *b, int *c) {
   int swap;
   if(*a > *b) {
      swap = *a;
      *a = *b;
      *b = swap;
   }
   if(*a > *c) {
      swap = *a;
      *a = *c;
      *c = swap;
   }
   if(*b > *c) {
      swap = *b;
      *b = *c;
      *c = swap;
   }
}


__kernel void median_filter(__global int* inImage, __global int* output, int width, int height)
{
    int workItemNum = get_global_id(0);
    int workGroupNum = get_group_id(0);

    float arg1 = *inImage;
    uint global_addr = workItemNum;

    int posx = workItemNum;
    int posy = workGroupNum;

    uint i = width*posy + workItemNum%width;
    //printf("i = %d\n", i);
    
    
    //printf("hello world\n");

    //printf("WorkItem: %d WorkGroup: %d\n", posx, posy);
    if ((posx%width == 0) || (posy == 0) || (posx == width-1) || (posy == height-1)) {
        //printf("WorkItem: %d WorkGroup: %d\n", posx, posy);
        output[i] = inImage[i];

    }
    else {
        int pix0, pix1, pix2, pix3, pix4, pix5, pix6, pix7, pix8;

        pix0 = inImage[i - 1 - width];
        pix1 = inImage[i - width];
        pix2 = inImage[i + 1 - width]; 
        pix3 = inImage[i - 1];
        pix4 = inImage[i];
        pix5 = inImage[i + 1];
        pix6 = inImage[i - 1 + width];
        pix7 = inImage[i + width];
        pix8 = inImage[i + 1 + width];

        //printf("i = %d\n", i);
        //printf("pixels  %d  %d   %d  %d  %d  %d  %d  %d  %d  %d   %d   %d  %d  %d  %d  %d  %d  %d  %d\n", i, i-1-width, i-width, i+1-width, i-1, i, i+1, i-1+width, i+width, i+1+width, pix0, pix1, pix2, pix3, pix4, pix5, pix6, pix7, pix8);

        //sort the rows
        sort( &(pix0), &(pix1), &(pix2) );
        sort( &(pix3), &(pix4), &(pix5) );
        sort( &(pix6), &(pix7), &(pix8) );
        //sort the columns
        sort( &(pix0), &(pix3), &(pix6) );
        sort( &(pix1), &(pix4), &(pix7) );
        sort( &(pix2), &(pix5), &(pix8) );
        //sort the diagonal
        sort( &(pix0), &(pix4), &(pix8) );
        // median is the the middle value of the diagonal
        output[i] = pix4;
        //printf("Pixel 4: %d     %d\n", output[i],i);
    }

}
	
}
