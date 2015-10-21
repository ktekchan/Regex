#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

bool isMatch(const char *pattern, const char *filename){

   // base case
   if(strlen(pattern) == 0){
      return strlen(filename) == 0;
   }

   // Special case with pattern length of 1
   if(strlen(pattern) == 1){

      // if pattern is '?' then it matches with a string length of either 0 or 
      // 1
      if(pattern[0] == '?' && (strlen(filename) == 0 || 
               strlen(filename) == 1)){
         return true;
      }

      // if pattern is just '*', then it matches with any possible string
      else if(pattern[0] == '*'){
         return true;
      }

      // if pattern is neither, then filename must match the pattern
      else if(strlen(filename) == 1 && filename[0] == pattern[0]){
         return true;
      }

      else {
         return false;
      }
   }

   // Case with pattern char '?'
   if(pattern[0] == '?'){
      return isMatch(pattern+1, filename) || isMatch(pattern+1, filename+1);
   }

   // Case with pattern char '*'
   if(pattern[0] == '*'){

      int i = 0;
      int j = 1;

      // Check till pattern has '*'
      while(i<strlen(filename) && j<strlen(pattern)){
         if(pattern[j] != '*' && pattern[j] == filename[i]){
            return isMatch(pattern+j+1, filename+i+1);
         }
         i++;
         j++;
      }

      // Incase pattern has more characters remaining and filename does not
      if(strlen(pattern) - 2 > 0 && i==strlen(filename))
         return false;
   }

   // character in pattern matches that in filename
   if(pattern[0] == filename[0]){
      return isMatch(pattern+1, filename+1); 
   }

   return false;
}

class Glob {
   public:
      vector<string> Match(const string& pattern, const vector<string>& filenames) const {
         // IMPLEMENT ME
         vector<string> output; 

         for(int i=0; i<filenames.size(); i++){
            if(isMatch(pattern.c_str(), filenames[i].c_str())){
               output.push_back(filenames[i]);
            }
         }
         return output;
      }
};


bool vector_equal(const vector<string>& expected, const vector<string>& actual) {
   if (expected.size() != actual.size()) {
      return false;
   }
   for (size_t i = 0; i < expected.size(); ++i) {
      if (expected[i] != actual[i]) {
         return false;
      }
   }
   return true;
}

#ifndef __main__
#define __main__

int main(int argc, char* argv[]) {
   // Should return true
   cout << vector_equal(
         { "abcd", "dabc", "abc" },
         Glob().Match("?abc*", { "abcd", "dabc", "abc", "efabc", "eadd" })) << endl;
   // Should return true
   cout << vector_equal(
         { "abcd", "dabc", "abc" },
         Glob().Match("?a**c*", { "abcd", "dabc", "abc", "efabc", "eadd" })) << endl;
}

#endif
