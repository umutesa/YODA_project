#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <time.h>
using namespace std;
 
/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n){
	int i, key, j;
	for (i = 1; i < n; i++){
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key){
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

int array[2000][2000];
int arr[2000][2000];

int main(){
	int window[8], row = 0, col = 0, nrows = 0, ncols = 0, MAX=0;
	ifstream infile("./img/img_noise/i1_s.pgm");
	stringstream ss;
	string inputLine = "";

	// Continue with a stringstream
	ss << infile.rdbuf();

	// Secondline : size of image
	ss >> ncols >> nrows >> MAX;

	//print total number of rows, columns and maximum intensity of image
	cout << ncols << " columns and " << nrows << " rows" <<endl<< " Maximum Intensity" << MAX <<endl;

	//Initialize a new array of same size of image with 0
	for(row = 0; row <= nrows; ++row){
		array[row][0]=0;	
	}
		
	for( col = 0; col<=ncols; ++col ){
		array[0][col]=0;
	}

	// Following lines : data
	for(row = 1; row <= nrows; ++row){
		for (col = 1; col <= ncols; ++col){
			//original data store in new array
			ss >> array[row][col];
		}
	}

	int start = clock();
	// Now print the array to see the result
	for(row = 1; row <= nrows; ++row){
		for(col = 1; col <= ncols; ++col){
			//neighbor pixel values are stored in window including this pixel
			window[0] = array[row-1][col-1];
			window[1] = array[row-1][col];
			window[2] = array[row-1][col+1];
			window[3] = array[row][col-1];
			window[4] = array[row][col];
			window[5] = array[row][col+1];
			window[6] = array[row+1][col-1];
			window[7] = array[row+1][col];
			window[8] = array[row+1][col+1];

			//sort window array
			insertionSort(window,9);
			//put the median to the new array
			arr[row][col]=window[4];
		}
	}
	int end = clock();
	ofstream outfile;
	
	//new file open to store the output image
	outfile.open("i1_s_filt.pgm");
	outfile<<"P2"<<endl;
	outfile<<ncols<<" "<<nrows<<endl;
	outfile<<"255"<<endl;
	
	for(row = 1; row <= nrows; ++row){
		for (col = 1; col <= ncols; ++col){
			//store resultant pixel values to the output file
			outfile << arr[row][col]<<" ";
		}
	}
	
	outfile.close();
	infile.close();
	printf ("Run Time: %0.8f sec \n",((float) end - start)/CLOCKS_PER_SEC);
	return 0 ;
}
