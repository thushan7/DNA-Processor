#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define NUMPROTEINS 64
#define SIZE 100

/*This function obtains the corresponding single-letter code for a nucleotide triplet.
One character array parameter containing nucleotide triplet.
Returns a character representing single-letter code.*/
char getCode (char protein [3]) {

    // array allProteins has a list of all 3-triplet amino acids required for this assignment

    char allProteins [NUMPROTEINS][SIZE] = {"GCA","GCC","GCG","GCU","AGA","AGG","CGA","CGC","CGG","CGU","GAC", "GAU","AAC","AAU","UGC","UGU","GAA","GAG","CAA","CAG","GGA","GGC","GGG","GGU","CAC","CAU","AUA","AUC","AUU", "UUA","UUG","CUA","CUC","CUG","CUU","AAA","AAG","AUG","UUC","UUU","CCA","CCC","CCG","CCU","AGC","AGU","UCA","UCC","UCG","UCU","ACA","ACC","ACG","ACU","UGG","UAC","UAU","GUA","GUC","GUG","GUU"};

    // array allCodes stores the single-letter code of each triplet given in the above array

    char allCodes [NUMPROTEINS] = {'A','A','A','A','R','R','R','R','R','R','D','D','N','N','C','C','E', 'E','Q','Q', 'G','G','G','G','H','H','I','I','I', 'L','L','L','L','L','L','K','K','M','F','F','P', 'P','P','P','S','S','S','S','S','S','T','T','T','T', 'W','Y','Y','V','V','V','V'};

    for (int i = 0; i < NUMPROTEINS; i++) {

        if  (strncmp (protein, allProteins[i], 3) == 0) {
            return allCodes [i];
        }
    }

    return 'Z';   // to indicate an incorrect code - code that doesn't exist in array allCodes
}



/*This function determines whether or not two nucleotides form a base pair.
Two character parameters containing the two nucleotides.
Returns a boolean value showing if they are/aren't a base pair.*/
bool isBasePair (char neu1, char neu2) {
  bool basePair = false;

  //compares neu1 and neu2 with all possible base pair combinations
  if ((neu1=='A'&&neu2=='T') || (neu1=='T'&&neu2=='A') || (neu1=='C'&&neu2=='G') || (neu1=='G'&&neu2=='C')) {
    basePair = true;
  }

  return basePair;
}



/*This function determines whether or not two DNA strands form a DNA sequence.
Two character array parameters containing the two DNA strands.
Returns a boolean value showing if they are/aren't a DNA sequence.*/
bool isItaDnaSequence (char strand1 [SIZE], char strand2 [SIZE]) {
  bool dnaSequence = true;

  //uses isBasePair function to determine whether the 2 strands form a DNA
  for (int i=0; i<strlen(strand1); i++) {
    if (isBasePair(strand1[i], strand2[i])==false) {
      dnaSequence = false;
    }
  }

  return dnaSequence;
}



/*This function reverses a DNA strand.
One character array parameter contaning the DNA strand to be reversed.*/
void reverse (char aStrand [SIZE]) {
  //duplicates original array and then reassigns elements in reverse order using duplicated array
  char temp [SIZE+1];
  strcpy(temp, aStrand);

  for (int i=0; i<strlen(aStrand); i++) {
    aStrand[i] = temp[strlen(aStrand)-1-i];
  }
}



/*This function complements a DNA strand.
One character array parameter contaning the DNA strand to be complemented.*/
void complementIt (char aStrand [SIZE]) {
  //goes through array and switches each character with its complement
  for (int i=0; i<strlen(aStrand); i++) {
    switch (aStrand[i]) {
      case 'A':
        aStrand[i] = 'T';
        break;
      case 'C':
        aStrand[i] = 'G';
        break;
      case 'G':
        aStrand[i] = 'C';
        break;
      case 'T':
        aStrand[i] = 'A';
        break;
    }
  }
}



/*This function determines whether or not a DNA strand is a palindrome.
One character array parameter containing the DNA strand in question.
Returns a boolean value showing if it is/isn't a palindrome.*/
bool isItPalindrome (char aStrand [SIZE]) {
  bool palindrome = true;

  //first determines whether array has an even or odd number of elements
  if (strlen(aStrand)%2==0) {
    //then goes through array accordingly to see if it is read the same forwards and backwards
    for (int i=0; i<strlen(aStrand)/2; i++) {
      if (aStrand[i]!=aStrand[strlen(aStrand)-1-i]) {
        palindrome = false;
      }
    }
  }
  else {
    for (int i=0; i<(strlen(aStrand)-1)/2; i++) {
      if (aStrand[i]!=aStrand[strlen(aStrand)-1-i]) {
        palindrome = false;
      }
    }
  }

  return palindrome;
}



/*This function determines whether or not a DNA strand is a DNA palindrome.
One character array parameter containing the DNA strand in question.
Returns a boolean value showing if it is/isn't a DNA palindrome.*/
bool isStrandDnaPalindrome (char aStrand [SIZE]) {
  bool dnaPalindrome;

  //duplicates original array
  char temp [strlen(aStrand)];
  for (int i=0; i<strlen(aStrand); i++) {
    temp[i] = aStrand[i];
  }

  //complements and reverses duplicated array
  complementIt(temp);
  reverse(temp);

  //if the duplicated array is now the same as the original array, we have a DNA palindrome
  if (strcmp(aStrand, temp)==0) {
    dnaPalindrome = true;
  }
  else {
    dnaPalindrome = false;
  }

  return dnaPalindrome;
}



/*This function determines the number of a certain nucleotide in a given DNA strand.
One character array parameter containing the DNA strand, one character parameter containing the nucleotide.
Returns an integer representing the number of the given nucleotide in the DNA strand.*/
int howMany (char aStrand [SIZE], char neu) {
  int num = 0;

  //goes through entire array and increases counter variable whenever the desired character is found
  for (int i=0; i<strlen(aStrand); i++) {
    if (aStrand[i]==neu) {
      num++;
    }
  }

  return num;
}



/*This function obtains an mRNA sequence given a DNA sequence.
One character array parameter containing the DNA sequence, another empty character array parameter to hold the mRNA sequence.*/
void dnaToMrna (char aSeq [SIZE], char mRNA [SIZE]) {
  //copies aSeq into mRNA
  for (int i=0; i<strlen(aSeq); i++) {
    mRNA[i] = aSeq[i];
  }

  //complements mRNA
  complementIt(mRNA);

  //replaces every 'T' with a 'U'
  for (int i=0; i<strlen(aSeq); i++) {
    if (mRNA[i]=='T') {
      mRNA[i] = 'U';
    }
  }
}



/*This function determines the mRNA proteins from a DNA sequence.
One character array parameter containing the DNA sequence.*/
void translateDnaToMrnaProteins (char aSeq [SIZE]) {
  char mRNA [SIZE]; //mRNA equivalent of DNA sequence
  char neuTriple [3]; //each nucleotide triplet in mRNA sequence
  char code; //single-letter code for each nucleotide triplet

  //obtains mRNA sequence from DNA sequence
  dnaToMrna(aSeq, mRNA);

  printf("DNA: %s\n", aSeq);
  printf("mRNA: %s, which translates to:\n", mRNA);

  for (int i=0; i<(strlen(mRNA)-1)/3; i++) {
    //copies each nucleotide triple into neuTriple one at a time
    neuTriple[0] = mRNA[3*i];
    neuTriple[1] = mRNA[3*i+1];
    neuTriple[2] = mRNA[3*i+2];

    //obtains single-letter code for the nucleotide triple
    code = getCode(neuTriple);

    printf("%c%c%c : %c\n", neuTriple[0], neuTriple[1], neuTriple[2], code);
    if (code == 'Z') {
      printf("The input sequence has an incorrect base\n");
    }
  }
}
