import time

# ---------- A) static stack + dynamic queue ----------

class StaticStack:
  def __init__(self, size):
    self.l = [None] * size
    self.top = 0
    self.size = size

  def is_empty(self):
    return self.top == 0

  def is_full(self):
    return self.top == self.size

  def push(self, x):
    if self.is_full():
      raise Exception("Full stack")
    self.l[self.top] = x
    self.top += 1

  def pop(self):
    if self.is_empty():
      raise Exception("Empty stack")
    self.top -= 1
    return self.l[self.top]

class Node:
  def __init__(self, data):
    self.data = data
    self.next = None

class LinkedQueue:
  def __init__(self):
    self.head = None
    self.tail = None

  def is_empty(self):
    return self.head == None

  def enqueue(self, x):
    node = Node(x)
    if self.is_empty():
      self.head = node
      self.tail = node
    else:
      self.tail.next = node
      self.tail = node

  def dequeue(self):
    if self.is_empty():
      raise Exception("Empty queue")
    tmp = self.head
    self.head = self.head.next
    if self.head == None:
      self.tail = None
    return tmp.data

def normalize(text):
  result = ""
  for ch in text:
    if ch.isalnum():
      result += ch.lower()
  return result

def is_palindrome(text):
  cleaned = normalize(text)
  st = StaticStack(len(cleaned))
  lq = LinkedQueue()

  for c in cleaned:
    st.push(c)
    lq.enqueue(c)

  while(not st.is_empty()):
    s = st.pop()
    q = lq.dequeue()
    if s != q:
      return False
  return True

# ---------- B) dynamic stack + static queue ----------

class DynamicStack:
  def __init__(self):
    self.top = None

  def is_empty(self):
    return self.top == None

  def push(self, x):
    node = Node(x)
    node.next = self.top
    self.top = node

  def pop(self):
    if self.is_empty():
      raise Exception("Empty stack")
    tmp = self.top
    self.top = self.top.next
    return tmp.data

class StaticQueue:
  def __init__(self, size):
    self.l = [None] * size
    self.size = size
    self.head = 0
    self.tail = 0

  def is_empty(self):
    return self.head == self.tail

  def is_full(self):
    return self.tail == self.size

  def enqueue(self, x):
    if self.is_full():
      raise Exception("Full queue")
    self.l[self.tail] = x
    self.tail += 1

  def dequeue(self):
    if self.is_empty():
      raise Exception("Empty queue")
    x = self.l[self.head]
    self.head += 1
    return x

def is_palindrome_b(text):
  cleaned = normalize(text)
  st = DynamicStack()
  sq = StaticQueue(len(cleaned))

  for c in cleaned:
    st.push(c)
    sq.enqueue(c)

  while(not st.is_empty()):
    s = st.pop()
    q = sq.dequeue()
    if s != q:
      return False
  return True

# ---------- Extra: char matrix with doubly linked lists ----------

class DNode:
  def __init__(self, data):
    self.data = data
    self.next = None
    self.prev = None

class DList:
  def __init__(self):
    self.head = None
    self.tail = None
    self.size = 0

  def add(self, x):
    node = DNode(x)
    if self.head == None:
      self.head = node
      self.tail = node
    else:
      self.tail.next = node
      node.prev = self.tail
      self.tail = node
    self.size += 1

  def get(self, i):
    node = self.head
    for k in range(i):
      node = node.next
    return node.data

def build_matrix(lines):
  matrix = DList()
  for line in lines:
    row = DList()
    for ch in line:
      row.add(ch)
    matrix.add(row)
  return matrix

def is_row_palindrome(row):
  left = row.head
  right = row.tail
  for i in range(row.size // 2):
    if left.data != right.data:
      return False
    left = left.next
    right = right.prev
  return True

def are_rows_palindromes(matrix):
  node = matrix.head
  while node != None:
    if not is_row_palindrome(node.data):
      return False
    node = node.next
  return True

def is_column_palindrome(matrix, j):
  top = matrix.head
  bottom = matrix.tail
  for i in range(matrix.size // 2):
    if top.data.get(j) != bottom.data.get(j):
      return False
    top = top.next
    bottom = bottom.prev
  return True

def are_columns_palindromes(matrix):
  columns = matrix.head.data.size
  for j in range(columns):
    if not is_column_palindrome(matrix, j):
      return False
  return True

# ---------- Tests ----------

print("--- A) static stack + dynamic queue ---")
print(is_palindrome("Anna"))                             # True
print(is_palindrome("A man, a plan, a canal: Panama"))   # True
print(is_palindrome("hello"))                            # False

print("--- B) dynamic stack + static queue ---")
print(is_palindrome_b("Anna"))                             # True
print(is_palindrome_b("A man, a plan, a canal: Panama"))   # True
print(is_palindrome_b("hello"))                            # False

print("--- Extra: matrix ---")
m1 = build_matrix(["aba", "bab", "aba"])
print(are_rows_palindromes(m1))      # True
print(are_columns_palindromes(m1))   # True

m2 = build_matrix(["abc", "bab", "aba"])
print(are_rows_palindromes(m2))      # False
print(are_columns_palindromes(m2))   # False

# ---------- Measuring ----------

def measure_a(text):
  start = time.perf_counter()
  result = is_palindrome(text)
  end = time.perf_counter()
  return result, (end - start) * 1000

def measure_b(text):
  start = time.perf_counter()
  result = is_palindrome_b(text)
  end = time.perf_counter()
  return result, (end - start) * 1000

print("--- Measuring (n, result A, ms A, result B, ms B, loops) ---")
tests = ["a" * 10, "a" * 100, "a" * 1000, "a" * 10000, "a" * 100000]

for t in tests:
  ra, ma = measure_a(t)
  rb, mb = measure_b(t)
  loops = len(t) + 2 * len(normalize(t))
  print(len(t), ra, round(ma, 3), rb, round(mb, 3), loops)
