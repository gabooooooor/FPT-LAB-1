// ---------- A) static stack + dynamic queue ----------

class StaticStack {
  private char[] l;
  private int top;
  private int size;

  public StaticStack(int size) {
    this.l = new char[size];
    this.top = 0;
    this.size = size;
  }

  public boolean isEmpty() {
    return top == 0;
  }

  public boolean isFull() {
    return top == size;
  }

  public void push(char x) {
    if (isFull()) {
      throw new RuntimeException("Full stack");
    }
    l[top] = x;
    top++;
  }

  public char pop() {
    if (isEmpty()) {
      throw new RuntimeException("Empty stack");
    }
    top--;
    return l[top];
  }
}

class Node {
  char data;
  Node next;

  public Node(char data) {
    this.data = data;
    this.next = null;
  }
}

class LinkedQueue {
  private Node head;
  private Node tail;

  public LinkedQueue() {
    head = null;
    tail = null;
  }

  public boolean isEmpty() {
    return head == null;
  }

  public void enqueue(char x) {
    Node node = new Node(x);
    if (isEmpty()) {
      head = node;
      tail = node;
    } else {
      tail.next = node;
      tail = node;
    }
  }

  public char dequeue() {
    if (isEmpty()) {
      throw new RuntimeException("Empty queue");
    }
    Node tmp = head;
    head = head.next;
    if (head == null) {
      tail = null;
    }
    return tmp.data;
  }
}

// ---------- B) dynamic stack + static queue ----------

class DynamicStack {
  private Node top;

  public DynamicStack() {
    top = null;
  }

  public boolean isEmpty() {
    return top == null;
  }

  public void push(char x) {
    Node node = new Node(x);
    node.next = top;
    top = node;
  }

  public char pop() {
    if (isEmpty()) {
      throw new RuntimeException("Empty stack");
    }
    Node tmp = top;
    top = top.next;
    return tmp.data;
  }
}

class StaticQueue {
  private char[] l;
  private int size;
  private int head;
  private int tail;

  public StaticQueue(int size) {
    this.l = new char[size];
    this.size = size;
    this.head = 0;
    this.tail = 0;
  }

  public boolean isEmpty() {
    return head == tail;
  }

  public boolean isFull() {
    return tail == size;
  }

  public void enqueue(char x) {
    if (isFull()) {
      throw new RuntimeException("Full queue");
    }
    l[tail] = x;
    tail++;
  }

  public char dequeue() {
    if (isEmpty()) {
      throw new RuntimeException("Empty queue");
    }
    char x = l[head];
    head++;
    return x;
  }
}

// ---------- Extra: char matrix with doubly linked lists ----------

class DNode<T> {
  T data;
  DNode<T> next;
  DNode<T> prev;

  public DNode(T data) {
    this.data = data;
    this.next = null;
    this.prev = null;
  }
}

class DList<T> {
  DNode<T> head;
  DNode<T> tail;
  int size;

  public DList() {
    head = null;
    tail = null;
    size = 0;
  }

  public void add(T x) {
    DNode<T> node = new DNode<T>(x);
    if (head == null) {
      head = node;
      tail = node;
    } else {
      tail.next = node;
      node.prev = tail;
      tail = node;
    }
    size++;
  }

  public T get(int i) {
    DNode<T> node = head;
    for (int k = 0; k < i; k++) {
      node = node.next;
    }
    return node.data;
  }
}

public class Palindrom {

  // keeps only letters and digits, in lower case
  static String normalize(String text) {
    StringBuilder result = new StringBuilder();
    for (int i = 0; i < text.length(); i++) {
      char ch = text.charAt(i);
      if (Character.isLetterOrDigit(ch)) {
        result.append(Character.toLowerCase(ch));
      }
    }
    return result.toString();
  }

  static boolean isPalindrome(String text) {
    String cleaned = normalize(text);
    StaticStack st = new StaticStack(cleaned.length());
    LinkedQueue lq = new LinkedQueue();

    for (int i = 0; i < cleaned.length(); i++) {
      char c = cleaned.charAt(i);
      st.push(c);
      lq.enqueue(c);
    }

    while (!st.isEmpty()) {
      char s = st.pop();
      char q = lq.dequeue();
      if (s != q) {
        return false;
      }
    }
    return true;
  }

  static boolean isPalindromeB(String text) {
    String cleaned = normalize(text);
    DynamicStack st = new DynamicStack();
    StaticQueue sq = new StaticQueue(cleaned.length());

    for (int i = 0; i < cleaned.length(); i++) {
      char c = cleaned.charAt(i);
      st.push(c);
      sq.enqueue(c);
    }

    while (!st.isEmpty()) {
      char s = st.pop();
      char q = sq.dequeue();
      if (s != q) {
        return false;
      }
    }
    return true;
  }

  static DList<DList<Character>> buildMatrix(String[] lines) {
    DList<DList<Character>> matrix = new DList<DList<Character>>();
    for (int i = 0; i < lines.length; i++) {
      DList<Character> row = new DList<Character>();
      for (int j = 0; j < lines[i].length(); j++) {
        row.add(lines[i].charAt(j));
      }
      matrix.add(row);
    }
    return matrix;
  }

  static boolean isRowPalindrome(DList<Character> row) {
    DNode<Character> left = row.head;
    DNode<Character> right = row.tail;
    for (int i = 0; i < row.size / 2; i++) {
      // Character is an object: we must use equals, not ==
      if (!left.data.equals(right.data)) {
        return false;
      }
      left = left.next;
      right = right.prev;
    }
    return true;
  }

  static boolean areRowsPalindromes(DList<DList<Character>> matrix) {
    DNode<DList<Character>> node = matrix.head;
    while (node != null) {
      if (!isRowPalindrome(node.data)) {
        return false;
      }
      node = node.next;
    }
    return true;
  }

  static boolean isColumnPalindrome(DList<DList<Character>> matrix, int j) {
    DNode<DList<Character>> top = matrix.head;
    DNode<DList<Character>> bottom = matrix.tail;
    for (int i = 0; i < matrix.size / 2; i++) {
      if (!top.data.get(j).equals(bottom.data.get(j))) {
        return false;
      }
      top = top.next;
      bottom = bottom.prev;
    }
    return true;
  }

  static boolean areColumnsPalindromes(DList<DList<Character>> matrix) {
    int columns = matrix.head.data.size;
    for (int j = 0; j < columns; j++) {
      if (!isColumnPalindrome(matrix, j)) {
        return false;
      }
    }
    return true;
  }

  // ---------- Measuring ----------

  static double measureA(String text) {
    long start = System.nanoTime();
    isPalindrome(text);
    long end = System.nanoTime();
    return (end - start) / 1000000.0;   // nanoseconds -> milliseconds
  }

  static double measureB(String text) {
    long start = System.nanoTime();
    isPalindromeB(text);
    long end = System.nanoTime();
    return (end - start) / 1000000.0;
  }

  public static void main(String[] args) {
    System.out.println("--- A) static stack + dynamic queue ---");
    System.out.println(isPalindrome("Anna"));                             // true
    System.out.println(isPalindrome("A man, a plan, a canal: Panama"));   // true
    System.out.println(isPalindrome("hello"));                            // false

    System.out.println("--- B) dynamic stack + static queue ---");
    System.out.println(isPalindromeB("Anna"));                            // true
    System.out.println(isPalindromeB("A man, a plan, a canal: Panama"));  // true
    System.out.println(isPalindromeB("hello"));                           // false

    System.out.println("--- Extra: matrix ---");
    DList<DList<Character>> m1 = buildMatrix(new String[] {"aba", "bab", "aba"});
    System.out.println(areRowsPalindromes(m1));      // true
    System.out.println(areColumnsPalindromes(m1));   // true

    DList<DList<Character>> m2 = buildMatrix(new String[] {"abc", "bab", "aba"});
    System.out.println(areRowsPalindromes(m2));      // false
    System.out.println(areColumnsPalindromes(m2));   // false

    System.out.println("--- Measuring (n, ms A, ms B, loops) ---");
    int[] sizes = {10, 100, 1000, 10000, 100000};
    for (int k = 0; k < sizes.length; k++) {
      int n = sizes[k];
      StringBuilder sb = new StringBuilder();
      for (int i = 0; i < n; i++) {
        sb.append('a');
      }
      String t = sb.toString();

      double ma = measureA(t);
      double mb = measureB(t);
      int loops = 3 * n;   // normalize + fill + empty, all n steps
      System.out.println(n + " " + String.format("%.3f", ma) + " " + String.format("%.3f", mb) + " " + loops);
    }
  }
}
