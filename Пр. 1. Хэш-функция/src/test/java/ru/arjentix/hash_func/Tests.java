package ru.arjentix.hash_func;

import java.lang.StringBuilder;
import java.util.concurrent.ThreadLocalRandom;
import org.junit.Test;
import static org.junit.Assert.*;

public class Tests {

  private static char [] alphabet = new char[] {
    'а','б','в','г','д','е','ё','ж',
    'з','и','й','к','л','м','н','о',
    'п','р','с','т','у','ф','х','ц',
    'ч','ш','щ','ъ','ы','ь','э','ю','я'
  };

  private IHasher buildHasher() {
   return new ru.arjentix.hash_func.zkg_ar.Hasher();
  }

  @Test
  public void sameHashForSameInputTest() {
    // Wasn't working with original zkg_ar hasher cause of static hash variable

    IHasher hasher = buildHasher();
    final String input = generateRandomString();

    assertEquals(hasher.hash(input), hasher.hash(input));
  }

  @Test
  public void preImageResistanceTest() {
    IHasher hasher = buildHasher();
    final int tryCount = 100;

    for (int i = 0; i < tryCount; ++i) {
      String randomInput = generateRandomString();

      long firstHash = hasher.hash(randomInput);
      randomInput = null; // To mention that it won't be using

      final int divisor = findDivisor(firstHash);
      char first;
      char last;
      if (divisor >= 0) {
        first = alphabet[0];
        last = alphabet[(divisor - 1) % alphabet.length];
      } else {
        last = alphabet[0];
        first = alphabet[(-1*divisor + 1) % alphabet.length];
      }

      final int sum = (int) firstHash / divisor;
      StringBuilder builder = new StringBuilder(Character.toString(first));
      for (int j = 0; j < sum; ++j) {
        builder.append(alphabet[1]);
      }
      builder.append(last);

      final String preImage = builder.toString();
      assertNotEquals(firstHash, hasher.hash(preImage));
    }
  }
  
  @Test
  public void secondPreImageResistanceTest() {
    IHasher hasher = buildHasher();
    String input1 = "";
    String input2 = "";

    while (input1.equals(input2)) {
      input1 = generateRandomString();

      StringBuilder builder = new StringBuilder(Character.toString(input1.charAt(0)));
      builder.append(input1.charAt(2));
      builder.append(input1.charAt(1));
      builder.append(input1.substring(3));
      input2 = builder.toString();
    }

    assertNotEquals(hasher.hash(input1), hasher.hash(input2));
  }

  private String generateRandomString() {
    StringBuilder builder = new StringBuilder();
    int length = ThreadLocalRandom.current().nextInt(16, 129);
    
    for (int i = 0; i < length; ++i) {
      int pos = ThreadLocalRandom.current().nextInt(0, alphabet.length);
      builder.append(alphabet[pos]);
    }

    return builder.toString();
  }

  private int findDivisor(long hash) {
    for (int i = 2; i < Math.abs(hash) / 2 && i < 100; ++i) {
      if (hash % i == 0) {
        return i * (int) Math.signum(hash);
      }
    }

    return 1;
  }
}
