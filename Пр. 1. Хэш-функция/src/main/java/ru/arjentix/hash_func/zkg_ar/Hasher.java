package ru.arjentix.hash_func.zkg_ar;

import ru.arjentix.hash_func.IHasher;

public class Hasher implements IHasher {
  /**
   * Code below was written by Zkg-ar. See https://github.com/Zkg-ar/HashFunc/blob/master/HashFunc1/src/com/company/Main.java
   * I changed the return type from String to long and added some comments
   */

  // WTF? Hi was using static hash variable. It was breaking all things, so I fixed id
  // private static long hash = 0; 
  private static char [] alphabet = new char[] { // Hash function works only for russian language? Why?
            'а','б','в','г','д','е','ё','ж',
            'з','и','й','к','л','м','н','о',
            'п','р','с','т','у','ф','х','ц',
            'ч','ш','щ','ъ','ы','ь','э','ю','я'
  };

  @Override
  public long hash(String input){
    long hash = 0; // My fix
    int sum = 0,first=0,last=0;
    input = input.toLowerCase();
    String [] words = input.split("\\s|[.!,?\\-]");

    for (int i = 0;i<words.length;i++){
      for(int j = 0;j<words[i].length();j++){

        for (int k = 0;k<alphabet.length;k++) {
          if(words[i].charAt(0)==alphabet[k]){
            first=k;
          }
          if(words[i].charAt(words[i].length()-1)==alphabet[k]){
            last=k+1;
          }

          if (words[i].charAt(j) == alphabet[k]) {
            sum += k;
          }

        }

      }
      sum = sum * ((last-first));

      hash += sum;
      sum = 0;

    }

    return hash;
  }

}
