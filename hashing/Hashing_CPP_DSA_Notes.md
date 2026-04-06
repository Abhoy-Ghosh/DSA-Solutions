# Hashing in C++ — Interview-Ready DSA Notes

---

## Table of Contents

1. [Definition / Intuition](#1-definition--intuition)
2. [How Hashing Works](#2-how-hashing-works)
3. [Hash Functions](#3-hash-functions)
4. [Collision Resolution Techniques](#4-collision-resolution-techniques)
5. [C++ STL: unordered_map & unordered_set](#5-c-stl-unordered_map--unordered_set)
6. [ordered vs unordered Containers](#6-ordered-vs-unordered-containers)
7. [Time and Space Complexity](#7-time-and-space-complexity)
8. [Custom Hash Functions in C++](#8-custom-hash-functions-in-c)
9. [Important Edge Cases / Pitfalls](#9-important-edge-cases--pitfalls)
10. [Example Problems](#10-example-problems)
11. [Decision Rules](#11-decision-rules)
12. [Best Practices & Interview Tips](#12-best-practices--interview-tips)
13. [Common Mistakes](#13-common-mistakes)
14. [Summary / Key Takeaways](#14-summary--key-takeaways)

---

## 1. Definition / Intuition

**Hashing** is a technique that maps data of arbitrary size to fixed-size values (called **hash codes** or **hash values**) using a **hash function**. The result is used as an index into a data structure called a **hash table**, enabling near-constant-time lookups, insertions, and deletions.

### Real-World Analogy

Think of a library with books organized by the last two digits of their ISBN. Instead of searching every shelf, you go directly to the shelf labeled with those digits. Hashing works the same way — it computes a "shelf number" (index) from the data itself.

### Core Idea

```
key  ──→  hash_function(key)  ──→  index  ──→  value stored at index
```

---

## 2. How Hashing Works

### Internal Structure of a Hash Table

```
Buckets (array of size N):
Index 0: [ ]
Index 1: [ ("apple", 5) ]
Index 2: [ ("banana", 3) → ("grape", 7) ]   ← collision handled by chaining
Index 3: [ ]
Index 4: [ ("mango", 2) ]
...
```

### Steps

1. Compute `h = hash_function(key) % table_size`
2. Go to index `h` in the array
3. Store/retrieve the value at that index
4. Handle collisions if two keys map to the same index

### Load Factor

```
Load Factor (α) = Number of elements / Number of buckets
```

- A higher load factor means more collisions and degraded performance.
- C++ `unordered_map` rehashes automatically when `load_factor > max_load_factor` (default: 1.0).

---

## 3. Hash Functions

A good hash function must be:
- **Deterministic** — same input always gives same output
- **Uniform** — distributes keys evenly across buckets
- **Fast** — O(1) to compute
- **Minimal collisions**

### Common Hash Function Strategies

**Division Method:**
```cpp
int hash(int key, int tableSize) {
    return key % tableSize;
}
```

**Multiplication Method:**
```cpp
int hash(int key, int tableSize) {
    double A = 0.6180339887; // (sqrt(5) - 1) / 2
    return (int)(tableSize * fmod(key * A, 1.0));
}
```

**Polynomial Rolling Hash (for strings):**
```cpp
long long hashString(const string& s, int p = 31, int m = 1e9 + 9) {
    long long hashVal = 0, power = 1;
    for (char c : s) {
        hashVal = (hashVal + (c - 'a' + 1) * power) % m;
        power = (power * p) % m;
    }
    return hashVal;
}
```

---

## 4. Collision Resolution Techniques

### 4.1 Separate Chaining (Open Hashing)

Each bucket holds a **linked list** (or vector) of all key-value pairs that hash to that index.

```
Index 2: → ("banana", 3) → ("grape", 7) → NULL
```

```cpp
// Conceptual implementation
vector<list<pair<int,int>>> table(SIZE);

void insert(int key, int val) {
    int idx = key % SIZE;
    table[idx].push_back({key, val});
}

int search(int key) {
    int idx = key % SIZE;
    for (auto& p : table[idx])
        if (p.first == key) return p.second;
    return -1;
}
```

**C++ STL uses separate chaining internally for `unordered_map`.**

### 4.2 Open Addressing (Closed Hashing)

All elements are stored **within the array itself**. On collision, probe for the next available slot.

#### Linear Probing

```
h(key, i) = (hash(key) + i) % N
```

```cpp
// Linear probing insert (simplified)
int table[SIZE];
fill(table, table + SIZE, -1);

void insert(int key) {
    int idx = key % SIZE;
    while (table[idx] != -1)
        idx = (idx + 1) % SIZE;
    table[idx] = key;
}
```

*Problem:* **Primary clustering** — long chains of filled buckets form.

#### Quadratic Probing

```
h(key, i) = (hash(key) + i*i) % N
```

*Problem:* **Secondary clustering** — keys with the same initial hash follow the same probe sequence.

#### Double Hashing

```
h(key, i) = (h1(key) + i * h2(key)) % N
```

Where `h2(key)` should never be zero, e.g., `h2(key) = 7 - (key % 7)`.

*Best open addressing strategy — avoids clustering.*

### Comparison Table

| Technique          | Handles Clustering | Cache Friendly | Deletion Ease | Used In      |
|--------------------|-------------------|----------------|---------------|--------------|
| Separate Chaining  | Yes (no clustering) | No (pointers) | Easy          | STL (C++)    |
| Linear Probing     | No (primary)       | Yes            | Tricky        | Python dicts |
| Quadratic Probing  | Partial (secondary)| Moderate       | Tricky        | Some DBs     |
| Double Hashing     | Yes                | Moderate       | Tricky        | Custom impl  |

---

## 5. C++ STL: unordered_map & unordered_set

### unordered_map

```cpp
#include <unordered_map>
using namespace std;

unordered_map<string, int> freq;

// Insert / Update
freq["apple"] = 5;
freq["banana"]++;

// Access with default value
int val = freq["cherry"]; // inserts 0 if not found (creates entry!)

// Safe access
if (freq.count("apple")) {
    cout << freq["apple"];
}
// OR
auto it = freq.find("apple");
if (it != freq.end()) {
    cout << it->second;
}

// Iterate
for (auto& [key, val] : freq) {
    cout << key << ": " << val << "\n";
}

// Erase
freq.erase("apple");

// Size, empty
cout << freq.size();
cout << freq.empty();
```

### unordered_set

```cpp
#include <unordered_set>

unordered_set<int> seen;

seen.insert(42);
seen.insert(10);

if (seen.count(42)) cout << "Found!\n";
if (seen.find(99) == seen.end()) cout << "Not found\n";

seen.erase(10);

for (int x : seen) cout << x << " ";
```

### Key Member Functions Summary

| Function              | Description                                    | Complexity |
|-----------------------|------------------------------------------------|------------|
| `insert({k, v})`      | Insert key-value pair                          | O(1) avg   |
| `operator[]`          | Access/insert by key                           | O(1) avg   |
| `find(k)`             | Returns iterator, `end()` if not found        | O(1) avg   |
| `count(k)`            | Returns 0 or 1                                 | O(1) avg   |
| `erase(k)`            | Remove element by key                          | O(1) avg   |
| `size()`              | Number of elements                             | O(1)       |
| `clear()`             | Remove all elements                            | O(n)       |
| `reserve(n)`          | Pre-allocate n buckets (prevents rehashing)    | O(n)       |
| `bucket_count()`      | Number of current buckets                      | O(1)       |
| `load_factor()`       | Current load factor                            | O(1)       |

---

## 6. ordered vs unordered Containers

| Feature              | `map` / `set`          | `unordered_map` / `unordered_set` |
|----------------------|------------------------|-----------------------------------|
| Internal Structure   | Red-Black BST          | Hash Table                        |
| Key Ordering         | Sorted (ascending)     | None                              |
| Lookup / Insert      | O(log n)               | O(1) average, O(n) worst         |
| Space                | O(n)                   | O(n) (+ overhead for buckets)    |
| Key Requirement      | Must support `<`       | Must support `==` and `hash<>`   |
| Cache Performance    | Poor (pointer-based)   | Better for flat access            |
| Iteration Order      | Sorted                 | Arbitrary                         |
| Worst Case           | O(log n)               | O(n) — hash collision attack     |

### When to Use Which

Use `unordered_map` when:
- You need O(1) average lookup and order does not matter.
- Keys are integers, strings, or other hashable types.

Use `map` when:
- You need sorted order or range queries (e.g., `lower_bound`).
- Worst-case O(log n) is required (competitive programming with adversarial inputs).
- Key type is not hashable by default.

---

## 7. Time and Space Complexity

### Time Complexity

| Operation  | Average Case | Worst Case   | Notes                               |
|------------|--------------|--------------|-------------------------------------|
| Insert     | O(1)         | O(n)         | Worst case: all keys collide        |
| Search     | O(1)         | O(n)         | Degrades with high load factor      |
| Delete     | O(1)         | O(n)         | Same as search + pointer adjustment |
| Rehash     | O(n)         | O(n)         | Triggered automatically by STL      |

### Space Complexity

- O(n) for n key-value pairs stored.
- Additional overhead for empty buckets: O(bucket_count).

### Amortized Analysis

Insertions are O(1) **amortized** because rehashing (which is O(n)) happens rarely — only when the load factor threshold is exceeded, which occurs at most O(log n) times for n insertions.

---

## 8. Custom Hash Functions in C++

Needed when:
- Key is a custom struct or class.
- You want to combine multiple fields as a key.
- You need a better hash to avoid collisions (important in competitive programming).

### Custom Hash for Struct

```cpp
struct Point {
    int x, y;
    bool operator==(const Point& o) const {
        return x == o.x && y == o.y;
    }
};

struct PointHash {
    size_t operator()(const Point& p) const {
        // Combine hashes: shift one and XOR
        return hash<int>()(p.x) ^ (hash<int>()(p.y) << 16);
    }
};

unordered_map<Point, int, PointHash> dist;
dist[{0, 0}] = 0;
```

### Custom Hash for pair<int, int>

```cpp
struct PairHash {
    size_t operator()(const pair<int,int>& p) const {
        return hash<long long>()(((long long)p.first << 32) | (unsigned int)p.second);
    }
};

unordered_map<pair<int,int>, int, PairHash> dp;
```

### Anti-Hack Hash (Competitive Programming)

Standard `unordered_map` with integer keys can be hacked using crafted inputs that cause all keys to collide. Use a custom hash with a random seed:

```cpp
struct SafeHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

unordered_map<long long, int, SafeHash> mp;
```

---

## 9. Important Edge Cases / Pitfalls

### 1. Operator[] creates entries on access

```cpp
unordered_map<string, int> mp;
int x = mp["missing"]; // Inserts "missing" → 0 into the map!
// Use .count() or .find() for safe reads
```

### 2. Iterating while modifying

```cpp
// UNDEFINED BEHAVIOR
for (auto& [k, v] : mp) {
    if (v == 0) mp.erase(k); // modifying during iteration
}

// CORRECT: collect keys first
vector<string> toRemove;
for (auto& [k, v] : mp)
    if (v == 0) toRemove.push_back(k);
for (auto& k : toRemove) mp.erase(k);
```

### 3. Rehashing invalidates iterators

```cpp
auto it = mp.begin();
mp.insert({"newkey", 1}); // may trigger rehash
// it is now potentially invalid!
```

### 4. Integer overflow in hash combination

```cpp
// Bad: can overflow and produce poor distribution
size_t h = key.x * 1000000 + key.y;

// Better: use prime multiplication and XOR
size_t h = hash<int>()(key.x) * 2654435761ULL ^ hash<int>()(key.y);
```

### 5. Worst-case O(n) for unordered_map with adversarial inputs

Default hash for integers is predictable. In competitive programming, use `SafeHash` (see Section 8) or use `map` when worst-case guarantees are needed.

### 6. Negative indices in manual hash tables

```cpp
int h = key % SIZE; // If key is negative, h can be negative in C++
h = (h + SIZE) % SIZE; // Always non-negative
```

---

## 10. Example Problems

### Problem 1: Two Sum

**Task:** Given an array and a target, return indices of the two numbers that add up to the target.

**Approach:** For each element `x`, check if `target - x` is already in the hash map.

```cpp
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen; // value → index

    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (seen.count(complement)) {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {}; // no solution
}
```

**Complexity:** Time O(n), Space O(n)

---

### Problem 2: Longest Subarray with Zero Sum

**Task:** Find the length of the longest subarray with sum 0.

**Approach:** Track prefix sums. If `prefix[j] == prefix[i]`, then subarray `(i, j]` has sum 0. Store first occurrence of each prefix sum.

```cpp
int longestZeroSumSubarray(vector<int>& arr) {
    unordered_map<int, int> firstOccurrence;
    firstOccurrence[0] = -1; // prefix sum 0 at index -1 (before start)

    int prefixSum = 0, maxLen = 0;

    for (int i = 0; i < arr.size(); i++) {
        prefixSum += arr[i];

        if (firstOccurrence.count(prefixSum)) {
            maxLen = max(maxLen, i - firstOccurrence[prefixSum]);
        } else {
            firstOccurrence[prefixSum] = i;
        }
    }
    return maxLen;
}
```

**Complexity:** Time O(n), Space O(n)

---

### Problem 3: Group Anagrams

**Task:** Group strings that are anagrams of each other.

**Approach:** Sort each string to create a canonical key. All anagrams map to the same sorted form.

```cpp
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;

    for (const string& s : strs) {
        string key = s;
        sort(key.begin(), key.end()); // canonical form
        groups[key].push_back(s);
    }

    vector<vector<string>> result;
    for (auto& [key, group] : groups) {
        result.push_back(group);
    }
    return result;
}
```

**Complexity:** Time O(n * k log k) where k = max string length, Space O(n * k)

---

## 11. Decision Rules

```
Do you need fast lookup, insert, delete?
├── Yes → Use hashing (unordered_map / unordered_set)
│   ├── Need sorted order or range queries? → Use map / set instead
│   ├── Need guaranteed O(log n) worst case? → Use map / set
│   ├── Key is a custom type? → Provide custom hash + operator==
│   └── Adversarial input possible? → Use SafeHash
└── No → Array or linked list may suffice
```

```
Need frequency count?      → unordered_map<T, int>
Need presence check only?  → unordered_set<T>
Need ordered traversal?    → map<T, V> or set<T>
Need both fast + ordered?  → No perfect O(1) solution; use map or augment
Need multi-values per key? → unordered_map<T, vector<V>>
```

---

## 12. Best Practices & Interview Tips

### General

- **Prefer `.count()` or `.find()` over `operator[]`** when you don't want to insert a default value.
- **Use `reserve(n)`** before bulk insertions to avoid repeated rehashing.
- **Use structured bindings** `auto& [k, v]` for clean iteration (C++17).
- Always **initialize counts to 0** using `mp[key]++` (exploits default initialization).

### Interview-Level Insights

- Mention **average vs worst-case complexity** proactively. Interviewers value this distinction.
- Know that the **worst case is O(n)** due to collisions, and mention hash function quality.
- For strings as keys, **sort the string as a canonical key** for anagram-type problems.
- For **subarray sum problems**, always think of prefix sums + hash map.
- When asked about custom keys, demonstrate knowledge of **how to write a hash functor**.
- Know the **difference between `map` and `unordered_map`** — sorted vs. unsorted, log n vs O(1).

### Tricks

```cpp
// Count character frequencies
string s = "hello";
unordered_map<char, int> freq;
for (char c : s) freq[c]++;

// Check if two strings are anagrams
bool isAnagram(string a, string b) {
    if (a.size() != b.size()) return false;
    unordered_map<char, int> cnt;
    for (char c : a) cnt[c]++;
    for (char c : b) {
        if (--cnt[c] < 0) return false;
    }
    return true;
}
```

---

## 13. Common Mistakes

### Mistake 1: Using `operator[]` for read-only access

```cpp
// BAD: inserts default value if key absent
if (mp["key"] == 5) { ... }

// GOOD: does not modify the map
auto it = mp.find("key");
if (it != mp.end() && it->second == 5) { ... }
```

### Mistake 2: Assuming iteration order

```cpp
// WRONG assumption: unordered_map iterates in insertion order
// unordered_map has NO guaranteed iteration order
// Use map if you need sorted output
```

### Mistake 3: Using unordered containers without a proper hash for custom types

```cpp
// COMPILE ERROR: no hash<Point> defined
unordered_map<Point, int> mp; // will not compile without custom hash
```

### Mistake 4: Not accounting for negative keys in manual hash tables

```cpp
int idx = key % N; // May be negative for negative keys
idx = ((idx % N) + N) % N; // Correct
```

### Mistake 5: Forgetting to handle the prefix sum base case

```cpp
// Forget this and longestZeroSumSubarray fails for subarrays starting at index 0
firstOccurrence[0] = -1; // Always initialize!
```

### Mistake 6: Erasing elements by value (unordered_set erase)

```cpp
unordered_set<int> s = {1, 2, 3};
s.erase(2);     // Erases element with value 2 — correct
// s.erase(it) also works when you have an iterator
```

### Mistake 7: Mixing up erase(key) vs erase(iterator)

```cpp
unordered_map<int,int> mp = {{1,10},{2,20}};
mp.erase(1);         // Erases by key — OK
auto it = mp.find(2);
mp.erase(it);        // Erases by iterator — OK
```

---

## 14. Summary / Key Takeaways

| Concept                   | Key Point                                                         |
|---------------------------|-------------------------------------------------------------------|
| Hash Function             | Maps key → index; must be fast, uniform, deterministic           |
| Collision Resolution      | Chaining (STL default) or Open Addressing (linear/quadratic/double) |
| `unordered_map`           | O(1) avg insert/lookup; no ordering                              |
| `map`                     | O(log n) guaranteed; sorted; use when order matters              |
| Load Factor               | > 1 triggers rehash; control with `reserve()`                    |
| Custom Hash               | Required for custom key types; use `operator==` + hash functor   |
| Anti-hack hash            | Use `splitmix64` with random seed in competitive programming      |
| Common pattern: frequency | `unordered_map<T, int>` with `mp[key]++`                         |
| Common pattern: presence  | `unordered_set<T>`                                               |
| Common pattern: prefix sum| `unordered_map<int, int>` with `firstOccurrence[0] = -1`        |

### Quick Complexity Reference

```
Operation        | unordered_map  | map
-----------------+----------------+---------
Insert           | O(1) avg       | O(log n)
Lookup           | O(1) avg       | O(log n)
Delete           | O(1) avg       | O(log n)
Iteration        | O(n)           | O(n)
Min/Max element  | O(n)           | O(log n)
Range query      | Not supported  | O(log n)
```

### Final Interview Checklist

- Know when to prefer `map` over `unordered_map` (ordering, worst-case guarantees).
- Be able to write a custom hash for pairs/structs from memory.
- Remember: `operator[]` **inserts** on missing keys — always use `find()` or `count()` for safe reads.
- For subarray/prefix sum problems, always think of `firstOccurrence[0] = -1`.
- Mention load factor, rehashing, and amortized complexity when discussing performance.

---

*Notes prepared for interview-ready revision. Topic: Hashing in C++.*
