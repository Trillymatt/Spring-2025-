# Remove parentheses, whitespace, and dashes
s/[() -]//g

# Swap the third and eighth digit using simpler grouping
s/\(..\)\(.\)\(....\)\(.\)\(.*\)/\1\4\3\2\5/

# Replace digits with random letters (alternating case)
y/0123456789/FSAetDqwTr/

# Insert first 10 letters of your name after the third phone number
3a\
MattNorman
