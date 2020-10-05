import collections

def unique_words(banned_words, para):
  banned_set = set(banned_words)
  count = {}
  for c in "!?;.,'":
    para = para.replace(c, " ")

  count = collections.Counter(word for word in para.lower().split())

  max_count = 0
  most_frequent_word = ""
  for word in count:
    if word not in banned_set and count[word] > max_count:
      max_count = count[word]
      most_frequent_word = word

  print count
  return most_frequent_word, max_count

if __name__ == "__main__":
  para = "Bob hit a ball, the hit BALL flew far after it was hit."
  banned = ["hit"]

  fword, cnt = unique_words(banned, para)

  print "%s: %d" %(fword, cnt)
  
  
