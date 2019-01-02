// B-CPE-100_rush2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>
#include <string>
//#include <math>
#include <algorithm>
#include <iomanip>
using namespace std;

string strLowerChar(string);
string checkLanguage(string);
int amountChar(string);
double fabs(double a);

int main()
{
	//Initialization
	string mystr,  mychar, mycharlower, language;
	int count = 0;
	int strcount = 0;
	float charpercent = 0.0f;
	
	// Input sentence and characters
	cout << "Type your sentence: ";
	getline(cin, mystr);
	mystr = strLowerChar(mystr);	// Set to lower case
	cout << "Which character should I count? ";
	getline(cin, mychar);
	mycharlower = strLowerChar(mychar); // Set to lower case
	strcount = amountChar(mystr);
	
	// Calculate the amount of selected characters and percentage of occurrence 
	for (int j = 0; j < mycharlower.size(); j++)
	{
		if (mychar[j] != ' ')
		{
			for (int i = 0; i < mystr.size(); i++)
			{
				if (mystr[i] == mycharlower[j])
				{
					++count;
				}
			}
			charpercent = (float)count / strcount * 100;
			
			cout << mychar[j] << ":" << count << " (" << setprecision(2) << fixed << charpercent << "%)$" << "\n";
			count = 0;
			}
	}
	
	// Check language
	language = checkLanguage(mystr);
	return 0;
}

string strLowerChar(string mystr) 
{
	int i;
	for (i = 0; i < mystr.size(); i++) {
		if (mystr[i] >= 'A' && mystr[i] <= 'Z') {
			mystr[i] += 32;
		}
	}
	return mystr;
}

int amountChar(string mystr)
{
	// Calculate the amount of characters in mystr
	int strcount = 0;
	for (int i = 0; i < mystr.size(); i++)
	{
		if (mystr[i] != ' ')
		{
			++strcount;
		}
	}
	return strcount;
}

string checkLanguage(string mystr)
{
	// Check language
	float freqenglish[26] = { 8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074 };
	float freqgerman[26] = { 6.516, 1.886, 2.732, 5.076, 16.396, 1.656, 3.009, 4.577, 6.550, 0.268, 1.417, 3.437, 2.534, 9.776, 2.594, 0.670, 0.018, 7.003, 7.270, 6.154, 4.166, 0.846, 1.921, 0.034, 0.039, 1.134 };
	float freqfrench[26] = { 7.636, 0.901, 3.260, 3.669, 14.715, 1.066, 0.866, 0.737, 7.529, 0.613, 0.074, 5.456, 2.968, 7.095, 5.796, 2.521, 1.362, 6.693, 7.948, 7.244, 6.311, 1.838, 0.049, 0.427, 0.128, 0.326 };
	float freqspanish[26] = { 11.525, 2.215, 4.019, 5.010, 12.181, 0.692, 1.768, 0.703, 6.247, 0.493, 0.011, 4.967, 3.157, 6.712, 8.683, 2.510, 0.877, 6.871, 7.977, 4.632, 2.927, 1.138, 0.017, 0.215, 1.008, 0.467 };

	int strcount, c = 0, ccount[26] = { 0 }, lcount[5] = { 0 }, x;
	double percent, comp[4] = { 0 };
	string language;

	strcount = amountChar(mystr);

	while (mystr[c] != '\0')
	{
		/** Considering characters from 'a' to 'z' only and ignoring others. */

		if (mystr[c] >= 'a' && mystr[c] <= 'z') {
			x = mystr[c] - 'a';
			ccount[x]++;
		}

		c++;
	}

	for (c = 0; c < 26; c++)
	{
		//printf("%c occurs %d times in the string.\n", c + 'a', ccount[c]);
		percent = (double)ccount[c] / strcount * 100;

		comp[0] = fabs(percent - freqenglish[c]);
		comp[1] = fabs(percent - freqgerman[c]);
		comp[2] = fabs(percent - freqfrench[c]);
		comp[3] = fabs(percent - freqspanish[c]);

		if (comp[0] < comp[1] && comp[0] < comp[2] && comp[0] < comp[3])
			lcount[0]++;
		if (comp[1] < comp[0] && comp[1] < comp[2] && comp[1] < comp[3])
			lcount[1]++;
		if (comp[2] < comp[0] && comp[2] < comp[1] && comp[2] < comp[3])
			lcount[2]++;
		if (comp[3] < comp[0] && comp[3] < comp[1] && comp[3] < comp[2])
			lcount[3]++;
			   		 
	}
	lcount[4] = lcount[0] + lcount[1] + lcount[2] + lcount[3];
	if (lcount[0] > lcount[1] && lcount[0] > lcount[2] && lcount[0] > lcount[3])
	{
		language = "=> English";
		percent = (float)lcount[0] / lcount[4] * 100;
		cout << language << " (" << percent << "%)";
	}
	else if (lcount[1] > lcount[0] && lcount[1] > lcount[2] && lcount[1] > lcount[3])
	{
		language = "=> German";
		percent = (float)lcount[1] / lcount[4] * 100;
		cout << language << " (" << percent << "%)";
	}
	else if (lcount[2] > lcount[0] && lcount[2] > lcount[1] && lcount[2] > lcount[3])
	{
		language = "=> French";
		percent = (float)lcount[2] / lcount[4] * 100;
		cout << language << " (" << percent << "%)";
	}
	else if (lcount[3] > lcount[0] && lcount[3] > lcount[1] && lcount[3] > lcount[2])
		{
			language = "=> Spanish";
			percent = (float)lcount[3] / lcount[4] * 100;
			cout << language << " (" << percent << "%)";
		}
	else
	{
		language = "=> Text is too short to specify the language. Two or more languages have the same probability! ";
		cout << language;
	}

	return language;
}
