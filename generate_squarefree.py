# Generates test input for 2 long square free words

print'2 A 3'

n=10**7 # word length

# SOURCE: https://codegolf.stackexchange.com/a/10606
# Generates squarefree word using difference of thue-morse sequence
x=[0]
while x==x[:n]:x+=[1-y for y in x]
print''.join('ABC'[x[i+1]-x[i]]for i in range(n))

# SOURCE: https://codegolf.stackexchange.com/a/10602
# Generates square-free word using john leech's method
s='A'
while len(s)<=n:s=''.join('ABCBCACABBCAABCCABBCACABABCBCACABBCAABC'[ord(t)%5::3]for t in s)
print s[:n]