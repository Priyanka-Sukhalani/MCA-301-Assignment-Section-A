/*
	Suppose you are managing the construction of billboards on the university road,
	a heavily travelled stretch of road that runs west-east for M miles. The possible 
	sites for billboards are given by numbers ‫x1,x2,...xn each in the interval [0, ‫M]
	(specifying their position along the roads, measured in miles from its western end). 
	If you place billboard at location ‫xi , you receive revenue of ‫ri > 0.

	Regulations imposed by the Delhi road authority require that no two billboards be
	within less than or equal to 5 miles of each other. You had like to place billboards at
	a subset of the sites so as to maximize your total revenue, subject to this restriction.
	Example: Suppose M=20, n=4
	{x1, x2, x3, x4} = {6, 7, 12, 14} and {r1, r2, r3, r4} = {5, 6, 5, 1}

	Then the optimal solution would be to place billboards at ‫x1 and x3 for total revenue
	of 10.
	Give an algorithm that takes an instance of this problem as input and returns the
	maximum total revenue that can be obtained from any valid subsets of sites.

*/

/*
	Space Complexity: O(M).
	Time Complexity : O(M)

*/

using namespace std;
#include <iostream>

#define min_placement 5

void printBillBoard(int x[],int k,bool billboard_no[]) {
	
	/*
		x[] : array containing billboard position
		k   : no of billboards
		billboard_no[] : array consisting of 1/0 :
				 where 1 represents the billboard which is placed.
	*/

	cout << "\n BillBoard should be placed (Position) at : ";
	// printing the miles at which billboard are placed.
	for ( int i=0; i < k; i++) {
		if ( billboard_no[i] == 1 ) {
			cout << x[i] << "-miles ";
		}
	}
	cout << endl;
}

int billboard_construction( int M, int k, int x[], int r[] ) {

	int max_rev[M+1];			// to represent maximum revenue at each mile.
						// Maximum mile is M.
	for ( int i=0; i <= M; i++) {
		max_rev[i] = 0;
	}
	int n = 0;

	bool billboard_no[k];			// to know which billboard is placed.
	for( int i=0; i < k; i++ ) 
		billboard_no[i] = 0;


	for ( int i = 1; i <= M; i++ ) {

		if ( n < k ) {
			if ( x[n] != i ) 	// if ith mile is not a billboard position
				max_rev[i] = max_rev[i-1];	// maximum revenue is revenue of previous mile.

			else {
				if ( i <= min_placement ) { 	// when we need to the what will be the starting billboard

					// to choose/ignore the starting billboard which are less than or equal to 5 miles apart
					int t1 = max_rev[i-1]; 
					int t2 = r[n];
					if ( t1 > t2 ) {
						max_rev[i] = t1;
					}

					else {
						max_rev[i] = t2;
					}
				}

				else {
					// if ith mile matches with billboard position
					int t1 = max_rev[i-min_placement-1] + r[n];	// current billboard revenue + maximum revenue of i-6 billboard
					int t2 = max_rev[i-1];				// current revenue does not contribute to maximum revenue
					if ( t1 > t2 ) {
						
						max_rev[i] = t1;
					}
					else {
						max_rev[i] = t2;
					}
				}

				n++;
			}
		}

		else
			max_rev[i] = max_rev[i-1];
	
	}

	n = k-1;
	int value = max_rev[M];
	
	//Finding BillBoard No which are being placed.
	for ( int i = M-1; i >= 0 ; i-- ) {
		
		if ( value == max_rev[i] && max_rev[i] > 0 ) {

				while ( value == max_rev[i] )
					i--;

				while ( n >= 0 ) {
					if ( x[n] == i+1 ) {
						
						billboard_no[n] = 1;
						value -= r[n];
						break;
					}
					n--;
				}
		}
	}

	//Printing BillBoard No which are being placed.
	printBillBoard(x,k,billboard_no);

	return max_rev[M];
}

int main () {

	int k;
	cout << "\n Enter How many Billboard position(and their revenues) you have ? : ";
	cin >> k;

	int x[k], r[k];

	cout<< "\n Enter BillBoard Position aand their corresponding revenues : "<<endl<<endl;
	for ( int i=0; i<k; i++ ) {
		cout <<" BillBoard Position  : ";
		cin >> x[i];
		if ( x[i] - x[i-1] < 0 && i > 0 ) {
			cout << "\n Cannot allow billboard less than the previous billboard position.";
			cout << "\n Re-enter BillBoard Position greater than previous billboard position  : ";
			cin >> x[i];
		}
		cout <<" BillBoard Revenue   : ";
		cin >> r[i];
		cout <<"\n";
	}

	int M;
	cout << " Total Mile : ";
	cin >> M;

	int maximum_revenue = billboard_construction (M, k, x, r);

	cout << "\n The maximum revenue obtained : "<<maximum_revenue << endl;


	return 0;
}
