package ru.arjentix.hash_func;

public class Hasher implements IHasher {
  /**
   * @brief   calculates hash of input string
   * 
   * @details https://cp-algorithms.com/string/string-hashing.html#:~:text=Hashing%20algorithms%20are%20helpful%20in%20solving%20a%20lot%20of%20problems.&text=The%20idea%20behind%20strings%20is,an%20O(1)%20operation.
   * 
   * @param   input input string to hash
   * @return  hash of input string
   */
  @Override
  public long hash(String input) {
    final int p = 127;
    final int m = (int) 1e9 + 9;
    long hashValue = 0;
    long power = 1;

    for (char c : input.toCharArray()) {
      hashValue = (hashValue + c * power) % m;
      power = (power * p) % m;
    }

    return hashValue;
  }
}
