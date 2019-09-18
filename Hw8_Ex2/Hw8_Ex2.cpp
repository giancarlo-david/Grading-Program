// Author:        Giancarlo David
// Course:        CS 1336.008
// Date:          12/6/2016
// Assignment:    Lecture Homework #8 Exercise# 2
// Compiler:      Visual C++ 2015
// Description:   This program demonstrates uses of arrays.

#include <iostream>
#include <fstream>
using namespace std;

void studentAnswers(char ans[], int &studentsEntered)
{
   // Set and define variables
   ifstream inputFile;
   int count = 0;

   // Open "StudentAnswers.txt"
   inputFile.open("StudentAnswers.txt");

   // While loop for when inputFile >> ans[count]
   while (inputFile >> ans[count])
   {
      count++;
   }

   // Close "StudentAnswers.txt"
   inputFile.close();

   // Set studentsEntered = count / 20
   studentsEntered = count / 20;
}

void answerKey(char correct[])
{
   // Define and set variables
   ifstream inputFile;
   int count = 0;

   // Open "CorrectAnswers.txt"
   inputFile.open("CorrectAnswers.txt");

   // While loop for when inputFile >> correct[count]
   while (inputFile >> correct[count])
   {
      count++;
   }

   // Close "CorrectAnswers.txt"
   inputFile.close();
}

int main()
{
   // Define and set variables
   const int questions = 20;
   char correct[questions];
   const int answers = 300;
   char numAnswers[answers];
   const int numStudents = 16;
   char student[numStudents][questions];
   int percent[numStudents];
   int studentsEntered;
   int bestGrade = 0;
   int worstGrade = 2000;
   int worstStudent;
   int bestStudent;

   // Call answerKey and studentAnswers
   answerKey(correct);
   studentAnswers(numAnswers, studentsEntered);
   
   // Set variables
   int studentNumber = 1;
   int counter = 0;

   // While loop for when counter < answers
   while (counter < answers)
   {
      // For loop to store student's answers in student array
      for (int count = 0; count < 20; count++)
      {
         student[studentNumber][count] = numAnswers[counter];
         counter++;
      }
      studentNumber++;
   }

   // Open "ExamAnalysis.txt"
   ofstream outputFile;
   outputFile.open("ExamAnalysis.txt");

   // For loop to get student grades
   for (int studentNumber = 1; studentNumber <= studentsEntered; studentNumber++)
   {
      // Set and define variables
      int questionNum = 0;
      int right = 0;
      int wrong = 0;
      int questionsMissed[20];

      // For loop to get questions right and wrong
      for (int count = 0; count < 20; count++)
      {
         // If statement for when student answer is correct
         if (correct[count] == student[studentNumber][count])
         {
            right++;
         }

         // Else statement for when student answer is wrong
         else
         {
            questionsMissed[wrong] = count + 1;
            wrong++;
         }
      }

      // Set percent = (right * 100) / 20
      percent[studentNumber] = (right * 100) / 20;

      // Display results
      cout << "Report for Student " << studentNumber << ":" << endl;
      cout << "---------------------" << endl;
      cout << "Missed " << wrong << " out of 20 questions for " << percent[studentNumber] << "% correct." << endl;
      cout << "Questions missed:" << endl;
      cout << "\t";
      outputFile << "Report for Student " << studentNumber << ":" << endl;
      outputFile << "---------------------" << endl;
      outputFile << "Missed " << wrong << " out of 20 questions for " << percent[studentNumber] << "% correct." << endl;
      outputFile << "Questions missed:" << endl;
      outputFile << "\t";

      // For loop to display questionsMissed
      for (int number = 0; number < wrong; number++)
      {
         int value = questionsMissed[number] - 1;
         cout << questionsMissed[number] << "(" << correct[value];
         cout << "/" << student[studentNumber][value] << ")";
         outputFile << questionsMissed[number] << "(" << correct[value];
         outputFile << "/" << student[studentNumber][value] << ")";

         if (number == (wrong - 1))
         {
            cout << endl;
            outputFile << endl;
         }
         else
         {
            cout << ", ";
            outputFile << ", ";
         }
      }

      if (percent[studentNumber] < 70)
      {
         cout << "This student failed the exam." << endl << endl;
         outputFile << "This student failed the exam." << endl << endl;
      }
      else
      {
         cout << "This student passed the exam!" << endl << endl;
         outputFile << "This student passed the exam!" << endl << endl;
      }
   }

   // For loop to find best grad and worst grade
   for (int count = 1; count <= studentsEntered; count++)
   {
      if (percent[count] > bestGrade)
      {
         bestGrade = percent[count];
         bestStudent = count;
      }
      if (percent[count] < worstGrade)
      {
         worstGrade = percent[count];
         worstStudent = count;
      }

   }
   
   // Display results
   cout << "Student " << bestStudent << " had the best grade with " << bestGrade << "%." << endl;
   outputFile << "Student " << bestStudent << " had the best grade with " << bestGrade << "%." << endl;
   cout << "Student " << worstStudent << " had the worst grade with " << worstGrade << "%." << endl;
   outputFile << "Student " << worstStudent << " had the worst grade with " << worstGrade << "%." << endl;
   
   // Close "ExamAnalysis.txt"
   outputFile.close();

   system("pause");
   return 0;
}