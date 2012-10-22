//============================================================================
// Name        : playfair.cpp
// Author      : Tony Trinh
// Version     : 1.0
// Copyright   : Tony Trinh, Kuala Lumpur, 2012
// Description : playfair en-decryption
//============================================================================

#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define MATRIX_SIZE 5


vector< vector<char> > cipher_matrix(string key)
{
   const int LIST_SIZE = 25;
   vector<char> letter_list;
   vector<char> result_list;
   for(char letter = 'a'; letter <= 'z' ; letter++)
   {
      if(letter != 'j') letter_list.push_back(letter);
   }
   for(int i= 0; i <  key.length(); i++)
   {
      for(int j = 0; j < LIST_SIZE; j++)
      {
         if(key[i] == letter_list[j])
         {
            result_list.push_back(key[i]);
            letter_list[j] = '-';
            break;
         }
      }
   }
   for(int i = 0 ; i < LIST_SIZE ; i++)
   {
      if(letter_list[i] != '-') result_list.push_back(letter_list[i]);
   }

   vector< vector<char> > matrix;
   vector<char> temp_vector;
   for(int i = 0; i < result_list.size(); i++)
   {
      temp_vector.push_back(result_list[i]);
      if((i+1) % MATRIX_SIZE == 0)
      {
         matrix.push_back(temp_vector);
         temp_vector.clear();
//         cout << temp_vector.size();
      }
   }
   return matrix;
}
void print_matrix(vector< vector<char> > matrix )
{
   for (int i = 0; i < matrix.size(); i++)
   {
      for(int j = 0; j < matrix[i].size(); j++)
      {
         cout << matrix[i][j] << '\t';
      }
      cout << endl;
   }
}
int shift_left_up(int position)
{
   return (position + 4) % MATRIX_SIZE;
}

int shift_right_down(int position)
{
   return (position + 1) % MATRIX_SIZE;
}
string cipher_decipher (string input, bool mode, vector< vector<char> > matrix )
{
   string output = "";
   string init = "";
   char first = input[0];
   char second = input[1];
   int first_row = 0, first_col = 0;
   int second_row = 0, second_col = 0;
   for(int i = 0; i < MATRIX_SIZE; i++)
   {
      for(int j = 0; j < MATRIX_SIZE; j++)
      {
         if(first == matrix[i][j])
         {
            first_row = i;
            first_col = j;
         }
         if(second == matrix[i][j])
         {
            second_row = i;
            second_col = j;
         }
      }
   }
   if(first_row == second_row)
   {
//      shift_left_upshift_right_down
      if(mode == true)
      {
         output = init + matrix[first_row][shift_right_down(first_col)] + matrix[second_row][shift_right_down(second_col)];
      }
      else if(mode == false)
      {
         output = init + matrix[first_row][shift_left_up(first_col)] + matrix[second_row][shift_left_up(second_col)];
      }

   }
   else if(first_col == second_col)
   {
      if(mode == true)
      {
         output = init + matrix[shift_right_down(first_row)][first_col] + matrix[shift_right_down(second_row)][second_col];
      }
      else if(mode == false)
      {
         output = init + matrix[shift_left_up(first_row)][first_col] + matrix[shift_left_up(second_row)][second_col];
      }
   }
   else
   {
      output = init + matrix[first_row][second_col] + matrix[second_row][first_col];
   }

   return output;
}

int main()
{

   string input = "";//tessinx sample
   string output = "";
   string key = "";//committed sample
   cout << "Input: ";
   cin >> input;
   cout << "Key: ";
   cin >> key;
   string mode_str = "";
   bool mode = true;//encryption by default
   cout << "Choose 'en' for encrypt and 'de' for decryption (encryption by default): ";
   cin >> mode_str;
   if(mode_str == "de")
   {
      mode = false;
   }
   else
   {
      mode = true;
   }
   if((input.length() % 2) == 1) input += "x";
   vector< vector<char> > matrix = cipher_matrix(key);
   string process_pair = "";
//   print_matrix(matrix);
   while(true)
   {
      if(input.length() == 1)
      {
         process_pair = input + "x";
      }
      else
      {
         process_pair = input.substr(0,2);
         if(process_pair[0] == process_pair[1])
         {
            input = process_pair.substr(1,1) + input;
            process_pair = process_pair.substr(0,1) + "x";
//            cout << process_pair << "..." << endl;
         }
      }
//      cout << process_pair << '\t';
      process_pair = cipher_decipher(process_pair, mode, matrix);
      output +=  process_pair;
//      cout << process_pair << '\t' << output << endl;
      if(input.length() > 2)
      {
        input = input.substr(2);

      }
      else break;
   }
   cout << output;
   return 0;
}
