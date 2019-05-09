#include<iostream>  
#include<map>  
#include<vector>  
#include<stdio.h>  
#include<cmath>  
#include<cstdlib>  
#include<algorithm>  
#include<fstream>  
#include<sstream>



using namespace std;

typedef pair<int, double>  PAIR;

//const int colLen = 14;
//const int rowLen = 178;
int start_time;
int end_time;

void quicksort(double arr[], int left, int right)
{
	int i = left, j = right;
	double tmp;
	double pivot = arr[(left + right) / 2];

	/* partition */
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quicksort(arr, left, j);
	if (i < right)
		quicksort(arr, i, right);
}

class knn
{
private:
	string TotalData[14][178];

	string TrainData[13][89];
	string TestData[13][89];

	string Train_Label[189];
	string Test_Label[189];

	double d_TrainData[13][89];
	double d_TestData[13][89];

	double dist[13][89];
	double add_dist[89] = { 0 };
	int k;

	map<int, double> map_index_dis;
	map<string, int> map_label_freq;

	double get_distance(double *d1, double *d2)
	{
//		double sum;
		
		{
			//sum += pow((d1[i] - d2[i]), 2);
		}

		return 0;
	}


public:
	void load_data();
	void get_all_distance();
	void get_max_freq_label();
	
	struct CmpByValue
	{
		bool operator() (const PAIR& lhs, const PAIR& rhs)
		{
			return lhs.second < rhs.second;
		}
	};

};

void split(const std::string& s,
	std::vector<std::string>& sv,
	const char delim ) {
	sv.clear();
	std::istringstream iss(s);
	std::string temp;

	while (std::getline(iss, temp, delim)) {
		sv.emplace_back(std::move(temp));
	}
	return;
}

void knn::load_data()
{
	int p = 0, q = 0;
	int a = 0, b = 0;
	int c = 0, d = 0;

	
	fstream file ;
	file.open("wine.txt");
	string inputStr;

	vector<string> inputContent;

	while (getline(file, inputStr, '\n'))
	{
		//if (getline(file, inputStr, ','))
		{
			inputContent.push_back(inputStr);

			string s = inputStr;		  
			cout << s<<endl;
			vector<string> sv;
			split(s, sv, ',');
			
			for (const auto& s : sv) {
				//cout <<s<<endl;
				TotalData[p][q] = s;
				p++;
					
			
			}
			for (p = 0; p < 14; p++)
			{
				//cout << "TotalData number" << "[" << p << "]" << "[" << q << "]" << TotalData[p][q] << endl;
				if (p == 13)
					q++;
					
			}	
			p = 0;
			
		}


		}
		cout << "finalllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll" << endl;
		file.close();

		/* input the Train_Data */

		for (int j = 0; j < 178; j++)
		{
			for (int i = 1; i < 14; i++)
			{
				if (j % 2 == 0)
				{
					Train_Label[b] = TotalData[0][j];

					TrainData[a][b] = TotalData[i][j];

					d_TrainData[a][b] = atof(TrainData[a][b].c_str());
					
					//cout << d_TestData[a][b] << endl;
					
					
					//cout << "TrainData number" << "[" << a << "]" << "[" << b << "]" << d_TrainData[a][b] << endl;
					a++;
					if (a == 13)
					{
					//		cout << "Train_Label  " << "[" << b << "]" << Train_Label[b] << endl;
						a = 0;
						b++;

					}
				}
				else
				{
					

					Test_Label[d] = TotalData[0][j];

					TestData[c][d] = TotalData[i][j];
					
					d_TestData[c][d] = atof(TestData[c][d].c_str());
					//cout <<"TestData number"<<"["<<c<<"]"<<"["<<d<<"]"<<d_TestData[c][d] << endl;
					c++;
					if (c == 13)
					{
					//		cout << "Test_Label  " << "[" << d << "]" << Test_Label[d] << endl;
						c = 0;
						d++;

					}
				}

			}

		}
		//正規化前置步驟 先找最大值 再做正規化


		double temp = 0;

		for (int a = 0; a < 13; a++)
		{
			for (int b = 0; b < 89; b++)
			{
				temp = max(temp, d_TrainData[a][b]);
			}			
			//cout <<"第"<<a+1<<"項之最大值"<<temp<<endl;
			for (int b = 0; b < 89; b++)
			{
				d_TrainData[a][b] = d_TrainData[a][b] / temp;
				//cout << d_TrainData[a][b]<<endl;
			}
			temp = 0;
		}
		temp = 0;

		for (int c = 0; c < 13; c++)
		{
			for (int d = 0; d < 89; d++)
			{
				temp = max(temp, d_TestData[c][d]);
			}
			//cout << "第" << c + 1 << "項之最大值" << temp << endl;
			for (int d = 0; d < 89; d++)
			{
				d_TestData[c][d] = d_TestData[c][d] / temp;
				//cout << d_TestData[c][d]<<endl;
			}
			temp = 0;
		}
		///////////////////////////////////////////////////////////////////////////








	}
	


	void knn::get_all_distance()
	{
	
		for (int d = 0; d < 89; d++)
		
		{			
			//for (int i = 0; i < 89; i++)

				for (int c = 0; c < 13; c++)
				{

					
						
							dist[c][d] = pow(d_TestData[c][0] - d_TestData[c][d], 2);
						//	cout << dist[c][d] << endl;
							cout << "dict" << "[" << c << "]" << "[" << d << "]" <<"第0筆之"<<"第" << c << "項參數與第"<<d<<"筆之距離"<< dist[c][d] << endl;
						
							
				}
			
		}
		for (int d = 0; d < 89; d++)
		{
			for (int c = 0; c < 13; c++)
			{

				add_dist[d] += dist[c][d];
				cout << "第0項與第" << d << "項" << "之距離" << add_dist[d] << endl;
				
			}

		}
			

	}

	

	
	

	void knn::get_max_freq_label()
	{
		double temp_add_dist[89];
		int max_label[89];
		for (int d = 0; d < 89; d++)
		{
			temp_add_dist[d] = add_dist[d];
		}

		quicksort(temp_add_dist, 0, 88);

		for (int d = 0; d < 6; d++)
		{
			for (int c = 0; c < 89; c++)
			{
				if (temp_add_dist[d] == add_dist[c])
				{

					max_label[c] = 1;
					cout <<"與第" <<c<<"個點最靠近"<<max_label[c]<<endl;
					
				}


				//	cout << "第0項與第" << d << "項" << "之距離" << temp_add_dist[d] << endl;
				//cout



			}
		}



	}
	
	



	int main()
	{
		
	int k;
	//cout << "please input the k value : " << endl;
	//cin >> k;
	knn knn;
	knn.load_data();
	knn.get_all_distance();
	knn.get_max_freq_label();


	system("pause");
	return 0;
	}
	








